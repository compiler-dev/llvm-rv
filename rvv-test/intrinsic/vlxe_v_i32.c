#include "riscv_vector.h"
vint32m1_t test_vlxe_v_i32m1(const int32_t *base, vuint32m1_t index){
	return vlxe_v_i32m1(base,index);
}
 vint32m2_t test_vlxe_v_i32m2(const int32_t *base, vuint32m2_t index){
	return vlxe_v_i32m2(base,index);
}
 vint32m4_t test_vlxe_v_i32m4(const int32_t *base, vuint32m4_t index){
	return vlxe_v_i32m4(base,index);
}
 vint32m8_t test_vlxe_v_i32m8(const int32_t *base, vuint32m8_t index){
	return vlxe_v_i32m8(base,index);
}