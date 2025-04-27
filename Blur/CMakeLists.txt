cmake_minimum_required(VERSION 3.10)
project(ImageBlur)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(ImageBlur
    main.cpp
    blur.cpp
)

target_link_libraries(ImageBlur PRIVATE Threads::Threads)

if(MSVC)
    target_compile_options(ImageBlur PRIVATE /W4 /WX /wd4267)
else()
    target_compile_options(ImageBlur PRIVATE -Wall -Wextra -Werror)
endif()