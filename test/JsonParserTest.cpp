#include <gtest/gtest.h>

#include "JsonParser.hpp"
#include "test_utils.hpp"

void expectProjectDataEq(const ProjectData& lhs, const ProjectData& rhs) {
  EXPECT_EQ(lhs.region_, rhs.region_);
  EXPECT_EQ(lhs.totalCosts_, rhs.totalCosts_);
}
class JsonParserTest : public ::testing::Test {
 protected:
  JsonParser parser{};
};

TEST_F(JsonParserTest, GivenInvalidJsonString_WhenParseProjects_ThenThrowException) {
  const auto& data = "<h>Hello</h>";
  ASSERT_ANY_THROW(parser.parseProjects(data));
}

TEST_F(JsonParserTest, GivenEmptyString_WhenParseProjects_ThenReturnEmptyVector) {
  const std::string data{};

  const auto vec = parser.parseProjects(data);

  EXPECT_TRUE(vec.empty());
}

TEST_F(JsonParserTest, Given1ProjectInJsonString_WhenParseProjects_ThenReturnVectorWith1Element) {
  const auto& data = readTestData("first.json");
  const ProjectData expectedData = {.region_ = "Africa", .totalCosts_ = 130000000};

  const auto vec = parser.parseProjects(data);

  ASSERT_EQ(vec.size(), 1);
  expectProjectDataEq(vec.front(), expectedData);
}

TEST_F(JsonParserTest,
       GivenMultipleProjectsInJsonString_WhenParseProjects_ThenReturnVectorWithMultipleElements) {
  const auto& data = readTestData("multiple.json");
  const ProjectData expectedData0 = {.region_ = "Middle East and North Africa", .totalCosts_ = 0};
  const ProjectData expectedData1 = {.region_ = "East Asia and Pacific", .totalCosts_ = 6060000};
  const ProjectData expectedData2 = {.region_ = "Middle East and North Africa", .totalCosts_ = 0};

  const auto vec = parser.parseProjects(data);

  ASSERT_EQ(vec.size(), 3);
  expectProjectDataEq(vec[0], expectedData0);
  expectProjectDataEq(vec[1], expectedData1);
  expectProjectDataEq(vec[2], expectedData2);
}

TEST_F(JsonParserTest,
       GivenInvalidProjectDataInJsonString_WhenParseProjects_ThenSkipInvalidProject) {
  const auto& data = "{\"name\": \"bob\"}\n{\"regionname\":\"Africa\",\"totalamt\":100}";
  const ProjectData expectedData = {.region_ = "Africa", .totalCosts_ = 100};

  const auto vec = parser.parseProjects(data);

  ASSERT_EQ(vec.size(), 1);
  expectProjectDataEq(vec.front(), expectedData);
}
