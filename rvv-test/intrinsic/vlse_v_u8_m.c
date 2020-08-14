#include "riscv_vector.h"
vuint8m1_t test_vlse_v_u8m1_m(vmask_t mask, const uint8_t *base, const int32_t stride){
	return vlse_v_u8m1_m(mask,base,stride);
}
 vuint8m2_t test_vlse_v_u8m2_m(vmask_t mask, const uint8_t *base, const int32_t stride){
	return vlse_v_u8m2_m(mask,base,stride);
}
 vuint8m4_t test_vlse_v_u8m4_m(vmask_t mask, const uint8_t *base, const int32_t stride){
	return vlse_v_u8m4_m(mask,base,stride);
}
 vuint8m8_t test_vlse_v_u8m8_m(vmask_t mask, const uint8_t *base, const int32_t stride){
	return vlse_v_u8m8_m(mask,base,stride);
}
