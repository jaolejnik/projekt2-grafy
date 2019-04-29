cmake_minimum_required(VERSION 3.13)
project(Projekt2_Grafy)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projekt2_Grafy
        inc/GraphArray.hh
        inc/GraphList.hh
        inc/HelperFunc.hh
        inc/noe.hh
        src/main.cpp
        src/HelperFunc.cpp
        src/GraphArray.cpp
        src/GraphList.cpp src/BellmanFord.cpp inc/BellmanFord.hh src/MyList.cpp inc/MyList.hh)