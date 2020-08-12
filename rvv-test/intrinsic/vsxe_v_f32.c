#include "riscv_vector.h"
void test_vsxe_v_f32m1(float32_t *base, vuint32m1_t index, vfloat32m1_t value){
	vsxe_v_f32m1(base,index,value);
}
 void test_vsxe_v_f32m2(float32_t *base, vuint32m2_t index, vfloat32m2_t value){
	vsxe_v_f32m2(base,index,value);
}
 void test_vsxe_v_f32m4(float32_t *base, vuint32m4_t index, vfloat32m4_t value){
	vsxe_v_f32m4(base,index,value);
}
 void test_vsxe_v_f32m8(float32_t *base, vuint32m8_t index, vfloat32m8_t value){
	vsxe_v_f32m8(base,index,value);
}