
find_package(ROOT REQUIRED)
find_package(Boost COMPONENTS filesystem)

configure_file(AnalysisTreeCutsGen.hpp.in AnalysisTreeCutsGen.hpp)

include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${AnalysisTree_BINARY_DIR}/include)
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
target_compile_definitions(AnalysisTreeCutsRegistry PRIVATE
        $<$<BOOL:${Boost_FOUND}>:BOOST_FOUND>
        $<$<BOOL:${Boost_FILESYSTEM_FOUND}>:BOOST_FILESYSTEM_FOUND>
        )
target_include_directories(AnalysisTreeCutsRegistry
        PUBLIC
        ${AnalysisTreeCuts_SOURCE_DIR}
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(AnalysisTreeCutsRegistry
        PUBLIC
        AnalysisTreeInfra
        $<TARGET_NAME_IF_EXISTS:AnalysisTreeInfraVersion1>
        ROOT::Core
        PRIVATE
        #see https://gitlab.kitware.com/cmake/cmake/-/issues/17834
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
        $<$<BOOL:${Boost_FILESYSTEM_FOUND}>:Boost::filesystem>
        )
install(TARGETS AnalysisTreeCutsRegistry EXPORT AnalysisTreeCutsRegistryTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
install(
        FILES
        CutsRegistry.hpp
        DESTINATION
        include/AnalysisTreeCutsRegistry
        COMPONENT
        Devel
)

set(PCM_FILE_NAME libAnalysisTreeCutsRegistry)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PCM_FILE_NAME}_rdict.pcm"
        DESTINATION
        lib
        OPTIONAL
)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PCM_FILE_NAME}.rootmap"
        DESTINATION
        lib
        OPTIONAL
)
