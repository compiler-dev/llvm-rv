#include "riscv_vector.h"
void test_vse_v_i8m1(vint8m1_t value, int8_t *base){
	vse_v_i8m1(value,base);
}
 void test_vse_v_i8m2(vint8m2_t value, int8_t *base){
	vse_v_i8m2(value,base);
}
 void test_vse_v_i8m4(vint8m4_t value, int8_t *base){
	vse_v_i8m4(value,base);
}
 void test_vse_v_i8m8(vint8m8_t value, int8_t *base){
	vse_v_i8m8(value,base);
}