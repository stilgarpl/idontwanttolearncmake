cmake_minimum_required(VERSION 3.16)
include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.254.tar.gz"
        SHA1 "017e688b9848c1f695303e8cfe9f35d40e154112"
)
get_filename_component(IDWTLC_PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${IDWTLC_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

#enable testing
enable_testing()


#speed up compilation
option(CMAKE_UNITY_BUILD "Enable unity builds" ON)
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CUDA_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif ()


#set destinations for install targets
include(GNUInstallDirs)
set(IDWTLC_DESTINATION_LIB "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}")
set(IDWTLC_DESTINATION_INCLUDE "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")
set(IDWTLC_CMAKE_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(IDWTLC_LIBRARIES )
add_subdirectory(libraries)
add_subdirectory(executables)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${IDWTLC_CMAKE_DIR}
        )

include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR TGZ;)
include(CPack)