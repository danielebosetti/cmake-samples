cmake_minimum_required(VERSION 3.15)

# edit the global setting
cmake_policy(SET CMP0091 NEW)
set( CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" )

project(myproject CXX)

add_library( module-1 module.cpp )

add_executable( exec-1 main.cpp )
target_link_libraries( exec-1 module-1 )

# break it, gogo

# _ITERATOR_DEBUG_LEVEL : see
# https://docs.microsoft.com/en-us/cpp/standard-library/iterator-debug-level?view=vs-2019

# break it with static/dynamic mismatch
# set_property(TARGET module-1 PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
# module uses static linkage, exec uses dynamic linking, errors are
# libcpmtd.lib(locale0.obj) : error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MTd_StaticDebug' doesn't match value 'MDd_DynamicDebug' in main.obj [C:\bin\dev\cmake-check-md-mt-flags\build\exec-1.vcxproj]
#and also msvcprtd.lib(MSVCP140D.dll) : error LNK2005: "public: bool __cdecl std::ios_base::good(void)const " (?good@ios_base@std@@QEBA_NXZ) already defined in module-1.lib(module.obj) [C:\bin\dev\cmake-check-md-mt-flags\build\exec-1.vcxproj]


# break it with module=release/exec=debug
#set_property(TARGET module-1 PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
# build debug config
# breaks with errors:
# (Link target) -> 
#   module-1.lib(module.obj) : error LNK2038: mismatch detected for '_ITERATOR_DEBUG_LEVEL': value '0' doesn't match value '2' in main.obj [C:\bin\dev\cmake-check-md-mt-flags\build\exec-1.vcxproj]
#   module-1.lib(module.obj) : error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MD_DynamicRelease' doesn't match value 'MDd_DynamicDebug' in main.obj [C:\bin\dev\cmake-check-md-mt-flags\build\exec-1.vcxproj]

# break it with module=debug/exec=release
# set_property(TARGET exec-1 PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
#set_target_properties( exec-1 PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

# build debug config
# breaks with errors:
# "C:\bin\dev\cmake-check-md-mt-flags\build\exec-1.vcxproj" (default target) (3) ->
# (Link target) -> 
# module-1.lib(module.obj) : error LNK2038: mismatch detected for '_ITERATOR_DEBUG_LEVEL': value '2' doesn't match value '0' in main.obj [C:\bin\dev\cmake-check-md-mt-flags\build\exec-1.vcxproj]
# module-1.lib(module.obj) : error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MDd_DynamicDebug' doesn't match value 'MD_DynamicRelease' in main.obj [C:\bin\dev\cmake-check-md-mt-flags\build\exec-1.vcxproj]
# C:\bin\dev\cmake-check-md-mt-flags\build\Debug\exec-1.exe : fatal error LNK1319: 2 mismatches detected [C:\bin\dev\cmake-check-md-mt-flags\build\exec-1.vcxproj]

# NOTE: on error [LNK2038: mismatch detected for 'RuntimeLibrary': value 'MDd_DynamicDebug' doesn't match value 'MD_DynamicRelease' in main.obj]
# we are linking main.obj and some library
# mismatch detected for 'RuntimeLibrary' : means the c++ runtime library
# [value MDd_DynamicDebug] : it is the setting for the library we are linking to
# [value MD_DynamicRelease] : it is the setting of the "main" object file we are linking
