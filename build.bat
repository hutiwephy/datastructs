cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=MinSizeRel -B./cmake-config -G "Ninja"
cmake --build ./cmake-config --config MinSizeRel
