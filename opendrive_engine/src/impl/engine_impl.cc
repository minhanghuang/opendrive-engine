#include "opendrive_engine/impl/engine_impl.h"

namespace opendrive {
namespace engine {

Status EngineImpl::Init() {
  auto status = parser_->Init();
  if (!status.ok()) {
    return status;
  }
  status = parser_->Start();
  return status;
}

core::Header::ConstPtr EngineImpl::GetHeader() { return map_->header(); }

}  // namespace engine
}  // namespace opendrive
