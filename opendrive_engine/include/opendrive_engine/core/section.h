#ifndef OPENDRIVE_ENGINE_CORE_SECTION_H_
#define OPENDRIVE_ENGINE_CORE_SECTION_H_

#include <string>
#include <vector>

#include "opendrive_engine/common/macros.h"
#include "opendrive_engine/core/id.h"
#include "opendrive_engine/core/lane.h"

namespace opendrive {
namespace core {

class Section {
  REGISTER_MEMBER_COMPLEX_TYPE(Id, id);
  REGISTER_MEMBER_COMPLEX_TYPE(Id, parent_id);
  REGISTER_MEMBER_BASIC_TYPE(double, start_position, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, end_position, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, length, 0);
  REGISTER_MEMBER_SHARED_PTR(Lane, center_lane);
  REGISTER_MEMBER_COMPLEX_TYPE(Lane::Ptrs, left_lanes);
  REGISTER_MEMBER_COMPLEX_TYPE(Lane::Ptrs, right_lanes);

 public:
  using Ptr = std::shared_ptr<Section>;
  using ConstPtr = std::shared_ptr<Section const>;
  using Ptrs = std::vector<Ptr>;
  using ConstPtrs = std::vector<ConstPtr>;
  Section() {}
};

}  // namespace core
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_CORE_SECTION_H_
