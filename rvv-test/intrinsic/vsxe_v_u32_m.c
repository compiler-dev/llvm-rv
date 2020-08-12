#include "riscv_vector.h"
void test_vsxe_v_u32m1_m(vmask_t mask,uint32_t *base, vuint32m1_t index, vuint32m1_t value){
	vsxe_v_u32m1_m(mask,base,index,value);
}
 void test_vsxe_v_u32m2_m(vmask_t mask,uint32_t *base, vuint32m2_t index, vuint32m2_t value){
	vsxe_v_u32m2_m(mask,base,index,value);
}
 void test_vsxe_v_u32m4_m(vmask_t mask,uint32_t *base, vuint32m4_t index, vuint32m4_t value){
	vsxe_v_u32m4_m(mask,base,index,value);
}
 void test_vsxe_v_u32m8_m(vmask_t mask,uint32_t *base, vuint32m8_t index, vuint32m8_t value){
	vsxe_v_u32m8_m(mask,base,index,value);
}
