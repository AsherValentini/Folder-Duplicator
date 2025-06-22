#pragma once
#include <sstream>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>
#include "dir_node.hpp"

class DirDuplicator {

public:
  // default constructor
  DirDuplicator() {
    // init the root
    root = std::make_unique<DirNode>();
  }

  // add a directory
  void add(std::string& word) {
    DirNode* node = root.get();

    for (auto& dir : splitPath(word)) {
      if (node->children_.count(dir)) {
        node = node->children_[dir].get();
      } else {
        node->children_[dir] = std::make_unique<DirNode>();
        node = node->children_[dir].get();
      }
    }
  }

  void removeDuplicates() {
    std::unordered_map<std::string, int> freq;
    postOrder(root.get(), freq);
  }

  // print the current directory
  void print() {
    DirNode* node = root.get();
    std::string indent = "";
    printDFS(indent, node);
  }

private:
  std::unique_ptr<DirNode> root;
  std::unordered_map<std::string, int> seen_;

  // process the path
  std::vector<std::string> splitPath(const std::string& path) {
    std::stringstream ss(path);
    std::string token;
    std::vector<std::string> tokens;

    while (getline(ss, token, '/')) {
      tokens.push_back(token);
    }

    return tokens;
  }

  // recursive print helper
  void printDFS(std::string indent, DirNode* node) {
    if (!node)
      return;
    for (const auto& [name, child] : node->children_) {
      std::cout << indent << name << "\n";
      printDFS(indent + "  ", child.get());
    }
  }

  std::string postOrder(DirNode* node, std::unordered_map<std::string, int>& freq) {
    if (!node)
      return "";

    std::vector<std::string> serials;
    for (auto& [name, child] : node->children_) {
      std::string child_serial = postOrder(child.get(), freq);
      serials.push_back(name + "(" + child_serial + ")");
    }

    std::sort(serials.begin(), serials.end()); // normalize order
    std::string subtree_serial = join(serials, ",");

    freq[subtree_serial]++;
    if (freq[subtree_serial] > 1) {
      node->children_.clear(); // deduplicate
    }

    return subtree_serial;
  }
  std::string join(const std::vector<std::string>& tokens, const std::string& delim) {
    std::ostringstream oss;
    for (size_t i = 0; i < tokens.size(); ++i) {
      oss << tokens[i];
      if (i + 1 < tokens.size())
        oss << delim;
    }
    return oss.str();
  }
};