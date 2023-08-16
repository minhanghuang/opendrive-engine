#include "opendrive_engine/parser/parser.h"

namespace opendrive {
namespace engine {

Status Parser::Init() {
  status_.Reset();
  // check opendrive file
  if (params_->opendrive_file_path.empty()) {
    return status_;
  }
  status_.set_error_code(ErrorCode::kOk);
  return status_;
}

Status Parser::Start() {
  if (!status_.ok()) {
    return status_;
  }
  tinyxml2::XMLDocument xml_doc;
  xml_doc.LoadFile(params_->opendrive_file_path.c_str());
  if (xml_doc.Error()) {
    status_.set_error_code(ErrorCode::kLoadOpenDriveFileError);
    status_.set_msg("opendrive file load fault");
    return status_;
  }

  // xml root
  tinyxml2::XMLElement* xml_element = xml_doc.RootElement();

  // parser header
  HeaderParser header_parser;
  header_parser.Start(xml_element, map_);

  return status_;
}

}  // namespace engine
}  // namespace opendrive
