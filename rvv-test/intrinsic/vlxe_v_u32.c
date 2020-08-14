#include "riscv_vector.h"
 vuint32m1_t test_vlxe_v_u32m1(const uint32_t *base, vuint32m1_t index){
	return vlxe_v_u32m1(base,index);
}
 vuint32m2_t test_vlxe_v_u32m2(const uint32_t *base, vuint32m2_t index){
	return vlxe_v_u32m2(base,index);
}
 vuint32m4_t test_vlxe_v_u32m4(const uint32_t *base, vuint32m4_t index){
	return vlxe_v_u32m4(base,index);
}
 vuint32m8_t test_vlxe_v_u32m8(const uint32_t *base, vuint32m8_t index){
	return vlxe_v_u32m8(base,index);
}