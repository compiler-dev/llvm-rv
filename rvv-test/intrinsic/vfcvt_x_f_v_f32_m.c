#include "riscv_vector.h"
 vint32m1_t test_vfcvt_x_f_v_f32m1_m(vmask_t mask, vfloat32m1_t op1){
	return vfcvt_x_f_v_f32m1_m(mask,op1);
}

 vint32m2_t test_vfcvt_x_f_v_f32m2_m(vmask_t mask, vfloat32m2_t op1){
	return vfcvt_x_f_v_f32m2_m(mask,op1);
}

 vint32m4_t test_vfcvt_x_f_v_f32m4_m(vmask_t mask, vfloat32m4_t op1){
	return vfcvt_x_f_v_f32m4_m(mask,op1);
}

 vint32m8_t test_vfcvt_x_f_v_f32m8_m(vmask_t mask, vfloat32m8_t op1){
	return vfcvt_x_f_v_f32m8_m(mask,op1);
}