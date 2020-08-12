#include "riscv_vector.h"
void test_vsxe_v_u32m1(uint32_t *base, vuint32m1_t index, vuint32m1_t value){
	vsxe_v_u32m1(base,index,value);
}
 void test_vsxe_v_u32m2(uint32_t *base, vuint32m2_t index, vuint32m2_t value){
	vsxe_v_u32m2(base,index,value);
}
 void test_vsxe_v_u32m4(uint32_t *base, vuint32m4_t index, vuint32m4_t value){
	vsxe_v_u32m4(base,index,value);
}
 void test_vsxe_v_u32m8(uint32_t *base, vuint32m8_t index, vuint32m8_t value){
	vsxe_v_u32m8(base,index,value);
}
