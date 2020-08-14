#include "riscv_vector.h"
 vfloat32m2_t test_vfwcvt_f_xu_v_u16m1(vuint16m1_t op1){
	return vfwcvt_f_xu_v_u16m1(op1);
}

 vfloat32m4_t test_vfwcvt_f_xu_v_u16m2(vuint16m2_t op1){
	return vfwcvt_f_xu_v_u16m2(op1);
}

 vfloat32m8_t test_vfwcvt_f_xu_v_u16m4(vuint16m4_t op1){
	return vfwcvt_f_xu_v_u16m4(op1);
}