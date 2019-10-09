
#include <string_view>

#include "ctre.hpp"

//static constexpr auto variable_pattern =
//	ctll::fixed_string { "([let]|[var])\\s([0-z]+)\\s?([:\\s?[0-z]+]?)\\s?([=\\s?[0-z]+]?)" };
static constexpr auto variable_pattern =
	ctll::fixed_string { "let|var\\s([0-z]+)\\s(.*)" };
static constexpr auto variable_define_pattern =
	ctll::fixed_string { "\\s?:\\s?([0-z]+)(.*)" };
static constexpr auto variable_init_pattern =
	ctll::fixed_string { "\\s?=\\s?([0-z]+)" }; // TODO: replace "[0-z]+"

static constexpr auto integer_literal_pattern = ctll::fixed_string { "([0-9]+)" };
static constexpr auto floating_literal_pattern = ctll::fixed_string { "([.0-9]+)" };

static constexpr auto function_pattern =
	ctll::fixed_string { "func\\s([0-z]+)\\s?\\((.*)\\)(.*)" };
static constexpr auto function_arg_pattern =
	ctll::fixed_string { "\,?\\s?([0-z]+)(\\s?[0-z]+)?:\\s?([0-z]+)(,.*)?" };
