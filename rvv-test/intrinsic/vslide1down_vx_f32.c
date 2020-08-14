#include "riscv_vector.h"
vfloat32m1_t test_vslide1down_vx_f32m1(vfloat32m1_t op1,uint32_t offset){
	return vslide1down_vx_f32m1(op1,offset);
}

 vfloat32m2_t test_vslide1down_vx_f32m2(vfloat32m2_t op1,uint32_t offset){
	return vslide1down_vx_f32m2(op1,offset);
}

 vfloat32m4_t test_vslide1down_vx_f32m4(vfloat32m4_t op1,uint32_t offset){
	return vslide1down_vx_f32m4(op1,offset);
}

 vfloat32m8_t test_vslide1down_vx_f32m8(vfloat32m8_t op1,uint32_t offset){
	return vslide1down_vx_f32m8(op1,offset);
}

