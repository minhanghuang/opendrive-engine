#ifndef OPENDRIVE_ENGINE_CORE_GEOMETRY_H_
#define OPENDRIVE_ENGINE_CORE_GEOMETRY_H_

#include <string>

#include "opendrive_engine/common/macros.h"

namespace opendrive {
namespace core {

class Point {
  REGISTER_MEMBER_BASIC_TYPE(double, x, 0.0);
  REGISTER_MEMBER_BASIC_TYPE(double, y, 0.0);
  REGISTER_MEMBER_BASIC_TYPE(double, z, 0.0);

 public:
  Point() = default;
  Point(double x, double y) : x_(x), y_(y) {}
  Point(double x, double y, double z) : x_(x), y_(y), z_(z) {}
};
using Point3D = Point;

class Point4D : public Point {
  REGISTER_MEMBER_BASIC_TYPE(double, heading, 0.0);

 public:
  Point4D() = default;
  Point4D(double x, double y) : Point(x, y) {}
  Point4D(double x, double y, double z) : Point(x, y, z) {}
  Point4D(double x, double y, double z, double heading)
      : Point(x, y, z), heading_(heading) {}
};

}  // namespace core
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_CORE_GEOMETRY_H_
