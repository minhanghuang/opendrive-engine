cmake_minimum_required(VERSION 3.0.2)

project(opendrive_engine)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES ${TARGET_NAME}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Tinyxml2 REQUIRED tinyxml2)


###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Tinyxml2_INCLUDE_DIRS}
)

link_directories(
  ${Tinyxml2_LIBRARY_DIRS}
)

file(GLOB_RECURSE OPENDRIVE_ENGINE_SRCS
  "src/*.cc"
)

############################
## Declare a cpp library
############################

add_library(${TARGET_NAME}
   ${OPENDRIVE_ENGINE_SRCS}
)

target_link_libraries(${TARGET_NAME}
  ${catkin_LIBRARIES}
  ${Tinyxml2_LIBRARIES}
)

#############
## Install ##
#############

install(TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME}-targets
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

