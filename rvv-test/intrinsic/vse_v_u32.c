#include "riscv_vector.h"
void test_vse_v_u32m1(vuint32m1_t value, uint32_t *base){
	vse_v_u32m1(value,base);
}
 void test_vse_v_u32m2(vuint32m2_t value, uint32_t *base){
	vse_v_u32m2(value,base);
}
 void test_vse_v_u32m4(vuint32m4_t value, uint32_t *base){
	vse_v_u32m4(value,base);
}
 void test_vse_v_u32m8(vuint32m8_t value, uint32_t *base){
	vse_v_u32m8(value,base);
}