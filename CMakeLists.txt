cmake_minimum_required(VERSION 3.0.0)
project(VelogToGitBlog VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
 ${CMAKE_CURRENT_SOURCE_DIR}/Project1/*.cpp
)

add_executable(VelogToGitBlog Main.cpp ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# set(CMAKE_CXX_STANDARD 17)

target_compile_features(VelogToGitBlog PRIVATE cxx_std_17)

include(CPack)

target_include_directories(VelogToGitBlog PUBLIC ${CMAKE_SOURCE_DIR}/Project1)