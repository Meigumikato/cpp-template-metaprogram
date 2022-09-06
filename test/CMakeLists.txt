# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(cpp-template-metaprogramTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(cpp-template-metaprogram_test source/cpp-template-metaprogram_test.cpp)
target_link_libraries(
    cpp-template-metaprogram_test PRIVATE
    cpp-template-metaprogram_lib
    Catch2::Catch2WithMain
)
target_compile_features(cpp-template-metaprogram_test PRIVATE cxx_std_20)

catch_discover_tests(cpp-template-metaprogram_test)

# ---- End-of-file commands ----

add_folders(Test)
