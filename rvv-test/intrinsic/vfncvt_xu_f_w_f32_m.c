#include "riscv_vector.h"
 vuint16m1_t test_vfncvt_xu_f_w_f32m2_m(vmask_t mask, vfloat32m2_t op1){
	return vfncvt_xu_f_w_f32m2_m(mask,op1);
}

 vuint16m2_t test_vfncvt_xu_f_w_f32m4_m(vmask_t mask, vfloat32m4_t op1){
	return vfncvt_xu_f_w_f32m4_m(mask,op1);
}

 vuint16m4_t test_vfncvt_xu_f_w_f32m8_m(vmask_t mask, vfloat32m8_t op1){
	return vfncvt_xu_f_w_f32m8_m(mask,op1);
}
