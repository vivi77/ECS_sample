set(NAME TextInputUpdater)

file(GLOB SRCS *.cpp *.hh *.hpp)

add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME} PUBLIC
  ${CMAKE_BINARY_DIR}
  ${PROJECT_SOURCE_DIR})
target_link_libraries(${NAME} PUBLIC
  ecs_core

  OSDLLoader

  TextInput

  CoreCommandsEvent
  )

generate_export_header(${NAME})
