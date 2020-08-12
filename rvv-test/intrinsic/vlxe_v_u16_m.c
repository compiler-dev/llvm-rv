#include "riscv_vector.h"
vuint16m1_t test_vlxe_v_u16m1_m(vmask_t mask, const uint16_t *base, vuint16m1_t index){
	return vlxe_v_u16m1_m(mask,base,index);
}
 vuint16m2_t test_vlxe_v_u16m2_m(vmask_t mask, const uint16_t *base, vuint16m2_t index){
	return vlxe_v_u16m2_m(mask,base,index);
}
 vuint16m4_t test_vlxe_v_u16m4_m(vmask_t mask, const uint16_t *base, vuint16m4_t index){
	return vlxe_v_u16m4_m(mask,base,index);
}
 vuint16m8_t test_vlxe_v_u16m8_m(vmask_t mask, const uint16_t *base, vuint16m8_t index){
	return vlxe_v_u16m8_m(mask,base,index);
}

