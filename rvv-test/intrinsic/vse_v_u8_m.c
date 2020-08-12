#include "riscv_vector.h"
void test_vse_v_u8m1_m(vmask_t mask,vuint8m1_t value, uint8_t  *base){
	vse_v_u8m1_m(mask,value,base);
}
 void test_vse_v_u8m2_m(vmask_t mask,vuint8m2_t value, uint8_t  *base){
	vse_v_u8m2_m(mask,value,base);
}
 void test_vse_v_u8m4_m(vmask_t mask,vuint8m4_t value, uint8_t  *base){
	vse_v_u8m4_m(mask,value,base);
}
 void test_vse_v_u8m8_m(vmask_t mask,vuint8m8_t value, uint8_t  *base){
	vse_v_u8m8_m(mask,value,base);
}