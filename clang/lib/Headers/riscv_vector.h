//===---- riscv_vector.h - ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// RISCV Vector Intrinsic Reference
// Contributed by Hunan Compiler Information Technology Co., Ltd, 
// http://www.compiler-dev.com,Email: <info@compiler-dev.com>
//
//===----------------------------------------------------------------------===//

#ifndef __RISCV_VECTOR_H
#define __RISCV_VECTOR_H

#ifndef __RISCV_VECTOR__
#error "RISCV vector support not enabled"
#endif


typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef float float32_t;

//LMUL = 1
typedef __attribute__((riscv_vector_type(16))) int8_t vint8m1_t;
typedef __attribute__((riscv_vector_type(16))) uint8_t vuint8m1_t;
typedef __attribute__((riscv_vector_type(8))) int16_t vint16m1_t;
typedef __attribute__((riscv_vector_type(8))) uint16_t vuint16m1_t;
typedef __attribute__((riscv_vector_type(4))) int32_t vint32m1_t;
typedef __attribute__((riscv_vector_type(4))) uint32_t vuint32m1_t;
typedef __attribute__((riscv_vector_type(4))) float32_t vfloat32m1_t;

//mask
typedef __attribute__((riscv_vector_type(16))) uint8_t vmask_t;

#define __rv32 static __inline__ __attribute__((__always_inline__, __nodebug__))

typedef enum {
	RVV_E8 = 0,
	RVV_E16,
	RVV_E32,
	RVV_E64,
	RVV_E128,
	RVV_E256,
	RVV_E512,
	RVV_E1024,
} RISCV_VSEW_T;

typedef enum{
	RVV_M1 = 0,
	RVV_M2,
	RVV_M4,
	RVV_M8,
} RISCV_VLMUL_T;

typedef enum{
	RVV_D1 = 0,
	RVV_D2,
	RVV_D4,
	RVV_D8,
} RISCV_VEDIV_T;

//vsetvli vsetvl
#define vsetvli(avl,sew,lmul,ediv)  __extension__ ({\
		uint32_t __ret;\
		__ret = (uint32_t) __builtin_riscv_vsetvli(avl, ediv<<5 | sew << 2 | lmul);\
		__ret;\
		})

__rv32 uint32_t vsetvl(uint32_t avl, uint32_t vtypei){
	uint32_t __ret;
	__ret = (uint32_t)__builtin_riscv_vsetvl(avl,vtypei);
	return __ret;
}

uint32_t vsetvl_e32m1(uint32_t avl){
	return vsetvli(avl,RVV_E32,RVV_M1,RVV_D1);
}

uint32_t vsetvl_e16m1(uint32_t avl){
	return vsetvli(avl,RVV_E16,RVV_M1,RVV_D1);
}

uint32_t vsetvl_e8m1(uint32_t avl){
	return vsetvli(avl,RVV_E8,RVV_M1,RVV_D1);
}

/*************Vector Unit-Stride Load Functions***************/
__rv32 vint8m1_t vle_v_i8m1(const int8_t *base){
	return __builtin_riscv_vle_v_i8m1(base);
}

__rv32 vint16m1_t vle_v_i16m1(const int16_t *base){
	return __builtin_riscv_vle_v_i16m1(base);
}

__rv32 vint32m1_t vle_v_i32m1(const int32_t *base){
	return __builtin_riscv_vle_v_i32m1(base);
}

__rv32 vuint8m1_t vle_v_u8m1(const uint8_t *base){
	return __builtin_riscv_vle_v_u8m1(base);
}

__rv32 vuint16m1_t vle_v_u16m1(const uint16_t *base){
	return __builtin_riscv_vle_v_u16m1(base);
}

__rv32 vuint32m1_t vle_v_u32m1(const uint32_t *base){
	return __builtin_riscv_vle_v_u32m1(base);
}

__rv32 vfloat32m1_t vle_v_f32m1(const float32_t *base){
	return __builtin_riscv_vle_v_f32m1(base);
}

//masked functions
__rv32 vint8m1_t vle_v_i8m1_m(vmask_t mask, const int8_t *base){
	return __builtin_riscv_vle_v_i8m1_m(mask,base);
}

__rv32 vint16m1_t vle_v_i16m1_m(vmask_t mask, const int16_t *base){
	return __builtin_riscv_vle_v_i16m1_m(mask,base);
}

__rv32 vint32m1_t vle_v_i32m1_m(vmask_t mask, const int32_t *base){
	return __builtin_riscv_vle_v_i32m1_m(mask,base);
}

__rv32 vuint8m1_t vle_v_u8m1_m(vmask_t mask, const uint8_t *base){
	return __builtin_riscv_vle_v_u8m1_m(mask,base);
}

__rv32 vuint16m1_t vle_v_u16m1_m(vmask_t mask, const uint16_t *base){
	return __builtin_riscv_vle_v_u16m1_m(mask,base);
}

__rv32 vuint32m1_t vle_v_u32m1_m(vmask_t mask, const uint32_t *base){
	return __builtin_riscv_vle_v_u32m1_m(mask,base);
}

__rv32 vfloat32m1_t vle_v_f32m1_m(vmask_t mask, const float32_t *base){
	return __builtin_riscv_vle_v_f32m1_m(mask,base);
}

/*************Vector Unit-Stride Store Functions***************/
__rv32 void vse_v_i8m1(vint8m1_t value,int8_t *base){
	__builtin_riscv_vse_v_i8m1(value,base);
}

__rv32 void vse_v_i16m1(vint16m1_t value, int16_t *base){
	__builtin_riscv_vse_v_i16m1(value,base);
}

__rv32 void vse_v_i32m1(vint32m1_t value, int32_t *base){
	__builtin_riscv_vse_v_i32m1(value,base);
}

__rv32 void vse_v_u8m1(vuint8m1_t value, uint8_t *base){
	__builtin_riscv_vse_v_u8m1(value,base);
}

__rv32 void vse_v_u16m1(vuint16m1_t value, uint16_t *base){
	__builtin_riscv_vse_v_u16m1(value,base);
}

__rv32 void vse_v_u32m1(vuint32m1_t value, uint32_t *base){
	__builtin_riscv_vse_v_u32m1(value,base);
}

__rv32 void vse_v_f32m1(vfloat32m1_t value, float32_t *base){
	__builtin_riscv_vse_v_f32m1(value,base);
}

//masked functions
__rv32 void vse_v_i8m1_m(vmask_t mask,vint8m1_t value, int8_t *base){
	__builtin_riscv_vse_v_i8m1_m(mask,value,base);
}

__rv32 void vse_v_i16m1_m(vmask_t mask,vint16m1_t value, int16_t *base){
	__builtin_riscv_vse_v_i16m1_m(mask,value,base);
}

__rv32 void vse_v_i32m1_m(vmask_t mask,vint32m1_t value, int32_t *base){
	__builtin_riscv_vse_v_i32m1_m(mask,value,base);
}

__rv32 void vse_v_u8m1_m(vmask_t mask,vuint8m1_t value, uint8_t *base){
	__builtin_riscv_vse_v_u8m1_m(mask,value,base);
}

__rv32 void vse_v_u16m1_m(vmask_t mask,vuint16m1_t value, uint16_t *base){
	__builtin_riscv_vse_v_u16m1_m(mask,value,base);
}

__rv32 void vse_v_u32m1_m(vmask_t mask,vuint32m1_t value, uint32_t *base){
	__builtin_riscv_vse_v_u32m1_m(mask,value,base);
}

__rv32 void vse_v_f32m1_m(vmask_t mask,vfloat32m1_t value, float32_t *base){
	__builtin_riscv_vse_v_f32m1_m(mask,value,base);
}

/*************Vector Stride Load Functions***************/
__rv32 vint8m1_t vlse_v_i8m1(const int8_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_i8m1(base,stride);
}

__rv32 vint16m1_t vlse_v_i16m1(const int16_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_i16m1(base,stride);
}
__rv32 vint32m1_t vlse_v_i32m1(const int32_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_i32m1(base,stride);
}

__rv32 vuint8m1_t vlse_v_u8m1(const uint8_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_u8m1(base,stride);
}

__rv32 vuint16m1_t vlse_v_u16m1(const uint16_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_u16m1(base,stride);
}

__rv32 vuint32m1_t vlse_v_u32m1(const uint32_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_u32m1(base,stride);
}

__rv32 vfloat32m1_t vlse_v_f32m1(const float32_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_f32m1(base,stride);
}

//masked functions
__rv32 vint8m1_t vlse_v_i8m1_m(vmask_t mask, const int8_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_i8m1_m(mask,base,stride);
}

__rv32 vint16m1_t vlse_v_i16m1_m(vmask_t mask, const int16_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_i16m1_m(mask,base,stride);
}

__rv32 vint32m1_t vlse_v_i32m1_m(vmask_t mask, const int32_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_i32m1_m(mask,base,stride);
}

__rv32 vuint8m1_t vlse_v_u8m1_m(vmask_t mask, const uint8_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_u8m1_m(mask,base,stride);
}

__rv32 vuint16m1_t vlse_v_u16m1_m(vmask_t mask, const uint16_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_u16m1_m(mask,base,stride);
}

__rv32 vuint32m1_t vlse_v_u32m1_m(vmask_t mask, const uint32_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_u32m1_m(mask,base,stride);
}

__rv32 vfloat32m1_t vlse_v_f32m1_m(vmask_t mask, const float32_t *base, const int32_t stride){
	return __builtin_riscv_vlse_v_f32m1_m(mask,base,stride);
}

/*************Vector Stride Store Functions***************/
__rv32 void vsse_v_i8m1(int8_t *base, const int32_t stride, vint8m1_t value){
	__builtin_riscv_vsse_v_i8m1(base,stride,value);
}

__rv32 void vsse_v_i16m1(int16_t *base, const int32_t stride, vint16m1_t value){
	__builtin_riscv_vsse_v_i16m1(base,stride,value);
}

__rv32 void vsse_v_i32m1(int32_t *base, const int32_t stride, vint32m1_t value){
	__builtin_riscv_vsse_v_i32m1(base,stride,value);
}

__rv32 void vsse_v_u8m1(uint8_t *base, const int32_t stride, vuint8m1_t value){
	__builtin_riscv_vsse_v_u8m1(base,stride,value);
}

__rv32 void vsse_v_u16m1(uint16_t *base, const int32_t stride, vuint16m1_t value){
	__builtin_riscv_vsse_v_u16m1(base,stride,value);
}

__rv32 void vsse_v_u32m1(uint32_t *base, const int32_t stride, vuint32m1_t value){
	__builtin_riscv_vsse_v_u32m1(base,stride,value);
}

__rv32 void vsse_v_f32m1(float32_t *base, const int32_t stride, vfloat32m1_t value){
	__builtin_riscv_vsse_v_f32m1(base,stride,value);
}


//masked functions
__rv32 void vsse_v_i8m1_m(vmask_t mask,int8_t *base, const int32_t stride, vint8m1_t value){
	__builtin_riscv_vsse_v_i8m1_m(mask,base,stride,value);
}

__rv32 void vsse_v_i16m1_m(vmask_t mask,int16_t *base, const int32_t stride, vint16m1_t value){
	__builtin_riscv_vsse_v_i16m1_m(mask,base,stride,value);
}

__rv32 void vsse_v_i32m1_m(vmask_t mask,int32_t *base, const int32_t stride, vint32m1_t value){
	__builtin_riscv_vsse_v_i32m1_m(mask,base,stride,value);
}

__rv32 void vsse_v_u8m1_m(vmask_t mask,uint8_t *base, const int32_t stride, vuint8m1_t value){
	__builtin_riscv_vsse_v_u8m1_m(mask,base,stride,value);
}

__rv32 void vsse_v_u16m1_m(vmask_t mask,uint16_t *base, const int32_t stride, vuint16m1_t value){
	__builtin_riscv_vsse_v_u16m1_m(mask,base,stride,value);
}

__rv32 void vsse_v_u32m1_m(vmask_t mask,uint32_t *base, const int32_t stride, vuint32m1_t value){
	__builtin_riscv_vsse_v_u32m1_m(mask,base,stride,value);
}

__rv32 void vsse_v_f32m1_m(vmask_t mask,float32_t *base, const int32_t stride, vfloat32m1_t value){
	__builtin_riscv_vsse_v_f32m1_m(mask,base,stride,value);
}

/*************Vector Index Load Functions***************/
__rv32 vint8m1_t vlxe_v_i8m1(const int8_t *base, vuint8m1_t index){
	return __builtin_riscv_vlxe_v_i8m1(base,index);
}

__rv32 vint16m1_t vlxe_v_i16m1(const int16_t *base, vuint16m1_t index){
	return __builtin_riscv_vlxe_v_i16m1(base,index);
}

__rv32 vint32m1_t vlxe_v_i32m1(const int32_t *base, vuint32m1_t index){
	return __builtin_riscv_vlxe_v_i32m1(base,index);
}

__rv32 vuint8m1_t vlxe_v_u8m1(const uint8_t *base, vuint8m1_t index){
	return __builtin_riscv_vlxe_v_u8m1(base,index);
}

__rv32 vuint16m1_t vlxe_v_u16m1(const uint16_t *base, vuint16m1_t index){
	return __builtin_riscv_vlxe_v_u16m1(base,index);
}

__rv32 vuint32m1_t vlxe_v_u32m1(const uint32_t *base, vuint32m1_t index){
	return __builtin_riscv_vlxe_v_u32m1(base,index);
}

__rv32 vfloat32m1_t vlxe_v_f32m1(const float32_t *base, vuint32m1_t index){
	return __builtin_riscv_vlxe_v_f32m1(base,index);
}

//masked functions
__rv32 vint8m1_t vlxe_v_i8m1_m(vmask_t mask, const int8_t *base, vuint8m1_t index){
	return __builtin_riscv_vlxe_v_i8m1_m(mask,base,index);
}

__rv32 vint16m1_t vlxe_v_i16m1_m(vmask_t mask, const int16_t *base, vuint16m1_t index){
	return __builtin_riscv_vlxe_v_i16m1_m(mask,base,index);
}

__rv32 vint32m1_t vlxe_v_i32m1_m(vmask_t mask, const int32_t *base, vuint32m1_t index){
	return __builtin_riscv_vlxe_v_i32m1_m(mask,base,index);
}

__rv32 vuint8m1_t vlxe_v_u8m1_m(vmask_t mask, const uint8_t *base, vuint8m1_t index){
	return __builtin_riscv_vlxe_v_u8m1_m(mask,base,index);
}

__rv32 vuint16m1_t vlxe_v_u16m1_m(vmask_t mask, const uint16_t *base, vuint16m1_t index){
	return __builtin_riscv_vlxe_v_u16m1_m(mask,base,index);
}

__rv32 vuint32m1_t vlxe_v_u32m1_m(vmask_t mask, const uint32_t *base, vuint32m1_t index){
	return __builtin_riscv_vlxe_v_u32m1_m(mask,base,index);
}

__rv32 vfloat32m1_t vlxe_v_f32m1_m(vmask_t mask, const float32_t *base, vuint32m1_t index){
	return __builtin_riscv_vlxe_v_f32m1_m(mask,base,index);
}

/*************Vector Index Store Functions***************/
__rv32 void vsxe_v_i8m1(int8_t *base, vuint8m1_t index, vint8m1_t value){
	__builtin_riscv_vsxe_v_i8m1(base,index,value);
}

__rv32 void vsxe_v_i16m1(int16_t *base, vuint16m1_t index, vint16m1_t value){
	__builtin_riscv_vsxe_v_i16m1(base,index,value);
}

__rv32 void vsxe_v_i32m1(int32_t *base, vuint32m1_t index, vint32m1_t value){
	__builtin_riscv_vsxe_v_i32m1(base,index,value);
}

__rv32 void vsxe_v_u8m1(uint8_t *base, vuint8m1_t index, vuint8m1_t value){
	__builtin_riscv_vsxe_v_u8m1(base,index,value);
}

__rv32 void vsxe_v_u16m1(uint16_t *base, vuint16m1_t index, vuint16m1_t value){
	__builtin_riscv_vsxe_v_u16m1(base,index,value);
}

__rv32 void vsxe_v_u32m1(uint32_t *base, vuint32m1_t index, vuint32m1_t value){
	__builtin_riscv_vsxe_v_u32m1(base,index,value);
}

__rv32 void vsxe_v_f32m1(float32_t *base, vuint32m1_t index, vfloat32m1_t value){
	__builtin_riscv_vsxe_v_f32m1(base,index,value);
}

//masked functions
__rv32 void vsxe_v_i8m1_m(vmask_t mask,int8_t *base, vuint8m1_t index, vint8m1_t value){
	__builtin_riscv_vsxe_v_i8m1_m(mask,base,index,value);
}

__rv32 void vsxe_v_i16m1_m(vmask_t mask,int16_t *base, vuint16m1_t index, vint16m1_t value){
	__builtin_riscv_vsxe_v_i16m1_m(mask,base,index,value);
}

__rv32 void vsxe_v_i32m1_m(vmask_t mask,int32_t *base, vuint32m1_t index, vint32m1_t value){
	__builtin_riscv_vsxe_v_i32m1_m(mask,base,index,value);
}

__rv32 void vsxe_v_u8m1_m(vmask_t mask,uint8_t *base, vuint8m1_t index, vuint8m1_t value){
	__builtin_riscv_vsxe_v_u8m1_m(mask,base,index,value);
}

__rv32 void vsxe_v_u16m1_m(vmask_t mask,uint16_t *base, vuint16m1_t index, vuint16m1_t value){
	__builtin_riscv_vsxe_v_u16m1_m(mask,base,index,value);
}

__rv32 void vsxe_v_u32m1_m(vmask_t mask,uint32_t *base, vuint32m1_t index, vuint32m1_t value){
	__builtin_riscv_vsxe_v_u32m1_m(mask,base,index,value);
}

__rv32 void vsxe_v_f32m1_m(vmask_t mask,float32_t *base, vuint32m1_t index, vfloat32m1_t value){
	__builtin_riscv_vsxe_v_f32m1_m(mask,base,index,value);
}

/*************Vector Unordered Index Store Functions***************/
__rv32 void vsuxe_v_i8m1(int8_t *base, vuint8m1_t index, vint8m1_t value){
	__builtin_riscv_vsuxe_v_i8m1(base,index,value);
}

__rv32 void vsuxe_v_i16m1(int16_t *base, vuint16m1_t index, vint16m1_t value){
	__builtin_riscv_vsuxe_v_i16m1(base,index,value);
}

__rv32 void vsuxe_v_i32m1(int32_t *base, vuint32m1_t index, vint32m1_t value){
	__builtin_riscv_vsuxe_v_i32m1(base,index,value);
}

__rv32 void vsuxe_v_u8m1(uint8_t *base, vuint8m1_t index, vuint8m1_t value){
	__builtin_riscv_vsuxe_v_u8m1(base,index,value);
}

__rv32 void vsuxe_v_u16m1(uint16_t *base, vuint16m1_t index, vuint16m1_t value){
	__builtin_riscv_vsuxe_v_u16m1(base,index,value);
}

__rv32 void vsuxe_v_u32m1(uint32_t *base, vuint32m1_t index, vuint32m1_t value){
	__builtin_riscv_vsuxe_v_u32m1(base,index,value);
}

__rv32 void vsuxe_v_f32m1(float32_t *base, vuint32m1_t index, vfloat32m1_t value){
	__builtin_riscv_vsuxe_v_f32m1(base,index,value);
}

//masked functions
__rv32 void vsuxe_v_i8m1_m(vmask_t mask,int8_t *base, vuint8m1_t index, vint8m1_t value){
	__builtin_riscv_vsuxe_v_i8m1_m(mask,base,index,value);
}

__rv32 void vsuxe_v_i16m1_m(vmask_t mask,int16_t *base, vuint16m1_t index, vint16m1_t value){
	__builtin_riscv_vsuxe_v_i16m1_m(mask,base,index,value);
}

__rv32 void vsuxe_v_i32m1_m(vmask_t mask,int32_t *base, vuint32m1_t index, vint32m1_t value){
	__builtin_riscv_vsuxe_v_i32m1_m(mask,base,index,value);
}

__rv32 void vsuxe_v_u8m1_m(vmask_t mask,uint8_t *base, vuint8m1_t index, vuint8m1_t value){
	__builtin_riscv_vsuxe_v_u8m1_m(mask,base,index,value);
}

__rv32 void vsuxe_v_u16m1_m(vmask_t mask,uint16_t *base, vuint16m1_t index, vuint16m1_t value){
	__builtin_riscv_vsuxe_v_u16m1_m(mask,base,index,value);
}

__rv32 void vsuxe_v_u32m1_m(vmask_t mask,uint32_t *base, vuint32m1_t index, vuint32m1_t value){
	__builtin_riscv_vsuxe_v_u32m1_m(mask,base,index,value);
}

__rv32 void vsuxe_v_f32m1_m(vmask_t mask,float32_t *base, vuint32m1_t index, vfloat32m1_t value){
	__builtin_riscv_vsuxe_v_f32m1_m(mask,base,index,value);
}

/*************Vector Unit Stride Fault-Only-First Loads Functions***************/
__rv32 vint8m1_t vleff_v_i8m1(const int8_t *base){
	return __builtin_riscv_vleff_v_i8m1(base);
}

__rv32 vint16m1_t vleff_v_i16m1(const int16_t *base){
	return __builtin_riscv_vleff_v_i16m1(base);
}

__rv32 vint32m1_t vleff_v_i32m1(const int32_t *base){
	return __builtin_riscv_vleff_v_i32m1(base);
}

__rv32 vuint8m1_t vleff_v_u8m1(const uint8_t *base){
	return __builtin_riscv_vleff_v_u8m1(base);
}

__rv32 vuint16m1_t vleff_v_u16m1(const uint16_t *base){
	return __builtin_riscv_vleff_v_u16m1(base);
}


__rv32 vuint32m1_t vleff_v_u32m1(const uint32_t *base){
	return __builtin_riscv_vleff_v_u32m1(base);
}

__rv32 vfloat32m1_t vleff_v_f32m1(const float32_t *base){
	return __builtin_riscv_vleff_v_f32m1(base);
}


//masked functions
__rv32 vint8m1_t vleff_v_i8m1_m(vmask_t mask, const int8_t *base){
	return __builtin_riscv_vleff_v_i8m1_m(mask,base);
}

__rv32 vint16m1_t vleff_v_i16m1_m(vmask_t mask, const int16_t *base){
	return __builtin_riscv_vleff_v_i16m1_m(mask,base);
}

__rv32 vint32m1_t vleff_v_i32m1_m(vmask_t mask, const int32_t *base){
	return __builtin_riscv_vleff_v_i32m1_m(mask,base);
}

__rv32 vuint8m1_t vleff_v_u8m1_m(vmask_t mask, const uint8_t *base){
	return __builtin_riscv_vleff_v_u8m1_m(mask,base);
}

__rv32 vuint16m1_t vleff_v_u16m1_m(vmask_t mask, const uint16_t *base){
	return __builtin_riscv_vleff_v_u16m1_m(mask,base);
}

__rv32 vuint32m1_t vleff_v_u32m1_m(vmask_t mask, const uint32_t *base){
	return __builtin_riscv_vleff_v_u32m1_m(mask,base);
}

__rv32 vfloat32m1_t vleff_v_f32m1_m(vmask_t mask, const float32_t *base){
	return __builtin_riscv_vleff_v_f32m1_m(mask,base);
}

/***** Vector Single-Width Integer Add and Subtract Fuctions*****/
__rv32 vint8m1_t vadd_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vadd_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vadd_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vadd_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vadd_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vadd_vv_i32m1(op1,op2);
}

__rv32 vuint8m1_t vadd_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vadd_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vadd_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vadd_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vadd_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vadd_vv_u32m1(op1,op2);
}

__rv32 vint8m1_t vadd_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vadd_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vadd_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vadd_vx_i16m1(op1,op2);
}


__rv32 vint32m1_t vadd_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vadd_vx_i32m1(op1,op2);
}

__rv32 vuint8m1_t vadd_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vadd_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vadd_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vadd_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vadd_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vadd_vx_u32m1(op1,op2);
}

#define vadd_vi_i8m1(op1, op2) __extension__ ({\
	vint8m1_t __ret;\
	__ret = __builtin_riscv_vadd_vi_i8m1(op1,op2);\
	__ret;\
})

#define vadd_vi_i16m1(op1, op2) __extension__ ({\
	vint16m1_t __ret;\
	__ret = __builtin_riscv_vadd_vi_i16m1(op1,op2);\
	__ret;\
})

#define vadd_vi_i32m1(op1, op2) __extension__ ({\
	vint32m1_t __ret;\
	__ret = __builtin_riscv_vadd_vi_i32m1(op1,op2);\
	__ret;\
})

__rv32 vint8m1_t vsub_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vsub_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vsub_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vsub_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vsub_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vsub_vv_i32m1(op1,op2);
}

__rv32 vuint8m1_t vsub_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsub_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vsub_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsub_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vsub_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsub_vv_u32m1(op1,op2);
}

__rv32 vint8m1_t vsub_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vsub_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vsub_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vsub_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vsub_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vsub_vx_i32m1(op1,op2);
}

__rv32 vuint8m1_t vsub_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsub_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vsub_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vsub_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vsub_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vsub_vx_u32m1(op1,op2);
}

__rv32 vint8m1_t vrsub_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vrsub_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vrsub_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vrsub_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vrsub_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vrsub_vx_i32m1(op1,op2);
}

__rv32 vuint8m1_t vrsub_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vrsub_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vrsub_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vrsub_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vrsub_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vrsub_vx_u32m1(op1,op2);
}

#define vrsub_vi_i8m1(op1, op2) __extension__ ({\
	vint8m1_t __ret;\
	__ret = __builtin_riscv_vrsub_vi_i8m1(op1,op2);\
	__ret;\
})

#define vrsub_vi_i16m1(op1, op2) __extension__ ({\
	vint16m1_t __ret;\
	__ret = __builtin_riscv_vrsub_vi_i16m1(op1,op2);\
	__ret;\
})

#define vrsub_vi_i32m1(op1, op2) __extension__ ({\
	vint32m1_t __ret;\
	__ret = __builtin_riscv_vrsub_vi_i32m1(op1,op2);\
	__ret;\
})

//masked functions
__rv32 vint8m1_t vadd_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vadd_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vadd_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vadd_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vadd_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vadd_vv_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vadd_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vadd_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vadd_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vadd_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vadd_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vadd_vv_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vadd_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vadd_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vadd_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vadd_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vadd_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vadd_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vadd_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vadd_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vadd_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vadd_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vadd_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vadd_vx_u32m1_m(mask,op1,op2);
}

#define vadd_vi_i8m1_m(mask,op1, op2) __extension__ ({\
	vint8m1_t __ret;\
	__ret = __builtin_riscv_vadd_vi_i8m1_m(mask,op1,op2);\
	__ret;\
})

#define vadd_vi_i16m1_m(mask,op1, op2) __extension__ ({\
	vint16m1_t __ret;\
	__ret = __builtin_riscv_vadd_vi_i16m1_m(mask,op1,op2);\
	__ret;\
})

#define vadd_vi_i32m1_m(mask,op1, op2) __extension__ ({\
	vint32m1_t __ret;\
	__ret = __builtin_riscv_vadd_vi_i32m1_m(mask,op1,op2);\
	__ret;\
})

__rv32 vint8m1_t vsub_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vsub_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vsub_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vsub_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vsub_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vsub_vv_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vsub_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsub_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vsub_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsub_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vsub_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsub_vv_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vsub_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vsub_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vsub_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vsub_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vsub_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vsub_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vsub_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsub_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vsub_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vsub_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vsub_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vsub_vx_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vrsub_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vrsub_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vrsub_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vrsub_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vrsub_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vrsub_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vrsub_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vrsub_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vrsub_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vrsub_vx_u16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vrsub_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vrsub_vx_u32m1_m(mask,op1,op2);
}

#define vrsub_vi_i8m1_m(mask,op1, op2) __extension__ ({\
	vint8m1_t __ret;\
	__ret = __builtin_riscv_vrsub_vi_i8m1_m(mask,op1,op2);\
	__ret;\
})

#define vrsub_vi_i16m1_m(mask,op1, op2) __extension__ ({\
	vint16m1_t __ret;\
	__ret = __builtin_riscv_vrsub_vi_i16m1_m(mask,op1,op2);\
	__ret;\
})

#define vrsub_vi_i32m1_m(mask,op1, op2) __extension__ ({\
	vint32m1_t __ret;\
	__ret = __builtin_riscv_vrsub_vi_i32m1_m(mask,op1,op2);\
	__ret;\
})

/*******Vector Integer Add-with-Carry/Subtract-with-Borrow Functions*******/
__rv32 vint8m1_t vadc_vvm_i8m1(vint8m1_t op1, vint8m1_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vvm_i8m1(op1,op2,carryin);
}

__rv32 vint16m1_t vadc_vvm_i16m1(vint16m1_t op1, vint16m1_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vvm_i16m1(op1,op2,carryin);
}

__rv32 vint32m1_t vadc_vvm_i32m1(vint32m1_t op1, vint32m1_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vvm_i32m1(op1,op2,carryin);
}

__rv32 vuint8m1_t vadc_vvm_u8m1(vuint8m1_t op1, vuint8m1_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vvm_u8m1(op1,op2,carryin);
}

__rv32 vuint16m1_t vadc_vvm_u16m1(vuint16m1_t op1, vuint16m1_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vvm_u16m1(op1,op2,carryin);
}

__rv32 vuint32m1_t vadc_vvm_u32m1(vuint32m1_t op1, vuint32m1_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vvm_u32m1(op1,op2,carryin);
}

__rv32 vint8m1_t vadc_vxm_i8m1(vint8m1_t op1, int8_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vxm_i8m1(op1,op2,carryin);
}


__rv32 vint16m1_t vadc_vxm_i16m1(vint16m1_t op1, int16_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vxm_i16m1(op1,op2,carryin);
}

__rv32 vint32m1_t vadc_vxm_i32m1(vint32m1_t op1, int32_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vxm_i32m1(op1,op2,carryin);
}

__rv32 vuint8m1_t vadc_vxm_u8m1(vuint8m1_t op1, uint8_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vxm_u8m1(op1,op2,carryin);
}

__rv32 vuint16m1_t vadc_vxm_u16m1(vuint16m1_t op1, uint16_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vxm_u16m1(op1,op2,carryin);
}

__rv32 vuint32m1_t vadc_vxm_u32m1(vuint32m1_t op1, uint32_t op2, vmask_t carryin){
	return __builtin_riscv_vadc_vxm_u32m1(op1,op2,carryin);
}


#define vadc_vim_i8m1(op1,op2,carryin) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vadc_vim_i8m1(op1,op2,carryin);\
		__ret;\
		})

#define vadc_vim_i16m1(op1,op2,carryin) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vadc_vim_i16m1(op1,op2,carryin);\
		__ret;\
		})
	
#define vadc_vim_i32m1(op1,op2,carryin) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vadc_vim_i32m1(op1,op2,carryin);\
		__ret;\
		})

#define vadc_vim_u8m1(op1,op2,carryin) __extension__({\
		vuint8m1_t __ret;\
		__ret = __builtin_riscv_vadc_vim_u8m1(op1,op2,carryin);\
		__ret;\
		})

#define vadc_vim_u16m1(op1,op2,carryin) __extension__({\
		vuint16m1_t __ret;\
		__ret = __builtin_riscv_vadc_vim_u16m1(op1,op2,carryin);\
		__ret;\
		})

#define vadc_vim_u32m1(op1,op2,carryin) __extension__({\
		vuint32m1_t __ret;\
		__ret = __builtin_riscv_vadc_vim_u32m1(op1,op2,carryin);\
		__ret;\
		})

__rv32 vmask_t vmadc_vvm_i8m1(vint8m1_t op1, vint8m1_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vvm_i8m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vvm_i16m1(vint16m1_t op1, vint16m1_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vvm_i16m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vvm_i32m1(vint32m1_t op1, vint32m1_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vvm_i32m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vvm_u8m1(vuint8m1_t op1, vuint8m1_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vvm_u8m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vvm_u16m1(vuint16m1_t op1, vuint16m1_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vvm_u16m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vvm_u32m1(vuint32m1_t op1, vuint32m1_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vvm_u32m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vxm_i8m1(vint8m1_t op1, int8_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vxm_i8m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vxm_i16m1(vint16m1_t op1, int16_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vxm_i16m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vxm_i32m1(vint32m1_t op1, int32_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vxm_i32m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vxm_u8m1(vuint8m1_t op1, uint8_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vxm_u8m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vxm_u16m1(vuint16m1_t op1, uint16_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vxm_u16m1(op1,op2,carryin);
}

__rv32 vmask_t vmadc_vxm_u32m1(vuint32m1_t op1, uint32_t op2, vmask_t carryin){
	return __builtin_riscv_vmadc_vxm_u32m1(op1,op2,carryin);
}


#define vmadc_vim_i8m1(op1,op2,carryin) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmadc_vim_i8m1(op1,op2,carryin);\
		__ret;\
		})

#define vmadc_vim_i16m1(op1,op2,carryin) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmadc_vim_i16m1(op1,op2,carryin);\
		__ret;\
		})

#define vmadc_vim_i32m1(op1,op2,carryin) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmadc_vim_i32m1(op1,op2,carryin);\
		__ret;\
		})

#define vmadc_vim_u8m1(op1,op2,carryin) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmadc_vim_u8m1(op1,op2,carryin);\
		__ret;\
		})

#define vmadc_vim_u16m1(op1,op2,carryin) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmadc_vim_u16m1(op1,op2,carryin);\
		__ret;\
		})

#define vmadc_vim_u32m1(op1,op2,carryin) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmadc_vim_u32m1(op1,op2,carryin);\
		__ret;\
		})

__rv32 vmask_t vmadc_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmadc_vv_i8m1(op1,op2);
}

__rv32 vmask_t vmadc_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmadc_vv_i16m1(op1,op2);
}

__rv32 vmask_t vmadc_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmadc_vv_i32m1(op1,op2);
}

__rv32 vmask_t vmadc_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmadc_vv_u8m1(op1,op2);
}

__rv32 vmask_t vmadc_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmadc_vv_u16m1(op1,op2);
}

__rv32 vmask_t vmadc_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmadc_vv_u32m1(op1,op2);
}

__rv32 vmask_t vmadc_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmadc_vx_i8m1(op1,op2);
}

__rv32 vmask_t vmadc_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmadc_vx_i16m1(op1,op2);
}

__rv32 vmask_t vmadc_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmadc_vx_i32m1(op1,op2);
}

__rv32 vmask_t vmadc_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmadc_vx_u8m1(op1,op2);
}

__rv32 vmask_t vmadc_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmadc_vx_u16m1(op1,op2);
}

__rv32 vmask_t vmadc_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmadc_vx_u32m1(op1,op2);
}

#define vmadc_vi_i8m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmadc_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vmadc_vi_i16m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmadc_vi_i16m1(op1,op2);\
		__ret;\
		})

#define vmadc_vi_i32m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmadc_vi_i32m1(op1,op2);\
		__ret;\
		})


__rv32 vint8m1_t vsbc_vvm_i8m1(vint8m1_t op1, vint8m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vvm_i8m1(op1,op2,borrowin);
}

__rv32 vint16m1_t vsbc_vvm_i16m1(vint16m1_t op1, vint16m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vvm_i16m1(op1,op2,borrowin);
}

__rv32 vint32m1_t vsbc_vvm_i32m1(vint32m1_t op1, vint32m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vvm_i32m1(op1,op2,borrowin);
}


__rv32 vuint8m1_t vsbc_vvm_u8m1(vuint8m1_t op1, vuint8m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vvm_u8m1(op1,op2,borrowin);
}

__rv32 vuint16m1_t vsbc_vvm_u16m1(vuint16m1_t op1, vuint16m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vvm_u16m1(op1,op2,borrowin);
}


__rv32 vuint32m1_t vsbc_vvm_u32m1(vuint32m1_t op1, vuint32m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vvm_u32m1(op1,op2,borrowin);
}

__rv32 vint8m1_t vsbc_vxm_i8m1(vint8m1_t op1, int8_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vxm_i8m1(op1,op2,borrowin);
}

__rv32 vint16m1_t vsbc_vxm_i16m1(vint16m1_t op1, int16_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vxm_i16m1(op1,op2,borrowin);
}

__rv32 vint32m1_t vsbc_vxm_i32m1(vint32m1_t op1, int32_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vxm_i32m1(op1,op2,borrowin);
}

__rv32 vuint8m1_t vsbc_vxm_u8m1(vuint8m1_t op1, uint8_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vxm_u8m1(op1,op2,borrowin);
}

__rv32 vuint16m1_t vsbc_vxm_u16m1(vuint16m1_t op1, uint16_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vxm_u16m1(op1,op2,borrowin);
}

__rv32 vuint32m1_t vsbc_vxm_u32m1(vuint32m1_t op1, uint32_t op2, vmask_t borrowin){
	return __builtin_riscv_vsbc_vxm_u32m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vvm_i8m1(vint8m1_t op1, vint8m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vvm_i8m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vvm_i16m1(vint16m1_t op1, vint16m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vvm_i16m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vvm_i32m1(vint32m1_t op1, vint32m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vvm_i32m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vvm_u8m1(vuint8m1_t op1, vuint8m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vvm_u8m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vvm_u16m1(vuint16m1_t op1, vuint16m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vvm_u16m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vvm_u32m1(vuint32m1_t op1, vuint32m1_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vvm_u32m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vxm_i8m1(vint8m1_t op1, int8_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vxm_i8m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vxm_i16m1(vint16m1_t op1, int16_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vxm_i16m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vxm_i32m1(vint32m1_t op1, int32_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vxm_i32m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vxm_u8m1(vuint8m1_t op1, uint8_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vxm_u8m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vxm_u16m1(vuint16m1_t op1, uint16_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vxm_u16m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vxm_u32m1(vuint32m1_t op1, uint32_t op2, vmask_t borrowin){
	return __builtin_riscv_vmsbc_vxm_u32m1(op1,op2,borrowin);
}

__rv32 vmask_t vmsbc_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmsbc_vv_i8m1(op1,op2);
}

__rv32 vmask_t vmsbc_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmsbc_vv_i16m1(op1,op2);
}

__rv32 vmask_t vmsbc_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmsbc_vv_i32m1(op1,op2);
}

__rv32 vmask_t vmsbc_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmsbc_vv_u8m1(op1,op2);
}

__rv32 vmask_t vmsbc_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmsbc_vv_u16m1(op1,op2);
}

__rv32 vmask_t vmsbc_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmsbc_vv_u32m1(op1,op2);
}

__rv32 vmask_t vmsbc_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmsbc_vx_i8m1(op1,op2);
}

__rv32 vmask_t vmsbc_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmsbc_vx_i16m1(op1,op2);
}


__rv32 vmask_t vmsbc_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmsbc_vx_i32m1(op1,op2);
}

__rv32 vmask_t vmsbc_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmsbc_vx_u8m1(op1,op2);
}

__rv32 vmask_t vmsbc_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmsbc_vx_u16m1(op1,op2);
}

__rv32 vmask_t vmsbc_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmsbc_vx_u32m1(op1,op2);
}


/*******Vector Bitwise Logical Functions*********/
__rv32 vint8m1_t vand_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vand_vv_i8m1(op1,op2);
}


__rv32 vint16m1_t vand_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vand_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vand_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vand_vv_i32m1(op1,op2);
}

__rv32 vuint8m1_t vand_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vand_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vand_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vand_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vand_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vand_vv_u32m1(op1,op2);
}

__rv32 vint8m1_t vand_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vand_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vand_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vand_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vand_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vand_vx_i32m1(op1,op2);
}

__rv32 vuint8m1_t vand_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vand_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vand_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vand_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vand_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vand_vx_u32m1(op1,op2);
}


#define vand_vi_i8m1(op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vand_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vand_vi_i16m1(op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vand_vi_i16m1(op1,op2);\
		__ret;\
		})

#define vand_vi_i32m1(op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vand_vi_i32m1(op1,op2);\
		__ret;\
		})

__rv32 vint8m1_t vor_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vor_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vor_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vor_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vor_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vor_vv_i32m1(op1,op2);
}

__rv32 vuint8m1_t vor_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vor_vv_u8m1(op1,op2);
}


__rv32 vuint16m1_t vor_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vor_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vor_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vor_vv_u32m1(op1,op2);
}

__rv32 vint8m1_t vor_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vor_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vor_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vor_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vor_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vor_vx_i32m1(op1,op2);
}


__rv32 vuint8m1_t vor_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vor_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vor_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vor_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vor_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vor_vx_u32m1(op1,op2);
}

#define vor_vi_i8m1(op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vor_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vor_vi_i16m1(op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vor_vi_i16m1(op1,op2);\
		__ret;\
		})

#define vor_vi_i32m1(op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vor_vi_i32m1(op1,op2);\
		__ret;\
		})

__rv32 vint8m1_t vxor_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vxor_vv_i8m1(op1,op2);
}


__rv32 vint16m1_t vxor_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vxor_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vxor_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vxor_vv_i32m1(op1,op2);
}

__rv32 vuint8m1_t vxor_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vxor_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vxor_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vxor_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vxor_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vxor_vv_u32m1(op1,op2);
}

__rv32 vint8m1_t vxor_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vxor_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vxor_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vxor_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vxor_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vxor_vx_i32m1(op1,op2);
}

__rv32 vuint8m1_t vxor_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vxor_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vxor_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vxor_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vxor_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vxor_vx_u32m1(op1,op2);
}

#define vxor_vi_i8m1(op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vxor_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vxor_vi_i16m1(op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vxor_vi_i16m1(op1,op2);\
		__ret;\
		})

#define vxor_vi_i32m1(op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vxor_vi_i32m1(op1,op2);\
		__ret;\
		})

//masked function
__rv32 vint8m1_t vand_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vand_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vand_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vand_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vand_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vand_vv_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vand_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vand_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vand_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vand_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vand_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vand_vv_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vand_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vand_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vand_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vand_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vand_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vand_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vand_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vand_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vand_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vand_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vand_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vand_vx_u32m1_m(mask,op1,op2);
}


#define vand_vi_i8m1_m(mask,op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vand_vi_i8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vand_vi_i16m1_m(mask,op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vand_vi_i16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vand_vi_i32m1_m(mask,op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vand_vi_i32m1_m(mask,op1,op2);\
		__ret;\
		})


__rv32 vint8m1_t vor_vv_i8m1_m(vmask_t mask,vint8m1_t op1,vint8m1_t op2){
	return __builtin_riscv_vor_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vor_vv_i16m1_m(vmask_t mask,vint16m1_t op1,vint16m1_t op2){
	return __builtin_riscv_vor_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vor_vv_i32m1_m(vmask_t mask,vint32m1_t op1,vint32m1_t op2){
	return __builtin_riscv_vor_vv_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vor_vv_u8m1_m(vmask_t mask,vuint8m1_t op1,vuint8m1_t op2){
	return __builtin_riscv_vor_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vor_vv_u16m1_m(vmask_t mask,vuint16m1_t op1,vuint16m1_t op2){
	return __builtin_riscv_vor_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vor_vv_u32m1_m(vmask_t mask,vuint32m1_t op1,vuint32m1_t op2){
	return __builtin_riscv_vor_vv_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vor_vx_i8m1_m(vmask_t mask,vint8m1_t op1,int8_t op2){
	return __builtin_riscv_vor_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vor_vx_i16m1_m(vmask_t mask,vint16m1_t op1,int16_t op2){
	return __builtin_riscv_vor_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vor_vx_i32m1_m(vmask_t mask,vint32m1_t op1,int32_t op2){
	return __builtin_riscv_vor_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vor_vx_u8m1_m(vmask_t mask,vuint8m1_t op1,uint8_t op2){
	return __builtin_riscv_vor_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vor_vx_u16m1_m(vmask_t mask,vuint16m1_t op1,uint16_t op2){
	return __builtin_riscv_vor_vx_u16m1_m(mask,op1,op2);
}


__rv32 vuint32m1_t vor_vx_u32m1_m(vmask_t mask,vuint32m1_t op1,uint32_t op2){
	return __builtin_riscv_vor_vx_u32m1_m(mask,op1,op2);
}


#define vor_vi_i8m1_m(mask,op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vor_vi_i8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vor_vi_i16m1_m(mask,op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vor_vi_i16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vor_vi_i32m1_m(mask,op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vor_vi_i32m1_m(mask,op1,op2);\
		__ret;\
		})

__rv32 vint8m1_t vxor_vv_i8m1_m(vmask_t mask,vint8m1_t op1,vint8m1_t op2){
	return __builtin_riscv_vxor_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vxor_vv_i16m1_m(vmask_t mask,vint16m1_t op1,vint16m1_t op2){
	return __builtin_riscv_vxor_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vxor_vv_i32m1_m(vmask_t mask,vint32m1_t op1,vint32m1_t op2){
	return __builtin_riscv_vxor_vv_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vxor_vv_u8m1_m(vmask_t mask,vuint8m1_t op1,vuint8m1_t op2){
	return __builtin_riscv_vxor_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vxor_vv_u16m1_m(vmask_t mask,vuint16m1_t op1,vuint16m1_t op2){
	return __builtin_riscv_vxor_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vxor_vv_u32m1_m(vmask_t mask,vuint32m1_t op1,vuint32m1_t op2){
	return __builtin_riscv_vxor_vv_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vxor_vx_i8m1_m(vmask_t mask,vint8m1_t op1,int8_t op2){
	return __builtin_riscv_vxor_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vxor_vx_i16m1_m(vmask_t mask,vint16m1_t op1,int16_t op2){
	return __builtin_riscv_vxor_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vxor_vx_i32m1_m(vmask_t mask,vint32m1_t op1,int32_t op2){
	return __builtin_riscv_vxor_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vxor_vx_u8m1_m(vmask_t mask,vuint8m1_t op1,uint8_t op2){
	return __builtin_riscv_vxor_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vxor_vx_u16m1_m(vmask_t mask,vuint16m1_t op1,uint16_t op2){
	return __builtin_riscv_vxor_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vxor_vx_u32m1_m(vmask_t mask,vuint32m1_t op1,uint32_t op2){
	return __builtin_riscv_vxor_vx_u32m1_m(mask,op1,op2);
}

#define vxor_vi_i8m1_m(mask,op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vxor_vi_i8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vxor_vi_i16m1_m(mask,op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vxor_vi_i16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vxor_vi_i32m1_m(mask,op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vxor_vi_i32m1_m(mask,op1,op2);\
		__ret;\
		})

/********Vector Single-Width Bit Shift Function**********/
__rv32 vint8m1_t vsll_vv_i8m1(vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsll_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vsll_vv_i16m1(vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsll_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vsll_vv_i32m1(vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsll_vv_i32m1(op1,op2);
}

__rv32 vuint8m1_t vsll_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsll_vv_u8m1(op1,op2);
}


__rv32 vuint16m1_t vsll_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsll_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vsll_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsll_vv_u32m1(op1,op2);
}

__rv32 vint8m1_t vsll_vx_i8m1(vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vsll_vx_i16m1(vint16m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vsll_vx_i32m1(vint32m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_i32m1(op1,op2);
}

__rv32 vuint8m1_t vsll_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vsll_vx_u16m1(vuint16m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vsll_vx_u32m1(vuint32m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_u32m1(op1,op2);
}

#define vsll_vi_i8m1(op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vsll_vi_i16m1(op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_i16m1(op1,op2);\
		__ret;\
		})

#define vsll_vi_i32m1(op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_i32m1(op1,op2);\
		__ret;\
		})

#define vsll_vi_u8m1(op1,op2) __extension__({\
		vuint8m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_u8m1(op1,op2);\
		__ret;\
		})

#define vsll_vi_u16m1(op1,op2) __extension__({\
		vuint16m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_u16m1(op1,op2);\
		__ret;\
		})

#define vsll_vi_u32m1(op1,op2) __extension__({\
		vuint32m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_u32m1(op1,op2);\
		__ret;\
		})

__rv32 vuint8m1_t vsrl_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsrl_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vsrl_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsrl_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vsrl_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsrl_vv_u32m1(op1,op2);
}

__rv32 vuint8m1_t vsrl_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsrl_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vsrl_vx_u16m1(vuint16m1_t op1, uint8_t op2){
	return __builtin_riscv_vsrl_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vsrl_vx_u32m1(vuint32m1_t op1, uint8_t op2){
	return __builtin_riscv_vsrl_vx_u32m1(op1,op2);
}

#define vsrl_vi_u8m1(op1,op2) __extension__({\
		vuint8m1_t __ret;\
		__ret = __builtin_riscv_vsrl_vi_u8m1(op1,op2);\
		__ret;\
		})

#define vsrl_vi_u16m1(op1,op2) __extension__({\
		vuint16m1_t __ret;\
		__ret = __builtin_riscv_vsrl_vi_u16m1(op1,op2);\
		__ret;\
		})

#define vsrl_vi_u32m1(op1,op2) __extension__({\
		vuint32m1_t __ret;\
		__ret = __builtin_riscv_vsrl_vi_u32m1(op1,op2);\
		__ret;\
		})

__rv32 vint8m1_t vsra_vv_i8m1(vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsra_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vsra_vv_i16m1(vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsra_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vsra_vv_i32m1(vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsra_vv_i32m1(op1,op2);
}

__rv32 vint8m1_t vsra_vx_i8m1(vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsra_vx_i8m1(op1,op2);
}


__rv32 vint16m1_t vsra_vx_i16m1(vint16m1_t op1, uint8_t op2){
	return __builtin_riscv_vsra_vx_i16m1(op1,op2);
}


__rv32 vint32m1_t vsra_vx_i32m1(vint32m1_t op1, uint8_t op2){
	return __builtin_riscv_vsra_vx_i32m1(op1,op2);
}

#define vsra_vi_i8m1(op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vsra_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vsra_vi_i16m1(op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vsra_vi_i16m1(op1,op2);\
		__ret;\
		})

#define vsra_vi_i32m1(op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vsra_vi_i32m1(op1,op2);\
		__ret;\
		})

//masked functions
__rv32 vint8m1_t vsll_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsll_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vsll_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsll_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vsll_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsll_vv_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vsll_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsll_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vsll_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsll_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vsll_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsll_vv_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vsll_vx_i8m1_m(vmask_t mask, vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vsll_vx_i16m1_m(vmask_t mask, vint16m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vsll_vx_i32m1_m(vmask_t mask, vint32m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vsll_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vsll_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vsll_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint8_t op2){
	return __builtin_riscv_vsll_vx_u32m1_m(mask,op1,op2);
}

#define vsll_vi_i8m1_m(mask,op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_i8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vsll_vi_i16m1_m(mask,op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_i16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vsll_vi_i32m1_m(mask,op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_i32m1_m(mask,op1,op2);\
		__ret;\
		})

#define vsll_vi_u8m1_m(mask,op1,op2) __extension__({\
		vuint8m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_u8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vsll_vi_u16m1_m(mask,op1,op2) __extension__({\
		vuint16m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_u16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vsll_vi_u32m1_m(mask,op1,op2) __extension__({\
		vuint32m1_t __ret;\
		__ret = __builtin_riscv_vsll_vi_u32m1_m(mask,op1,op2);\
		__ret;\
		})

__rv32 vuint8m1_t vsrl_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsrl_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vsrl_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsrl_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vsrl_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsrl_vv_u32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vsrl_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsrl_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vsrl_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint8_t op2){
	return __builtin_riscv_vsrl_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vsrl_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint8_t op2){
	return __builtin_riscv_vsrl_vx_u32m1_m(mask,op1,op2);
}

#define vsrl_vi_u8m1_m(mask,op1,op2) __extension__({\
		vuint8m1_t __ret;\
		__ret = __builtin_riscv_vsrl_vi_u8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vsrl_vi_u16m1_m(mask,op1,op2) __extension__({\
		vuint16m1_t __ret;\
		__ret = __builtin_riscv_vsrl_vi_u16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vsrl_vi_u32m1_m(mask,op1,op2) __extension__({\
		vuint32m1_t __ret;\
		__ret = __builtin_riscv_vsrl_vi_u32m1_m(mask,op1,op2);\
		__ret;\
		})

__rv32 vint8m1_t vsra_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsra_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vsra_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsra_vv_i16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vsra_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsra_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vsra_vx_i8m1_m(vmask_t mask, vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsra_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vsra_vx_i16m1_m(vmask_t mask, vint16m1_t op1, uint8_t op2){
	return __builtin_riscv_vsra_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vsra_vx_i32m1_m(vmask_t mask, vint32m1_t op1, uint8_t op2){
	return __builtin_riscv_vsra_vx_i32m1_m(mask,op1,op2);
}

#define vsra_vi_i8m1_m(mask,op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vsra_vi_i8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vsra_vi_i16m1_m(mask,op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vsra_vi_i16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vsra_vi_i32m1_m(mask,op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vsra_vi_i32m1_m(mask,op1,op2);\
		__ret;\
		})


/************Vector Integer Comparison Functions***************/
__rv32 vmask_t vmseq_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmseq_vv_i8m1(op1,op2);
}

__rv32 vmask_t vmseq_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmseq_vv_i16m1(op1,op2);
}

__rv32 vmask_t vmseq_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmseq_vv_i32m1(op1,op2);
}

__rv32 vmask_t vmseq_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmseq_vv_u8m1(op1,op2);
}

__rv32 vmask_t vmseq_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmseq_vv_u16m1(op1,op2);
}

__rv32 vmask_t vmseq_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmseq_vv_u32m1(op1,op2);
}

__rv32 vmask_t vmseq_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmseq_vx_i8m1(op1,op2);
}

__rv32 vmask_t vmseq_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmseq_vx_i16m1(op1,op2);
}

__rv32 vmask_t vmseq_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmseq_vx_i32m1(op1,op2);
}

__rv32 vmask_t vmseq_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmseq_vx_u8m1(op1,op2);
}

__rv32 vmask_t vmseq_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmseq_vx_u16m1(op1,op2);
}

__rv32 vmask_t vmseq_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmseq_vx_u32m1(op1,op2);
}

#define vmseq_vi_i8m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmseq_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vmseq_vi_i16m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmseq_vi_i16m1(op1,op2);\
		__ret;\
		})

#define vmseq_vi_i32m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmseq_vi_i32m1(op1,op2);\
		__ret;\
		})


__rv32 vmask_t vmsne_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmsne_vv_i8m1(op1,op2);
}

__rv32 vmask_t vmsne_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmsne_vv_i16m1(op1,op2);
}

__rv32 vmask_t vmsne_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmsne_vv_i32m1(op1,op2);
}

__rv32 vmask_t vmsne_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmsne_vv_u8m1(op1,op2);
}

__rv32 vmask_t vmsne_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmsne_vv_u16m1(op1,op2);
}

__rv32 vmask_t vmsne_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmsne_vv_u32m1(op1,op2);
}

__rv32 vmask_t vmsne_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmsne_vx_i8m1(op1,op2);
}

__rv32 vmask_t vmsne_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmsne_vx_i16m1(op1,op2);
}

__rv32 vmask_t vmsne_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmsne_vx_i32m1(op1,op2);
}

__rv32 vmask_t vmsne_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmsne_vx_u8m1(op1,op2);
}


__rv32 vmask_t vmsne_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmsne_vx_u16m1(op1,op2);
}

__rv32 vmask_t vmsne_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmsne_vx_u32m1(op1,op2);
}

#define vmsne_vi_i8m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsne_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vmsne_vi_i16m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsne_vi_i16m1(op1,op2);\
		__ret;\
		})


#define vmsne_vi_i32m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsne_vi_i32m1(op1,op2);\
		__ret;\
		})

__rv32 vmask_t vmsltu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmsltu_vv_u8m1(op1,op2);
}


__rv32 vmask_t vmsltu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmsltu_vv_u16m1(op1,op2);
}


__rv32 vmask_t vmsltu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmsltu_vv_u32m1(op1,op2);
}

__rv32 vmask_t vmsltu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmsltu_vx_u8m1(op1,op2);
} 

__rv32 vmask_t vmsltu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmsltu_vx_u16m1(op1,op2);
}


__rv32 vmask_t vmsltu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmsltu_vx_u32m1(op1,op2);
}

__rv32 vmask_t vmslt_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmslt_vv_i8m1(op1,op2);
}

__rv32 vmask_t vmslt_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmslt_vv_i16m1(op1,op2);
}

__rv32 vmask_t vmslt_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmslt_vv_i32m1(op1,op2);
}

__rv32 vmask_t vmslt_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmslt_vx_i8m1(op1,op2);
}

__rv32 vmask_t vmslt_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmslt_vx_i16m1(op1,op2);
}

__rv32 vmask_t vmslt_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmslt_vx_i32m1(op1,op2);
}

__rv32 vmask_t vmsleu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmsleu_vv_u8m1(op1,op2);
}

__rv32 vmask_t vmsleu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmsleu_vv_u16m1(op1,op2);
}

__rv32 vmask_t vmsleu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmsleu_vv_u32m1(op1,op2);
}

__rv32 vmask_t vmsleu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmsleu_vx_u8m1(op1,op2);
}

__rv32 vmask_t vmsleu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmsleu_vx_u16m1(op1,op2);
}

__rv32 vmask_t vmsleu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmsleu_vx_u32m1(op1,op2);
}

#define vmsleu_vi_u8m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsleu_vi_u8m1(op1,op2);\
		__ret;\
		})

#define vmsleu_vi_u16m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsleu_vi_u16m1(op1,op2);\
		__ret;\
		})

#define vmsleu_vi_u32m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsleu_vi_u32m1(op1,op2);\
		__ret;\
		})

__rv32 vmask_t vmsle_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmsle_vv_i8m1(op1,op2);
}

__rv32 vmask_t vmsle_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmsle_vv_i16m1(op1,op2);
}

__rv32 vmask_t vmsle_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmsle_vv_i32m1(op1,op2);
}

__rv32 vmask_t vmsle_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmsle_vx_i8m1(op1,op2);
}

__rv32 vmask_t vmsle_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmsle_vx_i16m1(op1,op2);
}

__rv32 vmask_t vmsle_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmsle_vx_i32m1(op1,op2);
}

#define vmsle_vi_i8m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsle_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vmsle_vi_i16m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsle_vi_i16m1(op1,op2);\
		__ret;\
		})

#define vmsle_vi_i32m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsle_vi_i32m1(op1,op2);\
		__ret;\
		})

__rv32 vmask_t vmsgtu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmsgtu_vx_u8m1(op1,op2);
}

__rv32 vmask_t vmsgtu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmsgtu_vx_u16m1(op1,op2);
}

__rv32 vmask_t vmsgtu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmsgtu_vx_u32m1(op1,op2);
}

#define vmsgtu_vi_u8m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgtu_vi_u8m1(op1,op2);\
		__ret;\
		})

#define vmsgtu_vi_u16m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgtu_vi_u16m1(op1,op2);\
		__ret;\
		})

#define vmsgtu_vi_u32m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgtu_vi_u32m1(op1,op2);\
		__ret;\
		})

__rv32 vmask_t vmsgt_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmsgt_vx_i8m1(op1,op2);
}

__rv32 vmask_t vmsgt_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmsgt_vx_i16m1(op1,op2);
}

__rv32 vmask_t vmsgt_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmsgt_vx_i32m1(op1,op2);
}

#define vmsgt_vi_i8m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgt_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vmsgt_vi_i16m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgt_vi_i16m1(op1,op2);\
		__ret;\
		})

#define vmsgt_vi_i32m1(op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgt_vi_i32m1(op1,op2);\
		__ret;\
		})

//masked functions
__rv32 vmask_t vmseq_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmseq_vv_i8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmseq_vv_i16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmseq_vv_i32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmseq_vv_u8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmseq_vv_u16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmseq_vv_u32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmseq_vx_i8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmseq_vx_i16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmseq_vx_i32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmseq_vx_u8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmseq_vx_u16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmseq_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmseq_vx_u32m1_m(mask,op1,op2);
}

#define vmseq_vi_i8m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmseq_vi_i8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmseq_vi_i16m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmseq_vi_i16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmseq_vi_i32m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmseq_vi_i32m1_m(mask,op1,op2);\
		__ret;\
		})


__rv32 vmask_t vmsne_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmsne_vv_i8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmsne_vv_i16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmsne_vv_i32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmsne_vv_u8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmsne_vv_u16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmsne_vv_u32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmsne_vx_i8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmsne_vx_i16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmsne_vx_i32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmsne_vx_u8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmsne_vx_u16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsne_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmsne_vx_u32m1_m(mask,op1,op2);
}

#define vmsne_vi_i8m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsne_vi_i8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmsne_vi_i16m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsne_vi_i16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmsne_vi_i32m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsne_vi_i32m1_m(mask,op1,op2);\
		__ret;\
		})

__rv32 vmask_t vmsltu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmsltu_vv_u8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsltu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmsltu_vv_u16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsltu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmsltu_vv_u32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsltu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmsltu_vx_u8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsltu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmsltu_vx_u16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsltu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmsltu_vx_u32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmslt_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmslt_vv_i8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmslt_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmslt_vv_i16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmslt_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmslt_vv_i32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmslt_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmslt_vx_i8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmslt_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmslt_vx_i16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmslt_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmslt_vx_i32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsleu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmsleu_vv_u8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsleu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmsleu_vv_u16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsleu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmsleu_vv_u32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsleu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmsleu_vx_u8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsleu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmsleu_vx_u16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsleu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmsleu_vx_u32m1_m(mask,op1,op2);
}

#define vmsleu_vi_u8m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsleu_vi_u8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmsleu_vi_u16m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsleu_vi_u16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmsleu_vi_u32m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsleu_vi_u32m1_m(mask,op1,op2);\
		__ret;\
		})

__rv32 vmask_t vmsle_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmsle_vv_i8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsle_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmsle_vv_i16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsle_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmsle_vv_i32m1_m(mask,op1,op2);
}


__rv32 vmask_t vmsle_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmsle_vx_i8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsle_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmsle_vx_i16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsle_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmsle_vx_i32m1_m(mask,op1,op2);
}

#define vmsle_vi_i8m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsle_vi_i8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmsle_vi_i16m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsle_vi_i16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmsle_vi_i32m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsle_vi_i32m1_m(mask,op1,op2);\
		__ret;\
		})

__rv32 vmask_t vmsgtu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmsgtu_vx_u8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsgtu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmsgtu_vx_u16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsgtu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmsgtu_vx_u32m1_m(mask,op1,op2);
}

#define vmsgtu_vi_u8m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgtu_vi_u8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmsgtu_vi_u16m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgtu_vi_u16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmsgtu_vi_u32m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgtu_vi_u32m1_m(mask,op1,op2);\
		__ret;\
		})

__rv32 vmask_t vmsgt_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmsgt_vx_i8m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsgt_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmsgt_vx_i16m1_m(mask,op1,op2);
}

__rv32 vmask_t vmsgt_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmsgt_vx_i32m1_m(mask,op1,op2);
}

#define vmsgt_vi_i8m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgt_vi_i8m1_m(mask,op1,op2);\
		__ret;\
		})

#define vmsgt_vi_i16m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgt_vi_i16m1_m(mask,op1,op2);\
		__ret;\
		})
		
#define vmsgt_vi_i32m1_m(mask,op1,op2) __extension__({\
		vmask_t __ret;\
		__ret = __builtin_riscv_vmsgt_vi_i32m1_m(mask,op1,op2);\
		__ret;\
		})	

/**********Vector Integer Min/Max Functions************/
__rv32 vuint8m1_t vminu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vminu_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vminu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vminu_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vminu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vminu_vv_u32m1(op1,op2);
}

__rv32 vuint8m1_t vminu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vminu_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vminu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vminu_vx_u16m1(op1,op2);
} 

__rv32 vuint32m1_t vminu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vminu_vx_u32m1(op1,op2);
}

__rv32 vint8m1_t vmin_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmin_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vmin_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmin_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vmin_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmin_vv_i32m1(op1,op2);
}

__rv32 vint8m1_t vmin_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmin_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vmin_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmin_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vmin_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmin_vx_i32m1(op1,op2);
}

__rv32 vuint8m1_t vmaxu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmaxu_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vmaxu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmaxu_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vmaxu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmaxu_vv_u32m1(op1,op2);
}

__rv32 vuint8m1_t vmaxu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmaxu_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vmaxu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmaxu_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vmaxu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmaxu_vx_u32m1(op1,op2);
}

__rv32 vint8m1_t vmax_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmax_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vmax_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmax_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vmax_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmax_vv_i32m1(op1,op2);
}

__rv32 vint8m1_t vmax_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmax_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vmax_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmax_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vmax_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmax_vx_i32m1(op1,op2);
}

//masked functions
__rv32 vuint8m1_t vminu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vminu_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vminu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vminu_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vminu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vminu_vv_u32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vminu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vminu_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vminu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vminu_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vminu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vminu_vx_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vmin_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmin_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmin_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmin_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmin_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmin_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vmin_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmin_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmin_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmin_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmin_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmin_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vmaxu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmaxu_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vmaxu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmaxu_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vmaxu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmaxu_vv_u32m1_m(mask,op1,op2);
}


__rv32 vuint8m1_t vmaxu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmaxu_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vmaxu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmaxu_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vmaxu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmaxu_vx_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vmax_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmax_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmax_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmax_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmax_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmax_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vmax_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmax_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmax_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmax_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmax_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmax_vx_i32m1_m(mask,op1,op2);
}

/*************Vector Single-Width Integer Multiply Functions****************/
__rv32 vint8m1_t vmul_vv_i8m1(vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmul_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vmul_vv_i16m1(vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmul_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vmul_vv_i32m1(vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmul_vv_i32m1(op1,op2);
}

__rv32 vuint8m1_t vmul_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmul_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vmul_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmul_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vmul_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmul_vv_u32m1(op1,op2);
}

__rv32 vint8m1_t vmul_vx_i8m1(vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmul_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vmul_vx_i16m1(vint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmul_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vmul_vx_i32m1(vint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmul_vx_i32m1(op1,op2);
}

__rv32 vuint8m1_t vmul_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmul_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vmul_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmul_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vmul_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmul_vx_u32m1(op1,op2);
}


__rv32 vint8m1_t vmulh_vv_i8m1(vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmulh_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vmulh_vv_i16m1(vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmulh_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vmulh_vv_i32m1(vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmulh_vv_i32m1(op1,op2);
}

__rv32 vint8m1_t vmulh_vx_i8m1(vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmulh_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vmulh_vx_i16m1(vint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmulh_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vmulh_vx_i32m1(vint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmulh_vx_i32m1(op1,op2);
}

__rv32 vuint8m1_t vmulhu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmulhu_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vmulhu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmulhu_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vmulhu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmulhu_vv_u32m1(op1,op2);
}

__rv32 vuint8m1_t vmulhu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmulhu_vx_u8m1(op1,op2);
}


__rv32 vuint16m1_t vmulhu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmulhu_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vmulhu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmulhu_vx_u32m1(op1,op2);
}

__rv32 vint8m1_t vmulhsu_vv_i8m1(vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmulhsu_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vmulhsu_vv_i16m1(vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmulhsu_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vmulhsu_vv_i32m1(vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmulhsu_vv_i32m1(op1,op2);
}

__rv32 vint8m1_t vmulhsu_vx_i8m1(vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmulhsu_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vmulhsu_vx_i16m1(vint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmulhsu_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vmulhsu_vx_i32m1(vint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmulhsu_vx_i32m1(op1,op2);
}


//masked functions
__rv32 vint8m1_t vmul_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmul_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmul_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmul_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmul_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmul_vv_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vmul_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmul_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vmul_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmul_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vmul_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmul_vv_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vmul_vx_i8m1_m(vmask_t mask, vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmul_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmul_vx_i16m1_m(vmask_t mask, vint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmul_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmul_vx_i32m1_m(vmask_t mask, vint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmul_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vmul_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmul_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vmul_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmul_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vmul_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmul_vx_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vmulh_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmulh_vv_i8m1_m(mask,op1,op2);
}


__rv32 vint16m1_t vmulh_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmulh_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmulh_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmulh_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vmulh_vx_i8m1_m(vmask_t mask, vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmulh_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmulh_vx_i16m1_m(vmask_t mask, vint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmulh_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmulh_vx_i32m1_m(vmask_t mask, vint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmulh_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vmulhu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmulhu_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vmulhu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmulhu_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vmulhu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmulhu_vv_u32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vmulhu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmulhu_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vmulhu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmulhu_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vmulhu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmulhu_vx_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vmulhsu_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmulhsu_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmulhsu_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmulhsu_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmulhsu_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmulhsu_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vmulhsu_vx_i8m1_m(vmask_t mask, vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vmulhsu_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmulhsu_vx_i16m1_m(vmask_t mask, vint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vmulhsu_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmulhsu_vx_i32m1_m(vmask_t mask, vint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vmulhsu_vx_i32m1_m(mask,op1,op2);
}

/*****************Vector Integer Divide Functions*******************/
__rv32 vuint8m1_t vdivu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vdivu_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vdivu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vdivu_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vdivu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vdivu_vv_u32m1(op1,op2);
}

__rv32 vuint8m1_t vdivu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vdivu_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vdivu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vdivu_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vdivu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vdivu_vx_u32m1(op1,op2);
}

__rv32 vint8m1_t vdiv_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vdiv_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vdiv_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vdiv_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vdiv_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vdiv_vv_i32m1(op1,op2);
}

__rv32 vint8m1_t vdiv_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vdiv_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vdiv_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vdiv_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vdiv_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vdiv_vx_i32m1(op1,op2);
}

__rv32 vuint8m1_t vremu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vremu_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vremu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vremu_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vremu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vremu_vv_u32m1(op1,op2);
}

__rv32 vuint8m1_t vremu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vremu_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vremu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vremu_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vremu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vremu_vx_u32m1(op1,op2);
}

__rv32 vint8m1_t vrem_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vrem_vv_i8m1(op1,op2);
}


__rv32 vint16m1_t vrem_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vrem_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vrem_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vrem_vv_i32m1(op1,op2);
}

__rv32 vint8m1_t vrem_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vrem_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vrem_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vrem_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vrem_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vrem_vx_i32m1(op1,op2);
}

//masked functions
__rv32 vuint8m1_t vdivu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vdivu_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vdivu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vdivu_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vdivu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vdivu_vv_u32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vdivu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vdivu_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vdivu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vdivu_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vdivu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vdivu_vx_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vdiv_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vdiv_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vdiv_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vdiv_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vdiv_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vdiv_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vdiv_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vdiv_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vdiv_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vdiv_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vdiv_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vdiv_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vremu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vremu_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vremu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vremu_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vremu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vremu_vv_u32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vremu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vremu_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vremu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vremu_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vremu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vremu_vx_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vrem_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vrem_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vrem_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vrem_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vrem_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vrem_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vrem_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vrem_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vrem_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vrem_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vrem_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vrem_vx_i32m1_m(mask,op1,op2);
}

/***********Vector Single-Width Integer Multiply-Add Functions************/
__rv32 vint8m1_t vmacc_vv_i8m1(vint8m1_t acc, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmacc_vv_i8m1(acc,op1,op2);
}

__rv32 vint16m1_t vmacc_vv_i16m1(vint16m1_t acc, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmacc_vv_i16m1(acc,op1,op2);
}

__rv32 vint32m1_t vmacc_vv_i32m1(vint32m1_t acc, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmacc_vv_i32m1(acc,op1,op2);
}

__rv32 vuint8m1_t vmacc_vv_u8m1(vuint8m1_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmacc_vv_u8m1(acc,op1,op2);
}

__rv32 vuint16m1_t vmacc_vv_u16m1(vuint16m1_t acc, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmacc_vv_u16m1(acc,op1,op2);
}

__rv32 vuint32m1_t vmacc_vv_u32m1(vuint32m1_t acc, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmacc_vv_u32m1(acc,op1,op2);
}

__rv32 vint8m1_t vmacc_vx_i8m1(vint8m1_t acc, int8_t op1, vint8m1_t op2){
	return __builtin_riscv_vmacc_vx_i8m1(acc,op1,op2);
}

__rv32 vint16m1_t vmacc_vx_i16m1(vint16m1_t acc, int16_t op1, vint16m1_t op2){
	return __builtin_riscv_vmacc_vx_i16m1(acc,op1,op2);
}

__rv32 vint32m1_t vmacc_vx_i32m1(vint32m1_t acc, int32_t op1, vint32m1_t op2){
	return __builtin_riscv_vmacc_vx_i32m1(acc,op1,op2);
}

__rv32 vuint8m1_t vmacc_vx_u8m1(vuint8m1_t acc, uint8_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmacc_vx_u8m1(acc,op1,op2);
}

__rv32 vuint16m1_t vmacc_vx_u16m1(vuint16m1_t acc, uint16_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmacc_vx_u16m1(acc,op1,op2);
}

__rv32 vuint32m1_t vmacc_vx_u32m1(vuint32m1_t acc, uint32_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmacc_vx_u32m1(acc,op1,op2);
}

__rv32 vint8m1_t vnmsac_vv_i8m1(vint8m1_t acc, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vnmsac_vv_i8m1(acc,op1,op2);
}

__rv32 vint16m1_t vnmsac_vv_i16m1(vint16m1_t acc, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vnmsac_vv_i16m1(acc,op1,op2);
}

__rv32 vint32m1_t vnmsac_vv_i32m1(vint32m1_t acc, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vnmsac_vv_i32m1(acc,op1,op2);
}

__rv32 vuint8m1_t vnmsac_vv_u8m1(vuint8m1_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vnmsac_vv_u8m1(acc,op1,op2);
}

__rv32 vuint16m1_t vnmsac_vv_u16m1(vuint16m1_t acc, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vnmsac_vv_u16m1(acc,op1,op2);
}

__rv32 vuint32m1_t vnmsac_vv_u32m1(vuint32m1_t acc, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vnmsac_vv_u32m1(acc,op1,op2);
}

__rv32 vint8m1_t vnmsac_vx_i8m1(vint8m1_t acc, int8_t op1, vint8m1_t op2){
	return __builtin_riscv_vnmsac_vx_i8m1(acc,op1,op2);
}

__rv32 vint16m1_t vnmsac_vx_i16m1(vint16m1_t acc, int16_t op1, vint16m1_t op2){
	return __builtin_riscv_vnmsac_vx_i16m1(acc,op1,op2);
}

__rv32 vint32m1_t vnmsac_vx_i32m1(vint32m1_t acc, int32_t op1, vint32m1_t op2){
	return __builtin_riscv_vnmsac_vx_i32m1(acc,op1,op2);
}

__rv32 vuint8m1_t vnmsac_vx_u8m1(vuint8m1_t acc, uint8_t op1, vuint8m1_t op2){
	return __builtin_riscv_vnmsac_vx_u8m1(acc,op1,op2);
}

__rv32 vuint16m1_t vnmsac_vx_u16m1(vuint16m1_t acc, uint16_t op1, vuint16m1_t op2){
	return __builtin_riscv_vnmsac_vx_u16m1(acc,op1,op2);
}

__rv32 vuint32m1_t vnmsac_vx_u32m1(vuint32m1_t acc, uint32_t op1, vuint32m1_t op2){
	return __builtin_riscv_vnmsac_vx_u32m1(acc,op1,op2);
}

__rv32 vint8m1_t vmadd_vv_i8m1(vint8m1_t acc, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmadd_vv_i8m1(acc,op1,op2);
}

__rv32 vint16m1_t vmadd_vv_i16m1(vint16m1_t acc, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmadd_vv_i16m1(acc,op1,op2);
}

__rv32 vint32m1_t vmadd_vv_i32m1(vint32m1_t acc, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmadd_vv_i32m1(acc,op1,op2);
}

__rv32 vuint8m1_t vmadd_vv_u8m1(vuint8m1_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmadd_vv_u8m1(acc,op1,op2);
}

__rv32 vuint16m1_t vmadd_vv_u16m1(vuint16m1_t acc, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmadd_vv_u16m1(acc,op1,op2);
}

__rv32 vuint32m1_t vmadd_vv_u32m1(vuint32m1_t acc, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmadd_vv_u32m1(acc,op1,op2);
}

__rv32 vint8m1_t vmadd_vx_i8m1(vint8m1_t acc, int8_t op1, vint8m1_t op2){
	return __builtin_riscv_vmadd_vx_i8m1(acc,op1,op2);
}

__rv32 vint16m1_t vmadd_vx_i16m1(vint16m1_t acc, int16_t op1, vint16m1_t op2){
	return __builtin_riscv_vmadd_vx_i16m1(acc,op1,op2);
}

__rv32 vint32m1_t vmadd_vx_i32m1(vint32m1_t acc, int32_t op1, vint32m1_t op2){
	return __builtin_riscv_vmadd_vx_i32m1(acc,op1,op2);
}

__rv32 vuint8m1_t vmadd_vx_u8m1(vuint8m1_t acc, uint8_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmadd_vx_u8m1(acc,op1,op2);
}

__rv32 vuint16m1_t vmadd_vx_u16m1(vuint16m1_t acc, uint16_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmadd_vx_u16m1(acc,op1,op2);
}

__rv32 vuint32m1_t vmadd_vx_u32m1(vuint32m1_t acc, uint32_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmadd_vx_u32m1(acc,op1,op2);
}

__rv32 vint8m1_t vnmsub_vv_i8m1(vint8m1_t acc, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vnmsub_vv_i8m1(acc,op1,op2);
}

__rv32 vint16m1_t vnmsub_vv_i16m1(vint16m1_t acc, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vnmsub_vv_i16m1(acc,op1,op2);
}

__rv32 vint32m1_t vnmsub_vv_i32m1(vint32m1_t acc, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vnmsub_vv_i32m1(acc,op1,op2);
}

__rv32 vuint8m1_t vnmsub_vv_u8m1(vuint8m1_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vnmsub_vv_u8m1(acc,op1,op2);
}

__rv32 vuint16m1_t vnmsub_vv_u16m1(vuint16m1_t acc, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vnmsub_vv_u16m1(acc,op1,op2);
}

__rv32 vuint32m1_t vnmsub_vv_u32m1(vuint32m1_t acc, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vnmsub_vv_u32m1(acc,op1,op2);
}

__rv32 vint8m1_t vnmsub_vx_i8m1(vint8m1_t acc, int8_t op1, vint8m1_t op2){
	return __builtin_riscv_vnmsub_vx_i8m1(acc,op1,op2);
}

__rv32 vint16m1_t vnmsub_vx_i16m1(vint16m1_t acc, int16_t op1, vint16m1_t op2){
	return __builtin_riscv_vnmsub_vx_i16m1(acc,op1,op2);
}

__rv32 vint32m1_t vnmsub_vx_i32m1(vint32m1_t acc, int32_t op1, vint32m1_t op2){
	return __builtin_riscv_vnmsub_vx_i32m1(acc,op1,op2);
}

__rv32 vuint8m1_t vnmsub_vx_u8m1(vuint8m1_t acc, uint8_t op1, vuint8m1_t op2){
	return __builtin_riscv_vnmsub_vx_u8m1(acc,op1,op2);
}

__rv32 vuint16m1_t vnmsub_vx_u16m1(vuint16m1_t acc, uint16_t op1, vuint16m1_t op2){
	return __builtin_riscv_vnmsub_vx_u16m1(acc,op1,op2);
}

__rv32 vuint32m1_t vnmsub_vx_u32m1(vuint32m1_t acc, uint32_t op1, vuint32m1_t op2){
	return __builtin_riscv_vnmsub_vx_u32m1(acc,op1,op2);
}

//masked functions
__rv32 vint8m1_t vmacc_vv_i8m1_m(vmask_t mask, vint8m1_t acc, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmacc_vv_i8m1_m(mask,acc,op1,op2);
}

__rv32 vint16m1_t vmacc_vv_i16m1_m(vmask_t mask, vint16m1_t acc, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmacc_vv_i16m1_m(mask,acc,op1,op2);
}

__rv32 vint32m1_t vmacc_vv_i32m1_m(vmask_t mask, vint32m1_t acc, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmacc_vv_i32m1_m(mask,acc,op1,op2);
}

__rv32 vuint8m1_t vmacc_vv_u8m1_m(vmask_t mask, vuint8m1_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmacc_vv_u8m1_m(mask,acc,op1,op2);
}

__rv32 vuint16m1_t vmacc_vv_u16m1_m(vmask_t mask, vuint16m1_t acc, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmacc_vv_u16m1_m(mask,acc,op1,op2);
}

__rv32 vuint32m1_t vmacc_vv_u32m1_m(vmask_t mask, vuint32m1_t acc, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmacc_vv_u32m1_m(mask,acc,op1,op2);
}

__rv32 vint8m1_t vmacc_vx_i8m1_m(vmask_t mask, vint8m1_t acc, int8_t op1, vint8m1_t op2){
	return __builtin_riscv_vmacc_vx_i8m1_m(mask,acc,op1,op2);
}

__rv32 vint16m1_t vmacc_vx_i16m1_m(vmask_t mask, vint16m1_t acc, int16_t op1, vint16m1_t op2){
	return __builtin_riscv_vmacc_vx_i16m1_m(mask,acc,op1,op2);
}

__rv32 vint32m1_t vmacc_vx_i32m1_m(vmask_t mask, vint32m1_t acc, int32_t op1, vint32m1_t op2){
	return __builtin_riscv_vmacc_vx_i32m1_m(mask,acc,op1,op2);
}

__rv32 vuint8m1_t vmacc_vx_u8m1_m(vmask_t mask, vuint8m1_t acc, uint8_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmacc_vx_u8m1_m(mask,acc,op1,op2);
}

__rv32 vuint16m1_t vmacc_vx_u16m1_m(vmask_t mask, vuint16m1_t acc, uint16_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmacc_vx_u16m1_m(mask,acc,op1,op2);
}

__rv32 vuint32m1_t vmacc_vx_u32m1_m(vmask_t mask, vuint32m1_t acc, uint32_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmacc_vx_u32m1_m(mask,acc,op1,op2);
}

__rv32 vint8m1_t vnmsac_vv_i8m1_m(vmask_t mask, vint8m1_t acc, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vnmsac_vv_i8m1_m(mask,acc,op1,op2);
}

__rv32 vint16m1_t vnmsac_vv_i16m1_m(vmask_t mask, vint16m1_t acc, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vnmsac_vv_i16m1_m(mask,acc,op1,op2);
}

__rv32 vint32m1_t vnmsac_vv_i32m1_m(vmask_t mask, vint32m1_t acc, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vnmsac_vv_i32m1_m(mask,acc,op1,op2);
}

__rv32 vuint8m1_t vnmsac_vv_u8m1_m(vmask_t mask, vuint8m1_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vnmsac_vv_u8m1_m(mask,acc,op1,op2);
}

__rv32 vuint16m1_t vnmsac_vv_u16m1_m(vmask_t mask, vuint16m1_t acc, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vnmsac_vv_u16m1_m(mask,acc,op1,op2);
}

__rv32 vuint32m1_t vnmsac_vv_u32m1_m(vmask_t mask, vuint32m1_t acc, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vnmsac_vv_u32m1_m(mask,acc,op1,op2);
}

__rv32 vint8m1_t vnmsac_vx_i8m1_m(vmask_t mask, vint8m1_t acc, int8_t op1, vint8m1_t op2){
	return __builtin_riscv_vnmsac_vx_i8m1_m(mask,acc,op1,op2);
}

__rv32 vint16m1_t vnmsac_vx_i16m1_m(vmask_t mask, vint16m1_t acc, int16_t op1, vint16m1_t op2){
	return __builtin_riscv_vnmsac_vx_i16m1_m(mask,acc,op1,op2);
}

__rv32 vint32m1_t vnmsac_vx_i32m1_m(vmask_t mask, vint32m1_t acc, int32_t op1, vint32m1_t op2){
	return __builtin_riscv_vnmsac_vx_i32m1_m(mask,acc,op1,op2);
}

__rv32 vuint8m1_t vnmsac_vx_u8m1_m(vmask_t mask, vuint8m1_t acc, uint8_t op1, vuint8m1_t op2){
	return __builtin_riscv_vnmsac_vx_u8m1_m(mask,acc,op1,op2);
}

__rv32 vuint16m1_t vnmsac_vx_u16m1_m(vmask_t mask, vuint16m1_t acc, uint16_t op1, vuint16m1_t op2){
	return __builtin_riscv_vnmsac_vx_u16m1_m(mask,acc,op1,op2);
}

__rv32 vuint32m1_t vnmsac_vx_u32m1_m(vmask_t mask, vuint32m1_t acc, uint32_t op1, vuint32m1_t op2){
	return __builtin_riscv_vnmsac_vx_u32m1_m(mask,acc,op1,op2);
}


__rv32 vint8m1_t vmadd_vv_i8m1_m(vmask_t mask, vint8m1_t acc, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmadd_vv_i8m1_m(mask,acc,op1,op2);
}

__rv32 vint16m1_t vmadd_vv_i16m1_m(vmask_t mask, vint16m1_t acc, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmadd_vv_i16m1_m(mask,acc,op1,op2);
}

__rv32 vint32m1_t vmadd_vv_i32m1_m(vmask_t mask, vint32m1_t acc, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmadd_vv_i32m1_m(mask,acc,op1,op2);
}

__rv32 vuint8m1_t vmadd_vv_u8m1_m(vmask_t mask, vuint8m1_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmadd_vv_u8m1_m(mask,acc,op1,op2);
}

__rv32 vuint16m1_t vmadd_vv_u16m1_m(vmask_t mask, vuint16m1_t acc, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmadd_vv_u16m1_m(mask,acc,op1,op2);
}

__rv32 vuint32m1_t vmadd_vv_u32m1_m(vmask_t mask, vuint32m1_t acc, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmadd_vv_u32m1_m(mask,acc,op1,op2);
}

__rv32 vint8m1_t vmadd_vx_i8m1_m(vmask_t mask, vint8m1_t acc, int8_t op1, vint8m1_t op2){
	return __builtin_riscv_vmadd_vx_i8m1_m(mask,acc,op1,op2);
}

__rv32 vint16m1_t vmadd_vx_i16m1_m(vmask_t mask, vint16m1_t acc, int16_t op1, vint16m1_t op2){
	return __builtin_riscv_vmadd_vx_i16m1_m(mask,acc,op1,op2);
}

__rv32 vint32m1_t vmadd_vx_i32m1_m(vmask_t mask, vint32m1_t acc, int32_t op1, vint32m1_t op2){
	return __builtin_riscv_vmadd_vx_i32m1_m(mask,acc,op1,op2);
}

__rv32 vuint8m1_t vmadd_vx_u8m1_m(vmask_t mask, vuint8m1_t acc, uint8_t op1, vuint8m1_t op2){
	return __builtin_riscv_vmadd_vx_u8m1_m(mask,acc,op1,op2);
}

__rv32 vuint16m1_t vmadd_vx_u16m1_m(vmask_t mask, vuint16m1_t acc, uint16_t op1, vuint16m1_t op2){
	return __builtin_riscv_vmadd_vx_u16m1_m(mask,acc,op1,op2);
}

__rv32 vuint32m1_t vmadd_vx_u32m1_m(vmask_t mask, vuint32m1_t acc, uint32_t op1, vuint32m1_t op2){
	return __builtin_riscv_vmadd_vx_u32m1_m(mask,acc,op1,op2);
}

__rv32 vint8m1_t vnmsub_vv_i8m1_m(vmask_t mask, vint8m1_t acc, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vnmsub_vv_i8m1_m(mask,acc,op1,op2);
}

__rv32 vint16m1_t vnmsub_vv_i16m1_m(vmask_t mask, vint16m1_t acc, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vnmsub_vv_i16m1_m(mask,acc,op1,op2);
}

__rv32 vint32m1_t vnmsub_vv_i32m1_m(vmask_t mask, vint32m1_t acc, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vnmsub_vv_i32m1_m(mask,acc,op1,op2);
}

__rv32 vuint8m1_t vnmsub_vv_u8m1_m(vmask_t mask, vuint8m1_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vnmsub_vv_u8m1_m(mask,acc,op1,op2);
}

__rv32 vuint16m1_t vnmsub_vv_u16m1_m(vmask_t mask, vuint16m1_t acc, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vnmsub_vv_u16m1_m(mask,acc,op1,op2);
}

__rv32 vuint32m1_t vnmsub_vv_u32m1_m(vmask_t mask, vuint32m1_t acc, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vnmsub_vv_u32m1_m(mask,acc,op1,op2);
}

__rv32 vint8m1_t vnmsub_vx_i8m1_m(vmask_t mask, vint8m1_t acc, int8_t op1, vint8m1_t op2){
	return __builtin_riscv_vnmsub_vx_i8m1_m(mask,acc,op1,op2);
}

__rv32 vint16m1_t vnmsub_vx_i16m1_m(vmask_t mask, vint16m1_t acc, int16_t op1, vint16m1_t op2){
	return __builtin_riscv_vnmsub_vx_i16m1_m(mask,acc,op1,op2);
}

__rv32 vint32m1_t vnmsub_vx_i32m1_m(vmask_t mask, vint32m1_t acc, int32_t op1, vint32m1_t op2){
	return __builtin_riscv_vnmsub_vx_i32m1_m(mask,acc,op1,op2);
}

__rv32 vuint8m1_t vnmsub_vx_u8m1_m(vmask_t mask, vuint8m1_t acc, uint8_t op1, vuint8m1_t op2){
	return __builtin_riscv_vnmsub_vx_u8m1_m(mask,acc,op1,op2);
}

__rv32 vuint16m1_t vnmsub_vx_u16m1_m(vmask_t mask, vuint16m1_t acc, uint16_t op1, vuint16m1_t op2){
	return __builtin_riscv_vnmsub_vx_u16m1_m(mask,acc,op1,op2);
}


__rv32 vuint32m1_t vnmsub_vx_u32m1_m(vmask_t mask, vuint32m1_t acc, uint32_t op1, vuint32m1_t op2){
	return __builtin_riscv_vnmsub_vx_u32m1_m(mask,acc,op1,op2);
}


/***********Vector Integer Merge Functions************/
__rv32 vint8m1_t vmerge_vvm_i8m1_m (vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vmerge_vvm_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmerge_vvm_i16m1_m (vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vmerge_vvm_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmerge_vvm_i32m1_m (vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vmerge_vvm_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vmerge_vxm_i8m1_m (vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vmerge_vxm_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vmerge_vxm_i16m1_m (vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vmerge_vxm_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vmerge_vxm_i32m1_m (vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vmerge_vxm_i32m1_m(mask,op1,op2);
}

#define vmerge_vim_i8m1_m(mask, op1, op2) __extension__ ({\
	vint8m1_t __ret;\
	__ret = __builtin_riscv_vmerge_vim_i8m1_m(mask,op1,op2);\
	__ret;\
})

#define vmerge_vim_i16m1_m(mask, op1, op2) __extension__ ({\
	vint16m1_t __ret;\
	__ret = __builtin_riscv_vmerge_vim_i16m1_m(mask,op1,op2);\
	__ret;\
})

#define vmerge_vim_i32m1_m(mask, op1, op2) __extension__ ({\
	vint32m1_t __ret;\
	__ret = __builtin_riscv_vmerge_vim_i32m1_m(mask,op1,op2);\
	__ret;\
})

/***********Vector Integer Move Functions************/
__rv32 vint8m1_t vmv_v_v_i8m1(vint8m1_t src){
	return __builtin_riscv_vmv_v_v_i8m1(src);
}

__rv32 vint16m1_t vmv_v_v_i16m1(vint16m1_t src){
	return __builtin_riscv_vmv_v_v_i16m1(src);
}

__rv32 vint32m1_t vmv_v_v_i32m1(vint32m1_t src){
	return __builtin_riscv_vmv_v_v_i32m1(src);
}

__rv32 vuint8m1_t vmv_v_v_u8m1(vuint8m1_t src){
	return __builtin_riscv_vmv_v_v_u8m1(src);
}

__rv32 vuint16m1_t vmv_v_v_u16m1(vuint16m1_t src){
	return __builtin_riscv_vmv_v_v_u16m1(src);
}

__rv32 vuint32m1_t vmv_v_v_u32m1(vuint32m1_t src){
	return __builtin_riscv_vmv_v_v_u32m1(src);
}

__rv32 vint8m1_t vmv_v_x_i8m1(int8_t src){
	return __builtin_riscv_vmv_v_x_i8m1(src);
}

__rv32 vint16m1_t vmv_v_x_i16m1(int16_t src){
	return __builtin_riscv_vmv_v_x_i16m1(src);
}

__rv32 vint32m1_t vmv_v_x_i32m1(int32_t src){
	return __builtin_riscv_vmv_v_x_i32m1(src);
}

__rv32 vuint8m1_t vmv_v_x_u8m1(uint8_t src){
	return __builtin_riscv_vmv_v_x_u8m1(src);
}

__rv32 vuint16m1_t vmv_v_x_u16m1(uint16_t src){
	return __builtin_riscv_vmv_v_x_u16m1(src);
}

__rv32 vuint32m1_t vmv_v_x_u32m1(uint32_t src){
	return __builtin_riscv_vmv_v_x_u32m1(src);
}

#define vmv_v_i_i8m1(src) __extension__ ({\
	vint8m1_t __ret;\
	__ret = __builtin_riscv_vmv_v_i_i8m1(src);\
	__ret;\
})

#define vmv_v_i_i16m1(src) __extension__ ({\
	vint16m1_t __ret;\
	__ret = __builtin_riscv_vmv_v_i_i16m1(src);\
	__ret;\
})

#define vmv_v_i_i32m1(src) __extension__ ({\
	vint32m1_t __ret;\
	__ret = __builtin_riscv_vmv_v_i_i32m1(src);\
	__ret;\
})

#define vmv_v_i_u8m1(src) __extension__ ({\
	vuint8m1_t __ret;\
	__ret = __builtin_riscv_vmv_v_i_u8m1(src);\
	__ret;\
})

#define vmv_v_i_u16m1(src) __extension__ ({\
	vuint16m1_t __ret;\
	__ret = __builtin_riscv_vmv_v_i_u16m1(src);\
	__ret;\
})


#define vmv_v_i_u32m1(src) __extension__ ({\
	vuint32m1_t __ret;\
	__ret = __builtin_riscv_vmv_v_i_u32m1(src);\
	__ret;\
})

/**************Vector Single-Width Saturating Add and Subtract Functions****************/
__rv32 vuint8m1_t vsaddu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsaddu_vv_u8m1(op1,op2);
} 

__rv32 vuint16m1_t vsaddu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsaddu_vv_u16m1(op1,op2);
} 

__rv32 vuint32m1_t vsaddu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsaddu_vv_u32m1(op1,op2);
}  

__rv32 vuint8m1_t vsaddu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsaddu_vx_u8m1(op1,op2);
} 

__rv32 vuint16m1_t vsaddu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vsaddu_vx_u16m1(op1,op2);
} 

__rv32 vuint32m1_t vsaddu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vsaddu_vx_u32m1(op1,op2);
} 

#define vsaddu_vi_u8m1(op1, op2) __extension__ ({\
	vuint8m1_t __ret;\
	__ret = __builtin_riscv_vsaddu_vi_u8m1(op1,op2);\
	__ret;\
})

#define vsaddu_vi_u16m1(op1, op2) __extension__ ({\
	vuint16m1_t __ret;\
	__ret = __builtin_riscv_vsaddu_vi_u16m1(op1,op2);\
	__ret;\
})

#define vsaddu_vi_u32m1(op1, op2) __extension__ ({\
	vuint32m1_t __ret;\
	__ret = __builtin_riscv_vsaddu_vi_u32m1(op1,op2);\
	__ret;\
})


__rv32 vint8m1_t vsadd_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vsadd_vv_i8m1(op1,op2);
}  

__rv32 vint16m1_t vsadd_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vsadd_vv_i16m1(op1,op2);
} 

__rv32 vint32m1_t vsadd_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vsadd_vv_i32m1(op1,op2);
} 

__rv32 vint8m1_t vsadd_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vsadd_vx_i8m1(op1,op2);
} 

__rv32 vint16m1_t vsadd_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vsadd_vx_i16m1(op1,op2);
} 

__rv32 vint32m1_t vsadd_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vsadd_vx_i32m1(op1,op2);
} 


#define vsadd_vi_i8m1(op1, op2) __extension__ ({\
	vint8m1_t __ret;\
	__ret = __builtin_riscv_vsadd_vi_i8m1(op1,op2);\
	__ret;\
})


#define vsadd_vi_i16m1(op1, op2) __extension__ ({\
	vint16m1_t __ret;\
	__ret = __builtin_riscv_vsadd_vi_i16m1(op1,op2);\
	__ret;\
})


#define vsadd_vi_i32m1(op1, op2) __extension__ ({\
	vint32m1_t __ret;\
	__ret = __builtin_riscv_vsadd_vi_i32m1(op1,op2);\
	__ret;\
})


__rv32 vuint8m1_t vssubu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vssubu_vv_u8m1(op1,op2);
} 

__rv32 vuint16m1_t vssubu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vssubu_vv_u16m1(op1,op2);
} 

__rv32 vuint32m1_t vssubu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vssubu_vv_u32m1(op1,op2);
} 


__rv32 vuint8m1_t vssubu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vssubu_vx_u8m1(op1,op2);
} 


__rv32 vuint16m1_t vssubu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vssubu_vx_u16m1(op1,op2);
} 


__rv32 vuint32m1_t vssubu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vssubu_vx_u32m1(op1,op2);
} 


__rv32 vint8m1_t vssub_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vssub_vv_i8m1(op1,op2);
} 


__rv32 vint16m1_t vssub_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vssub_vv_i16m1(op1,op2);
} 
 

__rv32 vint32m1_t vssub_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vssub_vv_i32m1(op1,op2);
} 
 

__rv32 vint8m1_t vssub_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vssub_vx_i8m1(op1,op2);
} 


__rv32 vint16m1_t vssub_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vssub_vx_i16m1(op1,op2);
} 

__rv32 vint32m1_t vssub_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vssub_vx_i32m1(op1,op2);
} 


//masked functions
__rv32 vuint8m1_t vsaddu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vsaddu_vv_u8m1_m(mask,op1,op2);
}


__rv32 vuint16m1_t vsaddu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vsaddu_vv_u16m1_m(mask,op1,op2);
}


__rv32 vuint32m1_t vsaddu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vsaddu_vv_u32m1_m(mask,op1,op2);
}


__rv32 vuint8m1_t vsaddu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vsaddu_vx_u8m1_m(mask,op1,op2);
}


__rv32 vuint16m1_t vsaddu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vsaddu_vx_u16m1_m(mask,op1,op2);
}


__rv32 vuint32m1_t vsaddu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vsaddu_vx_u32m1_m(mask,op1,op2);
}


#define vsaddu_vi_u8m1_m(mask, op1, op2) __extension__ ({\
	vuint8m1_t __ret;\
	__ret = __builtin_riscv_vsaddu_vi_u8m1_m(mask,op1,op2);\
	__ret;\
})


#define vsaddu_vi_u16m1_m(mask, op1, op2) __extension__ ({\
	vuint16m1_t __ret;\
	__ret = __builtin_riscv_vsaddu_vi_u16m1_m(mask,op1,op2);\
	__ret;\
})

#define vsaddu_vi_u32m1_m(mask, op1, op2) __extension__ ({\
	vuint32m1_t __ret;\
	__ret = __builtin_riscv_vsaddu_vi_u32m1_m(mask,op1,op2);\
	__ret;\
})


__rv32 vint8m1_t vsadd_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vsadd_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vsadd_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vsadd_vv_i16m1_m(mask,op1,op2);
}


__rv32 vint32m1_t vsadd_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vsadd_vv_i32m1_m(mask,op1,op2);
}


__rv32 vint8m1_t vsadd_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vsadd_vx_i8m1_m(mask,op1,op2);
}


__rv32 vint16m1_t vsadd_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vsadd_vx_i16m1_m(mask,op1,op2);
}


__rv32 vint32m1_t vsadd_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vsadd_vx_i32m1_m(mask,op1,op2);
}


#define vsadd_vi_i8m1_m(mask, op1, op2) __extension__ ({\
	vint8m1_t __ret;\
	__ret = __builtin_riscv_vsadd_vi_i8m1_m(mask,op1,op2);\
	__ret;\
})


#define vsadd_vi_i16m1_m(mask, op1, op2) __extension__ ({\
	vint16m1_t __ret;\
	__ret = __builtin_riscv_vsadd_vi_i16m1_m(mask,op1,op2);\
	__ret;\
})


#define vsadd_vi_i32m1_m(mask, op1, op2) __extension__ ({\
	vint32m1_t __ret;\
	__ret = __builtin_riscv_vsadd_vi_i32m1_m(mask,op1,op2);\
	__ret;\
})

__rv32 vuint8m1_t vssubu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vssubu_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vssubu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vssubu_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vssubu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vssubu_vv_u32m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vssubu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vssubu_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vssubu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vssubu_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vssubu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vssubu_vx_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vssub_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vssub_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vssub_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vssub_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vssub_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vssub_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vssub_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vssub_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vssub_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vssub_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vssub_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vssub_vx_i32m1_m(mask,op1,op2);
}

/*************Vector Single-Width Averaging Add and Subtract Functions****************/
__rv32 vuint8m1_t vaaddu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vaaddu_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vaaddu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vaaddu_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vaaddu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vaaddu_vv_u32m1(op1,op2);
}

__rv32 vuint8m1_t vaaddu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vaaddu_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vaaddu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vaaddu_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vaaddu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vaaddu_vx_u32m1(op1,op2);
}

__rv32 vint8m1_t vaadd_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vaadd_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vaadd_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vaadd_vv_i16m1(op1,op2);
}


__rv32 vint32m1_t vaadd_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vaadd_vv_i32m1(op1,op2);
}

__rv32 vint8m1_t vaadd_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vaadd_vx_i8m1(op1,op2);
}


__rv32 vint16m1_t vaadd_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vaadd_vx_i16m1(op1,op2);
}

__rv32 vuint32m1_t vaadd_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vaadd_vx_i32m1(op1,op2);
}


__rv32 vuint8m1_t vasubu_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vasubu_vv_u8m1(op1,op2);
}


__rv32 vuint16m1_t vasubu_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vasubu_vv_u16m1(op1,op2);
}


__rv32 vuint32m1_t vasubu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vasubu_vv_u32m1(op1,op2);
}

__rv32 vuint8m1_t vasubu_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vasubu_vx_u8m1(op1,op2);
}


__rv32 vuint16m1_t vasubu_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vasubu_vx_u16m1(op1,op2);
}


__rv32 vuint32m1_t vasubu_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vasubu_vx_u32m1(op1,op2);
}


__rv32 vint8m1_t vasub_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vasub_vv_i8m1(op1,op2);
}


__rv32 vint16m1_t vasub_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vasub_vv_i16m1(op1,op2);
}


__rv32 vint32m1_t vasub_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vasub_vv_i32m1(op1,op2);
}

__rv32 vint8m1_t vasub_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vasub_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vasub_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vasub_vx_i16m1(op1,op2);
}

__rv32 vuint32m1_t vasub_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vasub_vx_i32m1(op1,op2);
}


//masked functions
__rv32 vuint8m1_t vaaddu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vaaddu_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vaaddu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vaaddu_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vaaddu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vaaddu_vv_u32m1_m(mask,op1,op2);
}


__rv32 vuint8m1_t vaaddu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vaaddu_vx_u8m1_m(mask,op1,op2);
}


__rv32 vuint16m1_t vaaddu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vaaddu_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vaaddu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vaaddu_vx_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vaadd_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vaadd_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vaadd_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vaadd_vv_i16m1_m(mask,op1,op2);
}


__rv32 vint32m1_t vaadd_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vaadd_vv_i32m1_m(mask,op1,op2);
}


__rv32 vint8m1_t vaadd_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vaadd_vx_i8m1_m(mask,op1,op2);
}


__rv32 vint16m1_t vaadd_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vaadd_vx_i16m1_m(mask,op1,op2);
}


__rv32 vint32m1_t vaadd_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vaadd_vx_i32m1_m(mask,op1,op2);
}


__rv32 vuint8m1_t vasubu_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vasubu_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vasubu_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vasubu_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vasubu_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vasubu_vv_u32m1_m(mask,op1,op2);
}


__rv32 vuint8m1_t vasubu_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vasubu_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vasubu_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vasubu_vx_u16m1_m(mask,op1,op2);
}


__rv32 vuint32m1_t vasubu_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vasubu_vx_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vasub_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vasub_vv_i8m1_m(mask,op1,op2);
}


__rv32 vint16m1_t vasub_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vasub_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vasub_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vasub_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vasub_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vasub_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vasub_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vasub_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vasub_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vasub_vx_i32m1_m(mask,op1,op2);
}


/***********Vector Single-Width Fractional Multiply with Rounding and Saturation Functions***************/
__rv32 vint8m1_t vsmul_vv_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vsmul_vv_i8m1(op1,op2);
}

__rv32 vint16m1_t vsmul_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vsmul_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vsmul_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vsmul_vv_i32m1(op1,op2);
}

__rv32 vint8m1_t vsmul_vx_i8m1(vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vsmul_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vsmul_vx_i16m1(vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vsmul_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vsmul_vx_i32m1(vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vsmul_vx_i32m1(op1,op2);
}

//masked functions
__rv32 vint8m1_t vsmul_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vsmul_vv_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vsmul_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vsmul_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vsmul_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vsmul_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vsmul_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return __builtin_riscv_vsmul_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vsmul_vx_i16m1_m(vmask_t mask, vint16m1_t op1, int16_t op2){
	return __builtin_riscv_vsmul_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vsmul_vx_i32m1_m(vmask_t mask, vint32m1_t op1, int32_t op2){
	return __builtin_riscv_vsmul_vx_i32m1_m(mask,op1,op2);
}


/**************Vector Single-Width Scaling Shift Functions****************/
__rv32 vuint8m1_t vssrl_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vssrl_vv_u8m1(op1,op2);
}

__rv32 vuint16m1_t vssrl_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vssrl_vv_u16m1(op1,op2);
}

__rv32 vuint32m1_t vssrl_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vssrl_vv_u32m1(op1,op2);
}

__rv32 vuint8m1_t vssrl_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vssrl_vx_u8m1(op1,op2);
}

__rv32 vuint16m1_t vssrl_vx_u16m1(vuint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vssrl_vx_u16m1(op1,op2);
}

__rv32 vuint32m1_t vssrl_vx_u32m1(vuint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vssrl_vx_u32m1(op1,op2);
}

#define vssrl_vi_u8m1(op1, op2) __extension__ ({\
	vuint8m1_t __ret;\
	__ret = __builtin_riscv_vssrl_vi_u8m1(op1,op2);\
	__ret;\
})

#define vssrl_vi_u16m1(op1, op2) __extension__ ({\
	vuint16m1_t __ret;\
	__ret = __builtin_riscv_vssrl_vi_u16m1(op1,op2);\
	__ret;\
})

#define vssrl_vi_u32m1(op1, op2) __extension__ ({\
	vuint32m1_t __ret;\
	__ret = __builtin_riscv_vssrl_vi_u32m1(op1,op2);\
	__ret;\
})

__rv32 vint8m1_t vssra_vv_i8m1(vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vssra_vv_i8m1(op1,op2);
}


__rv32 vint16m1_t vssra_vv_i16m1(vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vssra_vv_i16m1(op1,op2);
}

__rv32 vint32m1_t vssra_vv_i32m1(vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vssra_vv_i32m1(op1,op2);
}


__rv32 vint8m1_t vssra_vx_i8m1(vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vssra_vx_i8m1(op1,op2);
}

__rv32 vint16m1_t vssra_vx_i16m1(vint16m1_t op1, uint16_t op2){
	return __builtin_riscv_vssra_vx_i16m1(op1,op2);
}

__rv32 vint32m1_t vssra_vx_i32m1(vint32m1_t op1, uint32_t op2){
	return __builtin_riscv_vssra_vx_i32m1(op1,op2);
}

#define vssra_vi_i8m1(op1, op2) __extension__ ({\
	vint8m1_t __ret;\
	__ret = __builtin_riscv_vssra_vi_i8m1(op1,op2);\
	__ret;\
})

#define vssra_vi_i16m1(op1, op2) __extension__ ({\
	vint16m1_t __ret;\
	__ret = __builtin_riscv_vssra_vi_i16m1(op1,op2);\
	__ret;\
})

#define vssra_vi_i32m1(op1, op2) __extension__ ({\
	vint32m1_t __ret;\
	__ret = __builtin_riscv_vssra_vi_i32m1(op1,op2);\
	__ret;\
})

//masked functions
__rv32 vuint8m1_t vssrl_vv_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vssrl_vv_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vssrl_vv_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vssrl_vv_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vssrl_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vssrl_vv_u32m1_m(mask,op1,op2);
}


__rv32 vuint8m1_t vssrl_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vssrl_vx_u8m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vssrl_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint8_t op2){
	return __builtin_riscv_vssrl_vx_u16m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vssrl_vx_u32m1_m(vmask_t mask, vuint32m1_t op1, uint8_t op2){
	return __builtin_riscv_vssrl_vx_u32m1_m(mask,op1,op2);
}


#define vssrl_vi_u8m1_m(mask, op1, op2) __extension__ ({\
	vuint8m1_t __ret;\
	__ret = __builtin_riscv_vssrl_vi_u8m1_m(mask,op1,op2);\
	__ret;\
})

#define vssrl_vi_u16m1_m(mask, op1, op2) __extension__ ({\
	vuint16m1_t __ret;\
	__ret = __builtin_riscv_vssrl_vi_u16m1_m(mask,op1,op2);\
	__ret;\
})


#define vssrl_vi_u32m1_m(mask, op1, op2) __extension__ ({\
	vuint32m1_t __ret;\
	__ret = __builtin_riscv_vssrl_vi_u32m1_m(mask,op1,op2);\
	__ret;\
})


__rv32 vint8m1_t vssra_vv_i8m1_m(vmask_t mask, vint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vssra_vv_i8m1_m(mask,op1,op2);
}


__rv32 vint16m1_t vssra_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vssra_vv_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vssra_vv_i32m1_m(vmask_t mask, vint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vssra_vv_i32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vssra_vx_i8m1_m(vmask_t mask, vint8m1_t op1, uint8_t op2){
	return __builtin_riscv_vssra_vx_i8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vssra_vx_i16m1_m(vmask_t mask, vint16m1_t op1, uint8_t op2){
	return __builtin_riscv_vssra_vx_i16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vssra_vx_i32m1_m(vmask_t mask, vint32m1_t op1, uint8_t op2){
	return __builtin_riscv_vssra_vx_i32m1_m(mask,op1,op2);
}

#define vssra_vi_i8m1_m(mask, op1, op2) __extension__ ({\
	vint8m1_t __ret;\
	__ret = __builtin_riscv_vssra_vi_i8m1_m(mask,op1,op2);\
	__ret;\
})

#define vssra_vi_i16m1_m(mask, op1, op2) __extension__ ({\
	vint16m1_t __ret;\
	__ret = __builtin_riscv_vssra_vi_i16m1_m(mask,op1,op2);\
	__ret;\
})


#define vssra_vi_i32m1_m(mask, op1, op2) __extension__ ({\
	vint32m1_t __ret;\
	__ret = __builtin_riscv_vssra_vi_i32m1_m(mask,op1,op2);\
	__ret;\
})



/*************Vector Single-Width Floating-Point Add/Subtract Functions****************/
__rv32 vfloat32m1_t vfadd_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfadd_vv_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfadd_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfadd_vf_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfsub_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfsub_vv_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfsub_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfsub_vf_f32m1(op1,op2);
}


__rv32 vfloat32m1_t vfrsub_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfrsub_vf_f32m1(op1,op2);
}


//masked functions
__rv32 vfloat32m1_t vfadd_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfadd_vv_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfadd_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfadd_vf_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfsub_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfsub_vv_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfsub_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfsub_vf_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfrsub_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfrsub_vf_f32m1_m(mask,op1,op2);
}


/*************Vector Single-Width Floating-Point Multiply/Divide Functions****************/
__rv32 vfloat32m1_t vfmul_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmul_vv_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfmul_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfmul_vf_f32m1(op1,op2);
}


__rv32 vfloat32m1_t vfdiv_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfdiv_vv_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfdiv_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfdiv_vf_f32m1(op1,op2);
}


__rv32 vfloat32m1_t vfrdiv_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfrdiv_vf_f32m1(op1,op2);
}


//masked functions
__rv32 vfloat32m1_t vfmul_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmul_vv_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfmul_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfmul_vf_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfdiv_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfdiv_vv_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfdiv_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfdiv_vf_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfrdiv_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfrdiv_vf_f32m1_m(mask,op1,op2);
}

/*************Vector Single-Width Floating-Point Fused Multiply-Add Functions****************/
__rv32 vfloat32m1_t vfmacc_vv_f32m1(vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmacc_vv_f32m1(acc,op1,op2);
}


__rv32 vfloat32m1_t vfmacc_vf_f32m1(vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmacc_vf_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmacc_vv_f32m1(vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmacc_vv_f32m1(acc,op1,op2);
}


__rv32 vfloat32m1_t vfnmacc_vf_f32m1(vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmacc_vf_f32m1(acc,op1,op2);
}


__rv32 vfloat32m1_t vfmsac_vv_f32m1(vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmsac_vv_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfmsac_vf_f32m1(vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmsac_vf_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmsac_vv_f32m1(vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmsac_vv_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmsac_vf_f32m1(vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmsac_vf_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfmadd_vv_f32m1(vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmadd_vv_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfmadd_vf_f32m1(vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmadd_vf_f32m1(acc,op1,op2);
}


__rv32 vfloat32m1_t vfnmadd_vv_f32m1(vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmadd_vv_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmadd_vf_f32m1(vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmadd_vf_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfmsub_vv_f32m1(vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmsub_vv_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfmsub_vf_f32m1(vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmsub_vf_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmsub_vv_f32m1(vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmsub_vv_f32m1(acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmsub_vf_f32m1(vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmsub_vf_f32m1(acc,op1,op2);
}


//masked functions
__rv32 vfloat32m1_t vfmacc_vv_f32m1_m(vmask_t mask, vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmacc_vv_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfmacc_vf_f32m1_m(vmask_t mask, vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmacc_vf_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmacc_vv_f32m1_m(vmask_t mask, vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmacc_vv_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmacc_vf_f32m1_m(vmask_t mask, vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmacc_vf_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfmsac_vv_f32m1_m(vmask_t mask, vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmsac_vv_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfmsac_vf_f32m1_m(vmask_t mask, vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmsac_vf_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmsac_vv_f32m1_m(vmask_t mask, vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmsac_vv_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmsac_vf_f32m1_m(vmask_t mask, vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmsac_vf_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfmadd_vv_f32m1_m(vmask_t mask, vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmadd_vv_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfmadd_vf_f32m1_m(vmask_t mask, vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmadd_vf_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmadd_vv_f32m1_m(vmask_t mask, vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmadd_vv_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmadd_vf_f32m1_m(vmask_t mask, vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmadd_vf_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfmsub_vv_f32m1_m(vmask_t mask, vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmsub_vv_f32m1_m(mask,acc,op1,op2);
}


__rv32 vfloat32m1_t vfmsub_vf_f32m1_m(vmask_t mask, vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmsub_vf_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmsub_vv_f32m1_m(vmask_t mask, vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmsub_vv_f32m1_m(mask,acc,op1,op2);
}

__rv32 vfloat32m1_t vfnmsub_vf_f32m1_m(vmask_t mask, vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfnmsub_vf_f32m1_m(mask,acc,op1,op2);
}


/*************Vector Floating-Point Square-Root Functions****************/
__rv32 vfloat32m1_t vfsqrt_v_f32m1(vfloat32m1_t op1){
	return __builtin_riscv_vfsqrt_v_f32m1(op1);
}

//masked functions
__rv32 vfloat32m1_t vfsqrt_v_f32m1_m(vmask_t mask,vfloat32m1_t op1){
	return __builtin_riscv_vfsqrt_v_f32m1_m(mask,op1);
}


/*************Vector  Floating-Point MIM/MAX Functions****************/
__rv32 vfloat32m1_t vfmin_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmin_vv_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfmin_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfmin_vf_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfmax_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmax_vv_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfmax_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfmax_vf_f32m1(op1,op2);
}

//masked functions
__rv32 vfloat32m1_t vfmin_vv_f32m1_m(vmask_t mask,vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmin_vv_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfmin_vf_f32m1_m(vmask_t mask,vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfmin_vf_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfmax_vv_f32m1_m(vmask_t mask,vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfmax_vv_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfmax_vf_f32m1_m(vmask_t mask,vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfmax_vf_f32m1_m(mask,op1,op2);
}


/*************Vector Floating-Point Sign-Injection Functions****************/
__rv32 vfloat32m1_t vfsgnj_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfsgnj_vv_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfsgnj_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfsgnj_vf_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfsgnjn_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfsgnjn_vv_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfsgnjn_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfsgnjn_vf_f32m1(op1,op2);
}


__rv32 vfloat32m1_t vfsgnjx_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfsgnjx_vv_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfsgnjx_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfsgnjx_vf_f32m1(op1,op2);
}


//masked functions
__rv32 vfloat32m1_t vfsgnj_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfsgnj_vv_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfsgnj_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfsgnj_vf_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfsgnjn_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfsgnjn_vv_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfsgnjn_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfsgnjn_vf_f32m1_m(mask,op1,op2);
}


__rv32 vfloat32m1_t vfsgnjx_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfsgnjx_vv_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfsgnjx_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfsgnjx_vf_f32m1_m(mask,op1,op2);
}

/*************Vector Floating-Point Compare Functions****************/
__rv32 vmask_t vmfeq_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vmfeq_vv_f32m1(op1,op2);
}

__rv32 vmask_t vmfeq_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmfeq_vf_f32m1(op1,op2);
}

__rv32 vmask_t vmfne_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vmfne_vv_f32m1(op1,op2);
}


__rv32 vmask_t vmfne_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmfne_vf_f32m1(op1,op2);
}


__rv32 vmask_t vmflt_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vmflt_vv_f32m1(op1,op2);
}


__rv32 vmask_t vmflt_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmflt_vf_f32m1(op1,op2);
}

__rv32 vmask_t vmfle_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vmfle_vv_f32m1(op1,op2);
}

__rv32 vmask_t vmfle_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmfle_vf_f32m1(op1,op2);
}

__rv32 vmask_t vmfgt_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmfgt_vf_f32m1(op1,op2);
}

__rv32 vmask_t vmfge_vf_f32m1(vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmfge_vf_f32m1(op1,op2);
}

//masked functions
__rv32 vmask_t vmfeq_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vmfeq_vv_f32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmfeq_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmfeq_vf_f32m1_m(mask,op1,op2);
}


__rv32 vmask_t vmfne_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vmfne_vv_f32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmfne_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmfne_vf_f32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmflt_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vmflt_vv_f32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmflt_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmflt_vf_f32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmfle_vv_f32m1_m(vmask_t mask, vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vmfle_vv_f32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmfle_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmfle_vf_f32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmfgt_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmfgt_vf_f32m1_m(mask,op1,op2);
}

__rv32 vmask_t vmfge_vf_f32m1_m(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vmfge_vf_f32m1_m(mask,op1,op2);
}

/*************Vector Floating-Point Classify Functions****************/
__rv32 vuint32m1_t vfclass_v_f32m1(vfloat32m1_t op1){
	return __builtin_riscv_vfclass_v_f32m1(op1);
}

//masked functions
__rv32 vuint32m1_t vfclass_v_f32m1_m(vmask_t mask, vfloat32m1_t op1){
	return __builtin_riscv_vfclass_v_f32m1_m(mask,op1 );
}


/*************Vector Floating-Point Merge Functions****************/
__rv32 vfloat32m1_t vfmerge_vfm_f32m1(vmask_t mask, vfloat32m1_t op1, float32_t op2){
	return __builtin_riscv_vfmerge_vfm_f32m1(mask,op1,op2);
}

/*************Vector Floating-Point Move Functions****************/
__rv32 vfloat32m1_t vfmv_v_f32m1(float32_t op1){
	return __builtin_riscv_vfmv_v_f32m1(op1);
}

/*************Vector Single-Width Floating-Point/Integer Type-Convert Functions****************/
__rv32 vuint32m1_t vfcvt_xu_f_v_f32m1(vfloat32m1_t op1){
	return __builtin_riscv_vfcvt_xu_f_v_f32m1(op1);
}

__rv32 vint32m1_t vfcvt_x_f_v_f32m1(vfloat32m1_t op1){
	return __builtin_riscv_vfcvt_x_f_v_f32m1(op1);
}


__rv32 vfloat32m1_t vfcvt_f_xu_v_u32m1(vuint32m1_t op1){
	return __builtin_riscv_vfcvt_f_xu_v_u32m1(op1);
}

__rv32 vfloat32m1_t vfcvt_f_x_v_i32m1(vint32m1_t op1){
	return __builtin_riscv_vfcvt_f_x_v_i32m1(op1);
}


//masked functions
__rv32 vuint32m1_t vfcvt_xu_f_v_f32m1_m(vmask_t mask, vfloat32m1_t op1){
	return __builtin_riscv_vfcvt_xu_f_v_f32m1_m(mask,op1);
}

__rv32 vint32m1_t vfcvt_x_f_v_f32m1_m(vmask_t mask, vfloat32m1_t op1){
	return __builtin_riscv_vfcvt_x_f_v_f32m1_m(mask,op1);
}

__rv32 vfloat32m1_t vfcvt_f_xu_v_u32m1_m(vmask_t mask, vuint32m1_t op1){
	return __builtin_riscv_vfcvt_f_xu_v_u32m1_m(mask,op1);
}

__rv32 vfloat32m1_t vfcvt_f_x_v_i32m1_m(vmask_t mask, vint32m1_t op1){
	return __builtin_riscv_vfcvt_f_x_v_i32m1_m(mask,op1);
}



/*************Vector Single-Width Integer Reduction Functions****************/
__rv32 vint8m1_t vredsum_vs_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredsum_vs_i8m1(op1,op2);
}


__rv32 vuint8m1_t vredsum_vs_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredsum_vs_u8m1(op1,op2);
}


__rv32 vint16m1_t vredsum_vs_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredsum_vs_i16m1(op1,op2);
}

__rv32 vuint16m1_t vredsum_vs_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredsum_vs_u16m1(op1,op2);
}

__rv32 vint32m1_t vredsum_vs_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredsum_vs_i32m1(op1,op2);
}

__rv32 vuint32m1_t vredsum_vs_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredsum_vs_u32m1(op1,op2);
}

__rv32 vint8m1_t vredand_vs_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredand_vs_i8m1(op1,op2);
}

__rv32 vuint8m1_t vredand_vs_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredand_vs_u8m1(op1,op2);
}

__rv32 vint16m1_t vredand_vs_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredand_vs_i16m1(op1,op2);
}

__rv32 vuint16m1_t vredand_vs_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredand_vs_u16m1(op1,op2);
}

__rv32 vint32m1_t vredand_vs_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredand_vs_i32m1(op1,op2);
}

__rv32 vuint32m1_t vredand_vs_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredand_vs_u32m1(op1,op2);
}

__rv32 vint8m1_t vredor_vs_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredor_vs_i8m1(op1,op2);
}

__rv32 vuint8m1_t vredor_vs_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredor_vs_u8m1(op1,op2);
}

__rv32 vint16m1_t vredor_vs_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredor_vs_i16m1(op1,op2);
}

__rv32 vuint16m1_t vredor_vs_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredor_vs_u16m1(op1,op2);
}

__rv32 vint32m1_t vredor_vs_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredor_vs_i32m1(op1,op2);
}

__rv32 vuint32m1_t vredor_vs_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredor_vs_u32m1(op1,op2);
}

__rv32 vint8m1_t vredxor_vs_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredxor_vs_i8m1(op1,op2);
}

__rv32 vuint8m1_t vredxor_vs_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredxor_vs_u8m1(op1,op2);
}

__rv32 vint16m1_t vredxor_vs_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredxor_vs_i16m1(op1,op2);
}

__rv32 vuint16m1_t vredxor_vs_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredxor_vs_u16m1(op1,op2);
}


__rv32 vint32m1_t vredxor_vs_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredxor_vs_i32m1(op1,op2);
}

__rv32 vuint32m1_t vredxor_vs_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredxor_vs_u32m1(op1,op2);
}

__rv32 vint8m1_t vredmax_vs_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredmax_vs_i8m1(op1,op2);
}

__rv32 vuint8m1_t vredmaxu_vs_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredmaxu_vs_u8m1(op1,op2);
}

__rv32 vint16m1_t vredmax_vs_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredmax_vs_i16m1(op1,op2);
}

__rv32 vuint16m1_t vredmaxu_vs_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredmaxu_vs_u16m1(op1,op2);
}

__rv32 vint32m1_t vredmax_vs_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredmax_vs_i32m1(op1,op2);
}

__rv32 vuint32m1_t vredmaxu_vs_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredmaxu_vs_u32m1(op1,op2);
}

__rv32 vint8m1_t vredmin_vs_i8m1(vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredmin_vs_i8m1(op1,op2);
}

__rv32 vuint8m1_t vredminu_vs_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredminu_vs_u8m1(op1,op2);
}

__rv32 vint16m1_t vredmin_vs_i16m1(vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredmin_vs_i16m1(op1,op2);
}

__rv32 vuint16m1_t vredminu_vs_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredminu_vs_u16m1(op1,op2);
}

__rv32 vint32m1_t vredmin_vs_i32m1(vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredmin_vs_i32m1(op1,op2);
}

__rv32 vuint32m1_t vredminu_vs_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredminu_vs_u32m1(op1,op2);
}

//masked functions

__rv32 vint8m1_t vredsum_vs_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredsum_vs_i8m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vredsum_vs_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredsum_vs_u8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vredsum_vs_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredsum_vs_i16m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vredsum_vs_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredsum_vs_u16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vredsum_vs_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredsum_vs_i32m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vredsum_vs_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredsum_vs_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vredand_vs_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredand_vs_i8m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vredand_vs_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredand_vs_u8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vredand_vs_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredand_vs_i16m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vredand_vs_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredand_vs_u16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vredand_vs_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredand_vs_i32m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vredand_vs_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredand_vs_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vredor_vs_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredor_vs_i8m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vredor_vs_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredor_vs_u8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vredor_vs_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredor_vs_i16m1_m(mask,op1,op2);
}


__rv32 vuint16m1_t vredor_vs_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredor_vs_u16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vredor_vs_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredor_vs_i32m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vredor_vs_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredor_vs_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vredxor_vs_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredxor_vs_i8m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vredxor_vs_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredxor_vs_u8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vredxor_vs_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredxor_vs_i16m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vredxor_vs_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredxor_vs_u16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vredxor_vs_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredxor_vs_i32m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vredxor_vs_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredxor_vs_u32m1_m(mask,op1,op2);
}


__rv32 vint8m1_t vredmax_vs_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredmax_vs_i8m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vredmaxu_vs_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredmaxu_vs_u8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vredmax_vs_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredmax_vs_i16m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vredmaxu_vs_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredmaxu_vs_u16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vredmax_vs_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredmax_vs_i32m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vredmaxu_vs_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredmaxu_vs_u32m1_m(mask,op1,op2);
}

__rv32 vint8m1_t vredmin_vs_i8m1_m(vmask_t mask, vint8m1_t op1, vint8m1_t op2){
	return __builtin_riscv_vredmin_vs_i8m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vredminu_vs_u8m1_m(vmask_t mask, vuint8m1_t op1, vuint8m1_t op2){
	return __builtin_riscv_vredminu_vs_u8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vredmin_vs_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return __builtin_riscv_vredmin_vs_i16m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vredminu_vs_u16m1_m(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return __builtin_riscv_vredminu_vs_u16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vredmin_vs_i32m1_m(vmask_t mask, vint32m1_t op1, vint32m1_t op2){
	return __builtin_riscv_vredmin_vs_i32m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vredminu_vs_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return __builtin_riscv_vredminu_vs_u32m1_m(mask,op1,op2);
}

/*************Vector Single-Width Floting-Point Reduction Functions****************/
__rv32 vfloat32m1_t vfredosum_vs_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfredosum_vs_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfredsum_vs_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfredsum_vs_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfredmax_vs_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfredmax_vs_f32m1(op1,op2);
}

__rv32 vfloat32m1_t vfredmin_vs_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfredmin_vs_f32m1(op1,op2);
}


//masked functions
__rv32 vfloat32m1_t vfredosum_vs_f32m1_m(vmask_t mask,vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfredosum_vs_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfredsum_vs_f32m1_m(vmask_t mask,vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfredsum_vs_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfredmax_vs_f32m1_m(vmask_t mask,vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfredmax_vs_f32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vfredmin_vs_f32m1_m(vmask_t mask,vfloat32m1_t op1, vfloat32m1_t op2){
	return __builtin_riscv_vfredmin_vs_f32m1_m(mask,op1,op2);
}

/*************Vector Mask-Register Logical Functions****************/
__rv32 vmask_t vmand_mm(vmask_t op1, vmask_t op2){
	return __builtin_riscv_vmand_mm(op1,op2);
}

__rv32 vmask_t vmnand_mm(vmask_t op1, vmask_t op2){
	return __builtin_riscv_vmnand_mm(op1,op2);
}

__rv32 vmask_t vmandnot_mm(vmask_t op1, vmask_t op2){
	return __builtin_riscv_vmandnot_mm(op1,op2);
}

__rv32 vmask_t vmxor_mm(vmask_t op1, vmask_t op2){
	return __builtin_riscv_vmxor_mm(op1,op2);
}

__rv32 vmask_t vmor_mm(vmask_t op1, vmask_t op2){
	return __builtin_riscv_vmor_mm(op1,op2);
}

__rv32 vmask_t vmnor_mm(vmask_t op1, vmask_t op2){
	return __builtin_riscv_vmnor_mm(op1,op2);
}

__rv32 vmask_t vmornot_mm(vmask_t op1, vmask_t op2){
	return __builtin_riscv_vmornot_mm(op1,op2);
}

__rv32 vmask_t vmxnor_mm(vmask_t op1, vmask_t op2){
	return __builtin_riscv_vmxnor_mm(op1,op2);
}

/*************Vector Mask Population Functions****************/
__rv32 uint32_t vpopc_m(vmask_t op1){
	return __builtin_riscv_vpopc_m(op1);
}

//masked functions
__rv32 uint32_t vpopc_m_m(vmask_t mask, vmask_t op1){
	return __builtin_riscv_vpopc_m_m(mask,op1);
}
/*************Vector find-first-set mask bit Functions****************/
__rv32 uint32_t vfirst_m(vmask_t op1){
	return __builtin_riscv_vfirst_m(op1);
}

//masked functions
__rv32 uint32_t vfirst_m_m(vmask_t mask, vmask_t op1){
	return __builtin_riscv_vfirst_m_m(mask,op1);
}

/*************Vector set-before-first mask bit Functions****************/
__rv32 vmask_t vmsbf_m(vmask_t op1){
	return __builtin_riscv_vmsbf_m(op1);
}

//masked functions
__rv32 vmask_t vmsbf_m_m(vmask_t mask, vmask_t op1){
	return __builtin_riscv_vmsbf_m_m(mask,op1);
}

/*************Vector set-including-first mask bit Functions****************/
__rv32 vmask_t vmsif_m(vmask_t op1){
	return __builtin_riscv_vmsif_m(op1);
}

//masked functions
__rv32 vmask_t vmsif_m_m(vmask_t mask, vmask_t op1){
	return __builtin_riscv_vmsif_m_m(mask,op1);
}

/*************Vector set-only-first mask bit Functions****************/
__rv32 vmask_t vmsof_m(vmask_t op1){
	return __builtin_riscv_vmsof_m(op1);
}

//masked functions
__rv32 vmask_t vmsof_m_m(vmask_t mask, vmask_t op1){
	return __builtin_riscv_vmsof_m_m(mask,op1);
}

/*************Vector iota Functions****************/
__rv32 vmask_t viota_m(vmask_t op1){
	return __builtin_riscv_viota_m(op1);
}

//masked functions
__rv32 vmask_t viota_m_m(vmask_t mask, vmask_t op1){
	return __builtin_riscv_viota_m_m(mask,op1);
}

/*************Vector vid Functions****************/
__rv32 vuint8m1_t vid_v_u8m1(void){
	return __builtin_riscv_vid_v_u8m1();
}

__rv32 vuint16m1_t vid_v_u16m1(void){
	return __builtin_riscv_vid_v_u16m1();
}

__rv32 vuint32m1_t vid_v_u32m1(void){
	return __builtin_riscv_vid_v_u32m1();
}

//masked functions
__rv32 vuint8m1_t vid_v_u8m1_m(vmask_t mask){
	return __builtin_riscv_vid_v_u8m1_m(mask);
}

__rv32 vuint16m1_t vid_v_u16m1_m(vmask_t mask){
	return __builtin_riscv_vid_v_u16m1_m(mask);
}

__rv32 vuint32m1_t vid_v_u32m1_m(vmask_t mask){
	return __builtin_riscv_vid_v_u32m1_m(mask);
}

/*************Vector Floating-Point Scalar Move Functions****************/
__rv32 float32_t vfmv_f_s_f32m1(vfloat32m1_t op1){
	return __builtin_riscv_vfmv_f_s_f32m1(op1);
}

__rv32 vfloat32m1_t vfmv_s_f_f32m1(float32_t op1){
	return __builtin_riscv_vfmv_s_f_f32m1(op1);
}

/*************Vector Slideup Functions****************/
//vslideup.vx
__rv32 vint8m1_t vslideup_vx_i8m1(vint8m1_t op1,int32_t offset){
	return __builtin_riscv_vslideup_vx_i8m1(op1,offset);
}

__rv32 vuint8m1_t vslideup_vx_u8m1(vuint8m1_t op1,uint32_t offset){
	return __builtin_riscv_vslideup_vx_u8m1(op1,offset);
}

__rv32 vint16m1_t vslideup_vx_i16m1(vint16m1_t op1,int32_t offset){
	return __builtin_riscv_vslideup_vx_i16m1(op1,offset);
}

__rv32 vuint16m1_t vslideup_vx_u16m1(vuint16m1_t op1,uint32_t offset){
	return __builtin_riscv_vslideup_vx_u16m1(op1,offset);
}

__rv32 vint32m1_t vslideup_vx_i32m1(vint32m1_t op1,int32_t offset){
	return __builtin_riscv_vslideup_vx_i32m1(op1,offset);
}

__rv32 vuint32m1_t vslideup_vx_u32m1(vuint32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslideup_vx_u32m1(op1,offset);
}


__rv32 vfloat32m1_t vslideup_vx_f32m1(vfloat32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslideup_vx_f32m1(op1,offset);
}

//masked functions
__rv32 vint8m1_t vslideup_vx_i8m1_m(vmask_t mask,vint8m1_t op1,int32_t offset){
	return __builtin_riscv_vslideup_vx_i8m1_m(mask,op1,offset);
}

__rv32 vuint8m1_t vslideup_vx_u8m1_m(vmask_t mask,vuint8m1_t op1,uint32_t offset){
	return __builtin_riscv_vslideup_vx_u8m1_m(mask,op1,offset);
}

__rv32 vint16m1_t vslideup_vx_i16m1_m(vmask_t mask,vint16m1_t op1,int32_t offset){
	return __builtin_riscv_vslideup_vx_i16m1_m(mask,op1,offset);
}

__rv32 vuint16m1_t vslideup_vx_u16m1_m(vmask_t mask,vuint16m1_t op1,uint32_t offset){
	return __builtin_riscv_vslideup_vx_u16m1_m(mask,op1,offset);
}

__rv32 vint32m1_t vslideup_vx_i32m1_m(vmask_t mask,vint32m1_t op1,int32_t offset){
	return __builtin_riscv_vslideup_vx_i32m1_m(mask,op1,offset);
}

__rv32 vuint32m1_t vslideup_vx_u32m1_m(vmask_t mask,vuint32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslideup_vx_u32m1_m(mask,op1,offset);
}

__rv32 vfloat32m1_t vslideup_vx_f32m1_m(vmask_t mask,vfloat32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslideup_vx_f32m1_m(mask,op1,offset);
}


//vslideup.vi
#define vslideup_vi_i8m1(op1,offset) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vslideup_vi_i8m1(op1,offset);\
		__ret;\
		})
		

#define vslideup_vi_i16m1(op1,offset) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vslideup_vi_i16m1(op1,offset);\
		__ret;\
		})

#define vslideup_vi_i32m1(op1,offset) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vslideup_vi_i32m1(op1,offset);\
		__ret;\
		})


#define vslideup_vi_f32m1(op1,offset) __extension__({\
		vfloat32m1_t __ret;\
		__ret = __builtin_riscv_vslideup_vi_f32m1(op1,offset);\
		__ret;\
		})

//masked functions
#define vslideup_vi_i8m1_m(mask,op1,offset) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vslideup_vi_i8m1_m(mask,op1,offset);\
		__ret;\
		})

#define vslideup_vi_i16m1_m(mask,op1,offset) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vslideup_vi_i16m1_m(mask,op1,offset);\
		__ret;\
		})

#define vslideup_vi_i32m1_m(mask,op1,offset) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vslideup_vi_i32m1_m(mask,op1,offset);\
		__ret;\
		})

#define vslideup_vi_f32m1_m(mask,op1,offset) __extension__({\
		vfloat32m1_t __ret;\
		__ret = __builtin_riscv_vslideup_vi_f32m1_m(mask,op1,offset);\
		__ret;\
		})


//vslidedown.vx
__rv32 vint8m1_t vslidedown_vx_i8m1(vint8m1_t op1,int32_t offset){
	return __builtin_riscv_vslidedown_vx_i8m1(op1,offset);
}

__rv32 vuint8m1_t vslidedown_vx_u8m1(vuint8m1_t op1,uint32_t offset){
	return __builtin_riscv_vslidedown_vx_u8m1(op1,offset);
}

__rv32 vint16m1_t vslidedown_vx_i16m1(vint16m1_t op1,int32_t offset){
	return __builtin_riscv_vslidedown_vx_i16m1(op1,offset);
}

__rv32 vuint16m1_t vslidedown_vx_u16m1(vuint16m1_t op1,uint32_t offset){
	return __builtin_riscv_vslidedown_vx_u16m1(op1,offset);
}

__rv32 vint32m1_t vslidedown_vx_i32m1(vint32m1_t op1,int32_t offset){
	return __builtin_riscv_vslidedown_vx_i32m1(op1,offset);
}

__rv32 vuint32m1_t vslidedown_vx_u32m1(vuint32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslidedown_vx_u32m1(op1,offset);
}

__rv32 vfloat32m1_t vslidedown_vx_f32m1(vfloat32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslidedown_vx_f32m1(op1,offset);
}

//masked functions
__rv32 vint8m1_t vslidedown_vx_i8m1_m(vmask_t mask,vint8m1_t op1,int32_t offset){
	return __builtin_riscv_vslidedown_vx_i8m1_m(mask,op1,offset);
}

__rv32 vuint8m1_t vslidedown_vx_u8m1_m(vmask_t mask,vuint8m1_t op1,uint32_t offset){
	return __builtin_riscv_vslidedown_vx_u8m1_m(mask,op1,offset);
}

__rv32 vint16m1_t vslidedown_vx_i16m1_m(vmask_t mask,vint16m1_t op1,int32_t offset){
	return __builtin_riscv_vslidedown_vx_i16m1_m(mask,op1,offset);
}

__rv32 vuint16m1_t vslidedown_vx_u16m1_m(vmask_t mask,vuint16m1_t op1,uint32_t offset){
	return __builtin_riscv_vslidedown_vx_u16m1_m(mask,op1,offset);
}

__rv32 vint32m1_t vslidedown_vx_i32m1_m(vmask_t mask,vint32m1_t op1,int32_t offset){
	return __builtin_riscv_vslidedown_vx_i32m1_m(mask,op1,offset);
}

__rv32 vuint32m1_t vslidedown_vx_u32m1_m(vmask_t mask,vuint32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslidedown_vx_u32m1_m(mask,op1,offset);
}

__rv32 vfloat32m1_t vslidedown_vx_f32m1_m(vmask_t mask,vfloat32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslidedown_vx_f32m1_m(mask,op1,offset);
}

//vslidedown.vi
#define vslidedown_vi_i8m1(op1,offset) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vslidedown_vi_i8m1(op1,offset);\
		__ret;\
		})

#define vslidedown_vi_i16m1(op1,offset) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vslidedown_vi_i16m1(op1,offset);\
		__ret;\
		})

#define vslidedown_vi_i32m1(op1,offset) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vslidedown_vi_i32m1(op1,offset);\
		__ret;\
		})

#define vslidedown_vi_f32m1(op1,offset) __extension__({\
		vfloat32m1_t __ret;\
		__ret = __builtin_riscv_vslidedown_vi_f32m1(op1,offset);\
		__ret;\
		})


//masked functions
#define vslidedown_vi_i8m1_m(mask,op1,offset) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vslidedown_vi_i8m1_m(mask,op1,offset);\
		__ret;\
		})


#define vslidedown_vi_i16m1_m(mask,op1,offset) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vslidedown_vi_i16m1_m(mask,op1,offset);\
		__ret;\
		})

#define vslidedown_vi_i32m1_m(mask,op1,offset) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vslidedown_vi_i32m1_m(mask,op1,offset);\
		__ret;\
		})

#define vslidedown_vi_f32m1_m(mask,op1,offset) __extension__({\
		vfloat32m1_t __ret;\
		__ret = __builtin_riscv_vslidedown_vi_f32m1_m(mask,op1,offset);\
		__ret;\
		})


//vslide1up.vx
__rv32 vint8m1_t vslide1up_vx_i8m1(vint8m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1up_vx_i8m1(op1,offset);
}

__rv32 vuint8m1_t vslide1up_vx_u8m1(vuint8m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1up_vx_u8m1(op1,offset);
}

__rv32 vint16m1_t vslide1up_vx_i16m1(vint16m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1up_vx_i16m1(op1,offset);
}

__rv32 vuint16m1_t vslide1up_vx_u16m1(vuint16m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1up_vx_u16m1(op1,offset);
}

__rv32 vint32m1_t vslide1up_vx_i32m1(vint32m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1up_vx_i32m1(op1,offset);
}

__rv32 vuint32m1_t vslide1up_vx_u32m1(vuint32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1up_vx_u32m1(op1,offset);
}

__rv32 vfloat32m1_t vslide1up_vx_f32m1(vfloat32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1up_vx_f32m1(op1,offset);
}

//masked functions
__rv32 vint8m1_t vslide1up_vx_i8m1_m(vmask_t mask,vint8m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1up_vx_i8m1_m(mask,op1,offset);
}

__rv32 vuint8m1_t vslide1up_vx_u8m1_m(vmask_t mask,vuint8m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1up_vx_u8m1_m(mask,op1,offset);
}

__rv32 vint16m1_t vslide1up_vx_i16m1_m(vmask_t mask,vint16m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1up_vx_i16m1_m(mask,op1,offset);
}

__rv32 vuint16m1_t vslide1up_vx_u16m1_m(vmask_t mask,vuint16m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1up_vx_u16m1_m(mask,op1,offset);
}

__rv32 vint32m1_t vslide1up_vx_i32m1_m(vmask_t mask,vint32m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1up_vx_i32m1_m(mask,op1,offset);
}

__rv32 vuint32m1_t vslide1up_vx_u32m1_m(vmask_t mask,vuint32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1up_vx_u32m1_m(mask,op1,offset);
}


__rv32 vfloat32m1_t vslide1up_vx_f32m1_m(vmask_t mask,vfloat32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1up_vx_f32m1_m(mask,op1,offset);
}


//vslide1down.vx
__rv32 vint8m1_t vslide1down_vx_i8m1(vint8m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1down_vx_i8m1(op1,offset);
}

__rv32 vuint8m1_t vslide1down_vx_u8m1(vuint8m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1down_vx_u8m1(op1,offset);
}

__rv32 vint16m1_t vslide1down_vx_i16m1(vint16m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1down_vx_i16m1(op1,offset);
}

__rv32 vuint16m1_t vslide1down_vx_u16m1(vuint16m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1down_vx_u16m1(op1,offset);
}

__rv32 vint32m1_t vslide1down_vx_i32m1(vint32m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1down_vx_i32m1(op1,offset);
}

__rv32 vuint32m1_t vslide1down_vx_u32m1(vuint32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1down_vx_u32m1(op1,offset);
}

__rv32 vfloat32m1_t vslide1down_vx_f32m1(vfloat32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1down_vx_f32m1(op1,offset);
}


//masked functions
__rv32 vint8m1_t vslide1down_vx_i8m1_m(vmask_t mask,vint8m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1down_vx_i8m1_m(mask,op1,offset);
}

__rv32 vuint8m1_t vslide1down_vx_u8m1_m(vmask_t mask,vuint8m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1down_vx_u8m1_m(mask,op1,offset);
}

__rv32 vint16m1_t vslide1down_vx_i16m1_m(vmask_t mask,vint16m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1down_vx_i16m1_m(mask,op1,offset);
}

__rv32 vuint16m1_t vslide1down_vx_u16m1_m(vmask_t mask,vuint16m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1down_vx_u16m1_m(mask,op1,offset);
}

__rv32 vint32m1_t vslide1down_vx_i32m1_m(vmask_t mask,vint32m1_t op1,int32_t offset){
	return __builtin_riscv_vslide1down_vx_i32m1_m(mask,op1,offset);
}

__rv32 vuint32m1_t vslide1down_vx_u32m1_m(vmask_t mask,vuint32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1down_vx_u32m1_m(mask,op1,offset);
}

__rv32 vfloat32m1_t vslide1down_vx_f32m1_m(vmask_t mask,vfloat32m1_t op1,uint32_t offset){
	return __builtin_riscv_vslide1down_vx_f32m1_m(mask,op1,offset);
}

//vrgather.vv
__rv32 vint8m1_t vrgather_vv_i8m1(vint8m1_t op1,vuint8m1_t op2){
	return __builtin_riscv_vrgather_vv_i8m1(op1,op2);
}

__rv32 vuint8m1_t vrgather_vv_u8m1(vuint8m1_t op1,vuint8m1_t op2){
	return __builtin_riscv_vrgather_vv_u8m1(op1,op2);
}

__rv32 vint16m1_t vrgather_vv_i16m1(vint16m1_t op1,vuint16m1_t op2){
	return __builtin_riscv_vrgather_vv_i16m1(op1,op2);
}

__rv32 vuint16m1_t vrgather_vv_u16m1(vuint16m1_t op1,vuint16m1_t op2){
	return __builtin_riscv_vrgather_vv_u16m1(op1,op2);
}

__rv32 vint32m1_t vrgather_vv_i32m1(vint32m1_t op1,vuint32m1_t op2){
	return __builtin_riscv_vrgather_vv_i32m1(op1,op2);
}

__rv32 vuint32m1_t vrgather_vv_u32m1(vuint32m1_t op1,vuint32m1_t op2){
	return __builtin_riscv_vrgather_vv_u32m1(op1,op2);
}

__rv32 vfloat32m1_t vrgather_vv_f32m1(vfloat32m1_t op1,vuint32m1_t op2){
	return __builtin_riscv_vrgather_vv_f32m1(op1,op2);
}

//masked functions
__rv32 vint8m1_t vrgather_vv_i8m1_m(vmask_t mask,vint8m1_t op1,vuint8m1_t op2){
	return __builtin_riscv_vrgather_vv_i8m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vrgather_vv_u8m1_m(vmask_t mask,vuint8m1_t op1,vuint8m1_t op2){
	return __builtin_riscv_vrgather_vv_u8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vrgather_vv_i16m1_m(vmask_t mask,vint16m1_t op1,vuint16m1_t op2){
	return __builtin_riscv_vrgather_vv_i16m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vrgather_vv_u16m1_m(vmask_t mask,vuint16m1_t op1,vuint16m1_t op2){
	return __builtin_riscv_vrgather_vv_u16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vrgather_vv_i32m1_m(vmask_t mask,vint32m1_t op1,vuint32m1_t op2){
	return __builtin_riscv_vrgather_vv_i32m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vrgather_vv_u32m1_m(vmask_t mask,vuint32m1_t op1,vuint32m1_t op2){
	return __builtin_riscv_vrgather_vv_u32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vrgather_vv_f32m1_m(vmask_t mask,vfloat32m1_t op1,vuint32m1_t op2){
	return __builtin_riscv_vrgather_vv_f32m1_m(mask,op1,op2);
}

//vrgather.vx
__rv32 vint8m1_t vrgather_vx_i8m1(vint8m1_t op1,uint8_t op2){
	return __builtin_riscv_vrgather_vx_i8m1(op1,op2);
}

__rv32 vuint8m1_t vrgather_vx_u8m1(vuint8m1_t op1,uint8_t op2){
	return __builtin_riscv_vrgather_vx_u8m1(op1,op2);
}

__rv32 vint16m1_t vrgather_vx_i16m1(vint16m1_t op1,uint16_t op2){
	return __builtin_riscv_vrgather_vx_i16m1(op1,op2);
}

__rv32 vuint16m1_t vrgather_vx_u16m1(vuint16m1_t op1,uint16_t op2){
	return __builtin_riscv_vrgather_vx_u16m1(op1,op2);
}

__rv32 vint32m1_t vrgather_vx_i32m1(vint32m1_t op1,uint32_t op2){
	return __builtin_riscv_vrgather_vx_i32m1(op1,op2);
}

__rv32 vuint32m1_t vrgather_vx_u32m1(vuint32m1_t op1,uint32_t op2){
	return __builtin_riscv_vrgather_vx_u32m1(op1,op2);
}

__rv32 vfloat32m1_t vrgather_vx_f32m1(vfloat32m1_t op1,uint32_t op2){
	return __builtin_riscv_vrgather_vx_f32m1(op1,op2);
}

//masked functions
__rv32 vint8m1_t vrgather_vx_i8m1_m(vmask_t mask,vint8m1_t op1,uint8_t op2){
	return __builtin_riscv_vrgather_vx_i8m1_m(mask,op1,op2);
}

__rv32 vuint8m1_t vrgather_vx_u8m1_m(vmask_t mask,vuint8m1_t op1,uint8_t op2){
	return __builtin_riscv_vrgather_vx_u8m1_m(mask,op1,op2);
}

__rv32 vint16m1_t vrgather_vx_i16m1_m(vmask_t mask,vint16m1_t op1,uint16_t op2){
	return __builtin_riscv_vrgather_vx_i16m1_m(mask,op1,op2);
}

__rv32 vuint16m1_t vrgather_vx_u16m1_m(vmask_t mask,vuint16m1_t op1,uint16_t op2){
	return __builtin_riscv_vrgather_vx_u16m1_m(mask,op1,op2);
}

__rv32 vint32m1_t vrgather_vx_i32m1_m(vmask_t mask,vint32m1_t op1,uint32_t op2){
	return __builtin_riscv_vrgather_vx_i32m1_m(mask,op1,op2);
}

__rv32 vuint32m1_t vrgather_vx_u32m1_m(vmask_t mask,vuint32m1_t op1,uint32_t op2){
	return __builtin_riscv_vrgather_vx_u32m1_m(mask,op1,op2);
}

__rv32 vfloat32m1_t vrgather_vx_f32m1_m(vmask_t mask,vfloat32m1_t op1,uint32_t op2){
	return __builtin_riscv_vrgather_vx_f32m1_m(mask,op1,op2);
}

//vrgather.vi
#define vrgather_vi_i8m1(op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vrgather_vi_i8m1(op1,op2);\
		__ret;\
		})

#define vrgather_vi_i16m1(op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vrgather_vi_i16m1(op1,op2);\
		__ret;\
		})

#define vrgather_vi_i32m1(op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vrgather_vi_i32m1(op1,op2);\
		__ret;\
		})


#define vrgather_vi_f32m1(op1,op2) __extension__({\
		vfloat32m1_t __ret;\
		__ret = __builtin_riscv_vrgather_vi_f32m1(op1,op2);\
		__ret;\
		})


//masked functions
#define vrgather_vi_i8m1_m(mask,op1,op2) __extension__({\
		vint8m1_t __ret;\
		__ret = __builtin_riscv_vrgather_vi_i8m1_m(mask,op1,op2);\
		__ret;\
		})


#define vrgather_vi_i16m1_m(mask,op1,op2) __extension__({\
		vint16m1_t __ret;\
		__ret = __builtin_riscv_vrgather_vi_i16m1_m(mask,op1,op2);\
		__ret;\
		})

#define vrgather_vi_i32m1_m(mask,op1,op2) __extension__({\
		vint32m1_t __ret;\
		__ret = __builtin_riscv_vrgather_vi_i32m1_m(mask,op1,op2);\
		__ret;\
		})


#define vrgather_vi_f32m1_m(mask,op1,op2) __extension__({\
		vfloat32m1_t __ret;\
		__ret = __builtin_riscv_vrgather_vi_f32m1_m(mask,op1,op2);\
		__ret;\
		})

//vcompress
__rv32 vint8m1_t vcompress_vm_i8m1(vmask_t mask,vint8m1_t op1){
	return __builtin_riscv_vcompress_vm_i8m1(mask,op1);
}

__rv32 vuint8m1_t vcompress_vm_u8m1(vmask_t mask,vuint8m1_t op1){
	return __builtin_riscv_vcompress_vm_u8m1(mask,op1);
}

__rv32 vint16m1_t vcompress_vm_i16m1(vmask_t mask,vint16m1_t op1){
	return __builtin_riscv_vcompress_vm_i16m1(mask,op1);
}

__rv32 vuint16m1_t vcompress_vm_u16m1(vmask_t mask,vuint16m1_t op1){
	return __builtin_riscv_vcompress_vm_u16m1(mask,op1);
}

__rv32 vint32m1_t vcompress_vm_i32m1(vmask_t mask,vint32m1_t op1){
	return __builtin_riscv_vcompress_vm_i32m1(mask,op1);
}

__rv32 vuint32m1_t vcompress_vm_u32m1(vmask_t mask,vuint32m1_t op1){
	return __builtin_riscv_vcompress_vm_u32m1(mask,op1);
}

__rv32 vfloat32m1_t vcompress_vm_f32m1(vmask_t mask,vfloat32m1_t op1){
	return __builtin_riscv_vcompress_vm_f32m1(mask,op1);
}

#endif
