cmake_minimum_required(VERSION 3.0)

project(ecs_dev)

set(OUTPUT_LOCATION ${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_LOCATION})
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

set(EXEC_NAME ecs_dev)
set(CMAKE_CXX_STANDARD 17)

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wl,--no-undefined")
  set(CMAKE_CXX_FLAGS_DEBUG "-g3 -DDEBUG -fsanitize=address,undefined")
endif(UNIX)

add_subdirectory(./ecs)
add_subdirectory(./S)
add_subdirectory(./C)
add_subdirectory(./E)

file(GLOB SRCS *.cpp *.hh *.hpp)

add_executable(${EXEC_NAME} ${SRCS})
target_include_directories(${EXEC_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${EXEC_NAME} PUBLIC ecs_core)
