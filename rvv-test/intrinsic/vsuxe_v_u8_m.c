#include "riscv_vector.h"
void test_vsuxe_v_u8m1_m(vmask_t mask,uint8_t *base, vuint8m1_t index, vuint8m1_t value){
	vsuxe_v_u8m1_m(mask,base,index,value);
}
 void test_vsuxe_v_u8m2_m(vmask_t mask,uint8_t *base, vuint8m2_t index, vuint8m2_t value){
	vsuxe_v_u8m2_m(mask,base,index,value);
}
 void test_vsuxe_v_u8m4_m(vmask_t mask,uint8_t *base, vuint8m4_t index, vuint8m4_t value){
	vsuxe_v_u8m4_m(mask,base,index,value);
}
 void test_vsuxe_v_u8m8_m(vmask_t mask,uint8_t *base, vuint8m8_t index, vuint8m8_t value){
	vsuxe_v_u8m8_m(mask,base,index,value);
}