# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\CLionProjects\Cjson_withTests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\CLionProjects\Cjson_withTests\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Cjson_withTests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Cjson_withTests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Cjson_withTests.dir/flags.make

CMakeFiles/Cjson_withTests.dir/main.cpp.obj: CMakeFiles/Cjson_withTests.dir/flags.make
CMakeFiles/Cjson_withTests.dir/main.cpp.obj: CMakeFiles/Cjson_withTests.dir/includes_CXX.rsp
CMakeFiles/Cjson_withTests.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionProjects\Cjson_withTests\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Cjson_withTests.dir/main.cpp.obj"
	"D:\Program Files\JetBrains\CLion 2020.1.1\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Cjson_withTests.dir\main.cpp.obj -c D:\CLionProjects\Cjson_withTests\main.cpp

CMakeFiles/Cjson_withTests.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cjson_withTests.dir/main.cpp.i"
	"D:\Program Files\JetBrains\CLion 2020.1.1\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CLionProjects\Cjson_withTests\main.cpp > CMakeFiles\Cjson_withTests.dir\main.cpp.i

CMakeFiles/Cjson_withTests.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cjson_withTests.dir/main.cpp.s"
	"D:\Program Files\JetBrains\CLion 2020.1.1\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CLionProjects\Cjson_withTests\main.cpp -o CMakeFiles\Cjson_withTests.dir\main.cpp.s

# Object files for target Cjson_withTests
Cjson_withTests_OBJECTS = \
"CMakeFiles/Cjson_withTests.dir/main.cpp.obj"

# External object files for target Cjson_withTests
Cjson_withTests_EXTERNAL_OBJECTS =

Cjson_withTests.exe: CMakeFiles/Cjson_withTests.dir/main.cpp.obj
Cjson_withTests.exe: CMakeFiles/Cjson_withTests.dir/build.make
Cjson_withTests.exe: Cjson_lib/libCjson_lib.a
Cjson_withTests.exe: CMakeFiles/Cjson_withTests.dir/linklibs.rsp
Cjson_withTests.exe: CMakeFiles/Cjson_withTests.dir/objects1.rsp
Cjson_withTests.exe: CMakeFiles/Cjson_withTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLionProjects\Cjson_withTests\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Cjson_withTests.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Cjson_withTests.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Cjson_withTests.dir/build: Cjson_withTests.exe

.PHONY : CMakeFiles/Cjson_withTests.dir/build

CMakeFiles/Cjson_withTests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Cjson_withTests.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Cjson_withTests.dir/clean

CMakeFiles/Cjson_withTests.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLionProjects\Cjson_withTests D:\CLionProjects\Cjson_withTests D:\CLionProjects\Cjson_withTests\cmake-build-debug D:\CLionProjects\Cjson_withTests\cmake-build-debug D:\CLionProjects\Cjson_withTests\cmake-build-debug\CMakeFiles\Cjson_withTests.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Cjson_withTests.dir/depend

