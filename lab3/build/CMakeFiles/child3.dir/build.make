# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/arnemkova/OS_labs/lab3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arnemkova/OS_labs/lab3/build

# Include any dependencies generated for this target.
include CMakeFiles/child3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/child3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/child3.dir/flags.make

CMakeFiles/child3.dir/src/child.o: CMakeFiles/child3.dir/flags.make
CMakeFiles/child3.dir/src/child.o: ../src/child.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arnemkova/OS_labs/lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/child3.dir/src/child.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/child3.dir/src/child.o -c /home/arnemkova/OS_labs/lab3/src/child.cpp

CMakeFiles/child3.dir/src/child.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/child3.dir/src/child.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arnemkova/OS_labs/lab3/src/child.cpp > CMakeFiles/child3.dir/src/child.i

CMakeFiles/child3.dir/src/child.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/child3.dir/src/child.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arnemkova/OS_labs/lab3/src/child.cpp -o CMakeFiles/child3.dir/src/child.s

CMakeFiles/child3.dir/src/utils.o: CMakeFiles/child3.dir/flags.make
CMakeFiles/child3.dir/src/utils.o: ../src/utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arnemkova/OS_labs/lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/child3.dir/src/utils.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/child3.dir/src/utils.o -c /home/arnemkova/OS_labs/lab3/src/utils.cpp

CMakeFiles/child3.dir/src/utils.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/child3.dir/src/utils.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arnemkova/OS_labs/lab3/src/utils.cpp > CMakeFiles/child3.dir/src/utils.i

CMakeFiles/child3.dir/src/utils.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/child3.dir/src/utils.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arnemkova/OS_labs/lab3/src/utils.cpp -o CMakeFiles/child3.dir/src/utils.s

# Object files for target child3
child3_OBJECTS = \
"CMakeFiles/child3.dir/src/child.o" \
"CMakeFiles/child3.dir/src/utils.o"

# External object files for target child3
child3_EXTERNAL_OBJECTS =

child3: CMakeFiles/child3.dir/src/child.o
child3: CMakeFiles/child3.dir/src/utils.o
child3: CMakeFiles/child3.dir/build.make
child3: CMakeFiles/child3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arnemkova/OS_labs/lab3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable child3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/child3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/child3.dir/build: child3

.PHONY : CMakeFiles/child3.dir/build

CMakeFiles/child3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/child3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/child3.dir/clean

CMakeFiles/child3.dir/depend:
	cd /home/arnemkova/OS_labs/lab3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arnemkova/OS_labs/lab3 /home/arnemkova/OS_labs/lab3 /home/arnemkova/OS_labs/lab3/build /home/arnemkova/OS_labs/lab3/build /home/arnemkova/OS_labs/lab3/build/CMakeFiles/child3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/child3.dir/depend

