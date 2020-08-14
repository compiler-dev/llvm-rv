#include "riscv_vector.h"
 void test_vsse_v_i32m1(int32_t *base, const int32_t stride, vint32m1_t value){
	vsse_v_i32m1(base,stride,value);
}
 void test_vsse_v_i32m2(int32_t *base, const int32_t stride, vint32m2_t value){
	vsse_v_i32m2(base,stride,value);
}
 void test_vsse_v_i32m4(int32_t *base, const int32_t stride, vint32m4_t value){
	vsse_v_i32m4(base,stride,value);
}
 void test_vsse_v_i32m8(int32_t *base, const int32_t stride, vint32m8_t value){
	vsse_v_i32m8(base,stride,value);
}
