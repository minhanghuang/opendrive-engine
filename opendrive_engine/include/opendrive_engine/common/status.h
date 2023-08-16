#ifndef OPENDRIVE_ENGINE_COMMON_STATUS_H_
#define OPENDRIVE_ENGINE_COMMON_STATUS_H_

#include <string>

namespace opendrive {

enum class ErrorCode {
  kOk = 0,
  kUnknown = 1,

  // OpenDRIVE File exception
  kLoadOpenDriveFileError = 100,

  // Parser Header Exception
  kEngineParserXmlHeaderError = 110,
};

class Status final {
 public:
  ~Status() = default;
  Status() : error_code_(ErrorCode::kUnknown) {}
  Status(ErrorCode error_code, const std::string& msg = "")
      : error_code_(error_code), msg_(msg) {}

  void set_error_code(ErrorCode error_code) { error_code_ = error_code; }

  void set_msg(const std::string& msg) { msg_ = msg; }

  ErrorCode error_code() const { return error_code_; }

  std::string msg() const { return msg_; }

  void Reset() {
    error_code_ = ErrorCode::kUnknown;
    msg_.clear();
  }

  bool ok() const { return ErrorCode::kOk == error_code_; }

 private:
  ErrorCode error_code_;
  std::string msg_;
};

}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_COMMON_STATUS_H_
