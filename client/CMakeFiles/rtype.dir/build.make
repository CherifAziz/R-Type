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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client

# Include any dependencies generated for this target.
include CMakeFiles/rtype.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rtype.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rtype.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rtype.dir/flags.make

CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.o: CMakeFiles/rtype.dir/flags.make
CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.o: src/GameScene/GameScene.cpp
CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.o: CMakeFiles/rtype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.o -MF CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.o.d -o CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.o -c /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/src/GameScene/GameScene.cpp

CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/src/GameScene/GameScene.cpp > CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.i

CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/src/GameScene/GameScene.cpp -o CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.s

CMakeFiles/rtype.dir/src/Core.cpp.o: CMakeFiles/rtype.dir/flags.make
CMakeFiles/rtype.dir/src/Core.cpp.o: src/Core.cpp
CMakeFiles/rtype.dir/src/Core.cpp.o: CMakeFiles/rtype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/rtype.dir/src/Core.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rtype.dir/src/Core.cpp.o -MF CMakeFiles/rtype.dir/src/Core.cpp.o.d -o CMakeFiles/rtype.dir/src/Core.cpp.o -c /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/src/Core.cpp

CMakeFiles/rtype.dir/src/Core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/src/Core.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/src/Core.cpp > CMakeFiles/rtype.dir/src/Core.cpp.i

CMakeFiles/rtype.dir/src/Core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/src/Core.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/src/Core.cpp -o CMakeFiles/rtype.dir/src/Core.cpp.s

CMakeFiles/rtype.dir/src/main.cpp.o: CMakeFiles/rtype.dir/flags.make
CMakeFiles/rtype.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/rtype.dir/src/main.cpp.o: CMakeFiles/rtype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/rtype.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rtype.dir/src/main.cpp.o -MF CMakeFiles/rtype.dir/src/main.cpp.o.d -o CMakeFiles/rtype.dir/src/main.cpp.o -c /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/src/main.cpp

CMakeFiles/rtype.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/src/main.cpp > CMakeFiles/rtype.dir/src/main.cpp.i

CMakeFiles/rtype.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/src/main.cpp -o CMakeFiles/rtype.dir/src/main.cpp.s

# Object files for target rtype
rtype_OBJECTS = \
"CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.o" \
"CMakeFiles/rtype.dir/src/Core.cpp.o" \
"CMakeFiles/rtype.dir/src/main.cpp.o"

# External object files for target rtype
rtype_EXTERNAL_OBJECTS =

rtype: CMakeFiles/rtype.dir/src/GameScene/GameScene.cpp.o
rtype: CMakeFiles/rtype.dir/src/Core.cpp.o
rtype: CMakeFiles/rtype.dir/src/main.cpp.o
rtype: CMakeFiles/rtype.dir/build.make
rtype: /opt/homebrew/lib/libsfml-graphics.2.5.1.dylib
rtype: /opt/homebrew/lib/libsfml-audio.2.5.1.dylib
rtype: /opt/homebrew/lib/libboost_system-mt.dylib
rtype: /opt/homebrew/lib/libboost_serialization-mt.dylib
rtype: /opt/homebrew/lib/libsfml-window.2.5.1.dylib
rtype: /opt/homebrew/lib/libsfml-system.2.5.1.dylib
rtype: CMakeFiles/rtype.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable rtype"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rtype.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rtype.dir/build: rtype
.PHONY : CMakeFiles/rtype.dir/build

CMakeFiles/rtype.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rtype.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rtype.dir/clean

CMakeFiles/rtype.dir/depend:
	cd /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client /Users/nicolasmoreau/Delivery/2022-2023/CPP/R-Type/client/CMakeFiles/rtype.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rtype.dir/depend

