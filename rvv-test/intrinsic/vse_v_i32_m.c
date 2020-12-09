#include "riscv_vector.h"
void test_vse_v_i32m1_m(vmask_t mask, int32_t *base, vint32m1_t value){
	vse_v_i32m1_m(mask,base,value);
}
 void test_vse_v_i32m2_m(vmask_t mask, int32_t *base, vint32m2_t value){
	vse_v_i32m2_m(mask,base,value);
}
 void test_vse_v_i32m4_m(vmask_t mask, int32_t *base, vint32m4_t value){
	vse_v_i32m4_m(mask,base,value);
}
 void test_vse_v_i32m8_m(vmask_t mask, int32_t *base, vint32m8_t value){
	vse_v_i32m8_m(mask,base,value);
}
