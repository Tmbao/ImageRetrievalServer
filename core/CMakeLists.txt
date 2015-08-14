cmake_minimum_required(VERSION 3.2)
project(ImageRetrievalCpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++0x")
set(Boost_USE_MULTITHREADE OFF)

find_package(OpenCV REQUIRED)
find_package(Armadillo REQUIRED)
find_package(HDF5 REQUIRED)
find_package(Boost COMPONENTS filesystem system REQUIRED)
find_package(PQ REQUIRED)
find_package(PQXX REQUIRED)

set(SOURCE_FILES
    app/appdata.h
    query/query.h
    utils/invertedindex.h
    extract/extract.h
    quantize/quantize.h
    utils/utils.h
    utils/score.h
    configurations.h
    initialize.h
    runserver.h
    main.cpp
    README.md)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Armadillo_INCLUDE_DIRS})
include_directories(${HDF5_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PostgreSQL_INCLUDE_DIRS})
include_directories(${PQ_INCLUDE_DIRECTORIES})
include_directories(${PQXX_INCLUDE_DIRECTORIES})

add_executable(ImageRetrievalCpp ${SOURCE_FILES})
target_link_libraries(ImageRetrievalCpp 
    ${OpenCV_LIBRARIES} 
    ${Armadillo_LIBRARIES}
    ${HDF5_LIBRARIES} 
    ${Boost_LIBRARIES} 
    ${PQXX_LIBRARIES}
    ${PQ_LIBRARIES})
