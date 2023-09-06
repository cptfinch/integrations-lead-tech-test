cmake_minimum_required(VERSION 3.10)
project(WindowsAPIProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the spdlog package (if you are using it)
find_package(spdlog CONFIG REQUIRED)

# Add your source files here
add_executable(WindowsAPIProject WindowsAPIProject.cpp )

# Add this line to specify that the application is a Windows GUI application
set_target_properties(WindowsAPIProject PROPERTIES WIN32_EXECUTABLE TRUE)

# Link libraries
target_link_libraries(WindowsAPIProject PRIVATE spdlog::spdlog Shell32.lib)

# Include directories
# target_include_directories(WindowsAPIProject PRIVATE ${CMAKE_SOURCE_DIR}/path/to/include)

# Compile definitions (macros)
# target_compile_definitions(WindowsAPIProject PRIVATE YOUR_MACRO=VALUE)

# Compiler flags
# if (MSVC)
#     target_compile_options(WindowsAPIProject PRIVATE /W4 /WX)
# else()
#     target_compile_options(WindowsAPIProject PRIVATE -Wall -Wextra -Werror)
# endif()
