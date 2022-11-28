cmake_minimum_required(VERSION 3.23)

project(EndlessGame LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Create the ShooterWorld Library
add_library(ShooterWorld STATIC)

target_sources(ShooterWorld
    PRIVATE
    WorldClass.cpp
    Coords.cpp
    Laser.cpp
    
    PUBLIC FILE_SET HEADERS
    BASE_DIRS ${PROJECT_SOURCE_DIR}
    FILES
    WorldClass.hpp
    Coords.hpp
    Laser.hpp
)

target_link_libraries(ShooterWorld
    PUBLIC
    Qt6::Widgets
    #Qt6::Core
    #Qt6::Gui
)

install(TARGETS ShooterWorld
    EXPORT ShooterWorldTargets
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(EXPORT ShooterWorldTargets
    FILE ShooterWorldTargets.cmake
    NAMESPACE ShooterWorld::
    DESTINATION lib/cmake/ShooterWorld)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "ShooterWorldConfigVersion.cmake"
    VERSION ${ShooterWorld_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(
    FILES
        "ShooterWorldConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ShooterWorldConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)

#Create ShooterWorld UnitTests Library
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(ShooterWorld_UnitTest)
target_sources(ShooterWorld_UnitTest
    PRIVATE
    ShooterWorld_UnitTests.cpp
)
target_link_libraries(ShooterWorld_UnitTest PRIVATE
          ${GTEST_LIBRARIES}
     ${GTEST_MAIN_LIBRARIES}
    ShooterWorld
)

#create the Qt GUI Executable
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(EndlessShooter ${PROJECT_SOURCES})
target_sources(EndlessShooter PRIVATE
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  icons/icons.qrc
  Gridscene.cpp
  Gridscene.h
)

target_link_libraries(EndlessShooter PRIVATE
  Qt6::Widgets
  ShooterWorld
)
