#include "riscv_vector.h"
vint32m1_t test_vslide1up_vx_i32m1_m(vmask_t mask,vint32m1_t op1,int32_t offset){
	return vslide1up_vx_i32m1_m(mask,op1,offset);
}

 vint32m2_t test_vslide1up_vx_i32m2_m(vmask_t mask,vint32m2_t op1,int32_t offset){
	return vslide1up_vx_i32m2_m(mask,op1,offset);
}

 vint32m4_t test_vslide1up_vx_i32m4_m(vmask_t mask,vint32m4_t op1,int32_t offset){
	return vslide1up_vx_i32m4_m(mask,op1,offset);
}

 vint32m8_t test_vslide1up_vx_i32m8_m(vmask_t mask,vint32m8_t op1,int32_t offset){
	return vslide1up_vx_i32m8_m(mask,op1,offset);
}


