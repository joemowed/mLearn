#include <cerrno>
#include <cstdlib>
extern void boot(void);
extern "C" int main(void) {
    while (true) {
        boot();
    }
}
