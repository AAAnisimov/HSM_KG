# Preface
The main idea was to compare the speed of Java and C++ encryption algorithms. Moreover, this code uses only the standard Linux libraries to pass security checks.

This project was created using Eclipse CDT. However, you can also compile it via the command line:

g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Base64.d" -MT"src/Base64.o" -o "src/Base64.o" "../src/Base64.cpp"

g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Crypt.d" -MT"src/Crypt.o" -o "src/Crypt.o" "../src/Crypt.cpp"

g++ -std=c++17 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/HSM_KG.d" -MT"src/HSM_KG.o" -o "src/HSM_KG.o" "../src/HSM_KG.cpp"

g++ -L/usr/lib/x86_64-linux-gnu/ -o "HSM_KG"  ./src/Base64.o ./src/Crypt.o ./src/HSM_KG.o   -lgcrypt -lstdc++fs -lpthread

# 1. Method description
## Request a list of valid keys 

This method is used for requesting a list of active keys. 

### Request

**Table 1–Parameters**

|Parameter  |Description                                 |
|---------|-------------------------------------|
|URL                  |http://<**serve**r>:8085/keys      |
|Method  |POST                                           |


The HTTP request header parameters are shown in the table below (see Table 2). 
**Table 2 – HTTP header parameters **

|Parameter|Description|Type|Mandatory|
|---------------|--------------|----------------------|-
|Content-Type|Value: application/json; charset=utf-8|String|Yes|
|Content-Length|Message body length in bytes|Number (integer)|Yes|

The JSON format of the request body is described in the table below (Table 3). 
**Table 3 – Description of the request body's JSON format**

|Parameter|Description|Type|Mandatory|
|---------------|--------------|----------------------|-
|type|Key type Possible values: <ul><li> 1 – asymmetric key</li><li> 2 – symmetric key</li></ul>|Number (integer)|Yes|
#### Request example
**Table 4 - Request example**

|Request examle|
|---------------------|
|<ul>POST /keys HTTP/1.1<br> Content-Length 10<br> Accep: application/json<br> Content-Type: application/json;<br>charset=UTF-8<br> Host: localhost:8080<br><br> _{ "type": 1 }_</ul>|

### Responce
When the request is successful, the server returns the HTTP code 200 and an array of key IDs. The JSON format of the response body is described in the table below (Table 5). 
**Table 5 – JSON format of the response body**

|Field|Description|Type|Mandatory|
|---------------|--------------|----------------------|-
|keys|An array of identifiers of the keys in ASCII format. Each key ID (array element) is represented by a four-digit hexadecimal value|JSON array of string|Yes|

An example of the response to the request is shown in the table below (see table 6). 
**Table 6 – Response example**

|Response example|
|--|
|<ul>HTTP 1.1 200 OK <br>**Content-Type**: application/json;<br>**charset**=UTF-8<br>**Content-Length**: 33 <br><br>_{<br> "keys": \["0001","0002"\] <br>}_</ul>|

An example of an error response to a request is shown in the table below (see table 7).
**Table 7 - Example of an error response**

|Example of an error response|
|---|
|<ul>HTTP 1.1 400 Bad Reques<br>t Content-Type: application/json;<br>charset=UTF-8<br> Content-Length: 33<br><br>_{<br> "errorCode": 106,<br> "errorText":"Wrong JSON object format" <br>}_</ul>|

## Generate a symmetric verification code
 This method is intended for generating a symmetric verification code for an array of product identification codes. 
 
 ### Request
 
 **Table 8 - Parameters**

|Parameter|Description|
|--|--|
|URL|http:// < server >:8085/sign/symmetric|
|Method|POST|

The HTTP request header parameters are shown in the table below (see Table 9). 
**Table 9 – HTTP header parameters**

|Parameter|Description|Type|Mandatory|
|---------------|--------------|----------------------|-
|Content-Type|Value: application/json; charset=utf-8|String|Yes|
|Content-Length|Message body length in bytes|Number (integer)|Yes|

The JSON format of the request body is described in the table below (Table 10). 

**Table 10 – Description of the request body's JSON format**

|Parameter|Description|Type|Mandatory|
|---------------|--------------|----------------------|-
|key|ID of the key for a symmetric signature. the key type must be symmetric = 2. A string in ASCII format that was previously received when calling the "Request a list of valid keys" method. Valid value - «0000»|String|Yes|
|blockCount|The number of codes passed in the codes structure (a block is a signed or checked part of data related to a single marking code)|Number (integer)|Yes|
|blockLength|The size of a single block in bytes, and all identification codes must be the same size.|Nember (integer)|Yes|
|imitoLength|The size of the verification code in bytes in the range \[1...8\] bytes.|Number (integer)|Yes|
|codes|A byte array of blocks in base64 format. Generated lines of marking codes in the form of a byte array are converted to base64 encoding|String|Yes|

**Table 11 - Request example**

|Request example|
|--|
|<ul>**POST** / sign/symmetric HTTP/1.1<br>**Content-Length:** 10<br>**Accept**: application/json<br>**Content-Type**: application/json;<br>**charset**=UTF-8<br>**Host**: localhost:8080 <br><br>_{ <br>"keys": "0002", <br>"blockCount": 4, <br>"blockLength": 6, <br>"imitoLength": 3, <br>"codes": " base64(КМ1 + КМ2 … КМn)"<br> _}</ul>

 ### Responce
 
 **Table 12 – JSON format of the response body**

|Field|Description|Type|Mandatory|
|---------------|--------------|----------------------|-
|signatures|Byte array of verification codes in base64 format|String|Yes|

An example of the response to the request is shown in the table below (see table 13). 
**Table 13 - Response example**

|Response example|
|--|
|<ul>HTTP 1.1 200 OK <br>**Content-Type**: application/json;<br>**charset**=UTF-8<br>**Content-Length**: 540 <br><br>_{<br>"signatures": "QUJDREVGC...........==)" <br>}_</ul>|

# Format and error codes
## Error format
The JSON format of the response body with error information is described in the table below (see table 13). HTTP code 400.
**Table 13 - JSON format of the response with an error**

|Field|Description|Type|
|--|--|--|
|errorCode|Error code|Number (integer)|
|errorText|Error description|string|

## Error description 

The error codes in the request response are shown in the table below (table 14).

**Table 14 - Error codes**

|Error code|Error description|
|--|--|
|100|Wrong key identifier|
|101|Key not found|
|102|Invalid format of the public key certificate|
|103|Verification is not possible, the server is overloaded|
|104|Cryptographic error|
|105|The signature is incorrect|
|106|Wrong JSON object format|
|108|The connection to HSM is lost, please repeat the request later|
