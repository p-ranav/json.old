#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>

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

  // Console and File I/O
  std::string to_string(int indent = 4, 
    bool comma_on_leaf = false, 
    bool comma_on_bracket = false);   // returns a string of the json for archiving
  void print();                       // pretty prints json data
  void write(std::string file_path);  // writes json to file at provided path

private:
  std::map<std::string, json*> data;
  //std::string json_string;
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

// returns a string of the json for archiving
std::string json::to_string(int indent, 
  bool comma_on_leaf, bool comma_on_bracket) {
  std::string json_string = "";
  std::string indent_str(indent - 4, ' ');
  bool leaf_node = false;

  for (auto& entry : data) {
    if (entry.second == nullptr) {
      leaf_node = true;
      json_string += '"' + entry.first + '"';
      if (comma_on_leaf)
        json_string += ',';
    }
  }

  if (!leaf_node) {
    if (indent - 4 > 0)
      json_string += '\n';
    json_string += indent_str + "{\n";
  }

  for (auto it = data.begin(); it != data.end(); ++it) {
    if (it->second != nullptr) {
      indent_str = std::string(indent, ' ');
      json_string += indent_str + '"' + it->first + '"' + " : ";
      if (std::next(it, 1) != data.end()) {
        json_string += it->second->to_string(indent + 4, true, true);
      }
      else {
        json_string += it->second->to_string(indent + 4, false, false);
      }
      indent_str = std::string(indent - 4, ' ');
    }
    else {
      json_string += '\n';
    }
  }

  if (!leaf_node)
    json_string += indent_str + "}";
  if (!leaf_node && comma_on_bracket)
    json_string += ',';
  if (!leaf_node)
    json_string += '\n';
  return json_string;
}

// pretty prints json data
void json::print() {
  std::cout << to_string() << std::endl;
}

// writes json to file at provided path
void json::write(std::string file_path) {
  std::ofstream output(file_path);
  if (output.is_open()) {
    output << to_string();
    output.close();
  }
  else 
    std::cout << "Unable to open file: " << file_path;
}