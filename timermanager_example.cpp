#include "timermanager.h"

#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

using std::cout;
using std::endl;
using std::chrono::microseconds;

int main() {
  cout << "Timer Manager Example" << endl;

  auto sleep_timer_count = microseconds(100);

  thorup::timermanager timer;
  std::vector<std::string> timer_name_vec{"first_timer", "second_timer",
                                          "third_timer"};
  for (auto name : timer_name_vec) {
    timer.start_timer(name);
  }
  std::this_thread::sleep_for(sleep_timer_count);
  for (auto name : timer_name_vec) {
    timer.stop_timer(name);
  }
  cout << "Sleep timer: " << sleep_timer_count.count() << endl;
  cout << std::left << std::setw(14) << "Timer Name" << std::setw(14)
       << "us" << std::setw(14) << "Microseconds" << std::setw(14)
       << "Milliseconds" << endl;

  for (auto name : timer_name_vec) {
    auto duration_sec = timer.get_duration_sec(name);
    auto duration_us = timer.get_duration_us(name);
    auto duration_ms = timer.get_duration_ms(name);

    cout << std::setw(14) << name << std::setw(14) << duration_sec
         << std::setw(14) << duration_us << std::setw(14)
         << duration_ms << endl;
  }

  cout << "Num of timers: " << timer.get_num_timers() << endl;

  auto timer_names = timer.get_timer_names();
  for (auto name : timer_names) {
    cout << name << " ";
  }
  cout << endl << "Cleaing up timers..." << endl;

  timer.delete_timer(timer_names.at(0));
  cout << "Num of timers: " << timer.get_num_timers() << endl;
  timer.delete_all_timers();
  cout << "Num of timers: " << timer.get_num_timers() << endl;

  return 0;
}