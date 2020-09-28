cmake_minimum_required(VERSION 3.1.0)

project(Rhino)

# 
# Automatically generate QT objects
#
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(AUTOGEN_BUILD_DIR ${PROJECT_SOURCE_DIR})

#
# Output directory
#
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin/)
file(MAKE_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# set(CMAKE_VERBOSE_MAKEFILE ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#
# Find QT
#
find_package(Qt5 COMPONENTS Widgets REQUIRED)

#
# Fint QT Printer
#
find_package(Qt5PrintSupport REQUIRED)

#
# Find QWT
#

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(QWT REQUIRED) 

if( NOT QWT_FOUND )
    message("QWT not found; set the proper include directory with -D QWT_INCLUDE_PATH and the lib directory with -D QWT_LIBRARY_PATH")
    return()
endif()

#
# Find ROOT
#
if(EXISTS $ENV{ROOTSYS}/cmake/ROOTConfig.cmake)
    list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
else()
    list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
endif()

find_package(ROOT REQUIRED)
# Add ROOTs header paths
include_directories(${ROOT_INCLUDE_DIRS})

#
# Source location
#
set( SRC_DIR ${PROJECT_SOURCE_DIR}/src/ )
include_directories(${SRC_DIR})

set( SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/mainwindow.cpp
    ${SRC_DIR}/mylabel.cpp
    ${SRC_DIR}/spectrum.cpp
    )

#
# Compilation
#   MOC_SRCS, RES_SOURCES and UI_HEADERS are generated automatically (CMAKE_AUTOMOC, CMAKE_AUTOUIC, CMAKE_AUTORCC)
#
add_executable( Rhino ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )

#
# Link QT and ROOT libraries
#
target_link_libraries(Rhino Qt5::Widgets Qt5::PrintSupport Qwt::Qwt ${ROOT_LIBRARIES})
