#ifndef OPENDRIVE_ENGINE_PARSER_H_
#define OPENDRIVE_ENGINE_PARSER_H_

#include <tinyxml2.h>

#include "opendrive_engine/common/common.hpp"
#include "opendrive_engine/common/params.h"
#include "opendrive_engine/common/status.h"
#include "opendrive_engine/core/map.h"
#include "opendrive_engine/parser/header_parser.h"
#include "opendrive_engine/parser/junction_parser.h"

namespace opendrive {
namespace engine {

class Parser {
 public:
  ~Parser() = default;
  Parser(std::shared_ptr<core::Map> map)
      : params_(common::Singleton::Instance<Params>()), map_(map) {}

  Status Init();

  Status Start();

 private:
  // engine params singleton
  std::shared_ptr<Params> params_;

  // opendrive map data
  std::shared_ptr<core::Map> map_;

  // status
  Status status_{ErrorCode::kUnknown};
};

}  // namespace engine
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_PARSER_H_
