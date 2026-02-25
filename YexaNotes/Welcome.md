ChatGPT suggested this for the folder layout of the project:

```
yexa/  
├── CMakeLists.txt  
├── src/  
│   └── main.cpp  
├── screen/  
│   ├── CMakeLists.txt        # optional: sub-CMake  
│   ├── include/  
│   │   └── screen/  
│   │       └── screen.hpp  
│   └── src/  
│       └── screen.cpp
```

I might want to rethink using the name `screen` for the screen handling library. `screen` is already a [well-known terminal program](https://www.gnu.org/software/screen/manual/screen.html).