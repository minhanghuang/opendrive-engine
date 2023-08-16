#ifndef OPENDRIVE_ENGINE_ROAD_PARSER_H_
#define OPENDRIVE_ENGINE_ROAD_PARSER_H_

#include <memory>
#include <utility>

#include "opendrive_engine/common/status.h"
#include "opendrive_engine/core/map.h"
#include "opendrive_engine/parser/parser_base.h"

namespace opendrive {
namespace engine {

class RoadParser : public ParserBase {
 public:
  RoadParser() = default;
  virtual Status Start(const tinyxml2::XMLElement* xml_element,
                       std::shared_ptr<core::Map> map) override;

 private:
  RoadParser& Attributes(const tinyxml2::XMLElement* road_xml_element,
                         std::shared_ptr<core::Road> road);
  RoadParser& LinkElement(const tinyxml2::XMLElement* road_xml_element,
                          std::shared_ptr<core::Road> road);
  RoadParser& TypeElement(const tinyxml2::XMLElement* road_xml_element,
                          std::shared_ptr<core::Road> road);
  RoadParser& PlanViewElement(const tinyxml2::XMLElement* road_xml_element,
                              std::shared_ptr<core::Road> road);
  RoadParser& LanesElement(const tinyxml2::XMLElement* road_xml_element,
                           std::shared_ptr<core::Road> road);
  RoadParser& GenerateRoad(const tinyxml2::XMLElement* road_xml_element,
                           std::shared_ptr<core::Road> road);
};

}  // namespace engine
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_ROAD_PARSER_H_
