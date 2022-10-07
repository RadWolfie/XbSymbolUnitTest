# CMakeList.txt : CMake project for XbSymbolUnitTest, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project(XbSymbolUnitTest)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

include_directories("${PROJECT_SOURCE_DIR}/import/xxHash")

set(XBSDB_BUILD_CLI ON)

add_subdirectory("${PROJECT_SOURCE_DIR}/import/XbSymbolDatabase")

# Add source to this project's executable.
file(GLOB_RECURSE HEADERS "src/*.hpp")

# Add source to this project's executable.
file(GLOB_RECURSE SOURCES "src/*.cpp")

set(SOURCES ${SOURCES}
  "import/xxHash/xxhash.c"
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} PREFIX "header" FILES ${HEADERS})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} PREFIX "source" FILES ${SOURCES})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
 # Configure startup project
 set_property(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

# GCC needs a lib for std::filesystem
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(STD_FILESYSTEM_LIBRARY -lstdc++fs)
else()
  set(STD_FILESYSTEM_LIBRARY)
endif()

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC libXbSymbolDatabase ${STD_FILESYSTEM_LIBRARY})


install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
)

# Collect all batch files from scripts folder.
file(GLOB BATCH_FILES
  "scripts/*.bat"
)
# Put all batch files into same folder where executable is in.
install(FILES ${BATCH_FILES}
  TYPE BIN
)
