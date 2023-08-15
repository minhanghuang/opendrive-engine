#ifndef OPENDRIVE_ENGINE_CORE_LANE_H_
#define OPENDRIVE_ENGINE_CORE_LANE_H_

#include <string>
#include <vector>

#include "opendrive_engine/common/macros.h"
#include "opendrive_engine/core/enums.h"
#include "opendrive_engine/core/geometry.h"
#include "opendrive_engine/core/id.h"

namespace opendrive {
namespace core {

class Curve {
 public:
  class Point : public Point4D {
    /*
     * e.g. 207_2_-2_9_1 (size: 5)
     * road id: 270
     * section id: 270_2
     * lane id: 207_2_-2 (0: reference line; minus: left lanes; plus: right
     * lanes)
     * point: left boundary point id: 9_1 center curve point id: 9_2
     *  right boundary point id: 9_3
     */
    REGISTER_MEMBER_COMPLEX_TYPE(Id, id);
    REGISTER_MEMBER_BASIC_TYPE(double, start_position, 0);

   public:
    Point() : start_position_(0), id_("") {}
    Point(double x, double y) : Point4D(x, y), start_position_(0), id_("") {}
    Point(double x, double y, double z)
        : Point4D(x, y, z), start_position_(0), id_("") {}
    Point(double x, double y, double z, double heading)
        : Point4D(x, y, z, heading), start_position_(0), id_("") {}
    Point(double x, double y, double z, double heading, double start_position)
        : Point4D(x, y, z, heading), start_position_(start_position), id_("") {}
    Point(double x, double y, double z, double heading, double start_position,
          const Id& id)
        : Point4D(x, y, z, heading), start_position_(start_position), id_(id) {}
  };
  using Points = std::vector<Point>;
  using Line = std::vector<Point>;
  REGISTER_MEMBER_COMPLEX_TYPE(Line, pts);
  REGISTER_MEMBER_BASIC_TYPE(double, length, 0);
};

class LaneBoundaryAttr {
  REGISTER_MEMBER_BASIC_TYPE(double, start_position, 0);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadMarkType, boundary_type);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadMarkColor, boundary_color);

 public:
  LaneBoundaryAttr()
      : start_position_(0),
        boundary_type_(RoadMarkType::kNone),
        boundary_color_(RoadMarkColor::kStandard) {}
};
using LaneBoundaryAttrs = std::vector<LaneBoundaryAttr>;

class LaneBoundary {
  REGISTER_MEMBER_COMPLEX_TYPE(Curve, curve);
  REGISTER_MEMBER_COMPLEX_TYPE(LaneBoundaryAttrs, attributes);

 public:
  LaneBoundary() {}
};

class SpeedLimit {
  REGISTER_MEMBER_BASIC_TYPE(double, start_position, 0);
  // meters per second
  REGISTER_MEMBER_BASIC_TYPE(double, value, 0);

 public:
  SpeedLimit() {}
};
using SpeedLimits = std::vector<SpeedLimit>;

class Geometry {
  REGISTER_MEMBER_COMPLEX_TYPE(opendrive::GeometryType, type);
  /*
   * 参考线车道 中线
   */
  REGISTER_MEMBER_COMPLEX_TYPE(Curve::Point, point);

 public:
  using Type = opendrive::GeometryType;
  Geometry() : type_(Type::kLine) {}
};
using Geometrys = std::vector<Geometry>;

class Lane {
  REGISTER_MEMBER_COMPLEX_TYPE(Id, id);
  REGISTER_MEMBER_COMPLEX_TYPE(Id, parent_id);
  REGISTER_MEMBER_COMPLEX_TYPE(Ids, predecessor_ids);
  REGISTER_MEMBER_COMPLEX_TYPE(Ids, successor_ids);
  REGISTER_MEMBER_COMPLEX_TYPE(Ids, left_neighbor_lane_ids);
  REGISTER_MEMBER_COMPLEX_TYPE(Ids, right_neighbor_lane_ids);
  REGISTER_MEMBER_COMPLEX_TYPE(Curve, central_curve);
  REGISTER_MEMBER_COMPLEX_TYPE(LaneBoundary, left_boundary);
  REGISTER_MEMBER_COMPLEX_TYPE(LaneBoundary, right_boundary);
  REGISTER_MEMBER_COMPLEX_TYPE(Geometrys, geometrys);

 public:
  using Ptr = std::shared_ptr<Lane>;
  using ConstPtr = std::shared_ptr<Lane const>;
  using Ptrs = std::vector<Ptr>;
  using ConstPtrs = std::vector<ConstPtr>;
  Lane() {}
};

}  // namespace core
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_CORE_LANE_H_
