#ifndef OPENDRIVE_ENGINE_CORE_HEADER_H_
#define OPENDRIVE_ENGINE_CORE_HEADER_H_

#include <string>
#include <vector>

#include "opendrive_engine/common/macros.h"

namespace opendrive {
namespace core {

class Header {
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, rev_major);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, rev_minor);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, name);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, version);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, date);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, vendor);
  REGISTER_MEMBER_BASIC_TYPE(double, north, 0.0);
  REGISTER_MEMBER_BASIC_TYPE(double, south, 0.0);
  REGISTER_MEMBER_BASIC_TYPE(double, west, 0.0);
  REGISTER_MEMBER_BASIC_TYPE(double, east, 0.0);

 public:
  using Ptr = std::shared_ptr<Header>;
  using ConstPtr = std::shared_ptr<Header const>;
  Header() {}
  ~Header() = default;
};

}  // namespace core
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_CORE_HEADER_H_
