#include "riscv_vector.h"
vint16m1_t test_vlxe_v_i16m1(const int16_t *base, vuint16m1_t index){
	return vlxe_v_i16m1(base,index);
}
 vint16m2_t test_vlxe_v_i16m2(const int16_t *base, vuint16m2_t index){
	return vlxe_v_i16m2(base,index);
}
 vint16m4_t test_vlxe_v_i16m4(const int16_t *base, vuint16m4_t index){
	return vlxe_v_i16m4(base,index);
}
 vint16m8_t test_vlxe_v_i16m8(const int16_t *base, vuint16m8_t index){
	return vlxe_v_i16m8(base,index);
}