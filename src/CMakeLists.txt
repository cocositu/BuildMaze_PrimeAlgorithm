# CMakeLists.txt in the src directory

# Define the sources for the executable
set(SOURCES maze.cpp)

# Define the name of the executable
add_executable(MyProject ${SOURCES})

# Specify the include directories for the executable
target_include_directories(MyProject PRIVATE ../include)

# Link the executable to the library file
target_link_libraries(MyProject graphics64)

link_directories("D:\\Software\\VScode\\mingw64\\lib")
target_link_libraries(MyProject libgraphics64.a
        libgdi32.a libimm32.a libmsimg32.a libole32.a
        liboleaut32.a libwinmm.a libuuid.a libgdiplus.a)

