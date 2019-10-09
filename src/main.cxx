
#include <iostream>
#include <string_view>
#include <string>
#include <fstream>
#include <streambuf>
#include <chrono>

#include "parser.hpp"

int main(int, char**) {
  std::ifstream f { "/Users/zoe/Developer/thunder-source/thunder/src/file.swift" };
  std::string str { std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>() };
  
  std::string_view str_v { str };
  auto out = parse_function_inst(str_v).value();
  std::cout << out.name << " -> " << out.return_type.name << "() " << out.args.size() << std::endl;
}
