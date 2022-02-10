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
    set_target_properties(FeatherUI PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE" MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")

    target_compile_definitions(FeatherUI PRIVATE "_DEBUG;" "_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING;"  "_UNICODE" "UNICODE")
    target_compile_options(FeatherUI PRIVATE /Od /permissive- /sdl /W3 /Y- /Zc:wchar_t)
else ()
    set_target_properties(FeatherUI PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE" MSVC_RUNTIME_LIBRARY "MultiThreaded")

    target_compile_definitions(FeatherUI PRIVATE "NDEBUG" "_UNICODE")
    target_compile_options(FeatherUI PRIVATE /Oi /Gy /permissive- /sdl /W3 /Y- /Zc:wchar_t)

    target_link_options(FeatherUI PRIVATE /OPT:REF /OPT:ICF /LTCG)
endif ()
target_compile_features(FeatherUI PRIVATE cxx_std_20)

target_link_libraries(
        FeatherUI

        PRIVATE ${ADDITIONAL_LIBRARY_DEPENDENCIES}
        PUBLIC d3d9
        PUBLIC d3dx9
)