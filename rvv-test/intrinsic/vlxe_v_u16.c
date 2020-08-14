#include "riscv_vector.h"
vuint16m1_t test_vlxe_v_u16m1(const uint16_t *base, vuint16m1_t index){
	return vlxe_v_u16m1(base,index);
}
 vuint16m2_t test_vlxe_v_u16m2(const uint16_t *base, vuint16m2_t index){
	return vlxe_v_u16m2(base,index);
}
 vuint16m4_t test_vlxe_v_u16m4(const uint16_t *base, vuint16m4_t index){
	return vlxe_v_u16m4(base,index);
}
 vuint16m8_t test_vlxe_v_u16m8(const uint16_t *base, vuint16m8_t index){
	return vlxe_v_u16m8(base,index);
}