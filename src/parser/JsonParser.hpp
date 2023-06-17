#pragma once

#include <string>
#include <vector>

#include "parser/IParser.hpp"

class JsonParser : public IParser {
 public:
  [[nodiscard]] Config parseConfig(const std::string& data) const override;
};
