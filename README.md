# ft_containers

### Description

Goal of this project was to implement behavior of C++ STL containers vector (Array), stack and map in accordance with C++98 standart.

### Build

Run `make` to create tester executable `containers`.
Tester has 2 modes:

0) Running tests for written containers;
1) Running same tests for STL containers.

To specify or change mode run `make re MODE=` and 0 or 1. 

To remove all files created by program run `make fclean`, or `make clean` to remove all except executable.

### Usage

To run tests use command `./containers` `NAME_OF_CONTAINER`, for example `./containers vector`.
