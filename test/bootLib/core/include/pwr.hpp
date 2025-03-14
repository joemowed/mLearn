#ifndef __pwr__INC_GRD__
#define __pwr__INC_GRD__
class pwr {
  public:
    pwr() = delete;
    // initializes peripherial clock
    static void init();
    static void enableOverdrive();
};
#endif
