#ifndef OPENDRIVE_ENGINE_HEADER_PARSER_H_
#define OPENDRIVE_ENGINE_HEADER_PARSER_H_

#include <utility>

#include "opendrive_engine/common/status.h"
#include "opendrive_engine/core/map.h"
#include "opendrive_engine/parser/parser_base.h"

namespace opendrive {
namespace engine {

class HeaderParser : public ParserBase {
 public:
  HeaderParser() = default;
  virtual Status Start(const tinyxml2::XMLElement* xml_element,
                       std::shared_ptr<core::Map> map) override;

 private:
};

}  // namespace engine
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_HEADER_PARSER_H_
