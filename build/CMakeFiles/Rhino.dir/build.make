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
CMAKE_SOURCE_DIR = /home/gcucciat/Documents/rhino

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gcucciat/Documents/rhino/build

# Include any dependencies generated for this target.
include CMakeFiles/Rhino.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Rhino.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Rhino.dir/flags.make

CMakeFiles/Rhino.dir/src/main.cpp.o: CMakeFiles/Rhino.dir/flags.make
CMakeFiles/Rhino.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gcucciat/Documents/rhino/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Rhino.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rhino.dir/src/main.cpp.o -c /home/gcucciat/Documents/rhino/src/main.cpp

CMakeFiles/Rhino.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rhino.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gcucciat/Documents/rhino/src/main.cpp > CMakeFiles/Rhino.dir/src/main.cpp.i

CMakeFiles/Rhino.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rhino.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gcucciat/Documents/rhino/src/main.cpp -o CMakeFiles/Rhino.dir/src/main.cpp.s

CMakeFiles/Rhino.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/Rhino.dir/src/main.cpp.o.requires

CMakeFiles/Rhino.dir/src/main.cpp.o.provides: CMakeFiles/Rhino.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Rhino.dir/build.make CMakeFiles/Rhino.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/Rhino.dir/src/main.cpp.o.provides

CMakeFiles/Rhino.dir/src/main.cpp.o.provides.build: CMakeFiles/Rhino.dir/src/main.cpp.o


CMakeFiles/Rhino.dir/src/mainwindow.cpp.o: CMakeFiles/Rhino.dir/flags.make
CMakeFiles/Rhino.dir/src/mainwindow.cpp.o: ../src/mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gcucciat/Documents/rhino/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Rhino.dir/src/mainwindow.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rhino.dir/src/mainwindow.cpp.o -c /home/gcucciat/Documents/rhino/src/mainwindow.cpp

CMakeFiles/Rhino.dir/src/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rhino.dir/src/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gcucciat/Documents/rhino/src/mainwindow.cpp > CMakeFiles/Rhino.dir/src/mainwindow.cpp.i

CMakeFiles/Rhino.dir/src/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rhino.dir/src/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gcucciat/Documents/rhino/src/mainwindow.cpp -o CMakeFiles/Rhino.dir/src/mainwindow.cpp.s

CMakeFiles/Rhino.dir/src/mainwindow.cpp.o.requires:

.PHONY : CMakeFiles/Rhino.dir/src/mainwindow.cpp.o.requires

CMakeFiles/Rhino.dir/src/mainwindow.cpp.o.provides: CMakeFiles/Rhino.dir/src/mainwindow.cpp.o.requires
	$(MAKE) -f CMakeFiles/Rhino.dir/build.make CMakeFiles/Rhino.dir/src/mainwindow.cpp.o.provides.build
.PHONY : CMakeFiles/Rhino.dir/src/mainwindow.cpp.o.provides

CMakeFiles/Rhino.dir/src/mainwindow.cpp.o.provides.build: CMakeFiles/Rhino.dir/src/mainwindow.cpp.o


CMakeFiles/Rhino.dir/src/mylabel.cpp.o: CMakeFiles/Rhino.dir/flags.make
CMakeFiles/Rhino.dir/src/mylabel.cpp.o: ../src/mylabel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gcucciat/Documents/rhino/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Rhino.dir/src/mylabel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rhino.dir/src/mylabel.cpp.o -c /home/gcucciat/Documents/rhino/src/mylabel.cpp

CMakeFiles/Rhino.dir/src/mylabel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rhino.dir/src/mylabel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gcucciat/Documents/rhino/src/mylabel.cpp > CMakeFiles/Rhino.dir/src/mylabel.cpp.i

CMakeFiles/Rhino.dir/src/mylabel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rhino.dir/src/mylabel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gcucciat/Documents/rhino/src/mylabel.cpp -o CMakeFiles/Rhino.dir/src/mylabel.cpp.s

CMakeFiles/Rhino.dir/src/mylabel.cpp.o.requires:

.PHONY : CMakeFiles/Rhino.dir/src/mylabel.cpp.o.requires

CMakeFiles/Rhino.dir/src/mylabel.cpp.o.provides: CMakeFiles/Rhino.dir/src/mylabel.cpp.o.requires
	$(MAKE) -f CMakeFiles/Rhino.dir/build.make CMakeFiles/Rhino.dir/src/mylabel.cpp.o.provides.build
.PHONY : CMakeFiles/Rhino.dir/src/mylabel.cpp.o.provides

CMakeFiles/Rhino.dir/src/mylabel.cpp.o.provides.build: CMakeFiles/Rhino.dir/src/mylabel.cpp.o


CMakeFiles/Rhino.dir/src/spectrum.cpp.o: CMakeFiles/Rhino.dir/flags.make
CMakeFiles/Rhino.dir/src/spectrum.cpp.o: ../src/spectrum.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gcucciat/Documents/rhino/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Rhino.dir/src/spectrum.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rhino.dir/src/spectrum.cpp.o -c /home/gcucciat/Documents/rhino/src/spectrum.cpp

CMakeFiles/Rhino.dir/src/spectrum.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rhino.dir/src/spectrum.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gcucciat/Documents/rhino/src/spectrum.cpp > CMakeFiles/Rhino.dir/src/spectrum.cpp.i

CMakeFiles/Rhino.dir/src/spectrum.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rhino.dir/src/spectrum.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gcucciat/Documents/rhino/src/spectrum.cpp -o CMakeFiles/Rhino.dir/src/spectrum.cpp.s

CMakeFiles/Rhino.dir/src/spectrum.cpp.o.requires:

.PHONY : CMakeFiles/Rhino.dir/src/spectrum.cpp.o.requires

CMakeFiles/Rhino.dir/src/spectrum.cpp.o.provides: CMakeFiles/Rhino.dir/src/spectrum.cpp.o.requires
	$(MAKE) -f CMakeFiles/Rhino.dir/build.make CMakeFiles/Rhino.dir/src/spectrum.cpp.o.provides.build
.PHONY : CMakeFiles/Rhino.dir/src/spectrum.cpp.o.provides

CMakeFiles/Rhino.dir/src/spectrum.cpp.o.provides.build: CMakeFiles/Rhino.dir/src/spectrum.cpp.o


CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o: CMakeFiles/Rhino.dir/flags.make
CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o: Rhino_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gcucciat/Documents/rhino/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o -c /home/gcucciat/Documents/rhino/build/Rhino_autogen/mocs_compilation.cpp

CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gcucciat/Documents/rhino/build/Rhino_autogen/mocs_compilation.cpp > CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.i

CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gcucciat/Documents/rhino/build/Rhino_autogen/mocs_compilation.cpp -o CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.s

CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o.requires:

.PHONY : CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o.requires

CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o.provides: CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o.requires
	$(MAKE) -f CMakeFiles/Rhino.dir/build.make CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o.provides.build
.PHONY : CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o.provides

CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o.provides.build: CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o


# Object files for target Rhino
Rhino_OBJECTS = \
"CMakeFiles/Rhino.dir/src/main.cpp.o" \
"CMakeFiles/Rhino.dir/src/mainwindow.cpp.o" \
"CMakeFiles/Rhino.dir/src/mylabel.cpp.o" \
"CMakeFiles/Rhino.dir/src/spectrum.cpp.o" \
"CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o"

# External object files for target Rhino
Rhino_EXTERNAL_OBJECTS =

../bin/Rhino: CMakeFiles/Rhino.dir/src/main.cpp.o
../bin/Rhino: CMakeFiles/Rhino.dir/src/mainwindow.cpp.o
../bin/Rhino: CMakeFiles/Rhino.dir/src/mylabel.cpp.o
../bin/Rhino: CMakeFiles/Rhino.dir/src/spectrum.cpp.o
../bin/Rhino: CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o
../bin/Rhino: CMakeFiles/Rhino.dir/build.make
../bin/Rhino: /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so.5.9.5
../bin/Rhino: /usr/local/qwt-6.1.5/lib/libqwt.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libCore.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libImt.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libRIO.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libNet.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libHist.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libGraf.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libGraf3d.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libGpad.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libROOTDataFrame.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libTree.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libTreePlayer.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libRint.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libPostscript.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libMatrix.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libPhysics.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libMathCore.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libThread.so
../bin/Rhino: /home/gcucciat/Programs/root/lib/libMultiProc.so
../bin/Rhino: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.9.5
../bin/Rhino: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.9.5
../bin/Rhino: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.9.5
../bin/Rhino: CMakeFiles/Rhino.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gcucciat/Documents/rhino/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../bin/Rhino"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Rhino.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Rhino.dir/build: ../bin/Rhino

.PHONY : CMakeFiles/Rhino.dir/build

CMakeFiles/Rhino.dir/requires: CMakeFiles/Rhino.dir/src/main.cpp.o.requires
CMakeFiles/Rhino.dir/requires: CMakeFiles/Rhino.dir/src/mainwindow.cpp.o.requires
CMakeFiles/Rhino.dir/requires: CMakeFiles/Rhino.dir/src/mylabel.cpp.o.requires
CMakeFiles/Rhino.dir/requires: CMakeFiles/Rhino.dir/src/spectrum.cpp.o.requires
CMakeFiles/Rhino.dir/requires: CMakeFiles/Rhino.dir/Rhino_autogen/mocs_compilation.cpp.o.requires

.PHONY : CMakeFiles/Rhino.dir/requires

CMakeFiles/Rhino.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Rhino.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Rhino.dir/clean

CMakeFiles/Rhino.dir/depend:
	cd /home/gcucciat/Documents/rhino/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gcucciat/Documents/rhino /home/gcucciat/Documents/rhino /home/gcucciat/Documents/rhino/build /home/gcucciat/Documents/rhino/build /home/gcucciat/Documents/rhino/build/CMakeFiles/Rhino.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Rhino.dir/depend

