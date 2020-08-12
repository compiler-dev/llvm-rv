#include "riscv_vector.h"
vint32m1_t test_vslide1up_vx_i32m1(vint32m1_t op1,int32_t offset){
	return vslide1up_vx_i32m1(op1,offset);
}

 vint32m2_t test_vslide1up_vx_i32m2(vint32m2_t op1,int32_t offset){
	return vslide1up_vx_i32m2(op1,offset);
}

 vint32m4_t test_vslide1up_vx_i32m4(vint32m4_t op1,int32_t offset){
	return vslide1up_vx_i32m4(op1,offset);
}

 vint32m8_t test_vslide1up_vx_i32m8(vint32m8_t op1,int32_t offset){
	return vslide1up_vx_i32m8(op1,offset);
}
