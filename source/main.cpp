#include <iostream>
#include <string>

#include "lib.hpp"


template <typename F>
void Test(F&& f) {

  if constexpr (std::is_member_function_pointer_v<std::decay_t<F>>) {
    std::cout << typeid(f).name() << "\n";
  }
}


int Test1(int, int);

auto main() -> int
{
  auto const lib = library {};
  auto const message = "Hello from " + lib.name + "!";

  auto res = detail::invoke(&library::GetName, lib); 

  detail::invoke(Test<decltype(&library::GetName)>, &library::GetName);

  detail::invoke_result_t<decltype(Test1), int> x;

  std::cout << message << '\n';
  return 0;
}
