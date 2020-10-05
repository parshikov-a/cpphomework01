cmake_minimum_required(VERSION 3.2)

project(cmake VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(helloworld_cli main.cpp)

add_library(helloworld_lib lib.cpp)

add_executable(helloworld_version_unittest version_unittest.cpp)

set_target_properties(helloworld_cli helloworld_lib helloworld_version_unittest PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties(helloworld_version_unittest PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(helloworld_cli
    helloworld_lib
    Threads::Threads
)

target_link_libraries(helloworld_version_unittest
    ${Boost_LIBRARIES}
    helloworld_lib
)

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT andrparshikov@yandex.ru)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(helloworld_tests helloworld_version_unittest)
