// called by main, this is entry point.  Runs in loop.
#include <unordered_set>
void boot(void) {
    volatile int i = 0x3237898;
    i = 0x0;
    i += 1;
    i += 1;
    i += 1;
    asm("nop");
}
