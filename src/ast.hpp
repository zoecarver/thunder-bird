
#include <string_view>
#include <vector>

struct type_info {
  enum info {
    is_const = 0x1
  };
  
  char value = 0;
  
  void addConst() {
    value &= info::is_const;
  }
  
  void removeConst() {
    value &= ~info::is_const;
  }
};

struct node
{
  std::string_view src;
};

struct type : node {
  std::string_view name;
  type_info info;
};

template<class T>
struct literal_inst : node
{
  T value;
};

using integer_literal_inst = literal_inst<int>;
using floating_literal_inst = literal_inst<double>;

struct argument_inst : node
{
  std::string_view name;
  std::string_view label;
  type ty;
};

struct function_inst : node
{
  std::string_view name;
  type return_type;
  std::vector<argument_inst> args;
};

struct variable_inst : node
{
  std::string_view name;
  type ty;
  node value;
};
