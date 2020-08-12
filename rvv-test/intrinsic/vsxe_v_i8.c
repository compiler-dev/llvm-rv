#include "riscv_vector.h"
void test_vsxe_v_i8m1(int8_t *base, vuint8m1_t index, vint8m1_t value){
	vsxe_v_i8m1(base,index,value);
}
 void test_vsxe_v_i8m2(int8_t *base, vuint8m2_t index, vint8m2_t value){
	vsxe_v_i8m2(base,index,value);
}
 void test_vsxe_v_i8m4(int8_t *base, vuint8m4_t index, vint8m4_t value){
	vsxe_v_i8m4(base,index,value);
}
 void test_vsxe_v_i8m8(int8_t *base, vuint8m8_t index, vint8m8_t value){
	vsxe_v_i8m8(base,index,value);
}
