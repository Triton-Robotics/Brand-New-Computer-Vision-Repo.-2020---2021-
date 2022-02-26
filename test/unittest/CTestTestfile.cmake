# CMake generated Testfile for 
# Source directory: /home/abanwait/Downloads/rapidjson-master/test/unittest
# Build directory: /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/test/unittest
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unittest "/home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/bin/unittest")
set_tests_properties(unittest PROPERTIES  WORKING_DIRECTORY "/home/abanwait/Downloads/rapidjson-master/bin")
add_test(valgrind_unittest "valgrind" "--suppressions=/home/abanwait/Downloads/rapidjson-master/test/valgrind.supp" "--leak-check=full" "--error-exitcode=1" "/home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/bin/unittest" "--gtest_filter=-SIMD.*")
set_tests_properties(valgrind_unittest PROPERTIES  WORKING_DIRECTORY "/home/abanwait/Downloads/rapidjson-master/bin")
