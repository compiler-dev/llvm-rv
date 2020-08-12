#include "riscv_vector.h"
void test_vsxe_v_i8m1_m(vmask_t mask,int8_t *base, vuint8m1_t index, vint8m1_t value){
	vsxe_v_i8m1_m(mask,base,index,value);
}
 void test_vsxe_v_i8m2_m(vmask_t mask,int8_t *base, vuint8m2_t index, vint8m2_t value){
	vsxe_v_i8m2_m(mask,base,index,value);
}
 void test_vsxe_v_i8m4_m(vmask_t mask,int8_t *base, vuint8m4_t index, vint8m4_t value){
	vsxe_v_i8m4_m(mask,base,index,value);
}
 void test_vsxe_v_i8m8_m(vmask_t mask,int8_t *base, vuint8m8_t index, vint8m8_t value){
	vsxe_v_i8m8_m(mask,base,index,value);
}