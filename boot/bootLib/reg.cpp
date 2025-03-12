#include <reg.hpp>
Reg32Base::Reg32Base(uint32_t registerAddress) : reg{reinterpret_cast<uint32_t *>(registerAddress)} {};
uint32_t *Reg32Base::getReg() const { return const_cast<uint32_t *>(this->reg); }
uint32_t Reg32Base::readBase(void) const { return *this->reg; }
void Reg32Base::writeBase(uint32_t value) const { *this->reg = value; }

uint32_t Reg32_RO::read() const { return this->readBase(); }

void Reg32_WO::write(uint32_t value) const { this->writeBase(value); }

uint32_t Reg32::read() const { return *this->reg; }
void Reg32::write(uint32_t value) const { this->writeBase(value); }
