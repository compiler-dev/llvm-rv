#include "riscv_vector.h"
vuint32m1_t test_vlse_v_u32m1(const uint32_t *base, const int32_t stride){
	return vlse_v_u32m1(base,stride);
}
 vuint32m2_t test_vlse_v_u32m2(const uint32_t *base, const int32_t stride){
	return vlse_v_u32m2(base,stride);
}
 vuint32m4_t test_vlse_v_u32m4(const uint32_t *base, const int32_t stride){
	return vlse_v_u32m4(base,stride);
}
 vuint32m8_t test_vlse_v_u32m8(const uint32_t *base, const int32_t stride){
	return vlse_v_u32m8(base,stride);
}
