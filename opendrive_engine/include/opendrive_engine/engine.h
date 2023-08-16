#ifndef OPENDRIVE_ENGINE_H_
#define OPENDRIVE_ENGINE_H_

#include <memory>

#include "opendrive_engine/common/status.h"
#include "opendrive_engine/impl/engine_impl.h"

namespace opendrive {
namespace engine {

class Engine {
 public:
  Engine() : impl_(std::make_shared<EngineImpl>()) {}

  // Engine Init
  Status Init();

  // Get
  core::Header::ConstPtr GetHeader();

 private:
  // engine impl
  std::shared_ptr<EngineImpl> impl_;
};

}  // namespace engine
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_H_
