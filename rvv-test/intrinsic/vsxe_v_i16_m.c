#include "riscv_vector.h"
void test_vsxe_v_i16m1_m(vmask_t mask,int16_t *base, vuint16m1_t index, vint16m1_t value){
	vsxe_v_i16m1_m(mask,base,index,value);
}
 void test_vsxe_v_i16m2_m(vmask_t mask,int16_t *base, vuint16m2_t index, vint16m2_t value){
	vsxe_v_i16m2_m(mask,base,index,value);
}
 void test_vsxe_v_i16m4_m(vmask_t mask,int16_t *base, vuint16m4_t index, vint16m4_t value){
	vsxe_v_i16m4_m(mask,base,index,value);
}
 void test_vsxe_v_i16m8_m(vmask_t mask,int16_t *base, vuint16m8_t index, vint16m8_t value){
	vsxe_v_i16m8_m(mask,base,index,value);
}