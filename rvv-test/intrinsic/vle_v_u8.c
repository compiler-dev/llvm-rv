#include "riscv_vector.h"
vuint8m1_t test_vle_v_u8m1(const uint8_t *base){
	return vle_v_u8m1(base);
}
 vuint8m2_t test_vle_v_u8m2(const uint8_t *base){
	return vle_v_u8m2(base);
}
 vuint8m4_t test_vle_v_u8m4(const uint8_t *base){
	return vle_v_u8m4(base);
}
 vuint8m8_t test_vle_v_u8m8(const uint8_t *base){
	return vle_v_u8m8(base);
}