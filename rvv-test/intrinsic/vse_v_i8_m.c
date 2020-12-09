#include "riscv_vector.h"
 void test_vse_v_i8m1_m(vmask_t mask, int8_t *base, vint8m1_t value){
	vse_v_i8m1_m(mask,base,value);
}
 void test_vse_v_i8m2_m(vmask_t mask, int8_t *base, vint8m2_t value){
	vse_v_i8m2_m(mask,base,value);
}
 void test_vse_v_i8m4_m(vmask_t mask, int8_t *base, vint8m4_t value){
	vse_v_i8m4_m(mask,base,value);
}
 void test_vse_v_i8m8_m(vmask_t mask, int8_t *base, vint8m8_t value){
	vse_v_i8m8_m(mask,base,value);
}
