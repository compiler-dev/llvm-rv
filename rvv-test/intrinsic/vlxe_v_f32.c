#include "riscv_vector.h"
vfloat32m1_t test_vlxe_v_f32m1(const float32_t *base, vuint32m1_t index){
	return vlxe_v_f32m1(base,index);
}
 vfloat32m2_t test_vlxe_v_f32m2(const float32_t *base, vuint32m2_t index){
	return vlxe_v_f32m2(base,index);
}
 vfloat32m4_t test_vlxe_v_f32m4(const float32_t *base, vuint32m4_t index){
	return vlxe_v_f32m4(base,index);
}
 vfloat32m8_t test_vlxe_v_f32m8(const float32_t *base, vuint32m8_t index){
	return vlxe_v_f32m8(base,index);
}