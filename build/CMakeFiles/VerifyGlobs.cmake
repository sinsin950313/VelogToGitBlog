# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.27
cmake_policy(SET CMP0009 NEW)

# SRC_FILES at CMakeLists.txt:7 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "C:/Users/sinsi/Desktop/VelogToGitBlog/Project1/*.cpp")
set(OLD_GLOB
  "C:/Users/sinsi/Desktop/VelogToGitBlog/Project1/DirectoryParser.cpp"
  "C:/Users/sinsi/Desktop/VelogToGitBlog/Project1/FileModifier.cpp"
  "C:/Users/sinsi/Desktop/VelogToGitBlog/Project1/FileParser.cpp"
  "C:/Users/sinsi/Desktop/VelogToGitBlog/Project1/OptionAction.cpp"
  "C:/Users/sinsi/Desktop/VelogToGitBlog/Project1/OptionManager.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/sinsi/Desktop/VelogToGitBlog/build/CMakeFiles/cmake.verify_globs")
endif()