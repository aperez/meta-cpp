cmake_minimum_required (VERSION 3.5)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Werror")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

include_directories(${CMAKE_SOURCE_DIR})

function(add_meta_project arg)
  file(GLOB_RECURSE module_source "${arg}/*.cpp" "${arg}/*/*.cpp")
  add_executable(${arg} ${module_source})
endfunction(add_meta_project)

add_meta_project(turing-machine)
add_meta_project(brainfuck)
