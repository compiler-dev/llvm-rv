#include "riscv_vector.h"
void test_vsxe_v_u16m1(uint16_t *base, vuint16m1_t index, vuint16m1_t value){
	vsxe_v_u16m1(base,index,value);
}
 void test_vsxe_v_u16m2(uint16_t *base, vuint16m2_t index, vuint16m2_t value){
	vsxe_v_u16m2(base,index,value);
}
 void test_vsxe_v_u16m4(uint16_t *base, vuint16m4_t index, vuint16m4_t value){
	vsxe_v_u16m4(base,index,value);
}
 void test_vsxe_v_u16m8(uint16_t *base, vuint16m8_t index, vuint16m8_t value){
	vsxe_v_u16m8(base,index,value);
}
