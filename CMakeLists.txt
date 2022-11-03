cmake_minimum_required(VERSION 3.16)
project (RegNumGen
         LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "\n-------------------------------------------")
message(STATUS "\n-- CMake: Configuring and building RegularNumGen.\n--")
message(STATUS "----------------------------------------")

if (BUILD_SHARED_LIBS)
  set (CMAKE_SKIP_BUILD_RPATH FALSE)
  set (CMAKE_SKIP_INSTALL_RPATH FALSE)
  set (CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
  set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE) 
  set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  set (CMAKE_INSTALL_NAME_DIR "${CMAKE_INSTALL_RPATH}")
else ()
  SET (CMAKE_SKIP_INSTALL_RPATH ON CACHE BOOL "Turn off for static install." FORCE)
  SET (CMAKE_SKIP_RPATH ON CACHE BOOL "Turn off for static install." FORCE)
endif ()

add_library (libRegNumGen regular_numbers.cc)
add_executable (RegNumGen driver.cc)
target_link_libraries (RegNumGen LINK_PUBLIC libRegNumGen)

install(TARGETS libRegNumGen RegNumGen)
