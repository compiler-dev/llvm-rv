#include "riscv_vector.h"
vuint32m1_t test_vlse_v_u32m1_m(vmask_t mask, const uint32_t *base, const int32_t stride){
	return vlse_v_u32m1_m(mask,base,stride);
}
 vuint32m2_t test_vlse_v_u32m2_m(vmask_t mask, const uint32_t *base, const int32_t stride){
	return vlse_v_u32m2_m(mask,base,stride);
}
 vuint32m4_t test_vlse_v_u32m4_m(vmask_t mask, const uint32_t *base, const int32_t stride){
	return vlse_v_u32m4_m(mask,base,stride);
}
 vuint32m8_t test_vlse_v_u32m8_m(vmask_t mask, const uint32_t *base, const int32_t stride){
	return vlse_v_u32m8_m(mask,base,stride);
}
