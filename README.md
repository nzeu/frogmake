# frogmake
>frogmake will compile with gcc from instructions given in a frogm.toml file [for now only works on unix based systems]

## Installation
```
git clone https://github.com/nzeu/frogmake
```
```
cd frogmake/build && make
```
This will create a binary in the build directory

## How to use
Frogmake uses the toml file format and looks for a frogm.toml file https://toml.io/en/

Define the name variable to set the name of the executable, the src array for the .c files and under the headers table, make an array for each directory containing headers with the file paths
