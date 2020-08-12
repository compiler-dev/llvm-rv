#include "riscv_vector.h"
vint16m1_t test_vlse_v_i16m1(const int16_t *base, const int32_t stride){
	return vlse_v_i16m1(base,stride);
}
 vint16m2_t test_vlse_v_i16m2(const int16_t *base, const int32_t stride){
	return vlse_v_i16m2(base,stride);
}
 vint16m4_t test_vlse_v_i16m4(const int16_t *base, const int32_t stride){
	return vlse_v_i16m4(base,stride);
}
 vint16m8_t test_vlse_v_i16m8(const int16_t *base, const int32_t stride){
	return vlse_v_i16m8(base,stride);
}