#include "opendrive_engine/parser/junction_parser.h"

namespace opendrive {
namespace engine {

Status JunctionParser::Start(const tinyxml2::XMLElement* xml_element,
                             std::shared_ptr<core::Map> map) {
  status_.Reset();
  if (!xml_element || !map) {
    return status_;
  }
  const tinyxml2::XMLElement* curr_xml_element =
      xml_element->FirstChildElement("junction");
  // while (curr_xml_element) {
  // }
  return status_;
}

}  // namespace engine
}  // namespace opendrive
