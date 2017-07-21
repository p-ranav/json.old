#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

class json {
public:
  json() {}

  json& operator[](std::string key) {
    if (data.find(key) != data.end()) {
      return *data[key];
    }
    else {
      json * value = new json();
      data.insert(std::pair<std::string, json*>(key, value));
      return *value;
    }
  }

  template<typename Type>
  json& operator=(Type rhs) {
    std::string result;
    std::ostringstream convert;
    convert << rhs;
    data.insert(std::pair<std::string, json*>(convert.str(), nullptr));
    return (*this);
  }

  auto keys() {
    std::vector<std::string> result;
    for (std::map<std::string, json*>::iterator it = data.begin(); it != data.end(); ++it) {
      result.push_back(it->first);
    }
    return result;
  }

  std::string value() {
    std::string result = "";
    if (data.size() == 1) {
      std::map<std::string, json*>::iterator it = data.begin();
      result = it->first;
    }
    return result;
  }

  void print(size_t indent_by = 0, bool leaf = false, bool last_leaf = false) {
    std::string indent = "";
    size_t key_indent = indent_by;
    while (key_indent > 0 && !leaf) {
      indent += " ";
      key_indent--;
    }
    if (!leaf)
      std::cout << indent << "{" << std::endl;
    auto keys = this->keys();
    for (size_t k = 0; k < keys.size(); k++) {
      if (data[keys[k]] != nullptr) {
        std::string key_indent = indent;
        for (size_t i = indent_by; i < indent_by + 4; i++) {
          key_indent += " ";
        }
        std::cout << key_indent << keys[k] << " : ";
        size_t nested_indent_by = indent_by + 4;
        // detect if leaf or not
        bool leaf_node = false;
        if (data[keys[k]]->keys().size() == 1) {
          std::string leaf_key = data[keys[k]]->keys()[0];
          if (data[keys[k]]->data[leaf_key] == nullptr) {
            leaf_node = true;
          }
          else {
            std::cout << std::endl;
          }
        }
        else {
          std::cout << std::endl;
        }
        bool last_leaf_node = false;
        if (leaf_node && k + 1 == keys.size()) {
          last_leaf_node = true;
        }
        data[keys[k]]->print(nested_indent_by, leaf_node, last_leaf_node);
      }
      else {
        if (!leaf) {
          for (size_t i = indent_by; i < indent_by + 4; i++) {
            indent += " ";
          }
        }
        std::cout << indent << '"' << keys[k] << '"';
        if (!last_leaf) {
          std::cout << ",";
        }
        std::cout << std::endl;
      }
    }
    indent = "";
    for (size_t i = 0; i < indent_by; i++) {
      indent += " ";
    }
    if (!leaf)
      std::cout << indent << "}" << std::endl;
  }

private:
  std::map<std::string, json*> data;
};