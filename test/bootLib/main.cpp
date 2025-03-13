extern void loop(void);
extern void init(void);
extern "C" int main(void) {
    init();

    while (true) {
        loop();
    }
}
