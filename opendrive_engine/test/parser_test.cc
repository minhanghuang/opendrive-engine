#include <gtest/gtest.h>
#include <tinyxml2.h>

#include <cassert>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "opendrive_engine/common/params.h"
#include "opendrive_engine/engine.h"

class TestEmpty : public testing::Test {
 public:
  static void SetUpTestCase();
  static void TearDownTestCase();
  void SetUp() override;
  void TearDown() override;
  static opendrive::engine::Engine* GetEngine() {
    static opendrive::engine::Engine* instance = nullptr;
    if (!instance) {
      static std::once_flag flag;
      std::call_once(flag, [&] {
        instance = new (std::nothrow) opendrive::engine::Engine();
        opendrive::common::Singleton::Instance<opendrive::engine::Params>()
            ->opendrive_file_path = MAP_FILE;
      });
    }
    return instance;
  }
  static std::string MAP_FILE;
};

std::string TestEmpty::MAP_FILE =
    "/opt/xodr/share/xodr/carla-simulator/Town01.xodr";
void TestEmpty::SetUpTestCase() {}
void TestEmpty::TearDownTestCase() {}
void TestEmpty::TearDown() {}
void TestEmpty::SetUp() {}

TEST_F(TestEmpty, TestEngineInit) {
  auto engine = TestEmpty::GetEngine();
  ASSERT_TRUE(nullptr != engine);
  auto status = engine->Init();
  ASSERT_TRUE(status.ok());
}

TEST_F(TestEmpty, TestHeaderXmlParser) {
  auto engine = TestEmpty::GetEngine();
  ASSERT_TRUE(nullptr != engine);
  auto header = engine->GetHeader();
  ASSERT_TRUE(nullptr != header);
  ASSERT_EQ("1", header->rev_major());
  ASSERT_EQ("4", header->rev_minor());
  ASSERT_EQ("1", header->version());
  ASSERT_EQ("", header->name());
  ASSERT_EQ("2019-04-06T10:38:28", header->date());
  ASSERT_EQ("VectorZero", header->vendor());
  ASSERT_EQ(2.8349990809409476e+1, header->north());
  ASSERT_EQ(-3.5690998535156251e+2, header->south());
  ASSERT_EQ(4.2268105762411665e+2, header->east());
  ASSERT_EQ(-2.8359911988457576e+1, header->west());
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
