
find_package(ROOT REQUIRED)


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
target_link_libraries(AnalysisTreeCutsRegistry
        PUBLIC
        AnalysisTreeInfra
        ROOT::Core
        PRIVATE
        #see https://gitlab.kitware.com/cmake/cmake/-/issues/17834
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
        )