#include "riscv_vector.h"
 vuint8m1_t test_vsll_vi_u8m1(vuint8m1_t op1){
	return vsll_vi_u8m1(op1,1);
}
 vuint8m2_t test_vsll_vi_u8m2(vuint8m2_t op1){
	return vsll_vi_u8m2(op1,1);
}
 vuint8m4_t test_vsll_vi_u8m4(vuint8m4_t op1){
	return vsll_vi_u8m4(op1,1);
}
 vuint8m8_t test_vsll_vi_u8m8(vuint8m8_t op1){
	return vsll_vi_u8m8(op1,1);
}