#include <gtest/gtest.h>

#include "analysis/Result.hpp"
#include "analysis/analysis.hpp"

void expectPairEqual(const std::pair<std::string, int64_t>& expected, const std::string& first,
                     int64_t second) {
  const auto actual = std::make_pair(first, second);
  EXPECT_EQ(expected, actual);
}

TEST(DataAnalysisTest, GivenEmptyProjectVec_WhenGetRegionsWithMostProjects_ThenReturnEmptyVec) {
  constexpr int regionCount = 10;
  const auto& result = analysis::getRegionsWithMostProjects({}, regionCount);

  ASSERT_TRUE(result.data_.empty());
}

TEST(DataAnalysisTest,
     GivenProjectsVec_WhenGetOneRegionWithMostProjects_ThenReturnVecWithMaxProjectsRegion) {
  constexpr int regionCount = 1;
  const std::string expectedRegion{"Africa"};
  const int expectedRegionCount{2};
  const auto projects =
      std::vector<ProjectData>{{expectedRegion, 0}, {"Europe", 0}, {expectedRegion, 0}};
  const auto& result = analysis::getRegionsWithMostProjects(projects, regionCount);

  ASSERT_EQ(result.data_.size(), 1);
  expectPairEqual(result.data_.front(), expectedRegion, expectedRegionCount);
}

TEST(DataAnalysisTest,
     GivenInsufficientRegionsCount_WhenGetMultipleRegions_ThenReturnAllAvailableRegions) {
  constexpr int regionCount = 5;
  const std::string expectedRegion0{"Asia"};
  const int expectedRegionCount0{3};
  const std::string expectedRegion1{"Europe"};
  const int expectedRegionCount1{2};
  const std::string expectedRegion2{"Africa"};
  const int expectedRegionCount2{1};
  const auto projects =
      std::vector<ProjectData>{{expectedRegion0, 0}, {expectedRegion0, 0}, {expectedRegion0, 0},
                               {expectedRegion1, 0}, {expectedRegion1, 0}, {expectedRegion2, 0}};
  const auto& result = analysis::getRegionsWithMostProjects(projects, regionCount);

  ASSERT_EQ(result.data_.size(), 3);
  expectPairEqual(result.data_[0], expectedRegion0, expectedRegionCount0);
  expectPairEqual(result.data_[1], expectedRegion1, expectedRegionCount1);
  expectPairEqual(result.data_[2], expectedRegion2, expectedRegionCount2);
}

TEST(DataAnalysisTest,
     GivenInsufficientProjectsCount_WhenGetMultipleRegions_ThenReturnAllAvailableRegions) {
  constexpr int regionCount = 5;
  const std::string expectedRegion{"Asia"};
  const int expectedRegionCount{1};
  const auto projects = std::vector<ProjectData>{
      {expectedRegion, 0},
  };
  const auto& result = analysis::getRegionsWithMostProjects(projects, regionCount);

  ASSERT_EQ(result.data_.size(), 1);
  expectPairEqual(result.data_.front(), expectedRegion, expectedRegionCount);
}

TEST(DataAnalysisTest, GivenEmptyProjectVec_WhenGetRegionsWithMostInvestments_ThenReturnEmptyVec) {
  constexpr int regionCount = 10;
  const auto& result = analysis::getRegionsWithMostInvestments({}, regionCount);

  ASSERT_TRUE(result.data_.empty());
}

TEST(DataAnalysisTest,
     GivenProjectsVec_WhenGetOneRegionWithMostInvestments_ThenReturnVecWithMaxInvestmentsRegion) {
  constexpr int regionCount = 1;
  const std::string expectedRegion{"Asia"};
  const int expectedInvestments{10000};
  const auto projects = std::vector<ProjectData>{{expectedRegion, expectedInvestments / 2},
                                                 {"Europe", 0},
                                                 {expectedRegion, expectedInvestments / 2}};
  const auto& result = analysis::getRegionsWithMostInvestments(projects, regionCount);

  ASSERT_EQ(result.data_.size(), 1);
  expectPairEqual(result.data_.front(), expectedRegion, expectedInvestments);
}

TEST(
    DataAnalysisTest,
    GivenInsufficientRegionsCount_WhenGetMultipleRegionsWithMostInvestments_ThenReturnAllAvailableRegions) {
  constexpr int regionCount = 5;
  const std::string expectedRegion0{"Asia"};
  const int expectedRegionInvestment0{1200};
  const std::string expectedRegion1{"Europe"};
  const int expectedRegionInvestment1{600};
  const std::string expectedRegion2{"Africa"};
  const int expectedRegionInvestment2{300};
  const auto projects = std::vector<ProjectData>{{expectedRegion0, expectedRegionInvestment0 / 3},
                                                 {expectedRegion0, expectedRegionInvestment0 / 3},
                                                 {expectedRegion0, expectedRegionInvestment0 / 3},
                                                 {expectedRegion1, expectedRegionInvestment1 / 2},
                                                 {expectedRegion1, expectedRegionInvestment1 / 2},
                                                 {expectedRegion2, expectedRegionInvestment2}};
  const auto& result = analysis::getRegionsWithMostInvestments(projects, regionCount);

  ASSERT_EQ(result.data_.size(), 3);
  expectPairEqual(result.data_[0], expectedRegion0, expectedRegionInvestment0);
  expectPairEqual(result.data_[1], expectedRegion1, expectedRegionInvestment1);
  expectPairEqual(result.data_[2], expectedRegion2, expectedRegionInvestment2);
}
