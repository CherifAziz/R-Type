# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seven/work/tech03/rtype/r-type

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seven/work/tech03/rtype/r-type

# Include any dependencies generated for this target.
include src/CMakeFiles/rtype.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/rtype.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/rtype.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/rtype.dir/flags.make

src/CMakeFiles/rtype.dir/GameScene/GameScene.cpp.o: src/CMakeFiles/rtype.dir/flags.make
src/CMakeFiles/rtype.dir/GameScene/GameScene.cpp.o: src/GameScene/GameScene.cpp
src/CMakeFiles/rtype.dir/GameScene/GameScene.cpp.o: src/CMakeFiles/rtype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seven/work/tech03/rtype/r-type/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/rtype.dir/GameScene/GameScene.cpp.o"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/rtype.dir/GameScene/GameScene.cpp.o -MF CMakeFiles/rtype.dir/GameScene/GameScene.cpp.o.d -o CMakeFiles/rtype.dir/GameScene/GameScene.cpp.o -c /home/seven/work/tech03/rtype/r-type/src/GameScene/GameScene.cpp

src/CMakeFiles/rtype.dir/GameScene/GameScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/GameScene/GameScene.cpp.i"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seven/work/tech03/rtype/r-type/src/GameScene/GameScene.cpp > CMakeFiles/rtype.dir/GameScene/GameScene.cpp.i

src/CMakeFiles/rtype.dir/GameScene/GameScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/GameScene/GameScene.cpp.s"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seven/work/tech03/rtype/r-type/src/GameScene/GameScene.cpp -o CMakeFiles/rtype.dir/GameScene/GameScene.cpp.s

src/CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.o: src/CMakeFiles/rtype.dir/flags.make
src/CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.o: src/GameScene/PlayerBullet.cpp
src/CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.o: src/CMakeFiles/rtype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seven/work/tech03/rtype/r-type/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.o"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.o -MF CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.o.d -o CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.o -c /home/seven/work/tech03/rtype/r-type/src/GameScene/PlayerBullet.cpp

src/CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.i"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seven/work/tech03/rtype/r-type/src/GameScene/PlayerBullet.cpp > CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.i

src/CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.s"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seven/work/tech03/rtype/r-type/src/GameScene/PlayerBullet.cpp -o CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.s

src/CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.o: src/CMakeFiles/rtype.dir/flags.make
src/CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.o: src/GameScene/BasicEnemy.cpp
src/CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.o: src/CMakeFiles/rtype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seven/work/tech03/rtype/r-type/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.o"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.o -MF CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.o.d -o CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.o -c /home/seven/work/tech03/rtype/r-type/src/GameScene/BasicEnemy.cpp

src/CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.i"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seven/work/tech03/rtype/r-type/src/GameScene/BasicEnemy.cpp > CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.i

src/CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.s"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seven/work/tech03/rtype/r-type/src/GameScene/BasicEnemy.cpp -o CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.s

src/CMakeFiles/rtype.dir/Core.cpp.o: src/CMakeFiles/rtype.dir/flags.make
src/CMakeFiles/rtype.dir/Core.cpp.o: src/Core.cpp
src/CMakeFiles/rtype.dir/Core.cpp.o: src/CMakeFiles/rtype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seven/work/tech03/rtype/r-type/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/rtype.dir/Core.cpp.o"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/rtype.dir/Core.cpp.o -MF CMakeFiles/rtype.dir/Core.cpp.o.d -o CMakeFiles/rtype.dir/Core.cpp.o -c /home/seven/work/tech03/rtype/r-type/src/Core.cpp

src/CMakeFiles/rtype.dir/Core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/Core.cpp.i"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seven/work/tech03/rtype/r-type/src/Core.cpp > CMakeFiles/rtype.dir/Core.cpp.i

src/CMakeFiles/rtype.dir/Core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/Core.cpp.s"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seven/work/tech03/rtype/r-type/src/Core.cpp -o CMakeFiles/rtype.dir/Core.cpp.s

src/CMakeFiles/rtype.dir/main.cpp.o: src/CMakeFiles/rtype.dir/flags.make
src/CMakeFiles/rtype.dir/main.cpp.o: src/main.cpp
src/CMakeFiles/rtype.dir/main.cpp.o: src/CMakeFiles/rtype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seven/work/tech03/rtype/r-type/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/rtype.dir/main.cpp.o"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/rtype.dir/main.cpp.o -MF CMakeFiles/rtype.dir/main.cpp.o.d -o CMakeFiles/rtype.dir/main.cpp.o -c /home/seven/work/tech03/rtype/r-type/src/main.cpp

src/CMakeFiles/rtype.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/main.cpp.i"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seven/work/tech03/rtype/r-type/src/main.cpp > CMakeFiles/rtype.dir/main.cpp.i

src/CMakeFiles/rtype.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/main.cpp.s"
	cd /home/seven/work/tech03/rtype/r-type/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seven/work/tech03/rtype/r-type/src/main.cpp -o CMakeFiles/rtype.dir/main.cpp.s

# Object files for target rtype
rtype_OBJECTS = \
"CMakeFiles/rtype.dir/GameScene/GameScene.cpp.o" \
"CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.o" \
"CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.o" \
"CMakeFiles/rtype.dir/Core.cpp.o" \
"CMakeFiles/rtype.dir/main.cpp.o"

# External object files for target rtype
rtype_EXTERNAL_OBJECTS =

bin/rtype: src/CMakeFiles/rtype.dir/GameScene/GameScene.cpp.o
bin/rtype: src/CMakeFiles/rtype.dir/GameScene/PlayerBullet.cpp.o
bin/rtype: src/CMakeFiles/rtype.dir/GameScene/BasicEnemy.cpp.o
bin/rtype: src/CMakeFiles/rtype.dir/Core.cpp.o
bin/rtype: src/CMakeFiles/rtype.dir/main.cpp.o
bin/rtype: src/CMakeFiles/rtype.dir/build.make
bin/rtype: /usr/lib/libsfml-graphics.so.2.5.1
bin/rtype: /usr/lib/libsfml-audio.so.2.5.1
bin/rtype: /usr/lib/libsfml-window.so.2.5.1
bin/rtype: /usr/lib/libsfml-system.so.2.5.1
bin/rtype: src/CMakeFiles/rtype.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/seven/work/tech03/rtype/r-type/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../bin/rtype"
	cd /home/seven/work/tech03/rtype/r-type/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rtype.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/rtype.dir/build: bin/rtype
.PHONY : src/CMakeFiles/rtype.dir/build

src/CMakeFiles/rtype.dir/clean:
	cd /home/seven/work/tech03/rtype/r-type/src && $(CMAKE_COMMAND) -P CMakeFiles/rtype.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/rtype.dir/clean

src/CMakeFiles/rtype.dir/depend:
	cd /home/seven/work/tech03/rtype/r-type && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seven/work/tech03/rtype/r-type /home/seven/work/tech03/rtype/r-type/src /home/seven/work/tech03/rtype/r-type /home/seven/work/tech03/rtype/r-type/src /home/seven/work/tech03/rtype/r-type/src/CMakeFiles/rtype.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/rtype.dir/depend

