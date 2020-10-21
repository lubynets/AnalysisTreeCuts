
find_package(ROOT REQUIRED)


set(AnalysisTreeCuts_LIBRARY_PATH
        ${AnalysisTreeCuts_SOURCE_DIR}/CutsLibrary CACHE STRING "Default path for the cuts library")
set(AnalysisTreeCuts_ENVNAME
        CUTS_LIBRARY_PATH CACHE STRING "Environment variable to set different lookup path")
message("Cuts default Library Path: ${AnalysisTreeCuts_LIBRARY_PATH}")
configure_file(AnalysisTreeCutsGen.hpp.in AnalysisTreeCutsGen.hpp)



include_directories(${CMAKE_CURRENT_SOURCE_DIR})
ROOT_GENERATE_DICTIONARY(G__AnalysisTreeCutsRegistry
        CutsRegistry.hpp
        LINKDEF AnalysisTreeCutsRegistryLinkDef.hpp
        OPTIONS
        -interpreteronly
        -I${CMAKE_BINARY_DIR}/include
        )
add_library(AnalysisTreeCutsRegistry SHARED
        CutsRegistry.cpp
        CutsRegistry.hpp
        AnalysisTreeCutsRegistryLinkDef.hpp
        G__AnalysisTreeCutsRegistry.cxx
        )
target_include_directories(AnalysisTreeCutsRegistry
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(AnalysisTreeCutsRegistry PUBLIC AnalysisTreeInfra ROOT::Core)