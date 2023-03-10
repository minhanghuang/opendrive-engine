#ifndef OPENDRIVE_ENGINE_SERVER_API_H_
#define OPENDRIVE_ENGINE_SERVER_API_H_
#include <typhoon/typhoon.h>

#include <nlohmann/json.hpp>

#include "global_data.h"
#include "log.h"
#include "util.h"

namespace opendrive {
namespace engine {
namespace server {

enum class HttpStatusCode {
  SUCCESS = 1000,
  FAILED,
  PARAM,
};

class RequestBase {
 public:
  RequestBase();
  virtual ~RequestBase() = default;

 protected:
  virtual bool CheckRequestData(
      const std::unordered_map<std::string, nlohmann::json::value_t>& keys,
      const std::string& data, Json& data_out) final;
  virtual bool IsNumberType(const Json& value) const final;
  virtual std::string SetResponse(const Json& data,
                                  HttpStatusCode code = HttpStatusCode::SUCCESS,
                                  const std::string& msg = "ok") final;
  engine::Engine::Ptr engine_;
};

class OkApi : public typhoon::RequestHandler, public RequestBase {
 public:
  virtual void Get(typhoon::Application* app,
                   typhoon::Connection* conn) override;
  virtual void Post(typhoon::Application* app,
                    typhoon::Connection* conn) override;
};

class GlobalMapApi : public typhoon::RequestHandler, public RequestBase {
 public:
  virtual void Get(typhoon::Application* app,
                   typhoon::Connection* conn) override;
};

}  // namespace server
}  // namespace engine
}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_SERVER_API_H_
