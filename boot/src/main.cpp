// called by main, this is entry point.  Runs in loop.
#include <algorithm>
#include <cstdint>
#include <irq.hpp>
#include <reg.hpp>
#include <vector>
void boot(void) {
    std::vector<uint32_t> vec{5, 2, 3};
    std::sort(vec.begin(), vec.end());
}
