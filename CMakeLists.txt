cmake_minimum_required(VERSION 2.6)
project(OCLINT)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_definitions(
  -D_DEBUG
  -D_GNU_SOURCE
  -D__STDC_LIMIT_MACROS
  -D__STDC_CONSTANT_MACROS
  -g
  -fno-common
  -Woverloaded-virtual
  -Wcast-qual
  -fno-rtti
  -fPIC
  )

include_directories(${OCLINT_SOURCE_DIR}/src/headers)
include_directories(${LLVM_SRC_DIR}/include)
include_directories(${LLVM_SRC_DIR}/tools/clang/include)
include_directories(${LLVM_BINARY_DIR}/include)
include_directories(${LLVM_BINARY_DIR}/tools/clang/include)

link_directories(${LLVM_BINARY_DIR}/lib)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -pedantic -Wno-long-long -Wall -W -Wno-unused-parameter -Wwrite-strings")
endif()

SET(OCLINT_COMMON_LINK_LIB
  libclang
  pthread
  )

if(IS_CI_BUILD)
add_definitions(
  -fprofile-arcs 
  -ftest-coverage
  )
endif()

add_subdirectory(src)

if(IS_CI_BUILD)
add_subdirectory(test)
endif()
