#ifndef OPENDRIVE_ENGINE_CORE_MAP_H_
#define OPENDRIVE_ENGINE_CORE_MAP_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "opendrive_engine/common/macros.h"
#include "opendrive_engine/core/header.h"
#include "opendrive_engine/core/id.h"
#include "opendrive_engine/core/junction.h"
#include "opendrive_engine/core/lane.h"
#include "opendrive_engine/core/road.h"
#include "opendrive_engine/core/section.h"

namespace opendrive {
namespace core {

using LaneRoute = std::unordered_map<Id, Lane::Ptr>;
using ConstLaneRoute = std::unordered_map<Id, Lane::ConstPtr>;
using SectionRoute = std::unordered_map<Id, Section::Ptr>;
using ConstSectionRoute = std::unordered_map<Id, Section::ConstPtr>;
using RoadRoute = std::unordered_map<Id, Road::Ptr>;
using ConstRoadRoute = std::unordered_map<Id, Road::ConstPtr>;
using JunctionRoute = std::unordered_map<Id, Junction::Ptr>;
using ConstJunctionRoute = std::unordered_map<Id, Junction::ConstPtr>;

class Map {
  REGISTER_MEMBER_SHARED_PTR(Header, header);
  REGISTER_MEMBER_COMPLEX_TYPE(LaneRoute, lanes);
  REGISTER_MEMBER_COMPLEX_TYPE(SectionRoute, sections);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadRoute, roads);
  REGISTER_MEMBER_COMPLEX_TYPE(JunctionRoute, junctions);

 public:
  using Ptr = std::shared_ptr<Map>;
  using ConstPtr = std::shared_ptr<Map const>;
  Map() {}
};

}  // namespace core
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_CORE_MAP_H_
