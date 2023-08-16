#include "opendrive_engine/parser/header_parser.h"

namespace opendrive {
namespace engine {

Status HeaderParser::Start(const tinyxml2::XMLElement* xml_element,
                           std::shared_ptr<core::Map> map) {
  status_.Reset();
  if (!xml_element || !map) {
    return status_;
  }
  const tinyxml2::XMLElement* xml_header =
      xml_element->FirstChildElement("header");
  if (!xml_header) {
    status_.set_error_code(ErrorCode::kEngineParserXmlHeaderError);
    status_.set_msg("parser xml header exception");
    return status_;
  }
  std::shared_ptr<core::Header> header = std::make_shared<core::Header>();
  XmlQueryStringAttribute(xml_header, "revMajor", header->mutable_rev_major());
  XmlQueryStringAttribute(xml_header, "revMinor", header->mutable_rev_minor());
  XmlQueryStringAttribute(xml_header, "version", header->mutable_version());
  XmlQueryStringAttribute(xml_header, "name", header->mutable_name());
  XmlQueryStringAttribute(xml_header, "vendor", header->mutable_vendor());
  XmlQueryStringAttribute(xml_header, "date", header->mutable_date());
  double north = header->north();
  double south = header->south();
  double east = header->east();
  double west = header->west();
  XmlQueryDoubleAttribute(xml_header, "north", &north);
  XmlQueryDoubleAttribute(xml_header, "south", &south);
  XmlQueryDoubleAttribute(xml_header, "east", &east);
  XmlQueryDoubleAttribute(xml_header, "west", &west);
  header->set_north(north);
  header->set_south(south);
  header->set_west(west);
  header->set_east(east);
  map->set_header(std::move(header));
  return status_;
}

}  // namespace engine
}  // namespace opendrive
