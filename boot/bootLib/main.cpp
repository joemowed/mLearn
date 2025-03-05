#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <vector>
extern void boot(void);
extern "C" int main(void) {
    while(true){
        boot();
    }
}
