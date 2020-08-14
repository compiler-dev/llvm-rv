#include "riscv_vector.h"
void test_vsxe_v_f32m1_m(vmask_t mask,float32_t *base, vuint32m1_t index, vfloat32m1_t value){
	vsxe_v_f32m1_m(mask,base,index,value);
}
 void test_vsxe_v_f32m2_m(vmask_t mask,float32_t *base, vuint32m2_t index, vfloat32m2_t value){
	vsxe_v_f32m2_m(mask,base,index,value);
}
 void test_vsxe_v_f32m4_m(vmask_t mask,float32_t *base, vuint32m4_t index, vfloat32m4_t value){
	vsxe_v_f32m4_m(mask,base,index,value);
}
 void test_vsxe_v_f32m8_m(vmask_t mask,float32_t *base, vuint32m8_t index, vfloat32m8_t value){
	vsxe_v_f32m8_m(mask,base,index,value);
}
