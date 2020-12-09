#include "riscv_vector.h"
void test_vse_v_f32m1(float32_t *base, vfloat32m1_t value){
	vse_v_f32m1(base,value);
}
 void test_vse_v_f32m2(float32_t *base, vfloat32m2_t value){
	vse_v_f32m2(base,value);
}
 void test_vse_v_f32m4(float32_t *base, vfloat32m4_t value){
	vse_v_f32m4(base,value);
}
 void test_vse_v_f32m8(float32_t *base, vfloat32m8_t value){
	vse_v_f32m8(base,value);
}
