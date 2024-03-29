#ifndef HDMAP_ADAPTER_OPENDRIVE_PARSER_H_
#define HDMAP_ADAPTER_OPENDRIVE_PARSER_H_

#include "hdmap/adapter/opendrive/parser/header_parser.h"
#include "hdmap/adapter/opendrive/parser/map_parser.h"
#include "hdmap/adapter/parser.h"

namespace hdmap {

class OpenDriveParser : public ParseProcessor {
 public:
  OpenDriveParser() = default;

  virtual bool process(std::shared_ptr<PipelineData>) override;

 private:
  OpenDriveParser& CheckIn(std::shared_ptr<PipelineData>);

  OpenDriveParser& Parse();

  bool Finish();
};

}  // namespace hdmap

#endif  // HDMAP_ADAPTER_OPENDRIVE_PARSER_H_
