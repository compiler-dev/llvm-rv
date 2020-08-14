#include "riscv_vector.h"
vfloat32m1_t test_vlse_v_f32m1_m(vmask_t mask, const float32_t *base, const int32_t stride){
	return vlse_v_f32m1_m(mask,base,stride);
}
 vfloat32m2_t test_vlse_v_f32m2_m(vmask_t mask, const float32_t *base, const int32_t stride){
	return vlse_v_f32m2_m(mask,base,stride);
}
 vfloat32m4_t test_vlse_v_f32m4_m(vmask_t mask, const float32_t *base, const int32_t stride){
	return vlse_v_f32m4_m(mask,base,stride);
}
 vfloat32m8_t test_vlse_v_f32m8_m(vmask_t mask, const float32_t *base, const int32_t stride){
	return vlse_v_f32m8_m(mask,base,stride);
}
