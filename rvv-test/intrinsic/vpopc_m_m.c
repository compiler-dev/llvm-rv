#include "riscv_vector.h"
 uint32_t test_vpopc_m_m(vmask_t mask, vmask_t op1){
	return vpopc_m_m(mask,op1);
}
