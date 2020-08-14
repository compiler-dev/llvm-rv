#include "riscv_vector.h"
 vint8m1_t test_vlse_v_i8m1(const int8_t *base, const int32_t stride){
	return vlse_v_i8m1(base,stride);
}
 vint8m2_t test_vlse_v_i8m2(const int8_t *base, const int32_t stride){
	return vlse_v_i8m2(base,stride);
}
 vint8m4_t test_vlse_v_i8m4(const int8_t *base, const int32_t stride){
	return vlse_v_i8m4(base,stride);
}
 vint8m8_t test_vlse_v_i8m8(const int8_t *base, const int32_t stride){
	return vlse_v_i8m8(base,stride);
}