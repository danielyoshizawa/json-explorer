![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/danielyoshizawa/json-explorer/cmake-single-platform.yml)
![GitHub commit activity](https://img.shields.io/github/commit-activity/t/danielyoshizawa/json-explorer)
![GitHub issues](https://img.shields.io/github/issues/danielyoshizawa/json-explorer)
![GitHub pull requests](https://img.shields.io/github/issues-pr/danielyoshizawa/json-explorer)
![GitHub Release](https://img.shields.io/github/v/release/danielyoshizawa/json-explorer)

# JSON Explorer

 - [Purpose](#purpose)
 - [Technologies Used](#technologies-used)
 - [Requirements](#requirements)
 - [Architecture and directories](#architecture-and-directories)
 - [Local Configurations](#local-configurations)
 - [Build](#build)
 - [Testing](#testing)
 - [On liner build | test | run command](#on-liner-build--test--run-command)
 - [Commands](#commands)
 - [Roadmap](#roadmap)
 - [Support](#support)

## Purpose
JSON explorer is a command line tool to fetch and navigate through a JSON structure, the intension is to make it easier to navigate complex JSON files.

## Technologies Used
 - [C++](https://isocpp.org/)
 - [CMake](https://cmake.org/)
 - [Catch2](https://github.com/catchorg/Catch2)
 - [LibCurl](https://curl.se/libcurl/)
 - [Simdjson](https://simdjson.org/)

## Requirements

### C++
This project is using C++20, compiling with GCC v.10.2.1, should work with other versions as well, and other c++ compilers, e.g. clang, since it have support to C++20.

### CMake
CMake is our pre-builder of choice, and we are generating makefiles to build it. You can opt for any builder that cmakes provides. You need to have it installed to build the project. To do so run :

`sudo apt install -y cmake`

### Catch2
Catch2 will be download and compiled as you build yhe project, don't need to worry about installing it locally, we only recomend to not constantly doing a full build, because it would that some time to build catch2 as well.

### LibCurl
Current version in use is v8.5.0-2 (openssl version), to install it locally on debain call : 

`sudo apt install -y libcurl4-openssl-dev`

If not in debian, or this lib is not available, check your distro repository to see which version is available, or manually install the .deb file. More information can be found [here](https://curl.se/libcurl/)

### Simdjson
We choose Simdjson for its performance, currently the project is using v3.6.3.1, however, we didn't tested any other and we believe that it will work with any version above v1. To install on debian call:

`sudo apt install -y libsimdjson-dev`

More information can be found [here](https://simdjson.org/).

## Architecture and directories
Following the old MVC architecture

```
Project
|-- src
|   |-- controller : Classes that control the flow of operations
|   |-- model : All the logic of our program
|   |-- test : Unit tests covering mostly the model and libs
|   |-- view : Anything that cin or cout to the console
|
|-- CMakeLists.txt : Base CMake File to set the project dependencies and structures
|-- main.cpp : Program entry point
|-- LICENSE : MIT License (Fell free to fork, modify and use, and if you could give me a Star I'd be very grateful)
|-- README.md : This file you are reading at this very momement. =)
```

## Local Configurations
 - After cloning the project, install the libs and tools pointed in the section [*Requirements*](#requirements).
 - Enter the project src directory and create a folder build (replace \<root\> by the project root folder)

    ```
    cd <root>/src
    mkdir build
    ```
 
### Build
To build and run the project 
 - Create the build using CMake and compile 
    ```
    cmake ..
    make
    ```
 - After the build is done, you can execute the program using
    ```
    ./json-explorer
    ```

### Testing
Tests were writing using Catch2 and integrated with ctest, to run call :

    make test

### On liner build | test | run command
    cd <root>/src && mkdir build && cmake .. && make && make test && ./json-explorer

## Commands

List of commands
```
 load <path>
    - Loads a json from the web, replace <path> with the resouce you want to load, e.g., https://api.com/json
 
 cd <path>
  - Enters the location pointed in <path>, works only on a single layer, to access arrays you must pass the array index, objects fields are accessed by keys.
  - cd .. (dot dot) is used to return one level
  - cd / (slash) is used to return to the root of the JSON
 
 ls
  - Show the content of the current position
 
 exit
  - Leave the program
 
 quit
  - Leave the program
 ```

## Roadmap
 - Implement help function
 - Implement support to read JSON files
 - Improve error handling
 - Implement Prettify Json
 - Editor command (values only)
 - Load variables
 - Arithmetical commands
 - Save to file command
 - Accept multi level paths
 - Add path support to ls command

More to come as the project evolves.

## Support
Feel free to participate in our discurssion page or create a pull request with a solution that you created, we are just getting started but we hope to build an awesome program with your help!

Wish you a wonderful day, my friend!