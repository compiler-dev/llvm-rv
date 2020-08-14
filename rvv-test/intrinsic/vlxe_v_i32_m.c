#include "riscv_vector.h"
vint32m1_t test_vlxe_v_i32m1_m(vmask_t mask, const int32_t *base, vuint32m1_t index){
	return vlxe_v_i32m1_m(mask,base,index);
}
 vint32m2_t test_vlxe_v_i32m2_m(vmask_t mask, const int32_t *base, vuint32m2_t index){
	return vlxe_v_i32m2_m(mask,base,index);
}
 vint32m4_t test_vlxe_v_i32m4_m(vmask_t mask, const int32_t *base, vuint32m4_t index){
	return vlxe_v_i32m4_m(mask,base,index);
}
 vint32m8_t test_vlxe_v_i32m8_m(vmask_t mask, const int32_t *base, vuint32m8_t index){
	return vlxe_v_i32m8_m(mask,base,index);
}
