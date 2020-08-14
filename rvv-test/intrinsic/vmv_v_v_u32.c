#include "riscv_vector.h"
 vuint32m1_t test_vmv_v_v_u32m1(vuint32m1_t src){
	return vmv_v_v_u32m1(src);
}
 vuint32m2_t test_vmv_v_v_u32m2(vuint32m2_t src){
	return vmv_v_v_u32m2(src);
}
 vuint32m4_t test_vmv_v_v_u32m4(vuint32m4_t src){
	return vmv_v_v_u32m4(src);
}
 vuint32m8_t test_vmv_v_v_u32m8(vuint32m8_t src){
	return vmv_v_v_u32m8(src);
}