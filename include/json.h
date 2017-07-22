#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <typeinfo>

class json {
public:
  // Constructors
  json();

  // Destructors
  ~json();

  // Overloaded Operators
  json& operator[](std::string key);  // overloaded index/subscript operator

  json& operator=(const char * rhs);  // assign const char array
  json& operator=(std::string rhs);   // assign string
  json& operator=(int rhs);           // assign integer
  json& operator=(double rhs);        // assign double
  json& operator=(bool rhs);          // assign boolean

  // Getters
  auto keys();                        // returns json keys at current level
  std::string json::value();          // returns value of json at current level    

  // Console and File I/O
  std::string to_string(int indent = 4, 
    bool comma_on_leaf = false, 
    bool comma_on_bracket = false);   // returns a string of the json for archiving
  void print();                       // pretty prints json object
  void write(std::string file_path);  // writes json to file at provided path

private:
  std::map<std::string, json*> object;
};

// default constructor
json::json() {}

// destructor
json::~json() {
  for (auto& pair : object) {
    if (pair.second != nullptr) {
      delete pair.second;
    }
  }
}

// overloaded index/subscript operator
json& json::operator[](std::string key) {
  if (object.find(key) != object.end()) {
    return *object[key];
  }
  else {
    json * value = new json();
    object.insert(std::pair<std::string, json*>(key, value));
    return *value;
  }
}

json& json::operator=(const char * rhs) {
  if (rhs != nullptr)
    object.insert(std::pair<std::string, json*>(std::string(rhs), nullptr));
  else
    object.insert(std::pair<std::string, json*>("null", nullptr));
  return (*this);
}

json& json::operator=(std::string rhs) {
  object.insert(std::pair<std::string, json*>(rhs, nullptr));
  return (*this);
}

// json value can be integer
json& json::operator=(int rhs) {
  std::ostringstream convert;
  convert << rhs;
  object.insert(std::pair<std::string, json*>(convert.str(), nullptr));
  return (*this);
}

// json value can be double
json& json::operator=(double rhs) {
  std::ostringstream convert;
  convert << rhs;
  object.insert(std::pair<std::string, json*>(convert.str(), nullptr));
  return (*this);
}

// json value can be boolean
json& json::operator=(bool rhs) {
    std::string bool_str = (rhs == true)? "true" : "false";
    object.insert(std::pair<std::string, json*>(bool_str, nullptr));
  return (*this);
}

// returns a vector of keys at the current level of the json
auto json::keys() {
  std::vector<std::string> result;
  for (std::map<std::string, json*>::iterator it = object.begin(); it != object.end(); ++it) {
    result.push_back(it->first);
  }
  return result;
}

// returns value of json at current level
std::string json::value() {
  std::string result = "";
  if (object.size() == 1) {
    std::map<std::string, json*>::iterator it = object.begin();
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

  for (auto& entry : object) {
    if (entry.second == nullptr) {
      leaf_node = true;
      if (entry.first == "true" || entry.first == "false")
        json_string += entry.first;
      else if (entry.first == "null")
        json_string += entry.first;
      else
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

  for (auto it = object.begin(); it != object.end(); ++it) {
    if (it->second != nullptr) {
      indent_str = std::string(indent, ' ');
      json_string += indent_str + '"' + it->first + '"' + " : ";
      if (std::next(it, 1) != object.end()) {
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

// pretty prints json object
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