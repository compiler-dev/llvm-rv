#include "riscv_vector.h"
 vint8m1_t test_vlxe_v_i8m1(const int8_t *base, vuint8m1_t index){
	return vlxe_v_i8m1(base,index);
}
 vint8m2_t test_vlxe_v_i8m2(const int8_t *base, vuint8m2_t index){
	return vlxe_v_i8m2(base,index);
}
 vint8m4_t test_vlxe_v_i8m4(const int8_t *base, vuint8m4_t index){
	return vlxe_v_i8m4(base,index);
}
 vint8m8_t test_vlxe_v_i8m8(const int8_t *base, vuint8m8_t index){
	return vlxe_v_i8m8(base,index);
}