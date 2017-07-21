#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

class json {
public:
  // Constructors
  json() {}

  // Overloaded Operators
  json& operator[](std::string key);  // overloaded index/subscript operator
  template<typename Type>
  json& operator=(Type rhs);          // overloaded assignment operator

  // Getters
  auto keys();                        // returns json keys at current level
  std::string json::value();          // returns value of json at current level    

  void print(int indent = 4, 
    bool comma_on_leaf = false,
    bool comma_on_bracket = false);   // pretty prints json data


private:
  std::map<std::string, json*> data;
};

// overloaded index/subscript operator
json& json::operator[](std::string key) {
  if (data.find(key) != data.end()) {
    return *data[key];
  }
  else {
    json * value = new json();
    data.insert(std::pair<std::string, json*>(key, value));
    return *value;
  }
}

// overloaded assignment operator.
// converts input data to string and stores in json
// TODO: check if conversion to string is possible/successful 
template<typename Type>
json& json::operator=(Type rhs) {
  std::ostringstream convert;
  convert << rhs;
  data.insert(std::pair<std::string, json*>(convert.str(), nullptr));
  return (*this);
}

// returns a vector of keys at the current level of the json
auto json::keys() {
  std::vector<std::string> result;
  for (std::map<std::string, json*>::iterator it = data.begin(); it != data.end(); ++it) {
    result.push_back(it->first);
  }
  return result;
}

// returns value of json at current level
std::string json::value() {
  std::string result = "";
  if (data.size() == 1) {
    std::map<std::string, json*>::iterator it = data.begin();
    result = it->first;
  }
  return result;
}

// pretty prints json data
void json::print(int indent, bool comma_on_leaf, bool comma_on_bracket) {
  std::string indent_str(indent - 4, ' ');
  bool leaf_node = false;

  for (auto& entry : data) {
    if (entry.second == nullptr) {   
      leaf_node = true;
      std::cout << '"' << entry.first << '"';
      if(comma_on_leaf)
        std::cout << ',';
    }
  }

  if (!leaf_node) {
    if (indent - 4 > 0)
      std::cout << std::endl;
    std::cout << indent_str << '{' << std::endl;
  }

  for (auto it = data.begin(); it != data.end(); ++it) {
    if (it->second != nullptr) {
      indent_str = std::string(indent, ' ');
      std::cout << indent_str << '"' << it->first << '"' << " : ";
      if (std::next(it, 1) != data.end()) {
        it->second->print(indent + 4, true, true);
      }
      else {
        it->second->print(indent + 4, false, false);
      }
      indent_str = std::string(indent - 4, ' ');
    }
    else {
      std::cout << std::endl;
    }
  }

  if (!leaf_node)
    std::cout << indent_str << "}";
  if (!leaf_node && comma_on_bracket)
    std::cout << ',';
  if (!leaf_node)
    std::cout << std::endl;
}