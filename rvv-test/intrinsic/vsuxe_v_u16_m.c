#include "riscv_vector.h"
void test_vsuxe_v_u16m1_m(vmask_t mask,uint16_t *base, vuint16m1_t index, vuint16m1_t value){
	vsuxe_v_u16m1_m(mask,base,index,value);
}
 void test_vsuxe_v_u16m2_m(vmask_t mask,uint16_t *base, vuint16m2_t index, vuint16m2_t value){
	vsuxe_v_u16m2_m(mask,base,index,value);
}
 void test_vsuxe_v_u16m4_m(vmask_t mask,uint16_t *base, vuint16m4_t index, vuint16m4_t value){
	vsuxe_v_u16m4_m(mask,base,index,value);
}
 void test_vsuxe_v_u16m8_m(vmask_t mask,uint16_t *base, vuint16m8_t index, vuint16m8_t value){
	vsuxe_v_u16m8_m(mask,base,index,value);
}
