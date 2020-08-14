#include "riscv_vector.h"
void test_vse_v_i32m1(vint32m1_t value, int32_t *base){
	vse_v_i32m1(value,base);
}
 void test_vse_v_i32m2(vint32m2_t value, int32_t *base){
	vse_v_i32m2(value,base);
}
 void test_vse_v_i32m4(vint32m4_t value, int32_t *base){
	vse_v_i32m4(value,base);
}
 void test_vse_v_i32m8(vint32m8_t value, int32_t *base){
	vse_v_i32m8(value,base);
}