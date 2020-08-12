#include "riscv_vector.h"
vint16m1_t test_vlse_v_i16m1_m(vmask_t mask, const int16_t *base, const int32_t stride){
	return vlse_v_i16m1_m(mask,base,stride);
}
 vint16m2_t test_vlse_v_i16m2_m(vmask_t mask, const int16_t *base, const int32_t stride){
	return vlse_v_i16m2_m(mask,base,stride);
}
 vint16m4_t test_vlse_v_i16m4_m(vmask_t mask, const int16_t *base, const int32_t stride){
	return vlse_v_i16m4_m(mask,base,stride);
}
 vint16m8_t test_vlse_v_i16m8_m(vmask_t mask, const int16_t *base, const int32_t stride){
	return vlse_v_i16m8_m(mask,base,stride);
}
