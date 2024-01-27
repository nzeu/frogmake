# frogmake
frogmake will compile with gcc from instructions given in a frogm.toml file, similar to cmake but my goal is to make it more like rust's cargo. [for now only works on unix based systems]

# Build from source
use make in the build directory to compile the project. Make install should come soon

# How to use
Right now fromgake lacks features so it only uses 2 tables: build and files
Under build, you can define name, which will determine how the executable is name (the -o flag)
I am planning to add optimization levels, how many warnings are shown during compile time, making working different directories very straight forward, managing dependencies, among others
