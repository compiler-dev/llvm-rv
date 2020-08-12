#include "riscv_vector.h"
 vmask_t test_vmsof_m_m(vmask_t mask, vmask_t op1){
	return vmsof_m_m(mask,op1);
}