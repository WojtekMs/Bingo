#include "parser/JsonParser.hpp"

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <nlohmann/json.hpp>
#include <range/v3/algorithm/any_of.hpp>

namespace
{
bool anyAttributeDoesNotExist(const nlohmann::json& json,
                              const std::vector<std::string>& attributes);
}  // namespace

Config JsonParser::parseConfig(const std::string& data) const
{
    namespace nh = nlohmann;
    const std::vector<std::string> attributes{"board_upper_left_corner",
                                        "board_upper_right_corner",
                                        "line_pixel_width",
                                        "generate_bingos_count",
                                        "generate_bingos_directory",
                                        "original_bingo_board_file"};
    nh::json json = nh::json::parse(data);
    if (anyAttributeDoesNotExist(json, attributes)) {
        fmt::print("Some required attributes are missing");
        return {};
    }
    auto& upperLeft = json["board_upper_left_corner"];
    auto& upperRight = json["board_upper_right_corner"];
    return Config{
        .boardUpperLeftCorner{upperLeft["x"], upperLeft["y"]},
        .boardUpperRightCorner{upperRight["x"], upperRight["y"]},
        .linePixelWidth{json["line_pixel_width"]},
        .generateBingosCount{json["generate_bingos_count"]},
        .generateBingosDirectory{std::string{json["generate_bingos_directory"]}},
        .originalBingoBoardFile{std::string{json["original_bingo_board_file"]}}};
}

namespace
{
bool anyAttributeDoesNotExist(const nlohmann::json& json,
                              const std::vector<std::string>& attributes)
{
    return ranges::any_of(attributes, [&json](const auto& attribute) {
        return !json.contains(attribute);
    });
}
}  // namespace
