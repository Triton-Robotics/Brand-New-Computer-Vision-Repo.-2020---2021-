cmake_minimum_required(VERSION 3.20)
project(RM)
find_package(RapidJSON REQUIRED)

set(CMAKE_CXX_STANDARD 11)
include_directories("./")
add_executable(RM main.cpp AutoAim/Armor/Aromor.cpp AutoAim/Armor/Aromor.h AutoAim/Detector/Detector.cpp AutoAim/Detector/Detector.h Camera/Camera_sdk.cpp Camera/Camera_sdk.h PowerRune/PowerRuneDetector/PowerRuneDetector.cpp PowerRune/PowerRuneDetector/PowerRuneDetector.h Config/Config_reader.cpp Config/Config_reader.h Utility/exceptions.h Utility/utility.h Utility/utility.cpp)

