#include <chrono>
#include <iostream>
#include <ratio>

#include "timermanager.h"

using std::cout;
using std::endl;
using namespace std::chrono;

namespace thorup {

void timermanager::start_timer(std::string &name) {
  if (auto itr = timer_map.find(name); itr == timer_map.end()) {
    timertype timer;
    timer_map[name] = timer;
    timer_map[name].start_time = std::chrono::high_resolution_clock::now();
    
  } else {
    itr->second.start_time = std::chrono::high_resolution_clock::now();
  }
}

void timermanager::stop_timer(std::string &name) {
  if (auto itr = timer_map.find(name); itr != timer_map.end()) {
    auto end_time = std::chrono::high_resolution_clock::now();
    itr->second.timer_duration =
        duration_cast<duration<double>>(end_time - itr->second.start_time);
  } else {
    std::cout << "timermanager " << name << " not found" << endl;
  }
}

std::vector<std::string> timermanager::get_timer_names() {
  std::vector<std::string> timer_names = {};
  for( auto itr = timer_map.begin(); itr != timer_map.end(); itr++) {
    auto name = itr->first;
    timer_names.push_back(name);
  }
  return timer_names;
}

double timermanager::get_duration_sec(std::string &name) {
  double d{0};
  if (auto itr = timer_map.find(name); itr != timer_map.end()) {
    d = itr->second.timer_duration.count();
  }
  return d;
}

double timermanager::get_duration_ms(std::string &name) {
  double d{0};
  if (auto itr = timer_map.find(name); itr != timer_map.end()) {
    d = duration_cast<duration<double, std::milli>>(itr->second.timer_duration)
            .count();
  }
  return d;
}

uint64_t timermanager::get_duration_us(std::string &name) {
  double duration{0};
  if (auto itr = timer_map.find(name); itr != timer_map.end()) {
    duration = duration_cast<microseconds>(itr->second.timer_duration).count();
  }
  return duration;
}

uint64_t timermanager::get_duration_ns(std::string &name) {
  double duration{0};
  if (auto itr = timer_map.find(name); itr != timer_map.end()) {
    duration = duration_cast<nanoseconds>(itr->second.timer_duration).count();
  }
  return duration;
}

} // namespace thorup