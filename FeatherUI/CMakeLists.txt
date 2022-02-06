# I'll be honest, I don't know what Im doing, I just need this to work with CMake
# Thanks for your understanding
file(
        GLOB_RECURSE featherui_SRC
        "*.h"
        "*.cpp"
)

add_library(FeatherUI STATIC ${featherui_SRC})
target_include_directories(FeatherUI PUBLIC Headers PRIVATE Headers/FeatherUI PUBLIC ${DIRECTX_PATH}Include)
target_link_directories(FeatherUI PRIVATE ${DIRECTX_PATH}Lib\\x64)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    set_target_properties(FeatherUI PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE")

    target_compile_definitions(FeatherUI PRIVATE "_DEBUG;" "_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING;")
    target_compile_options(FeatherUI PRIVATE /Od /permissive- /sdl /W3 /Y- /Zc:wchar_t)
else ()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    set_target_properties(FeatherUI PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE")

    target_compile_definitions(FeatherUI PRIVATE "NDEBUG")
    target_compile_options(FeatherUI PRIVATE /Oi /Gy /permissive- /sdl /W3 /Y- /Zc:wchar_t)
endif ()

target_link_libraries(
        FeatherUI

        PRIVATE ${ADDITIONAL_LIBRARY_DEPENDENCIES}
        PUBLIC d3d9
        PUBLIC d3dx9
)