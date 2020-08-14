#include "riscv_vector.h"
void test_vse_v_u32m1_m(vmask_t mask,vuint32m1_t value, uint32_t *base){
	vse_v_u32m1_m(mask,value,base);
}
 void test_vse_v_u32m2_m(vmask_t mask,vuint32m2_t value, uint32_t *base){
	vse_v_u32m2_m(mask,value,base);
}
 void test_vse_v_u32m4_m(vmask_t mask,vuint32m4_t value, uint32_t *base){
	vse_v_u32m4_m(mask,value,base);
}
 void test_vse_v_u32m8_m(vmask_t mask,vuint32m8_t value, uint32_t *base){
	vse_v_u32m8_m(mask,value,base);
}