//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP server, asynchronous
//
//------------------------------------------------------------------------------
//#define DEBUG
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include "json/single_include/nlohmann/json.hpp"
#include "Crypt.hpp"
#include "Base64.h"
#ifdef DEBUG
	#include <bits/stdc++.h>
#endif

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>

std::map <std::string, int> URIs;
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
//namespace pt = boost::property_tree;
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using json = nlohmann::json;

// Return a reasonable mime type based on the extension of a file.
beast::string_view
mime_type(beast::string_view path)
{
    using beast::iequals;
    auto const ext = [&path]
    {
        auto const pos = path.rfind(".");
        if(pos == beast::string_view::npos)
            return beast::string_view{};
        return path.substr(pos);
    }();
    if(iequals(ext, ".htm"))  return "text/html";
    if(iequals(ext, ".html")) return "text/html";
    if(iequals(ext, ".php"))  return "text/html";
    if(iequals(ext, ".css"))  return "text/css";
    if(iequals(ext, ".txt"))  return "text/plain";
    if(iequals(ext, ".js"))   return "application/javascript";
    if(iequals(ext, ".json")) return "application/json";
    if(iequals(ext, ".xml"))  return "application/xml";
    if(iequals(ext, ".swf"))  return "application/x-shockwave-flash";
    if(iequals(ext, ".flv"))  return "video/x-flv";
    if(iequals(ext, ".png"))  return "image/png";
    if(iequals(ext, ".jpe"))  return "image/jpeg";
    if(iequals(ext, ".jpeg")) return "image/jpeg";
    if(iequals(ext, ".jpg"))  return "image/jpeg";
    if(iequals(ext, ".gif"))  return "image/gif";
    if(iequals(ext, ".bmp"))  return "image/bmp";
    if(iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
    if(iequals(ext, ".tiff")) return "image/tiff";
    if(iequals(ext, ".tif"))  return "image/tiff";
    if(iequals(ext, ".svg"))  return "image/svg+xml";
    if(iequals(ext, ".svgz")) return "image/svg+xml";
    return "application/text";
}

template<
    class Body, class Allocator,
    class Send>
void
handle_request(
    beast::string_view doc_root,
    http::request<Body, http::basic_fields<Allocator>>&& req,
    Send&& send)
{
    // Returns a bad request response
    auto const bad_request =
    [&req](beast::string_view why)
    {
        http::response<http::string_body> res{http::status::bad_request, req.version()};
        res.set(http::field::server, "HSM module KG");
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = std::string(why);
        res.prepare_payload();
        return res;
    };

    // Returns a not found response
    auto const not_found =
    [&req](beast::string_view target)
    {
        http::response<http::string_body> res{http::status::not_found, req.version()};
        res.set(http::field::server, "HSM module KG");
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "The resource '" + std::string(target) + "' was not found.";
        res.prepare_payload();
        return res;
    };

    // Returns a server error response
    auto const server_error =
    [&req](beast::string_view what)
    {
        http::response<http::string_body> res{http::status::internal_server_error, req.version()};
        res.set(http::field::server, "HSM module KG");
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "An error occurred: '" + std::string(what) + "'";
        res.prepare_payload();
        return res;
    };

    // Make sure we can handle the method
    if( req.method() != http::verb::post &&
        req.method() != http::verb::head)
        return send(bad_request("Wrong HTTP-method"));
#ifdef DEBUG
    	std::cerr<<"from:"<<req.target().data()<<" Requested "<<req.body()<<std::endl;
#endif
    json Params=json::parse(req.body());
    switch (URIs[req.target().data()])
    {
    case 1: // Keys
    	if (Params["type"]==1)
			{//Symmetric
    			return send(bad_request("Not implemented yet"));
#ifdef DEBUG
    	std::cerr<<"Requested asymmetric keys"<<std::endl;
#endif
			}
    	else
    	{
#ifdef DEBUG
    	std::cerr<<"Requested symmetric keys"<<std::endl;
#endif
    		//int KeyType=pt.get_child("type").get_value<int>();
			http::response<http::string_body> res{http::status::ok, req.version()};
			res.set(http::field::server, "HSM module KG");
			res.set(http::field::content_type, "application/json");
			res.keep_alive(req.keep_alive());
			res.body()=std::string("{\"keys\": [\"0000\"] }");
			res.keep_alive(req.keep_alive());
			res.prepare_payload();
			return send(std::move(res));
    	}
		break;
    case 2: // /sign/symmetric
#ifdef DEBUG
    	std::cerr<<"Requested symmetric sign"<<std::endl;
#endif
    	if (Params["key"]=="0000")
    	{
    		int BlockCount=Params["blockCount"];
    		int BlockLength=Params["blockLength"];
    		int ImitoLength=Params["imitoLength"];
    		std::string Codes=base64_decode(Params["codes"]);
#ifdef DEBUG
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
#ifdef DEBUG
    			std::cerr<<"Hashing: "<<Codes.substr(i, BlockLength)<< "\tGot hash: ";
#endif
    			Hash=hash(Codes.substr(i, BlockLength).data());
    			memcpy (
    					HashArray+Blocks*ImitoLength,
						Hash.data(),
						ImitoLength);
    		}
    		if (Blocks!=BlockCount)
    		{
#ifdef DEBUG
    			std::cerr<<getpid()<<"Block count error: header="<<BlockCount<<" actual:"<<Blocks<<std::endl;
#endif
    			delete[] HashArray;
    			return send(bad_request("Wrong key!"));
    		}
    		else
    		{
    			Hashes=base64_encode(HashArray,ImitoLength*BlockCount);
#ifdef DEBUG
    			std::cerr<<getpid()<<"\tHashes array: ";
    			for (int i=0;i<ImitoLength*BlockCount;i++)
    			   	fprintf(stderr,"%02hhx:", HashArray[i]);
    			std::cerr<<"\n\tBase64 encoded array: "<<Hashes<<std::endl;
#endif
			http::response<http::string_body> res{http::status::ok, req.version()};
			res.set(http::field::server, "HSM module KG");
			res.set(http::field::content_type, "application/json");
			res.keep_alive(req.keep_alive());
			res.body()=std::string("{\n  \"signatures\": \""+Hashes+"\"\n}\n");
			res.keep_alive(req.keep_alive());
			res.prepare_payload();
			delete[] HashArray;
			return send(std::move(res));
    		}
    	}
    	else
		{
    		return send(bad_request("Wrong key!"));
		}
    	break;
    default:
    	std::cerr<<"Header error?\n"<<req.base()<<std::endl<<req.body()<<std::endl;
    	return send(bad_request(req.target().data()+std::string("\nIllegal request-target\n")));
    }
    return send(bad_request(req.target().data()+std::string("\nIllegal request-target\n")));
    // Build the path to the requested file
    //std::string path = path_cat(doc_root, req.target());
    //if(req.target().back() == '/')
    //    path.append("index.html");

    // Attempt to open the file
    //beast::error_code ec;
    //http::file_body::value_type body;
    //body.open(path.c_str(), beast::file_mode::scan, ec);

    // Handle the case where the file doesn't exist
    //if(ec == beast::errc::no_such_file_or_directory)
    //    return send(not_found(req.target()));

    // Handle an unknown error
    //if(ec)
    //    return send(server_error(ec.message()));

    // Cache the size since we need it after the move
    //auto const size = body.size();

    // Respond to HEAD request
    //if(req.method() == http::verb::head)
    //{
    //    http::response<http::empty_body> res{http::status::ok, req.version()};
    //    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    //    res.set(http::field::content_type, mime_type(path));
    //    res.content_length(size);
    //    res.keep_alive(req.keep_alive());
    //    return send(std::move(res));
    //}

    // Respond to GET request
    //http::response<http::file_body> res{
    //    std::piecewise_construct,
    //    std::make_tuple(std::move(body)),
    //    std::make_tuple(http::status::ok, req.version())};
    //res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    //res.set(http::field::content_type, mime_type(path));
    //res.content_length(size);
    //res.keep_alive(req.keep_alive());
    //return send(std::move(res));
}

//------------------------------------------------------------------------------

// Report a failure
void
fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Handles an HTTP server connection
class session : public std::enable_shared_from_this<session>
{
    // This is the C++11 equivalent of a generic lambda.
    // The function object is used to send an HTTP message.
    struct send_lambda
    {
        session& self_;

        explicit
        send_lambda(session& self)
            : self_(self)
        {
        }

        template<bool isRequest, class Body, class Fields>
        void
        operator()(http::message<isRequest, Body, Fields>&& msg) const
        {
            // The lifetime of the message has to extend
            // for the duration of the async operation so
            // we use a shared_ptr to manage it.
            auto sp = std::make_shared<
                http::message<isRequest, Body, Fields>>(std::move(msg));

            // Store a type-erased version of the shared
            // pointer in the class to keep it alive.
            self_.res_ = sp;

            // Write the response
            http::async_write(
                self_.stream_,
                *sp,
                beast::bind_front_handler(
                    &session::on_write,
                    self_.shared_from_this(),
                    sp->need_eof()));
        }
    };

    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    std::shared_ptr<std::string const> doc_root_;
    http::request<http::string_body> req_;
    std::shared_ptr<void> res_;
    send_lambda lambda_;

public:
    // Take ownership of the stream
    session(
        tcp::socket&& socket,
        std::shared_ptr<std::string const> const& doc_root)
        : stream_(std::move(socket))
        , doc_root_(doc_root)
        , lambda_(*this)
    {
    }

    // Start the asynchronous operation
    void
    run()
    {
        // We need to be executing within a strand to perform async operations
        // on the I/O objects in this session. Although not strictly necessary
        // for single-threaded contexts, this example code is written to be
        // thread-safe by default.
        net::dispatch(stream_.get_executor(),
                      beast::bind_front_handler(
                          &session::do_read,
                          shared_from_this()));
    }

    void
    do_read()
    {
        // Make the request empty before reading,
        // otherwise the operation behavior is undefined.
        req_ = {};

        // Set the timeout.
        stream_.expires_after(std::chrono::seconds(30));

        // Read a request
        http::async_read(stream_, buffer_, req_,
            beast::bind_front_handler(
                &session::on_read,
                shared_from_this()));
    }

    void
    on_read(
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        // This means they closed the connection
        if(ec == http::error::end_of_stream)
            return do_close();

        if(ec)
            return fail(ec, "read");

        // Send the response
        handle_request(*doc_root_, std::move(req_), lambda_);
    }

    void
    on_write(
        bool close,
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "write");

        if(close)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            return do_close();
        }

        // We're done with the response so delete it
        res_ = nullptr;

        // Read another request
        do_read();
    }

    void
    do_close()
    {
        // Send a TCP shutdown
        beast::error_code ec;
        stream_.socket().shutdown(tcp::socket::shutdown_send, ec);

        // At this point the connection is closed gracefully
    }
};

//------------------------------------------------------------------------------

// Accepts incoming connections and launches the sessions
class listener : public std::enable_shared_from_this<listener>
{
    net::io_context& ioc_;
    tcp::acceptor acceptor_;
    std::shared_ptr<std::string const> doc_root_;

public:
    listener(
        net::io_context& ioc,
        tcp::endpoint endpoint,
        std::shared_ptr<std::string const> const& doc_root)
        : ioc_(ioc)
        , acceptor_(net::make_strand(ioc))
        , doc_root_(doc_root)
    {
        beast::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if(ec)
        {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if(ec)
        {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if(ec)
        {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(
            net::socket_base::max_listen_connections, ec);
        if(ec)
        {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void
    run()
    {
        do_accept();
    }

private:
    void
    do_accept()
    {
        // The new connection gets its own strand
        acceptor_.async_accept(
            net::make_strand(ioc_),
            beast::bind_front_handler(
                &listener::on_accept,
                shared_from_this()));
    }

    void
    on_accept(beast::error_code ec, tcp::socket socket)
    {
        if(ec)
        {
            fail(ec, "accept");
        }
        else
        {
            // Create the session and run it
            std::make_shared<session>(
                std::move(socket),
                doc_root_)->run();
        }

        // Accept another connection
        do_accept();
    }
};

//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	 URIs["/keys"]=1;
	 URIs["/sign/symmetric"]=2;
	 URIs["/check/codes"]=3;
    // Check command line arguments.
    if (argc != 4)
    {
        std::cerr <<
            "Usage: HSM_KG <address> <port>  <threads>\n" <<
            "Example:\n" <<
            "    http-server-async 0.0.0.0 8080 1\n";
        return EXIT_FAILURE;
    }
    auto const address = net::ip::make_address(argv[1]);
    auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
    auto const doc_root = std::make_shared<std::string>(".");
    auto const threads = std::max<int>(1, std::atoi(argv[3]));

    // The io_context is required for all I/O
    net::io_context ioc{threads};

    // Create and launch a listening port
    std::make_shared<listener>(
        ioc,
        tcp::endpoint{address, port},
        doc_root)->run();

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for(auto i = threads - 1; i > 0; --i)
        v.emplace_back(
        [&ioc]
        {
            ioc.run();
        });
    ioc.run();

    return EXIT_SUCCESS;
}
