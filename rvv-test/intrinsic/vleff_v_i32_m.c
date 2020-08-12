#include "riscv_vector.h"
 vint32m1_t test_vleff_v_i32m1_m(vmask_t mask, const int32_t *base){
	return vleff_v_i32m1_m(mask,base);
}
 vint32m2_t test_vleff_v_i32m2_m(vmask_t mask, const int32_t *base){
	return vleff_v_i32m2_m(mask,base);
}
 vint32m4_t test_vleff_v_i32m4_m(vmask_t mask, const int32_t *base){
	return vleff_v_i32m4_m(mask,base);
}
 vint32m8_t test_vleff_v_i32m8_m(vmask_t mask, const int32_t *base){
	return vleff_v_i32m8_m(mask,base);
}