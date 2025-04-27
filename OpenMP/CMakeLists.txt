cmake_minimum_required(VERSION 3.10)
project(ImageBlurOMP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем поддержку OpenMP
find_package(OpenMP REQUIRED)

add_executable(ImageBlurOMP
    main.cpp
    blur.cpp
)

# Подключаем OpenMP
target_link_libraries(ImageBlurOMP PRIVATE OpenMP::OpenMP_CXX)

# Для Windows
if(MSVC)
    target_compile_options(ImageBlurOMP PRIVATE /W4 /WX)
else()
    target_compile_options(ImageBlurOMP PRIVATE -Wall -Wextra -Werror)
endif()