#include "riscv_vector.h"
void test_vse_v_i16m1_m(vmask_t mask,vint16m1_t value, int16_t *base){
	vse_v_i16m1_m(mask,value,base);
}
 void test_vse_v_i16m2_m(vmask_t mask,vint16m2_t value, int16_t *base){
	vse_v_i16m2_m(mask,value,base);
}
 void test_vse_v_i16m4_m(vmask_t mask,vint16m4_t value, int16_t *base){
	vse_v_i16m4_m(mask,value,base);
}
 void test_vse_v_i16m8_m(vmask_t mask,vint16m8_t value, int16_t *base){
	vse_v_i16m8_m(mask,value,base);
}