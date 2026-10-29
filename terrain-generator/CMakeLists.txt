# CMakeList.txt : CMake project for terrain-generator, include source and define
# project specific logic here.
#

include(FetchContent)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v2.0.8
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glad)



add_subdirectory(${glad_SOURCE_DIR}/cmake glad_cmake)
glad_add_library(glad REPRODUCIBLE API gl:core=4.6 LANGUAGE c)

add_executable(terrain-generator "main.cpp")
target_link_libraries(terrain-generator PRIVATE glfw glad opengl32)

# ====================================================================
# Ignore "variable used without being initialized" warnings / popups
# ====================================================================
if(MSVC)
    # Ignore compile-time warning C4700 for your executable
    target_compile_options(terrain-generator PRIVATE /wd4700)

    # Disable runtime popup check (/RTC1) in Debug mode
    string(REGEX REPLACE "/RTC(1|su)" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
endif()
