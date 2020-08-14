#include "riscv_vector.h"
 void test_vse_v_i8m1_m(vmask_t mask,vint8m1_t value, int8_t *base){
	vse_v_i8m1_m(mask,value,base);
}
 void test_vse_v_i8m2_m(vmask_t mask,vint8m2_t value, int8_t *base){
	vse_v_i8m2_m(mask,value,base);
}
 void test_vse_v_i8m4_m(vmask_t mask,vint8m4_t value, int8_t *base){
	vse_v_i8m4_m(mask,value,base);
}
 void test_vse_v_i8m8_m(vmask_t mask,vint8m8_t value, int8_t *base){
	vse_v_i8m8_m(mask,value,base);
}