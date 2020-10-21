project(Cuts CXX)
cmake_minimum_required(VERSION 3.11)


set(AnalysisTreeCuts_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

include(AnalysisTree)

add_subdirectory(AnalysisTreeCutsRegistry)

set(HEADERS
    CbmCuts.h
    ShineCuts.h
    HadesCuts.h
)


install(
        FILES
        ${HEADERS}
        DESTINATION
        include
        COMPONENT
        Devel
)
