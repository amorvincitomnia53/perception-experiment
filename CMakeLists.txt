cmake_minimum_required(VERSION 3.00)

project(main)


set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig)
pkg_check_modules(gtkmm IMPORTED_TARGET gtkmm-3.0 )
#pkg_check_modules(epoxy IMPORTED_TARGET epoxy)

find_package(Boost)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/oglplus)


link_libraries(PkgConfig::gtkmm)
add_executable(main main.cpp )
add_executable(main2 main2.cpp )