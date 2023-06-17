#pragma once

#include <string>
#include <vector>

#include "Config.hpp"

class IParser {
 public:
  [[nodiscard]] virtual Config parseConfig(const std::string& data) const = 0;
  virtual ~IParser() = default;
};
