#include "riscv_vector.h"
void test_vsuxe_v_u8m1(uint8_t *base, vuint8m1_t index, vuint8m1_t value){
	vsuxe_v_u8m1(base,index,value);
}
 void test_vsuxe_v_u8m2(uint8_t *base, vuint8m2_t index, vuint8m2_t value){
	vsuxe_v_u8m2(base,index,value);
}
 void test_vsuxe_v_u8m4(uint8_t *base, vuint8m4_t index, vuint8m4_t value){
	vsuxe_v_u8m4(base,index,value);
}
 void test_vsuxe_v_u8m8(uint8_t *base, vuint8m8_t index, vuint8m8_t value){
	vsuxe_v_u8m8(base,index,value);
}