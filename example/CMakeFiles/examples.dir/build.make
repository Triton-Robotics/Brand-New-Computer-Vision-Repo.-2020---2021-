# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/abanwait/Downloads/rapidjson-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-

# Utility rule file for examples.

# Include the progress variables for this target.
include example/CMakeFiles/examples.dir/progress.make

example/CMakeFiles/examples: bin/capitalize
example/CMakeFiles/examples: bin/condense
example/CMakeFiles/examples: bin/filterkey
example/CMakeFiles/examples: bin/filterkeydom
example/CMakeFiles/examples: bin/jsonx
example/CMakeFiles/examples: bin/lookaheadparser
example/CMakeFiles/examples: bin/messagereader
example/CMakeFiles/examples: bin/parsebyparts
example/CMakeFiles/examples: bin/pretty
example/CMakeFiles/examples: bin/prettyauto
example/CMakeFiles/examples: bin/schemavalidator
example/CMakeFiles/examples: bin/serialize
example/CMakeFiles/examples: bin/simpledom
example/CMakeFiles/examples: bin/simplereader
example/CMakeFiles/examples: bin/simplepullreader
example/CMakeFiles/examples: bin/simplewriter
example/CMakeFiles/examples: bin/sortkeys
example/CMakeFiles/examples: bin/tutorial


examples: example/CMakeFiles/examples
examples: example/CMakeFiles/examples.dir/build.make

.PHONY : examples

# Rule to build all files generated by this target.
example/CMakeFiles/examples.dir/build: examples

.PHONY : example/CMakeFiles/examples.dir/build

example/CMakeFiles/examples.dir/clean:
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && $(CMAKE_COMMAND) -P CMakeFiles/examples.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/examples.dir/clean

example/CMakeFiles/examples.dir/depend:
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021- && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abanwait/Downloads/rapidjson-master /home/abanwait/Downloads/rapidjson-master/example /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021- /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example/CMakeFiles/examples.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/examples.dir/depend

