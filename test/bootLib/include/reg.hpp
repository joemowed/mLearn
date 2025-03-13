#ifndef REG_INC_GRD
#define REG_INC_GRD

#define VAL2FLDRM(reg, field, value) ((((volatile uint32_t)reg) & (~(field##_Msk))) & ((((uint32_t)(value) << field##_Pos) & field##_Msk)))
#define VAL2FLDRMWRITE(reg, field, value) (reg = ((((uint32_t)reg) & (~(field##_Msk))) & ((((uint32_t)(value) << field##_Pos) & field##_Msk))))

#endif
