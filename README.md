# cplus_template

Creates a simple project with makefile and folders.

Project is ready to compile with google's GTest support. 

Folders sceleton after clone project:

```
project
│
└───include
│   │   routes.hpp
│   
└───src
│   │   main.cpp
│   │   routes.cpp
│   
└───tests
    │   gen.cpp
```
---
Folders sceleton after first ```make``` command:  
```
project
│
└───include
│   │   routes.hpp
│   
└───src
│   │   main.cpp
│   │   routes.cpp
│   
└───tests
|   │   gen.cpp
|   
└───build
│   │   main
|   |   
│   └───tests
│       │   gen  
│  
└───objs
    │   gtest.o
    │   gmock.o
    │   testing.o
```

## Requirements
- Google Gtest and Gmock source code: [link](https://github.com/google/googletest)
- GNU Make
- C++ toolchain
