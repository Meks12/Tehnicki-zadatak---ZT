cmake_minimum_required(VERSION 3.10)

# Ime projekta
project(ZenitelZadatak)

# Koristi C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dodaj main.cpp kao izvorni fajl
add_executable(ZenitelZadatak src/main.cpp)
