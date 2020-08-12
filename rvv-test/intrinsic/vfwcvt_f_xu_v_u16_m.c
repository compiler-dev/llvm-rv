#include "riscv_vector.h"
 vfloat32m2_t test_vfwcvt_f_xu_v_u16m1_m(vmask_t mask, vuint16m1_t op1){
	return vfwcvt_f_xu_v_u16m1_m(mask,op1);
}

 vfloat32m4_t test_vfwcvt_f_xu_v_u16m2_m(vmask_t mask, vuint16m2_t op1){
	return vfwcvt_f_xu_v_u16m2_m(mask,op1);
}

 vfloat32m8_t test_vfwcvt_f_xu_v_u16m4_m(vmask_t mask, vuint16m4_t op1){
	return vfwcvt_f_xu_v_u16m4_m(mask,op1);
}