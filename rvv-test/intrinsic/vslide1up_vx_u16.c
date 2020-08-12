#include "riscv_vector.h"
vuint16m1_t test_vslide1up_vx_u16m1(vuint16m1_t op1,uint32_t offset){
	return vslide1up_vx_u16m1(op1,offset);
}

 vuint16m2_t test_vslide1up_vx_u16m2(vuint16m2_t op1,uint32_t offset){
	return vslide1up_vx_u16m2(op1,offset);
}

 vuint16m4_t test_vslide1up_vx_u16m4(vuint16m4_t op1,uint32_t offset){
	return vslide1up_vx_u16m4(op1,offset);
}

 vuint16m8_t test_vslide1up_vx_u16m8(vuint16m8_t op1,uint32_t offset){
	return vslide1up_vx_u16m8(op1,offset);
}