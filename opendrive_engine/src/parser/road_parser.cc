#include "opendrive_engine/parser/road_parser.h"

namespace opendrive {
namespace engine {

Status RoadParser::Start(const tinyxml2::XMLElement* xml_element,
                         std::shared_ptr<core::Map> map) {
  status_.Reset();
  if (!xml_element || !map) {
    return status_;
  }
  const tinyxml2::XMLElement* curr_xml_road =
      xml_element->FirstChildElement("road");
  if (curr_xml_road) {
    status_.set_error_code(ErrorCode::kEngineParserXmlRoadError);
    status_.set_msg("parser xml road exception");
    return status_;
  }
  while (curr_xml_road) {
  }
  return status_;
}

RoadParser& RoadParser::Attributes(const tinyxml2::XMLElement* road_xml_element,
                                   std::shared_ptr<core::Road> road) {
  if (!status_.ok()) {
    return *this;
  }
  if (!road_xml_element || !road) {
    return *this;
  }
  return *this;
}

RoadParser& RoadParser::LinkElement(
    const tinyxml2::XMLElement* road_xml_element,
    std::shared_ptr<core::Road> road) {
  if (!status_.ok()) {
    return *this;
  }
  if (!road_xml_element || !road) {
    return *this;
  }

  return *this;
}

RoadParser& RoadParser::TypeElement(
    const tinyxml2::XMLElement* road_xml_element,
    std::shared_ptr<core::Road> road) {
  if (!status_.ok()) {
    return *this;
  }
  if (!road_xml_element || !road) {
    return *this;
  }

  return *this;
}

RoadParser& RoadParser::PlanViewElement(
    const tinyxml2::XMLElement* road_xml_element,
    std::shared_ptr<core::Road> road) {
  if (!status_.ok()) {
    return *this;
  }
  if (!road_xml_element || !road) {
    return *this;
  }

  return *this;
}

RoadParser& RoadParser::LanesElement(
    const tinyxml2::XMLElement* road_xml_element,
    std::shared_ptr<core::Road> road) {
  if (!status_.ok()) {
    return *this;
  }
  if (!road_xml_element || !road) {
    return *this;
  }

  return *this;
}

RoadParser& RoadParser::GenerateRoad(
    const tinyxml2::XMLElement* road_xml_element,
    std::shared_ptr<core::Road> road) {
  if (!status_.ok()) {
    return *this;
  }
  if (!road_xml_element || !road) {
    return *this;
  }

  return *this;
}

}  // namespace engine
}  // namespace opendrive
