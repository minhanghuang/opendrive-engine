#include "server.h"

namespace hdmap {

Server::Server() {}

int Server::Init() {
  auto global_data = server::GlobalData::Instance();
  options_.num_threads = global_data->GetParam()->http().thread_num;
  options_.port = global_data->GetParam()->http().port;
  options_.root = "";
  ok_ = std::make_shared<server::OkApi>();
  global_map_ = std::make_shared<server::GlobalMapApi>();
  nearest_lane_ = std::make_shared<server::NearestLane>();
  hot_update_ = std::make_shared<server::HotUpdate>();
  planning_ = std::make_shared<server::Planning>();
  real_time_data_ = std::make_shared<server::RealTimeData>();
  return 0;
}

int Server::Start() {
  cyclone::web::Application app;
  app.Init(options_);
  app.AddHandler("/opendrive/engine/ok/", ok_);
  app.AddHandler("/opendrive/engine/map/", global_map_);
  app.AddHandler("/opendrive/engine/nearest_lane/", nearest_lane_);
  app.AddHandler("/opendrive/engine/hot_update/", hot_update_);
  app.AddHandler("/opendrive/engine/planning/", planning_);
  app.AddHandler("/opendrive/engine/ws/real_time_data/", real_time_data_);
  app.Spin();
  return 0;
}

}  // namespace hdmap
