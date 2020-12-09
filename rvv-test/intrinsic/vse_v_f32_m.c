#include "riscv_vector.h"
void test_vse_v_f32m1_m(vmask_t mask, float32_t *base, vfloat32m1_t value){
	vse_v_f32m1_m(mask,base,value);
}
 void test_vse_v_f32m2_m(vmask_t mask, float32_t *base, vfloat32m2_t value){
	vse_v_f32m2_m(mask,base,value);
}
 void test_vse_v_f32m4_m(vmask_t mask, float32_t *base, vfloat32m4_t value){
	vse_v_f32m4_m(mask,base,value);
}
 void test_vse_v_f32m8_m(vmask_t mask, float32_t *base, vfloat32m8_t value){
	vse_v_f32m8_m(mask,base,value);
}
