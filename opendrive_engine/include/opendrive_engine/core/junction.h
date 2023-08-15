#ifndef OPENDRIVE_ENGINE_CORE_JUNCTION_H_
#define OPENDRIVE_ENGINE_CORE_JUNCTION_H_

#include <memory>
#include <string>
#include <vector>

#include "opendrive_engine/common/macros.h"
#include "opendrive_engine/core/enums.h"
#include "opendrive_engine/core/id.h"

namespace opendrive {
namespace core {

class Junction {
  REGISTER_MEMBER_COMPLEX_TYPE(Id, id);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, name);
  REGISTER_MEMBER_COMPLEX_TYPE(JunctionType, type);

 public:
  using Ptr = std::shared_ptr<Junction>;
  using ConstPtr = std::shared_ptr<Junction const>;
  Junction() : type_(JunctionType::kDefault) {}
};

}  // namespace core
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_CORE_JUNCTION_H_
