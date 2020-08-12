#include "riscv_vector.h"
void test_vse_v_u16m1(vuint16m1_t value, uint16_t *base){
	vse_v_u16m1(value,base);
}
 void test_vse_v_u16m2(vuint16m2_t value, uint16_t *base){
	vse_v_u16m2(value,base);
}
 void test_vse_v_u16m4(vuint16m4_t value, uint16_t *base){
	vse_v_u16m4(value,base);
}
 void test_vse_v_u16m8(vuint16m8_t value, uint16_t *base){
	vse_v_u16m8(value,base);
}