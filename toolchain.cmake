# fordítók
if(NOT WIN32)
	set(CMAKE_C_COMPILER clang CACHE STRING "" FORCE)
	set(CMAKE_CXX_COMPILER clang++ CACHE STRING "" FORCE)
endif()


# globális figyelmeztetések
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wdeprecated -pedantic")

# build típus specifikus
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# kimeneti mappák
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)