#pragma once

#include <map>
#include <memory>

struct DirNode {
  std::map<std::string, std::unique_ptr<DirNode>> children_;
};