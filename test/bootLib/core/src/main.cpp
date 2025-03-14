extern void loop(void);
extern void init(void);
#include "sys.hpp"
extern "C" int main(void) {
    sys::init();
    init();

    while (true) {
        loop();
    }
}
