# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /home/yabiel/.local/lib/python3.10/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/yabiel/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/build

# Include any dependencies generated for this target.
include CMakeFiles/aug_real.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/aug_real.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/aug_real.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/aug_real.dir/flags.make

CMakeFiles/aug_real.dir/aug_real.cpp.o: CMakeFiles/aug_real.dir/flags.make
CMakeFiles/aug_real.dir/aug_real.cpp.o: /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/aug_real.cpp
CMakeFiles/aug_real.dir/aug_real.cpp.o: CMakeFiles/aug_real.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/aug_real.dir/aug_real.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/aug_real.dir/aug_real.cpp.o -MF CMakeFiles/aug_real.dir/aug_real.cpp.o.d -o CMakeFiles/aug_real.dir/aug_real.cpp.o -c /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/aug_real.cpp

CMakeFiles/aug_real.dir/aug_real.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aug_real.dir/aug_real.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/aug_real.cpp > CMakeFiles/aug_real.dir/aug_real.cpp.i

CMakeFiles/aug_real.dir/aug_real.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aug_real.dir/aug_real.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/aug_real.cpp -o CMakeFiles/aug_real.dir/aug_real.cpp.s

CMakeFiles/aug_real.dir/common_code.cpp.o: CMakeFiles/aug_real.dir/flags.make
CMakeFiles/aug_real.dir/common_code.cpp.o: /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/common_code.cpp
CMakeFiles/aug_real.dir/common_code.cpp.o: CMakeFiles/aug_real.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/aug_real.dir/common_code.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/aug_real.dir/common_code.cpp.o -MF CMakeFiles/aug_real.dir/common_code.cpp.o.d -o CMakeFiles/aug_real.dir/common_code.cpp.o -c /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/common_code.cpp

CMakeFiles/aug_real.dir/common_code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aug_real.dir/common_code.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/common_code.cpp > CMakeFiles/aug_real.dir/common_code.cpp.i

CMakeFiles/aug_real.dir/common_code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aug_real.dir/common_code.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/common_code.cpp -o CMakeFiles/aug_real.dir/common_code.cpp.s

# Object files for target aug_real
aug_real_OBJECTS = \
"CMakeFiles/aug_real.dir/aug_real.cpp.o" \
"CMakeFiles/aug_real.dir/common_code.cpp.o"

# External object files for target aug_real
aug_real_EXTERNAL_OBJECTS =

aug_real: CMakeFiles/aug_real.dir/aug_real.cpp.o
aug_real: CMakeFiles/aug_real.dir/common_code.cpp.o
aug_real: CMakeFiles/aug_real.dir/build.make
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_alphamat.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_barcode.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_dnn_objdetect.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_dnn_superres.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_face.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_hfs.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_img_hash.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_intensity_transform.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_mcc.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_quality.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_rapid.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_tracking.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_wechat_qrcode.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_text.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_video.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_dnn.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.5.4d
aug_real: /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.5.4d
aug_real: CMakeFiles/aug_real.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable aug_real"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aug_real.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/aug_real.dir/build: aug_real
.PHONY : CMakeFiles/aug_real.dir/build

CMakeFiles/aug_real.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/aug_real.dir/cmake_clean.cmake
.PHONY : CMakeFiles/aug_real.dir/clean

CMakeFiles/aug_real.dir/depend:
	cd /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/build /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/build /home/yabiel/Documents/FSIV/P4/i12gafej/aug_real/build/CMakeFiles/aug_real.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/aug_real.dir/depend

