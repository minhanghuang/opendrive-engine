#ifndef OPENDRIVE_ENGINE_IMPL_H_
#define OPENDRIVE_ENGINE_IMPL_H_

#include <memory>

#include "opendrive_engine/common/macros.h"
#include "opendrive_engine/common/params.h"
#include "opendrive_engine/common/rw_lock.h"
#include "opendrive_engine/common/status.h"
#include "opendrive_engine/core/header.h"
#include "opendrive_engine/core/map.h"
#include "opendrive_engine/parser/parser.h"

namespace opendrive {
namespace engine {

class EngineImpl {
 public:
  ~EngineImpl() = default;
  EngineImpl()
      : params_(common::Singleton::Instance<Params>()),
        map_(std::make_shared<core::Map>()),
        parser_(std::make_shared<Parser>(map_)) {}

  Status Init();
  
  core::Header::ConstPtr GetHeader();

 private:
  // read write lock
  AtomicRWLock rw_lock_;

  // engine params singleton
  std::shared_ptr<Params> params_;

  // opendrive map data
  std::shared_ptr<core::Map> map_;

  // opendrive parser
  std::shared_ptr<Parser> parser_;
};

}  // namespace engine
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_IMPL_H_
