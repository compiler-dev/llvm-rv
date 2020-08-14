#include "riscv_vector.h"
vfloat32m1_t test_vlse_v_f32m1(const float32_t *base, const int32_t stride){
	return vlse_v_f32m1(base,stride);
}
 vfloat32m2_t test_vlse_v_f32m2(const float32_t *base, const int32_t stride){
	return vlse_v_f32m2(base,stride);
}
 vfloat32m4_t test_vlse_v_f32m4(const float32_t *base, const int32_t stride){
	return vlse_v_f32m4(base,stride);
}
 vfloat32m8_t test_vlse_v_f32m8(const float32_t *base, const int32_t stride){
	return vlse_v_f32m8(base,stride);
}
