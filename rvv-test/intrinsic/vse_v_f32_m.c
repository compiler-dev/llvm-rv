#include "riscv_vector.h"
void test_vse_v_f32m1_m(vmask_t mask,vfloat32m1_t value, float32_t *base){
	vse_v_f32m1_m(mask,value,base);
}
 void test_vse_v_f32m2_m(vmask_t mask,vfloat32m2_t value, float32_t *base){
	vse_v_f32m2_m(mask,value,base);
}
 void test_vse_v_f32m4_m(vmask_t mask,vfloat32m4_t value, float32_t *base){
	vse_v_f32m4_m(mask,value,base);
}
 void test_vse_v_f32m8_m(vmask_t mask,vfloat32m8_t value, float32_t *base){
	vse_v_f32m8_m(mask,value,base);
}