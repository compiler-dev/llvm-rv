#include "riscv_vector.h"
void test_vse_v_i32m1(int32_t *base, vint32m1_t value){
	vse_v_i32m1(base,value);
}
 void test_vse_v_i32m2(int32_t *base, vint32m2_t value){
	vse_v_i32m2(base,value);
}
 void test_vse_v_i32m4(int32_t *base, vint32m4_t value){
	vse_v_i32m4(base,value);
}
 void test_vse_v_i32m8(int32_t *base, vint32m8_t value){
	vse_v_i32m8(base,value);
}
