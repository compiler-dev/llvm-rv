#include "riscv_vector.h"
vuint32m1_t test_vssrl_vi_u32m1(vuint32m1_t op1){
	return vssrl_vi_u32m1(op1,1);
}
 vuint32m2_t test_vssrl_vi_u32m2(vuint32m2_t op1){
	return vssrl_vi_u32m2(op1,1);
}
 vuint32m4_t test_vssrl_vi_u32m4(vuint32m4_t op1){
	return vssrl_vi_u32m4(op1,1);
}
 vuint32m8_t test_vssrl_vi_u32m8(vuint32m8_t op1){
	return vssrl_vi_u32m8(op1,1);
}