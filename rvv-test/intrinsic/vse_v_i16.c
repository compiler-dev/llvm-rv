#include "riscv_vector.h"
void test_vse_v_i16m1(int16_t *base, vint16m1_t value){
	vse_v_i16m1(base,value);
}
 void test_vse_v_i16m2(int16_t *base, vint16m2_t value){
	vse_v_i16m2(base,value);
}
 void test_vse_v_i16m4(int16_t *base, vint16m4_t value){
	vse_v_i16m4(base,value);
}
 void test_vse_v_i16m8(int16_t *base, vint16m8_t value){
	vse_v_i16m8(base,value);
}
