#include "riscv_vector.h"
void test_vse_v_u32m1(uint32_t *base, vuint32m1_t value){
	vse_v_u32m1(base,value);
}
 void test_vse_v_u32m2(uint32_t *base, vuint32m2_t value){
	vse_v_u32m2(base,value);
}
 void test_vse_v_u32m4(uint32_t *base, vuint32m4_t value){
	vse_v_u32m4(base,value);
}
 void test_vse_v_u32m8(uint32_t *base, vuint32m8_t value){
	vse_v_u32m8(base,value);
}
