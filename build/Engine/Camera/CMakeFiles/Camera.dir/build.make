# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/airat/Projects/shootEmUp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/airat/Projects/shootEmUp/build

# Include any dependencies generated for this target.
include Engine/Camera/CMakeFiles/Camera.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Engine/Camera/CMakeFiles/Camera.dir/compiler_depend.make

# Include the progress variables for this target.
include Engine/Camera/CMakeFiles/Camera.dir/progress.make

# Include the compile flags for this target's objects.
include Engine/Camera/CMakeFiles/Camera.dir/flags.make

Engine/Camera/CMakeFiles/Camera.dir/ICamera.cpp.o: Engine/Camera/CMakeFiles/Camera.dir/flags.make
Engine/Camera/CMakeFiles/Camera.dir/ICamera.cpp.o: /Users/airat/Projects/shootEmUp/Engine/Camera/ICamera.cpp
Engine/Camera/CMakeFiles/Camera.dir/ICamera.cpp.o: Engine/Camera/CMakeFiles/Camera.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/airat/Projects/shootEmUp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Engine/Camera/CMakeFiles/Camera.dir/ICamera.cpp.o"
	cd /Users/airat/Projects/shootEmUp/build/Engine/Camera && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Engine/Camera/CMakeFiles/Camera.dir/ICamera.cpp.o -MF CMakeFiles/Camera.dir/ICamera.cpp.o.d -o CMakeFiles/Camera.dir/ICamera.cpp.o -c /Users/airat/Projects/shootEmUp/Engine/Camera/ICamera.cpp

Engine/Camera/CMakeFiles/Camera.dir/ICamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Camera.dir/ICamera.cpp.i"
	cd /Users/airat/Projects/shootEmUp/build/Engine/Camera && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/airat/Projects/shootEmUp/Engine/Camera/ICamera.cpp > CMakeFiles/Camera.dir/ICamera.cpp.i

Engine/Camera/CMakeFiles/Camera.dir/ICamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/ICamera.cpp.s"
	cd /Users/airat/Projects/shootEmUp/build/Engine/Camera && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/airat/Projects/shootEmUp/Engine/Camera/ICamera.cpp -o CMakeFiles/Camera.dir/ICamera.cpp.s

# Object files for target Camera
Camera_OBJECTS = \
"CMakeFiles/Camera.dir/ICamera.cpp.o"

# External object files for target Camera
Camera_EXTERNAL_OBJECTS =

Engine/Camera/libCamera.a: Engine/Camera/CMakeFiles/Camera.dir/ICamera.cpp.o
Engine/Camera/libCamera.a: Engine/Camera/CMakeFiles/Camera.dir/build.make
Engine/Camera/libCamera.a: Engine/Camera/CMakeFiles/Camera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/airat/Projects/shootEmUp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCamera.a"
	cd /Users/airat/Projects/shootEmUp/build/Engine/Camera && $(CMAKE_COMMAND) -P CMakeFiles/Camera.dir/cmake_clean_target.cmake
	cd /Users/airat/Projects/shootEmUp/build/Engine/Camera && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Camera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Engine/Camera/CMakeFiles/Camera.dir/build: Engine/Camera/libCamera.a
.PHONY : Engine/Camera/CMakeFiles/Camera.dir/build

Engine/Camera/CMakeFiles/Camera.dir/clean:
	cd /Users/airat/Projects/shootEmUp/build/Engine/Camera && $(CMAKE_COMMAND) -P CMakeFiles/Camera.dir/cmake_clean.cmake
.PHONY : Engine/Camera/CMakeFiles/Camera.dir/clean

Engine/Camera/CMakeFiles/Camera.dir/depend:
	cd /Users/airat/Projects/shootEmUp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/airat/Projects/shootEmUp /Users/airat/Projects/shootEmUp/Engine/Camera /Users/airat/Projects/shootEmUp/build /Users/airat/Projects/shootEmUp/build/Engine/Camera /Users/airat/Projects/shootEmUp/build/Engine/Camera/CMakeFiles/Camera.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Engine/Camera/CMakeFiles/Camera.dir/depend
