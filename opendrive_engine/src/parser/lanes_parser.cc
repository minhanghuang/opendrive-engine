#include "opendrive_engine/parser/lanes_parser.h"

namespace opendrive {
namespace engine {

Status LanesParser::Start(const tinyxml2::XMLElement* xml_element,
                          std::shared_ptr<core::Map> map) {
  status_.Reset();
  if (!xml_element || !map) {
    return status_;
  }
  return status_;
}

}  // namespace engine
}  // namespace opendrive
