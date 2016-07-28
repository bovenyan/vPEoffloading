cmake_minimum_required(VERSION 2.8) 
project(cntl)
set(CMAKE_C_FLAGS "-std=gnu99")

set(vPEoffsrc flow_entry.c of_msg.c rest.c whitebox.c util.c)
add_library(libvPEoff ${vPEoffsrc})
add_executable(offload offloader.c)

if(UNIX)
    target_link_libraries(
        offload
        libvPEoff
        curl
    )
elseif(WIN32)
elseif(APPLE)
endif(UNIX)
