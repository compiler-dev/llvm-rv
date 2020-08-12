#include "riscv_vector.h"
 vuint32m1_t test_vmv_v_x_u32m1(uint32_t src){
	return vmv_v_x_u32m1(src);
}
 vuint32m2_t test_vmv_v_x_u32m2(uint32_t src){
	return vmv_v_x_u32m2(src);
}
 vuint32m4_t test_vmv_v_x_u32m4(uint32_t src){
	return vmv_v_x_u32m4(src);
}
 vuint32m8_t test_vmv_v_x_u32m8(uint32_t src){
	return vmv_v_x_u32m8(src);
}