# frogmake
frogmake will compile with gcc from instructions given in a frogm.toml file, similar to cmake but my goal is to make it more like rust's cargo. [for now only works on unix based systems]

# Build from source or download the latest release
You can build it from source with make, i have yet to implement a make install target
Or you can download the binary for the latest release

# How to use
Frogmake uses the toml file format and looks for a frogm.toml file https://toml.io/en/

Right now fromgake lacks features so it only uses 2 tables: build and files.

Under build, you can define name, which will determine how the executable is name (the -o flag)

I am planning to add optimization levels, how many warnings are shown during compile time, making working different directories very straight forward, managing dependencies, among others
