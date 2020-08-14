#include "riscv_vector.h"
vuint16m1_t test_vlse_v_u16m1(const uint16_t *base, const int32_t stride){
	return vlse_v_u16m1(base,stride);
}
 vuint16m2_t test_vlse_v_u16m2(const uint16_t *base, const int32_t stride){
	return vlse_v_u16m2(base,stride);
}
 vuint16m4_t test_vlse_v_u16m4(const uint16_t *base, const int32_t stride){
	return vlse_v_u16m4(base,stride);
}
 vuint16m8_t test_vlse_v_u16m8(const uint16_t *base, const int32_t stride){
	return vlse_v_u16m8(base,stride);
}
