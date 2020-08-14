#include "riscv_vector.h"
void test_vse_v_i16m1(vint16m1_t value, int16_t *base){
	vse_v_i16m1(value,base);
}
 void test_vse_v_i16m2(vint16m2_t value, int16_t *base){
	vse_v_i16m2(value,base);
}
 void test_vse_v_i16m4(vint16m4_t value, int16_t *base){
	vse_v_i16m4(value,base);
}
 void test_vse_v_i16m8(vint16m8_t value, int16_t *base){
	vse_v_i16m8(value,base);
}