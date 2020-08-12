#include "riscv_vector.h"
int test(uint32_t avl)
{
	uint32_t vl;
	vl = vsetvli(avl,RVV_E16,RVV_M2,RVV_D4);
	return vsetvl(avl,vl);
}

