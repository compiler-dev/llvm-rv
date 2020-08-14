#include "riscv_vector.h"
vfloat32m1_t test_vle_v_f32m1_m(vmask_t mask, const float32_t *base){
	return vle_v_f32m1_m(mask,base);
}
 vfloat32m2_t test_vle_v_f32m2_m(vmask_t mask, const float32_t *base){
	return vle_v_f32m2_m(mask,base);
}
 vfloat32m4_t test_vle_v_f32m4_m(vmask_t mask, const float32_t *base){
	return vle_v_f32m4_m(mask,base);
}
 vfloat32m8_t test_vle_v_f32m8_m(vmask_t mask, const float32_t *base){
	return vle_v_f32m8_m(mask,base);
}



