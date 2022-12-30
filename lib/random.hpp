#include <random>
#include <sys/types.h>

class Random {
  public:
    static ulong Rng(const int &floor, const int &ceiling) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(floor,
                                                                      ceiling);
        return dist(rng);
    };
};
