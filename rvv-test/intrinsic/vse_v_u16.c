#include "riscv_vector.h"
void test_vse_v_u16m1(uint16_t *base, vuint16m1_t value){
	vse_v_u16m1(base,value);
}
 void test_vse_v_u16m2(uint16_t *base, vuint16m2_t value){
	vse_v_u16m2(base,value);
}
 void test_vse_v_u16m4(uint16_t *base, vuint16m4_t value){
	vse_v_u16m4(base,value);
}
 void test_vse_v_u16m8(uint16_t *base, vuint16m8_t value){
	vse_v_u16m8(base,value);
}
