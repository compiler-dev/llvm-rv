#include "riscv_vector.h"
 vint32m1_t test_vlse_v_i32m1_m(vmask_t mask, const int32_t *base, const int32_t stride){
	return vlse_v_i32m1_m(mask,base,stride);
}
 vint32m2_t test_vlse_v_i32m2_m(vmask_t mask, const int32_t *base, const int32_t stride){
	return vlse_v_i32m2_m(mask,base,stride);
}
 vint32m4_t test_vlse_v_i32m4_m(vmask_t mask, const int32_t *base, const int32_t stride){
	return vlse_v_i32m4_m(mask,base,stride);
}
 vint32m8_t test_vlse_v_i32m8_m(vmask_t mask, const int32_t *base, const int32_t stride){
	return vlse_v_i32m8_m(mask,base,stride);
}
