#include "riscv_vector.h"
 vfloat32m2_t test_vfwcvt_f_x_v_i16m1(vint16m1_t op1){
	return vfwcvt_f_x_v_i16m1(op1);
}

 vfloat32m4_t test_vfwcvt_f_x_v_i16m2(vint16m2_t op1){
	return vfwcvt_f_x_v_i16m2(op1);
}

 vfloat32m8_t test_vfwcvt_f_x_v_i16m4(vint16m4_t op1){
	return vfwcvt_f_x_v_i16m4(op1);
}