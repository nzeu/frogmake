# frogmake
frogmake will compile with gcc from instructions given in a frogm.toml file [for now only works on unix based systems]

# Installation
```
git clone https://github.com/nzeu/frogmake
```
```
cd frogmake/build && make
```
This will create a binary in the build directory

# How to use
Frogmake uses the toml file format and looks for a frogm.toml file https://toml.io/en/

Right now fromgake lacks features so it only uses 2 tables: build and files.

Under build, you can define name, which will determine how the executable is name (the -o flag)

I am planning to add optimization levels, how many warnings are shown during compile time, making working different directories very straight forward, managing dependencies, among others
