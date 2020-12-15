

rmdir /S /Q build
mkdir build
cmake -B build
cmake --build build --config Debug --verbose > build-debug.txt
build-debug.txt
build\debug\exec-1.exe

cmake --build build --config Release --verbose > build-release.txt
build-release.txt
build\release\exec-1.exe


# edit cmake: try use static linking ( /MTd , /MT )
# see https://stackoverflow.com/questions/14172856/compile-with-mt-instead-of-md-using-cmake


