#include "riscv_vector.h"
void test_vsuxe_v_i32m1(int32_t *base, vuint32m1_t index, vint32m1_t value){
	vsuxe_v_i32m1(base,index,value);
}
 void test_vsuxe_v_i32m2(int32_t *base, vuint32m2_t index, vint32m2_t value){
	vsuxe_v_i32m2(base,index,value);
}
 void test_vsuxe_v_i32m4(int32_t *base, vuint32m4_t index, vint32m4_t value){
	vsuxe_v_i32m4(base,index,value);
}
 void test_vsuxe_v_i32m8(int32_t *base, vuint32m8_t index, vint32m8_t value){
	vsuxe_v_i32m8(base,index,value);
}