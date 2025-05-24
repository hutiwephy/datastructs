# Datastructs
Extended Data Structures and Functionality for the C language

This library aims to provide support for arrays, lists, dictionaries and much more to the C language. 

## Contents
- [Adding to a CMake Project](#adding-to-a-cmake-project)
- [License](#license)


## Adding to a CMake Project
In the `CMakeLists.txt` before the targets add:
```cmake
include(FetchContent)

FetchContent_Declare(
    CTOOLS_DATASTRUCTS
    GIT_REPOSITORY https://github.com/hutiwephy/datastructs.git
    GIT_TAG master
)
FetchContent_MakeAvailable(CTOOLS_DATASTRUCTS)
```
and after the target declaration add:
```cmake
target_link_libraries(your_target CTOOLS::datastructs)
```

## License
```

   Copyright 2024 hutiwephy

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

```
