# ImageRetrieval
Image Retrieval using C++

# Installation
## Requirement
- OpenCV 2.4.9 or higher
- Boost C++ 1.54 or higher
- FLANN 1.7 or higher
- HDF5 library
- PostgreSQL client
- LibPQ, LibPQXX

## Setup
- Create a local_configurations.h corresponding to local_configurations_example.h

# How to use the service
- Send a POST request with the image file to the server

```
E.g.:
$ curl -X POST -F "content=@bana.jpg" http://112.78.11.178/request

{"id":1,"content":"/media/images/2015/08/16/bana.jpg","request_at":"2015-08-16T11:30:10.465797Z","response":"Pending"}
```

Use send a GET request to the url corresponding to the response id to get the ranked list
```
E.g.: 
curl -X GET http://112.78.11.178/request/1/
```
