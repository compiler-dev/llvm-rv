#include "riscv_vector.h"
vmask_t test_vmadc_vi_i32m1(vint32m1_t op1){
	return vmadc_vi_i32m1(op1,1);
}
vmask_t test_vmadc_vi_i32m2(vint32m2_t op1){
	return vmadc_vi_i32m2(op1,1);
}
vmask_t test_vmadc_vi_i32m4(vint32m4_t op1){
	return vmadc_vi_i32m4(op1,1);
}
vmask_t test_vmadc_vi_i32m8(vint32m8_t op1){
	return vmadc_vi_i32m8(op1,1);
}