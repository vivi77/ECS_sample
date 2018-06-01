set(NAME CLISystemEvent)

file(GLOB SRCS *.cpp *.hh *.hpp)

add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME}
  PUBLIC
  )
target_link_libraries(${NAME}
  PUBLIC
  ecs_core
  )
