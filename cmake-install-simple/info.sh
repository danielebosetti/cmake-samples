
# build and install [module-1] under (?) a modules folder
# > as part of installing: export the [module-1] cmake find- modules (targets?)

# import [module-1] it from another cmake build

# Installation
# We only need to install the following in order to use the library: the header files,
# the tool executable and the built library. This can be done in a very straightforward
# way with the install() command. It will simply copy the files into the ${CMAKE_INSTALL_PREFIX}
# (/usr/local/ under Linux) when entering the cmake install command in a terminal.

###############################################################################################
# build and install module 1
rmdir C:\bin\dev\cmake-install-simple\temp-install /S /Q
mkdir C:\bin\dev\cmake-install-simple\temp-install
cd C:\bin\dev\cmake-install-simple\module-1-install
rmdir build /S /Q
cmake -B build -DCMAKE_INSTALL_PREFIX=C:\bin\dev\cmake-install-simple\temp-install
cmake --build build
cmake --build build --config Release
cmake --build build --target install
cmake --build build --config Release --target install


###############################################################################################
# use module 1 (no vcpkg)
cd C:\bin\dev\cmake-install-simple\exe-uses-module-1
rmdir build /S /Q
cmake -B build -DCMAKE_PREFIX_PATH=C:/bin/dev/cmake-install-simple/temp-install
cmake --build build
cmake --build build --config Release



###############################################################################################
# build and install module 2 (use vcpkg)
cd C:\bin\dev\cmake-install-simple\module-2-install
rmdir build /S /Q
cmv




