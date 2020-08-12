#include "riscv_vector.h"
 vint16m1_t test_vnsra_wi_i16m1(vint32m2_t op1){
	return vnsra_wi_i16m1(op1,1);
}
 vint16m2_t test_vnsra_wi_i16m2(vint32m4_t op1){
	return vnsra_wi_i16m2(op1,1);
}
 vint16m4_t test_vnsra_wi_i16m4(vint32m8_t op1){
	return vnsra_wi_i16m4(op1,1);
}
