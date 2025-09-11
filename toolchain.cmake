# ford�t�k
if(NOT WIN32)
	set(CMAKE_C_COMPILER clang CACHE STRING "" FORCE)
	set(CMAKE_CXX_COMPILER clang++ CACHE STRING "" FORCE)
endif()


# glob�lis figyelmeztet�sek
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wdeprecated -pedantic")

# build t�pus specifikus
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# kimeneti mapp�k
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)