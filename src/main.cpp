#include <iostream>

#include "dir_duplicator.hpp"

int main() {
  std::vector<std::string> paths{{"a/x/y"}, {"c/x/y"}};
  auto dir = std::make_unique<DirDuplicator>();
  for (auto& s : paths) {

    dir->add(s);
  }

  dir->print();
  dir->removeDuplicates();
  dir->print();
  return 0;
}

