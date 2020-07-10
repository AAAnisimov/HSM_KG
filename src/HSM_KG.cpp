#include <stdexcept>
#include <memory>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <future>
#include <experimental/filesystem>

#include <cstring> // strerror
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h> // ::close

#include <netdb.h>
#include <netinet/in.h>
#include "json/single_include/nlohmann/json.hpp"
#include "Crypt.hpp"
#include "Base64.h"
using json = nlohmann::json;

using namespace std::literals;
namespace fs = std::experimental::filesystem;

static std::map <std::string, int> URIs;
static const char *Err404="HTTP/1.1 404 Not Found\nServer: final\nDate: Mon, 27 Mar 2017 09:22:16 GMT\nContent-Type: text/html\nContent-Length: 162\
        \nConnection: close\n\n<html>\n<head><title>404 Not Found</title></head>\n<body bgcolor=\"white\">\
        \n<center><h1>404 Not Found</h1></center>\
        \n<hr><center>HSM</center>\n</body>\n</html>\n\n";


/** Returns true on success, or false if there was an error */
int set_nonblock(int fd)
{
    int flags;
#if defined(O_NONBLOCK)
    if (-1 ==(flags=fcntl(fd,F_GETFL,0)))
    	flags=0;
    return fcntl(fd, F_SETFL, flags|O_NONBLOCK);
#else
    flags=1;
    return ioctl(fd,FIOBIO,&flags);
#endif
}
struct Header{
	Header(std::string Path_="",std::string Body_="", bool HasBody_=false,bool ExpectContinue_=false, std::size_t BodySize_=0):Path(Path_),Body(Body_),HasBody(HasBody_),ExpectContinue(ExpectContinue_),BodySize(BodySize_)
	{
		ErrorCode=0;
		Error="";
	}
	Header(int ErrorCode_, std::string Error_=""):ErrorCode(ErrorCode_), Error(Error_){}
	Header & operator=(Header &&a)
	{
		std::swap(a.Path,Path);
		std::swap(a.Body,Body);
		std::swap(a.HasBody,HasBody);
		std::swap(a.ExpectContinue,ExpectContinue);
		std::swap(a.BodySize,BodySize);
		return *this;
	}
	Header(Header&& a) noexcept
	{
		std::swap(a.Path,Path);
		std::swap(a.Body,Body);
		std::swap(a.Error,Error);
		std::exchange(ErrorCode,a.ErrorCode);
		std::exchange(HasBody,a.HasBody);
		std::exchange(ExpectContinue,a.ExpectContinue);
		std::exchange(BodySize,a.BodySize);
	}
	std::string Path="";
	std::string Body="";
	int ErrorCode;
	std::string Error;
	bool HasBody=false;
	bool ExpectContinue=false;
	std::size_t BodySize=0;
};
std::ostream& operator<<(std::ostream& os, const Header& Hdr) {
	return os 	<< "Path: " << 				Hdr.Path << std::endl
				<< "ExpectContinue: " << 	Hdr.ExpectContinue << std::endl
				<< "HasBody: " << 			Hdr.HasBody << std::endl
				<< "BodySize: " << 			Hdr.BodySize << std::endl
				<< "Body: " << 				Hdr.Body << std::endl
    			<< "ErrorCode: " << 		Hdr.ErrorCode << std::endl
    			<< "Error: " << 			Hdr.Error << std::endl;
}

struct Job
{
    int         sockfd;
    std::string Header="",Body="";

    Job(int sockfd,std::string&& Header_,std::string&& Body_="")
        : sockfd(sockfd)
    {
    		std::swap(Header,Header_);
    		std::swap(Body,Body_);
    }
    ~Job()
    {
        if (sockfd)
        {
            ::close(sockfd);
        }
    }
};

class SimpleSocket
{
    int sockfd;
    public:
        SimpleSocket(int port)
        {
            sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0)
            {
                throw std::runtime_error("Failed to create socket");
            }

            struct sockaddr_in serv_addr;
            ::bzero((char *) &serv_addr, sizeof(serv_addr));

            serv_addr.sin_family        = AF_INET;
            serv_addr.sin_addr.s_addr   = INADDR_ANY;
            serv_addr.sin_port          = htons(port);

            if (::bind(sockfd, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0)
            {
                throw std::runtime_error("Failed to bind to port: "s + std::strerror(errno));
            }
        }
        ~SimpleSocket()
        {
            ::close(sockfd);
        }
        int waitForConnection()
        {
            int result = ::listen(sockfd,5);
            if (result < 0)
            {
                throw std::runtime_error("Listen failed");
            }
            sockaddr_in     cli_addr;
            socklen_t       clilen      = sizeof(cli_addr);
            int             newsockfd   = ::accept(sockfd, reinterpret_cast<sockaddr*>(&cli_addr), &clilen);
            //set_nonblock(sockfd);
            if (newsockfd < 0)
            {
                throw std::runtime_error("accept failed");
            }
            return newsockfd;
        }
};

std::string BadRequest (int code, std::string Text)
{
	std::string Rval="{\r\n\t\"errorCode\":"+std::to_string(code)+",\r\n\t\"errorText\":\""+Text+"\"\r\n\r\n}";
	Rval="HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\nContent-Length:"+std::to_string(Rval.length()+2)+"\r\n";
	return Rval;
}

class Respomces
{
    public:
        static std::unique_ptr<Job> getJob(int sockfd, Header&& H)
        {
        	if (H.ErrorCode)
				return std::make_unique<Job>(sockfd,BadRequest(H.ErrorCode, H.Error),"{\r\n\t\"errorCode\":"+std::to_string(H.ErrorCode)+",\r\n\t\"errorText\":\""+H.Error+"\"\r\n\r\n}");
        	json Params;
        	if (H.HasBody)
        	{
        		Params=json::parse(H.Body);
        	}
        	switch (URIs[H.Path])
        	{
        	case 1: //Keys
        		if (Params["type"]==1)
				{//Symmetric
        			return std::make_unique<Job>(sockfd,BadRequest(100, "Not implemented yet..."),"");
				}
        		else
        		{
        			return std::make_unique<Job>(sockfd,"HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n","{\"keys\": [\"0000\"] }");
        		}
        		break;
        	case 2:         //Symmetric sign
        		if (Params["key"]=="0000")
				{
					int BlockCount=Params["blockCount"];
					int BlockLength=Params["blockLength"];
					int ImitoLength=Params["imitoLength"];
					std::string Codes=base64_decode(Params["codes"]);
#ifdef __DEBUG
					std::cerr<<getpid()<<"Parsing result: \n"<<
    		    		"\tblockCount: "<<BlockCount<<std::endl<<
    		    		"\tblockLength: "<<BlockLength<<std::endl<<
    		    		"\timitoLength: "<<ImitoLength<<std::endl<<
    		    		"\tcodes: "<<Codes<<std::endl;
#endif
					std::array<unsigned char,32> Hash;
					std::string Hashes="";
					int Blocks=0;
					unsigned char *HashArray=new unsigned char [ImitoLength*Codes.length()/BlockLength];
					memset  (HashArray,0,ImitoLength*Codes.length()/BlockLength);
					for (unsigned i = 0; i < Codes.length(); i += BlockLength,Blocks++)
					{
#ifdef __DEBUG
						std::cerr<<"Hashing: "<<Codes.substr(i, BlockLength)<< "\tGot hash: ";
#endif
						Hash=hash(Codes.substr(i, BlockLength).data());
#ifdef __DEBUG
						for (int i=0;i<32;i++)
						    fprintf(stderr,"%02hhx:", Hash[i]);
						std::cerr<<"\n";
#endif
						memcpy (
								HashArray+Blocks*ImitoLength,
								Hash.data(),
								ImitoLength);
					}
					if (Blocks!=BlockCount)
					{
#ifdef __DEBUG
						std::cerr<<getpid()<<"Block count error: header="<<BlockCount<<" actual:"<<Blocks<<std::endl;
#endif
						delete[] HashArray;
						return std::make_unique<Job>(sockfd,BadRequest(106, "BlockCount error"),"");
					}
					else
					{
						Hashes=base64_encode(HashArray,ImitoLength*BlockCount);
#ifdef __DEBUG
						std::cerr<<getpid()<<"\tHashes array: ";
						for (int i=0;i<ImitoLength*BlockCount;i++)
							fprintf(stderr,"%02hhx:", HashArray[i]);
						std::cerr<<"\n\tBase64 encoded array: "<<Hashes<<std::endl;
#endif
						delete[] HashArray;
						return std::make_unique<Job>(sockfd,"HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n","{\r\n\t\"signatures\": \""+Hashes+"\"\r\n}\r\n");
					}
				}
        		break;
        	case 3:         //Check codes
        		break;
        	default:        //Error
        		return std::make_unique<Job>(sockfd,Err404);
        	}
            return std::make_unique<Job>(sockfd,"","");
        }
};

/* Copy a buffer to stream */
void sendToClient(int sockfd, const char* buffer, std::size_t size)
{
    std::size_t writen = 0;
    int out=0;
    while(writen < size)
    {
        out = ::write(sockfd, buffer + writen, (size - writen>65536)?65536:size - writen);
        if (out == -1 && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
		{
			continue;
		}
		if (out == -1)
		{
			throw std::runtime_error("Failed to write to socket");
		}
        writen += out;
#ifdef __DEBUG
        std::cerr<<"Writing "<<out<<" bytes. "<<writen<<" bytes writen "<<size<<" bytes total).\n";
#endif
    }
}

/* Read the request from the socket */
void ReadBytes(int connection, char *BodyBuf, int Size)
{
	int readed=0;
	while(true)
		{
#ifdef __DEBUG
			std::cerr<<"Reading....  ";
#endif
			std::size_t actual = ::read(connection, BodyBuf + readed, Size - readed );
#ifdef __DEBUG
			std::cerr<<"Readed chunk: "<<actual<<" bytes, "<<readed+actual<<" bytes total \n";
			std::cerr<<"Last 50 bytes: "<<&BodyBuf[actual+readed-50]<<std::endl;
#endif
			if (actual == 0)
			{
				break;
			}
			if ((int)actual == -1 && (errno == EAGAIN || errno == EINTR))
			{
				continue;
			}
			if ((int)actual == -1)
			{
				throw std::runtime_error("Read Error");
			}
			readed += actual;
			if (readed == Size)
			{
				break;
			}
		}
#ifdef __DEBUG
	std::cerr<<"Readed: "<<readed<<" bytes \n";
	std::cerr<<"Last 50 bytes: "<<&BodyBuf[readed-50]<<std::endl;
#endif
}
Header ParceRequest(int connection)
{

    char buffer[4097];
    memset (buffer,0,4097);
    Header HDR;
    std::size_t readed;
    int StartPos,HdrEnd;
    readed = ::read(connection, buffer , 4096 );
#ifdef __DEBUG
    	std::cerr<<"Header: "<<readed<<" bytes \n";
#endif
    std::string Hdr=std::string (buffer,buffer+readed);
    std::for_each(Hdr.begin(), Hdr.end(), [](char & c){c = ::toupper(c);});
#ifdef __DEBUG
    std::cerr<<"Got request\n-----------------------------------\n"<<buffer<<"\n-----------------------------------\n";
#endif
    StartPos=Hdr.find("POST");
    if ((StartPos<0)||(StartPos>5)) return Header (404,"Wrong metod. The POST is expected at the very beginning of the header.");
    char* DataStart  = buffer+StartPos+5;
    StartPos=Hdr.find(" ",StartPos+6);
    char* DataEnd = buffer+StartPos;
    HDR.Path=std::string(DataStart, DataEnd);
    StartPos=Hdr.find("CONTENT-LENGTH");
    HdrEnd=Hdr.find("\r\n\r\n",StartPos)+4;
    if (StartPos>0)
    {
    	DataStart  = buffer+StartPos+15;
    	StartPos=Hdr.find("\n",StartPos+15);
    	DataEnd=buffer+StartPos;
    	HDR.BodySize=std::stoi(std::string(DataStart, DataEnd));
    	HDR.HasBody=true;
    }
    StartPos=Hdr.find("100-CONTINUE");
    if (StartPos==-1)
    {
    	if (HDR.BodySize!=0)
    	{
    		HDR.HasBody=true;
    		HDR.Body=std::string(buffer+HdrEnd,buffer+Hdr.length());
    		if (HDR.BodySize>(size_t)4096-HdrEnd)
    		{
    			char *BodyBuf=new char[HDR.BodySize-4095+HdrEnd];
    			BodyBuf[HDR.BodySize-4096+HdrEnd]=0;
    			ReadBytes(connection, BodyBuf, HDR.BodySize-4096+HdrEnd);
    			HDR.Body.append(BodyBuf, &BodyBuf[HDR.BodySize-4095+HdrEnd]);
#ifdef __DEBUG
    			std::cerr<<"Got body without HTTP 100\n";
#endif
    			delete[] BodyBuf;
    		}
    	}
    }
    else
    {
    	if (HDR.BodySize==0) return Header (404,"Body size = 0. Expected Body size when HTTP 100-continue set.");
    	HDR.ExpectContinue=true;
    	char *BodyBuf=new char[HDR.BodySize+1];
    	BodyBuf[HDR.BodySize]=0;
    	sendToClient(connection, "HTTP/1.1 100 Continue\r\n\r\n", 26);
#ifdef __DEBUG
    	std::cerr<<"HTTP/1.1 100 Continue sent\n";
#endif
    	ReadBytes(connection, BodyBuf, HDR.BodySize);
    	if (BodyBuf[readed-1]=='"')
		{
    		std::cerr<<"Added '}' at: "<<readed<<std::endl;
			BodyBuf[readed++]='}';
		}
    	HDR.Body.append(BodyBuf);
    	HDR.HasBody=true;
    	delete[] BodyBuf;
    }
    if (HDR.HasBody)
    {
    	if (HDR.Body.find("}",HDR.Body.length()-10)<0) HDR.Body+="}";
    }
    return HDR;
}

void handleJob(std::unique_ptr<Job> job) {
    if (job->sockfd)
    {

    	job->Header+="Server: HSM module KG\r\n";
    	if (job->Body.length())
    	{
    		job->Header+="Content-Length: "+std::to_string(job->Body.length())+"\r\nConnection: Closed\r\n\r\n";
    		job->Body=job->Header+job->Body;
    		sendToClient(job->sockfd, job->Body.data(), job->Body.length());
    		//job->Header+=job->Body;
    	}
    	else
    	{
    		job->Header+="\r\n\r\n";
    		sendToClient(job->sockfd, job->Header.data(), job->Header.length());
    	}

#ifdef __DEBUG
    	std::cerr<<"Got responce\n-----------------------------------\n"<<job->Header<<"\n-----------------------------------\n"<<job->Body<<"\n-----------------------------------\n";
#endif
    }
}

int main()
	{
	URIs["/keys"]=1;
	URIs["/sign/symmetric"]=2;
	URIs["/check/codes"]=3;
    std::vector<std::future<void>> pending_futures;
    SimpleSocket    socket(8085);

    int connection;
    while ((connection = socket.waitForConnection())!=0)
    {
        Header H = ParceRequest(connection);
#ifdef __DEBUG
        std::cerr<<H<<std::endl;
#endif
        pending_futures.push_back(std::async(std::launch::async, handleJob, Respomces::getJob(connection,std::move(H))));
    }

}
