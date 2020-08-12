#include "riscv_vector.h"
vuint8m1_t test_vlse_v_u8m1(const uint8_t *base, const int32_t stride){
	return vlse_v_u8m1(base,stride);
}
 vuint8m2_t test_vlse_v_u8m2(const uint8_t *base, const int32_t stride){
	return vlse_v_u8m2(base,stride);
}
 vuint8m4_t test_vlse_v_u8m4(const uint8_t *base, const int32_t stride){
	return vlse_v_u8m4(base,stride);
}
 vuint8m8_t test_vlse_v_u8m8(const uint8_t *base, const int32_t stride){
	return vlse_v_u8m8(base,stride);
}
