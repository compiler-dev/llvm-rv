#include "riscv_vector.h"
vmask_t test_vmadc_vi_i8m1(vint8m1_t op1){
	return vmadc_vi_i8m1(op1,1);
}
vmask_t test_vmadc_vi_i8m2(vint8m2_t op1){
	return vmadc_vi_i8m2(op1,1);
}
vmask_t test_vmadc_vi_i8m4(vint8m4_t op1){
	return vmadc_vi_i8m4(op1,1);
}
vmask_t test_vmadc_vi_i8m8(vint8m8_t op1){
	return vmadc_vi_i8m8(op1,1);
}