#ifndef OPENDRIVE_ENGINE_COMMON_PARAMS_H_
#define OPENDRIVE_ENGINE_COMMON_PARAMS_H_

#include <string>

#include "opendrive_engine/common/macros.h"

namespace opendrive {
namespace engine {

struct Params {
  std::string opendrive_file_path;

 private:
  DECLARE_SINGLETON(Params)
};

}  // namespace engine
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_COMMON_PARAMS_H_
