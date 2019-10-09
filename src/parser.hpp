
#include <optional>
#include <string_view>
#include <vector>

#include "ast.hpp"
#include "patterns.hpp"
#include "ctre.hpp"

std::optional<node>
parse_single(std::string_view s) noexcept;

std::optional<variable_inst>
parse_variable_inst(std::string_view s) noexcept {
  using namespace ctre::literals;

  if (auto [whole1, name, define] = ctre::match<variable_pattern>(s); whole1) {
    std::optional<type> t;
    std::optional<std::string_view> init_str;
    if (auto [whole2, found_type, init] = ctre::match<variable_define_pattern>(define); found_type) {
      t = type { {whole2.to_view()}, found_type.to_view() };
      init_str = init.to_view();
    }
    
    if (!init_str) init_str = define.to_view();
    
    if (!t) return std::nullopt; // TODO: infer type
    if (auto [whole3, value] = ctre::match<variable_init_pattern>(init_str.value()); whole3) {
      if (auto value_inst = parse_single(value))
      	return variable_inst { {whole1.to_view()}, name.to_view(), t.value(), value_inst.value() };
    }
    
    return variable_inst { {whole1.to_view()}, name.to_view(), t.value(), node {} };
  }
  
  return std::nullopt;
}

std::optional<integer_literal_inst>
parse_integer_literal_inst(std::string_view s) noexcept {
  using namespace ctre::literals;

  if (auto [whole, number] = ctre::match<integer_literal_pattern>(s); whole) {
    return integer_literal_inst { {whole.to_view()}, std::stoi(number.to_string()) };
  }
  
  return std::nullopt;
}

std::tuple<std::optional<argument_inst>, std::optional<std::string_view>>
parse_argument_inst(std::string_view s) noexcept {
  using namespace ctre::literals;

  if (auto [whole, label, name, t, rest] = ctre::match<function_arg_pattern>(s); whole) {
    type arg_t { {whole.to_view()}, t.to_view() };
    std::string_view name_sv = name ? name.to_view() : label.to_view();
    return { argument_inst { {whole.to_view()}, name_sv, label.to_view(), arg_t }, rest.to_view() };
  }
  
  return { std::nullopt, std::nullopt };
}

std::optional<function_inst>
parse_function_inst(std::string_view s) noexcept {
  using namespace ctre::literals;

  if (auto [whole, name, args_str, rest] = ctre::match<function_pattern>(s); whole) {
    std::vector<argument_inst> args;
    std::string_view current_arg = args_str.to_view();
parse_arg:
    if (auto [arg, others] = parse_argument_inst(current_arg); arg) {
      args.push_back(arg.value());
      if (others) {
        current_arg = others.value();
        goto parse_arg;
      }
    }
    
    return function_inst { {whole.to_view()}, name.to_view(), type{}, args };
  }
  
  return std::nullopt;
}

std::optional<node>
parse_single(std::string_view s) noexcept {
  if (auto var = parse_variable_inst(s)) return var;
  if (auto integer = parse_integer_literal_inst(s)) return integer;
  if (auto func = parse_function_inst(s)) return func;
  
  return std::nullopt;
}
