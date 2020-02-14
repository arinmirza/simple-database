cmake_minimum_required(VERSION 3.4)
project(KeyValueStoreChallenge)

set(CMAKE_CXX_STANDARD 11)

add_executable(KeyValueStoreChallenge main.cpp key_value_store.cpp)

if(UNIX AND NOT APPLE)
    # Link against posix threading library.
    # http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html
    target_link_libraries(KeyValueStoreChallenge pthread)
elseif(WIN32)
    # psapi.dll is needed for threading API under windows.
    target_link_libraries(KeyValueStoreChallenge psapi.dll)
endif()