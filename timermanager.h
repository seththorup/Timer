#pragma once
#include <chrono>
#include <map>
#include <vector>

namespace thorup {

typedef std::chrono::high_resolution_clock::time_point timer_time_type;
typedef std::chrono::duration<double> timer_duration_type;
class timertype {
public:
  timer_time_type start_time;
  timer_duration_type timer_duration;
  
};

class timermanager {
private:
  std::map<std::string, timertype> timer_map;

public:
  timermanager() = default;

  void start_timer(std::string &name);
  void stop_timer(std::string &name);
  double get_duration_sec(std::string &name);
  double get_duration_ms(std::string &name);
  uint64_t get_duration_us(std::string &name);
  uint64_t get_duration_ns(std::string &name);
  std::vector<std::string> get_timer_names();
  inline uint32_t get_num_timers() {return timer_map.size();}
  inline void delete_timer(std::string& name) {timer_map.erase(name);}
  inline void delete_all_timers() {timer_map.clear();}
};
} // namespace thorup