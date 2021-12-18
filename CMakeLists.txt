cmake_minimum_required(VERSION 3.20)
project(RM)
find_package(RapidJSON REQUIRED)
find_package(OpenCV REQUIRED )
set(CMAKE_CXX_STANDARD 11)


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(RM main.cpp
        AutoAim/Armor/Armor.cpp
        AutoAim/Armor/Armor.h
        AutoAim/Detector/Detector.cpp
        AutoAim/Detector/Detector.h
        Camera/Camera_sdk.cpp
        Camera/Camera_sdk.h
        PowerRune/PowerRuneDetector/PowerRuneDetector.cpp
        PowerRune/PowerRuneDetector/PowerRuneDetector.h
        Config/Config_reader.cpp
        Config/Config_reader.h
        Utility/exceptions.h
        Utility/utility.h
        Utility/utility.cpp
        Communication/communication.cpp
        Communication/communication.h
        ThreadManagement/threadManagement.cpp
        ThreadManagement/threadManagement.h)



target_link_libraries(RM ${OpenCV_LIBS})


add_executable(powerRune PowerRune/powerruneTest/detect_powerrune_class.cpp)
target_link_libraries(powerRune ${OpenCV_LIBS})



if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
    message(STATUS "The current platform is arm")
    SET(CMAKE_BUILD_TYPE Release)
    message(STATUS "CMAKE_BUILD_TYPE='${CMAKE_BUILD_TYPE}' is defined")
    message(STATUS "The debug flag is ${CMAKE_CXX_FLAGS_DEBUG}")
else ()
    message(STATUS "The current platform is x86_64")
    SET(CMAKE_BUILD_TYPE Debug)
    message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} is defined")
    message(STATUS "The release flag is ${CMAKE_CXX_FLAGS_RELEASE}")
endif ()

