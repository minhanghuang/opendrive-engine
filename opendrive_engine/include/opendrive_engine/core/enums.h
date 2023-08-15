#ifndef OPENDRIVE_ENGINE_CORE_ENUMS_H_
#define OPENDRIVE_ENGINE_CORE_ENUMS_H_

#include <string>

namespace opendrive {

enum class Boolean : std::uint8_t { kFalse = 0, kTrue, kUnknown };

enum class GeometryType : std::uint8_t {
  kArc,
  kLine,
  kSpiral,
  kPoly3,
  kParamPoly3,
};

enum class LaneType : std::uint8_t {
  kSholder = 0,  // Describes a soft border at the edge of the road.
  kBorder,   // Describes a hard border at the edge of the road. It has the same
             // height as the drivable lane.
  kDriving,  // Describes a "normal" drivable road that is not one of the other
             // types.
  kStop,     // Hard shoulder on motorways for emergency stops
  kNone,  // Describes the space on the outermost edge of the road and does not
          // have actual content Its only purpose is for applications to
          // register that ASAM OpenDRIVE is still present in case the (human)
          // driver leaves the road.
  kRestricted,  // Describes a lane on which cars should not drive. The lane has
                // the same height as drivable lanes. Typically, the lane is
                // separated with lines and often contains dotted lines as well.
  kParking,     // Describes a lane with parking spaces.
  kMedian,      // Describes a lane that sits between driving lanes that lead in
            // opposite directions. It is typically used to separate traffic in
            // towns on large roads.
  kBiking,    // Describes a lane that is reserved for cyclists.
  kSidewalk,  // Describes a lane on which pedestrians can walk.
  kCurb,  // Describes curb stones. Curb stones have a different height than the
          // adjacent drivable lanes.
  kExit,  // Describes a lane that is used for sections that are parallel to the
          // main road. It is mainly used for deceleration lanes.
  kEntry,   // Describes a lane type that is used for sections that are parallel
            // to the main road. It is mainly used for acceleration lanes.
  kOnramp,  // A ramp leading to a motorway from rural or urban roads.
  kOfframp,  //  A ramp leading away from a motorway and onto rural urban roads.
  kConnectingramp,  //  A ramp that connects two motorways, for example,
                    //  motorway junctions.
  kBidirectional,
  kSpecial1,
  kSpecial2,
  kSpecial3,
  kRoadworks,
  kTram,
  kRail,
  kBus,
  kTaxi,
  kHov,
  kMwyentry,
  kMwyexit
};

enum class RoadMarkType : std::uint8_t {
  kUnknown = 0,
  kNone,
  kSolid,
  kBroken,
  kSolidsolid,
  kSolidbroken,
  kBrokensolid,
  kBrokenbroken,
  kBottsdots,
  kGrass,
  kCurb,
  kCustom,
  kEdge
};

enum class RoadMarkColor : std::uint8_t {
  kStandard = 0,
  kBlue,
  kGreen,
  kRed,
  kWhite,
  kYellow,
  kOrange
};

enum class RoadMarkWeight : std::uint8_t { kUnknown = 0, kStandard, kBold };

enum class RoadMarkLaneChange : std::uint8_t {
  kUnknown = 0,
  kNone,
  kIncrease,
  kDecrease,
  kBoth,
};

enum class RoadRule { kRht, kLht };

enum class RoadType : std::uint8_t {
  kRural = 0,
  kMotorway,
  kTown,
  kLowspeed,
  kPedestrian,
  kBicycle,
  kTownexpressway,
  kTowncollector,
  kTownarterial,
  kTownprivate,
  kTownlocal,
  kTownplaystreet,
};

enum class RoadLinkType { kRoad = 0, kJunction };

enum class SpeedUnit {
  kMs = 0,  // m/s
  kMph,     // mph
  kKmh      // km/h
};

enum class LaneDirection { kUnknown = 0, kLeft, kCenter, kRight };

enum class JunctionType { kDefault, kDirect, kVirtual };

enum class JunctionConnectionType { kUnknown = 0, kDefault, kVirtual };

enum class ContactPointType { kUnknown = 0, kStart, kEnd };

enum class Dir { kUnknown = 0, kPlus, kMinus };

}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_CORE_ENUMS_H_
