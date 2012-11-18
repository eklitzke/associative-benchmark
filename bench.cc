#include <chrono>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>

#include <stdlib.h>
#include <unistd.h>

class Timer {
 public:

  typedef std::chrono::system_clock clock_type;

  Timer() :start_time_(clock_type::now()) {}

  void reset() { start_time_ = clock_type::now(); }

  long elapsed_ms() { return elapsed_count<std::chrono::milliseconds>(); }
  long elapsed_us() { return elapsed_count<std::chrono::microseconds>(); }
  long elapsed_ns() { return elapsed_count<std::chrono::nanoseconds>(); }
 private:
  std::chrono::time_point<std::chrono::system_clock> start_time_;

  template <typename T>
  inline int elapsed_count() {
    return std::chrono::duration_cast<T>(
        clock_type::now() - start_time_).count();
  }
};

int main(int argc, char **argv) {
  int c;
  bool reserve = false;
  std::size_t num = 1000000;
  while ((c = getopt(argc, argv, "hrn:")) != -1) {
    switch (c) {
      case 'h':
        std::cout << "usage: " << argv[0] << " [-h] [-r] [-n num]\n";
        return 0;
        break;
      case 'n':
        num = static_cast<std::size_t>(atoi(optarg));
        break;
      case 'r':
        reserve = true;
        break;
      default:
        std::cout << "usage: " << argv[0] << " [-h] [-n num]\n";
        return 1;
    }
  }

  std::cout << "generating number list with " << num
            << " integer pairs..." << std::endl;
  std::ifstream urandom("/dev/urandom",
                        std::ifstream::in | std::ifstream::binary);
  Timer gen_timer;
  std::vector<std::pair<int, int> > pairs;
  if (reserve) {
    pairs.reserve(num);
  }
  char charbuf[sizeof(int)];
  for (std::size_t i = 0; i < num; i++) {
    int key, val;
    urandom.read(charbuf, sizeof(charbuf));
    key = *reinterpret_cast<int*>(charbuf);
    urandom.read(charbuf, sizeof(charbuf));
    val = *reinterpret_cast<int*>(charbuf);
    pairs.emplace_back(std::make_pair(key, val));
  }
  std::cout << "generated in " << gen_timer.elapsed_ms() << " ms\n";

  {
    std::cout << "\nmap\n----------" << std::endl;
    Timer timer;
    std::map<int, int> number_map;
    for (const auto &kv : pairs) {
      number_map.insert(kv);
    }
    std::cout << "create: " << timer.elapsed_ms() << std::endl;

    timer.reset();
    for (const auto &kv : pairs) {
      number_map.find(kv.first);
    }
    std::cout << "search: " << timer.elapsed_ms() << std::endl;
  }

  {
    std::cout << "\nhash\n----------" << std::endl;
    Timer timer;
    std::unordered_map<int, int> number_hash;
    if (reserve) {
      number_hash.reserve(num);
    }
    for (const auto &kv : pairs) {
      number_hash.insert(kv);
    }
    std::cout << "create: " << timer.elapsed_ms() << std::endl;

    timer.reset();
    for (const auto &kv : pairs) {
      number_hash.find(kv.first);
    }
    std::cout << "search: " << timer.elapsed_ms() << "\n\n";

    std::cout << "bucket count = " << number_hash.bucket_count() << "\n";
    std::cout << "load factor = " << number_hash.load_factor() << "\n";
    std::cout << "max load factor = " << number_hash.max_load_factor() << "\n";
  }
  return 0;
}
