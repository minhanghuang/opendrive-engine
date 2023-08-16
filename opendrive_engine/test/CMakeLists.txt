cmake_minimum_required(VERSION 3.5.1)

project(opendrive-engine-test VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
find_package(GTest REQUIRED)
pkg_check_modules(Tinyxml2 REQUIRED tinyxml2)

include_directories(
  ../include
  ${Tinyxml2_INCLUDE_DIRS}
)

link_directories (
  ${Tinyxml2_LIBRARY_DIRS}
)

SET(TEST_SOURCES
  parser_test
)

FOREACH(test_src ${TEST_SOURCES})
  add_executable(${test_src} ${test_src}.cc)
  target_link_libraries(${test_src}
    ${Tinyxml2_LIBRARIES}
    opendrive_engine
    GTest::GTest
    GTest::Main
  )
ENDFOREACH(test_src)

install(TARGETS ${TEST_SOURCES}
  EXPORT ${TARGET_NAME}-targets
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

