cmake_minimum_required(VERSION 3.15)
project(tinyvec LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
set(FLAGS /WX /W4)
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
set(FLAGS -Wall -Wextra -Wpedantic -Werror)
else()
set(FLAGS) # Nothing
endif()

set(LIB_SRC src/tinyvec.c)
set(EXAMPLES_SRC examples/example.c)
set(COMPILE_DEFS _CRT_SECURE_NO_WARNINGS TINYVEC_CONFIG_BUILDING)

add_library(tinyvec_stat STATIC ${LIB_SRC})
add_library(tinyvec_dyn SHARED ${LIB_SRC})
add_library(tinyvec ALIAS tinyvec_dyn)

target_compile_definitions(tinyvec_stat PRIVATE ${COMPILE_DEFS})
target_compile_definitions(tinyvec_dyn PRIVATE ${COMPILE_DEFS})

target_include_directories(tinyvec_stat PRIVATE include)
target_include_directories(tinyvec_dyn PRIVATE include)

target_compile_options(tinyvec_stat PRIVATE ${FLAGS})
target_compile_options(tinyvec_dyn PRIVATE ${FLAGS})

add_executable(example ${EXAMPLES_SRC})
target_compile_definitions(example PRIVATE ${COMPILE_DEFS})
target_compile_options(example PRIVATE ${FLAGS})
target_link_libraries(example PRIVATE tinyvec)
target_include_directories(example PRIVATE include)