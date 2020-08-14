#include "riscv_vector.h"
void test_vsuxe_v_i32m1_m(vmask_t mask,int32_t *base, vuint32m1_t index, vint32m1_t value){
	vsuxe_v_i32m1_m(mask,base,index,value);
}
 void test_vsuxe_v_i32m2_m(vmask_t mask,int32_t *base, vuint32m2_t index, vint32m2_t value){
	vsuxe_v_i32m2_m(mask,base,index,value);
}
 void test_vsuxe_v_i32m4_m(vmask_t mask,int32_t *base, vuint32m4_t index, vint32m4_t value){
	vsuxe_v_i32m4_m(mask,base,index,value);
}
 void test_vsuxe_v_i32m8_m(vmask_t mask,int32_t *base, vuint32m8_t index, vint32m8_t value){
	vsuxe_v_i32m8_m(mask,base,index,value);
}