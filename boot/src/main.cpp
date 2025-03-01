#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <vector>
int main(void) {
    for (int i = 0; i < 1000; i++) {
        std::vector<int> *N = new std::vector<int>(33);
        volatile void *i2 = malloc(300);
        volatile void *i3 = i2;
        N->push_back(i);
    }
    return 0;
}
