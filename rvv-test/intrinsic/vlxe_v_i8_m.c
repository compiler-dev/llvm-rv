#include "riscv_vector.h"
vint8m1_t test_vlxe_v_i8m1_m(vmask_t mask, const int8_t *base, vuint8m1_t index){
	return vlxe_v_i8m1_m(mask,base,index);
}
 vint8m2_t test_vlxe_v_i8m2_m(vmask_t mask, const int8_t *base, vuint8m2_t index){
	return vlxe_v_i8m2_m(mask,base,index);
}
 vint8m4_t test_test_vlxe_v_i8m4_m(vmask_t mask, const int8_t *base, vuint8m4_t index){
	return vlxe_v_i8m4_m(mask,base,index);
}
 vint8m8_t test_vlxe_v_i8m8_m(vmask_t mask, const int8_t *base, vuint8m8_t index){
	return vlxe_v_i8m8_m(mask,base,index);
}
