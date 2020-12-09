#include "riscv_vector.h"
void test_vse_v_u8m1_m(vmask_t mask, uint8_t  *base, vuint8m1_t value){
	vse_v_u8m1_m(mask,base,value);
}
 void test_vse_v_u8m2_m(vmask_t mask, uint8_t  *base, vuint8m2_t value){
	vse_v_u8m2_m(mask,base,value);
}
 void test_vse_v_u8m4_m(vmask_t mask, uint8_t  *base, vuint8m4_t value){
	vse_v_u8m4_m(mask,base,value);
}
 void test_vse_v_u8m8_m(vmask_t mask, uint8_t  *base, vuint8m8_t value){
	vse_v_u8m8_m(mask,base,value);
}
