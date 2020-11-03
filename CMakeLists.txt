project(AnalysisTreeCuts CXX)
cmake_minimum_required(VERSION 3.11)

list(APPEND CMAKE_PREFIX_PATH ${ROOTSYS})
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
include(AnalysisTree)
include(CMakeDependentOption)

set(AnalysisTreeCuts_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(AnalysisTreeCuts_LIBRARY_PATH
        ${AnalysisTreeCuts_SOURCE_DIR}/CutsLibrary CACHE STRING "Default path for the cuts library")
set(AnalysisTreeCuts_ENVNAME
        CUTS_LIBRARY_PATH CACHE STRING "Environment variable to set different lookup path")
message("Cuts default Library Path: ${AnalysisTreeCuts_LIBRARY_PATH}")

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
