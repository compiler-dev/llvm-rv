#include "riscv_vector.h"
void test_vse_v_u16m1_m(vmask_t mask,vuint16m1_t value, uint16_t  *base){
	vse_v_u16m1_m(mask,value,base);
}
 void test_vse_v_u16m2_m(vmask_t mask,vuint16m2_t value, uint16_t  *base){
	vse_v_u16m2_m(mask,value,base);
}
 void test_vse_v_u16m4_m(vmask_t mask,vuint16m4_t value, uint16_t  *base){
	vse_v_u16m4_m(mask,value,base);
}
 void test_vse_v_u16m8_m(vmask_t mask,vuint16m8_t value, uint16_t  *base){
	vse_v_u16m8_m(mask,value,base);
}