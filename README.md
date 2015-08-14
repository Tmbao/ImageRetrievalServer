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
    curl -X POST -F "content=@all_souls_1_query.png" http://192.168.24.66:8080/request
```
