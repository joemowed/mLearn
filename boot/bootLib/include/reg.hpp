#ifndef REG_INC_GRD
#define REG_INC_GRD
#include <cstdint>
#include <type_traits>

// Register base class.  Not to be used by user code
class Reg32Base {
  protected:
    volatile uint32_t *const reg;

  public:
    // Register base class.  Not to be used by user code
    explicit Reg32Base(uint32_t registerAddress);
    ~Reg32Base() = default;
    // Returns the currently used register
    uint32_t *getReg() const;
};
// read-only register
class Reg32_RO : virtual public Reg32Base {
  public:
    using Reg32Base::Reg32Base;
    uint32_t read() const;
};

// write-only register
class Reg32_WO : virtual public Reg32Base {
  public:
    using Reg32Base::Reg32Base;
    void write(uint32_t value) const;
};
// Read and write register
class Reg32 : public Reg32Base {
  public:
    using Reg32Base::Reg32Base;
    void write(uint32_t value) const;
    uint32_t read() const;
};
#endif
