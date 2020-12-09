#include "riscv_vector.h"
void test_vse_v_u16m1_m(vmask_t mask, uint16_t  *base, vuint16m1_t value){
	vse_v_u16m1_m(mask,base,value);
}
 void test_vse_v_u16m2_m(vmask_t mask, uint16_t  *base, vuint16m2_t value){
	vse_v_u16m2_m(mask,base,value);
}
 void test_vse_v_u16m4_m(vmask_t mask, uint16_t  *base, vuint16m4_t value){
	vse_v_u16m4_m(mask,base,value);
}
 void test_vse_v_u16m8_m(vmask_t mask, uint16_t  *base, vuint16m8_t value){
	vse_v_u16m8_m(mask,base,value);
}
