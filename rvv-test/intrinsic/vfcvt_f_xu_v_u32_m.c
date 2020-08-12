#include "riscv_vector.h"
 vfloat32m1_t test_vfcvt_f_xu_v_u32m1_m(vmask_t mask, vuint32m1_t op1){
	return vfcvt_f_xu_v_u32m1_m(mask,op1);
}

 vfloat32m2_t test_vfcvt_f_xu_v_u32m2_m(vmask_t mask, vuint32m2_t op1){
	return vfcvt_f_xu_v_u32m2_m(mask,op1);
}

 vfloat32m4_t test_vfcvt_f_xu_v_u32m4_m(vmask_t mask, vuint32m4_t op1){
	return vfcvt_f_xu_v_u32m4_m(mask,op1);
}

 vfloat32m8_t test_vfcvt_f_xu_v_u32m8_m(vmask_t mask, vuint32m8_t op1){
	return vfcvt_f_xu_v_u32m8_m(mask,op1);
}