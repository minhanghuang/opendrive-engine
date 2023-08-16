#include "opendrive_engine/engine.h"

namespace opendrive {
namespace engine {

Status Engine::Init() { return impl_->Init(); }

core::Header::ConstPtr Engine::GetHeader() { return impl_->GetHeader(); }

}  // namespace engine
}  // namespace opendrive
