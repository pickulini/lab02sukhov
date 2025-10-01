cmake_minimum_required(VERSION 3.10)
project(16g)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Основная библиотека
add_library(${CMAKE_PROJECT_NAME}_lib 
    src/16g.cpp
)

# Основная программа
add_executable(${CMAKE_PROJECT_NAME} 
    src/main.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)

# Включаем директории
target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

# Тесты
add_executable(tests 
    test/tests.cpp
)
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_test(NAME AllTests COMMAND tests)
