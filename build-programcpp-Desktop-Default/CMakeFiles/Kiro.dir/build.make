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
CMAKE_SOURCE_DIR = /home/charles/Documents/SansIMI/programcpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/charles/Documents/SansIMI/build-programcpp-Desktop-Default

# Include any dependencies generated for this target.
include CMakeFiles/Kiro.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Kiro.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Kiro.dir/flags.make

CMakeFiles/Kiro.dir/kiro.cpp.o: CMakeFiles/Kiro.dir/flags.make
CMakeFiles/Kiro.dir/kiro.cpp.o: /home/charles/Documents/SansIMI/programcpp/kiro.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charles/Documents/SansIMI/build-programcpp-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Kiro.dir/kiro.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Kiro.dir/kiro.cpp.o -c /home/charles/Documents/SansIMI/programcpp/kiro.cpp

CMakeFiles/Kiro.dir/kiro.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Kiro.dir/kiro.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charles/Documents/SansIMI/programcpp/kiro.cpp > CMakeFiles/Kiro.dir/kiro.cpp.i

CMakeFiles/Kiro.dir/kiro.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Kiro.dir/kiro.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charles/Documents/SansIMI/programcpp/kiro.cpp -o CMakeFiles/Kiro.dir/kiro.cpp.s

CMakeFiles/Kiro.dir/kiro.cpp.o.requires:

.PHONY : CMakeFiles/Kiro.dir/kiro.cpp.o.requires

CMakeFiles/Kiro.dir/kiro.cpp.o.provides: CMakeFiles/Kiro.dir/kiro.cpp.o.requires
	$(MAKE) -f CMakeFiles/Kiro.dir/build.make CMakeFiles/Kiro.dir/kiro.cpp.o.provides.build
.PHONY : CMakeFiles/Kiro.dir/kiro.cpp.o.provides

CMakeFiles/Kiro.dir/kiro.cpp.o.provides.build: CMakeFiles/Kiro.dir/kiro.cpp.o


CMakeFiles/Kiro.dir/main.cpp.o: CMakeFiles/Kiro.dir/flags.make
CMakeFiles/Kiro.dir/main.cpp.o: /home/charles/Documents/SansIMI/programcpp/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charles/Documents/SansIMI/build-programcpp-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Kiro.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Kiro.dir/main.cpp.o -c /home/charles/Documents/SansIMI/programcpp/main.cpp

CMakeFiles/Kiro.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Kiro.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charles/Documents/SansIMI/programcpp/main.cpp > CMakeFiles/Kiro.dir/main.cpp.i

CMakeFiles/Kiro.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Kiro.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charles/Documents/SansIMI/programcpp/main.cpp -o CMakeFiles/Kiro.dir/main.cpp.s

CMakeFiles/Kiro.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Kiro.dir/main.cpp.o.requires

CMakeFiles/Kiro.dir/main.cpp.o.provides: CMakeFiles/Kiro.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Kiro.dir/build.make CMakeFiles/Kiro.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Kiro.dir/main.cpp.o.provides

CMakeFiles/Kiro.dir/main.cpp.o.provides.build: CMakeFiles/Kiro.dir/main.cpp.o


# Object files for target Kiro
Kiro_OBJECTS = \
"CMakeFiles/Kiro.dir/kiro.cpp.o" \
"CMakeFiles/Kiro.dir/main.cpp.o"

# External object files for target Kiro
Kiro_EXTERNAL_OBJECTS =

Kiro: CMakeFiles/Kiro.dir/kiro.cpp.o
Kiro: CMakeFiles/Kiro.dir/main.cpp.o
Kiro: CMakeFiles/Kiro.dir/build.make
Kiro: /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.9.5
Kiro: /usr/lib/x86_64-linux-gnu/libGL.so
Kiro: /usr/lib/x86_64-linux-gnu/libGLU.so
Kiro: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.9.5
Kiro: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.9.5
Kiro: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.9.5
Kiro: CMakeFiles/Kiro.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/charles/Documents/SansIMI/build-programcpp-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Kiro"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Kiro.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Kiro.dir/build: Kiro

.PHONY : CMakeFiles/Kiro.dir/build

CMakeFiles/Kiro.dir/requires: CMakeFiles/Kiro.dir/kiro.cpp.o.requires
CMakeFiles/Kiro.dir/requires: CMakeFiles/Kiro.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Kiro.dir/requires

CMakeFiles/Kiro.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Kiro.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Kiro.dir/clean

CMakeFiles/Kiro.dir/depend:
	cd /home/charles/Documents/SansIMI/build-programcpp-Desktop-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/charles/Documents/SansIMI/programcpp /home/charles/Documents/SansIMI/programcpp /home/charles/Documents/SansIMI/build-programcpp-Desktop-Default /home/charles/Documents/SansIMI/build-programcpp-Desktop-Default /home/charles/Documents/SansIMI/build-programcpp-Desktop-Default/CMakeFiles/Kiro.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Kiro.dir/depend

