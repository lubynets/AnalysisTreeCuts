project(Cuts CXX)
cmake_minimum_required(VERSION 3.15)

set(HEADERS
    CbmCuts.h
    ShineCuts.h)


install(
        FILES
        ${HEADERS}
        DESTINATION
        include
        COMPONENT
        Devel
)