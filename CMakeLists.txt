cmake_minimum_required(VERSION 3.0.0)
project(wx-pomodoro VERSION 0.1.0)

include(CTest)
enable_testing()

## TODO: set to ON if triplet is static
set(wxWidgets_USE_STATIC ON)

find_package(wxWidgets COMPONENTS core base)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")

add_executable(${PROJECT_NAME} WIN32 src/tomato-app.cpp src/tomato-frame.cpp src/tomato-tray.cpp src/wx-pomodoro.rc)

target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})

set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
