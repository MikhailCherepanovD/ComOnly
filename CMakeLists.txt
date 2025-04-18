cmake_minimum_required(VERSION 3.14)

project(ScannerComOnlyNew LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

FILE(GLOB SOURCE_FILES
    "./*.h"
    "./*.cpp"
    "./.ui"
)
add_executable(ScannerComOnlyNew
  ${SOURCE_FILES}
)

target_link_libraries(ScannerComOnlyNew Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS ScannerComOnlyNew
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
