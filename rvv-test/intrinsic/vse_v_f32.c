#include "riscv_vector.h"
void test_vse_v_f32m1(vfloat32m1_t value, float32_t *base){
	vse_v_f32m1(value,base);
}
 void test_vse_v_f32m2(vfloat32m2_t value, float32_t *base){
	vse_v_f32m2(value,base);
}
 void test_vse_v_f32m4(vfloat32m4_t value, float32_t *base){
	vse_v_f32m4(value,base);
}
 void test_vse_v_f32m8(vfloat32m8_t value, float32_t *base){
	vse_v_f32m8(value,base);
}