#ifndef OPENDRIVE_ENGINE_CORE_ROAD_H_
#define OPENDRIVE_ENGINE_CORE_ROAD_H_

#include <string>
#include <vector>

#include "opendrive_engine/common/macros.h"
#include "opendrive_engine/core/id.h"
#include "opendrive_engine/core/lane.h"
#include "opendrive_engine/core/section.h"

namespace opendrive {
namespace core {

class RoadInfo {
  REGISTER_MEMBER_BASIC_TYPE(double, start_position, 0);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadType, type);
  // meters per second
  REGISTER_MEMBER_BASIC_TYPE(double, speed_limit, 0);

 public:
  RoadInfo() : type_(RoadType::kTown) {}
};
using RoadInfos = std::vector<RoadInfo>;

class Road {
  REGISTER_MEMBER_COMPLEX_TYPE(Id, id);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, name);
  REGISTER_MEMBER_COMPLEX_TYPE(Id, junction_id);
  REGISTER_MEMBER_BASIC_TYPE(double, length, 0);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadRule, rule);
  REGISTER_MEMBER_COMPLEX_TYPE(Section::Ptrs, sections);
  REGISTER_MEMBER_COMPLEX_TYPE(Ids, predecessor_ids);
  REGISTER_MEMBER_COMPLEX_TYPE(Ids, successor_ids);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadInfos, info);

 public:
  using Ptr = std::shared_ptr<Road>;
  using ConstPtr = std::shared_ptr<Road const>;
  using Ptrs = std::vector<Ptr>;
  using ConstPtrs = std::vector<ConstPtr>;
  Road() : rule_(RoadRule::kRht) {}
};

}  // namespace core
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_CORE_ROAD_H_
