#include "riscv_vector.h"
 void test_vsxe_v_i16m1(int16_t *base, vuint16m1_t index, vint16m1_t value){
	vsxe_v_i16m1(base,index,value);
}
 void test_vsxe_v_i16m2(int16_t *base, vuint16m2_t index, vint16m2_t value){
	vsxe_v_i16m2(base,index,value);
}
 void test_vsxe_v_i16m4(int16_t *base, vuint16m4_t index, vint16m4_t value){
	vsxe_v_i16m4(base,index,value);
}
 void test_vsxe_v_i16m8(int16_t *base, vuint16m8_t index, vint16m8_t value){
	vsxe_v_i16m8(base,index,value);
}
