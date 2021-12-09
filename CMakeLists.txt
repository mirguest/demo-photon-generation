cmake_minimum_required (VERSION 3.15)

# add this options before PROJECT keyword
# disable in source build
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Set the default CMAKE_BUILD_TYPE to Release (copied from ROOT)
if(NOT GENERATOR_IS_MULTI_CONFIG AND NOT CMAKE_BUILD_TYPE)
  if(NOT CMAKE_C_FLAGS AND NOT CMAKE_CXX_FLAGS AND NOT CMAKE_Fortran_FLAGS)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Specifies the build type on single-configuration generators" FORCE)
  endif()
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

##############################################################################
project (demo-photon-generation LANGUAGES CXX CUDA)
##############################################################################

# C++ Standard: 17
#   it could be overriden by -DCMAKE_CXX_STANDARD=17
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

# Use the GNU Install Directories
include(GNUInstallDirs)

##############################################################################
# BUILD libraries
##############################################################################

add_library(PhotonGeneration SHARED
  src/scintillation.cc
  src/cerenkov.cc
  src/OpEngine.cc
  src/GPUOpEngine.cu
)

target_include_directories(PhotonGeneration
  PUBLIC
    include
)

install(TARGETS PhotonGeneration)

##############################################################################
# BUILD demos/tests
##############################################################################

add_executable(demo-photon-generation
  tests/demo-photon-generation.cc
)

target_link_libraries(demo-photon-generation
  PhotonGeneration
)

install(TARGETS demo-photon-generation)


add_executable(demo-photon-generation-gpu
  tests/demo-photon-generation-gpu.cu
)
target_link_libraries(demo-photon-generation-gpu
  PhotonGeneration
)

install(TARGETS demo-photon-generation-gpu)
