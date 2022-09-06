cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    cpp-template-metaprogram
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    cpp-template-metaprogram_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    cpp-template-metaprogram_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(cpp-template-metaprogram_lib PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
target_link_libraries(cpp-template-metaprogram_lib PRIVATE fmt::fmt)

# ---- Declare executable ----

add_executable(cpp-template-metaprogram_exe source/main.cpp)
add_executable(cpp-template-metaprogram::exe ALIAS cpp-template-metaprogram_exe)

set_target_properties(
    cpp-template-metaprogram_exe PROPERTIES
    OUTPUT_NAME cpp-template-metaprogram
    EXPORT_NAME exe
)

target_compile_features(cpp-template-metaprogram_exe PRIVATE cxx_std_20)

target_link_libraries(cpp-template-metaprogram_exe PRIVATE cpp-template-metaprogram_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT cpp-template-metaprogram_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of cpp-template-metaprogram"
  )
endif()

include(cmake/dev-mode.cmake)
