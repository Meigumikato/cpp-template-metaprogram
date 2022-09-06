#pragma once

#include <string>
#include <type_traits>

/**
 * @brief The core implementation of the executable
 *
 * This class makes up the library part of the executable, which means that the
 * main logic is implemented here. This kind of separation makes it easy to
 * test the implementation for the executable, because the logic is nicely
 * separated from the command-line logic implemented in the main function.
 */
struct library
{
  /**
   * @brief Simply initializes the name member to the name of the project
   */
  library();

  const std::string& GetName() const {
    return name;
  }

  std::string name;
};




namespace detail {

// cpp 17 version
// template <typename F, typename... Args>
// auto invoke(F&& f, Args&&... args) -> std::invoke_result_t<F, Args...> {

//   if constexpr (std::is_member_function_pointer_v<F>) {
//     return std::mem_fn(f)(std::forward<Args>(args)...);
//   } else {
//     return f(std::forward<Args>(args)...);
//   }
// }

// cpp 11 version

template <bool T, typename E = void>
using enable_if_t = typename std::enable_if<T, E>::type;

template <typename T>
using decay_t = typename std::decay<T>::type;

template <typename T>
constexpr bool is_member_function_pointer_v = std::is_member_function_pointer<T>::value;

template <typename F, typename... Args,
          typename = enable_if_t<is_member_function_pointer_v<decay_t<F>>>
         >
constexpr auto invoke(F&& f, Args&&... args) noexcept(noexcept(std::mem_fn(f)(std::forward<Args>(args)...)))
  -> decltype(std::mem_fn(f)(std::forward<Args>(args)...)) {
  return std::mem_fn(f)(std::forward<Args>(args)...);
}

template <typename F, typename... Args,
          typename = enable_if_t<!is_member_function_pointer_v<decay_t<F>>>
         >
constexpr auto invoke(F&& f, Args&&... args) noexcept(noexcept(std::forward<F>(f)(std::forward<Args>(args)...))) 
  -> decltype(std::forward<F>(f)(std::forward<Args>(args)...)) {
  return std::forward<F>(f)(std::forward<Args>(args)...);
}

template<typename V, typename F, typename... Args>
struct invoke_result_impl;

template<typename F, typename... Args>
struct invoke_result_impl <std::void_t<decltype(invoke(std::declval<F>(), std::declval<Args>()...))>, F, Args...> {
  using type = decltype(invoke(std::declval<F>(), std::declval<Args>()...));
};

template <typename F, typename... Args>
using invoke_result = invoke_result_impl<void, F, Args...>;

template <typename F, typename... Args>
using invoke_result_t = typename invoke_result<F, Args...>::type;


}
