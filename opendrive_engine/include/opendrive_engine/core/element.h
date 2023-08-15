#ifndef OPENDRIVE_ENGINE_CORE_ELEMENT_H_
#define OPENDRIVE_ENGINE_CORE_ELEMENT_H_

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "opendrive_engine/common/common.hpp"
#include "opendrive_engine/common/macros.h"
#include "opendrive_engine/common/spiral/odrSpiral.h"
#include "opendrive_engine/core/enums.h"

namespace opendrive {
namespace element {

using Id = int;
using Idx = Id;
using Ids = std::vector<Id>;
using IdStr = std::string;
using Name = std::string;

class Point {
  REGISTER_MEMBER_BASIC_TYPE(double, x, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, y, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, z, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, heading, 0);

 public:
  Point() : x_(0), y_(0), z_(0), heading_(0) {}
  Point(double x, double y, double z) : x_(x), y_(y), z_(z), heading_(0) {}
  Point(double x, double y, double z, double heading)
      : x_(x), y_(y), z_(z), heading_(heading) {}
};

class Header {
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, rev_major);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, rev_minor);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, version);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, name);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, date);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, vendor);
  REGISTER_MEMBER_BASIC_TYPE(double, north, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, south, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, west, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, east, 0);

 public:
  Header() : north_(0), south_(0), west_(0), east_(0) {}
};

class Geometry {
  REGISTER_MEMBER_BASIC_TYPE(double, s, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, x, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, y, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, hdg, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, length, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, sin_hdg, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, cos_hdg, 0);
  REGISTER_MEMBER_COMPLEX_TYPE(GeometryType, type);

 public:
  using Ptr = std::shared_ptr<Geometry>;
  using ConstPtr = std::shared_ptr<Geometry const>;
  using Ptrs = std::vector<Ptr>;
  using ConstPtrs = std::vector<ConstPtr>;
  Geometry(double _s, double _x, double _y, double _hdg, double _length,
           GeometryType _type)
      : s_(_s),
        x_(_x),
        y_(_y),
        hdg_(_hdg),
        length_(_length),
        type_(_type),
        sin_hdg_(std::sin(_hdg)),
        cos_hdg_(std::cos(_hdg)) {}
  virtual ~Geometry() = default;
  virtual Point GetPoint(double ref_line_ds) const = 0;
};

class GeometryLine final : public Geometry {
 public:
  GeometryLine(double s, double x, double y, double hdg, double length,
               GeometryType type)
      : Geometry(s, x, y, hdg, length, type) {}
  virtual Point GetPoint(double road_ds) const override {
    const double ref_line_ds = road_ds - s();
    const double xd = x() + (cos_hdg() * ref_line_ds);
    const double yd = y() + (sin_hdg() * ref_line_ds);
    return Point{xd, yd, 0, hdg()};
  }
};

class GeometryArc final : public Geometry {
  REGISTER_MEMBER_BASIC_TYPE(double, curvature, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, radius, 0);

 public:
  GeometryArc(double s, double x, double y, double hdg, double length,
              GeometryType type, double curvature)
      : Geometry(s, x, y, hdg, length, type),
        curvature_(curvature),
        radius_(1.0 / curvature) {}
  virtual Point GetPoint(double road_ds) const override {
    const double ref_line_ds = road_ds - s();
    const double angle_at_s = ref_line_ds * curvature_ - M_PI / 2;
    const double xd =
        radius_ * (std::cos(hdg() + angle_at_s) - sin_hdg()) + x();
    const double yd =
        radius_ * (std::sin(hdg() + angle_at_s) + cos_hdg()) + y();
    const double tangent = hdg() + ref_line_ds * curvature_;
    return Point{xd, yd, 0, tangent};
  }
};

class GeometrySpiral final : public Geometry {
  REGISTER_MEMBER_BASIC_TYPE(double, curve_start, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, curve_end, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, curve_dot, 0);

 public:
  GeometrySpiral(double s, double x, double y, double hdg, double length,
                 GeometryType type, double curve_start, double curve_end)
      : Geometry(s, x, y, hdg, length, type),
        curve_start_(curve_start),
        curve_end_(curve_end),
        curve_dot_((curve_end - curve_start) / (length)) {}

  virtual Point GetPoint(double road_ds) const override {
    const double ref_line_ds = road_ds - s();
    const double s1 = curve_start_ / curve_dot_ + ref_line_ds;
    double x1;
    double y1;
    double t1;
    odrSpiral(s1, curve_dot_, &x1, &y1, &t1);

    const double s0 = curve_start_ / curve_dot_;
    double x0;
    double y0;
    double t0;
    odrSpiral(s1, curve_dot_, &x0, &y0, &t0);

    x1 -= x0;
    y1 -= y0;
    t1 -= t0;
    const double angle = hdg() - t0;
    const double cos_a = std::cos(angle);
    const double sin_a = std::sin(angle);
    const double xd = x() + x1 * cos_a - y1 * sin_a;
    const double yd = y() + y1 * cos_a + x1 * sin_a;
    const double tangent = hdg() + t1;
    return Point{xd, yd, 0, tangent};
  }
};

class GeometryPoly3 final : public Geometry {
  REGISTER_MEMBER_BASIC_TYPE(double, a, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, b, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, c, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, d, 0);

 public:
  GeometryPoly3(double s, double x, double y, double hdg, double length,
                GeometryType type, double a, double b, double c, double d)
      : Geometry(s, x, y, hdg, length, type), a_(a), b_(b), c_(c), d_(d) {}

  virtual Point GetPoint(double road_ds) const override {
    const double ref_line_ds = road_ds - s();
    const double u = ref_line_ds;
    const double v = a_ + b_ * u + c_ * std::pow(u, 2) + d_ * std::pow(u, 3);
    const double x1 = u * cos_hdg() - v * sin_hdg();
    const double y1 = u * sin_hdg() + v * cos_hdg();
    const double tangent_v = b_ + 2.0 * c_ * u + 3.0 * d_ * std::pow(u, 2);
    const double theta = std::atan2(tangent_v, 1.0);
    const double xd = x() + x1;
    const double yd = y() + y1;
    const double tangent = hdg() + theta;
    return Point{xd, yd, 0, tangent};
  }
};

class GeometryParamPoly3 final : public Geometry {
 public:
  enum class PRange : std::uint8_t {
    UNKNOWN = 0,
    ARCLENGTH = 1,
    NORMALIZED = 2
  };
  REGISTER_MEMBER_COMPLEX_TYPE(PRange, p_range);
  REGISTER_MEMBER_BASIC_TYPE(double, au, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, bu, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, cu, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, du, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, av, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, bv, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, cv, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, dv, 0);

 public:
  GeometryParamPoly3(double s, double x, double y, double hdg, double length,
                     GeometryType type, double au, double bu, double cu,
                     double du, double av, double bv, double cv, double dv,
                     PRange p_range)
      : Geometry(s, x, y, hdg, length, type),
        au_(au),
        bu_(bu),
        cu_(cu),
        du_(du),
        av_(av),
        bv_(bv),
        cv_(cv),
        dv_(dv),
        p_range_(p_range) {}
  virtual Point GetPoint(double road_ds) const override {
    const double ref_line_ds = road_ds - s();
    double p = ref_line_ds;
    if (PRange::NORMALIZED == p_range_) {
      p = std::min(1.0, ref_line_ds / length());
    }
    const double u =
        au_ + bu_ * p + cu_ * std::pow(p, 2) + du_ * std::pow(p, 3);
    const double v =
        av_ + bv_ * p + cv_ * std::pow(p, 2) + dv_ * std::pow(p, 3);
    const double x1 = u * cos_hdg() - v * sin_hdg();
    const double y1 = u * sin_hdg() + v * cos_hdg();
    const double tangent_u = bu_ + 2 * cu_ * p + 3 * du_ * std::pow(p, 2);
    const double tangent_v = bv_ + 2 * cv_ * p + 3 * dv_ * std::pow(p, 2);
    const double theta = std::atan2(tangent_v, tangent_u);
    const double xd = x() + x1;
    const double yd = y() + y1;
    const double tangent = hdg() + theta;
    return Point{xd, yd, 0, tangent};
  }
};

class LaneAttribute {
  REGISTER_MEMBER_BASIC_TYPE(Id, id, std::numeric_limits<Id>::max());
  REGISTER_MEMBER_COMPLEX_TYPE(LaneType, type);
  REGISTER_MEMBER_COMPLEX_TYPE(Boolean, level);

 public:
  LaneAttribute()
      : id_(std::numeric_limits<Id>::max()),
        type_(LaneType::kDriving),
        level_(Boolean::kUnknown) {}
};

class OffsetPoly3 {
  // f(s) = a + b*s + c*s*s + d*s*s*s
  REGISTER_MEMBER_BASIC_TYPE(double, s, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, a, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, b, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, c, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, d, 0);

 public:
  OffsetPoly3() : s_(0), a_(0), b_(0), c_(0), d_(0) {}
  bool operator<(const OffsetPoly3& obj) const { return this->s_ > obj.s_; }
  virtual double GetOffsetValue(double road_ds) const final {
    const double ds = road_ds - s_;
    return a_ + b_ * ds + c_ * std::pow(ds, 2) + d_ * std::pow(ds, 3);
  }
};

class RoadMark {
  REGISTER_MEMBER_BASIC_TYPE(double, s, 0);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadMarkType, type);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadMarkColor, color);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadMarkWeight, weight);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadMarkLaneChange, lane_change);
  REGISTER_MEMBER_BASIC_TYPE(double, width, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, height, 0);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, material);

 public:
  RoadMark()
      : s_(0),
        type_(RoadMarkType::kNone),
        color_(RoadMarkColor::kStandard),
        weight_(RoadMarkWeight::kUnknown),
        lane_change_(RoadMarkLaneChange::kUnknown),
        width_(0),
        height_(0),
        material_("standard") {}
};
using RoadMarks = std::vector<RoadMark>;

class LaneWidth : public OffsetPoly3 {};
using LaneWidths = std::vector<LaneWidth>;

class LaneBorder : public OffsetPoly3 {};
using LaneBorders = std::vector<LaneBorder>;

class LaneLink {
  REGISTER_MEMBER_COMPLEX_TYPE(Ids, predecessors);
  REGISTER_MEMBER_COMPLEX_TYPE(Ids, successors);

 public:
  LaneLink() {}
};
using LaneLinks = std::vector<LaneLink>;

class LaneSpeed {
  REGISTER_MEMBER_BASIC_TYPE(double, s, 0);
  REGISTER_MEMBER_BASIC_TYPE(float, max, 0);
  REGISTER_MEMBER_COMPLEX_TYPE(SpeedUnit, unit);

 public:
  LaneSpeed() : s_(0), max_(0), unit_(SpeedUnit::kMs) {}
};
using LaneSpeeds = std::vector<LaneSpeed>;

class Lane {
  REGISTER_MEMBER_COMPLEX_TYPE(LaneAttribute, attribute);
  REGISTER_MEMBER_COMPLEX_TYPE(LaneLink, link);
  REGISTER_MEMBER_COMPLEX_TYPE(LaneWidths, widths);
  REGISTER_MEMBER_COMPLEX_TYPE(LaneBorders, borders);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadMarks, road_marks);
  REGISTER_MEMBER_COMPLEX_TYPE(LaneSpeeds, max_speeds);

 public:
  Lane() {}
  double GetLaneWidth(double road_ds) const {
    // width >> border
    if (road_ds < 0) {
      return GetLaneWidth(0.);
    }
    if (widths_.empty()) {
      if (borders_.empty()) {
        return 0.;
      }
      /// border
      int border_index = common::GetGtValuePoloy3(borders_, road_ds);
      if (border_index < 0) {
        return 0.;
      }
      auto border = widths_.at(border_index);
      return border.GetOffsetValue(road_ds);
    } else {
      /// width
      int width_index = common::GetGtValuePoloy3(widths_, road_ds);
      if (width_index < 0) {
        return 0.;
      }
      auto width = widths_.at(width_index);
      return width.GetOffsetValue(road_ds);
    }
    return 0.;
  }
};

class LanesInfo {
  REGISTER_MEMBER_COMPLEX_TYPE(std::vector<Lane>, lanes);

 public:
  LanesInfo() {}
};

class LaneOffset : public OffsetPoly3 {};
using LaneOffsets = std::vector<LaneOffset>;

class LaneSection {
  REGISTER_MEMBER_BASIC_TYPE(Id, id, -1);
  REGISTER_MEMBER_BASIC_TYPE(double, start_position, 0);
  REGISTER_MEMBER_BASIC_TYPE(double, end_position, 0);
  REGISTER_MEMBER_COMPLEX_TYPE(LanesInfo, left);
  REGISTER_MEMBER_COMPLEX_TYPE(LanesInfo, center);
  REGISTER_MEMBER_COMPLEX_TYPE(LanesInfo, right);

 public:
  LaneSection() : id_(-1), start_position_(0), end_position_(0) {}
};
using LaneSections = std::vector<LaneSection>;

class Lanes {
  REGISTER_MEMBER_COMPLEX_TYPE(LaneOffsets, lane_offsets);
  REGISTER_MEMBER_COMPLEX_TYPE(LaneSections, lane_sections);

 public:
  Lanes() {}
};

class RoadAttribute {
  REGISTER_MEMBER_COMPLEX_TYPE(Name, name);
  REGISTER_MEMBER_BASIC_TYPE(Id, id, -1);  // [>=0]
  REGISTER_MEMBER_BASIC_TYPE(Id, junction_id,
                             -1);  // -1: Road; other: junction road
  REGISTER_MEMBER_BASIC_TYPE(double, length, 0);
  REGISTER_MEMBER_COMPLEX_TYPE(
      RoadRule, rule);  // RHT=right-hand traffic, LHT=left-hand traffic. When
                        // this attribute is missing, RHT is assumed

 public:
  RoadAttribute()
      : name_(""),
        id_(-1),
        junction_id_(-1),
        length_(0),
        rule_(RoadRule::kRht) {}
};

class RoadLinkInfo {
  REGISTER_MEMBER_BASIC_TYPE(Id, id, -1);  // [>=0]
  REGISTER_MEMBER_BASIC_TYPE(double, start_position, -1);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadLinkType, type);
  REGISTER_MEMBER_COMPLEX_TYPE(
      ContactPointType,
      contact_point);  // Contact point of link on the linked element
  REGISTER_MEMBER_COMPLEX_TYPE(Dir, dir);

 public:
  RoadLinkInfo()
      : id_(-1),
        start_position_(-1),
        type_(RoadLinkType::kRoad),
        contact_point_(ContactPointType::kUnknown),
        dir_(Dir::kUnknown) {}
};

class RoadLink {
  REGISTER_MEMBER_COMPLEX_TYPE(RoadLinkInfo, predecessor);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadLinkInfo, successor);

 public:
  RoadLink() {}
};

class RoadTypeInfo {
  REGISTER_MEMBER_BASIC_TYPE(double, start_position, -1);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadType, type);
  REGISTER_MEMBER_COMPLEX_TYPE(std::string, country);
  REGISTER_MEMBER_BASIC_TYPE(float, max_speed, 0);
  REGISTER_MEMBER_COMPLEX_TYPE(SpeedUnit, speed_unit);

 public:
  RoadTypeInfo()
      : start_position_(0),
        type_(RoadType::kTown),
        country_(""),
        max_speed_(0),
        speed_unit_(SpeedUnit::kMs) {}
};

class RoadPlanView {
  REGISTER_MEMBER_COMPLEX_TYPE(Geometry::Ptrs, geometrys);

 public:
  RoadPlanView() {}
};

class Road {
  REGISTER_MEMBER_COMPLEX_TYPE(RoadAttribute, attribute);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadLink, link);
  REGISTER_MEMBER_COMPLEX_TYPE(std::vector<RoadTypeInfo>, type_info);
  REGISTER_MEMBER_COMPLEX_TYPE(RoadPlanView, plan_view);
  REGISTER_MEMBER_COMPLEX_TYPE(Lanes, lanes);

 public:
  Road() {}
};

class JunctionAttribute {
  REGISTER_MEMBER_BASIC_TYPE(Id, id, -1);
  REGISTER_MEMBER_COMPLEX_TYPE(Name, name);
  REGISTER_MEMBER_COMPLEX_TYPE(JunctionType, type);
  REGISTER_MEMBER_BASIC_TYPE(Id, main_road, -1);  // virtual junctions v1.7
  REGISTER_MEMBER_BASIC_TYPE(double, start_position,
                             -1);  // virtual junctions v1.7
  REGISTER_MEMBER_BASIC_TYPE(double, end_position,
                             -1);          // virtual junctions v1.7
  REGISTER_MEMBER_COMPLEX_TYPE(Dir, dir);  // virtual junctions v1.7

 public:
  JunctionAttribute()
      : id_(-1),
        type_(JunctionType::kDefault),
        main_road_(-1),
        start_position_(-1),
        end_position_(-1),
        dir_(Dir::kUnknown) {}
};

class JunctionLaneLink {
  REGISTER_MEMBER_BASIC_TYPE(Id, from, -1);
  REGISTER_MEMBER_BASIC_TYPE(Id, to, -1);

 public:
  JunctionLaneLink() : from_(-1), to_(-1) {}
};
using JunctionLaneLinks = std::vector<JunctionLaneLink>;

class JunctionConnection {
  REGISTER_MEMBER_BASIC_TYPE(Id, id, -1);
  REGISTER_MEMBER_COMPLEX_TYPE(JunctionConnectionType, type);
  REGISTER_MEMBER_BASIC_TYPE(Id, incoming_road, -1);
  REGISTER_MEMBER_BASIC_TYPE(Id, connecting_road, -1);
  REGISTER_MEMBER_BASIC_TYPE(Id, linked_road, -1);
  REGISTER_MEMBER_COMPLEX_TYPE(ContactPointType, contact_point);
  REGISTER_MEMBER_COMPLEX_TYPE(JunctionLaneLinks, lane_links);

 public:
  JunctionConnection()
      : id_(-1),
        type_(JunctionConnectionType::kUnknown),
        incoming_road_(-1),
        connecting_road_(-1),
        linked_road_(-1),
        contact_point_(ContactPointType::kUnknown) {}
};
using JunctionConnections = std::vector<JunctionConnection>;

class Junction {
  REGISTER_MEMBER_COMPLEX_TYPE(JunctionAttribute, attribute);
  REGISTER_MEMBER_COMPLEX_TYPE(JunctionConnections, connections);

 public:
  Junction() {}
};

class Map {
  REGISTER_MEMBER_COMPLEX_TYPE(Header, header);
  REGISTER_MEMBER_COMPLEX_TYPE(std::vector<Road>, roads);
  REGISTER_MEMBER_COMPLEX_TYPE(std::vector<Junction>, junctions);

 public:
  using Ptr = std::shared_ptr<Map>;
  using ConstPtr = std::shared_ptr<Map const>;
  Map() {}
};

}  // namespace element
}  // namespace opendrive

#endif  // OPENDRIVE_CPP_ELEMENT_H_
