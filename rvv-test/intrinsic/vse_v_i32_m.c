#include "riscv_vector.h"
void test_vse_v_i32m1_m(vmask_t mask,vint32m1_t value, int32_t *base){
	vse_v_i32m1_m(mask,value,base);
}
 void test_vse_v_i32m2_m(vmask_t mask,vint32m2_t value, int32_t *base){
	vse_v_i32m2_m(mask,value,base);
}
 void test_vse_v_i32m4_m(vmask_t mask,vint32m4_t value, int32_t *base){
	vse_v_i32m4_m(mask,value,base);
}
 void test_vse_v_i32m8_m(vmask_t mask,vint32m8_t value, int32_t *base){
	vse_v_i32m8_m(mask,value,base);
}