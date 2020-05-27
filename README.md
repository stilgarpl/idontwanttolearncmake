# idontwanttolearncmake
## CMake configuration that "just works".

The goal of this project is to provide a cmake configuration that will work for most simple projects. The developers shouldn't have to edit CMakeLists.txt files.

### This project is for you if...
* You are a beginner developer and learning both C++ and CMake is too much at first
* You don't want to learn cmake, but you have to use it. 
* You just want to build your project and you just want to code and not think about build systems. 
* You couldn't find good cmake tutorial online. 

### This CMake configuration:
* Automatically collects all C and C++ source files from library and executable directories and builds them.
* Provides easy way to separate project into libraries and executables (All executables are linked to all libraries)
* Provides install target that will install all headers, libraries and executables in right locations along with cmake Config files that will enable other cmake projects to use them. 
* Uses Hunter to download external dependencies.
* All names (project, libraries, executables) are configured from corresponding directory names   

### Project structure
```
idontwanttolearncmake/
|--cmake/ <-- cmake configuration
|
|--executables/ <-- folder for all executables
|  |--exampleExe/ <-- main folder for executable, copy it and rename if you want to make another executable
|     |--exampleExe/ <-- source folder, it name should be exacly the same as one folder above (this is top level element in includes)
|     |--depends <-- optional file with external dependencies\
|
|--libraries/ <-- folder for all libraries
   |--exampleLib/ <-- main folder for library, copy it and rename if you want to make another library
      |--exampleLib/ <-- source folder, it name should be exacly the same as one folder above (this is top level element in includes)
      |--depends <-- optional file with external dependencies
```

### External dependencies configuration
Every executable and library can have external dependencies added. They will be downloaded by Hunter and automatically linked. Every line should contain library name and then optionally list of components (it will be transformed for target_link_library as LIBRARY_NAME::COMPONENT_NAME for every component)

### Example source files

Project includes example library and example executable that link to boost::regex and prints something to standard output. Those files should be edited or replaced with actual source files.  