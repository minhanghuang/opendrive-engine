#ifndef OPENDRIVE_ENGINE_PARSER_BASE_H_
#define OPENDRIVE_ENGINE_PARSER_BASE_H_

#include <tinyxml2.h>

#include "opendrive_engine/common/status.h"
#include "opendrive_engine/core/map.h"

namespace opendrive {
namespace engine {

class ParserBase {
 public:
  virtual ~ParserBase() = default;
  ParserBase() = default;

  virtual Status Start(const tinyxml2::XMLElement* xml_element,
                       std::shared_ptr<core::Map> map) = 0;

 protected:
  tinyxml2::XMLError XmlQueryStringAttribute(
      const tinyxml2::XMLElement* xml_element, const std::string& name,
      std::string* value) {
    const char* val = xml_element->Attribute(name.c_str());
    if (nullptr == val) {
      return tinyxml2::XML_NO_ATTRIBUTE;
    }
    *value = val;
    return tinyxml2::XML_SUCCESS;
  }
  tinyxml2::XMLError XmlQueryDoubleAttribute(
      const tinyxml2::XMLElement* xml_element, const std::string& name,
      double* value) {
    return xml_element->QueryDoubleAttribute(name.c_str(), value);
  }
  tinyxml2::XMLError XmlQueryIntAttribute(
      const tinyxml2::XMLElement* xml_element, const std::string& name,
      int* value) {
    return xml_element->QueryIntAttribute(name.c_str(), value);
  }
  const tinyxml2::XMLElement* XmlNextSiblingElement(
      const tinyxml2::XMLElement* element) {
    return element->NextSiblingElement(element->Name());
  }

 protected:
  // opendrive map data
  std::shared_ptr<core::Map> map_;

  // status
  Status status_{ErrorCode::kOk};
};

}  // namespace engine
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_PARSER_BASE_H_
