#include <gtest/gtest.h>
#include <opendrive-engine/common/param.h>
#include <opendrive-engine/engine.h>
#include <tinyxml2.h>

#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class TestEmpty : public testing::Test {
 public:
  static void SetUpTestCase();     // 在第一个case之前执行
  static void TearDownTestCase();  // 在最后一个case之后执行
  void SetUp() override;           // 在每个case之前执行
  void TearDown() override;        // 在每个case之后执行
};

void TestEmpty::SetUpTestCase() {}
void TestEmpty::TearDownTestCase() {}
void TestEmpty::TearDown() {}
void TestEmpty::SetUp() {}

TEST_F(TestEmpty, TestInit) {
  const std::string map_file =
      "/opt/xodr/share/xodr/carla-simulator/Town01.xodr";
  opendrive::engine::common::Param param;
  param.map_file = map_file;
  opendrive::engine::Engine engine;
  engine.Init(param);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}