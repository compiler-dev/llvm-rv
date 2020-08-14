#include "riscv_vector.h"
 vuint16m1_t test_vleff_v_u16m1_m(vmask_t mask, const uint16_t *base){
	return vleff_v_u16m1_m(mask,base);
}
 vuint16m2_t test_vleff_v_u16m2_m(vmask_t mask, const uint16_t *base){
	return vleff_v_u16m2_m(mask,base);
}
 vuint16m4_t test_vleff_v_u16m4_m(vmask_t mask, const uint16_t *base){
	return vleff_v_u16m4_m(mask,base);
}
 vuint16m8_t test_vleff_v_u16m8_m(vmask_t mask, const uint16_t *base){
	return vleff_v_u16m8_m(mask,base);
}