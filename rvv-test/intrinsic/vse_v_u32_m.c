#include "riscv_vector.h"
void test_vse_v_u32m1_m(vmask_t mask, uint32_t *base, vuint32m1_t value){
	vse_v_u32m1_m(mask,base,value);
}
 void test_vse_v_u32m2_m(vmask_t mask, uint32_t *base, vuint32m2_t value){
	vse_v_u32m2_m(mask,base,value);
}
 void test_vse_v_u32m4_m(vmask_t mask, uint32_t *base, vuint32m4_t value){
	vse_v_u32m4_m(mask,base,value);
}
 void test_vse_v_u32m8_m(vmask_t mask, uint32_t *base, vuint32m8_t value){
	vse_v_u32m8_m(mask,base,value);
}
