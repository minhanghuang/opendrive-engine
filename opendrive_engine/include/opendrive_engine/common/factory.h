#ifndef OPENDRIVE_ENGINE_COMMON_FACTORY_H_
#define OPENDRIVE_ENGINE_COMMON_FACTORY_H_

#include <unordered_map>
#include <vector>

#include "opendrive_engine/common/macros.h"

namespace opendrive {

class Factory {
 public:
  ~Factory();
  bool Contains(const std::string& unique_id);
  bool Empty();
  void Clear();
  std::vector<std::string> GetObjectNames();

  template <typename Class>
  bool Register(const std::string& unique_id, bool force = false) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (!force && producers_.count(unique_id)) {
      return false;
    }
    producers_.emplace(std::make_pair(unique_id, std::make_shared<Class>()));
    return true;
  }

  template <typename Class>
  bool Register(const Class* object, const std::string& unique_id,
                bool force = false) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (!force && producers_.count(unique_id)) {
      return false;
    }
    producers_[unique_id] = std::make_shared<Class>(*object);
    return true;
  }

  template <typename Class>
  bool Register(const std::shared_ptr<Class>& object,
                const std::string& unique_id, bool force = false) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (!force && producers_.count(unique_id)) {
      return false;
    }
    producers_[unique_id] = object;
    return true;
  }

  template <typename Class>
  bool Register(std::shared_ptr<Class>&& object, const std::string& unique_id,
                bool force = false) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (!force && producers_.count(unique_id)) {
      return false;
    }
    producers_[unique_id] = std::move(object);
    return true;
  }

  template <typename Class>
  bool Unregister(const std::string& unique_id) {
    std::lock_guard<std::mutex> guard(mutex_);
    if (producers_.count(unique_id)) {
      producers_.erase(unique_id);
      return true;
    }
    return false;
  }

  template <typename Class>
  std::shared_ptr<Class> GetObject(const std::string& unique_id) {
    std::lock_guard<std::mutex> guard(mutex_);
    auto id_iter = producers_.find(unique_id);
    if (id_iter != producers_.end()) {
      return std::static_pointer_cast<Class>(id_iter->second);
    }
    return nullptr;
  }

 private:
  std::mutex mutex_;
  std::unordered_map<std::string, std::shared_ptr<void>> producers_;
  DECLARE_SINGLETON(Factory)  // 声明单例
};

}  // namespace opendrive

#endif  // OPENDRIVE_ENGINE_COMMON_FACTORY_H_
