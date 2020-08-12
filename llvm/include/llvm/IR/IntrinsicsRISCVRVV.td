//===- IntrinsicsRISCV.td - Defines RISCV Vector intrinsics -------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines all of the RISCV Vector intrinsics.
// Contributed by Hunan Compiler Information Technology Co., Ltd, 
//  http://wwww.compiler-dev.com, Email: <info@compiler-dev.com>.
//===----------------------------------------------------------------------===//

let TargetPrefix = "riscv" in {
  //vsetvli/vsetvl
  def int_riscv_vsetvli : Intrinsic<[llvm_i32_ty],[llvm_i32_ty,llvm_i32_ty],[IntrNoMem,IntrHasSideEffects]>;
  def int_riscv_vsetvl : Intrinsic<[llvm_i32_ty],[llvm_i32_ty,llvm_i32_ty],[IntrNoMem,IntrHasSideEffects]>;


  //Vector Single-Width Integer Add and Subtract Functions
  
  class VgrVgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class VgrVgr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class VgrVgr_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v128i8_ty,llvm_v128i8_ty],[IntrNoMem]>;

  class VgrVgr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class VgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class VgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class VgrVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_v64i16_ty],[IntrNoMem]>;

  class VgrVgr_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4i32_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class VgrVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class VgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class VgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_v32i32_ty],[IntrNoMem]>;


  class VgrGpr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class VgrGpr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class VgrGpr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class VgrGpr_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v128i8_ty,llvm_i32_ty],[IntrNoMem]>;

  class VgrGpr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class VgrGpr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class VgrGpr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class VgrGpr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_i32_ty],[IntrNoMem]>;

  class VgrGpr_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class VgrGpr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class VgrGpr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class VgrGpr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_i32_ty],[IntrNoMem]>;

  
  def int_riscv_vadd_vv_8m1 : VgrVgr_8m1; 
  def int_riscv_vadd_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vadd_vv_8m4 : VgrVgr_8m4; 
  def int_riscv_vadd_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vsub_vv_8m1 : VgrVgr_8m1; 
  def int_riscv_vsub_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vsub_vv_8m4 : VgrVgr_8m4; 
  def int_riscv_vsub_vv_8m8 : VgrVgr_8m8;
	
  def int_riscv_vadd_vv_16m1 : VgrVgr_16m1; 
  def int_riscv_vadd_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vadd_vv_16m4 : VgrVgr_16m4; 
  def int_riscv_vadd_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vsub_vv_16m1 : VgrVgr_16m1; 
  def int_riscv_vsub_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vsub_vv_16m4 : VgrVgr_16m4; 
  def int_riscv_vsub_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vadd_vv_32m1 : VgrVgr_32m1; 
  def int_riscv_vadd_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vadd_vv_32m4 : VgrVgr_32m4; 
  def int_riscv_vadd_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vsub_vv_32m1 : VgrVgr_32m1; 
  def int_riscv_vsub_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vsub_vv_32m4 : VgrVgr_32m4; 
  def int_riscv_vsub_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vadd_vx_8m1 : VgrGpr_8m1; 
  def int_riscv_vadd_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vadd_vx_8m4 : VgrGpr_8m4; 
  def int_riscv_vadd_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vadd_vi_8m1 : VgrGpr_8m1; 
  def int_riscv_vadd_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vadd_vi_8m4 : VgrGpr_8m4; 
  def int_riscv_vadd_vi_8m8 : VgrGpr_8m8;

  def int_riscv_vsub_vx_8m1 : VgrGpr_8m1; 
  def int_riscv_vsub_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vsub_vx_8m4 : VgrGpr_8m4; 
  def int_riscv_vsub_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vrsub_vx_8m1 : VgrGpr_8m1; 
  def int_riscv_vrsub_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vrsub_vx_8m4 : VgrGpr_8m4; 
  def int_riscv_vrsub_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vrsub_vi_8m1 : VgrGpr_8m1; 
  def int_riscv_vrsub_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vrsub_vi_8m4 : VgrGpr_8m4; 
  def int_riscv_vrsub_vi_8m8 : VgrGpr_8m8;

  def int_riscv_vadd_vx_16m1 : VgrGpr_16m1; 
  def int_riscv_vadd_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vadd_vx_16m4 : VgrGpr_16m4; 
  def int_riscv_vadd_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vadd_vi_16m1 : VgrGpr_16m1; 
  def int_riscv_vadd_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vadd_vi_16m4 : VgrGpr_16m4; 
  def int_riscv_vadd_vi_16m8 : VgrGpr_16m8;

  def int_riscv_vsub_vx_16m1 : VgrGpr_16m1; 
  def int_riscv_vsub_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vsub_vx_16m4 : VgrGpr_16m4; 
  def int_riscv_vsub_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vrsub_vx_16m1 : VgrGpr_16m1; 
  def int_riscv_vrsub_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vrsub_vx_16m4 : VgrGpr_16m4; 
  def int_riscv_vrsub_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vrsub_vi_16m1 : VgrGpr_16m1; 
  def int_riscv_vrsub_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vrsub_vi_16m4 : VgrGpr_16m4; 
  def int_riscv_vrsub_vi_16m8 : VgrGpr_16m8;

  def int_riscv_vadd_vx_32m1 : VgrGpr_32m1; 
  def int_riscv_vadd_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vadd_vx_32m4 : VgrGpr_32m4; 
  def int_riscv_vadd_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vadd_vi_32m1 : VgrGpr_32m1; 
  def int_riscv_vadd_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vadd_vi_32m4 : VgrGpr_32m4; 
  def int_riscv_vadd_vi_32m8 : VgrGpr_32m8;

  def int_riscv_vsub_vx_32m1 : VgrGpr_32m1; 
  def int_riscv_vsub_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vsub_vx_32m4 : VgrGpr_32m4; 
  def int_riscv_vsub_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vrsub_vx_32m1 : VgrGpr_32m1; 
  def int_riscv_vrsub_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vrsub_vx_32m4 : VgrGpr_32m4; 
  def int_riscv_vrsub_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vrsub_vi_32m1 : VgrGpr_32m1; 
  def int_riscv_vrsub_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vrsub_vi_32m4 : VgrGpr_32m4; 
  def int_riscv_vrsub_vi_32m8 : VgrGpr_32m8;

  //masked Functions
 
  class VmVgrVgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VmVgrVgr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class VmVgrVgr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class VmVgrVgr_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty,llvm_v128i8_ty,llvm_v128i8_ty],[IntrNoMem]>;

  class VmVgrVgr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class VmVgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class VmVgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class VmVgrVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_v64i16_ty],[IntrNoMem]>;

  class VmVgrVgr_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_v4i32_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class VmVgrVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class VmVgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class VmVgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_v32i32_ty],[IntrNoMem]>;

  class VmVgrGpr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmVgrGpr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmVgrGpr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmVgrGpr_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty,llvm_v128i8_ty,llvm_i32_ty],[IntrNoMem]>;

  class VmVgrGpr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmVgrGpr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmVgrGpr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmVgrGpr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_i32_ty],[IntrNoMem]>;

  class VmVgrGpr_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_v4i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmVgrGpr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmVgrGpr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmVgrGpr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_i32_ty],[IntrNoMem]>;


  def int_riscv_vadd_vv_8m1_m : VmVgrVgr_8m1; 
  def int_riscv_vadd_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vadd_vv_8m4_m : VmVgrVgr_8m4; 
  def int_riscv_vadd_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vsub_vv_8m1_m : VmVgrVgr_8m1; 
  def int_riscv_vsub_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vsub_vv_8m4_m : VmVgrVgr_8m4; 
  def int_riscv_vsub_vv_8m8_m : VmVgrVgr_8m8;
	
  def int_riscv_vadd_vv_16m1_m : VmVgrVgr_16m1; 
  def int_riscv_vadd_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vadd_vv_16m4_m : VmVgrVgr_16m4; 
  def int_riscv_vadd_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vsub_vv_16m1_m : VmVgrVgr_16m1; 
  def int_riscv_vsub_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vsub_vv_16m4_m : VmVgrVgr_16m4; 
  def int_riscv_vsub_vv_16m8_m : VmVgrVgr_16m8;


  def int_riscv_vadd_vv_32m1_m : VmVgrVgr_32m1; 
  def int_riscv_vadd_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vadd_vv_32m4_m : VmVgrVgr_32m4; 
  def int_riscv_vadd_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vsub_vv_32m1_m : VmVgrVgr_32m1; 
  def int_riscv_vsub_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vsub_vv_32m4_m : VmVgrVgr_32m4; 
  def int_riscv_vsub_vv_32m8_m : VmVgrVgr_32m8;


  def int_riscv_vadd_vx_8m1_m : VmVgrGpr_8m1; 
  def int_riscv_vadd_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vadd_vx_8m4_m : VmVgrGpr_8m4; 
  def int_riscv_vadd_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vadd_vi_8m1_m : VmVgrGpr_8m1; 
  def int_riscv_vadd_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vadd_vi_8m4_m : VmVgrGpr_8m4; 
  def int_riscv_vadd_vi_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vsub_vx_8m1_m : VmVgrGpr_8m1; 
  def int_riscv_vsub_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsub_vx_8m4_m : VmVgrGpr_8m4; 
  def int_riscv_vsub_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vrsub_vx_8m1_m : VmVgrGpr_8m1; 
  def int_riscv_vrsub_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vrsub_vx_8m4_m : VmVgrGpr_8m4; 
  def int_riscv_vrsub_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vrsub_vi_8m1_m : VmVgrGpr_8m1; 
  def int_riscv_vrsub_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vrsub_vi_8m4_m : VmVgrGpr_8m4; 
  def int_riscv_vrsub_vi_8m8_m : VmVgrGpr_8m8;


  def int_riscv_vadd_vx_16m1_m : VmVgrGpr_16m1; 
  def int_riscv_vadd_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vadd_vx_16m4_m : VmVgrGpr_16m4; 
  def int_riscv_vadd_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vadd_vi_16m1_m : VmVgrGpr_16m1; 
  def int_riscv_vadd_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vadd_vi_16m4_m : VmVgrGpr_16m4; 
  def int_riscv_vadd_vi_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vsub_vx_16m1_m : VmVgrGpr_16m1; 
  def int_riscv_vsub_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsub_vx_16m4_m : VmVgrGpr_16m4; 
  def int_riscv_vsub_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vrsub_vx_16m1_m : VmVgrGpr_16m1; 
  def int_riscv_vrsub_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vrsub_vx_16m4_m : VmVgrGpr_16m4; 
  def int_riscv_vrsub_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vrsub_vi_16m1_m : VmVgrGpr_16m1; 
  def int_riscv_vrsub_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vrsub_vi_16m4_m : VmVgrGpr_16m4; 
  def int_riscv_vrsub_vi_16m8_m : VmVgrGpr_16m8;


  def int_riscv_vadd_vx_32m1_m : VmVgrGpr_32m1; 
  def int_riscv_vadd_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vadd_vx_32m4_m : VmVgrGpr_32m4; 
  def int_riscv_vadd_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vadd_vi_32m1_m : VmVgrGpr_32m1; 
  def int_riscv_vadd_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vadd_vi_32m4_m : VmVgrGpr_32m4; 
  def int_riscv_vadd_vi_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vsub_vx_32m1_m : VmVgrGpr_32m1; 
  def int_riscv_vsub_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsub_vx_32m4_m : VmVgrGpr_32m4; 
  def int_riscv_vsub_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vrsub_vx_32m1_m : VmVgrGpr_32m1; 
  def int_riscv_vrsub_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vrsub_vx_32m4_m : VmVgrGpr_32m4; 
  def int_riscv_vrsub_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vrsub_vi_32m1_m : VmVgrGpr_32m1; 
  def int_riscv_vrsub_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vrsub_vi_32m4_m : VmVgrGpr_32m4; 
  def int_riscv_vrsub_vi_32m8_m : VmVgrGpr_32m8;  

  //Vector Widening Integer Add/Subtract Functions
  
  class Widen_VgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Widen_VgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Widen_VgrVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;

  class Widen_VgrVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Widen_VgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Widen_VgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;

  class Widen_VgrGpr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_VgrGpr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_VgrGpr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i8_ty,llvm_i32_ty],[IntrNoMem]>;

  class Widen_VgrGpr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_VgrGpr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_VgrGpr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;

  class Widen_WidenVgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Widen_WidenVgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Widen_WidenVgrVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_v64i8_ty],[IntrNoMem]>;

  class Widen_WidenVgrVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Widen_WidenVgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Widen_WidenVgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_v32i16_ty],[IntrNoMem]>;

  class Widen_WidenVgrGpr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_WidenVgrGpr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_WidenVgrGpr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_i32_ty],[IntrNoMem]>;

  class Widen_WidenVgrGpr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_WidenVgrGpr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_WidenVgrGpr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_i32_ty],[IntrNoMem]>;


  def int_riscv_vwaddu_vv_16m2 : Widen_VgrVgr_16m2;
  def int_riscv_vwaddu_vv_16m4 : Widen_VgrVgr_16m4;
  def int_riscv_vwaddu_vv_16m8 : Widen_VgrVgr_16m8;

  def int_riscv_vwsubu_vv_16m2 : Widen_VgrVgr_16m2;
  def int_riscv_vwsubu_vv_16m4 : Widen_VgrVgr_16m4;
  def int_riscv_vwsubu_vv_16m8 : Widen_VgrVgr_16m8;

  def int_riscv_vwadd_vv_16m2 : Widen_VgrVgr_16m2;
  def int_riscv_vwadd_vv_16m4 : Widen_VgrVgr_16m4;
  def int_riscv_vwadd_vv_16m8 : Widen_VgrVgr_16m8;

  def int_riscv_vwsub_vv_16m2 : Widen_VgrVgr_16m2;
  def int_riscv_vwsub_vv_16m4 : Widen_VgrVgr_16m4;
  def int_riscv_vwsub_vv_16m8 : Widen_VgrVgr_16m8;


  def int_riscv_vwaddu_vv_32m2 : Widen_VgrVgr_32m2;
  def int_riscv_vwaddu_vv_32m4 : Widen_VgrVgr_32m4;
  def int_riscv_vwaddu_vv_32m8 : Widen_VgrVgr_32m8;

  def int_riscv_vwsubu_vv_32m2 : Widen_VgrVgr_32m2;
  def int_riscv_vwsubu_vv_32m4 : Widen_VgrVgr_32m4;
  def int_riscv_vwsubu_vv_32m8 : Widen_VgrVgr_32m8;

  def int_riscv_vwadd_vv_32m2 : Widen_VgrVgr_32m2;
  def int_riscv_vwadd_vv_32m4 : Widen_VgrVgr_32m4;
  def int_riscv_vwadd_vv_32m8 : Widen_VgrVgr_32m8;

  def int_riscv_vwsub_vv_32m2 : Widen_VgrVgr_32m2;
  def int_riscv_vwsub_vv_32m4 : Widen_VgrVgr_32m4;
  def int_riscv_vwsub_vv_32m8 : Widen_VgrVgr_32m8;


  def int_riscv_vwaddu_vx_16m2 : Widen_VgrGpr_16m2;
  def int_riscv_vwaddu_vx_16m4 : Widen_VgrGpr_16m4;
  def int_riscv_vwaddu_vx_16m8 : Widen_VgrGpr_16m8;

  def int_riscv_vwsubu_vx_16m2 : Widen_VgrGpr_16m2;
  def int_riscv_vwsubu_vx_16m4 : Widen_VgrGpr_16m4;
  def int_riscv_vwsubu_vx_16m8 : Widen_VgrGpr_16m8;

  def int_riscv_vwadd_vx_16m2 : Widen_VgrGpr_16m2;
  def int_riscv_vwadd_vx_16m4 : Widen_VgrGpr_16m4;
  def int_riscv_vwadd_vx_16m8 : Widen_VgrGpr_16m8;

  def int_riscv_vwsub_vx_16m2 : Widen_VgrGpr_16m2;
  def int_riscv_vwsub_vx_16m4 : Widen_VgrGpr_16m4;
  def int_riscv_vwsub_vx_16m8 : Widen_VgrGpr_16m8;


  def int_riscv_vwaddu_vx_32m2 : Widen_VgrGpr_32m2;
  def int_riscv_vwaddu_vx_32m4 : Widen_VgrGpr_32m4;
  def int_riscv_vwaddu_vx_32m8 : Widen_VgrGpr_32m8;

  def int_riscv_vwsubu_vx_32m2 : Widen_VgrGpr_32m2;
  def int_riscv_vwsubu_vx_32m4 : Widen_VgrGpr_32m4;
  def int_riscv_vwsubu_vx_32m8 : Widen_VgrGpr_32m8;

  def int_riscv_vwadd_vx_32m2 : Widen_VgrGpr_32m2;
  def int_riscv_vwadd_vx_32m4 : Widen_VgrGpr_32m4;
  def int_riscv_vwadd_vx_32m8 : Widen_VgrGpr_32m8;

  def int_riscv_vwsub_vx_32m2 : Widen_VgrGpr_32m2;
  def int_riscv_vwsub_vx_32m4 : Widen_VgrGpr_32m4;
  def int_riscv_vwsub_vx_32m8 : Widen_VgrGpr_32m8;


  def int_riscv_vwaddu_wv_16m2 : Widen_WidenVgrVgr_16m2;
  def int_riscv_vwaddu_wv_16m4 : Widen_WidenVgrVgr_16m4;
  def int_riscv_vwaddu_wv_16m8 : Widen_WidenVgrVgr_16m8;

  def int_riscv_vwsubu_wv_16m2 : Widen_WidenVgrVgr_16m2;
  def int_riscv_vwsubu_wv_16m4 : Widen_WidenVgrVgr_16m4;
  def int_riscv_vwsubu_wv_16m8 : Widen_WidenVgrVgr_16m8;

  def int_riscv_vwadd_wv_16m2 : Widen_WidenVgrVgr_16m2;
  def int_riscv_vwadd_wv_16m4 : Widen_WidenVgrVgr_16m4;
  def int_riscv_vwadd_wv_16m8 : Widen_WidenVgrVgr_16m8;

  def int_riscv_vwsub_wv_16m2 : Widen_WidenVgrVgr_16m2;
  def int_riscv_vwsub_wv_16m4 : Widen_WidenVgrVgr_16m4;
  def int_riscv_vwsub_wv_16m8 : Widen_WidenVgrVgr_16m8;


  def int_riscv_vwaddu_wv_32m2 : Widen_WidenVgrVgr_32m2;
  def int_riscv_vwaddu_wv_32m4 : Widen_WidenVgrVgr_32m4;
  def int_riscv_vwaddu_wv_32m8 : Widen_WidenVgrVgr_32m8;

  def int_riscv_vwsubu_wv_32m2 : Widen_WidenVgrVgr_32m2;
  def int_riscv_vwsubu_wv_32m4 : Widen_WidenVgrVgr_32m4;
  def int_riscv_vwsubu_wv_32m8 : Widen_WidenVgrVgr_32m8;

  def int_riscv_vwadd_wv_32m2 : Widen_WidenVgrVgr_32m2;
  def int_riscv_vwadd_wv_32m4 : Widen_WidenVgrVgr_32m4;
  def int_riscv_vwadd_wv_32m8 : Widen_WidenVgrVgr_32m8;

  def int_riscv_vwsub_wv_32m2 : Widen_WidenVgrVgr_32m2;
  def int_riscv_vwsub_wv_32m4 : Widen_WidenVgrVgr_32m4;
  def int_riscv_vwsub_wv_32m8 : Widen_WidenVgrVgr_32m8;


  def int_riscv_vwaddu_wx_16m2 : Widen_WidenVgrGpr_16m2;
  def int_riscv_vwaddu_wx_16m4 : Widen_WidenVgrGpr_16m4;
  def int_riscv_vwaddu_wx_16m8 : Widen_WidenVgrGpr_16m8;

  def int_riscv_vwsubu_wx_16m2 : Widen_WidenVgrGpr_16m2;
  def int_riscv_vwsubu_wx_16m4 : Widen_WidenVgrGpr_16m4;
  def int_riscv_vwsubu_wx_16m8 : Widen_WidenVgrGpr_16m8;

  def int_riscv_vwadd_wx_16m2 : Widen_WidenVgrGpr_16m2;
  def int_riscv_vwadd_wx_16m4 : Widen_WidenVgrGpr_16m4;
  def int_riscv_vwadd_wx_16m8 : Widen_WidenVgrGpr_16m8;

  def int_riscv_vwsub_wx_16m2 : Widen_WidenVgrGpr_16m2;
  def int_riscv_vwsub_wx_16m4 : Widen_WidenVgrGpr_16m4;
  def int_riscv_vwsub_wx_16m8 : Widen_WidenVgrGpr_16m8;


  def int_riscv_vwaddu_wx_32m2 : Widen_WidenVgrGpr_32m2;
  def int_riscv_vwaddu_wx_32m4 : Widen_WidenVgrGpr_32m4;
  def int_riscv_vwaddu_wx_32m8 : Widen_WidenVgrGpr_32m8;

  def int_riscv_vwsubu_wx_32m2 : Widen_WidenVgrGpr_32m2;
  def int_riscv_vwsubu_wx_32m4 : Widen_WidenVgrGpr_32m4;
  def int_riscv_vwsubu_wx_32m8 : Widen_WidenVgrGpr_32m8;

  def int_riscv_vwadd_wx_32m2 : Widen_WidenVgrGpr_32m2;
  def int_riscv_vwadd_wx_32m4 : Widen_WidenVgrGpr_32m4;
  def int_riscv_vwadd_wx_32m8 : Widen_WidenVgrGpr_32m8;

  def int_riscv_vwsub_wx_32m2 : Widen_WidenVgrGpr_32m2;
  def int_riscv_vwsub_wx_32m4 : Widen_WidenVgrGpr_32m4;
  def int_riscv_vwsub_wx_32m8 : Widen_WidenVgrGpr_32m8;

  //masked functions
  class Widen_VmVgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Widen_VmVgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Widen_VmVgrVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;

  class Widen_VmVgrVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Widen_VmVgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Widen_VmVgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;

  class Widen_VmVgrGpr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_VmVgrGpr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_VmVgrGpr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_i32_ty],[IntrNoMem]>;

  class Widen_VmVgrGpr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_VmVgrGpr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_VmVgrGpr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;

  class Widen_WidenVmVgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Widen_WidenVmVgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Widen_WidenVmVgrVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_v64i8_ty],[IntrNoMem]>;

  class Widen_WidenVmVgrVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Widen_WidenVmVgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Widen_WidenVmVgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_v32i16_ty],[IntrNoMem]>;

  class Widen_WidenVmVgrGpr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_WidenVmVgrGpr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_WidenVmVgrGpr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_i32_ty],[IntrNoMem]>;

  class Widen_WidenVmVgrGpr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_WidenVmVgrGpr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class Widen_WidenVmVgrGpr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_i32_ty],[IntrNoMem]>;


  def int_riscv_vwaddu_vv_16m2_m : Widen_VmVgrVgr_16m2;
  def int_riscv_vwaddu_vv_16m4_m : Widen_VmVgrVgr_16m4;
  def int_riscv_vwaddu_vv_16m8_m : Widen_VmVgrVgr_16m8;

  def int_riscv_vwsubu_vv_16m2_m : Widen_VmVgrVgr_16m2;
  def int_riscv_vwsubu_vv_16m4_m : Widen_VmVgrVgr_16m4;
  def int_riscv_vwsubu_vv_16m8_m : Widen_VmVgrVgr_16m8;

  def int_riscv_vwadd_vv_16m2_m : Widen_VmVgrVgr_16m2;
  def int_riscv_vwadd_vv_16m4_m : Widen_VmVgrVgr_16m4;
  def int_riscv_vwadd_vv_16m8_m : Widen_VmVgrVgr_16m8;

  def int_riscv_vwsub_vv_16m2_m : Widen_VmVgrVgr_16m2;
  def int_riscv_vwsub_vv_16m4_m : Widen_VmVgrVgr_16m4;
  def int_riscv_vwsub_vv_16m8_m : Widen_VmVgrVgr_16m8;


  def int_riscv_vwaddu_vv_32m2_m : Widen_VmVgrVgr_32m2;
  def int_riscv_vwaddu_vv_32m4_m : Widen_VmVgrVgr_32m4;
  def int_riscv_vwaddu_vv_32m8_m : Widen_VmVgrVgr_32m8;

  def int_riscv_vwsubu_vv_32m2_m : Widen_VmVgrVgr_32m2;
  def int_riscv_vwsubu_vv_32m4_m : Widen_VmVgrVgr_32m4;
  def int_riscv_vwsubu_vv_32m8_m : Widen_VmVgrVgr_32m8;

  def int_riscv_vwadd_vv_32m2_m : Widen_VmVgrVgr_32m2;
  def int_riscv_vwadd_vv_32m4_m : Widen_VmVgrVgr_32m4;
  def int_riscv_vwadd_vv_32m8_m : Widen_VmVgrVgr_32m8;

  def int_riscv_vwsub_vv_32m2_m : Widen_VmVgrVgr_32m2;
  def int_riscv_vwsub_vv_32m4_m : Widen_VmVgrVgr_32m4;
  def int_riscv_vwsub_vv_32m8_m : Widen_VmVgrVgr_32m8;


  def int_riscv_vwaddu_vx_16m2_m : Widen_VmVgrGpr_16m2;
  def int_riscv_vwaddu_vx_16m4_m : Widen_VmVgrGpr_16m4;
  def int_riscv_vwaddu_vx_16m8_m : Widen_VmVgrGpr_16m8;

  def int_riscv_vwsubu_vx_16m2_m : Widen_VmVgrGpr_16m2;
  def int_riscv_vwsubu_vx_16m4_m : Widen_VmVgrGpr_16m4;
  def int_riscv_vwsubu_vx_16m8_m : Widen_VmVgrGpr_16m8;

  def int_riscv_vwadd_vx_16m2_m : Widen_VmVgrGpr_16m2;
  def int_riscv_vwadd_vx_16m4_m : Widen_VmVgrGpr_16m4;
  def int_riscv_vwadd_vx_16m8_m : Widen_VmVgrGpr_16m8;

  def int_riscv_vwsub_vx_16m2_m : Widen_VmVgrGpr_16m2;
  def int_riscv_vwsub_vx_16m4_m : Widen_VmVgrGpr_16m4;
  def int_riscv_vwsub_vx_16m8_m : Widen_VmVgrGpr_16m8;


  def int_riscv_vwaddu_vx_32m2_m : Widen_VmVgrGpr_32m2;
  def int_riscv_vwaddu_vx_32m4_m : Widen_VmVgrGpr_32m4;
  def int_riscv_vwaddu_vx_32m8_m : Widen_VmVgrGpr_32m8;

  def int_riscv_vwsubu_vx_32m2_m : Widen_VmVgrGpr_32m2;
  def int_riscv_vwsubu_vx_32m4_m : Widen_VmVgrGpr_32m4;
  def int_riscv_vwsubu_vx_32m8_m : Widen_VmVgrGpr_32m8;

  def int_riscv_vwadd_vx_32m2_m : Widen_VmVgrGpr_32m2;
  def int_riscv_vwadd_vx_32m4_m : Widen_VmVgrGpr_32m4;
  def int_riscv_vwadd_vx_32m8_m : Widen_VmVgrGpr_32m8;

  def int_riscv_vwsub_vx_32m2_m : Widen_VmVgrGpr_32m2;
  def int_riscv_vwsub_vx_32m4_m : Widen_VmVgrGpr_32m4;
  def int_riscv_vwsub_vx_32m8_m : Widen_VmVgrGpr_32m8;


  def int_riscv_vwaddu_wv_16m2_m : Widen_WidenVmVgrVgr_16m2;
  def int_riscv_vwaddu_wv_16m4_m : Widen_WidenVmVgrVgr_16m4;
  def int_riscv_vwaddu_wv_16m8_m : Widen_WidenVmVgrVgr_16m8;

  def int_riscv_vwsubu_wv_16m2_m : Widen_WidenVmVgrVgr_16m2;
  def int_riscv_vwsubu_wv_16m4_m : Widen_WidenVmVgrVgr_16m4;
  def int_riscv_vwsubu_wv_16m8_m : Widen_WidenVmVgrVgr_16m8;

  def int_riscv_vwadd_wv_16m2_m : Widen_WidenVmVgrVgr_16m2;
  def int_riscv_vwadd_wv_16m4_m : Widen_WidenVmVgrVgr_16m4;
  def int_riscv_vwadd_wv_16m8_m : Widen_WidenVmVgrVgr_16m8;

  def int_riscv_vwsub_wv_16m2_m : Widen_WidenVmVgrVgr_16m2;
  def int_riscv_vwsub_wv_16m4_m : Widen_WidenVmVgrVgr_16m4;
  def int_riscv_vwsub_wv_16m8_m : Widen_WidenVmVgrVgr_16m8;


  def int_riscv_vwaddu_wv_32m2_m : Widen_WidenVmVgrVgr_32m2;
  def int_riscv_vwaddu_wv_32m4_m : Widen_WidenVmVgrVgr_32m4;
  def int_riscv_vwaddu_wv_32m8_m : Widen_WidenVmVgrVgr_32m8;

  def int_riscv_vwsubu_wv_32m2_m : Widen_WidenVmVgrVgr_32m2;
  def int_riscv_vwsubu_wv_32m4_m : Widen_WidenVmVgrVgr_32m4;
  def int_riscv_vwsubu_wv_32m8_m : Widen_WidenVmVgrVgr_32m8;

  def int_riscv_vwadd_wv_32m2_m : Widen_WidenVmVgrVgr_32m2;
  def int_riscv_vwadd_wv_32m4_m : Widen_WidenVmVgrVgr_32m4;
  def int_riscv_vwadd_wv_32m8_m : Widen_WidenVmVgrVgr_32m8;

  def int_riscv_vwsub_wv_32m2_m : Widen_WidenVmVgrVgr_32m2;
  def int_riscv_vwsub_wv_32m4_m : Widen_WidenVmVgrVgr_32m4;
  def int_riscv_vwsub_wv_32m8_m : Widen_WidenVmVgrVgr_32m8;


  def int_riscv_vwaddu_wx_16m2_m : Widen_WidenVmVgrGpr_16m2;
  def int_riscv_vwaddu_wx_16m4_m : Widen_WidenVmVgrGpr_16m4;
  def int_riscv_vwaddu_wx_16m8_m : Widen_WidenVmVgrGpr_16m8;

  def int_riscv_vwsubu_wx_16m2_m : Widen_WidenVmVgrGpr_16m2;
  def int_riscv_vwsubu_wx_16m4_m : Widen_WidenVmVgrGpr_16m4;
  def int_riscv_vwsubu_wx_16m8_m : Widen_WidenVmVgrGpr_16m8;

  def int_riscv_vwadd_wx_16m2_m : Widen_WidenVmVgrGpr_16m2;
  def int_riscv_vwadd_wx_16m4_m : Widen_WidenVmVgrGpr_16m4;
  def int_riscv_vwadd_wx_16m8_m : Widen_WidenVmVgrGpr_16m8;

  def int_riscv_vwsub_wx_16m2_m : Widen_WidenVmVgrGpr_16m2;
  def int_riscv_vwsub_wx_16m4_m : Widen_WidenVmVgrGpr_16m4;
  def int_riscv_vwsub_wx_16m8_m : Widen_WidenVmVgrGpr_16m8;


  def int_riscv_vwaddu_wx_32m2_m : Widen_WidenVmVgrGpr_32m2;
  def int_riscv_vwaddu_wx_32m4_m : Widen_WidenVmVgrGpr_32m4;
  def int_riscv_vwaddu_wx_32m8_m : Widen_WidenVmVgrGpr_32m8;

  def int_riscv_vwsubu_wx_32m2_m : Widen_WidenVmVgrGpr_32m2;
  def int_riscv_vwsubu_wx_32m4_m : Widen_WidenVmVgrGpr_32m4;
  def int_riscv_vwsubu_wx_32m8_m : Widen_WidenVmVgrGpr_32m8;

  def int_riscv_vwadd_wx_32m2_m : Widen_WidenVmVgrGpr_32m2;
  def int_riscv_vwadd_wx_32m4_m : Widen_WidenVmVgrGpr_32m4;
  def int_riscv_vwadd_wx_32m8_m : Widen_WidenVmVgrGpr_32m8;

  def int_riscv_vwsub_wx_32m2_m : Widen_WidenVmVgrGpr_32m2;
  def int_riscv_vwsub_wx_32m4_m : Widen_WidenVmVgrGpr_32m4;
  def int_riscv_vwsub_wx_32m8_m : Widen_WidenVmVgrGpr_32m8;


  //Vector Integer Add-with-Carry/Subtract-with-Borrow Functions

  class VgrVgrVm_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgrVm_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i8_ty,llvm_v32i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgrVm_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i8_ty,llvm_v64i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgrVm_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v128i8_ty,llvm_v128i8_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class VgrVgrVm_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i16_ty,llvm_v8i16_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgrVm_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_v16i16_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgrVm_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_v32i16_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgrVm_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_v64i16_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class VgrVgrVm_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4i32_ty,llvm_v4i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgrVm_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_v8i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgrVm_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_v16i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgrVm_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_v32i32_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class VgrGprVm_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrGprVm_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i8_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrGprVm_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i8_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrGprVm_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v128i8_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class VgrGprVm_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i16_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrGprVm_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrGprVm_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrGprVm_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class VgrGprVm_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4i32_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrGprVm_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrGprVm_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrGprVm_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class Vm_VgrVgrVm_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrVgrVm_8m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i8_ty,llvm_v32i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrVgrVm_8m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v64i8_ty,llvm_v64i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrVgrVm_8m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v128i8_ty,llvm_v128i8_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class Vm_VgrVgrVm_16m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v8i16_ty,llvm_v8i16_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrVgrVm_16m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i16_ty,llvm_v16i16_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrVgrVm_16m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i16_ty,llvm_v32i16_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrVgrVm_16m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v64i16_ty,llvm_v64i16_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class Vm_VgrVgrVm_32m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v4i32_ty,llvm_v4i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrVgrVm_32m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v8i32_ty,llvm_v8i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrVgrVm_32m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i32_ty,llvm_v16i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrVgrVm_32m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i32_ty,llvm_v32i32_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class Vm_VgrGprVm_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrGprVm_8m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i8_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrGprVm_8m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v64i8_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrGprVm_8m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v128i8_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class Vm_VgrGprVm_16m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v8i16_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrGprVm_16m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i16_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrGprVm_16m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i16_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrGprVm_16m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v64i16_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class Vm_VgrGprVm_32m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v4i32_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrGprVm_32m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v8i32_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrGprVm_32m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i32_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrGprVm_32m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i32_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;

  class Vm_VgrVgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VgrVgr_8m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Vm_VgrVgr_8m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class Vm_VgrVgr_8m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v128i8_ty,llvm_v128i8_ty],[IntrNoMem]>;

  class Vm_VgrVgr_16m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Vm_VgrVgr_16m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Vm_VgrVgr_16m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class Vm_VgrVgr_16m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v64i16_ty,llvm_v64i16_ty],[IntrNoMem]>;

  class Vm_VgrVgr_32m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v4i32_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class Vm_VgrVgr_32m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v8i32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class Vm_VgrVgr_32m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class Vm_VgrVgr_32m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i32_ty,llvm_v32i32_ty],[IntrNoMem]>;

  class Vm_VgrGpr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VgrGpr_8m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VgrGpr_8m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v64i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VgrGpr_8m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v128i8_ty,llvm_i32_ty],[IntrNoMem]>;

  class Vm_VgrGpr_16m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v8i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VgrGpr_16m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VgrGpr_16m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VgrGpr_16m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v64i16_ty,llvm_i32_ty],[IntrNoMem]>;

  class Vm_VgrGpr_32m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v4i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VgrGpr_32m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v8i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VgrGpr_32m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VgrGpr_32m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v32i32_ty,llvm_i32_ty],[IntrNoMem]>;


  def int_riscv_vadc_vvm_8m1 : VgrVgrVm_8m1;
  def int_riscv_vadc_vvm_8m2 : VgrVgrVm_8m2;
  def int_riscv_vadc_vvm_8m4 : VgrVgrVm_8m4;
  def int_riscv_vadc_vvm_8m8 : VgrVgrVm_8m8;

  def int_riscv_vsbc_vvm_8m1 : VgrVgrVm_8m1;
  def int_riscv_vsbc_vvm_8m2 : VgrVgrVm_8m2;
  def int_riscv_vsbc_vvm_8m4 : VgrVgrVm_8m4;
  def int_riscv_vsbc_vvm_8m8 : VgrVgrVm_8m8;


  def int_riscv_vadc_vvm_16m1 : VgrVgrVm_16m1;
  def int_riscv_vadc_vvm_16m2 : VgrVgrVm_16m2;
  def int_riscv_vadc_vvm_16m4 : VgrVgrVm_16m4;
  def int_riscv_vadc_vvm_16m8 : VgrVgrVm_16m8;

  def int_riscv_vsbc_vvm_16m1 : VgrVgrVm_16m1;
  def int_riscv_vsbc_vvm_16m2 : VgrVgrVm_16m2;
  def int_riscv_vsbc_vvm_16m4 : VgrVgrVm_16m4;
  def int_riscv_vsbc_vvm_16m8 : VgrVgrVm_16m8;


  def int_riscv_vadc_vvm_32m1 : VgrVgrVm_32m1;
  def int_riscv_vadc_vvm_32m2 : VgrVgrVm_32m2;
  def int_riscv_vadc_vvm_32m4 : VgrVgrVm_32m4;
  def int_riscv_vadc_vvm_32m8 : VgrVgrVm_32m8;

  def int_riscv_vsbc_vvm_32m1 : VgrVgrVm_32m1;
  def int_riscv_vsbc_vvm_32m2 : VgrVgrVm_32m2;
  def int_riscv_vsbc_vvm_32m4 : VgrVgrVm_32m4;
  def int_riscv_vsbc_vvm_32m8 : VgrVgrVm_32m8;


  def int_riscv_vadc_vxm_8m1 : VgrGprVm_8m1;
  def int_riscv_vadc_vxm_8m2 : VgrGprVm_8m2;
  def int_riscv_vadc_vxm_8m4 : VgrGprVm_8m4;
  def int_riscv_vadc_vxm_8m8 : VgrGprVm_8m8;

  def int_riscv_vadc_vim_8m1 : VgrGprVm_8m1;
  def int_riscv_vadc_vim_8m2 : VgrGprVm_8m2;
  def int_riscv_vadc_vim_8m4 : VgrGprVm_8m4;
  def int_riscv_vadc_vim_8m8 : VgrGprVm_8m8;

  def int_riscv_vsbc_vxm_8m1 : VgrGprVm_8m1;
  def int_riscv_vsbc_vxm_8m2 : VgrGprVm_8m2;
  def int_riscv_vsbc_vxm_8m4 : VgrGprVm_8m4;
  def int_riscv_vsbc_vxm_8m8 : VgrGprVm_8m8;


  def int_riscv_vadc_vxm_16m1 : VgrGprVm_16m1;
  def int_riscv_vadc_vxm_16m2 : VgrGprVm_16m2;
  def int_riscv_vadc_vxm_16m4 : VgrGprVm_16m4;
  def int_riscv_vadc_vxm_16m8 : VgrGprVm_16m8;

  def int_riscv_vadc_vim_16m1 : VgrGprVm_16m1;
  def int_riscv_vadc_vim_16m2 : VgrGprVm_16m2;
  def int_riscv_vadc_vim_16m4 : VgrGprVm_16m4;
  def int_riscv_vadc_vim_16m8 : VgrGprVm_16m8;

  def int_riscv_vsbc_vxm_16m1 : VgrGprVm_16m1;
  def int_riscv_vsbc_vxm_16m2 : VgrGprVm_16m2;
  def int_riscv_vsbc_vxm_16m4 : VgrGprVm_16m4;
  def int_riscv_vsbc_vxm_16m8 : VgrGprVm_16m8;


  def int_riscv_vadc_vxm_32m1 : VgrGprVm_32m1;
  def int_riscv_vadc_vxm_32m2 : VgrGprVm_32m2;
  def int_riscv_vadc_vxm_32m4 : VgrGprVm_32m4;
  def int_riscv_vadc_vxm_32m8 : VgrGprVm_32m8;

  def int_riscv_vadc_vim_32m1 : VgrGprVm_32m1;
  def int_riscv_vadc_vim_32m2 : VgrGprVm_32m2;
  def int_riscv_vadc_vim_32m4 : VgrGprVm_32m4;
  def int_riscv_vadc_vim_32m8 : VgrGprVm_32m8;

  def int_riscv_vsbc_vxm_32m1 : VgrGprVm_32m1;
  def int_riscv_vsbc_vxm_32m2 : VgrGprVm_32m2;
  def int_riscv_vsbc_vxm_32m4 : VgrGprVm_32m4;
  def int_riscv_vsbc_vxm_32m8 : VgrGprVm_32m8;


  def int_riscv_vmadc_vvm_8m1 : Vm_VgrVgrVm_8m1;
  def int_riscv_vmadc_vvm_8m2 : Vm_VgrVgrVm_8m2;
  def int_riscv_vmadc_vvm_8m4 : Vm_VgrVgrVm_8m4;
  def int_riscv_vmadc_vvm_8m8 : Vm_VgrVgrVm_8m8;

  def int_riscv_vmsbc_vvm_8m1 : Vm_VgrVgrVm_8m1;
  def int_riscv_vmsbc_vvm_8m2 : Vm_VgrVgrVm_8m2;
  def int_riscv_vmsbc_vvm_8m4 : Vm_VgrVgrVm_8m4;
  def int_riscv_vmsbc_vvm_8m8 : Vm_VgrVgrVm_8m8;


  def int_riscv_vmadc_vvm_16m1 : Vm_VgrVgrVm_16m1;
  def int_riscv_vmadc_vvm_16m2 : Vm_VgrVgrVm_16m2;
  def int_riscv_vmadc_vvm_16m4 : Vm_VgrVgrVm_16m4;
  def int_riscv_vmadc_vvm_16m8 : Vm_VgrVgrVm_16m8;

  def int_riscv_vmsbc_vvm_16m1 : Vm_VgrVgrVm_16m1;
  def int_riscv_vmsbc_vvm_16m2 : Vm_VgrVgrVm_16m2;
  def int_riscv_vmsbc_vvm_16m4 : Vm_VgrVgrVm_16m4;
  def int_riscv_vmsbc_vvm_16m8 : Vm_VgrVgrVm_16m8;


  def int_riscv_vmadc_vvm_32m1 : Vm_VgrVgrVm_32m1;
  def int_riscv_vmadc_vvm_32m2 : Vm_VgrVgrVm_32m2;
  def int_riscv_vmadc_vvm_32m4 : Vm_VgrVgrVm_32m4;
  def int_riscv_vmadc_vvm_32m8 : Vm_VgrVgrVm_32m8;

  def int_riscv_vmsbc_vvm_32m1 : Vm_VgrVgrVm_32m1;
  def int_riscv_vmsbc_vvm_32m2 : Vm_VgrVgrVm_32m2;
  def int_riscv_vmsbc_vvm_32m4 : Vm_VgrVgrVm_32m4;
  def int_riscv_vmsbc_vvm_32m8 : Vm_VgrVgrVm_32m8;


  def int_riscv_vmadc_vxm_8m1 : Vm_VgrGprVm_8m1;
  def int_riscv_vmadc_vxm_8m2 : Vm_VgrGprVm_8m2;
  def int_riscv_vmadc_vxm_8m4 : Vm_VgrGprVm_8m4;
  def int_riscv_vmadc_vxm_8m8 : Vm_VgrGprVm_8m8;

  def int_riscv_vmadc_vim_8m1 : Vm_VgrGprVm_8m1;
  def int_riscv_vmadc_vim_8m2 : Vm_VgrGprVm_8m2;
  def int_riscv_vmadc_vim_8m4 : Vm_VgrGprVm_8m4;
  def int_riscv_vmadc_vim_8m8 : Vm_VgrGprVm_8m8;

  def int_riscv_vmsbc_vxm_8m1 : Vm_VgrGprVm_8m1;
  def int_riscv_vmsbc_vxm_8m2 : Vm_VgrGprVm_8m2;
  def int_riscv_vmsbc_vxm_8m4 : Vm_VgrGprVm_8m4;
  def int_riscv_vmsbc_vxm_8m8 : Vm_VgrGprVm_8m8;


  def int_riscv_vmadc_vxm_16m1 : Vm_VgrGprVm_16m1;
  def int_riscv_vmadc_vxm_16m2 : Vm_VgrGprVm_16m2;
  def int_riscv_vmadc_vxm_16m4 : Vm_VgrGprVm_16m4;
  def int_riscv_vmadc_vxm_16m8 : Vm_VgrGprVm_16m8;

  def int_riscv_vmadc_vim_16m1 : Vm_VgrGprVm_16m1;
  def int_riscv_vmadc_vim_16m2 : Vm_VgrGprVm_16m2;
  def int_riscv_vmadc_vim_16m4 : Vm_VgrGprVm_16m4;
  def int_riscv_vmadc_vim_16m8 : Vm_VgrGprVm_16m8;

  def int_riscv_vmsbc_vxm_16m1 : Vm_VgrGprVm_16m1;
  def int_riscv_vmsbc_vxm_16m2 : Vm_VgrGprVm_16m2;
  def int_riscv_vmsbc_vxm_16m4 : Vm_VgrGprVm_16m4;
  def int_riscv_vmsbc_vxm_16m8 : Vm_VgrGprVm_16m8;


  def int_riscv_vmadc_vxm_32m1 : Vm_VgrGprVm_32m1;
  def int_riscv_vmadc_vxm_32m2 : Vm_VgrGprVm_32m2;
  def int_riscv_vmadc_vxm_32m4 : Vm_VgrGprVm_32m4;
  def int_riscv_vmadc_vxm_32m8 : Vm_VgrGprVm_32m8;

  def int_riscv_vmadc_vim_32m1 : Vm_VgrGprVm_32m1;
  def int_riscv_vmadc_vim_32m2 : Vm_VgrGprVm_32m2;
  def int_riscv_vmadc_vim_32m4 : Vm_VgrGprVm_32m4;
  def int_riscv_vmadc_vim_32m8 : Vm_VgrGprVm_32m8;

  def int_riscv_vmsbc_vxm_32m1 : Vm_VgrGprVm_32m1;
  def int_riscv_vmsbc_vxm_32m2 : Vm_VgrGprVm_32m2;
  def int_riscv_vmsbc_vxm_32m4 : Vm_VgrGprVm_32m4;
  def int_riscv_vmsbc_vxm_32m8 : Vm_VgrGprVm_32m8;


  def int_riscv_vmadc_vv_8m1 : Vm_VgrVgr_8m1;
  def int_riscv_vmadc_vv_8m2 : Vm_VgrVgr_8m2;
  def int_riscv_vmadc_vv_8m4 : Vm_VgrVgr_8m4;
  def int_riscv_vmadc_vv_8m8 : Vm_VgrVgr_8m8;

  def int_riscv_vmsbc_vv_8m1 : Vm_VgrVgr_8m1;
  def int_riscv_vmsbc_vv_8m2 : Vm_VgrVgr_8m2;
  def int_riscv_vmsbc_vv_8m4 : Vm_VgrVgr_8m4;
  def int_riscv_vmsbc_vv_8m8 : Vm_VgrVgr_8m8;


  def int_riscv_vmadc_vv_16m1 : Vm_VgrVgr_16m1;
  def int_riscv_vmadc_vv_16m2 : Vm_VgrVgr_16m2;
  def int_riscv_vmadc_vv_16m4 : Vm_VgrVgr_16m4;
  def int_riscv_vmadc_vv_16m8 : Vm_VgrVgr_16m8;

  def int_riscv_vmsbc_vv_16m1 : Vm_VgrVgr_16m1;
  def int_riscv_vmsbc_vv_16m2 : Vm_VgrVgr_16m2;
  def int_riscv_vmsbc_vv_16m4 : Vm_VgrVgr_16m4;
  def int_riscv_vmsbc_vv_16m8 : Vm_VgrVgr_16m8;


  def int_riscv_vmadc_vv_32m1 : Vm_VgrVgr_32m1;
  def int_riscv_vmadc_vv_32m2 : Vm_VgrVgr_32m2;
  def int_riscv_vmadc_vv_32m4 : Vm_VgrVgr_32m4;
  def int_riscv_vmadc_vv_32m8 : Vm_VgrVgr_32m8;

  def int_riscv_vmsbc_vv_32m1 : Vm_VgrVgr_32m1;
  def int_riscv_vmsbc_vv_32m2 : Vm_VgrVgr_32m2;
  def int_riscv_vmsbc_vv_32m4 : Vm_VgrVgr_32m4;
  def int_riscv_vmsbc_vv_32m8 : Vm_VgrVgr_32m8;


  def int_riscv_vmadc_vx_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmadc_vx_8m2 : Vm_VgrGpr_8m2;
  def int_riscv_vmadc_vx_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmadc_vx_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmadc_vi_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmadc_vi_8m2 : Vm_VgrGpr_8m2;
  def int_riscv_vmadc_vi_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmadc_vi_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsbc_vx_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsbc_vx_8m2 : Vm_VgrGpr_8m2;
  def int_riscv_vmsbc_vx_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsbc_vx_8m8 : Vm_VgrGpr_8m8;


  def int_riscv_vmadc_vx_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmadc_vx_16m2 : Vm_VgrGpr_16m2;
  def int_riscv_vmadc_vx_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmadc_vx_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmadc_vi_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmadc_vi_16m2 : Vm_VgrGpr_16m2;
  def int_riscv_vmadc_vi_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmadc_vi_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsbc_vx_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsbc_vx_16m2 : Vm_VgrGpr_16m2;
  def int_riscv_vmsbc_vx_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsbc_vx_16m8 : Vm_VgrGpr_16m8;


  def int_riscv_vmadc_vx_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmadc_vx_32m2 : Vm_VgrGpr_32m2;
  def int_riscv_vmadc_vx_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmadc_vx_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmadc_vi_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmadc_vi_32m2 : Vm_VgrGpr_32m2;
  def int_riscv_vmadc_vi_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmadc_vi_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsbc_vx_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsbc_vx_32m2 : Vm_VgrGpr_32m2;
  def int_riscv_vmsbc_vx_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsbc_vx_32m8 : Vm_VgrGpr_32m8;


  //Vector Bitwise Logical Functions

  def int_riscv_vand_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vand_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vand_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vand_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vor_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vor_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vor_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vor_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vxor_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vxor_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vxor_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vxor_vv_8m8 : VgrVgr_8m8;


  def int_riscv_vand_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vand_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vand_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vand_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vor_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vor_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vor_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vor_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vxor_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vxor_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vxor_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vxor_vv_16m8 : VgrVgr_16m8;


  def int_riscv_vand_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vand_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vand_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vand_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vor_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vor_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vor_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vor_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vxor_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vxor_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vxor_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vxor_vv_32m8 : VgrVgr_32m8;


  def int_riscv_vand_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vand_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vand_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vand_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vand_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vand_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vand_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vand_vi_8m8 : VgrGpr_8m8;

  def int_riscv_vor_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vor_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vor_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vor_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vor_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vor_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vor_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vor_vi_8m8 : VgrGpr_8m8;

  def int_riscv_vxor_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vxor_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vxor_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vxor_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vxor_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vxor_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vxor_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vxor_vi_8m8 : VgrGpr_8m8;


  def int_riscv_vand_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vand_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vand_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vand_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vand_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vand_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vand_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vand_vi_16m8 : VgrGpr_16m8;

  def int_riscv_vor_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vor_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vor_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vor_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vor_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vor_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vor_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vor_vi_16m8 : VgrGpr_16m8;

  def int_riscv_vxor_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vxor_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vxor_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vxor_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vxor_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vxor_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vxor_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vxor_vi_16m8 : VgrGpr_16m8;


  def int_riscv_vand_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vand_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vand_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vand_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vand_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vand_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vand_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vand_vi_32m8 : VgrGpr_32m8;

  def int_riscv_vor_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vor_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vor_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vor_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vor_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vor_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vor_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vor_vi_32m8 : VgrGpr_32m8;

  def int_riscv_vxor_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vxor_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vxor_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vxor_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vxor_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vxor_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vxor_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vxor_vi_32m8 : VgrGpr_32m8;


  //masked functions

  def int_riscv_vand_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vand_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vand_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vand_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vor_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vor_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vor_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vor_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vxor_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vxor_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vxor_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vxor_vv_8m8_m : VmVgrVgr_8m8;


  def int_riscv_vand_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vand_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vand_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vand_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vor_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vor_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vor_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vor_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vxor_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vxor_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vxor_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vxor_vv_16m8_m : VmVgrVgr_16m8;


  def int_riscv_vand_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vand_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vand_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vand_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vor_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vor_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vor_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vor_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vxor_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vxor_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vxor_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vxor_vv_32m8_m : VmVgrVgr_32m8;


  def int_riscv_vand_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vand_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vand_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vand_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vand_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vand_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vand_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vand_vi_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vor_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vor_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vor_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vor_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vor_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vor_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vor_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vor_vi_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vxor_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vxor_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vxor_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vxor_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vxor_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vxor_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vxor_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vxor_vi_8m8_m : VmVgrGpr_8m8;


  def int_riscv_vand_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vand_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vand_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vand_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vand_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vand_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vand_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vand_vi_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vor_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vor_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vor_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vor_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vor_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vor_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vor_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vor_vi_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vxor_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vxor_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vxor_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vxor_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vxor_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vxor_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vxor_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vxor_vi_16m8_m : VmVgrGpr_16m8;


  def int_riscv_vand_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vand_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vand_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vand_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vand_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vand_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vand_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vand_vi_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vor_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vor_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vor_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vor_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vor_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vor_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vor_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vor_vi_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vxor_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vxor_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vxor_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vxor_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vxor_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vxor_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vxor_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vxor_vi_32m8_m : VmVgrGpr_32m8;


  //Vector Single-Width Bit Shift Function

  def int_riscv_vsll_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vsll_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vsll_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vsll_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vsrl_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vsrl_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vsrl_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vsrl_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vsra_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vsra_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vsra_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vsra_vv_8m8 : VgrVgr_8m8;


  def int_riscv_vsll_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vsll_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vsll_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vsll_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vsrl_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vsrl_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vsrl_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vsrl_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vsra_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vsra_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vsra_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vsra_vv_16m8 : VgrVgr_16m8;


  def int_riscv_vsll_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vsll_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vsll_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vsll_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vsrl_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vsrl_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vsrl_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vsrl_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vsra_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vsra_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vsra_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vsra_vv_32m8 : VgrVgr_32m8;


  def int_riscv_vsll_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vsll_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vsll_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vsll_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vsll_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vsll_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vsll_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vsll_vi_8m8 : VgrGpr_8m8;

  def int_riscv_vsrl_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vsrl_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vsrl_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vsrl_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vsrl_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vsrl_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vsrl_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vsrl_vi_8m8 : VgrGpr_8m8;

  def int_riscv_vsra_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vsra_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vsra_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vsra_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vsra_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vsra_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vsra_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vsra_vi_8m8 : VgrGpr_8m8;


  def int_riscv_vsll_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vsll_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vsll_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vsll_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vsll_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vsll_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vsll_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vsll_vi_16m8 : VgrGpr_16m8;

  def int_riscv_vsrl_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vsrl_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vsrl_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vsrl_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vsrl_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vsrl_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vsrl_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vsrl_vi_16m8 : VgrGpr_16m8;

  def int_riscv_vsra_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vsra_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vsra_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vsra_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vsra_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vsra_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vsra_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vsra_vi_16m8 : VgrGpr_16m8;


  def int_riscv_vsll_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vsll_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vsll_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vsll_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vsll_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vsll_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vsll_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vsll_vi_32m8 : VgrGpr_32m8;

  def int_riscv_vsrl_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vsrl_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vsrl_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vsrl_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vsrl_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vsrl_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vsrl_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vsrl_vi_32m8 : VgrGpr_32m8;

  def int_riscv_vsra_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vsra_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vsra_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vsra_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vsra_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vsra_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vsra_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vsra_vi_32m8 : VgrGpr_32m8;


  //masked functions

  def int_riscv_vsll_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vsll_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vsll_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vsll_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vsrl_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vsrl_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vsrl_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vsrl_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vsra_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vsra_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vsra_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vsra_vv_8m8_m : VmVgrVgr_8m8;


  def int_riscv_vsll_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vsll_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vsll_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vsll_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vsrl_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vsrl_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vsrl_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vsrl_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vsra_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vsra_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vsra_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vsra_vv_16m8_m : VmVgrVgr_16m8;


  def int_riscv_vsll_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vsll_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vsll_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vsll_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vsrl_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vsrl_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vsrl_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vsrl_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vsra_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vsra_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vsra_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vsra_vv_32m8_m : VmVgrVgr_32m8;


  def int_riscv_vsll_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsll_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsll_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsll_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vsll_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsll_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsll_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsll_vi_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vsrl_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsrl_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsrl_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsrl_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vsrl_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsrl_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsrl_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsrl_vi_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vsra_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsra_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsra_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsra_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vsra_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsra_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsra_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsra_vi_8m8_m : VmVgrGpr_8m8;


  def int_riscv_vsll_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsll_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsll_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsll_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vsll_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsll_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsll_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsll_vi_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vsrl_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsrl_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsrl_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsrl_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vsrl_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsrl_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsrl_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsrl_vi_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vsra_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsra_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsra_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsra_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vsra_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsra_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsra_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsra_vi_16m8_m : VmVgrGpr_16m8;


  def int_riscv_vsll_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsll_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsll_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsll_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vsll_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsll_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsll_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsll_vi_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vsrl_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsrl_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsrl_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsrl_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vsrl_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsrl_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsrl_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsrl_vi_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vsra_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsra_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsra_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsra_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vsra_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsra_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsra_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsra_vi_32m8_m : VmVgrGpr_32m8;


  //Vector Narrowing Integer Right Shift Functions

  class NarrowVgrVgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i16_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class NarrowVgrVgr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i16_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class NarrowVgrVgr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i16_ty,llvm_v64i8_ty],[IntrNoMem]>;

  class NarrowVgrVgr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i32_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class NarrowVgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i32_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class NarrowVgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i32_ty,llvm_v32i16_ty],[IntrNoMem]>;

  class NarrowVgrGpr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class NarrowVgrGpr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class NarrowVgrGpr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i16_ty,llvm_i32_ty],[IntrNoMem]>;

  class NarrowVgrGpr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class NarrowVgrGpr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class NarrowVgrGpr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i32_ty,llvm_i32_ty],[IntrNoMem]>;


  def int_riscv_vnsrl_wv_8m1 : NarrowVgrVgr_8m1;
  def int_riscv_vnsrl_wv_8m2 : NarrowVgrVgr_8m2;
  def int_riscv_vnsrl_wv_8m4 : NarrowVgrVgr_8m4;

  def int_riscv_vnsra_wv_8m1 : NarrowVgrVgr_8m1;
  def int_riscv_vnsra_wv_8m2 : NarrowVgrVgr_8m2;
  def int_riscv_vnsra_wv_8m4 : NarrowVgrVgr_8m4;


  def int_riscv_vnsrl_wv_16m1 : NarrowVgrVgr_16m1;
  def int_riscv_vnsrl_wv_16m2 : NarrowVgrVgr_16m2;
  def int_riscv_vnsrl_wv_16m4 : NarrowVgrVgr_16m4;

  def int_riscv_vnsra_wv_16m1 : NarrowVgrVgr_16m1;
  def int_riscv_vnsra_wv_16m2 : NarrowVgrVgr_16m2;
  def int_riscv_vnsra_wv_16m4 : NarrowVgrVgr_16m4;


  def int_riscv_vnsrl_wx_8m1 : NarrowVgrGpr_8m1;
  def int_riscv_vnsrl_wx_8m2 : NarrowVgrGpr_8m2;
  def int_riscv_vnsrl_wx_8m4 : NarrowVgrGpr_8m4;

  def int_riscv_vnsrl_wi_8m1 : NarrowVgrGpr_8m1;
  def int_riscv_vnsrl_wi_8m2 : NarrowVgrGpr_8m2;
  def int_riscv_vnsrl_wi_8m4 : NarrowVgrGpr_8m4;

  def int_riscv_vnsra_wx_8m1 : NarrowVgrGpr_8m1;
  def int_riscv_vnsra_wx_8m2 : NarrowVgrGpr_8m2;
  def int_riscv_vnsra_wx_8m4 : NarrowVgrGpr_8m4;

  def int_riscv_vnsra_wi_8m1 : NarrowVgrGpr_8m1;
  def int_riscv_vnsra_wi_8m2 : NarrowVgrGpr_8m2;
  def int_riscv_vnsra_wi_8m4 : NarrowVgrGpr_8m4;


  def int_riscv_vnsrl_wx_16m1 : NarrowVgrGpr_16m1;
  def int_riscv_vnsrl_wx_16m2 : NarrowVgrGpr_16m2;
  def int_riscv_vnsrl_wx_16m4 : NarrowVgrGpr_16m4;

  def int_riscv_vnsrl_wi_16m1 : NarrowVgrGpr_16m1;
  def int_riscv_vnsrl_wi_16m2 : NarrowVgrGpr_16m2;
  def int_riscv_vnsrl_wi_16m4 : NarrowVgrGpr_16m4;

  def int_riscv_vnsra_wx_16m1 : NarrowVgrGpr_16m1;
  def int_riscv_vnsra_wx_16m2 : NarrowVgrGpr_16m2;
  def int_riscv_vnsra_wx_16m4 : NarrowVgrGpr_16m4;

  def int_riscv_vnsra_wi_16m1 : NarrowVgrGpr_16m1;
  def int_riscv_vnsra_wi_16m2 : NarrowVgrGpr_16m2;
  def int_riscv_vnsra_wi_16m4 : NarrowVgrGpr_16m4;


  //masked functions

  class VmNarrowVgrVgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VmNarrowVgrVgr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class VmNarrowVgrVgr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_v64i8_ty],[IntrNoMem]>;

  class VmNarrowVgrVgr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class VmNarrowVgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class VmNarrowVgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_v32i16_ty],[IntrNoMem]>;

  class VmNarrowVgrGpr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmNarrowVgrGpr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmNarrowVgrGpr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_i32_ty],[IntrNoMem]>;

  class VmNarrowVgrGpr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmNarrowVgrGpr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class VmNarrowVgrGpr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_i32_ty],[IntrNoMem]>;


  def int_riscv_vnsrl_wv_8m1_m : VmNarrowVgrVgr_8m1;
  def int_riscv_vnsrl_wv_8m2_m : VmNarrowVgrVgr_8m2;
  def int_riscv_vnsrl_wv_8m4_m : VmNarrowVgrVgr_8m4;

  def int_riscv_vnsra_wv_8m1_m : VmNarrowVgrVgr_8m1;
  def int_riscv_vnsra_wv_8m2_m : VmNarrowVgrVgr_8m2;
  def int_riscv_vnsra_wv_8m4_m : VmNarrowVgrVgr_8m4;


  def int_riscv_vnsrl_wv_16m1_m : VmNarrowVgrVgr_16m1;
  def int_riscv_vnsrl_wv_16m2_m : VmNarrowVgrVgr_16m2;
  def int_riscv_vnsrl_wv_16m4_m : VmNarrowVgrVgr_16m4;

  def int_riscv_vnsra_wv_16m1_m : VmNarrowVgrVgr_16m1;
  def int_riscv_vnsra_wv_16m2_m : VmNarrowVgrVgr_16m2;
  def int_riscv_vnsra_wv_16m4_m : VmNarrowVgrVgr_16m4;


  def int_riscv_vnsrl_wx_8m1_m : VmNarrowVgrGpr_8m1;
  def int_riscv_vnsrl_wx_8m2_m : VmNarrowVgrGpr_8m2;
  def int_riscv_vnsrl_wx_8m4_m : VmNarrowVgrGpr_8m4;

  def int_riscv_vnsrl_wi_8m1_m : VmNarrowVgrGpr_8m1;
  def int_riscv_vnsrl_wi_8m2_m : VmNarrowVgrGpr_8m2;
  def int_riscv_vnsrl_wi_8m4_m : VmNarrowVgrGpr_8m4;

  def int_riscv_vnsra_wx_8m1_m : VmNarrowVgrGpr_8m1;
  def int_riscv_vnsra_wx_8m2_m : VmNarrowVgrGpr_8m2;
  def int_riscv_vnsra_wx_8m4_m : VmNarrowVgrGpr_8m4;

  def int_riscv_vnsra_wi_8m1_m : VmNarrowVgrGpr_8m1;
  def int_riscv_vnsra_wi_8m2_m : VmNarrowVgrGpr_8m2;
  def int_riscv_vnsra_wi_8m4_m : VmNarrowVgrGpr_8m4;


  def int_riscv_vnsrl_wx_16m1_m : VmNarrowVgrGpr_16m1;
  def int_riscv_vnsrl_wx_16m2_m : VmNarrowVgrGpr_16m2;
  def int_riscv_vnsrl_wx_16m4_m : VmNarrowVgrGpr_16m4;

  def int_riscv_vnsrl_wi_16m1_m : VmNarrowVgrGpr_16m1;
  def int_riscv_vnsrl_wi_16m2_m : VmNarrowVgrGpr_16m2;
  def int_riscv_vnsrl_wi_16m4_m : VmNarrowVgrGpr_16m4;

  def int_riscv_vnsra_wx_16m1_m : VmNarrowVgrGpr_16m1;
  def int_riscv_vnsra_wx_16m2_m : VmNarrowVgrGpr_16m2;
  def int_riscv_vnsra_wx_16m4_m : VmNarrowVgrGpr_16m4;

  def int_riscv_vnsra_wi_16m1_m : VmNarrowVgrGpr_16m1;
  def int_riscv_vnsra_wi_16m2_m : VmNarrowVgrGpr_16m2;
  def int_riscv_vnsra_wi_16m4_m : VmNarrowVgrGpr_16m4; 


  //Vector Integer Comparison Functions

  def int_riscv_vmseq_vv_8m1 : Vm_VgrVgr_8m1;
  def int_riscv_vmseq_vv_8m2 : Vm_VgrVgr_8m2;  
  def int_riscv_vmseq_vv_8m4 : Vm_VgrVgr_8m4;
  def int_riscv_vmseq_vv_8m8 : Vm_VgrVgr_8m8;

  def int_riscv_vmsne_vv_8m1 : Vm_VgrVgr_8m1;
  def int_riscv_vmsne_vv_8m2 : Vm_VgrVgr_8m2;  
  def int_riscv_vmsne_vv_8m4 : Vm_VgrVgr_8m4;
  def int_riscv_vmsne_vv_8m8 : Vm_VgrVgr_8m8;

  def int_riscv_vmsltu_vv_8m1 : Vm_VgrVgr_8m1;
  def int_riscv_vmsltu_vv_8m2 : Vm_VgrVgr_8m2;  
  def int_riscv_vmsltu_vv_8m4 : Vm_VgrVgr_8m4;
  def int_riscv_vmsltu_vv_8m8 : Vm_VgrVgr_8m8;

  def int_riscv_vmslt_vv_8m1 : Vm_VgrVgr_8m1;
  def int_riscv_vmslt_vv_8m2 : Vm_VgrVgr_8m2;  
  def int_riscv_vmslt_vv_8m4 : Vm_VgrVgr_8m4;
  def int_riscv_vmslt_vv_8m8 : Vm_VgrVgr_8m8;

  def int_riscv_vmsleu_vv_8m1 : Vm_VgrVgr_8m1;
  def int_riscv_vmsleu_vv_8m2 : Vm_VgrVgr_8m2;  
  def int_riscv_vmsleu_vv_8m4 : Vm_VgrVgr_8m4;
  def int_riscv_vmsleu_vv_8m8 : Vm_VgrVgr_8m8;

  def int_riscv_vmsle_vv_8m1 : Vm_VgrVgr_8m1;
  def int_riscv_vmsle_vv_8m2 : Vm_VgrVgr_8m2;  
  def int_riscv_vmsle_vv_8m4 : Vm_VgrVgr_8m4;
  def int_riscv_vmsle_vv_8m8 : Vm_VgrVgr_8m8;


  def int_riscv_vmseq_vv_16m1 : Vm_VgrVgr_16m1;
  def int_riscv_vmseq_vv_16m2 : Vm_VgrVgr_16m2;  
  def int_riscv_vmseq_vv_16m4 : Vm_VgrVgr_16m4;
  def int_riscv_vmseq_vv_16m8 : Vm_VgrVgr_16m8;

  def int_riscv_vmsne_vv_16m1 : Vm_VgrVgr_16m1;
  def int_riscv_vmsne_vv_16m2 : Vm_VgrVgr_16m2;  
  def int_riscv_vmsne_vv_16m4 : Vm_VgrVgr_16m4;
  def int_riscv_vmsne_vv_16m8 : Vm_VgrVgr_16m8;

  def int_riscv_vmsltu_vv_16m1 : Vm_VgrVgr_16m1;
  def int_riscv_vmsltu_vv_16m2 : Vm_VgrVgr_16m2;  
  def int_riscv_vmsltu_vv_16m4 : Vm_VgrVgr_16m4;
  def int_riscv_vmsltu_vv_16m8 : Vm_VgrVgr_16m8;

  def int_riscv_vmslt_vv_16m1 : Vm_VgrVgr_16m1;
  def int_riscv_vmslt_vv_16m2 : Vm_VgrVgr_16m2;  
  def int_riscv_vmslt_vv_16m4 : Vm_VgrVgr_16m4;
  def int_riscv_vmslt_vv_16m8 : Vm_VgrVgr_16m8;

  def int_riscv_vmsleu_vv_16m1 : Vm_VgrVgr_16m1;
  def int_riscv_vmsleu_vv_16m2 : Vm_VgrVgr_16m2;  
  def int_riscv_vmsleu_vv_16m4 : Vm_VgrVgr_16m4;
  def int_riscv_vmsleu_vv_16m8 : Vm_VgrVgr_16m8;

  def int_riscv_vmsle_vv_16m1 : Vm_VgrVgr_16m1;
  def int_riscv_vmsle_vv_16m2 : Vm_VgrVgr_16m2;  
  def int_riscv_vmsle_vv_16m4 : Vm_VgrVgr_16m4;
  def int_riscv_vmsle_vv_16m8 : Vm_VgrVgr_16m8;


  def int_riscv_vmseq_vv_32m1 : Vm_VgrVgr_32m1;
  def int_riscv_vmseq_vv_32m2 : Vm_VgrVgr_32m2;  
  def int_riscv_vmseq_vv_32m4 : Vm_VgrVgr_32m4;
  def int_riscv_vmseq_vv_32m8 : Vm_VgrVgr_32m8;

  def int_riscv_vmsne_vv_32m1 : Vm_VgrVgr_32m1;
  def int_riscv_vmsne_vv_32m2 : Vm_VgrVgr_32m2;  
  def int_riscv_vmsne_vv_32m4 : Vm_VgrVgr_32m4;
  def int_riscv_vmsne_vv_32m8 : Vm_VgrVgr_32m8;

  def int_riscv_vmsltu_vv_32m1 : Vm_VgrVgr_32m1;
  def int_riscv_vmsltu_vv_32m2 : Vm_VgrVgr_32m2;  
  def int_riscv_vmsltu_vv_32m4 : Vm_VgrVgr_32m4;
  def int_riscv_vmsltu_vv_32m8 : Vm_VgrVgr_32m8;

  def int_riscv_vmslt_vv_32m1 : Vm_VgrVgr_32m1;
  def int_riscv_vmslt_vv_32m2 : Vm_VgrVgr_32m2;  
  def int_riscv_vmslt_vv_32m4 : Vm_VgrVgr_32m4;
  def int_riscv_vmslt_vv_32m8 : Vm_VgrVgr_32m8;

  def int_riscv_vmsleu_vv_32m1 : Vm_VgrVgr_32m1;
  def int_riscv_vmsleu_vv_32m2 : Vm_VgrVgr_32m2;  
  def int_riscv_vmsleu_vv_32m4 : Vm_VgrVgr_32m4;
  def int_riscv_vmsleu_vv_32m8 : Vm_VgrVgr_32m8;

  def int_riscv_vmsle_vv_32m1 : Vm_VgrVgr_32m1;
  def int_riscv_vmsle_vv_32m2 : Vm_VgrVgr_32m2;  
  def int_riscv_vmsle_vv_32m4 : Vm_VgrVgr_32m4;
  def int_riscv_vmsle_vv_32m8 : Vm_VgrVgr_32m8;


  def int_riscv_vmseq_vx_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmseq_vx_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmseq_vx_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmseq_vx_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmseq_vi_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmseq_vi_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmseq_vi_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmseq_vi_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsne_vx_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsne_vx_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsne_vx_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsne_vx_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsne_vi_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsne_vi_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsne_vi_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsne_vi_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsltu_vx_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsltu_vx_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsltu_vx_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsltu_vx_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmslt_vx_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmslt_vx_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmslt_vx_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmslt_vx_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsleu_vx_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsleu_vx_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsleu_vx_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsleu_vx_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsleu_vi_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsleu_vi_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsleu_vi_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsleu_vi_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsle_vx_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsle_vx_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsle_vx_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsle_vx_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsle_vi_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsle_vi_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsle_vi_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsle_vi_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsgtu_vx_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsgtu_vx_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsgtu_vx_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsgtu_vx_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsgtu_vi_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsgtu_vi_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsgtu_vi_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsgtu_vi_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsgt_vx_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsgt_vx_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsgt_vx_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsgt_vx_8m8 : Vm_VgrGpr_8m8;

  def int_riscv_vmsgt_vi_8m1 : Vm_VgrGpr_8m1;
  def int_riscv_vmsgt_vi_8m2 : Vm_VgrGpr_8m2;  
  def int_riscv_vmsgt_vi_8m4 : Vm_VgrGpr_8m4;
  def int_riscv_vmsgt_vi_8m8 : Vm_VgrGpr_8m8;


  def int_riscv_vmseq_vx_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmseq_vx_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmseq_vx_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmseq_vx_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmseq_vi_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmseq_vi_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmseq_vi_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmseq_vi_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsne_vx_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsne_vx_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsne_vx_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsne_vx_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsne_vi_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsne_vi_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsne_vi_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsne_vi_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsltu_vx_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsltu_vx_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsltu_vx_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsltu_vx_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmslt_vx_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmslt_vx_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmslt_vx_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmslt_vx_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsleu_vx_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsleu_vx_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsleu_vx_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsleu_vx_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsleu_vi_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsleu_vi_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsleu_vi_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsleu_vi_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsle_vx_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsle_vx_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsle_vx_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsle_vx_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsle_vi_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsle_vi_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsle_vi_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsle_vi_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsgtu_vx_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsgtu_vx_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsgtu_vx_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsgtu_vx_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsgtu_vi_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsgtu_vi_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsgtu_vi_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsgtu_vi_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsgt_vx_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsgt_vx_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsgt_vx_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsgt_vx_16m8 : Vm_VgrGpr_16m8;

  def int_riscv_vmsgt_vi_16m1 : Vm_VgrGpr_16m1;
  def int_riscv_vmsgt_vi_16m2 : Vm_VgrGpr_16m2;  
  def int_riscv_vmsgt_vi_16m4 : Vm_VgrGpr_16m4;
  def int_riscv_vmsgt_vi_16m8 : Vm_VgrGpr_16m8;


  def int_riscv_vmseq_vx_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmseq_vx_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmseq_vx_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmseq_vx_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmseq_vi_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmseq_vi_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmseq_vi_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmseq_vi_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsne_vx_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsne_vx_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsne_vx_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsne_vx_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsne_vi_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsne_vi_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsne_vi_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsne_vi_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsltu_vx_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsltu_vx_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsltu_vx_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsltu_vx_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmslt_vx_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmslt_vx_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmslt_vx_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmslt_vx_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsleu_vx_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsleu_vx_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsleu_vx_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsleu_vx_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsleu_vi_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsleu_vi_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsleu_vi_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsleu_vi_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsle_vx_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsle_vx_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsle_vx_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsle_vx_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsle_vi_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsle_vi_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsle_vi_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsle_vi_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsgtu_vx_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsgtu_vx_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsgtu_vx_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsgtu_vx_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsgtu_vi_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsgtu_vi_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsgtu_vi_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsgtu_vi_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsgt_vx_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsgt_vx_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsgt_vx_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsgt_vx_32m8 : Vm_VgrGpr_32m8;

  def int_riscv_vmsgt_vi_32m1 : Vm_VgrGpr_32m1;
  def int_riscv_vmsgt_vi_32m2 : Vm_VgrGpr_32m2;  
  def int_riscv_vmsgt_vi_32m4 : Vm_VgrGpr_32m4;
  def int_riscv_vmsgt_vi_32m8 : Vm_VgrGpr_32m8;


  class Vm_VmVgrVgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_VmVgrVgr_8m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Vm_VmVgrVgr_8m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class Vm_VmVgrVgr_8m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v128i8_ty,llvm_v128i8_ty],[IntrNoMem]>;

  class Vm_VmVgrVgr_16m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Vm_VmVgrVgr_16m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Vm_VmVgrVgr_16m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class Vm_VmVgrVgr_16m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_v64i16_ty],[IntrNoMem]>;

  class Vm_VmVgrVgr_32m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v4i32_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class Vm_VmVgrVgr_32m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class Vm_VmVgrVgr_32m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class Vm_VmVgrVgr_32m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_v32i32_ty],[IntrNoMem]>;

  class Vm_VmVgrGpr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VmVgrGpr_8m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VmVgrGpr_8m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VmVgrGpr_8m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v128i8_ty,llvm_i32_ty],[IntrNoMem]>;

  class Vm_VmVgrGpr_16m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VmVgrGpr_16m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VmVgrGpr_16m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VmVgrGpr_16m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_i32_ty],[IntrNoMem]>;

  class Vm_VmVgrGpr_32m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v4i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VmVgrGpr_32m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VmVgrGpr_32m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vm_VmVgrGpr_32m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_i32_ty],[IntrNoMem]>;


  //masked functions

  def int_riscv_vmseq_vv_8m1_m : Vm_VmVgrVgr_8m1;
  def int_riscv_vmseq_vv_8m2_m : Vm_VmVgrVgr_8m2;  
  def int_riscv_vmseq_vv_8m4_m : Vm_VmVgrVgr_8m4;
  def int_riscv_vmseq_vv_8m8_m : Vm_VmVgrVgr_8m8;

  def int_riscv_vmsne_vv_8m1_m : Vm_VmVgrVgr_8m1;
  def int_riscv_vmsne_vv_8m2_m : Vm_VmVgrVgr_8m2;  
  def int_riscv_vmsne_vv_8m4_m : Vm_VmVgrVgr_8m4;
  def int_riscv_vmsne_vv_8m8_m : Vm_VmVgrVgr_8m8;

  def int_riscv_vmsltu_vv_8m1_m : Vm_VmVgrVgr_8m1;
  def int_riscv_vmsltu_vv_8m2_m : Vm_VmVgrVgr_8m2;  
  def int_riscv_vmsltu_vv_8m4_m : Vm_VmVgrVgr_8m4;
  def int_riscv_vmsltu_vv_8m8_m : Vm_VmVgrVgr_8m8;

  def int_riscv_vmslt_vv_8m1_m : Vm_VmVgrVgr_8m1;
  def int_riscv_vmslt_vv_8m2_m : Vm_VmVgrVgr_8m2;  
  def int_riscv_vmslt_vv_8m4_m : Vm_VmVgrVgr_8m4;
  def int_riscv_vmslt_vv_8m8_m : Vm_VmVgrVgr_8m8;

  def int_riscv_vmsleu_vv_8m1_m : Vm_VmVgrVgr_8m1;
  def int_riscv_vmsleu_vv_8m2_m : Vm_VmVgrVgr_8m2;  
  def int_riscv_vmsleu_vv_8m4_m : Vm_VmVgrVgr_8m4;
  def int_riscv_vmsleu_vv_8m8_m : Vm_VmVgrVgr_8m8;

  def int_riscv_vmsle_vv_8m1_m : Vm_VmVgrVgr_8m1;
  def int_riscv_vmsle_vv_8m2_m : Vm_VmVgrVgr_8m2;  
  def int_riscv_vmsle_vv_8m4_m : Vm_VmVgrVgr_8m4;
  def int_riscv_vmsle_vv_8m8_m : Vm_VmVgrVgr_8m8;


  def int_riscv_vmseq_vv_16m1_m : Vm_VmVgrVgr_16m1;
  def int_riscv_vmseq_vv_16m2_m : Vm_VmVgrVgr_16m2;  
  def int_riscv_vmseq_vv_16m4_m : Vm_VmVgrVgr_16m4;
  def int_riscv_vmseq_vv_16m8_m : Vm_VmVgrVgr_16m8;

  def int_riscv_vmsne_vv_16m1_m : Vm_VmVgrVgr_16m1;
  def int_riscv_vmsne_vv_16m2_m : Vm_VmVgrVgr_16m2;  
  def int_riscv_vmsne_vv_16m4_m : Vm_VmVgrVgr_16m4;
  def int_riscv_vmsne_vv_16m8_m : Vm_VmVgrVgr_16m8;

  def int_riscv_vmsltu_vv_16m1_m : Vm_VmVgrVgr_16m1;
  def int_riscv_vmsltu_vv_16m2_m : Vm_VmVgrVgr_16m2;  
  def int_riscv_vmsltu_vv_16m4_m : Vm_VmVgrVgr_16m4;
  def int_riscv_vmsltu_vv_16m8_m : Vm_VmVgrVgr_16m8;

  def int_riscv_vmslt_vv_16m1_m : Vm_VmVgrVgr_16m1;
  def int_riscv_vmslt_vv_16m2_m : Vm_VmVgrVgr_16m2;  
  def int_riscv_vmslt_vv_16m4_m : Vm_VmVgrVgr_16m4;
  def int_riscv_vmslt_vv_16m8_m : Vm_VmVgrVgr_16m8;

  def int_riscv_vmsleu_vv_16m1_m : Vm_VmVgrVgr_16m1;
  def int_riscv_vmsleu_vv_16m2_m : Vm_VmVgrVgr_16m2;  
  def int_riscv_vmsleu_vv_16m4_m : Vm_VmVgrVgr_16m4;
  def int_riscv_vmsleu_vv_16m8_m : Vm_VmVgrVgr_16m8;

  def int_riscv_vmsle_vv_16m1_m : Vm_VmVgrVgr_16m1;
  def int_riscv_vmsle_vv_16m2_m : Vm_VmVgrVgr_16m2;  
  def int_riscv_vmsle_vv_16m4_m : Vm_VmVgrVgr_16m4;
  def int_riscv_vmsle_vv_16m8_m : Vm_VmVgrVgr_16m8;


  def int_riscv_vmseq_vv_32m1_m : Vm_VmVgrVgr_32m1;
  def int_riscv_vmseq_vv_32m2_m : Vm_VmVgrVgr_32m2;  
  def int_riscv_vmseq_vv_32m4_m : Vm_VmVgrVgr_32m4;
  def int_riscv_vmseq_vv_32m8_m : Vm_VmVgrVgr_32m8;

  def int_riscv_vmsne_vv_32m1_m : Vm_VmVgrVgr_32m1;
  def int_riscv_vmsne_vv_32m2_m : Vm_VmVgrVgr_32m2;  
  def int_riscv_vmsne_vv_32m4_m : Vm_VmVgrVgr_32m4;
  def int_riscv_vmsne_vv_32m8_m : Vm_VmVgrVgr_32m8;

  def int_riscv_vmsltu_vv_32m1_m : Vm_VmVgrVgr_32m1;
  def int_riscv_vmsltu_vv_32m2_m : Vm_VmVgrVgr_32m2;  
  def int_riscv_vmsltu_vv_32m4_m : Vm_VmVgrVgr_32m4;
  def int_riscv_vmsltu_vv_32m8_m : Vm_VmVgrVgr_32m8;

  def int_riscv_vmslt_vv_32m1_m : Vm_VmVgrVgr_32m1;
  def int_riscv_vmslt_vv_32m2_m : Vm_VmVgrVgr_32m2;  
  def int_riscv_vmslt_vv_32m4_m : Vm_VmVgrVgr_32m4;
  def int_riscv_vmslt_vv_32m8_m : Vm_VmVgrVgr_32m8;

  def int_riscv_vmsleu_vv_32m1_m : Vm_VmVgrVgr_32m1;
  def int_riscv_vmsleu_vv_32m2_m : Vm_VmVgrVgr_32m2;  
  def int_riscv_vmsleu_vv_32m4_m : Vm_VmVgrVgr_32m4;
  def int_riscv_vmsleu_vv_32m8_m : Vm_VmVgrVgr_32m8;

  def int_riscv_vmsle_vv_32m1_m : Vm_VmVgrVgr_32m1;
  def int_riscv_vmsle_vv_32m2_m : Vm_VmVgrVgr_32m2;  
  def int_riscv_vmsle_vv_32m4_m : Vm_VmVgrVgr_32m4;
  def int_riscv_vmsle_vv_32m8_m : Vm_VmVgrVgr_32m8;


  def int_riscv_vmseq_vx_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmseq_vx_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmseq_vx_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmseq_vx_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmseq_vi_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmseq_vi_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmseq_vi_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmseq_vi_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsne_vx_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsne_vx_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsne_vx_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsne_vx_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsne_vi_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsne_vi_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsne_vi_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsne_vi_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsltu_vx_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsltu_vx_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsltu_vx_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsltu_vx_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmslt_vx_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmslt_vx_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmslt_vx_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmslt_vx_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsleu_vx_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsleu_vx_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsleu_vx_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsleu_vx_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsleu_vi_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsleu_vi_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsleu_vi_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsleu_vi_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsle_vx_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsle_vx_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsle_vx_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsle_vx_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsle_vi_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsle_vi_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsle_vi_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsle_vi_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsgtu_vx_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsgtu_vx_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsgtu_vx_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsgtu_vx_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsgtu_vi_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsgtu_vi_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsgtu_vi_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsgtu_vi_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsgt_vx_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsgt_vx_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsgt_vx_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsgt_vx_8m8_m : Vm_VmVgrGpr_8m8;

  def int_riscv_vmsgt_vi_8m1_m : Vm_VmVgrGpr_8m1;
  def int_riscv_vmsgt_vi_8m2_m : Vm_VmVgrGpr_8m2;  
  def int_riscv_vmsgt_vi_8m4_m : Vm_VmVgrGpr_8m4;
  def int_riscv_vmsgt_vi_8m8_m : Vm_VmVgrGpr_8m8;


  def int_riscv_vmseq_vx_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmseq_vx_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmseq_vx_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmseq_vx_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmseq_vi_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmseq_vi_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmseq_vi_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmseq_vi_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsne_vx_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsne_vx_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsne_vx_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsne_vx_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsne_vi_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsne_vi_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsne_vi_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsne_vi_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsltu_vx_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsltu_vx_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsltu_vx_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsltu_vx_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmslt_vx_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmslt_vx_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmslt_vx_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmslt_vx_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsleu_vx_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsleu_vx_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsleu_vx_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsleu_vx_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsleu_vi_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsleu_vi_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsleu_vi_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsleu_vi_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsle_vx_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsle_vx_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsle_vx_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsle_vx_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsle_vi_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsle_vi_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsle_vi_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsle_vi_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsgtu_vx_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsgtu_vx_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsgtu_vx_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsgtu_vx_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsgtu_vi_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsgtu_vi_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsgtu_vi_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsgtu_vi_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsgt_vx_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsgt_vx_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsgt_vx_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsgt_vx_16m8_m : Vm_VmVgrGpr_16m8;

  def int_riscv_vmsgt_vi_16m1_m : Vm_VmVgrGpr_16m1;
  def int_riscv_vmsgt_vi_16m2_m : Vm_VmVgrGpr_16m2;  
  def int_riscv_vmsgt_vi_16m4_m : Vm_VmVgrGpr_16m4;
  def int_riscv_vmsgt_vi_16m8_m : Vm_VmVgrGpr_16m8;


  def int_riscv_vmseq_vx_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmseq_vx_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmseq_vx_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmseq_vx_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmseq_vi_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmseq_vi_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmseq_vi_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmseq_vi_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsne_vx_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsne_vx_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsne_vx_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsne_vx_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsne_vi_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsne_vi_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsne_vi_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsne_vi_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsltu_vx_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsltu_vx_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsltu_vx_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsltu_vx_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmslt_vx_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmslt_vx_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmslt_vx_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmslt_vx_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsleu_vx_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsleu_vx_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsleu_vx_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsleu_vx_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsleu_vi_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsleu_vi_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsleu_vi_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsleu_vi_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsle_vx_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsle_vx_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsle_vx_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsle_vx_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsle_vi_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsle_vi_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsle_vi_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsle_vi_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsgtu_vx_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsgtu_vx_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsgtu_vx_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsgtu_vx_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsgtu_vi_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsgtu_vi_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsgtu_vi_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsgtu_vi_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsgt_vx_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsgt_vx_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsgt_vx_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsgt_vx_32m8_m : Vm_VmVgrGpr_32m8;

  def int_riscv_vmsgt_vi_32m1_m : Vm_VmVgrGpr_32m1;
  def int_riscv_vmsgt_vi_32m2_m : Vm_VmVgrGpr_32m2;  
  def int_riscv_vmsgt_vi_32m4_m : Vm_VmVgrGpr_32m4;
  def int_riscv_vmsgt_vi_32m8_m : Vm_VmVgrGpr_32m8;


  //Vector Integer Min/Max Functions

  def int_riscv_vminu_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vminu_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vminu_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vminu_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vmin_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vmin_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vmin_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vmin_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vmaxu_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vmaxu_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vmaxu_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vmaxu_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vmax_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vmax_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vmax_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vmax_vv_8m8 : VgrVgr_8m8;


  def int_riscv_vminu_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vminu_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vminu_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vminu_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vmin_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vmin_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vmin_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vmin_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vmaxu_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vmaxu_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vmaxu_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vmaxu_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vmax_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vmax_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vmax_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vmax_vv_16m8 : VgrVgr_16m8;


  def int_riscv_vminu_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vminu_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vminu_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vminu_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vmin_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vmin_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vmin_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vmin_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vmaxu_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vmaxu_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vmaxu_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vmaxu_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vmax_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vmax_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vmax_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vmax_vv_32m8 : VgrVgr_32m8;


  def int_riscv_vminu_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vminu_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vminu_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vminu_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vmin_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vmin_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vmin_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vmin_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vmaxu_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vmaxu_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vmaxu_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vmaxu_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vmax_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vmax_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vmax_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vmax_vx_8m8 : VgrGpr_8m8;


  def int_riscv_vminu_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vminu_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vminu_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vminu_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vmin_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vmin_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vmin_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vmin_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vmaxu_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vmaxu_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vmaxu_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vmaxu_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vmax_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vmax_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vmax_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vmax_vx_16m8 : VgrGpr_16m8;


  def int_riscv_vminu_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vminu_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vminu_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vminu_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vmin_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vmin_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vmin_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vmin_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vmaxu_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vmaxu_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vmaxu_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vmaxu_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vmax_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vmax_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vmax_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vmax_vx_32m8 : VgrGpr_32m8;


  //masked functions

  def int_riscv_vminu_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vminu_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vminu_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vminu_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vmin_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vmin_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vmin_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vmin_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vmaxu_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vmaxu_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vmaxu_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vmaxu_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vmax_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vmax_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vmax_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vmax_vv_8m8_m : VmVgrVgr_8m8;


  def int_riscv_vminu_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vminu_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vminu_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vminu_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vmin_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vmin_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vmin_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vmin_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vmaxu_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vmaxu_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vmaxu_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vmaxu_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vmax_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vmax_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vmax_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vmax_vv_16m8_m : VmVgrVgr_16m8;


  def int_riscv_vminu_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vminu_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vminu_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vminu_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vmin_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vmin_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vmin_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vmin_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vmaxu_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vmaxu_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vmaxu_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vmaxu_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vmax_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vmax_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vmax_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vmax_vv_32m8_m : VmVgrVgr_32m8;


  def int_riscv_vminu_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vminu_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vminu_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vminu_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vmin_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vmin_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vmin_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vmin_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vmaxu_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vmaxu_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vmaxu_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vmaxu_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vmax_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vmax_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vmax_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vmax_vx_8m8_m : VmVgrGpr_8m8;


  def int_riscv_vminu_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vminu_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vminu_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vminu_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vmin_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vmin_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vmin_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vmin_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vmaxu_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vmaxu_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vmaxu_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vmaxu_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vmax_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vmax_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vmax_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vmax_vx_16m8_m : VmVgrGpr_16m8;


  def int_riscv_vminu_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vminu_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vminu_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vminu_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vmin_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vmin_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vmin_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vmin_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vmaxu_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vmaxu_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vmaxu_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vmaxu_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vmax_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vmax_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vmax_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vmax_vx_32m8_m : VmVgrGpr_32m8;


  //Vector Single-Width Integer Multiply Functions

  def int_riscv_vmul_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vmul_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vmul_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vmul_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vmulh_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vmulh_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vmulh_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vmulh_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vmulhu_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vmulhu_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vmulhu_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vmulhu_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vmulhsu_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vmulhsu_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vmulhsu_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vmulhsu_vv_8m8 : VgrVgr_8m8;


  def int_riscv_vmul_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vmul_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vmul_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vmul_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vmulh_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vmulh_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vmulh_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vmulh_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vmulhu_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vmulhu_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vmulhu_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vmulhu_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vmulhsu_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vmulhsu_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vmulhsu_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vmulhsu_vv_16m8 : VgrVgr_16m8;


  def int_riscv_vmul_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vmul_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vmul_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vmul_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vmulh_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vmulh_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vmulh_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vmulh_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vmulhu_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vmulhu_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vmulhu_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vmulhu_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vmulhsu_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vmulhsu_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vmulhsu_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vmulhsu_vv_32m8 : VgrVgr_32m8;


  def int_riscv_vmul_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vmul_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vmul_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vmul_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vmulh_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vmulh_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vmulh_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vmulh_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vmulhu_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vmulhu_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vmulhu_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vmulhu_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vmulhsu_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vmulhsu_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vmulhsu_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vmulhsu_vx_8m8 : VgrGpr_8m8;


  def int_riscv_vmul_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vmul_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vmul_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vmul_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vmulh_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vmulh_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vmulh_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vmulh_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vmulhu_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vmulhu_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vmulhu_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vmulhu_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vmulhsu_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vmulhsu_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vmulhsu_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vmulhsu_vx_16m8 : VgrGpr_16m8;


  def int_riscv_vmul_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vmul_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vmul_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vmul_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vmulh_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vmulh_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vmulh_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vmulh_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vmulhu_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vmulhu_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vmulhu_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vmulhu_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vmulhsu_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vmulhsu_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vmulhsu_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vmulhsu_vx_32m8 : VgrGpr_32m8;


  //masked functions

  def int_riscv_vmul_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vmul_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vmul_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vmul_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vmulh_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vmulh_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vmulh_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vmulh_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vmulhu_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vmulhu_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vmulhu_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vmulhu_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vmulhsu_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vmulhsu_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vmulhsu_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vmulhsu_vv_8m8_m : VmVgrVgr_8m8;


  def int_riscv_vmul_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vmul_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vmul_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vmul_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vmulh_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vmulh_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vmulh_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vmulh_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vmulhu_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vmulhu_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vmulhu_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vmulhu_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vmulhsu_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vmulhsu_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vmulhsu_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vmulhsu_vv_16m8_m : VmVgrVgr_16m8;


  def int_riscv_vmul_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vmul_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vmul_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vmul_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vmulh_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vmulh_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vmulh_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vmulh_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vmulhu_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vmulhu_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vmulhu_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vmulhu_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vmulhsu_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vmulhsu_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vmulhsu_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vmulhsu_vv_32m8_m : VmVgrVgr_32m8;


  def int_riscv_vmul_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vmul_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vmul_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vmul_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vmulh_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vmulh_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vmulh_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vmulh_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vmulhu_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vmulhu_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vmulhu_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vmulhu_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vmulhsu_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vmulhsu_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vmulhsu_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vmulhsu_vx_8m8_m : VmVgrGpr_8m8;


  def int_riscv_vmul_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vmul_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vmul_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vmul_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vmulh_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vmulh_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vmulh_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vmulh_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vmulhu_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vmulhu_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vmulhu_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vmulhu_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vmulhsu_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vmulhsu_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vmulhsu_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vmulhsu_vx_16m8_m : VmVgrGpr_16m8;


  def int_riscv_vmul_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vmul_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vmul_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vmul_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vmulh_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vmulh_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vmulh_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vmulh_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vmulhu_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vmulhu_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vmulhu_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vmulhu_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vmulhsu_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vmulhsu_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vmulhsu_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vmulhsu_vx_32m8_m : VmVgrGpr_32m8;


  //Vector Integer Divide Functions

  def int_riscv_vdivu_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vdivu_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vdivu_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vdivu_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vdiv_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vdiv_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vdiv_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vdiv_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vremu_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vremu_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vremu_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vremu_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vrem_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vrem_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vrem_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vrem_vv_8m8 : VgrVgr_8m8;


  def int_riscv_vdivu_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vdivu_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vdivu_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vdivu_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vdiv_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vdiv_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vdiv_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vdiv_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vremu_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vremu_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vremu_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vremu_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vrem_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vrem_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vrem_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vrem_vv_16m8 : VgrVgr_16m8;


  def int_riscv_vdivu_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vdivu_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vdivu_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vdivu_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vdiv_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vdiv_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vdiv_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vdiv_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vremu_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vremu_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vremu_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vremu_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vrem_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vrem_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vrem_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vrem_vv_32m8 : VgrVgr_32m8;


  def int_riscv_vdivu_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vdivu_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vdivu_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vdivu_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vdiv_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vdiv_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vdiv_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vdiv_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vremu_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vremu_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vremu_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vremu_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vrem_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vrem_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vrem_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vrem_vx_8m8 : VgrGpr_8m8;


  def int_riscv_vdivu_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vdivu_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vdivu_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vdivu_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vdiv_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vdiv_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vdiv_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vdiv_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vremu_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vremu_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vremu_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vremu_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vrem_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vrem_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vrem_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vrem_vx_16m8 : VgrGpr_16m8;


  def int_riscv_vdivu_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vdivu_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vdivu_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vdivu_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vdiv_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vdiv_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vdiv_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vdiv_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vremu_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vremu_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vremu_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vremu_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vrem_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vrem_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vrem_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vrem_vx_32m8 : VgrGpr_32m8;


  //masked functions

  def int_riscv_vdivu_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vdivu_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vdivu_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vdivu_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vdiv_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vdiv_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vdiv_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vdiv_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vremu_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vremu_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vremu_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vremu_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vrem_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vrem_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vrem_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vrem_vv_8m8_m : VmVgrVgr_8m8;


  def int_riscv_vdivu_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vdivu_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vdivu_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vdivu_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vdiv_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vdiv_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vdiv_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vdiv_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vremu_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vremu_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vremu_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vremu_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vrem_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vrem_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vrem_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vrem_vv_16m8_m : VmVgrVgr_16m8;


  def int_riscv_vdivu_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vdivu_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vdivu_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vdivu_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vdiv_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vdiv_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vdiv_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vdiv_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vremu_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vremu_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vremu_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vremu_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vrem_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vrem_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vrem_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vrem_vv_32m8_m : VmVgrVgr_32m8;


  def int_riscv_vdivu_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vdivu_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vdivu_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vdivu_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vdiv_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vdiv_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vdiv_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vdiv_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vremu_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vremu_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vremu_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vremu_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vrem_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vrem_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vrem_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vrem_vx_8m8_m : VmVgrGpr_8m8;


  def int_riscv_vdivu_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vdivu_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vdivu_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vdivu_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vdiv_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vdiv_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vdiv_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vdiv_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vremu_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vremu_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vremu_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vremu_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vrem_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vrem_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vrem_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vrem_vx_16m8_m : VmVgrGpr_16m8;


  def int_riscv_vdivu_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vdivu_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vdivu_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vdivu_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vdiv_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vdiv_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vdiv_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vdiv_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vremu_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vremu_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vremu_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vremu_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vrem_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vrem_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vrem_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vrem_vx_32m8_m : VmVgrGpr_32m8;  


  //Vector Widening Integer Multiply Funtions

  def int_riscv_vwmul_vv_16m2 : Widen_VgrVgr_16m2;
  def int_riscv_vwmul_vv_16m4 : Widen_VgrVgr_16m4;
  def int_riscv_vwmul_vv_16m8 : Widen_VgrVgr_16m8;

  def int_riscv_vwmulu_vv_16m2 : Widen_VgrVgr_16m2;
  def int_riscv_vwmulu_vv_16m4 : Widen_VgrVgr_16m4;
  def int_riscv_vwmulu_vv_16m8 : Widen_VgrVgr_16m8;

  def int_riscv_vwmulsu_vv_16m2 : Widen_VgrVgr_16m2;
  def int_riscv_vwmulsu_vv_16m4 : Widen_VgrVgr_16m4;
  def int_riscv_vwmulsu_vv_16m8 : Widen_VgrVgr_16m8;


  def int_riscv_vwmul_vv_32m2 : Widen_VgrVgr_32m2;
  def int_riscv_vwmul_vv_32m4 : Widen_VgrVgr_32m4;
  def int_riscv_vwmul_vv_32m8 : Widen_VgrVgr_32m8;

  def int_riscv_vwmulu_vv_32m2 : Widen_VgrVgr_32m2;
  def int_riscv_vwmulu_vv_32m4 : Widen_VgrVgr_32m4;
  def int_riscv_vwmulu_vv_32m8 : Widen_VgrVgr_32m8;

  def int_riscv_vwmulsu_vv_32m2 : Widen_VgrVgr_32m2;
  def int_riscv_vwmulsu_vv_32m4 : Widen_VgrVgr_32m4;
  def int_riscv_vwmulsu_vv_32m8 : Widen_VgrVgr_32m8;


  def int_riscv_vwmul_vx_16m2 : Widen_VgrGpr_16m2;
  def int_riscv_vwmul_vx_16m4 : Widen_VgrGpr_16m4;
  def int_riscv_vwmul_vx_16m8 : Widen_VgrGpr_16m8;

  def int_riscv_vwmulu_vx_16m2 : Widen_VgrGpr_16m2;
  def int_riscv_vwmulu_vx_16m4 : Widen_VgrGpr_16m4;
  def int_riscv_vwmulu_vx_16m8 : Widen_VgrGpr_16m8;

  def int_riscv_vwmulsu_vx_16m2 : Widen_VgrGpr_16m2;
  def int_riscv_vwmulsu_vx_16m4 : Widen_VgrGpr_16m4;
  def int_riscv_vwmulsu_vx_16m8 : Widen_VgrGpr_16m8;


  def int_riscv_vwmul_vx_32m2 : Widen_VgrGpr_32m2;
  def int_riscv_vwmul_vx_32m4 : Widen_VgrGpr_32m4;
  def int_riscv_vwmul_vx_32m8 : Widen_VgrGpr_32m8;

  def int_riscv_vwmulu_vx_32m2 : Widen_VgrGpr_32m2;
  def int_riscv_vwmulu_vx_32m4 : Widen_VgrGpr_32m4;
  def int_riscv_vwmulu_vx_32m8 : Widen_VgrGpr_32m8;

  def int_riscv_vwmulsu_vx_32m2 : Widen_VgrGpr_32m2;
  def int_riscv_vwmulsu_vx_32m4 : Widen_VgrGpr_32m4;
  def int_riscv_vwmulsu_vx_32m8 : Widen_VgrGpr_32m8;


  //masked functions

  def int_riscv_vwmul_vv_16m2_m : Widen_VmVgrVgr_16m2;
  def int_riscv_vwmul_vv_16m4_m : Widen_VmVgrVgr_16m4;
  def int_riscv_vwmul_vv_16m8_m : Widen_VmVgrVgr_16m8;

  def int_riscv_vwmulu_vv_16m2_m : Widen_VmVgrVgr_16m2;
  def int_riscv_vwmulu_vv_16m4_m : Widen_VmVgrVgr_16m4;
  def int_riscv_vwmulu_vv_16m8_m : Widen_VmVgrVgr_16m8;

  def int_riscv_vwmulsu_vv_16m2_m : Widen_VmVgrVgr_16m2;
  def int_riscv_vwmulsu_vv_16m4_m : Widen_VmVgrVgr_16m4;
  def int_riscv_vwmulsu_vv_16m8_m : Widen_VmVgrVgr_16m8;


  def int_riscv_vwmul_vv_32m2_m : Widen_VmVgrVgr_32m2;
  def int_riscv_vwmul_vv_32m4_m : Widen_VmVgrVgr_32m4;
  def int_riscv_vwmul_vv_32m8_m : Widen_VmVgrVgr_32m8;

  def int_riscv_vwmulu_vv_32m2_m : Widen_VmVgrVgr_32m2;
  def int_riscv_vwmulu_vv_32m4_m : Widen_VmVgrVgr_32m4;
  def int_riscv_vwmulu_vv_32m8_m : Widen_VmVgrVgr_32m8;

  def int_riscv_vwmulsu_vv_32m2_m : Widen_VmVgrVgr_32m2;
  def int_riscv_vwmulsu_vv_32m4_m : Widen_VmVgrVgr_32m4;
  def int_riscv_vwmulsu_vv_32m8_m : Widen_VmVgrVgr_32m8;


  def int_riscv_vwmul_vx_16m2_m : Widen_VmVgrGpr_16m2;
  def int_riscv_vwmul_vx_16m4_m : Widen_VmVgrGpr_16m4;
  def int_riscv_vwmul_vx_16m8_m : Widen_VmVgrGpr_16m8;

  def int_riscv_vwmulu_vx_16m2_m : Widen_VmVgrGpr_16m2;
  def int_riscv_vwmulu_vx_16m4_m : Widen_VmVgrGpr_16m4;
  def int_riscv_vwmulu_vx_16m8_m : Widen_VmVgrGpr_16m8;

  def int_riscv_vwmulsu_vx_16m2_m : Widen_VmVgrGpr_16m2;
  def int_riscv_vwmulsu_vx_16m4_m : Widen_VmVgrGpr_16m4;
  def int_riscv_vwmulsu_vx_16m8_m : Widen_VmVgrGpr_16m8;


  def int_riscv_vwmul_vx_32m2_m : Widen_VmVgrGpr_32m2;
  def int_riscv_vwmul_vx_32m4_m : Widen_VmVgrGpr_32m4;
  def int_riscv_vwmul_vx_32m8_m : Widen_VmVgrGpr_32m8;

  def int_riscv_vwmulu_vx_32m2_m : Widen_VmVgrGpr_32m2;
  def int_riscv_vwmulu_vx_32m4_m : Widen_VmVgrGpr_32m4;
  def int_riscv_vwmulu_vx_32m8_m : Widen_VmVgrGpr_32m8;

  def int_riscv_vwmulsu_vx_32m2_m : Widen_VmVgrGpr_32m2;
  def int_riscv_vwmulsu_vx_32m4_m : Widen_VmVgrGpr_32m4;
  def int_riscv_vwmulsu_vx_32m8_m : Widen_VmVgrGpr_32m8;


  //Vector Single-Width Integer Multiply-Add Functions

  class VgrVgrVgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrVgrVgr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i8_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class VgrVgrVgr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i8_ty,llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class VgrVgrVgr_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v128i8_ty,llvm_v128i8_ty,llvm_v128i8_ty],[IntrNoMem]>;

  class VgrVgrVgr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i16_ty,llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class VgrVgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class VgrVgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class VgrVgrVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_v64i16_ty,llvm_v64i16_ty],[IntrNoMem]>;

  class VgrVgrVgr_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4i32_ty,llvm_v4i32_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class VgrVgrVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_v8i32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class VgrVgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_v16i32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class VgrVgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_v32i32_ty,llvm_v32i32_ty],[IntrNoMem]>;

  class VgrGprVgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VgrGprVgr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i8_ty,llvm_i32_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class VgrGprVgr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i8_ty,llvm_i32_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class VgrGprVgr_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v128i8_ty,llvm_i32_ty,llvm_v128i8_ty],[IntrNoMem]>;

  class VgrGprVgr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i16_ty,llvm_i32_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class VgrGprVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_i32_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class VgrGprVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_i32_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class VgrGprVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_i32_ty,llvm_v64i16_ty],[IntrNoMem]>;

  class VgrGprVgr_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4i32_ty,llvm_i32_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class VgrGprVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_i32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class VgrGprVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_i32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class VgrGprVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_i32_ty,llvm_v32i32_ty],[IntrNoMem]>;


  def int_riscv_vmacc_vv_8m1 : VgrVgrVgr_8m1;
  def int_riscv_vmacc_vv_8m2 : VgrVgrVgr_8m2;
  def int_riscv_vmacc_vv_8m4 : VgrVgrVgr_8m4;
  def int_riscv_vmacc_vv_8m8 : VgrVgrVgr_8m8;

  def int_riscv_vnmsac_vv_8m1 : VgrVgrVgr_8m1;
  def int_riscv_vnmsac_vv_8m2 : VgrVgrVgr_8m2;
  def int_riscv_vnmsac_vv_8m4 : VgrVgrVgr_8m4;
  def int_riscv_vnmsac_vv_8m8 : VgrVgrVgr_8m8;

  def int_riscv_vmadd_vv_8m1 : VgrVgrVgr_8m1;
  def int_riscv_vmadd_vv_8m2 : VgrVgrVgr_8m2;
  def int_riscv_vmadd_vv_8m4 : VgrVgrVgr_8m4;
  def int_riscv_vmadd_vv_8m8 : VgrVgrVgr_8m8;

  def int_riscv_vnmsub_vv_8m1 : VgrVgrVgr_8m1;
  def int_riscv_vnmsub_vv_8m2 : VgrVgrVgr_8m2;
  def int_riscv_vnmsub_vv_8m4 : VgrVgrVgr_8m4;
  def int_riscv_vnmsub_vv_8m8 : VgrVgrVgr_8m8;


  def int_riscv_vmacc_vv_16m1 : VgrVgrVgr_16m1;
  def int_riscv_vmacc_vv_16m2 : VgrVgrVgr_16m2;
  def int_riscv_vmacc_vv_16m4 : VgrVgrVgr_16m4;
  def int_riscv_vmacc_vv_16m8 : VgrVgrVgr_16m8;

  def int_riscv_vnmsac_vv_16m1 : VgrVgrVgr_16m1;
  def int_riscv_vnmsac_vv_16m2 : VgrVgrVgr_16m2;
  def int_riscv_vnmsac_vv_16m4 : VgrVgrVgr_16m4;
  def int_riscv_vnmsac_vv_16m8 : VgrVgrVgr_16m8;

  def int_riscv_vmadd_vv_16m1 : VgrVgrVgr_16m1;
  def int_riscv_vmadd_vv_16m2 : VgrVgrVgr_16m2;
  def int_riscv_vmadd_vv_16m4 : VgrVgrVgr_16m4;
  def int_riscv_vmadd_vv_16m8 : VgrVgrVgr_16m8;

  def int_riscv_vnmsub_vv_16m1 : VgrVgrVgr_16m1;
  def int_riscv_vnmsub_vv_16m2 : VgrVgrVgr_16m2;
  def int_riscv_vnmsub_vv_16m4 : VgrVgrVgr_16m4;
  def int_riscv_vnmsub_vv_16m8 : VgrVgrVgr_16m8;


  def int_riscv_vmacc_vv_32m1 : VgrVgrVgr_32m1;
  def int_riscv_vmacc_vv_32m2 : VgrVgrVgr_32m2;
  def int_riscv_vmacc_vv_32m4 : VgrVgrVgr_32m4;
  def int_riscv_vmacc_vv_32m8 : VgrVgrVgr_32m8;

  def int_riscv_vnmsac_vv_32m1 : VgrVgrVgr_32m1;
  def int_riscv_vnmsac_vv_32m2 : VgrVgrVgr_32m2;
  def int_riscv_vnmsac_vv_32m4 : VgrVgrVgr_32m4;
  def int_riscv_vnmsac_vv_32m8 : VgrVgrVgr_32m8;

  def int_riscv_vmadd_vv_32m1 : VgrVgrVgr_32m1;
  def int_riscv_vmadd_vv_32m2 : VgrVgrVgr_32m2;
  def int_riscv_vmadd_vv_32m4 : VgrVgrVgr_32m4;
  def int_riscv_vmadd_vv_32m8 : VgrVgrVgr_32m8;

  def int_riscv_vnmsub_vv_32m1 : VgrVgrVgr_32m1;
  def int_riscv_vnmsub_vv_32m2 : VgrVgrVgr_32m2;
  def int_riscv_vnmsub_vv_32m4 : VgrVgrVgr_32m4;
  def int_riscv_vnmsub_vv_32m8 : VgrVgrVgr_32m8;


  def int_riscv_vmacc_vx_8m1 : VgrGprVgr_8m1;
  def int_riscv_vmacc_vx_8m2 : VgrGprVgr_8m2;
  def int_riscv_vmacc_vx_8m4 : VgrGprVgr_8m4;
  def int_riscv_vmacc_vx_8m8 : VgrGprVgr_8m8;
  
  def int_riscv_vnmsac_vx_8m1 : VgrGprVgr_8m1;
  def int_riscv_vnmsac_vx_8m2 : VgrGprVgr_8m2;
  def int_riscv_vnmsac_vx_8m4 : VgrGprVgr_8m4;
  def int_riscv_vnmsac_vx_8m8 : VgrGprVgr_8m8;

  def int_riscv_vmadd_vx_8m1 : VgrGprVgr_8m1;
  def int_riscv_vmadd_vx_8m2 : VgrGprVgr_8m2;
  def int_riscv_vmadd_vx_8m4 : VgrGprVgr_8m4;
  def int_riscv_vmadd_vx_8m8 : VgrGprVgr_8m8;

  def int_riscv_vnmsub_vx_8m1 : VgrGprVgr_8m1;
  def int_riscv_vnmsub_vx_8m2 : VgrGprVgr_8m2;
  def int_riscv_vnmsub_vx_8m4 : VgrGprVgr_8m4;
  def int_riscv_vnmsub_vx_8m8 : VgrGprVgr_8m8;


  def int_riscv_vmacc_vx_16m1 : VgrGprVgr_16m1;
  def int_riscv_vmacc_vx_16m2 : VgrGprVgr_16m2;
  def int_riscv_vmacc_vx_16m4 : VgrGprVgr_16m4;
  def int_riscv_vmacc_vx_16m8 : VgrGprVgr_16m8;

  def int_riscv_vnmsac_vx_16m1 : VgrGprVgr_16m1;
  def int_riscv_vnmsac_vx_16m2 : VgrGprVgr_16m2;
  def int_riscv_vnmsac_vx_16m4 : VgrGprVgr_16m4;
  def int_riscv_vnmsac_vx_16m8 : VgrGprVgr_16m8;

  def int_riscv_vmadd_vx_16m1 : VgrGprVgr_16m1;
  def int_riscv_vmadd_vx_16m2 : VgrGprVgr_16m2;
  def int_riscv_vmadd_vx_16m4 : VgrGprVgr_16m4;
  def int_riscv_vmadd_vx_16m8 : VgrGprVgr_16m8;

  def int_riscv_vnmsub_vx_16m1 : VgrGprVgr_16m1;
  def int_riscv_vnmsub_vx_16m2 : VgrGprVgr_16m2;
  def int_riscv_vnmsub_vx_16m4 : VgrGprVgr_16m4;
  def int_riscv_vnmsub_vx_16m8 : VgrGprVgr_16m8;


  def int_riscv_vmacc_vx_32m1 : VgrGprVgr_32m1;
  def int_riscv_vmacc_vx_32m2 : VgrGprVgr_32m2;
  def int_riscv_vmacc_vx_32m4 : VgrGprVgr_32m4;
  def int_riscv_vmacc_vx_32m8 : VgrGprVgr_32m8;

  def int_riscv_vnmsac_vx_32m1 : VgrGprVgr_32m1;
  def int_riscv_vnmsac_vx_32m2 : VgrGprVgr_32m2;
  def int_riscv_vnmsac_vx_32m4 : VgrGprVgr_32m4;
  def int_riscv_vnmsac_vx_32m8 : VgrGprVgr_32m8;

  def int_riscv_vmadd_vx_32m1 : VgrGprVgr_32m1;
  def int_riscv_vmadd_vx_32m2 : VgrGprVgr_32m2;
  def int_riscv_vmadd_vx_32m4 : VgrGprVgr_32m4;
  def int_riscv_vmadd_vx_32m8 : VgrGprVgr_32m8;

  def int_riscv_vnmsub_vx_32m1 : VgrGprVgr_32m1;
  def int_riscv_vnmsub_vx_32m2 : VgrGprVgr_32m2;
  def int_riscv_vnmsub_vx_32m4 : VgrGprVgr_32m4;
  def int_riscv_vnmsub_vx_32m8 : VgrGprVgr_32m8;


  //masked functions

  class VmVgrVgrVgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VmVgrVgrVgr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class VmVgrVgrVgr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class VmVgrVgrVgr_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty,llvm_v128i8_ty,llvm_v128i8_ty,llvm_v128i8_ty],[IntrNoMem]>;

  class VmVgrVgrVgr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class VmVgrVgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class VmVgrVgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class VmVgrVgrVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_v64i16_ty,llvm_v64i16_ty],[IntrNoMem]>;

  class VmVgrVgrVgr_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_v4i32_ty,llvm_v4i32_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class VmVgrVgrVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_v8i32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class VmVgrVgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_v16i32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class VmVgrVgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_v32i32_ty,llvm_v32i32_ty],[IntrNoMem]>;

  class VmVgrGprVgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class VmVgrGprVgr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_i32_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class VmVgrGprVgr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_i32_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class VmVgrGprVgr_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty,llvm_v128i8_ty,llvm_i32_ty,llvm_v128i8_ty],[IntrNoMem]>;

  class VmVgrGprVgr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_i32_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class VmVgrGprVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_i32_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class VmVgrGprVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_i32_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class VmVgrGprVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_i32_ty,llvm_v64i16_ty],[IntrNoMem]>;

  class VmVgrGprVgr_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_v4i32_ty,llvm_i32_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class VmVgrGprVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_i32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class VmVgrGprVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_i32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class VmVgrGprVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_i32_ty,llvm_v32i32_ty],[IntrNoMem]>;


  def int_riscv_vmacc_vv_8m1_m : VmVgrVgrVgr_8m1;
  def int_riscv_vmacc_vv_8m2_m : VmVgrVgrVgr_8m2;
  def int_riscv_vmacc_vv_8m4_m : VmVgrVgrVgr_8m4;
  def int_riscv_vmacc_vv_8m8_m : VmVgrVgrVgr_8m8;

  def int_riscv_vnmsac_vv_8m1_m : VmVgrVgrVgr_8m1;
  def int_riscv_vnmsac_vv_8m2_m : VmVgrVgrVgr_8m2;
  def int_riscv_vnmsac_vv_8m4_m : VmVgrVgrVgr_8m4;
  def int_riscv_vnmsac_vv_8m8_m : VmVgrVgrVgr_8m8;

  def int_riscv_vmadd_vv_8m1_m : VmVgrVgrVgr_8m1;
  def int_riscv_vmadd_vv_8m2_m : VmVgrVgrVgr_8m2;
  def int_riscv_vmadd_vv_8m4_m : VmVgrVgrVgr_8m4;
  def int_riscv_vmadd_vv_8m8_m : VmVgrVgrVgr_8m8;

  def int_riscv_vnmsub_vv_8m1_m : VmVgrVgrVgr_8m1;
  def int_riscv_vnmsub_vv_8m2_m : VmVgrVgrVgr_8m2;
  def int_riscv_vnmsub_vv_8m4_m : VmVgrVgrVgr_8m4;
  def int_riscv_vnmsub_vv_8m8_m : VmVgrVgrVgr_8m8;


  def int_riscv_vmacc_vv_16m1_m : VmVgrVgrVgr_16m1;
  def int_riscv_vmacc_vv_16m2_m : VmVgrVgrVgr_16m2;
  def int_riscv_vmacc_vv_16m4_m : VmVgrVgrVgr_16m4;
  def int_riscv_vmacc_vv_16m8_m : VmVgrVgrVgr_16m8;

  def int_riscv_vnmsac_vv_16m1_m : VmVgrVgrVgr_16m1;
  def int_riscv_vnmsac_vv_16m2_m : VmVgrVgrVgr_16m2;
  def int_riscv_vnmsac_vv_16m4_m : VmVgrVgrVgr_16m4;
  def int_riscv_vnmsac_vv_16m8_m : VmVgrVgrVgr_16m8;

  def int_riscv_vmadd_vv_16m1_m : VmVgrVgrVgr_16m1;
  def int_riscv_vmadd_vv_16m2_m : VmVgrVgrVgr_16m2;
  def int_riscv_vmadd_vv_16m4_m : VmVgrVgrVgr_16m4;
  def int_riscv_vmadd_vv_16m8_m : VmVgrVgrVgr_16m8;

  def int_riscv_vnmsub_vv_16m1_m : VmVgrVgrVgr_16m1;
  def int_riscv_vnmsub_vv_16m2_m : VmVgrVgrVgr_16m2;
  def int_riscv_vnmsub_vv_16m4_m : VmVgrVgrVgr_16m4;
  def int_riscv_vnmsub_vv_16m8_m : VmVgrVgrVgr_16m8;


  def int_riscv_vmacc_vv_32m1_m : VmVgrVgrVgr_32m1;
  def int_riscv_vmacc_vv_32m2_m : VmVgrVgrVgr_32m2;
  def int_riscv_vmacc_vv_32m4_m : VmVgrVgrVgr_32m4;
  def int_riscv_vmacc_vv_32m8_m : VmVgrVgrVgr_32m8;

  def int_riscv_vnmsac_vv_32m1_m : VmVgrVgrVgr_32m1;
  def int_riscv_vnmsac_vv_32m2_m : VmVgrVgrVgr_32m2;
  def int_riscv_vnmsac_vv_32m4_m : VmVgrVgrVgr_32m4;
  def int_riscv_vnmsac_vv_32m8_m : VmVgrVgrVgr_32m8;

  def int_riscv_vmadd_vv_32m1_m : VmVgrVgrVgr_32m1;
  def int_riscv_vmadd_vv_32m2_m : VmVgrVgrVgr_32m2;
  def int_riscv_vmadd_vv_32m4_m : VmVgrVgrVgr_32m4;
  def int_riscv_vmadd_vv_32m8_m : VmVgrVgrVgr_32m8;

  def int_riscv_vnmsub_vv_32m1_m : VmVgrVgrVgr_32m1;
  def int_riscv_vnmsub_vv_32m2_m : VmVgrVgrVgr_32m2;
  def int_riscv_vnmsub_vv_32m4_m : VmVgrVgrVgr_32m4;
  def int_riscv_vnmsub_vv_32m8_m : VmVgrVgrVgr_32m8;


  def int_riscv_vmacc_vx_8m1_m : VmVgrGprVgr_8m1;
  def int_riscv_vmacc_vx_8m2_m : VmVgrGprVgr_8m2;
  def int_riscv_vmacc_vx_8m4_m : VmVgrGprVgr_8m4;
  def int_riscv_vmacc_vx_8m8_m : VmVgrGprVgr_8m8;
  
  def int_riscv_vnmsac_vx_8m1_m : VmVgrGprVgr_8m1;
  def int_riscv_vnmsac_vx_8m2_m : VmVgrGprVgr_8m2;
  def int_riscv_vnmsac_vx_8m4_m : VmVgrGprVgr_8m4;
  def int_riscv_vnmsac_vx_8m8_m : VmVgrGprVgr_8m8;

  def int_riscv_vmadd_vx_8m1_m : VmVgrGprVgr_8m1;
  def int_riscv_vmadd_vx_8m2_m : VmVgrGprVgr_8m2;
  def int_riscv_vmadd_vx_8m4_m : VmVgrGprVgr_8m4;
  def int_riscv_vmadd_vx_8m8_m : VmVgrGprVgr_8m8;

  def int_riscv_vnmsub_vx_8m1_m : VmVgrGprVgr_8m1;
  def int_riscv_vnmsub_vx_8m2_m : VmVgrGprVgr_8m2;
  def int_riscv_vnmsub_vx_8m4_m : VmVgrGprVgr_8m4;
  def int_riscv_vnmsub_vx_8m8_m : VmVgrGprVgr_8m8;


  def int_riscv_vmacc_vx_16m1_m : VmVgrGprVgr_16m1;
  def int_riscv_vmacc_vx_16m2_m : VmVgrGprVgr_16m2;
  def int_riscv_vmacc_vx_16m4_m : VmVgrGprVgr_16m4;
  def int_riscv_vmacc_vx_16m8_m : VmVgrGprVgr_16m8;

  def int_riscv_vnmsac_vx_16m1_m : VmVgrGprVgr_16m1;
  def int_riscv_vnmsac_vx_16m2_m : VmVgrGprVgr_16m2;
  def int_riscv_vnmsac_vx_16m4_m : VmVgrGprVgr_16m4;
  def int_riscv_vnmsac_vx_16m8_m : VmVgrGprVgr_16m8;

  def int_riscv_vmadd_vx_16m1_m : VmVgrGprVgr_16m1;
  def int_riscv_vmadd_vx_16m2_m : VmVgrGprVgr_16m2;
  def int_riscv_vmadd_vx_16m4_m : VmVgrGprVgr_16m4;
  def int_riscv_vmadd_vx_16m8_m : VmVgrGprVgr_16m8;

  def int_riscv_vnmsub_vx_16m1_m : VmVgrGprVgr_16m1;
  def int_riscv_vnmsub_vx_16m2_m : VmVgrGprVgr_16m2;
  def int_riscv_vnmsub_vx_16m4_m : VmVgrGprVgr_16m4;
  def int_riscv_vnmsub_vx_16m8_m : VmVgrGprVgr_16m8;


  def int_riscv_vmacc_vx_32m1_m : VmVgrGprVgr_32m1;
  def int_riscv_vmacc_vx_32m2_m : VmVgrGprVgr_32m2;
  def int_riscv_vmacc_vx_32m4_m : VmVgrGprVgr_32m4;
  def int_riscv_vmacc_vx_32m8_m : VmVgrGprVgr_32m8;

  def int_riscv_vnmsac_vx_32m1_m : VmVgrGprVgr_32m1;
  def int_riscv_vnmsac_vx_32m2_m : VmVgrGprVgr_32m2;
  def int_riscv_vnmsac_vx_32m4_m : VmVgrGprVgr_32m4;
  def int_riscv_vnmsac_vx_32m8_m : VmVgrGprVgr_32m8;

  def int_riscv_vmadd_vx_32m1_m : VmVgrGprVgr_32m1;
  def int_riscv_vmadd_vx_32m2_m : VmVgrGprVgr_32m2;
  def int_riscv_vmadd_vx_32m4_m : VmVgrGprVgr_32m4;
  def int_riscv_vmadd_vx_32m8_m : VmVgrGprVgr_32m8;

  def int_riscv_vnmsub_vx_32m1_m : VmVgrGprVgr_32m1;
  def int_riscv_vnmsub_vx_32m2_m : VmVgrGprVgr_32m2;
  def int_riscv_vnmsub_vx_32m4_m : VmVgrGprVgr_32m4;
  def int_riscv_vnmsub_vx_32m8_m : VmVgrGprVgr_32m8;


  //Vector Widening Integer Multiply-Add Functions

  class Widen_WidenVgrVgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Widen_WidenVgrVgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Widen_WidenVgrVgrVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;

  class Widen_WidenVgrVgrVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Widen_WidenVgrVgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Widen_WidenVgrVgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;

  class Widen_WidenVgrGprVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Widen_WidenVgrGprVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_i32_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Widen_WidenVgrGprVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_i32_ty,llvm_v64i8_ty],[IntrNoMem]>;

  class Widen_WidenVgrGprVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_i32_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Widen_WidenVgrGprVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_i32_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Widen_WidenVgrGprVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_i32_ty,llvm_v32i16_ty],[IntrNoMem]>;


  def int_riscv_vwmaccu_vv_16m2 : Widen_WidenVgrVgrVgr_16m2;
  def int_riscv_vwmaccu_vv_16m4 : Widen_WidenVgrVgrVgr_16m4;
  def int_riscv_vwmaccu_vv_16m8 : Widen_WidenVgrVgrVgr_16m8;

  def int_riscv_vwmacc_vv_16m2 : Widen_WidenVgrVgrVgr_16m2;
  def int_riscv_vwmacc_vv_16m4 : Widen_WidenVgrVgrVgr_16m4;
  def int_riscv_vwmacc_vv_16m8 : Widen_WidenVgrVgrVgr_16m8;

  def int_riscv_vwmaccsu_vv_16m2 : Widen_WidenVgrVgrVgr_16m2;
  def int_riscv_vwmaccsu_vv_16m4 : Widen_WidenVgrVgrVgr_16m4;
  def int_riscv_vwmaccsu_vv_16m8 : Widen_WidenVgrVgrVgr_16m8;


  def int_riscv_vwmaccu_vv_32m2 : Widen_WidenVgrVgrVgr_32m2;
  def int_riscv_vwmaccu_vv_32m4 : Widen_WidenVgrVgrVgr_32m4;
  def int_riscv_vwmaccu_vv_32m8 : Widen_WidenVgrVgrVgr_32m8;

  def int_riscv_vwmacc_vv_32m2 : Widen_WidenVgrVgrVgr_32m2;
  def int_riscv_vwmacc_vv_32m4 : Widen_WidenVgrVgrVgr_32m4;
  def int_riscv_vwmacc_vv_32m8 : Widen_WidenVgrVgrVgr_32m8;

  def int_riscv_vwmaccsu_vv_32m2 : Widen_WidenVgrVgrVgr_32m2;
  def int_riscv_vwmaccsu_vv_32m4 : Widen_WidenVgrVgrVgr_32m4;
  def int_riscv_vwmaccsu_vv_32m8 : Widen_WidenVgrVgrVgr_32m8;


  def int_riscv_vwmaccu_vx_16m2 : Widen_WidenVgrGprVgr_16m2;
  def int_riscv_vwmaccu_vx_16m4 : Widen_WidenVgrGprVgr_16m4;
  def int_riscv_vwmaccu_vx_16m8 : Widen_WidenVgrGprVgr_16m8;

  def int_riscv_vwmacc_vx_16m2 : Widen_WidenVgrGprVgr_16m2;
  def int_riscv_vwmacc_vx_16m4 : Widen_WidenVgrGprVgr_16m4;
  def int_riscv_vwmacc_vx_16m8 : Widen_WidenVgrGprVgr_16m8;

  def int_riscv_vwmaccsu_vx_16m2 : Widen_WidenVgrGprVgr_16m2;
  def int_riscv_vwmaccsu_vx_16m4 : Widen_WidenVgrGprVgr_16m4;
  def int_riscv_vwmaccsu_vx_16m8 : Widen_WidenVgrGprVgr_16m8;

  def int_riscv_vwmaccus_vx_16m2 : Widen_WidenVgrGprVgr_16m2;
  def int_riscv_vwmaccus_vx_16m4 : Widen_WidenVgrGprVgr_16m4;
  def int_riscv_vwmaccus_vx_16m8 : Widen_WidenVgrGprVgr_16m8;


  def int_riscv_vwmaccu_vx_32m2 : Widen_WidenVgrGprVgr_32m2;
  def int_riscv_vwmaccu_vx_32m4 : Widen_WidenVgrGprVgr_32m4;
  def int_riscv_vwmaccu_vx_32m8 : Widen_WidenVgrGprVgr_32m8;

  def int_riscv_vwmacc_vx_32m2 : Widen_WidenVgrGprVgr_32m2;
  def int_riscv_vwmacc_vx_32m4 : Widen_WidenVgrGprVgr_32m4;
  def int_riscv_vwmacc_vx_32m8 : Widen_WidenVgrGprVgr_32m8;

  def int_riscv_vwmaccsu_vx_32m2 : Widen_WidenVgrGprVgr_32m2;
  def int_riscv_vwmaccsu_vx_32m4 : Widen_WidenVgrGprVgr_32m4;
  def int_riscv_vwmaccsu_vx_32m8 : Widen_WidenVgrGprVgr_32m8;

  def int_riscv_vwmaccus_vx_32m2 : Widen_WidenVgrGprVgr_32m2;
  def int_riscv_vwmaccus_vx_32m4 : Widen_WidenVgrGprVgr_32m4;
  def int_riscv_vwmaccus_vx_32m8 : Widen_WidenVgrGprVgr_32m8;


  //masked functions

  class Widen_VmWidenVgrVgrVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Widen_VmWidenVgrVgrVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Widen_VmWidenVgrVgrVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;

  class Widen_VmWidenVgrVgrVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Widen_VmWidenVgrVgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Widen_VmWidenVgrVgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;

  class Widen_VmWidenVgrGprVgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Widen_VmWidenVgrGprVgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_i32_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Widen_VmWidenVgrGprVgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_i32_ty,llvm_v64i8_ty],[IntrNoMem]>;

  class Widen_VmWidenVgrGprVgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_i32_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Widen_VmWidenVgrGprVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_i32_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Widen_VmWidenVgrGprVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_i32_ty,llvm_v32i16_ty],[IntrNoMem]>;


  def int_riscv_vwmaccu_vv_16m2_m : Widen_VmWidenVgrVgrVgr_16m2;
  def int_riscv_vwmaccu_vv_16m4_m : Widen_VmWidenVgrVgrVgr_16m4;
  def int_riscv_vwmaccu_vv_16m8_m : Widen_VmWidenVgrVgrVgr_16m8;

  def int_riscv_vwmacc_vv_16m2_m : Widen_VmWidenVgrVgrVgr_16m2;
  def int_riscv_vwmacc_vv_16m4_m : Widen_VmWidenVgrVgrVgr_16m4;
  def int_riscv_vwmacc_vv_16m8_m : Widen_VmWidenVgrVgrVgr_16m8;

  def int_riscv_vwmaccsu_vv_16m2_m : Widen_VmWidenVgrVgrVgr_16m2;
  def int_riscv_vwmaccsu_vv_16m4_m : Widen_VmWidenVgrVgrVgr_16m4;
  def int_riscv_vwmaccsu_vv_16m8_m : Widen_VmWidenVgrVgrVgr_16m8;


  def int_riscv_vwmaccu_vv_32m2_m : Widen_VmWidenVgrVgrVgr_32m2;
  def int_riscv_vwmaccu_vv_32m4_m : Widen_VmWidenVgrVgrVgr_32m4;
  def int_riscv_vwmaccu_vv_32m8_m : Widen_VmWidenVgrVgrVgr_32m8;

  def int_riscv_vwmacc_vv_32m2_m : Widen_VmWidenVgrVgrVgr_32m2;
  def int_riscv_vwmacc_vv_32m4_m : Widen_VmWidenVgrVgrVgr_32m4;
  def int_riscv_vwmacc_vv_32m8_m : Widen_VmWidenVgrVgrVgr_32m8;

  def int_riscv_vwmaccsu_vv_32m2_m : Widen_VmWidenVgrVgrVgr_32m2;
  def int_riscv_vwmaccsu_vv_32m4_m : Widen_VmWidenVgrVgrVgr_32m4;
  def int_riscv_vwmaccsu_vv_32m8_m : Widen_VmWidenVgrVgrVgr_32m8;


  def int_riscv_vwmaccu_vx_16m2_m : Widen_VmWidenVgrGprVgr_16m2;
  def int_riscv_vwmaccu_vx_16m4_m : Widen_VmWidenVgrGprVgr_16m4;
  def int_riscv_vwmaccu_vx_16m8_m : Widen_VmWidenVgrGprVgr_16m8;

  def int_riscv_vwmacc_vx_16m2_m : Widen_VmWidenVgrGprVgr_16m2;
  def int_riscv_vwmacc_vx_16m4_m : Widen_VmWidenVgrGprVgr_16m4;
  def int_riscv_vwmacc_vx_16m8_m : Widen_VmWidenVgrGprVgr_16m8;

  def int_riscv_vwmaccsu_vx_16m2_m : Widen_VmWidenVgrGprVgr_16m2;
  def int_riscv_vwmaccsu_vx_16m4_m : Widen_VmWidenVgrGprVgr_16m4;
  def int_riscv_vwmaccsu_vx_16m8_m : Widen_VmWidenVgrGprVgr_16m8;

  def int_riscv_vwmaccus_vx_16m2_m : Widen_VmWidenVgrGprVgr_16m2;
  def int_riscv_vwmaccus_vx_16m4_m : Widen_VmWidenVgrGprVgr_16m4;
  def int_riscv_vwmaccus_vx_16m8_m : Widen_VmWidenVgrGprVgr_16m8;


  def int_riscv_vwmaccu_vx_32m2_m : Widen_VmWidenVgrGprVgr_32m2;
  def int_riscv_vwmaccu_vx_32m4_m : Widen_VmWidenVgrGprVgr_32m4;
  def int_riscv_vwmaccu_vx_32m8_m : Widen_VmWidenVgrGprVgr_32m8;

  def int_riscv_vwmacc_vx_32m2_m : Widen_VmWidenVgrGprVgr_32m2;
  def int_riscv_vwmacc_vx_32m4_m : Widen_VmWidenVgrGprVgr_32m4;
  def int_riscv_vwmacc_vx_32m8_m : Widen_VmWidenVgrGprVgr_32m8;

  def int_riscv_vwmaccsu_vx_32m2_m : Widen_VmWidenVgrGprVgr_32m2;
  def int_riscv_vwmaccsu_vx_32m4_m : Widen_VmWidenVgrGprVgr_32m4;
  def int_riscv_vwmaccsu_vx_32m8_m : Widen_VmWidenVgrGprVgr_32m8;

  def int_riscv_vwmaccus_vx_32m2_m : Widen_VmWidenVgrGprVgr_32m2;
  def int_riscv_vwmaccus_vx_32m4_m : Widen_VmWidenVgrGprVgr_32m4;
  def int_riscv_vwmaccus_vx_32m8_m : Widen_VmWidenVgrGprVgr_32m8;


  //Vector Quad-Widening Integer Multiply-Add Functions

  class QuadWiden_QuadWidenVgrVgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class QuadWiden_QuadWidenVgrVgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;

  class QuadWiden_QuadWidenVgrGprVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class QuadWiden_QuadWidenVgrGprVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_i32_ty,llvm_v32i8_ty],[IntrNoMem]>;


  def int_riscv_vqmaccu_vv_32m4 : QuadWiden_QuadWidenVgrVgrVgr_32m4;
  def int_riscv_vqmaccu_vv_32m8 : QuadWiden_QuadWidenVgrVgrVgr_32m8;

  def int_riscv_vqmacc_vv_32m4 : QuadWiden_QuadWidenVgrVgrVgr_32m4;
  def int_riscv_vqmacc_vv_32m8 : QuadWiden_QuadWidenVgrVgrVgr_32m8;

  def int_riscv_vqmaccsu_vv_32m4 : QuadWiden_QuadWidenVgrVgrVgr_32m4;
  def int_riscv_vqmaccsu_vv_32m8 : QuadWiden_QuadWidenVgrVgrVgr_32m8;


  def int_riscv_vqmaccu_vx_32m4 : QuadWiden_QuadWidenVgrGprVgr_32m4;
  def int_riscv_vqmaccu_vx_32m8 : QuadWiden_QuadWidenVgrGprVgr_32m8;

  def int_riscv_vqmacc_vx_32m4 : QuadWiden_QuadWidenVgrGprVgr_32m4;
  def int_riscv_vqmacc_vx_32m8 : QuadWiden_QuadWidenVgrGprVgr_32m8;

  def int_riscv_vqmaccsu_vx_32m4 : QuadWiden_QuadWidenVgrGprVgr_32m4;
  def int_riscv_vqmaccsu_vx_32m8 : QuadWiden_QuadWidenVgrGprVgr_32m8;

  def int_riscv_vqmaccus_vx_32m4 : QuadWiden_QuadWidenVgrGprVgr_32m4;
  def int_riscv_vqmaccus_vx_32m8 : QuadWiden_QuadWidenVgrGprVgr_32m8;


  //masked functions

  class QuadWiden_VmQuadWidenVgrVgrVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class QuadWiden_VmQuadWidenVgrVgrVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;

  class QuadWiden_VmQuadWidenVgrGprVgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class QuadWiden_VmQuadWidenVgrGprVgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_i32_ty,llvm_v32i8_ty],[IntrNoMem]>;


  def int_riscv_vqmaccu_vv_32m4_m : QuadWiden_VmQuadWidenVgrVgrVgr_32m4;
  def int_riscv_vqmaccu_vv_32m8_m : QuadWiden_VmQuadWidenVgrVgrVgr_32m8;

  def int_riscv_vqmacc_vv_32m4_m : QuadWiden_VmQuadWidenVgrVgrVgr_32m4;
  def int_riscv_vqmacc_vv_32m8_m : QuadWiden_VmQuadWidenVgrVgrVgr_32m8;

  def int_riscv_vqmaccsu_vv_32m4_m : QuadWiden_VmQuadWidenVgrVgrVgr_32m4;
  def int_riscv_vqmaccsu_vv_32m8_m : QuadWiden_VmQuadWidenVgrVgrVgr_32m8;


  def int_riscv_vqmaccu_vx_32m4_m : QuadWiden_VmQuadWidenVgrGprVgr_32m4;
  def int_riscv_vqmaccu_vx_32m8_m : QuadWiden_VmQuadWidenVgrGprVgr_32m8;

  def int_riscv_vqmacc_vx_32m4_m : QuadWiden_VmQuadWidenVgrGprVgr_32m4;
  def int_riscv_vqmacc_vx_32m8_m : QuadWiden_VmQuadWidenVgrGprVgr_32m8;

  def int_riscv_vqmaccsu_vx_32m4_m : QuadWiden_VmQuadWidenVgrGprVgr_32m4;
  def int_riscv_vqmaccsu_vx_32m8_m : QuadWiden_VmQuadWidenVgrGprVgr_32m8;

  def int_riscv_vqmaccus_vx_32m4_m : QuadWiden_VmQuadWidenVgrGprVgr_32m4;
  def int_riscv_vqmaccus_vx_32m8_m : QuadWiden_VmQuadWidenVgrGprVgr_32m8;


  //Vector Integer Merge Functions

  def int_riscv_vmerge_vvm_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vmerge_vvm_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vmerge_vvm_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vmerge_vvm_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vmerge_vvm_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vmerge_vvm_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vmerge_vvm_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vmerge_vvm_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vmerge_vvm_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vmerge_vvm_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vmerge_vvm_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vmerge_vvm_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vmerge_vxm_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vmerge_vxm_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vmerge_vxm_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vmerge_vxm_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vmerge_vim_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vmerge_vim_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vmerge_vim_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vmerge_vim_8m8_m : VmVgrGpr_8m8;


  def int_riscv_vmerge_vxm_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vmerge_vxm_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vmerge_vxm_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vmerge_vxm_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vmerge_vim_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vmerge_vim_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vmerge_vim_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vmerge_vim_16m8_m : VmVgrGpr_16m8;


  def int_riscv_vmerge_vxm_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vmerge_vxm_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vmerge_vxm_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vmerge_vxm_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vmerge_vim_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vmerge_vim_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vmerge_vim_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vmerge_vim_32m8_m : VmVgrGpr_32m8;


  //Vector Integer Move Functions

  class Vgr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty],[IntrNoMem]>;
  class Vgr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i8_ty],[IntrNoMem]>;
  class Vgr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i8_ty],[IntrNoMem]>;
  class Vgr_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v128i8_ty],[IntrNoMem]>;

  class Vgr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i16_ty],[IntrNoMem]>;
  class Vgr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty],[IntrNoMem]>;
  class Vgr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty],[IntrNoMem]>;
  class Vgr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty],[IntrNoMem]>;

  class Vgr_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4i32_ty],[IntrNoMem]>;
  class Vgr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty],[IntrNoMem]>;
  class Vgr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty],[IntrNoMem]>;
  class Vgr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty],[IntrNoMem]>;

  class Gpr_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_i32_ty],[IntrNoMem]>;
  class Gpr_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_i32_ty],[IntrNoMem]>;
  class Gpr_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_i32_ty],[IntrNoMem]>;
  class Gpr_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_i32_ty],[IntrNoMem]>;

  class Gpr_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_i32_ty],[IntrNoMem]>;
  class Gpr_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_i32_ty],[IntrNoMem]>;
  class Gpr_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_i32_ty],[IntrNoMem]>;
  class Gpr_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_i32_ty],[IntrNoMem]>;

  class Gpr_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_i32_ty],[IntrNoMem]>;
  class Gpr_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_i32_ty],[IntrNoMem]>;
  class Gpr_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_i32_ty],[IntrNoMem]>;
  class Gpr_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_i32_ty],[IntrNoMem]>;


  def int_riscv_vmv_v_v_8m1 : Vgr_8m1;
  def int_riscv_vmv_v_v_8m2 : Vgr_8m2;
  def int_riscv_vmv_v_v_8m4 : Vgr_8m4;
  def int_riscv_vmv_v_v_8m8 : Vgr_8m8;

  def int_riscv_vmv_v_v_16m1 : Vgr_16m1;
  def int_riscv_vmv_v_v_16m2 : Vgr_16m2;
  def int_riscv_vmv_v_v_16m4 : Vgr_16m4;
  def int_riscv_vmv_v_v_16m8 : Vgr_16m8;

  def int_riscv_vmv_v_v_32m1 : Vgr_32m1;
  def int_riscv_vmv_v_v_32m2 : Vgr_32m2;
  def int_riscv_vmv_v_v_32m4 : Vgr_32m4;
  def int_riscv_vmv_v_v_32m8 : Vgr_32m8;


  def int_riscv_vmv_v_x_8m1 : Gpr_8m1;
  def int_riscv_vmv_v_x_8m2 : Gpr_8m2;
  def int_riscv_vmv_v_x_8m4 : Gpr_8m4;
  def int_riscv_vmv_v_x_8m8 : Gpr_8m8;

  def int_riscv_vmv_v_i_8m1 : Gpr_8m1;
  def int_riscv_vmv_v_i_8m2 : Gpr_8m2;
  def int_riscv_vmv_v_i_8m4 : Gpr_8m4;
  def int_riscv_vmv_v_i_8m8 : Gpr_8m8;


  def int_riscv_vmv_v_x_16m1 : Gpr_16m1;
  def int_riscv_vmv_v_x_16m2 : Gpr_16m2;
  def int_riscv_vmv_v_x_16m4 : Gpr_16m4;
  def int_riscv_vmv_v_x_16m8 : Gpr_16m8;

  def int_riscv_vmv_v_i_16m1 : Gpr_16m1;
  def int_riscv_vmv_v_i_16m2 : Gpr_16m2;
  def int_riscv_vmv_v_i_16m4 : Gpr_16m4;
  def int_riscv_vmv_v_i_16m8 : Gpr_16m8;


  def int_riscv_vmv_v_x_32m1 : Gpr_32m1;
  def int_riscv_vmv_v_x_32m2 : Gpr_32m2;
  def int_riscv_vmv_v_x_32m4 : Gpr_32m4;
  def int_riscv_vmv_v_x_32m8 : Gpr_32m8;

  def int_riscv_vmv_v_i_32m1 : Gpr_32m1;
  def int_riscv_vmv_v_i_32m2 : Gpr_32m2;
  def int_riscv_vmv_v_i_32m4 : Gpr_32m4;
  def int_riscv_vmv_v_i_32m8 : Gpr_32m8;


  //Vector Single-Width Saturating Add and Subtract Functions

  def int_riscv_vsaddu_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vsaddu_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vsaddu_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vsaddu_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vsadd_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vsadd_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vsadd_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vsadd_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vssubu_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vssubu_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vssubu_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vssubu_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vssub_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vssub_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vssub_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vssub_vv_8m8 : VgrVgr_8m8;


  def int_riscv_vsaddu_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vsaddu_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vsaddu_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vsaddu_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vsadd_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vsadd_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vsadd_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vsadd_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vssubu_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vssubu_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vssubu_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vssubu_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vssub_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vssub_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vssub_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vssub_vv_16m8 : VgrVgr_16m8;


  def int_riscv_vsaddu_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vsaddu_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vsaddu_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vsaddu_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vsadd_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vsadd_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vsadd_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vsadd_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vssubu_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vssubu_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vssubu_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vssubu_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vssub_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vssub_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vssub_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vssub_vv_32m8 : VgrVgr_32m8;


  def int_riscv_vsaddu_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vsaddu_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vsaddu_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vsaddu_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vsaddu_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vsaddu_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vsaddu_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vsaddu_vi_8m8 : VgrGpr_8m8;

  def int_riscv_vsadd_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vsadd_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vsadd_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vsadd_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vsadd_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vsadd_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vsadd_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vsadd_vi_8m8 : VgrGpr_8m8;

  def int_riscv_vssubu_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vssubu_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vssubu_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vssubu_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vssubu_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vssubu_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vssubu_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vssubu_vi_8m8 : VgrGpr_8m8;

  def int_riscv_vssub_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vssub_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vssub_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vssub_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vssub_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vssub_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vssub_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vssub_vi_8m8 : VgrGpr_8m8;


  def int_riscv_vsaddu_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vsaddu_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vsaddu_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vsaddu_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vsaddu_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vsaddu_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vsaddu_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vsaddu_vi_16m8 : VgrGpr_16m8;

  def int_riscv_vsadd_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vsadd_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vsadd_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vsadd_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vsadd_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vsadd_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vsadd_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vsadd_vi_16m8 : VgrGpr_16m8;

  def int_riscv_vssubu_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vssubu_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vssubu_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vssubu_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vssubu_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vssubu_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vssubu_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vssubu_vi_16m8 : VgrGpr_16m8;

  def int_riscv_vssub_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vssub_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vssub_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vssub_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vssub_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vssub_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vssub_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vssub_vi_16m8 : VgrGpr_16m8;


  def int_riscv_vsaddu_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vsaddu_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vsaddu_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vsaddu_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vsaddu_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vsaddu_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vsaddu_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vsaddu_vi_32m8 : VgrGpr_32m8;

  def int_riscv_vsadd_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vsadd_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vsadd_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vsadd_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vsadd_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vsadd_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vsadd_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vsadd_vi_32m8 : VgrGpr_32m8;

  def int_riscv_vssubu_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vssubu_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vssubu_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vssubu_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vssubu_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vssubu_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vssubu_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vssubu_vi_32m8 : VgrGpr_32m8;

  def int_riscv_vssub_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vssub_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vssub_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vssub_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vssub_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vssub_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vssub_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vssub_vi_32m8 : VgrGpr_32m8;


  //masked functions

  def int_riscv_vsaddu_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vsaddu_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vsaddu_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vsaddu_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vsadd_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vsadd_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vsadd_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vsadd_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vssubu_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vssubu_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vssubu_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vssubu_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vssub_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vssub_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vssub_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vssub_vv_8m8_m : VmVgrVgr_8m8;


  def int_riscv_vsaddu_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vsaddu_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vsaddu_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vsaddu_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vsadd_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vsadd_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vsadd_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vsadd_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vssubu_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vssubu_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vssubu_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vssubu_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vssub_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vssub_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vssub_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vssub_vv_16m8_m : VmVgrVgr_16m8;


  def int_riscv_vsaddu_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vsaddu_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vsaddu_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vsaddu_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vsadd_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vsadd_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vsadd_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vsadd_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vssubu_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vssubu_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vssubu_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vssubu_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vssub_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vssub_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vssub_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vssub_vv_32m8_m : VmVgrVgr_32m8;


  def int_riscv_vsaddu_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsaddu_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsaddu_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsaddu_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vsaddu_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsaddu_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsaddu_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsaddu_vi_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vsadd_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsadd_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsadd_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsadd_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vsadd_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsadd_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsadd_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsadd_vi_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vssubu_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vssubu_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vssubu_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vssubu_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vssubu_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vssubu_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vssubu_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vssubu_vi_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vssub_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vssub_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vssub_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vssub_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vssub_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vssub_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vssub_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vssub_vi_8m8_m : VmVgrGpr_8m8;


  def int_riscv_vsaddu_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsaddu_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsaddu_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsaddu_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vsaddu_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsaddu_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsaddu_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsaddu_vi_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vsadd_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsadd_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsadd_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsadd_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vsadd_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsadd_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsadd_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsadd_vi_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vssubu_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vssubu_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vssubu_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vssubu_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vssubu_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vssubu_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vssubu_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vssubu_vi_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vssub_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vssub_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vssub_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vssub_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vssub_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vssub_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vssub_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vssub_vi_16m8_m : VmVgrGpr_16m8;


  def int_riscv_vsaddu_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsaddu_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsaddu_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsaddu_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vsaddu_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsaddu_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsaddu_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsaddu_vi_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vsadd_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsadd_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsadd_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsadd_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vsadd_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsadd_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsadd_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsadd_vi_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vssubu_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vssubu_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vssubu_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vssubu_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vssubu_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vssubu_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vssubu_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vssubu_vi_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vssub_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vssub_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vssub_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vssub_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vssub_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vssub_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vssub_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vssub_vi_32m8_m : VmVgrGpr_32m8;


  //Vector Single-Width Averaging Add and Subtract Functions

  def int_riscv_vaaddu_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vaaddu_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vaaddu_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vaaddu_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vaadd_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vaadd_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vaadd_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vaadd_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vasubu_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vasubu_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vasubu_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vasubu_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vasub_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vasub_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vasub_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vasub_vv_8m8 : VgrVgr_8m8;


  def int_riscv_vaaddu_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vaaddu_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vaaddu_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vaaddu_vv_16m8 : VgrVgr_16m8;  

  def int_riscv_vaadd_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vaadd_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vaadd_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vaadd_vv_16m8 : VgrVgr_16m8;  

  def int_riscv_vasubu_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vasubu_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vasubu_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vasubu_vv_16m8 : VgrVgr_16m8;  

  def int_riscv_vasub_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vasub_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vasub_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vasub_vv_16m8 : VgrVgr_16m8;


  def int_riscv_vaaddu_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vaaddu_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vaaddu_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vaaddu_vv_32m8 : VgrVgr_32m8; 

  def int_riscv_vaadd_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vaadd_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vaadd_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vaadd_vv_32m8 : VgrVgr_32m8; 

  def int_riscv_vasubu_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vasubu_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vasubu_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vasubu_vv_32m8 : VgrVgr_32m8; 

  def int_riscv_vasub_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vasub_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vasub_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vasub_vv_32m8 : VgrVgr_32m8; 


  def int_riscv_vaaddu_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vaaddu_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vaaddu_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vaaddu_vx_8m8 : VgrGpr_8m8;  

  def int_riscv_vaadd_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vaadd_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vaadd_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vaadd_vx_8m8 : VgrGpr_8m8;  

  def int_riscv_vasubu_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vasubu_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vasubu_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vasubu_vx_8m8 : VgrGpr_8m8;  

  def int_riscv_vasub_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vasub_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vasub_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vasub_vx_8m8 : VgrGpr_8m8; 


  def int_riscv_vaaddu_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vaaddu_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vaaddu_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vaaddu_vx_16m8 : VgrGpr_16m8;  

  def int_riscv_vaadd_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vaadd_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vaadd_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vaadd_vx_16m8 : VgrGpr_16m8; 

  def int_riscv_vasubu_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vasubu_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vasubu_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vasubu_vx_16m8 : VgrGpr_16m8;  

  def int_riscv_vasub_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vasub_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vasub_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vasub_vx_16m8 : VgrGpr_16m8;


  def int_riscv_vaaddu_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vaaddu_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vaaddu_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vaaddu_vx_32m8 : VgrGpr_32m8; 

  def int_riscv_vaadd_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vaadd_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vaadd_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vaadd_vx_32m8 : VgrGpr_32m8; 

  def int_riscv_vasubu_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vasubu_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vasubu_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vasubu_vx_32m8 : VgrGpr_32m8; 

  def int_riscv_vasub_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vasub_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vasub_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vasub_vx_32m8 : VgrGpr_32m8;


  //masked functions

  def int_riscv_vaaddu_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vaaddu_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vaaddu_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vaaddu_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vaadd_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vaadd_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vaadd_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vaadd_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vasubu_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vasubu_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vasubu_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vasubu_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vasub_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vasub_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vasub_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vasub_vv_8m8_m : VmVgrVgr_8m8;


  def int_riscv_vaaddu_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vaaddu_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vaaddu_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vaaddu_vv_16m8_m : VmVgrVgr_16m8;  

  def int_riscv_vaadd_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vaadd_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vaadd_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vaadd_vv_16m8_m : VmVgrVgr_16m8;  

  def int_riscv_vasubu_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vasubu_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vasubu_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vasubu_vv_16m8_m : VmVgrVgr_16m8;  

  def int_riscv_vasub_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vasub_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vasub_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vasub_vv_16m8_m : VmVgrVgr_16m8;


  def int_riscv_vaaddu_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vaaddu_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vaaddu_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vaaddu_vv_32m8_m : VmVgrVgr_32m8; 

  def int_riscv_vaadd_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vaadd_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vaadd_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vaadd_vv_32m8_m : VmVgrVgr_32m8; 

  def int_riscv_vasubu_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vasubu_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vasubu_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vasubu_vv_32m8_m : VmVgrVgr_32m8; 

  def int_riscv_vasub_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vasub_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vasub_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vasub_vv_32m8_m : VmVgrVgr_32m8; 


  def int_riscv_vaaddu_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vaaddu_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vaaddu_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vaaddu_vx_8m8_m : VmVgrGpr_8m8;  

  def int_riscv_vaadd_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vaadd_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vaadd_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vaadd_vx_8m8_m : VmVgrGpr_8m8;  

  def int_riscv_vasubu_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vasubu_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vasubu_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vasubu_vx_8m8_m : VmVgrGpr_8m8;  

  def int_riscv_vasub_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vasub_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vasub_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vasub_vx_8m8_m : VmVgrGpr_8m8; 


  def int_riscv_vaaddu_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vaaddu_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vaaddu_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vaaddu_vx_16m8_m : VmVgrGpr_16m8;  

  def int_riscv_vaadd_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vaadd_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vaadd_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vaadd_vx_16m8_m : VmVgrGpr_16m8; 

  def int_riscv_vasubu_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vasubu_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vasubu_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vasubu_vx_16m8_m : VmVgrGpr_16m8;  

  def int_riscv_vasub_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vasub_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vasub_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vasub_vx_16m8_m : VmVgrGpr_16m8;


  def int_riscv_vaaddu_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vaaddu_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vaaddu_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vaaddu_vx_32m8_m : VmVgrGpr_32m8; 

  def int_riscv_vaadd_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vaadd_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vaadd_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vaadd_vx_32m8_m : VmVgrGpr_32m8; 

  def int_riscv_vasubu_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vasubu_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vasubu_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vasubu_vx_32m8_m : VmVgrGpr_32m8; 

  def int_riscv_vasub_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vasub_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vasub_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vasub_vx_32m8_m : VmVgrGpr_32m8;  


  //Vector Single-Width Fractional Multiply with Rounding and Saturation Functions

  def int_riscv_vsmul_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vsmul_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vsmul_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vsmul_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vsmul_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vsmul_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vsmul_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vsmul_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vsmul_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vsmul_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vsmul_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vsmul_vv_32m8 : VgrVgr_32m8;


  def int_riscv_vsmul_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vsmul_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vsmul_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vsmul_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vsmul_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vsmul_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vsmul_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vsmul_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vsmul_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vsmul_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vsmul_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vsmul_vx_32m8 : VgrGpr_32m8;


  //masked functions

  def int_riscv_vsmul_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vsmul_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vsmul_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vsmul_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vsmul_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vsmul_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vsmul_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vsmul_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vsmul_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vsmul_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vsmul_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vsmul_vv_32m8_m : VmVgrVgr_32m8;


  def int_riscv_vsmul_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vsmul_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vsmul_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vsmul_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vsmul_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vsmul_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vsmul_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vsmul_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vsmul_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vsmul_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vsmul_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vsmul_vx_32m8_m : VmVgrGpr_32m8;


  //Vector Single-Width Scaling Shift Functions

  def int_riscv_vssrl_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vssrl_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vssrl_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vssrl_vv_8m8 : VgrVgr_8m8;

  def int_riscv_vssra_vv_8m1 : VgrVgr_8m1;
  def int_riscv_vssra_vv_8m2 : VgrVgr_8m2;
  def int_riscv_vssra_vv_8m4 : VgrVgr_8m4;
  def int_riscv_vssra_vv_8m8 : VgrVgr_8m8;


  def int_riscv_vssrl_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vssrl_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vssrl_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vssrl_vv_16m8 : VgrVgr_16m8;

  def int_riscv_vssra_vv_16m1 : VgrVgr_16m1;
  def int_riscv_vssra_vv_16m2 : VgrVgr_16m2;
  def int_riscv_vssra_vv_16m4 : VgrVgr_16m4;
  def int_riscv_vssra_vv_16m8 : VgrVgr_16m8;


  def int_riscv_vssrl_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vssrl_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vssrl_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vssrl_vv_32m8 : VgrVgr_32m8;

  def int_riscv_vssra_vv_32m1 : VgrVgr_32m1;
  def int_riscv_vssra_vv_32m2 : VgrVgr_32m2;
  def int_riscv_vssra_vv_32m4 : VgrVgr_32m4;
  def int_riscv_vssra_vv_32m8 : VgrVgr_32m8;


  def int_riscv_vssrl_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vssrl_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vssrl_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vssrl_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vssrl_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vssrl_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vssrl_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vssrl_vi_8m8 : VgrGpr_8m8;

  def int_riscv_vssra_vx_8m1 : VgrGpr_8m1;
  def int_riscv_vssra_vx_8m2 : VgrGpr_8m2;
  def int_riscv_vssra_vx_8m4 : VgrGpr_8m4;
  def int_riscv_vssra_vx_8m8 : VgrGpr_8m8;

  def int_riscv_vssra_vi_8m1 : VgrGpr_8m1;
  def int_riscv_vssra_vi_8m2 : VgrGpr_8m2;
  def int_riscv_vssra_vi_8m4 : VgrGpr_8m4;
  def int_riscv_vssra_vi_8m8 : VgrGpr_8m8;


  def int_riscv_vssrl_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vssrl_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vssrl_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vssrl_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vssrl_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vssrl_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vssrl_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vssrl_vi_16m8 : VgrGpr_16m8;

  def int_riscv_vssra_vx_16m1 : VgrGpr_16m1;
  def int_riscv_vssra_vx_16m2 : VgrGpr_16m2;
  def int_riscv_vssra_vx_16m4 : VgrGpr_16m4;
  def int_riscv_vssra_vx_16m8 : VgrGpr_16m8;

  def int_riscv_vssra_vi_16m1 : VgrGpr_16m1;
  def int_riscv_vssra_vi_16m2 : VgrGpr_16m2;
  def int_riscv_vssra_vi_16m4 : VgrGpr_16m4;
  def int_riscv_vssra_vi_16m8 : VgrGpr_16m8;


  def int_riscv_vssrl_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vssrl_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vssrl_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vssrl_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vssrl_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vssrl_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vssrl_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vssrl_vi_32m8 : VgrGpr_32m8;

  def int_riscv_vssra_vx_32m1 : VgrGpr_32m1;
  def int_riscv_vssra_vx_32m2 : VgrGpr_32m2;
  def int_riscv_vssra_vx_32m4 : VgrGpr_32m4;
  def int_riscv_vssra_vx_32m8 : VgrGpr_32m8;

  def int_riscv_vssra_vi_32m1 : VgrGpr_32m1;
  def int_riscv_vssra_vi_32m2 : VgrGpr_32m2;
  def int_riscv_vssra_vi_32m4 : VgrGpr_32m4;
  def int_riscv_vssra_vi_32m8 : VgrGpr_32m8;


  //masked functions

  def int_riscv_vssrl_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vssrl_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vssrl_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vssrl_vv_8m8_m : VmVgrVgr_8m8;

  def int_riscv_vssra_vv_8m1_m : VmVgrVgr_8m1;
  def int_riscv_vssra_vv_8m2_m : VmVgrVgr_8m2;
  def int_riscv_vssra_vv_8m4_m : VmVgrVgr_8m4;
  def int_riscv_vssra_vv_8m8_m : VmVgrVgr_8m8;


  def int_riscv_vssrl_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vssrl_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vssrl_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vssrl_vv_16m8_m : VmVgrVgr_16m8;

  def int_riscv_vssra_vv_16m1_m : VmVgrVgr_16m1;
  def int_riscv_vssra_vv_16m2_m : VmVgrVgr_16m2;
  def int_riscv_vssra_vv_16m4_m : VmVgrVgr_16m4;
  def int_riscv_vssra_vv_16m8_m : VmVgrVgr_16m8;


  def int_riscv_vssrl_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vssrl_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vssrl_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vssrl_vv_32m8_m : VmVgrVgr_32m8;

  def int_riscv_vssra_vv_32m1_m : VmVgrVgr_32m1;
  def int_riscv_vssra_vv_32m2_m : VmVgrVgr_32m2;
  def int_riscv_vssra_vv_32m4_m : VmVgrVgr_32m4;
  def int_riscv_vssra_vv_32m8_m : VmVgrVgr_32m8;


  def int_riscv_vssrl_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vssrl_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vssrl_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vssrl_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vssrl_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vssrl_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vssrl_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vssrl_vi_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vssra_vx_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vssra_vx_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vssra_vx_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vssra_vx_8m8_m : VmVgrGpr_8m8;

  def int_riscv_vssra_vi_8m1_m : VmVgrGpr_8m1;
  def int_riscv_vssra_vi_8m2_m : VmVgrGpr_8m2;
  def int_riscv_vssra_vi_8m4_m : VmVgrGpr_8m4;
  def int_riscv_vssra_vi_8m8_m : VmVgrGpr_8m8;


  def int_riscv_vssrl_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vssrl_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vssrl_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vssrl_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vssrl_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vssrl_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vssrl_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vssrl_vi_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vssra_vx_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vssra_vx_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vssra_vx_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vssra_vx_16m8_m : VmVgrGpr_16m8;

  def int_riscv_vssra_vi_16m1_m : VmVgrGpr_16m1;
  def int_riscv_vssra_vi_16m2_m : VmVgrGpr_16m2;
  def int_riscv_vssra_vi_16m4_m : VmVgrGpr_16m4;
  def int_riscv_vssra_vi_16m8_m : VmVgrGpr_16m8;


  def int_riscv_vssrl_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vssrl_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vssrl_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vssrl_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vssrl_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vssrl_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vssrl_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vssrl_vi_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vssra_vx_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vssra_vx_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vssra_vx_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vssra_vx_32m8_m : VmVgrGpr_32m8;

  def int_riscv_vssra_vi_32m1_m : VmVgrGpr_32m1;
  def int_riscv_vssra_vi_32m2_m : VmVgrGpr_32m2;
  def int_riscv_vssra_vi_32m4_m : VmVgrGpr_32m4;
  def int_riscv_vssra_vi_32m8_m : VmVgrGpr_32m8;


  //Vector Narrowing Fixed-Point Clip Functions

  def int_riscv_vnclipu_wv_8m1 : NarrowVgrVgr_8m1;
  def int_riscv_vnclipu_wv_8m2 : NarrowVgrVgr_8m2;
  def int_riscv_vnclipu_wv_8m4 : NarrowVgrVgr_8m4;

  def int_riscv_vnclip_wv_8m1 : NarrowVgrVgr_8m1;
  def int_riscv_vnclip_wv_8m2 : NarrowVgrVgr_8m2;
  def int_riscv_vnclip_wv_8m4 : NarrowVgrVgr_8m4;


  def int_riscv_vnclipu_wv_16m1 : NarrowVgrVgr_16m1;
  def int_riscv_vnclipu_wv_16m2 : NarrowVgrVgr_16m2;
  def int_riscv_vnclipu_wv_16m4 : NarrowVgrVgr_16m4;

  def int_riscv_vnclip_wv_16m1 : NarrowVgrVgr_16m1;
  def int_riscv_vnclip_wv_16m2 : NarrowVgrVgr_16m2;
  def int_riscv_vnclip_wv_16m4 : NarrowVgrVgr_16m4;


  def int_riscv_vnclipu_wx_8m1 : NarrowVgrGpr_8m1;
  def int_riscv_vnclipu_wx_8m2 : NarrowVgrGpr_8m2;
  def int_riscv_vnclipu_wx_8m4 : NarrowVgrGpr_8m4;

  def int_riscv_vnclipu_wi_8m1 : NarrowVgrGpr_8m1;
  def int_riscv_vnclipu_wi_8m2 : NarrowVgrGpr_8m2;
  def int_riscv_vnclipu_wi_8m4 : NarrowVgrGpr_8m4;

  def int_riscv_vnclip_wx_8m1 : NarrowVgrGpr_8m1;
  def int_riscv_vnclip_wx_8m2 : NarrowVgrGpr_8m2;
  def int_riscv_vnclip_wx_8m4 : NarrowVgrGpr_8m4;

  def int_riscv_vnclip_wi_8m1 : NarrowVgrGpr_8m1;
  def int_riscv_vnclip_wi_8m2 : NarrowVgrGpr_8m2;
  def int_riscv_vnclip_wi_8m4 : NarrowVgrGpr_8m4;


  def int_riscv_vnclipu_wx_16m1 : NarrowVgrGpr_16m1;
  def int_riscv_vnclipu_wx_16m2 : NarrowVgrGpr_16m2;
  def int_riscv_vnclipu_wx_16m4 : NarrowVgrGpr_16m4;

  def int_riscv_vnclipu_wi_16m1 : NarrowVgrGpr_16m1;
  def int_riscv_vnclipu_wi_16m2 : NarrowVgrGpr_16m2;
  def int_riscv_vnclipu_wi_16m4 : NarrowVgrGpr_16m4;

  def int_riscv_vnclip_wx_16m1 : NarrowVgrGpr_16m1;
  def int_riscv_vnclip_wx_16m2 : NarrowVgrGpr_16m2;
  def int_riscv_vnclip_wx_16m4 : NarrowVgrGpr_16m4;

  def int_riscv_vnclip_wi_16m1 : NarrowVgrGpr_16m1;
  def int_riscv_vnclip_wi_16m2 : NarrowVgrGpr_16m2;
  def int_riscv_vnclip_wi_16m4 : NarrowVgrGpr_16m4;


  //masked functions

  def int_riscv_vnclipu_wv_8m1_m : VmNarrowVgrVgr_8m1;
  def int_riscv_vnclipu_wv_8m2_m : VmNarrowVgrVgr_8m2;
  def int_riscv_vnclipu_wv_8m4_m : VmNarrowVgrVgr_8m4;

  def int_riscv_vnclip_wv_8m1_m : VmNarrowVgrVgr_8m1;
  def int_riscv_vnclip_wv_8m2_m : VmNarrowVgrVgr_8m2;
  def int_riscv_vnclip_wv_8m4_m : VmNarrowVgrVgr_8m4;


  def int_riscv_vnclipu_wv_16m1_m : VmNarrowVgrVgr_16m1;
  def int_riscv_vnclipu_wv_16m2_m : VmNarrowVgrVgr_16m2;
  def int_riscv_vnclipu_wv_16m4_m : VmNarrowVgrVgr_16m4;

  def int_riscv_vnclip_wv_16m1_m : VmNarrowVgrVgr_16m1;
  def int_riscv_vnclip_wv_16m2_m : VmNarrowVgrVgr_16m2;
  def int_riscv_vnclip_wv_16m4_m : VmNarrowVgrVgr_16m4;


  def int_riscv_vnclipu_wx_8m1_m : VmNarrowVgrGpr_8m1;
  def int_riscv_vnclipu_wx_8m2_m : VmNarrowVgrGpr_8m2;
  def int_riscv_vnclipu_wx_8m4_m : VmNarrowVgrGpr_8m4;

  def int_riscv_vnclipu_wi_8m1_m : VmNarrowVgrGpr_8m1;
  def int_riscv_vnclipu_wi_8m2_m : VmNarrowVgrGpr_8m2;
  def int_riscv_vnclipu_wi_8m4_m : VmNarrowVgrGpr_8m4;

  def int_riscv_vnclip_wx_8m1_m : VmNarrowVgrGpr_8m1;
  def int_riscv_vnclip_wx_8m2_m : VmNarrowVgrGpr_8m2;
  def int_riscv_vnclip_wx_8m4_m : VmNarrowVgrGpr_8m4;

  def int_riscv_vnclip_wi_8m1_m : VmNarrowVgrGpr_8m1;
  def int_riscv_vnclip_wi_8m2_m : VmNarrowVgrGpr_8m2;
  def int_riscv_vnclip_wi_8m4_m : VmNarrowVgrGpr_8m4;


  def int_riscv_vnclipu_wx_16m1_m : VmNarrowVgrGpr_16m1;
  def int_riscv_vnclipu_wx_16m2_m : VmNarrowVgrGpr_16m2;
  def int_riscv_vnclipu_wx_16m4_m : VmNarrowVgrGpr_16m4;

  def int_riscv_vnclipu_wi_16m1_m : VmNarrowVgrGpr_16m1;
  def int_riscv_vnclipu_wi_16m2_m : VmNarrowVgrGpr_16m2;
  def int_riscv_vnclipu_wi_16m4_m : VmNarrowVgrGpr_16m4;

  def int_riscv_vnclip_wx_16m1_m : VmNarrowVgrGpr_16m1;
  def int_riscv_vnclip_wx_16m2_m : VmNarrowVgrGpr_16m2;
  def int_riscv_vnclip_wx_16m4_m : VmNarrowVgrGpr_16m4;

  def int_riscv_vnclip_wi_16m1_m : VmNarrowVgrGpr_16m1;
  def int_riscv_vnclip_wi_16m2_m : VmNarrowVgrGpr_16m2;
  def int_riscv_vnclip_wi_16m4_m : VmNarrowVgrGpr_16m4;


  //Vector Unit-Stride Load Functions
  class Vload_1VectorArg_v8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vle_v_8m1 : Vload_1VectorArg_v8m1;
  def int_riscv_vle_v_8m2 : Vload_1VectorArg_v8m2;
  def int_riscv_vle_v_8m4 : Vload_1VectorArg_v8m4;
  def int_riscv_vle_v_8m8 : Vload_1VectorArg_v8m8;

  class Vload_1VectorArg_v16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vle_v_16m1 : Vload_1VectorArg_v16m1;
  def int_riscv_vle_v_16m2 : Vload_1VectorArg_v16m2;
  def int_riscv_vle_v_16m4 : Vload_1VectorArg_v16m4;
  def int_riscv_vle_v_16m8 : Vload_1VectorArg_v16m8;

  class Vload_1VectorArg_v32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vle_v_32m1 : Vload_1VectorArg_v32m1;
  def int_riscv_vle_v_32m2 : Vload_1VectorArg_v32m2;
  def int_riscv_vle_v_32m4 : Vload_1VectorArg_v32m4;
  def int_riscv_vle_v_32m8 : Vload_1VectorArg_v32m8;

  class Vload_1VectorArg_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vle_v_f32m1 : Vload_1VectorArg_f32m1;
  def int_riscv_vle_v_f32m2 : Vload_1VectorArg_f32m2;
  def int_riscv_vle_v_f32m4 : Vload_1VectorArg_f32m4;
  def int_riscv_vle_v_f32m8 : Vload_1VectorArg_f32m8;

  //masked functions
  class Vload_1VectorArg_v8m1_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v8m2_m : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v8m4_m : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v8m8_m : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vle_v_8m1_m : Vload_1VectorArg_v8m1_m;
  def int_riscv_vle_v_8m2_m : Vload_1VectorArg_v8m2_m;
  def int_riscv_vle_v_8m4_m : Vload_1VectorArg_v8m4_m;
  def int_riscv_vle_v_8m8_m : Vload_1VectorArg_v8m8_m;

  class Vload_1VectorArg_v16m1_m : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v16m2_m : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v16m4_m : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v16m8_m : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vle_v_16m1_m : Vload_1VectorArg_v16m1_m;
  def int_riscv_vle_v_16m2_m : Vload_1VectorArg_v16m2_m;
  def int_riscv_vle_v_16m4_m : Vload_1VectorArg_v16m4_m;
  def int_riscv_vle_v_16m8_m : Vload_1VectorArg_v16m8_m;

  class Vload_1VectorArg_v32m1_m : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v32m2_m : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v32m4_m : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_v32m8_m : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vle_v_32m1_m : Vload_1VectorArg_v32m1_m;
  def int_riscv_vle_v_32m2_m : Vload_1VectorArg_v32m2_m;
  def int_riscv_vle_v_32m4_m : Vload_1VectorArg_v32m4_m;
  def int_riscv_vle_v_32m8_m : Vload_1VectorArg_v32m8_m;

  class Vload_1VectorArg_f32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_f32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_f32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_f32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_ptr_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vle_v_f32m1_m : Vload_1VectorArg_f32m1_m;
  def int_riscv_vle_v_f32m2_m : Vload_1VectorArg_f32m2_m;
  def int_riscv_vle_v_f32m4_m : Vload_1VectorArg_f32m4_m;
  def int_riscv_vle_v_f32m8_m : Vload_1VectorArg_f32m8_m;

  //Vector Unit-Stride Store Functions
  class Vstore_1VectorArg_v8m1 : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v8m2 : Intrinsic<[],[llvm_v32i8_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v8m4 : Intrinsic<[],[llvm_v64i8_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v8m8 : Intrinsic<[],[llvm_v128i8_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vse_v_8m1 : Vstore_1VectorArg_v8m1;
  def int_riscv_vse_v_8m2 : Vstore_1VectorArg_v8m2;
  def int_riscv_vse_v_8m4 : Vstore_1VectorArg_v8m4;
  def int_riscv_vse_v_8m8 : Vstore_1VectorArg_v8m8;

  class Vstore_1VectorArg_v16m1 : Intrinsic<[],[llvm_v8i16_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v16m2 : Intrinsic<[],[llvm_v16i16_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v16m4 : Intrinsic<[],[llvm_v32i16_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v16m8 : Intrinsic<[],[llvm_v64i16_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vse_v_16m1 : Vstore_1VectorArg_v16m1;
  def int_riscv_vse_v_16m2 : Vstore_1VectorArg_v16m2;
  def int_riscv_vse_v_16m4 : Vstore_1VectorArg_v16m4;
  def int_riscv_vse_v_16m8 : Vstore_1VectorArg_v16m8;

  class Vstore_1VectorArg_v32m1 : Intrinsic<[],[llvm_v4i32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v32m2 : Intrinsic<[],[llvm_v8i32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v32m4 : Intrinsic<[],[llvm_v16i32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v32m8 : Intrinsic<[],[llvm_v32i32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vse_v_32m1 : Vstore_1VectorArg_v32m1;
  def int_riscv_vse_v_32m2 : Vstore_1VectorArg_v32m2;
  def int_riscv_vse_v_32m4 : Vstore_1VectorArg_v32m4;
  def int_riscv_vse_v_32m8 : Vstore_1VectorArg_v32m8;

  class Vstore_1VectorArg_f32m1 : Intrinsic<[],[llvm_v4f32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_f32m2 : Intrinsic<[],[llvm_v8f32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_f32m4 : Intrinsic<[],[llvm_v16f32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_f32m8 : Intrinsic<[],[llvm_v32f32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vse_v_f32m1 : Vstore_1VectorArg_f32m1;
  def int_riscv_vse_v_f32m2 : Vstore_1VectorArg_f32m2;
  def int_riscv_vse_v_f32m4 : Vstore_1VectorArg_f32m4;
  def int_riscv_vse_v_f32m8 : Vstore_1VectorArg_f32m8;

  //masked functions
  class Vstore_1VectorArg_v8m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v8m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v8m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v8m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v128i8_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vse_v_8m1_m : Vstore_1VectorArg_v8m1_m;
  def int_riscv_vse_v_8m2_m : Vstore_1VectorArg_v8m2_m;
  def int_riscv_vse_v_8m4_m : Vstore_1VectorArg_v8m4_m;
  def int_riscv_vse_v_8m8_m : Vstore_1VectorArg_v8m8_m;

  class Vstore_1VectorArg_v16m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v16m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v16m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v16m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vse_v_16m1_m : Vstore_1VectorArg_v16m1_m;
  def int_riscv_vse_v_16m2_m : Vstore_1VectorArg_v16m2_m;
  def int_riscv_vse_v_16m4_m : Vstore_1VectorArg_v16m4_m;
  def int_riscv_vse_v_16m8_m : Vstore_1VectorArg_v16m8_m;

  class Vstore_1VectorArg_v32m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v4i32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v32m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v32m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_v32m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vse_v_32m1_m : Vstore_1VectorArg_v32m1_m;
  def int_riscv_vse_v_32m2_m : Vstore_1VectorArg_v32m2_m;
  def int_riscv_vse_v_32m4_m : Vstore_1VectorArg_v32m4_m;
  def int_riscv_vse_v_32m8_m : Vstore_1VectorArg_v32m8_m;

  class Vstore_1VectorArg_f32m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v4f32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_f32m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v8f32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_f32m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v16f32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_f32m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_v32f32_ty,llvm_ptr_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vse_v_f32m1_m : Vstore_1VectorArg_f32m1_m;
  def int_riscv_vse_v_f32m2_m : Vstore_1VectorArg_f32m2_m;
  def int_riscv_vse_v_f32m4_m : Vstore_1VectorArg_f32m4_m;
  def int_riscv_vse_v_f32m8_m : Vstore_1VectorArg_f32m8_m;

//vector stride load
  class Vload_1VectorArg_1ScalarArg_v8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlse_v_8m1 : Vload_1VectorArg_1ScalarArg_v8m1;
  def int_riscv_vlse_v_8m2 : Vload_1VectorArg_1ScalarArg_v8m2;
  def int_riscv_vlse_v_8m4 : Vload_1VectorArg_1ScalarArg_v8m4;
  def int_riscv_vlse_v_8m8 : Vload_1VectorArg_1ScalarArg_v8m8;
  
  class Vload_1VectorArg_1ScalarArg_v16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlse_v_16m1 : Vload_1VectorArg_1ScalarArg_v16m1;
  def int_riscv_vlse_v_16m2 : Vload_1VectorArg_1ScalarArg_v16m2;
  def int_riscv_vlse_v_16m4 : Vload_1VectorArg_1ScalarArg_v16m4;
  def int_riscv_vlse_v_16m8 : Vload_1VectorArg_1ScalarArg_v16m8;

  class Vload_1VectorArg_1ScalarArg_v32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlse_v_32m1 : Vload_1VectorArg_1ScalarArg_v32m1;
  def int_riscv_vlse_v_32m2 : Vload_1VectorArg_1ScalarArg_v32m2;
  def int_riscv_vlse_v_32m4 : Vload_1VectorArg_1ScalarArg_v32m4;
  def int_riscv_vlse_v_32m8 : Vload_1VectorArg_1ScalarArg_v32m8;
  
  class Vload_1VectorArg_1ScalarArg_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlse_v_f32m1 : Vload_1VectorArg_1ScalarArg_f32m1;
  def int_riscv_vlse_v_f32m2 : Vload_1VectorArg_1ScalarArg_f32m2;
  def int_riscv_vlse_v_f32m4 : Vload_1VectorArg_1ScalarArg_f32m4;
  def int_riscv_vlse_v_f32m8 : Vload_1VectorArg_1ScalarArg_f32m8; 
  
  
//masked
  class Vload_1VectorArg_1ScalarArg_v8m1_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v8m2_m : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v8m4_m : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v8m8_m : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlse_v_8m1_m : Vload_1VectorArg_1ScalarArg_v8m1_m;
  def int_riscv_vlse_v_8m2_m : Vload_1VectorArg_1ScalarArg_v8m2_m;
  def int_riscv_vlse_v_8m4_m : Vload_1VectorArg_1ScalarArg_v8m4_m;
  def int_riscv_vlse_v_8m8_m : Vload_1VectorArg_1ScalarArg_v8m8_m;
  
  class Vload_1VectorArg_1ScalarArg_v16m1_m : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v16m2_m : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v16m4_m : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v16m8_m : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlse_v_16m1_m : Vload_1VectorArg_1ScalarArg_v16m1_m;
  def int_riscv_vlse_v_16m2_m : Vload_1VectorArg_1ScalarArg_v16m2_m;
  def int_riscv_vlse_v_16m4_m : Vload_1VectorArg_1ScalarArg_v16m4_m;
  def int_riscv_vlse_v_16m8_m : Vload_1VectorArg_1ScalarArg_v16m8_m;

  class Vload_1VectorArg_1ScalarArg_v32m1_m : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v32m2_m : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v32m4_m : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_v32m8_m : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlse_v_32m1_m : Vload_1VectorArg_1ScalarArg_v32m1_m;
  def int_riscv_vlse_v_32m2_m : Vload_1VectorArg_1ScalarArg_v32m2_m;
  def int_riscv_vlse_v_32m4_m : Vload_1VectorArg_1ScalarArg_v32m4_m;
  def int_riscv_vlse_v_32m8_m : Vload_1VectorArg_1ScalarArg_v32m8_m;
  
  class Vload_1VectorArg_1ScalarArg_f32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_f32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_f32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_1VectorArg_1ScalarArg_f32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlse_v_f32m1_m : Vload_1VectorArg_1ScalarArg_f32m1_m;
  def int_riscv_vlse_v_f32m2_m : Vload_1VectorArg_1ScalarArg_f32m2_m;
  def int_riscv_vlse_v_f32m4_m : Vload_1VectorArg_1ScalarArg_f32m4_m;
  def int_riscv_vlse_v_f32m8_m : Vload_1VectorArg_1ScalarArg_f32m8_m; 
  
//vector stride store 
  class Vstore_1VectorArg_1ScalarArg_v8m1 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v8m2 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v32i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v8m4 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v64i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v8m8 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v128i8_ty],[IntrWriteMem,IntrArgMemOnly]>; 

  def int_riscv_vsse_v_8m1 : Vstore_1VectorArg_1ScalarArg_v8m1;
  def int_riscv_vsse_v_8m2 : Vstore_1VectorArg_1ScalarArg_v8m2;
  def int_riscv_vsse_v_8m4 : Vstore_1VectorArg_1ScalarArg_v8m4;
  def int_riscv_vsse_v_8m8 : Vstore_1VectorArg_1ScalarArg_v8m8;
  
  class Vstore_1VectorArg_1ScalarArg_v16m1 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v8i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v16m2 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v16i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v16m4 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v32i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v16m8 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v64i16_ty],[IntrWriteMem,IntrArgMemOnly]>; 

  def int_riscv_vsse_v_16m1 : Vstore_1VectorArg_1ScalarArg_v16m1;
  def int_riscv_vsse_v_16m2 : Vstore_1VectorArg_1ScalarArg_v16m2;
  def int_riscv_vsse_v_16m4 : Vstore_1VectorArg_1ScalarArg_v16m4;
  def int_riscv_vsse_v_16m8 : Vstore_1VectorArg_1ScalarArg_v16m8;  
  
  class Vstore_1VectorArg_1ScalarArg_v32m1 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v4i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v32m2 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v8i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v32m4 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v16i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v32m8 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v32i32_ty],[IntrWriteMem,IntrArgMemOnly]>; 

  def int_riscv_vsse_v_32m1 : Vstore_1VectorArg_1ScalarArg_v32m1;
  def int_riscv_vsse_v_32m2 : Vstore_1VectorArg_1ScalarArg_v32m2;
  def int_riscv_vsse_v_32m4 : Vstore_1VectorArg_1ScalarArg_v32m4;
  def int_riscv_vsse_v_32m8 : Vstore_1VectorArg_1ScalarArg_v32m8;  
  
  class Vstore_1VectorArg_1ScalarArg_f32m1 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v4f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_f32m2 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v8f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_f32m4 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v16f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_f32m8 : Intrinsic<[],[llvm_ptr_ty,llvm_i32_ty,llvm_v32f32_ty],[IntrWriteMem,IntrArgMemOnly]>; 

  def int_riscv_vsse_v_f32m1 : Vstore_1VectorArg_1ScalarArg_f32m1;
  def int_riscv_vsse_v_f32m2 : Vstore_1VectorArg_1ScalarArg_f32m2;
  def int_riscv_vsse_v_f32m4 : Vstore_1VectorArg_1ScalarArg_f32m4;
  def int_riscv_vsse_v_f32m8 : Vstore_1VectorArg_1ScalarArg_f32m8;  
  
//masked
  class Vstore_1VectorArg_1ScalarArg_v8m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v16i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v8m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v32i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v8m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v64i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v8m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v128i8_ty],[IntrWriteMem,IntrArgMemOnly]>; 

  def int_riscv_vsse_v_8m1_m : Vstore_1VectorArg_1ScalarArg_v8m1_m;
  def int_riscv_vsse_v_8m2_m : Vstore_1VectorArg_1ScalarArg_v8m2_m;
  def int_riscv_vsse_v_8m4_m : Vstore_1VectorArg_1ScalarArg_v8m4_m;
  def int_riscv_vsse_v_8m8_m : Vstore_1VectorArg_1ScalarArg_v8m8_m;
  
  class Vstore_1VectorArg_1ScalarArg_v16m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v8i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v16m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v16i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v16m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v32i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v16m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v64i16_ty],[IntrWriteMem,IntrArgMemOnly]>; 

  def int_riscv_vsse_v_16m1_m : Vstore_1VectorArg_1ScalarArg_v16m1_m;
  def int_riscv_vsse_v_16m2_m : Vstore_1VectorArg_1ScalarArg_v16m2_m;
  def int_riscv_vsse_v_16m4_m : Vstore_1VectorArg_1ScalarArg_v16m4_m;
  def int_riscv_vsse_v_16m8_m : Vstore_1VectorArg_1ScalarArg_v16m8_m;  
  
  class Vstore_1VectorArg_1ScalarArg_v32m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v4i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v32m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v8i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v32m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v16i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_v32m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v32i32_ty],[IntrWriteMem,IntrArgMemOnly]>; 

  def int_riscv_vsse_v_32m1_m : Vstore_1VectorArg_1ScalarArg_v32m1_m;
  def int_riscv_vsse_v_32m2_m : Vstore_1VectorArg_1ScalarArg_v32m2_m;
  def int_riscv_vsse_v_32m4_m : Vstore_1VectorArg_1ScalarArg_v32m4_m;
  def int_riscv_vsse_v_32m8_m : Vstore_1VectorArg_1ScalarArg_v32m8_m;  
  
  class Vstore_1VectorArg_1ScalarArg_f32m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v4f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_f32m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v8f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_f32m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v16f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_1VectorArg_1ScalarArg_f32m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_i32_ty,llvm_v32f32_ty],[IntrWriteMem,IntrArgMemOnly]>; 

  def int_riscv_vsse_v_f32m1_m : Vstore_1VectorArg_1ScalarArg_f32m1_m;
  def int_riscv_vsse_v_f32m2_m : Vstore_1VectorArg_1ScalarArg_f32m2_m;
  def int_riscv_vsse_v_f32m4_m : Vstore_1VectorArg_1ScalarArg_f32m4_m;
  def int_riscv_vsse_v_f32m8_m : Vstore_1VectorArg_1ScalarArg_f32m8_m;  
  
  
//vector index load
  class Vload_2VectorArg_v8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_ptr_ty,llvm_v16i8_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_ptr_ty,llvm_v32i8_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_ptr_ty,llvm_v64i8_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_ptr_ty,llvm_v128i8_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlxe_v_8m1 : Vload_2VectorArg_v8m1;
  def int_riscv_vlxe_v_8m2 : Vload_2VectorArg_v8m2;
  def int_riscv_vlxe_v_8m4 : Vload_2VectorArg_v8m4;
  def int_riscv_vlxe_v_8m8 : Vload_2VectorArg_v8m8;
  
  class Vload_2VectorArg_v16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_ptr_ty,llvm_v8i16_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_ptr_ty,llvm_v16i16_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_ptr_ty,llvm_v32i16_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_ptr_ty,llvm_v64i16_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlxe_v_16m1 : Vload_2VectorArg_v16m1;
  def int_riscv_vlxe_v_16m2 : Vload_2VectorArg_v16m2;
  def int_riscv_vlxe_v_16m4 : Vload_2VectorArg_v16m4;
  def int_riscv_vlxe_v_16m8 : Vload_2VectorArg_v16m8;

  class Vload_2VectorArg_v32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_ptr_ty,llvm_v4i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_ptr_ty,llvm_v8i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_ptr_ty,llvm_v16i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_ptr_ty,llvm_v32i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlxe_v_32m1 : Vload_2VectorArg_v32m1;
  def int_riscv_vlxe_v_32m2 : Vload_2VectorArg_v32m2;
  def int_riscv_vlxe_v_32m4 : Vload_2VectorArg_v32m4;
  def int_riscv_vlxe_v_32m8 : Vload_2VectorArg_v32m8;
  
  class Vload_2VectorArg_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_ptr_ty,llvm_v4i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_ptr_ty,llvm_v8i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_ptr_ty,llvm_v16i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_ptr_ty,llvm_v32i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlxe_v_f32m1 : Vload_2VectorArg_f32m1;
  def int_riscv_vlxe_v_f32m2 : Vload_2VectorArg_f32m2;
  def int_riscv_vlxe_v_f32m4 : Vload_2VectorArg_f32m4;
  def int_riscv_vlxe_v_f32m8 : Vload_2VectorArg_f32m8; 
  
//masked
  class Vload_2VectorArg_v8m1_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v16i8_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v8m2_m : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v32i8_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v8m4_m : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v64i8_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v8m8_m : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v128i8_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlxe_v_8m1_m : Vload_2VectorArg_v8m1_m;
  def int_riscv_vlxe_v_8m2_m : Vload_2VectorArg_v8m2_m;
  def int_riscv_vlxe_v_8m4_m : Vload_2VectorArg_v8m4_m;
  def int_riscv_vlxe_v_8m8_m : Vload_2VectorArg_v8m8_m;
  
  class Vload_2VectorArg_v16m1_m : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v8i16_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v16m2_m : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v16i16_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v16m4_m : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v32i16_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v16m8_m : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v64i16_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlxe_v_16m1_m : Vload_2VectorArg_v16m1_m;
  def int_riscv_vlxe_v_16m2_m : Vload_2VectorArg_v16m2_m;
  def int_riscv_vlxe_v_16m4_m : Vload_2VectorArg_v16m4_m;
  def int_riscv_vlxe_v_16m8_m : Vload_2VectorArg_v16m8_m;

  class Vload_2VectorArg_v32m1_m : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v4i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v32m2_m : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v8i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v32m4_m : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v16i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_v32m8_m : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v32i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlxe_v_32m1_m : Vload_2VectorArg_v32m1_m;
  def int_riscv_vlxe_v_32m2_m : Vload_2VectorArg_v32m2_m;
  def int_riscv_vlxe_v_32m4_m : Vload_2VectorArg_v32m4_m;
  def int_riscv_vlxe_v_32m8_m : Vload_2VectorArg_v32m8_m;
  
  class Vload_2VectorArg_f32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v4i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_f32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v8i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_f32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v16i32_ty],[IntrReadMem,IntrArgMemOnly]>;
  class Vload_2VectorArg_f32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v32i32_ty],[IntrReadMem,IntrArgMemOnly]>;

  def int_riscv_vlxe_v_f32m1_m : Vload_2VectorArg_f32m1_m;
  def int_riscv_vlxe_v_f32m2_m : Vload_2VectorArg_f32m2_m;
  def int_riscv_vlxe_v_f32m4_m : Vload_2VectorArg_f32m4_m;
  def int_riscv_vlxe_v_f32m8_m : Vload_2VectorArg_f32m8_m; 
  
//vector index store
  class Vstore_2VectorArg_v8m1 : Intrinsic<[],[llvm_ptr_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v8m2 : Intrinsic<[],[llvm_ptr_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v8m4 : Intrinsic<[],[llvm_ptr_ty,llvm_v64i8_ty,llvm_v64i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v8m8 : Intrinsic<[],[llvm_ptr_ty,llvm_v128i8_ty,llvm_v128i8_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vsxe_v_8m1 : Vstore_2VectorArg_v8m1;
  def int_riscv_vsxe_v_8m2 : Vstore_2VectorArg_v8m2;
  def int_riscv_vsxe_v_8m4 : Vstore_2VectorArg_v8m4;
  def int_riscv_vsxe_v_8m8 : Vstore_2VectorArg_v8m8;
  
  class Vstore_2VectorArg_v16m1 : Intrinsic<[],[llvm_ptr_ty,llvm_v8i16_ty,llvm_v8i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v16m2 : Intrinsic<[],[llvm_ptr_ty,llvm_v16i16_ty,llvm_v16i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v16m4 : Intrinsic<[],[llvm_ptr_ty,llvm_v32i16_ty,llvm_v32i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v16m8 : Intrinsic<[],[llvm_ptr_ty,llvm_v64i16_ty,llvm_v64i16_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vsxe_v_16m1 : Vstore_2VectorArg_v16m1;
  def int_riscv_vsxe_v_16m2 : Vstore_2VectorArg_v16m2;
  def int_riscv_vsxe_v_16m4 : Vstore_2VectorArg_v16m4;
  def int_riscv_vsxe_v_16m8 : Vstore_2VectorArg_v16m8;

  class Vstore_2VectorArg_v32m1 : Intrinsic<[],[llvm_ptr_ty,llvm_v4i32_ty,llvm_v4i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v32m2 : Intrinsic<[],[llvm_ptr_ty,llvm_v8i32_ty,llvm_v8i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v32m4 : Intrinsic<[],[llvm_ptr_ty,llvm_v16i32_ty,llvm_v16i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v32m8 : Intrinsic<[],[llvm_ptr_ty,llvm_v32i32_ty,llvm_v32i32_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vsxe_v_32m1 : Vstore_2VectorArg_v32m1;
  def int_riscv_vsxe_v_32m2 : Vstore_2VectorArg_v32m2;
  def int_riscv_vsxe_v_32m4 : Vstore_2VectorArg_v32m4;
  def int_riscv_vsxe_v_32m8 : Vstore_2VectorArg_v32m8;
  
  class Vstore_2VectorArg_f32m1 : Intrinsic<[],[llvm_ptr_ty,llvm_v4i32_ty,llvm_v4f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_f32m2 : Intrinsic<[],[llvm_ptr_ty,llvm_v8i32_ty,llvm_v8f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_f32m4 : Intrinsic<[],[llvm_ptr_ty,llvm_v16i32_ty,llvm_v16f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_f32m8 : Intrinsic<[],[llvm_ptr_ty,llvm_v32i32_ty,llvm_v32f32_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vsxe_v_f32m1 : Vstore_2VectorArg_f32m1;
  def int_riscv_vsxe_v_f32m2 : Vstore_2VectorArg_f32m2;
  def int_riscv_vsxe_v_f32m4 : Vstore_2VectorArg_f32m4;
  def int_riscv_vsxe_v_f32m8 : Vstore_2VectorArg_f32m8; 
  
//masked
  class Vstore_2VectorArg_v8m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v8m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v8m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v64i8_ty,llvm_v64i8_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v8m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v128i8_ty,llvm_v128i8_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vsxe_v_8m1_m : Vstore_2VectorArg_v8m1_m;
  def int_riscv_vsxe_v_8m2_m : Vstore_2VectorArg_v8m2_m;
  def int_riscv_vsxe_v_8m4_m : Vstore_2VectorArg_v8m4_m;
  def int_riscv_vsxe_v_8m8_m : Vstore_2VectorArg_v8m8_m;
  
  class Vstore_2VectorArg_v16m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v8i16_ty,llvm_v8i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v16m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v16i16_ty,llvm_v16i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v16m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v32i16_ty,llvm_v32i16_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v16m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v64i16_ty,llvm_v64i16_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vsxe_v_16m1_m : Vstore_2VectorArg_v16m1_m;
  def int_riscv_vsxe_v_16m2_m : Vstore_2VectorArg_v16m2_m;
  def int_riscv_vsxe_v_16m4_m : Vstore_2VectorArg_v16m4_m;
  def int_riscv_vsxe_v_16m8_m : Vstore_2VectorArg_v16m8_m;

  class Vstore_2VectorArg_v32m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v4i32_ty,llvm_v4i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v32m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v8i32_ty,llvm_v8i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v32m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v16i32_ty,llvm_v16i32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_v32m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v32i32_ty,llvm_v32i32_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vsxe_v_32m1_m : Vstore_2VectorArg_v32m1_m;
  def int_riscv_vsxe_v_32m2_m : Vstore_2VectorArg_v32m2_m;
  def int_riscv_vsxe_v_32m4_m : Vstore_2VectorArg_v32m4_m;
  def int_riscv_vsxe_v_32m8_m : Vstore_2VectorArg_v32m8_m;
  
  class Vstore_2VectorArg_f32m1_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v4i32_ty,llvm_v4f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_f32m2_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v8i32_ty,llvm_v8f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_f32m4_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v16i32_ty,llvm_v16f32_ty],[IntrWriteMem,IntrArgMemOnly]>;
  class Vstore_2VectorArg_f32m8_m : Intrinsic<[],[llvm_v16i8_ty,llvm_ptr_ty,llvm_v32i32_ty,llvm_v32f32_ty],[IntrWriteMem,IntrArgMemOnly]>;

  def int_riscv_vsxe_v_f32m1_m : Vstore_2VectorArg_f32m1_m;
  def int_riscv_vsxe_v_f32m2_m : Vstore_2VectorArg_f32m2_m;
  def int_riscv_vsxe_v_f32m4_m : Vstore_2VectorArg_f32m4_m;
  def int_riscv_vsxe_v_f32m8_m : Vstore_2VectorArg_f32m8_m; 
  
  //vector unorder index store 
  def int_riscv_vsuxe_v_8m1 : Vstore_2VectorArg_v8m1;
  def int_riscv_vsuxe_v_8m2 : Vstore_2VectorArg_v8m2;
  def int_riscv_vsuxe_v_8m4 : Vstore_2VectorArg_v8m4;
  def int_riscv_vsuxe_v_8m8 : Vstore_2VectorArg_v8m8;
  
  def int_riscv_vsuxe_v_16m1 : Vstore_2VectorArg_v16m1;
  def int_riscv_vsuxe_v_16m2 : Vstore_2VectorArg_v16m2;
  def int_riscv_vsuxe_v_16m4 : Vstore_2VectorArg_v16m4;
  def int_riscv_vsuxe_v_16m8 : Vstore_2VectorArg_v16m8;

  def int_riscv_vsuxe_v_32m1 : Vstore_2VectorArg_v32m1;
  def int_riscv_vsuxe_v_32m2 : Vstore_2VectorArg_v32m2;
  def int_riscv_vsuxe_v_32m4 : Vstore_2VectorArg_v32m4;
  def int_riscv_vsuxe_v_32m8 : Vstore_2VectorArg_v32m8;
  
  def int_riscv_vsuxe_v_f32m1 : Vstore_2VectorArg_f32m1;
  def int_riscv_vsuxe_v_f32m2 : Vstore_2VectorArg_f32m2;
  def int_riscv_vsuxe_v_f32m4 : Vstore_2VectorArg_f32m4;
  def int_riscv_vsuxe_v_f32m8 : Vstore_2VectorArg_f32m8; 
  
//masked
  def int_riscv_vsuxe_v_8m1_m : Vstore_2VectorArg_v8m1_m;
  def int_riscv_vsuxe_v_8m2_m : Vstore_2VectorArg_v8m2_m;
  def int_riscv_vsuxe_v_8m4_m : Vstore_2VectorArg_v8m4_m;
  def int_riscv_vsuxe_v_8m8_m : Vstore_2VectorArg_v8m8_m;
  
  def int_riscv_vsuxe_v_16m1_m : Vstore_2VectorArg_v16m1_m;
  def int_riscv_vsuxe_v_16m2_m : Vstore_2VectorArg_v16m2_m;
  def int_riscv_vsuxe_v_16m4_m : Vstore_2VectorArg_v16m4_m;
  def int_riscv_vsuxe_v_16m8_m : Vstore_2VectorArg_v16m8_m;

  def int_riscv_vsuxe_v_32m1_m : Vstore_2VectorArg_v32m1_m;
  def int_riscv_vsuxe_v_32m2_m : Vstore_2VectorArg_v32m2_m;
  def int_riscv_vsuxe_v_32m4_m : Vstore_2VectorArg_v32m4_m;
  def int_riscv_vsuxe_v_32m8_m : Vstore_2VectorArg_v32m8_m;
  
  def int_riscv_vsuxe_v_f32m1_m : Vstore_2VectorArg_f32m1_m;
  def int_riscv_vsuxe_v_f32m2_m : Vstore_2VectorArg_f32m2_m;
  def int_riscv_vsuxe_v_f32m4_m : Vstore_2VectorArg_f32m4_m;
  def int_riscv_vsuxe_v_f32m8_m : Vstore_2VectorArg_f32m8_m; 

  
//vector first-only-fault load
  def int_riscv_vleff_v_8m1 : Vload_1VectorArg_v8m1;
  def int_riscv_vleff_v_8m2 : Vload_1VectorArg_v8m2;
  def int_riscv_vleff_v_8m4 : Vload_1VectorArg_v8m4;
  def int_riscv_vleff_v_8m8 : Vload_1VectorArg_v8m8;

  def int_riscv_vleff_v_16m1 : Vload_1VectorArg_v16m1;
  def int_riscv_vleff_v_16m2 : Vload_1VectorArg_v16m2;
  def int_riscv_vleff_v_16m4 : Vload_1VectorArg_v16m4;
  def int_riscv_vleff_v_16m8 : Vload_1VectorArg_v16m8;

  def int_riscv_vleff_v_32m1 : Vload_1VectorArg_v32m1;
  def int_riscv_vleff_v_32m2 : Vload_1VectorArg_v32m2;
  def int_riscv_vleff_v_32m4 : Vload_1VectorArg_v32m4;
  def int_riscv_vleff_v_32m8 : Vload_1VectorArg_v32m8;

  def int_riscv_vleff_v_f32m1 : Vload_1VectorArg_f32m1;
  def int_riscv_vleff_v_f32m2 : Vload_1VectorArg_f32m2;
  def int_riscv_vleff_v_f32m4 : Vload_1VectorArg_f32m4;
  def int_riscv_vleff_v_f32m8 : Vload_1VectorArg_f32m8;

  //masked functions
  def int_riscv_vleff_v_8m1_m : Vload_1VectorArg_v8m1_m;
  def int_riscv_vleff_v_8m2_m : Vload_1VectorArg_v8m2_m;
  def int_riscv_vleff_v_8m4_m : Vload_1VectorArg_v8m4_m;
  def int_riscv_vleff_v_8m8_m : Vload_1VectorArg_v8m8_m;

  def int_riscv_vleff_v_16m1_m : Vload_1VectorArg_v16m1_m;
  def int_riscv_vleff_v_16m2_m : Vload_1VectorArg_v16m2_m;
  def int_riscv_vleff_v_16m4_m : Vload_1VectorArg_v16m4_m;
  def int_riscv_vleff_v_16m8_m : Vload_1VectorArg_v16m8_m;

  def int_riscv_vleff_v_32m1_m : Vload_1VectorArg_v32m1_m;
  def int_riscv_vleff_v_32m2_m : Vload_1VectorArg_v32m2_m;
  def int_riscv_vleff_v_32m4_m : Vload_1VectorArg_v32m4_m;
  def int_riscv_vleff_v_32m8_m : Vload_1VectorArg_v32m8_m;

  def int_riscv_vleff_v_f32m1_m : Vload_1VectorArg_f32m1_m;
  def int_riscv_vleff_v_f32m2_m : Vload_1VectorArg_f32m2_m;
  def int_riscv_vleff_v_f32m4_m : Vload_1VectorArg_f32m4_m;
  def int_riscv_vleff_v_f32m8_m : Vload_1VectorArg_f32m8_m;
  
//vector floating template

  class Vector_mov_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_float_ty],[IntrNoMem]>;
  class Vector_mov_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_float_ty],[IntrNoMem]>;
  class Vector_mov_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_float_ty],[IntrNoMem]>;
  class Vector_mov_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_float_ty],[IntrNoMem]>;  
 
  class Int_Vector_f32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4f32_ty],[IntrNoMem]>;
  class Int_Vector_f32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8f32_ty],[IntrNoMem]>;
  class Int_Vector_f32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16f32_ty],[IntrNoMem]>;
  class Int_Vector_f32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32f32_ty],[IntrNoMem]>;
      
  class Vector_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_v32f32_ty],[IntrNoMem]>;
  
  
  class Int_Vector_f32m1_m : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Int_Vector_f32m2_m : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Int_Vector_f32m4_m : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Int_Vector_f32m8_m : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32f32_ty],[IntrNoMem]>;
  
  class Vector_f32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_f32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_f32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_f32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32f32_ty],[IntrNoMem]>;
  
 
  class Vector_Vector_v8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vector_Vector_v8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Vector_Vector_v8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class Vector_Vector_v8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v128i8_ty,llvm_v128i8_ty],[IntrNoMem]>;
  
  class Vector_Vector_v16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Vector_Vector_v16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Vector_Vector_v16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class Vector_Vector_v16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_v64i16_ty],[IntrNoMem]>;  
  
  class Vector_Vector_v32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4i32_ty,llvm_v4i32_ty],[IntrNoMem]>;  
  class Vector_Vector_v32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class Vector_Vector_v32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class Vector_Vector_v32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_v32i32_ty],[IntrNoMem]>;    
    
  class Vector_Vector_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_v4f32_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_Vector_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_v8f32_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_Vector_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_v16f32_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_Vector_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_v32f32_ty,llvm_v32f32_ty],[IntrNoMem]>;
  
  class Vector_VectorInt_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_v4f32_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class Vector_VectorInt_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_v8f32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class Vector_VectorInt_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_v16f32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class Vector_VectorInt_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_v32f32_ty,llvm_v32i32_ty],[IntrNoMem]>;

  class Vector_float_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_v4f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_v8f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_v16f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_v32f32_ty,llvm_float_ty],[IntrNoMem]>;

  class Vector_Vector_v8m1_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vector_Vector_v8m2_m : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Vector_Vector_v8m4_m : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class Vector_Vector_v8m8_m : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty,llvm_v128i8_ty,llvm_v128i8_ty],[IntrNoMem]>;
  
  class Vector_Vector_v16m1_m : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Vector_Vector_v16m2_m : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Vector_Vector_v16m4_m : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class Vector_Vector_v16m8_m : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_v64i16_ty],[IntrNoMem]>;  
  
  class Vector_Vector_v32m1_m : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_v4i32_ty,llvm_v4i32_ty],[IntrNoMem]>;  
  class Vector_Vector_v32m2_m : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class Vector_Vector_v32m4_m : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class Vector_Vector_v32m8_m : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_v32i32_ty],[IntrNoMem]>;   
     
  class Vector_Vector_f32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4f32_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_Vector_f32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8f32_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_Vector_f32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16f32_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_Vector_f32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32f32_ty,llvm_v32f32_ty],[IntrNoMem]>;
  
  class Vector_VectorInt_f32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4f32_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class Vector_VectorInt_f32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8f32_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class Vector_VectorInt_f32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16f32_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class Vector_VectorInt_f32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32f32_ty,llvm_v32i32_ty],[IntrNoMem]>;

  class Vector_float_f32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_f32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_f32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_f32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32f32_ty,llvm_float_ty],[IntrNoMem]>;

  class Vector_Vector_Vector_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_v4f32_ty,llvm_v4f32_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_Vector_Vector_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_v8f32_ty,llvm_v8f32_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_Vector_Vector_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_v16f32_ty,llvm_v16f32_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_Vector_Vector_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_v32f32_ty,llvm_v32f32_ty,llvm_v32f32_ty],[IntrNoMem]>;

  class Vector_Vector_float_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_v4f32_ty,llvm_float_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_Vector_float_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_v8f32_ty,llvm_float_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_Vector_float_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_v16f32_ty,llvm_float_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_Vector_float_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_v32f32_ty,llvm_float_ty,llvm_v32f32_ty],[IntrNoMem]>;

  class Vector_Vector_Vector_f32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4f32_ty,llvm_v4f32_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_Vector_Vector_f32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8f32_ty,llvm_v8f32_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_Vector_Vector_f32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16f32_ty,llvm_v16f32_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_Vector_Vector_f32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32f32_ty,llvm_v32f32_ty,llvm_v32f32_ty],[IntrNoMem]>;

  class Vector_Vector_float_f32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4f32_ty,llvm_float_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_Vector_float_f32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8f32_ty,llvm_float_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_Vector_float_f32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16f32_ty,llvm_float_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_Vector_float_f32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32f32_ty,llvm_float_ty,llvm_v32f32_ty],[IntrNoMem]>;
  
  class Vector_integer_and_float_f32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_integer_and_float_f32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_integer_and_float_f32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_integer_and_float_f32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32f32_ty],[IntrNoMem]>;
  
  class Vector_integer_and_float_f32m1_m : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_integer_and_float_f32m2_m : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_integer_and_float_f32m4_m : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_integer_and_float_f32m8_m : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32f32_ty],[IntrNoMem]>;

  class Vector_float_and_integer_u32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_v4i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_u32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_v8i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_u32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_v16i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_u32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_v32i32_ty],[IntrNoMem]>;

  class Vector_float_and_integer_i32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_v4i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_i32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_v8i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_i32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_v16i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_i32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_v32i32_ty],[IntrNoMem]>;
 
  class Vector_float_and_integer_u32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_u32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_u32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_u32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32i32_ty],[IntrNoMem]>;

  class Vector_float_and_integer_i32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_i32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_i32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class Vector_float_and_integer_i32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32i32_ty],[IntrNoMem]>; 
  
  class Vector_scalar_v8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v32i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v64i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v128i8_ty,llvm_i32_ty],[IntrNoMem]>;
  
  class Vector_scalar_v16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v8i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i16_ty,llvm_i32_ty],[IntrNoMem]>;    
  
  class Vector_scalar_v32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v4i32_ty,llvm_i32_ty],[IntrNoMem]>;  
  class Vector_scalar_v32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i32_ty,llvm_i32_ty],[IntrNoMem]>; 
  class Vector_scalar_v32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i32_ty,llvm_i32_ty],[IntrNoMem]>; 
  class Vector_scalar_v32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i32_ty,llvm_i32_ty],[IntrNoMem]>; 
   
  class Vector_scalar_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_v4f32_ty,llvm_i32_ty],[IntrNoMem]>;  
  class Vector_scalar_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_v8f32_ty,llvm_i32_ty],[IntrNoMem]>; 
  class Vector_scalar_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_v16f32_ty,llvm_i32_ty],[IntrNoMem]>; 
  class Vector_scalar_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_v32f32_ty,llvm_i32_ty],[IntrNoMem]>; 
 
  class Vector_scalar_v8m1_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v8m2_m : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v8m4_m : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v8m8_m : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty,llvm_v128i8_ty,llvm_i32_ty],[IntrNoMem]>;
  
  class Vector_scalar_v16m1_m : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v16m2_m : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v16m4_m : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_i32_ty],[IntrNoMem]>;
  class Vector_scalar_v16m8_m : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty,llvm_i32_ty],[IntrNoMem]>;    
  
  class Vector_scalar_v32m1_m : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_v4i32_ty,llvm_i32_ty],[IntrNoMem]>;  
  class Vector_scalar_v32m2_m : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty,llvm_i32_ty],[IntrNoMem]>; 
  class Vector_scalar_v32m4_m : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty,llvm_i32_ty],[IntrNoMem]>; 
  class Vector_scalar_v32m8_m : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty,llvm_i32_ty],[IntrNoMem]>; 
   
  class Vector_scalar_f32m1_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4f32_ty,llvm_i32_ty],[IntrNoMem]>;  
  class Vector_scalar_f32m2_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8f32_ty,llvm_i32_ty],[IntrNoMem]>; 
  class Vector_scalar_f32m4_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16f32_ty,llvm_i32_ty],[IntrNoMem]>; 
  class Vector_scalar_f32m8_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32f32_ty,llvm_i32_ty],[IntrNoMem]>; 
  
  class Vector_Vector_Compare_f32m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v4f32_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_Vector_Compare_f32m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v8f32_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_Vector_Compare_f32m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16f32_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_Vector_Compare_f32m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v32f32_ty,llvm_v32f32_ty],[IntrNoMem]>;

  class Vector_float_Compare_f32m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v4f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_Compare_f32m2 : Intrinsic<[llvm_v16i8_ty],[llvm_v8f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_Compare_f32m4 : Intrinsic<[llvm_v16i8_ty],[llvm_v16f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_Compare_f32m8 : Intrinsic<[llvm_v16i8_ty],[llvm_v32f32_ty,llvm_float_ty],[IntrNoMem]>;
  
  class Vector_Vector_Compare_f32m1_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v4f32_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vector_Vector_Compare_f32m2_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v8f32_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vector_Vector_Compare_f32m4_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16f32_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vector_Vector_Compare_f32m8_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v32f32_ty,llvm_v32f32_ty],[IntrNoMem]>;

  class Vector_float_Compare_f32m1_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v4f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_Compare_f32m2_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v8f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_Compare_f32m4_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16f32_ty,llvm_float_ty],[IntrNoMem]>;
  class Vector_float_Compare_f32m8_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v32f32_ty,llvm_float_ty],[IntrNoMem]>;
  
  class Vm_Vector_v8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  class Vm_Vector_v8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty,llvm_v32i8_ty],[IntrNoMem]>;
  class Vm_Vector_v8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty,llvm_v64i8_ty],[IntrNoMem]>;
  class Vm_Vector_v8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty,llvm_v128i8_ty],[IntrNoMem]>;
  
  class Vm_Vector_v16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8i16_ty],[IntrNoMem]>;
  class Vm_Vector_v16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty],[IntrNoMem]>;
  class Vm_Vector_v16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i16_ty],[IntrNoMem]>;
  class Vm_Vector_v16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i16_ty],[IntrNoMem]>;  
  
  class Vm_Vector_v32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty,llvm_v4i32_ty],[IntrNoMem]>;  
  class Vm_Vector_v32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i32_ty],[IntrNoMem]>;
  class Vm_Vector_v32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i32_ty],[IntrNoMem]>;
  class Vm_Vector_v32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i32_ty],[IntrNoMem]>;   
    
  class Vm_Vector_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4f32_ty],[IntrNoMem]>;
  class Vm_Vector_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8f32_ty],[IntrNoMem]>;
  class Vm_Vector_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16f32_ty],[IntrNoMem]>;
  class Vm_Vector_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32f32_ty],[IntrNoMem]>;
         
  //vector fadd/fsub
  def int_riscv_vfadd_vv_f32m1 : Vector_Vector_f32m1;
  def int_riscv_vfadd_vv_f32m2 : Vector_Vector_f32m2;
  def int_riscv_vfadd_vv_f32m4 : Vector_Vector_f32m4;
  def int_riscv_vfadd_vv_f32m8 : Vector_Vector_f32m8;
  
  def int_riscv_vfadd_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfadd_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfadd_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfadd_vf_f32m8 : Vector_float_f32m8;
 
  def int_riscv_vfsub_vv_f32m1 : Vector_Vector_f32m1;
  def int_riscv_vfsub_vv_f32m2 : Vector_Vector_f32m2;
  def int_riscv_vfsub_vv_f32m4 : Vector_Vector_f32m4;
  def int_riscv_vfsub_vv_f32m8 : Vector_Vector_f32m8;

  def int_riscv_vfsub_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfsub_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfsub_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfsub_vf_f32m8 : Vector_float_f32m8;
  
  def int_riscv_vfrsub_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfrsub_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfrsub_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfrsub_vf_f32m8 : Vector_float_f32m8;
  
//masked
  def int_riscv_vfadd_vv_f32m1_m : Vector_Vector_f32m1_m;
  def int_riscv_vfadd_vv_f32m2_m : Vector_Vector_f32m2_m;
  def int_riscv_vfadd_vv_f32m4_m : Vector_Vector_f32m4_m;
  def int_riscv_vfadd_vv_f32m8_m : Vector_Vector_f32m8_m;
  
  def int_riscv_vfadd_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfadd_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfadd_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfadd_vf_f32m8_m : Vector_float_f32m8_m;  
  
  def int_riscv_vfsub_vv_f32m1_m : Vector_Vector_f32m1_m;
  def int_riscv_vfsub_vv_f32m2_m : Vector_Vector_f32m2_m;
  def int_riscv_vfsub_vv_f32m4_m : Vector_Vector_f32m4_m;
  def int_riscv_vfsub_vv_f32m8_m : Vector_Vector_f32m8_m;
  
  def int_riscv_vfsub_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfsub_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfsub_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfsub_vf_f32m8_m : Vector_float_f32m8_m; 
  
  def int_riscv_vfrsub_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfrsub_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfrsub_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfrsub_vf_f32m8_m : Vector_float_f32m8_m; 
  
//vecotr fmul/fdiv
  def int_riscv_vfmul_vv_f32m1 : Vector_Vector_f32m1;
  def int_riscv_vfmul_vv_f32m2 : Vector_Vector_f32m2;
  def int_riscv_vfmul_vv_f32m4 : Vector_Vector_f32m4;
  def int_riscv_vfmul_vv_f32m8 : Vector_Vector_f32m8;
  
  def int_riscv_vfmul_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfmul_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfmul_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfmul_vf_f32m8 : Vector_float_f32m8;
  
  def int_riscv_vfdiv_vv_f32m1 : Vector_Vector_f32m1;
  def int_riscv_vfdiv_vv_f32m2 : Vector_Vector_f32m2;
  def int_riscv_vfdiv_vv_f32m4 : Vector_Vector_f32m4;
  def int_riscv_vfdiv_vv_f32m8 : Vector_Vector_f32m8;

  def int_riscv_vfdiv_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfdiv_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfdiv_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfdiv_vf_f32m8 : Vector_float_f32m8;
  
  def int_riscv_vfrdiv_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfrdiv_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfrdiv_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfrdiv_vf_f32m8 : Vector_float_f32m8;
  
//masked
  def int_riscv_vfmul_vv_f32m1_m : Vector_Vector_f32m1_m;
  def int_riscv_vfmul_vv_f32m2_m : Vector_Vector_f32m2_m;
  def int_riscv_vfmul_vv_f32m4_m : Vector_Vector_f32m4_m;
  def int_riscv_vfmul_vv_f32m8_m : Vector_Vector_f32m8_m;
  
  def int_riscv_vfmul_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfmul_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfmul_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfmul_vf_f32m8_m : Vector_float_f32m8_m;  
  
  def int_riscv_vfdiv_vv_f32m1_m : Vector_Vector_f32m1_m;
  def int_riscv_vfdiv_vv_f32m2_m : Vector_Vector_f32m2_m;
  def int_riscv_vfdiv_vv_f32m4_m : Vector_Vector_f32m4_m;
  def int_riscv_vfdiv_vv_f32m8_m : Vector_Vector_f32m8_m;

  def int_riscv_vfdiv_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfdiv_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfdiv_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfdiv_vf_f32m8_m : Vector_float_f32m8_m; 
  
  def int_riscv_vfrdiv_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfrdiv_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfrdiv_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfrdiv_vf_f32m8_m : Vector_float_f32m8_m;
  
//vector vfmadd/vfmsub
  def int_riscv_vfmacc_vv_f32m1 : Vector_Vector_Vector_f32m1;
  def int_riscv_vfmacc_vv_f32m2 : Vector_Vector_Vector_f32m2;
  def int_riscv_vfmacc_vv_f32m4 : Vector_Vector_Vector_f32m4;
  def int_riscv_vfmacc_vv_f32m8 : Vector_Vector_Vector_f32m8;
  
  def int_riscv_vfmacc_vf_f32m1 : Vector_Vector_float_f32m1;
  def int_riscv_vfmacc_vf_f32m2 : Vector_Vector_float_f32m2;
  def int_riscv_vfmacc_vf_f32m4 : Vector_Vector_float_f32m4;
  def int_riscv_vfmacc_vf_f32m8 : Vector_Vector_float_f32m8;
  
  def int_riscv_vfnmacc_vv_f32m1 : Vector_Vector_Vector_f32m1;
  def int_riscv_vfnmacc_vv_f32m2 : Vector_Vector_Vector_f32m2;
  def int_riscv_vfnmacc_vv_f32m4 : Vector_Vector_Vector_f32m4;
  def int_riscv_vfnmacc_vv_f32m8 : Vector_Vector_Vector_f32m8;
  
  def int_riscv_vfnmacc_vf_f32m1 : Vector_Vector_float_f32m1;
  def int_riscv_vfnmacc_vf_f32m2 : Vector_Vector_float_f32m2;
  def int_riscv_vfnmacc_vf_f32m4 : Vector_Vector_float_f32m4;
  def int_riscv_vfnmacc_vf_f32m8 : Vector_Vector_float_f32m8; 
  
  def int_riscv_vfmsac_vv_f32m1 : Vector_Vector_Vector_f32m1;
  def int_riscv_vfmsac_vv_f32m2 : Vector_Vector_Vector_f32m2;
  def int_riscv_vfmsac_vv_f32m4 : Vector_Vector_Vector_f32m4;
  def int_riscv_vfmsac_vv_f32m8 : Vector_Vector_Vector_f32m8;
  
  def int_riscv_vfmsac_vf_f32m1 : Vector_Vector_float_f32m1;
  def int_riscv_vfmsac_vf_f32m2 : Vector_Vector_float_f32m2;
  def int_riscv_vfmsac_vf_f32m4 : Vector_Vector_float_f32m4;
  def int_riscv_vfmsac_vf_f32m8 : Vector_Vector_float_f32m8;  
  
  def int_riscv_vfnmsac_vv_f32m1 : Vector_Vector_Vector_f32m1;
  def int_riscv_vfnmsac_vv_f32m2 : Vector_Vector_Vector_f32m2;
  def int_riscv_vfnmsac_vv_f32m4 : Vector_Vector_Vector_f32m4;
  def int_riscv_vfnmsac_vv_f32m8 : Vector_Vector_Vector_f32m8;
  
  def int_riscv_vfnmsac_vf_f32m1 : Vector_Vector_float_f32m1;
  def int_riscv_vfnmsac_vf_f32m2 : Vector_Vector_float_f32m2;
  def int_riscv_vfnmsac_vf_f32m4 : Vector_Vector_float_f32m4;
  def int_riscv_vfnmsac_vf_f32m8 : Vector_Vector_float_f32m8;   
  
  def int_riscv_vfmadd_vv_f32m1 : Vector_Vector_Vector_f32m1;
  def int_riscv_vfmadd_vv_f32m2 : Vector_Vector_Vector_f32m2;
  def int_riscv_vfmadd_vv_f32m4 : Vector_Vector_Vector_f32m4;
  def int_riscv_vfmadd_vv_f32m8 : Vector_Vector_Vector_f32m8;
  
  def int_riscv_vfmadd_vf_f32m1 : Vector_Vector_float_f32m1;
  def int_riscv_vfmadd_vf_f32m2 : Vector_Vector_float_f32m2;
  def int_riscv_vfmadd_vf_f32m4 : Vector_Vector_float_f32m4;
  def int_riscv_vfmadd_vf_f32m8 : Vector_Vector_float_f32m8;  
  
  def int_riscv_vfnmadd_vv_f32m1 : Vector_Vector_Vector_f32m1;
  def int_riscv_vfnmadd_vv_f32m2 : Vector_Vector_Vector_f32m2;
  def int_riscv_vfnmadd_vv_f32m4 : Vector_Vector_Vector_f32m4;
  def int_riscv_vfnmadd_vv_f32m8 : Vector_Vector_Vector_f32m8;
  
  def int_riscv_vfnmadd_vf_f32m1 : Vector_Vector_float_f32m1;
  def int_riscv_vfnmadd_vf_f32m2 : Vector_Vector_float_f32m2;
  def int_riscv_vfnmadd_vf_f32m4 : Vector_Vector_float_f32m4;
  def int_riscv_vfnmadd_vf_f32m8 : Vector_Vector_float_f32m8;  
  
  def int_riscv_vfmsub_vv_f32m1 : Vector_Vector_Vector_f32m1;
  def int_riscv_vfmsub_vv_f32m2 : Vector_Vector_Vector_f32m2;
  def int_riscv_vfmsub_vv_f32m4 : Vector_Vector_Vector_f32m4;
  def int_riscv_vfmsub_vv_f32m8 : Vector_Vector_Vector_f32m8;
  
  def int_riscv_vfmsub_vf_f32m1 : Vector_Vector_float_f32m1;
  def int_riscv_vfmsub_vf_f32m2 : Vector_Vector_float_f32m2;
  def int_riscv_vfmsub_vf_f32m4 : Vector_Vector_float_f32m4;
  def int_riscv_vfmsub_vf_f32m8 : Vector_Vector_float_f32m8;  
  
  def int_riscv_vfnmsub_vv_f32m1 : Vector_Vector_Vector_f32m1;
  def int_riscv_vfnmsub_vv_f32m2 : Vector_Vector_Vector_f32m2;
  def int_riscv_vfnmsub_vv_f32m4 : Vector_Vector_Vector_f32m4;
  def int_riscv_vfnmsub_vv_f32m8 : Vector_Vector_Vector_f32m8;
  
  def int_riscv_vfnmsub_vf_f32m1 : Vector_Vector_float_f32m1;
  def int_riscv_vfnmsub_vf_f32m2 : Vector_Vector_float_f32m2;
  def int_riscv_vfnmsub_vf_f32m4 : Vector_Vector_float_f32m4;
  def int_riscv_vfnmsub_vf_f32m8 : Vector_Vector_float_f32m8; 

//madked   
  def int_riscv_vfmacc_vv_f32m1_m : Vector_Vector_Vector_f32m1_m;
  def int_riscv_vfmacc_vv_f32m2_m : Vector_Vector_Vector_f32m2_m;
  def int_riscv_vfmacc_vv_f32m4_m : Vector_Vector_Vector_f32m4_m;
  def int_riscv_vfmacc_vv_f32m8_m : Vector_Vector_Vector_f32m8_m;
  
  def int_riscv_vfmacc_vf_f32m1_m : Vector_Vector_float_f32m1_m;
  def int_riscv_vfmacc_vf_f32m2_m : Vector_Vector_float_f32m2_m;
  def int_riscv_vfmacc_vf_f32m4_m : Vector_Vector_float_f32m4_m;
  def int_riscv_vfmacc_vf_f32m8_m : Vector_Vector_float_f32m8_m; 
  
  def int_riscv_vfnmacc_vv_f32m1_m : Vector_Vector_Vector_f32m1_m;
  def int_riscv_vfnmacc_vv_f32m2_m : Vector_Vector_Vector_f32m2_m;
  def int_riscv_vfnmacc_vv_f32m4_m : Vector_Vector_Vector_f32m4_m;
  def int_riscv_vfnmacc_vv_f32m8_m : Vector_Vector_Vector_f32m8_m;
  
  def int_riscv_vfnmacc_vf_f32m1_m : Vector_Vector_float_f32m1_m;
  def int_riscv_vfnmacc_vf_f32m2_m : Vector_Vector_float_f32m2_m;
  def int_riscv_vfnmacc_vf_f32m4_m : Vector_Vector_float_f32m4_m;
  def int_riscv_vfnmacc_vf_f32m8_m : Vector_Vector_float_f32m8_m;
  
  def int_riscv_vfmsac_vv_f32m1_m : Vector_Vector_Vector_f32m1_m;
  def int_riscv_vfmsac_vv_f32m2_m : Vector_Vector_Vector_f32m2_m;
  def int_riscv_vfmsac_vv_f32m4_m : Vector_Vector_Vector_f32m4_m;
  def int_riscv_vfmsac_vv_f32m8_m : Vector_Vector_Vector_f32m8_m;
  
  def int_riscv_vfmsac_vf_f32m1_m : Vector_Vector_float_f32m1_m;
  def int_riscv_vfmsac_vf_f32m2_m : Vector_Vector_float_f32m2_m;
  def int_riscv_vfmsac_vf_f32m4_m : Vector_Vector_float_f32m4_m;
  def int_riscv_vfmsac_vf_f32m8_m : Vector_Vector_float_f32m8_m;  
  
  def int_riscv_vfnmsac_vv_f32m1_m : Vector_Vector_Vector_f32m1_m;
  def int_riscv_vfnmsac_vv_f32m2_m : Vector_Vector_Vector_f32m2_m;
  def int_riscv_vfnmsac_vv_f32m4_m : Vector_Vector_Vector_f32m4_m;
  def int_riscv_vfnmsac_vv_f32m8_m : Vector_Vector_Vector_f32m8_m;
  
  def int_riscv_vfnmsac_vf_f32m1_m : Vector_Vector_float_f32m1_m;
  def int_riscv_vfnmsac_vf_f32m2_m : Vector_Vector_float_f32m2_m;
  def int_riscv_vfnmsac_vf_f32m4_m : Vector_Vector_float_f32m4_m;
  def int_riscv_vfnmsac_vf_f32m8_m : Vector_Vector_float_f32m8_m;

  def int_riscv_vfmadd_vv_f32m1_m : Vector_Vector_Vector_f32m1_m;
  def int_riscv_vfmadd_vv_f32m2_m : Vector_Vector_Vector_f32m2_m;
  def int_riscv_vfmadd_vv_f32m4_m : Vector_Vector_Vector_f32m4_m;
  def int_riscv_vfmadd_vv_f32m8_m : Vector_Vector_Vector_f32m8_m;
  
  def int_riscv_vfmadd_vf_f32m1_m : Vector_Vector_float_f32m1_m;
  def int_riscv_vfmadd_vf_f32m2_m : Vector_Vector_float_f32m2_m;
  def int_riscv_vfmadd_vf_f32m4_m : Vector_Vector_float_f32m4_m;
  def int_riscv_vfmadd_vf_f32m8_m : Vector_Vector_float_f32m8_m;
 
  def int_riscv_vfnmadd_vv_f32m1_m : Vector_Vector_Vector_f32m1_m;
  def int_riscv_vfnmadd_vv_f32m2_m : Vector_Vector_Vector_f32m2_m;
  def int_riscv_vfnmadd_vv_f32m4_m : Vector_Vector_Vector_f32m4_m;
  def int_riscv_vfnmadd_vv_f32m8_m : Vector_Vector_Vector_f32m8_m;
  
  def int_riscv_vfnmadd_vf_f32m1_m : Vector_Vector_float_f32m1_m;
  def int_riscv_vfnmadd_vf_f32m2_m : Vector_Vector_float_f32m2_m;
  def int_riscv_vfnmadd_vf_f32m4_m : Vector_Vector_float_f32m4_m;
  def int_riscv_vfnmadd_vf_f32m8_m : Vector_Vector_float_f32m8_m; 
  
  def int_riscv_vfmsub_vv_f32m1_m : Vector_Vector_Vector_f32m1_m;
  def int_riscv_vfmsub_vv_f32m2_m : Vector_Vector_Vector_f32m2_m;
  def int_riscv_vfmsub_vv_f32m4_m : Vector_Vector_Vector_f32m4_m;
  def int_riscv_vfmsub_vv_f32m8_m : Vector_Vector_Vector_f32m8_m;
  
  def int_riscv_vfmsub_vf_f32m1_m : Vector_Vector_float_f32m1_m;
  def int_riscv_vfmsub_vf_f32m2_m : Vector_Vector_float_f32m2_m;
  def int_riscv_vfmsub_vf_f32m4_m : Vector_Vector_float_f32m4_m;
  def int_riscv_vfmsub_vf_f32m8_m : Vector_Vector_float_f32m8_m; 
  
  def int_riscv_vfnmsub_vv_f32m1_m : Vector_Vector_Vector_f32m1_m;
  def int_riscv_vfnmsub_vv_f32m2_m : Vector_Vector_Vector_f32m2_m;
  def int_riscv_vfnmsub_vv_f32m4_m : Vector_Vector_Vector_f32m4_m;
  def int_riscv_vfnmsub_vv_f32m8_m : Vector_Vector_Vector_f32m8_m;
  
  def int_riscv_vfnmsub_vf_f32m1_m : Vector_Vector_float_f32m1_m;
  def int_riscv_vfnmsub_vf_f32m2_m : Vector_Vector_float_f32m2_m;
  def int_riscv_vfnmsub_vf_f32m4_m : Vector_Vector_float_f32m4_m;
  def int_riscv_vfnmsub_vf_f32m8_m : Vector_Vector_float_f32m8_m;   
  
//vector vfsqrt  
  def int_riscv_vfsqrt_v_f32m1 : Vector_f32m1;
  def int_riscv_vfsqrt_v_f32m2 : Vector_f32m2;
  def int_riscv_vfsqrt_v_f32m4 : Vector_f32m4;
  def int_riscv_vfsqrt_v_f32m8 : Vector_f32m8;  
//masked 
  def int_riscv_vfsqrt_v_f32m1_m : Vector_f32m1_m;
  def int_riscv_vfsqrt_v_f32m2_m : Vector_f32m2_m;
  def int_riscv_vfsqrt_v_f32m4_m : Vector_f32m4_m;
  def int_riscv_vfsqrt_v_f32m8_m : Vector_f32m8_m;  

  
//vector vfmin/vfmax
  def int_riscv_vfmin_vv_f32m1 : Vector_Vector_f32m1;
  def int_riscv_vfmin_vv_f32m2 : Vector_Vector_f32m2;
  def int_riscv_vfmin_vv_f32m4 : Vector_Vector_f32m4;
  def int_riscv_vfmin_vv_f32m8 : Vector_Vector_f32m8;
  
  def int_riscv_vfmin_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfmin_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfmin_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfmin_vf_f32m8 : Vector_float_f32m8;
  
  def int_riscv_vfmax_vv_f32m1 : Vector_Vector_f32m1;
  def int_riscv_vfmax_vv_f32m2 : Vector_Vector_f32m2;
  def int_riscv_vfmax_vv_f32m4 : Vector_Vector_f32m4;
  def int_riscv_vfmax_vv_f32m8 : Vector_Vector_f32m8;
  
  def int_riscv_vfmax_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfmax_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfmax_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfmax_vf_f32m8 : Vector_float_f32m8;
  
//masked 
  def int_riscv_vfmin_vv_f32m1_m : Vector_Vector_f32m1_m;
  def int_riscv_vfmin_vv_f32m2_m : Vector_Vector_f32m2_m;
  def int_riscv_vfmin_vv_f32m4_m : Vector_Vector_f32m4_m;
  def int_riscv_vfmin_vv_f32m8_m : Vector_Vector_f32m8_m;
  
  def int_riscv_vfmin_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfmin_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfmin_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfmin_vf_f32m8_m : Vector_float_f32m8_m;
  
  def int_riscv_vfmax_vv_f32m1_m : Vector_Vector_f32m1_m;
  def int_riscv_vfmax_vv_f32m2_m : Vector_Vector_f32m2_m;
  def int_riscv_vfmax_vv_f32m4_m : Vector_Vector_f32m4_m;
  def int_riscv_vfmax_vv_f32m8_m : Vector_Vector_f32m8_m;
  
  def int_riscv_vfmax_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfmax_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfmax_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfmax_vf_f32m8_m : Vector_float_f32m8_m;  
  
 //vector sign-injection 
  def int_riscv_vfsgnj_vv_f32m1 : Vector_Vector_f32m1;
  def int_riscv_vfsgnj_vv_f32m2 : Vector_Vector_f32m2;
  def int_riscv_vfsgnj_vv_f32m4 : Vector_Vector_f32m4;
  def int_riscv_vfsgnj_vv_f32m8 : Vector_Vector_f32m8;
  
  def int_riscv_vfsgnj_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfsgnj_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfsgnj_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfsgnj_vf_f32m8 : Vector_float_f32m8;
  
  def int_riscv_vfsgnjn_vv_f32m1 : Vector_Vector_f32m1;
  def int_riscv_vfsgnjn_vv_f32m2 : Vector_Vector_f32m2;
  def int_riscv_vfsgnjn_vv_f32m4 : Vector_Vector_f32m4;
  def int_riscv_vfsgnjn_vv_f32m8 : Vector_Vector_f32m8;
  
  def int_riscv_vfsgnjn_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfsgnjn_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfsgnjn_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfsgnjn_vf_f32m8 : Vector_float_f32m8;
  
  def int_riscv_vfsgnjx_vv_f32m1 : Vector_Vector_f32m1;
  def int_riscv_vfsgnjx_vv_f32m2 : Vector_Vector_f32m2;
  def int_riscv_vfsgnjx_vv_f32m4 : Vector_Vector_f32m4;
  def int_riscv_vfsgnjx_vv_f32m8 : Vector_Vector_f32m8;
  
  def int_riscv_vfsgnjx_vf_f32m1 : Vector_float_f32m1;
  def int_riscv_vfsgnjx_vf_f32m2 : Vector_float_f32m2;
  def int_riscv_vfsgnjx_vf_f32m4 : Vector_float_f32m4;
  def int_riscv_vfsgnjx_vf_f32m8 : Vector_float_f32m8; 
   
//masked 
  def int_riscv_vfsgnj_vv_f32m1_m : Vector_Vector_f32m1_m;
  def int_riscv_vfsgnj_vv_f32m2_m : Vector_Vector_f32m2_m;
  def int_riscv_vfsgnj_vv_f32m4_m : Vector_Vector_f32m4_m;
  def int_riscv_vfsgnj_vv_f32m8_m : Vector_Vector_f32m8_m;
  
  def int_riscv_vfsgnj_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfsgnj_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfsgnj_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfsgnj_vf_f32m8_m : Vector_float_f32m8_m;
  
  def int_riscv_vfsgnjn_vv_f32m1_m : Vector_Vector_f32m1_m;
  def int_riscv_vfsgnjn_vv_f32m2_m : Vector_Vector_f32m2_m;
  def int_riscv_vfsgnjn_vv_f32m4_m : Vector_Vector_f32m4_m;
  def int_riscv_vfsgnjn_vv_f32m8_m : Vector_Vector_f32m8_m;
  
  def int_riscv_vfsgnjn_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfsgnjn_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfsgnjn_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfsgnjn_vf_f32m8_m : Vector_float_f32m8_m;
 
  def int_riscv_vfsgnjx_vv_f32m1_m : Vector_Vector_f32m1_m;
  def int_riscv_vfsgnjx_vv_f32m2_m : Vector_Vector_f32m2_m;
  def int_riscv_vfsgnjx_vv_f32m4_m : Vector_Vector_f32m4_m;
  def int_riscv_vfsgnjx_vv_f32m8_m : Vector_Vector_f32m8_m;
  
  def int_riscv_vfsgnjx_vf_f32m1_m : Vector_float_f32m1_m;
  def int_riscv_vfsgnjx_vf_f32m2_m : Vector_float_f32m2_m;
  def int_riscv_vfsgnjx_vf_f32m4_m : Vector_float_f32m4_m;
  def int_riscv_vfsgnjx_vf_f32m8_m : Vector_float_f32m8_m;
   
//vector compare
  
  def int_riscv_vmfeq_vv_f32m1 : Vector_Vector_Compare_f32m1;
  def int_riscv_vmfeq_vv_f32m2 : Vector_Vector_Compare_f32m2;
  def int_riscv_vmfeq_vv_f32m4 : Vector_Vector_Compare_f32m4;
  def int_riscv_vmfeq_vv_f32m8 : Vector_Vector_Compare_f32m8;
  
  def int_riscv_vmfeq_vf_f32m1 : Vector_float_Compare_f32m1;
  def int_riscv_vmfeq_vf_f32m2 : Vector_float_Compare_f32m2;
  def int_riscv_vmfeq_vf_f32m4 : Vector_float_Compare_f32m4;
  def int_riscv_vmfeq_vf_f32m8 : Vector_float_Compare_f32m8; 
  
  def int_riscv_vmfne_vv_f32m1 : Vector_Vector_Compare_f32m1;
  def int_riscv_vmfne_vv_f32m2 : Vector_Vector_Compare_f32m2;
  def int_riscv_vmfne_vv_f32m4 : Vector_Vector_Compare_f32m4;
  def int_riscv_vmfne_vv_f32m8 : Vector_Vector_Compare_f32m8;
  
  def int_riscv_vmfne_vf_f32m1 : Vector_float_Compare_f32m1;
  def int_riscv_vmfne_vf_f32m2 : Vector_float_Compare_f32m2;
  def int_riscv_vmfne_vf_f32m4 : Vector_float_Compare_f32m4;
  def int_riscv_vmfne_vf_f32m8 : Vector_float_Compare_f32m8;
  
  def int_riscv_vmflt_vv_f32m1 : Vector_Vector_Compare_f32m1;
  def int_riscv_vmflt_vv_f32m2 : Vector_Vector_Compare_f32m2;
  def int_riscv_vmflt_vv_f32m4 : Vector_Vector_Compare_f32m4;
  def int_riscv_vmflt_vv_f32m8 : Vector_Vector_Compare_f32m8;
  
  def int_riscv_vmflt_vf_f32m1 : Vector_float_Compare_f32m1;
  def int_riscv_vmflt_vf_f32m2 : Vector_float_Compare_f32m2;
  def int_riscv_vmflt_vf_f32m4 : Vector_float_Compare_f32m4;
  def int_riscv_vmflt_vf_f32m8 : Vector_float_Compare_f32m8;
  
  def int_riscv_vmfle_vv_f32m1 : Vector_Vector_Compare_f32m1;
  def int_riscv_vmfle_vv_f32m2 : Vector_Vector_Compare_f32m2;
  def int_riscv_vmfle_vv_f32m4 : Vector_Vector_Compare_f32m4;
  def int_riscv_vmfle_vv_f32m8 : Vector_Vector_Compare_f32m8;
  
  def int_riscv_vmfle_vf_f32m1 : Vector_float_Compare_f32m1;
  def int_riscv_vmfle_vf_f32m2 : Vector_float_Compare_f32m2;
  def int_riscv_vmfle_vf_f32m4 : Vector_float_Compare_f32m4;
  def int_riscv_vmfle_vf_f32m8 : Vector_float_Compare_f32m8;
  
  def int_riscv_vmfgt_vf_f32m1 : Vector_float_Compare_f32m1;
  def int_riscv_vmfgt_vf_f32m2 : Vector_float_Compare_f32m2;
  def int_riscv_vmfgt_vf_f32m4 : Vector_float_Compare_f32m4;
  def int_riscv_vmfgt_vf_f32m8 : Vector_float_Compare_f32m8;

  def int_riscv_vmfge_vf_f32m1 : Vector_float_Compare_f32m1;
  def int_riscv_vmfge_vf_f32m2 : Vector_float_Compare_f32m2;
  def int_riscv_vmfge_vf_f32m4 : Vector_float_Compare_f32m4;
  def int_riscv_vmfge_vf_f32m8 : Vector_float_Compare_f32m8;
     
//masked
  def int_riscv_vmfeq_vv_f32m1_m : Vector_Vector_Compare_f32m1_m;
  def int_riscv_vmfeq_vv_f32m2_m : Vector_Vector_Compare_f32m2_m;
  def int_riscv_vmfeq_vv_f32m4_m : Vector_Vector_Compare_f32m4_m;
  def int_riscv_vmfeq_vv_f32m8_m : Vector_Vector_Compare_f32m8_m;
  
  def int_riscv_vmfeq_vf_f32m1_m : Vector_float_Compare_f32m1_m;
  def int_riscv_vmfeq_vf_f32m2_m : Vector_float_Compare_f32m2_m;
  def int_riscv_vmfeq_vf_f32m4_m : Vector_float_Compare_f32m4_m;
  def int_riscv_vmfeq_vf_f32m8_m : Vector_float_Compare_f32m8_m;
   
  def int_riscv_vmfne_vv_f32m1_m : Vector_Vector_Compare_f32m1_m;
  def int_riscv_vmfne_vv_f32m2_m : Vector_Vector_Compare_f32m2_m;
  def int_riscv_vmfne_vv_f32m4_m : Vector_Vector_Compare_f32m4_m;
  def int_riscv_vmfne_vv_f32m8_m : Vector_Vector_Compare_f32m8_m;
   
  def int_riscv_vmfne_vf_f32m1_m : Vector_float_Compare_f32m1_m;
  def int_riscv_vmfne_vf_f32m2_m : Vector_float_Compare_f32m2_m;
  def int_riscv_vmfne_vf_f32m4_m : Vector_float_Compare_f32m4_m;
  def int_riscv_vmfne_vf_f32m8_m : Vector_float_Compare_f32m8_m;
  
  def int_riscv_vmflt_vv_f32m1_m : Vector_Vector_Compare_f32m1_m;
  def int_riscv_vmflt_vv_f32m2_m : Vector_Vector_Compare_f32m2_m;
  def int_riscv_vmflt_vv_f32m4_m : Vector_Vector_Compare_f32m4_m;
  def int_riscv_vmflt_vv_f32m8_m : Vector_Vector_Compare_f32m8_m;
  
  def int_riscv_vmflt_vf_f32m1_m : Vector_float_Compare_f32m1_m;
  def int_riscv_vmflt_vf_f32m2_m : Vector_float_Compare_f32m2_m;
  def int_riscv_vmflt_vf_f32m4_m : Vector_float_Compare_f32m4_m;
  def int_riscv_vmflt_vf_f32m8_m : Vector_float_Compare_f32m8_m;
  
  def int_riscv_vmfle_vv_f32m1_m : Vector_Vector_Compare_f32m1_m;
  def int_riscv_vmfle_vv_f32m2_m : Vector_Vector_Compare_f32m2_m;
  def int_riscv_vmfle_vv_f32m4_m : Vector_Vector_Compare_f32m4_m;
  def int_riscv_vmfle_vv_f32m8_m : Vector_Vector_Compare_f32m8_m;
  
  def int_riscv_vmfle_vf_f32m1_m : Vector_float_Compare_f32m1_m;
  def int_riscv_vmfle_vf_f32m2_m : Vector_float_Compare_f32m2_m;
  def int_riscv_vmfle_vf_f32m4_m : Vector_float_Compare_f32m4_m;
  def int_riscv_vmfle_vf_f32m8_m : Vector_float_Compare_f32m8_m;
  
  def int_riscv_vmfgt_vf_f32m1_m : Vector_float_Compare_f32m1_m;
  def int_riscv_vmfgt_vf_f32m2_m : Vector_float_Compare_f32m2_m;
  def int_riscv_vmfgt_vf_f32m4_m : Vector_float_Compare_f32m4_m;
  def int_riscv_vmfgt_vf_f32m8_m : Vector_float_Compare_f32m8_m;

  def int_riscv_vmfge_vf_f32m1_m : Vector_float_Compare_f32m1_m;
  def int_riscv_vmfge_vf_f32m2_m : Vector_float_Compare_f32m2_m;
  def int_riscv_vmfge_vf_f32m4_m : Vector_float_Compare_f32m4_m;
  def int_riscv_vmfge_vf_f32m8_m : Vector_float_Compare_f32m8_m;
  
//vfclass
  def int_riscv_vfclass_v_f32m1 : Int_Vector_f32m1;
  def int_riscv_vfclass_v_f32m2 : Int_Vector_f32m2;
  def int_riscv_vfclass_v_f32m4 : Int_Vector_f32m4;
  def int_riscv_vfclass_v_f32m8 : Int_Vector_f32m8;   

//masked 
  def int_riscv_vfclass_v_f32m1_m : Int_Vector_f32m1_m;
  def int_riscv_vfclass_v_f32m2_m : Int_Vector_f32m2_m;
  def int_riscv_vfclass_v_f32m4_m : Int_Vector_f32m4_m;
  def int_riscv_vfclass_v_f32m8_m : Int_Vector_f32m8_m;  
  
//vfmerge.vfm
  def int_riscv_vfmerge_vfm_f32m1 : Vector_float_f32m1_m;
  def int_riscv_vfmerge_vfm_f32m2 : Vector_float_f32m2_m;
  def int_riscv_vfmerge_vfm_f32m4 : Vector_float_f32m4_m;
  def int_riscv_vfmerge_vfm_f32m8 : Vector_float_f32m8_m;  
  
//vfmv.v. 
	def int_riscv_vfmv_v_f32m1 : Vector_mov_f32m1;	 
	def int_riscv_vfmv_v_f32m2 : Vector_mov_f32m2;	
	def int_riscv_vfmv_v_f32m4 : Vector_mov_f32m4;	
	def int_riscv_vfmv_v_f32m8 : Vector_mov_f32m8;		
 
//vector type-convert
	def int_riscv_vfcvt_xu_f_v_f32m1 : Vector_integer_and_float_f32m1;
	def int_riscv_vfcvt_xu_f_v_f32m2 : Vector_integer_and_float_f32m2;  
	def int_riscv_vfcvt_xu_f_v_f32m4 : Vector_integer_and_float_f32m4;  
	def int_riscv_vfcvt_xu_f_v_f32m8 : Vector_integer_and_float_f32m8;  

	def int_riscv_vfcvt_x_f_v_f32m1 : Vector_integer_and_float_f32m1;
	def int_riscv_vfcvt_x_f_v_f32m2 : Vector_integer_and_float_f32m2;  
	def int_riscv_vfcvt_x_f_v_f32m4 : Vector_integer_and_float_f32m4;  
	def int_riscv_vfcvt_x_f_v_f32m8 : Vector_integer_and_float_f32m8;  

	def int_riscv_vfcvt_f_xu_v_u32m1 : Vector_float_and_integer_u32m1;  
	def int_riscv_vfcvt_f_xu_v_u32m2 : Vector_float_and_integer_u32m2;    
	def int_riscv_vfcvt_f_xu_v_u32m4 : Vector_float_and_integer_u32m4;   
	def int_riscv_vfcvt_f_xu_v_u32m8 : Vector_float_and_integer_u32m8;  

	def int_riscv_vfcvt_f_x_v_i32m1 : Vector_float_and_integer_i32m1;  
	def int_riscv_vfcvt_f_x_v_i32m2 : Vector_float_and_integer_i32m2;    
	def int_riscv_vfcvt_f_x_v_i32m4 : Vector_float_and_integer_i32m4;   
	def int_riscv_vfcvt_f_x_v_i32m8 : Vector_float_and_integer_i32m8;	
	
//masked 	
	def int_riscv_vfcvt_xu_f_v_f32m1_m : Vector_integer_and_float_f32m1_m;
	def int_riscv_vfcvt_xu_f_v_f32m2_m : Vector_integer_and_float_f32m2_m;  
	def int_riscv_vfcvt_xu_f_v_f32m4_m : Vector_integer_and_float_f32m4_m;  
	def int_riscv_vfcvt_xu_f_v_f32m8_m : Vector_integer_and_float_f32m8_m;  

	def int_riscv_vfcvt_x_f_v_f32m1_m : Vector_integer_and_float_f32m1_m;
	def int_riscv_vfcvt_x_f_v_f32m2_m : Vector_integer_and_float_f32m2_m;  
	def int_riscv_vfcvt_x_f_v_f32m4_m : Vector_integer_and_float_f32m4_m;  
	def int_riscv_vfcvt_x_f_v_f32m8_m : Vector_integer_and_float_f32m8_m;  

	def int_riscv_vfcvt_f_xu_v_u32m1_m : Vector_float_and_integer_u32m1_m;  
	def int_riscv_vfcvt_f_xu_v_u32m2_m : Vector_float_and_integer_u32m2_m;    
	def int_riscv_vfcvt_f_xu_v_u32m4_m : Vector_float_and_integer_u32m4_m;   
	def int_riscv_vfcvt_f_xu_v_u32m8_m : Vector_float_and_integer_u32m8_m;  

	def int_riscv_vfcvt_f_x_v_i32m1_m : Vector_float_and_integer_i32m1_m;  
	def int_riscv_vfcvt_f_x_v_i32m2_m : Vector_float_and_integer_i32m2_m;    
	def int_riscv_vfcvt_f_x_v_i32m4_m : Vector_float_and_integer_i32m4_m;   
	def int_riscv_vfcvt_f_x_v_i32m8_m : Vector_float_and_integer_i32m8_m;	
	
//vector widening type-convert			

	def int_riscv_vfwcvt_f_xu_v_u16m1 : Intrinsic<[llvm_v8f32_ty],[llvm_v8i16_ty],[IntrNoMem]>;
	def int_riscv_vfwcvt_f_xu_v_u16m2 : Intrinsic<[llvm_v16f32_ty],[llvm_v16i16_ty],[IntrNoMem]>;
	def int_riscv_vfwcvt_f_xu_v_u16m4 : Intrinsic<[llvm_v32f32_ty],[llvm_v32i16_ty],[IntrNoMem]>;

	def int_riscv_vfwcvt_f_x_v_i16m1 : Intrinsic<[llvm_v8f32_ty],[llvm_v8i16_ty],[IntrNoMem]>;
	def int_riscv_vfwcvt_f_x_v_i16m2 : Intrinsic<[llvm_v16f32_ty],[llvm_v16i16_ty],[IntrNoMem]>;
	def int_riscv_vfwcvt_f_x_v_i16m4 : Intrinsic<[llvm_v32f32_ty],[llvm_v32i16_ty],[IntrNoMem]>;	
	
//masked		
	def int_riscv_vfwcvt_f_xu_v_u16m1_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8i16_ty],[IntrNoMem]>;
	def int_riscv_vfwcvt_f_xu_v_u16m2_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16i16_ty],[IntrNoMem]>;
	def int_riscv_vfwcvt_f_xu_v_u16m4_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32i16_ty],[IntrNoMem]>;

	def int_riscv_vfwcvt_f_x_v_i16m1_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8i16_ty],[IntrNoMem]>;
	def int_riscv_vfwcvt_f_x_v_i16m2_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16i16_ty],[IntrNoMem]>;
	def int_riscv_vfwcvt_f_x_v_i16m4_m : Intrinsic<[llvm_v32f32_ty],[llvm_v16i8_ty,llvm_v32i16_ty],[IntrNoMem]>;	

//vector narrowing type-convert		
	def int_riscv_vfncvt_xu_f_w_f32m2 : Intrinsic<[llvm_v8i16_ty],[llvm_v8f32_ty],[IntrNoMem]>;
	def int_riscv_vfncvt_xu_f_w_f32m4 : Intrinsic<[llvm_v16i16_ty],[llvm_v16f32_ty],[IntrNoMem]>;	
	def int_riscv_vfncvt_xu_f_w_f32m8 : Intrinsic<[llvm_v32i16_ty],[llvm_v32f32_ty],[IntrNoMem]>;
	
	def int_riscv_vfncvt_x_f_w_f32m2 : Intrinsic<[llvm_v8i16_ty],[llvm_v8f32_ty],[IntrNoMem]>;
	def int_riscv_vfncvt_x_f_w_f32m4 : Intrinsic<[llvm_v16i16_ty],[llvm_v16f32_ty],[IntrNoMem]>;	
	def int_riscv_vfncvt_x_f_w_f32m8 : Intrinsic<[llvm_v32i16_ty],[llvm_v32f32_ty],[IntrNoMem]>;
	
//masked
	def int_riscv_vfncvt_xu_f_w_f32m2_m : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8f32_ty],[IntrNoMem]>;
	def int_riscv_vfncvt_xu_f_w_f32m4_m : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16f32_ty],[IntrNoMem]>;	
	def int_riscv_vfncvt_xu_f_w_f32m8_m : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32f32_ty],[IntrNoMem]>;
	
	def int_riscv_vfncvt_x_f_w_f32m2_m : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty,llvm_v8f32_ty],[IntrNoMem]>;
	def int_riscv_vfncvt_x_f_w_f32m4_m : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16f32_ty],[IntrNoMem]>;	
	def int_riscv_vfncvt_x_f_w_f32m8_m : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32f32_ty],[IntrNoMem]>;
			
	def int_riscv_vfncvt_f_xu_w_u64m2_m : Intrinsic<[llvm_v4f32_ty],[llvm_v16i8_ty,llvm_v4i64_ty],[IntrNoMem]>;
	def int_riscv_vfncvt_f_xu_w_u64m4_m : Intrinsic<[llvm_v8f32_ty],[llvm_v16i8_ty,llvm_v8i64_ty],[IntrNoMem]>;
	def int_riscv_vfncvt_f_xu_w_u64m8_m : Intrinsic<[llvm_v16f32_ty],[llvm_v16i8_ty,llvm_v16i64_ty],[IntrNoMem]>;
	
//vector 	vredsum.vs
	def int_riscv_vredsum_vs_8m1 : Vector_Vector_v8m1;
	def int_riscv_vredsum_vs_8m2 : Vector_Vector_v8m2;	
	def int_riscv_vredsum_vs_8m4 : Vector_Vector_v8m4;	
	def int_riscv_vredsum_vs_8m8 : Vector_Vector_v8m8;		
	
	def int_riscv_vredsum_vs_16m1 : Vector_Vector_v16m1;
	def int_riscv_vredsum_vs_16m2 : Vector_Vector_v16m2;	
	def int_riscv_vredsum_vs_16m4 : Vector_Vector_v16m4;	
	def int_riscv_vredsum_vs_16m8 : Vector_Vector_v16m8;	

	def int_riscv_vredsum_vs_32m1 : Vector_Vector_v32m1;
	def int_riscv_vredsum_vs_32m2 : Vector_Vector_v32m2;	
	def int_riscv_vredsum_vs_32m4 : Vector_Vector_v32m4;	
	def int_riscv_vredsum_vs_32m8 : Vector_Vector_v32m8;			
	
	def int_riscv_vredand_vs_8m1 : Vector_Vector_v8m1;
	def int_riscv_vredand_vs_8m2 : Vector_Vector_v8m2;	
	def int_riscv_vredand_vs_8m4 : Vector_Vector_v8m4;	
	def int_riscv_vredand_vs_8m8 : Vector_Vector_v8m8;		
	
	def int_riscv_vredand_vs_16m1 : Vector_Vector_v16m1;
	def int_riscv_vredand_vs_16m2 : Vector_Vector_v16m2;	
	def int_riscv_vredand_vs_16m4 : Vector_Vector_v16m4;	
	def int_riscv_vredand_vs_16m8 : Vector_Vector_v16m8;	

	def int_riscv_vredand_vs_32m1 : Vector_Vector_v32m1;
	def int_riscv_vredand_vs_32m2 : Vector_Vector_v32m2;	
	def int_riscv_vredand_vs_32m4 : Vector_Vector_v32m4;	
	def int_riscv_vredand_vs_32m8 : Vector_Vector_v32m8;			
	
	def int_riscv_vredor_vs_8m1 : Vector_Vector_v8m1;
	def int_riscv_vredor_vs_8m2 : Vector_Vector_v8m2;	
	def int_riscv_vredor_vs_8m4 : Vector_Vector_v8m4;	
	def int_riscv_vredor_vs_8m8 : Vector_Vector_v8m8;		
	
	def int_riscv_vredor_vs_16m1 : Vector_Vector_v16m1;
	def int_riscv_vredor_vs_16m2 : Vector_Vector_v16m2;	
	def int_riscv_vredor_vs_16m4 : Vector_Vector_v16m4;	
	def int_riscv_vredor_vs_16m8 : Vector_Vector_v16m8;	

	def int_riscv_vredor_vs_32m1 : Vector_Vector_v32m1;
	def int_riscv_vredor_vs_32m2 : Vector_Vector_v32m2;	
	def int_riscv_vredor_vs_32m4 : Vector_Vector_v32m4;	
	def int_riscv_vredor_vs_32m8 : Vector_Vector_v32m8;		
	
	def int_riscv_vredxor_vs_8m1 : Vector_Vector_v8m1;
	def int_riscv_vredxor_vs_8m2 : Vector_Vector_v8m2;	
	def int_riscv_vredxor_vs_8m4 : Vector_Vector_v8m4;	
	def int_riscv_vredxor_vs_8m8 : Vector_Vector_v8m8;		
	
	def int_riscv_vredxor_vs_16m1 : Vector_Vector_v16m1;
	def int_riscv_vredxor_vs_16m2 : Vector_Vector_v16m2;	
	def int_riscv_vredxor_vs_16m4 : Vector_Vector_v16m4;	
	def int_riscv_vredxor_vs_16m8 : Vector_Vector_v16m8;	

	def int_riscv_vredxor_vs_32m1 : Vector_Vector_v32m1;
	def int_riscv_vredxor_vs_32m2 : Vector_Vector_v32m2;	
	def int_riscv_vredxor_vs_32m4 : Vector_Vector_v32m4;	
	def int_riscv_vredxor_vs_32m8 : Vector_Vector_v32m8;				
	
	def int_riscv_vredmaxu_vs_u8m1 : Vector_Vector_v8m1;
	def int_riscv_vredmaxu_vs_u8m2 : Vector_Vector_v8m2;	
	def int_riscv_vredmaxu_vs_u8m4 : Vector_Vector_v8m4;	
	def int_riscv_vredmaxu_vs_u8m8 : Vector_Vector_v8m8;		
	
	def int_riscv_vredmaxu_vs_u16m1 : Vector_Vector_v16m1;
	def int_riscv_vredmaxu_vs_u16m2 : Vector_Vector_v16m2;	
	def int_riscv_vredmaxu_vs_u16m4 : Vector_Vector_v16m4;	
	def int_riscv_vredmaxu_vs_u16m8 : Vector_Vector_v16m8;	

	def int_riscv_vredmaxu_vs_u32m1 : Vector_Vector_v32m1;
	def int_riscv_vredmaxu_vs_u32m2 : Vector_Vector_v32m2;	
	def int_riscv_vredmaxu_vs_u32m4 : Vector_Vector_v32m4;	
	def int_riscv_vredmaxu_vs_u32m8 : Vector_Vector_v32m8;		
	
	def int_riscv_vredmax_vs_i8m1 : Vector_Vector_v8m1;
	def int_riscv_vredmax_vs_i8m2 : Vector_Vector_v8m2;	
	def int_riscv_vredmax_vs_i8m4 : Vector_Vector_v8m4;	
	def int_riscv_vredmax_vs_i8m8 : Vector_Vector_v8m8;		
	
	def int_riscv_vredmax_vs_i16m1 : Vector_Vector_v16m1;
	def int_riscv_vredmax_vs_i16m2 : Vector_Vector_v16m2;	
	def int_riscv_vredmax_vs_i16m4 : Vector_Vector_v16m4;	
	def int_riscv_vredmax_vs_i16m8 : Vector_Vector_v16m8;	

	def int_riscv_vredmax_vs_i32m1 : Vector_Vector_v32m1;
	def int_riscv_vredmax_vs_i32m2 : Vector_Vector_v32m2;	
	def int_riscv_vredmax_vs_i32m4 : Vector_Vector_v32m4;	
	def int_riscv_vredmax_vs_i32m8 : Vector_Vector_v32m8;				

	def int_riscv_vredminu_vs_u8m1 : Vector_Vector_v8m1;
	def int_riscv_vredminu_vs_u8m2 : Vector_Vector_v8m2;	
	def int_riscv_vredminu_vs_u8m4 : Vector_Vector_v8m4;	
	def int_riscv_vredminu_vs_u8m8 : Vector_Vector_v8m8;		
	
	def int_riscv_vredminu_vs_u16m1 : Vector_Vector_v16m1;
	def int_riscv_vredminu_vs_u16m2 : Vector_Vector_v16m2;	
	def int_riscv_vredminu_vs_u16m4 : Vector_Vector_v16m4;	
	def int_riscv_vredminu_vs_u16m8 : Vector_Vector_v16m8;	

	def int_riscv_vredminu_vs_u32m1 : Vector_Vector_v32m1;
	def int_riscv_vredminu_vs_u32m2 : Vector_Vector_v32m2;	
	def int_riscv_vredminu_vs_u32m4 : Vector_Vector_v32m4;	
	def int_riscv_vredminu_vs_u32m8 : Vector_Vector_v32m8;		
	
	def int_riscv_vredmin_vs_i8m1 : Vector_Vector_v8m1;
	def int_riscv_vredmin_vs_i8m2 : Vector_Vector_v8m2;	
	def int_riscv_vredmin_vs_i8m4 : Vector_Vector_v8m4;	
	def int_riscv_vredmin_vs_i8m8 : Vector_Vector_v8m8;		
	
	def int_riscv_vredmin_vs_i16m1 : Vector_Vector_v16m1;
	def int_riscv_vredmin_vs_i16m2 : Vector_Vector_v16m2;	
	def int_riscv_vredmin_vs_i16m4 : Vector_Vector_v16m4;	
	def int_riscv_vredmin_vs_i16m8 : Vector_Vector_v16m8;	

	def int_riscv_vredmin_vs_i32m1 : Vector_Vector_v32m1;
	def int_riscv_vredmin_vs_i32m2 : Vector_Vector_v32m2;	
	def int_riscv_vredmin_vs_i32m4 : Vector_Vector_v32m4;	
	def int_riscv_vredmin_vs_i32m8 : Vector_Vector_v32m8;		
	
//masked
	def int_riscv_vredsum_vs_8m1_m : Vector_Vector_v8m1_m;
	def int_riscv_vredsum_vs_8m2_m : Vector_Vector_v8m2_m;	
	def int_riscv_vredsum_vs_8m4_m : Vector_Vector_v8m4_m;	
	def int_riscv_vredsum_vs_8m8_m : Vector_Vector_v8m8_m;		
	
	def int_riscv_vredsum_vs_16m1_m : Vector_Vector_v16m1_m;
	def int_riscv_vredsum_vs_16m2_m : Vector_Vector_v16m2_m;	
	def int_riscv_vredsum_vs_16m4_m : Vector_Vector_v16m4_m;	
	def int_riscv_vredsum_vs_16m8_m : Vector_Vector_v16m8_m;	

	def int_riscv_vredsum_vs_32m1_m : Vector_Vector_v32m1_m;
	def int_riscv_vredsum_vs_32m2_m : Vector_Vector_v32m2_m;	
	def int_riscv_vredsum_vs_32m4_m : Vector_Vector_v32m4_m;	
	def int_riscv_vredsum_vs_32m8_m : Vector_Vector_v32m8_m;			
	
	def int_riscv_vredand_vs_8m1_m : Vector_Vector_v8m1_m;
	def int_riscv_vredand_vs_8m2_m : Vector_Vector_v8m2_m;	
	def int_riscv_vredand_vs_8m4_m : Vector_Vector_v8m4_m;	
	def int_riscv_vredand_vs_8m8_m : Vector_Vector_v8m8_m;		
	
	def int_riscv_vredand_vs_16m1_m : Vector_Vector_v16m1_m;
	def int_riscv_vredand_vs_16m2_m : Vector_Vector_v16m2_m;	
	def int_riscv_vredand_vs_16m4_m : Vector_Vector_v16m4_m;	
	def int_riscv_vredand_vs_16m8_m : Vector_Vector_v16m8_m;	

	def int_riscv_vredand_vs_32m1_m : Vector_Vector_v32m1_m;
	def int_riscv_vredand_vs_32m2_m : Vector_Vector_v32m2_m;	
	def int_riscv_vredand_vs_32m4_m : Vector_Vector_v32m4_m;	
	def int_riscv_vredand_vs_32m8_m : Vector_Vector_v32m8_m;		
	
	def int_riscv_vredor_vs_8m1_m : Vector_Vector_v8m1_m;
	def int_riscv_vredor_vs_8m2_m : Vector_Vector_v8m2_m;	
	def int_riscv_vredor_vs_8m4_m : Vector_Vector_v8m4_m;	
	def int_riscv_vredor_vs_8m8_m : Vector_Vector_v8m8_m;		
	
	def int_riscv_vredor_vs_16m1_m : Vector_Vector_v16m1_m;
	def int_riscv_vredor_vs_16m2_m : Vector_Vector_v16m2_m;	
	def int_riscv_vredor_vs_16m4_m : Vector_Vector_v16m4_m;	
	def int_riscv_vredor_vs_16m8_m : Vector_Vector_v16m8_m;	

	def int_riscv_vredor_vs_32m1_m : Vector_Vector_v32m1_m;
	def int_riscv_vredor_vs_32m2_m : Vector_Vector_v32m2_m;	
	def int_riscv_vredor_vs_32m4_m : Vector_Vector_v32m4_m;	
	def int_riscv_vredor_vs_32m8_m : Vector_Vector_v32m8_m;			
	
	def int_riscv_vredxor_vs_8m1_m : Vector_Vector_v8m1_m;
	def int_riscv_vredxor_vs_8m2_m : Vector_Vector_v8m2_m;	
	def int_riscv_vredxor_vs_8m4_m : Vector_Vector_v8m4_m;	
	def int_riscv_vredxor_vs_8m8_m : Vector_Vector_v8m8_m;		
	
	def int_riscv_vredxor_vs_16m1_m : Vector_Vector_v16m1_m;
	def int_riscv_vredxor_vs_16m2_m : Vector_Vector_v16m2_m;	
	def int_riscv_vredxor_vs_16m4_m : Vector_Vector_v16m4_m;	
	def int_riscv_vredxor_vs_16m8_m : Vector_Vector_v16m8_m;	

	def int_riscv_vredxor_vs_32m1_m : Vector_Vector_v32m1_m;
	def int_riscv_vredxor_vs_32m2_m : Vector_Vector_v32m2_m;	
	def int_riscv_vredxor_vs_32m4_m : Vector_Vector_v32m4_m;	
	def int_riscv_vredxor_vs_32m8_m : Vector_Vector_v32m8_m;			
	
	def int_riscv_vredmaxu_vs_u8m1_m : Vector_Vector_v8m1_m;
	def int_riscv_vredmaxu_vs_u8m2_m : Vector_Vector_v8m2_m;	
	def int_riscv_vredmaxu_vs_u8m4_m : Vector_Vector_v8m4_m;	
	def int_riscv_vredmaxu_vs_u8m8_m : Vector_Vector_v8m8_m;		
	
	def int_riscv_vredmaxu_vs_u16m1_m : Vector_Vector_v16m1_m;
	def int_riscv_vredmaxu_vs_u16m2_m : Vector_Vector_v16m2_m;	
	def int_riscv_vredmaxu_vs_u16m4_m : Vector_Vector_v16m4_m;	
	def int_riscv_vredmaxu_vs_u16m8_m : Vector_Vector_v16m8_m;	

	def int_riscv_vredmaxu_vs_u32m1_m : Vector_Vector_v32m1_m;
	def int_riscv_vredmaxu_vs_u32m2_m : Vector_Vector_v32m2_m;	
	def int_riscv_vredmaxu_vs_u32m4_m : Vector_Vector_v32m4_m;	
	def int_riscv_vredmaxu_vs_u32m8_m : Vector_Vector_v32m8_m;		
	
	def int_riscv_vredmax_vs_i8m1_m : Vector_Vector_v8m1_m;
	def int_riscv_vredmax_vs_i8m2_m : Vector_Vector_v8m2_m;	
	def int_riscv_vredmax_vs_i8m4_m : Vector_Vector_v8m4_m;	
	def int_riscv_vredmax_vs_i8m8_m : Vector_Vector_v8m8_m;		
	
	def int_riscv_vredmax_vs_i16m1_m : Vector_Vector_v16m1_m;
	def int_riscv_vredmax_vs_i16m2_m : Vector_Vector_v16m2_m;	
	def int_riscv_vredmax_vs_i16m4_m : Vector_Vector_v16m4_m;	
	def int_riscv_vredmax_vs_i16m8_m : Vector_Vector_v16m8_m;	

	def int_riscv_vredmax_vs_i32m1_m : Vector_Vector_v32m1_m;
	def int_riscv_vredmax_vs_i32m2_m : Vector_Vector_v32m2_m;	
	def int_riscv_vredmax_vs_i32m4_m : Vector_Vector_v32m4_m;	
	def int_riscv_vredmax_vs_i32m8_m : Vector_Vector_v32m8_m;				

	def int_riscv_vredminu_vs_u8m1_m : Vector_Vector_v8m1_m;
	def int_riscv_vredminu_vs_u8m2_m : Vector_Vector_v8m2_m;	
	def int_riscv_vredminu_vs_u8m4_m : Vector_Vector_v8m4_m;	
	def int_riscv_vredminu_vs_u8m8_m : Vector_Vector_v8m8_m;		
	
	def int_riscv_vredminu_vs_u16m1_m : Vector_Vector_v16m1_m;
	def int_riscv_vredminu_vs_u16m2_m : Vector_Vector_v16m2_m;	
	def int_riscv_vredminu_vs_u16m4_m : Vector_Vector_v16m4_m;	
	def int_riscv_vredminu_vs_u16m8_m : Vector_Vector_v16m8_m;	

	def int_riscv_vredminu_vs_u32m1_m : Vector_Vector_v32m1_m;
	def int_riscv_vredminu_vs_u32m2_m : Vector_Vector_v32m2_m;	
	def int_riscv_vredminu_vs_u32m4_m : Vector_Vector_v32m4_m;	
	def int_riscv_vredminu_vs_u32m8_m : Vector_Vector_v32m8_m;		
	
	def int_riscv_vredmin_vs_i8m1_m : Vector_Vector_v8m1_m;
	def int_riscv_vredmin_vs_i8m2_m : Vector_Vector_v8m2_m;	
	def int_riscv_vredmin_vs_i8m4_m : Vector_Vector_v8m4_m;	
	def int_riscv_vredmin_vs_i8m8_m : Vector_Vector_v8m8_m;		
	
	def int_riscv_vredmin_vs_i16m1_m : Vector_Vector_v16m1_m;
	def int_riscv_vredmin_vs_i16m2_m : Vector_Vector_v16m2_m;	
	def int_riscv_vredmin_vs_i16m4_m : Vector_Vector_v16m4_m;	
	def int_riscv_vredmin_vs_i16m8_m : Vector_Vector_v16m8_m;	

	def int_riscv_vredmin_vs_i32m1_m : Vector_Vector_v32m1_m;
	def int_riscv_vredmin_vs_i32m2_m : Vector_Vector_v32m2_m;	
	def int_riscv_vredmin_vs_i32m4_m : Vector_Vector_v32m4_m;	
	def int_riscv_vredmin_vs_i32m8_m : Vector_Vector_v32m8_m;				

//vector widending vredsum.vs
	def int_riscv_vwredsumu_vs_u8m1 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty],[IntrNoMem]>;	
	def int_riscv_vwredsumu_vs_u8m2 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i8_ty,llvm_v32i16_ty],[IntrNoMem]>;	
	def int_riscv_vwredsumu_vs_u8m4 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i8_ty,llvm_v64i16_ty],[IntrNoMem]>;		
	
	def int_riscv_vwredsumu_vs_u16m1 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i16_ty,llvm_v8i32_ty],[IntrNoMem]>;	
	def int_riscv_vwredsumu_vs_u16m2 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i16_ty,llvm_v16i32_ty],[IntrNoMem]>;	
	def int_riscv_vwredsumu_vs_u16m4 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i16_ty,llvm_v32i32_ty],[IntrNoMem]>;		
	
	def int_riscv_vwredsum_vs_i8m1 : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i16_ty],[IntrNoMem]>;	
	def int_riscv_vwredsum_vs_i8m2 : Intrinsic<[llvm_v32i16_ty],[llvm_v32i8_ty,llvm_v32i16_ty],[IntrNoMem]>;	
	def int_riscv_vwredsum_vs_i8m4 : Intrinsic<[llvm_v64i16_ty],[llvm_v64i8_ty,llvm_v64i16_ty],[IntrNoMem]>;		
	
	def int_riscv_vwredsum_vs_i16m1 : Intrinsic<[llvm_v8i32_ty],[llvm_v8i16_ty,llvm_v8i32_ty],[IntrNoMem]>;	
	def int_riscv_vwredsum_vs_i16m2 : Intrinsic<[llvm_v16i32_ty],[llvm_v16i16_ty,llvm_v16i32_ty],[IntrNoMem]>;	
	def int_riscv_vwredsum_vs_i16m4 : Intrinsic<[llvm_v32i32_ty],[llvm_v32i16_ty,llvm_v32i32_ty],[IntrNoMem]>;	
	
//masked
	def int_riscv_vwredsumu_vs_u8m1_m : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i16_ty],[IntrNoMem]>;	
	def int_riscv_vwredsumu_vs_u8m2_m : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_v32i16_ty],[IntrNoMem]>;	
	def int_riscv_vwredsumu_vs_u8m4_m : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_v64i16_ty],[IntrNoMem]>;		
	
	def int_riscv_vwredsumu_vs_u16m1_m : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_v8i32_ty],[IntrNoMem]>;	
	def int_riscv_vwredsumu_vs_u16m2_m : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_v16i32_ty],[IntrNoMem]>;	
	def int_riscv_vwredsumu_vs_u16m4_m : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_v32i32_ty],[IntrNoMem]>;	

	def int_riscv_vwredsum_vs_i8m1_m : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty,llvm_v16i8_ty,llvm_v16i16_ty],[IntrNoMem]>;	
	def int_riscv_vwredsum_vs_i8m2_m : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty,llvm_v32i8_ty,llvm_v32i16_ty],[IntrNoMem]>;	
	def int_riscv_vwredsum_vs_i8m4_m : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty,llvm_v64i8_ty,llvm_v64i16_ty],[IntrNoMem]>;		
	
	def int_riscv_vwredsum_vs_i16m1_m : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty,llvm_v8i16_ty,llvm_v8i32_ty],[IntrNoMem]>;	
	def int_riscv_vwredsum_vs_i16m2_m : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty,llvm_v16i16_ty,llvm_v16i32_ty],[IntrNoMem]>;	
	def int_riscv_vwredsum_vs_i16m4_m : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty,llvm_v32i16_ty,llvm_v32i32_ty],[IntrNoMem]>;	

	
//vector vfredsum.vs
	def int_riscv_vfredosum_vs_f32m1 : Vector_Vector_f32m1;
	def int_riscv_vfredosum_vs_f32m2 : Vector_Vector_f32m2;
	def int_riscv_vfredosum_vs_f32m4 : Vector_Vector_f32m4;
	def int_riscv_vfredosum_vs_f32m8 : Vector_Vector_f32m8;
	
	def int_riscv_vfredsum_vs_f32m1 : Vector_Vector_f32m1;
	def int_riscv_vfredsum_vs_f32m2 : Vector_Vector_f32m2;
	def int_riscv_vfredsum_vs_f32m4 : Vector_Vector_f32m4;
	def int_riscv_vfredsum_vs_f32m8 : Vector_Vector_f32m8;

	def int_riscv_vfredmax_vs_f32m1 : Vector_Vector_f32m1;
	def int_riscv_vfredmax_vs_f32m2 : Vector_Vector_f32m2;
	def int_riscv_vfredmax_vs_f32m4 : Vector_Vector_f32m4;
	def int_riscv_vfredmax_vs_f32m8 : Vector_Vector_f32m8;
	
	def int_riscv_vfredmin_vs_f32m1 : Vector_Vector_f32m1;
	def int_riscv_vfredmin_vs_f32m2 : Vector_Vector_f32m2;
	def int_riscv_vfredmin_vs_f32m4 : Vector_Vector_f32m4;
	def int_riscv_vfredmin_vs_f32m8 : Vector_Vector_f32m8;
	
//masked	
	def int_riscv_vfredosum_vs_f32m1_m : Vector_Vector_f32m1_m;
	def int_riscv_vfredosum_vs_f32m2_m : Vector_Vector_f32m2_m;
	def int_riscv_vfredosum_vs_f32m4_m : Vector_Vector_f32m4_m;
	def int_riscv_vfredosum_vs_f32m8_m : Vector_Vector_f32m8_m;
	
	def int_riscv_vfredsum_vs_f32m1_m : Vector_Vector_f32m1_m;
	def int_riscv_vfredsum_vs_f32m2_m : Vector_Vector_f32m2_m;
	def int_riscv_vfredsum_vs_f32m4_m : Vector_Vector_f32m4_m;
	def int_riscv_vfredsum_vs_f32m8_m : Vector_Vector_f32m8_m;

	def int_riscv_vfredmax_vs_f32m1_m : Vector_Vector_f32m1_m;
	def int_riscv_vfredmax_vs_f32m2_m : Vector_Vector_f32m2_m;
	def int_riscv_vfredmax_vs_f32m4_m : Vector_Vector_f32m4_m;
	def int_riscv_vfredmax_vs_f32m8_m : Vector_Vector_f32m8_m;
	
	def int_riscv_vfredmin_vs_f32m1_m : Vector_Vector_f32m1_m;
	def int_riscv_vfredmin_vs_f32m2_m : Vector_Vector_f32m2_m;
	def int_riscv_vfredmin_vs_f32m4_m : Vector_Vector_f32m4_m;
	def int_riscv_vfredmin_vs_f32m8_m : Vector_Vector_f32m8_m;
	
//vector mask register
	def int_riscv_vmand_mm :  Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vmnand_mm :  Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vmandnot_mm :  Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vmxor_mm :  Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vmor_mm :  Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
  def int_riscv_vmnor_mm :  Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vmornot_mm :  Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vmxnor_mm :  Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
	
	def int_riscv_vpopc_m : Intrinsic<[llvm_i32_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vpopc_m_m : Intrinsic<[llvm_i32_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;

	def int_riscv_vfirst_m : Intrinsic<[llvm_i32_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vfirst_m_m : Intrinsic<[llvm_i32_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;	

	def int_riscv_vmsbf_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vmsbf_m_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
	
	def int_riscv_vmsif_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vmsif_m_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;
	
	def int_riscv_vmsof_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vmsof_m_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;

	def int_riscv_viota_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_viota_m_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty,llvm_v16i8_ty],[IntrNoMem]>;	
	
//vid.v
	def int_riscv_vid_v_u8m1 : Intrinsic<[llvm_v16i8_ty],[],[IntrNoMem]>;
	def int_riscv_vid_v_u8m2 : Intrinsic<[llvm_v32i8_ty],[],[IntrNoMem]>;
	def int_riscv_vid_v_u8m4 : Intrinsic<[llvm_v64i8_ty],[],[IntrNoMem]>;
	def int_riscv_vid_v_u8m8 : Intrinsic<[llvm_v128i8_ty],[],[IntrNoMem]>;
	
	def int_riscv_vid_v_u16m1 : Intrinsic<[llvm_v8i16_ty],[],[IntrNoMem]>;
	def int_riscv_vid_v_u16m2 : Intrinsic<[llvm_v16i16_ty],[],[IntrNoMem]>;
	def int_riscv_vid_v_u16m4 : Intrinsic<[llvm_v32i16_ty],[],[IntrNoMem]>;
	def int_riscv_vid_v_u16m8 : Intrinsic<[llvm_v64i16_ty],[],[IntrNoMem]>;
	
	def int_riscv_vid_v_u32m1 : Intrinsic<[llvm_v4i32_ty],[],[IntrNoMem]>;
	def int_riscv_vid_v_u32m2 : Intrinsic<[llvm_v8i32_ty],[],[IntrNoMem]>;
	def int_riscv_vid_v_u32m4 : Intrinsic<[llvm_v16i32_ty],[],[IntrNoMem]>;
	def int_riscv_vid_v_u32m8 : Intrinsic<[llvm_v32i32_ty],[],[IntrNoMem]>;	
	
//masked
	def int_riscv_vid_v_u8m1_m : Intrinsic<[llvm_v16i8_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vid_v_u8m2_m : Intrinsic<[llvm_v32i8_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vid_v_u8m4_m : Intrinsic<[llvm_v64i8_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vid_v_u8m8_m : Intrinsic<[llvm_v128i8_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	
	def int_riscv_vid_v_u16m1_m : Intrinsic<[llvm_v8i16_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vid_v_u16m2_m : Intrinsic<[llvm_v16i16_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vid_v_u16m4_m : Intrinsic<[llvm_v32i16_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vid_v_u16m8_m : Intrinsic<[llvm_v64i16_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	
	def int_riscv_vid_v_u32m1_m : Intrinsic<[llvm_v4i32_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vid_v_u32m2_m : Intrinsic<[llvm_v8i32_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vid_v_u32m4_m : Intrinsic<[llvm_v16i32_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vid_v_u32m8_m : Intrinsic<[llvm_v32i32_ty],[llvm_v16i8_ty],[IntrNoMem]>;

//vmv.x.s 
	def int_riscv_vmv_x_s_8m1 : Intrinsic<[llvm_i32_ty],[llvm_v16i8_ty],[IntrNoMem]>;
	def int_riscv_vmv_x_s_8m2 : Intrinsic<[llvm_i32_ty],[llvm_v32i8_ty],[IntrNoMem]>;
	def int_riscv_vmv_x_s_8m4 : Intrinsic<[llvm_i32_ty],[llvm_v64i8_ty],[IntrNoMem]>;
	def int_riscv_vmv_x_s_8m8 : Intrinsic<[llvm_i32_ty],[llvm_v128i8_ty],[IntrNoMem]>;

	def int_riscv_vmv_x_s_16m1 : Intrinsic<[llvm_i32_ty],[llvm_v8i16_ty],[IntrNoMem]>;
	def int_riscv_vmv_x_s_16m2 : Intrinsic<[llvm_i32_ty],[llvm_v16i16_ty],[IntrNoMem]>;
	def int_riscv_vmv_x_s_16m4 : Intrinsic<[llvm_i32_ty],[llvm_v32i16_ty],[IntrNoMem]>;
	def int_riscv_vmv_x_s_16m8 : Intrinsic<[llvm_i32_ty],[llvm_v64i16_ty],[IntrNoMem]>;
	
	def int_riscv_vmv_x_s_32m1 : Intrinsic<[llvm_i32_ty],[llvm_v4i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_x_s_32m2 : Intrinsic<[llvm_i32_ty],[llvm_v8i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_x_s_32m4 : Intrinsic<[llvm_i32_ty],[llvm_v16i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_x_s_32m8 : Intrinsic<[llvm_i32_ty],[llvm_v32i32_ty],[IntrNoMem]>;

//vmv.s.x
	def int_riscv_vmv_s_x_8m1 : Intrinsic<[llvm_v16i8_ty],[llvm_i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_s_x_8m2 : Intrinsic<[llvm_v32i8_ty],[llvm_i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_s_x_8m4 : Intrinsic<[llvm_v64i8_ty],[llvm_i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_s_x_8m8 : Intrinsic<[llvm_v128i8_ty],[llvm_i32_ty],[IntrNoMem]>;

	def int_riscv_vmv_s_x_16m1 : Intrinsic<[llvm_v8i16_ty],[llvm_i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_s_x_16m2 : Intrinsic<[llvm_v16i16_ty],[llvm_i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_s_x_16m4 : Intrinsic<[llvm_v32i16_ty],[llvm_i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_s_x_16m8 : Intrinsic<[llvm_v64i16_ty],[llvm_i32_ty],[IntrNoMem]>;

	def int_riscv_vmv_s_x_32m1 : Intrinsic<[llvm_v4i32_ty],[llvm_i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_s_x_32m2 : Intrinsic<[llvm_v8i32_ty],[llvm_i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_s_x_32m4 : Intrinsic<[llvm_v16i32_ty],[llvm_i32_ty],[IntrNoMem]>;
	def int_riscv_vmv_s_x_32m8 : Intrinsic<[llvm_v32i32_ty],[llvm_i32_ty],[IntrNoMem]>;

//vfmv.f.s vfmv.s.f
	def int_riscv_vfmv_f_s_f32m1 : Intrinsic<[llvm_float_ty],[llvm_v4f32_ty],[IntrNoMem]>;
	def int_riscv_vfmv_f_s_f32m2 : Intrinsic<[llvm_float_ty],[llvm_v8f32_ty],[IntrNoMem]>;
	def int_riscv_vfmv_f_s_f32m4 : Intrinsic<[llvm_float_ty],[llvm_v16f32_ty],[IntrNoMem]>;
	def int_riscv_vfmv_f_s_f32m8 : Intrinsic<[llvm_float_ty],[llvm_v32f32_ty],[IntrNoMem]>;		
	
	def int_riscv_vfmv_s_f_f32m1 : Intrinsic<[llvm_v4f32_ty],[llvm_float_ty],[IntrNoMem]>;
	def int_riscv_vfmv_s_f_f32m2 : Intrinsic<[llvm_v8f32_ty],[llvm_float_ty],[IntrNoMem]>;
	def int_riscv_vfmv_s_f_f32m4 : Intrinsic<[llvm_v16f32_ty],[llvm_float_ty],[IntrNoMem]>;
	def int_riscv_vfmv_s_f_f32m8 : Intrinsic<[llvm_v32f32_ty],[llvm_float_ty],[IntrNoMem]>;
		
	
//vsldeup.vx
	def int_riscv_vslideup_vx_8m1 : Vector_scalar_v8m1;
	def int_riscv_vslideup_vx_8m2 : Vector_scalar_v8m2;
	def int_riscv_vslideup_vx_8m4 : Vector_scalar_v8m4;
	def int_riscv_vslideup_vx_8m8 : Vector_scalar_v8m8;	
	
	def int_riscv_vslideup_vx_16m1 : Vector_scalar_v16m1;
	def int_riscv_vslideup_vx_16m2 : Vector_scalar_v16m2;
	def int_riscv_vslideup_vx_16m4 : Vector_scalar_v16m4;
	def int_riscv_vslideup_vx_16m8 : Vector_scalar_v16m8;		
	
	def int_riscv_vslideup_vx_32m1 : Vector_scalar_v32m1;
	def int_riscv_vslideup_vx_32m2 : Vector_scalar_v32m2;
	def int_riscv_vslideup_vx_32m4 : Vector_scalar_v32m4;
	def int_riscv_vslideup_vx_32m8 : Vector_scalar_v32m8;		

	def int_riscv_vslideup_vx_f32m1 : Vector_scalar_f32m1;
	def int_riscv_vslideup_vx_f32m2 : Vector_scalar_f32m2;
	def int_riscv_vslideup_vx_f32m4 : Vector_scalar_f32m4;
	def int_riscv_vslideup_vx_f32m8 : Vector_scalar_f32m8;		
	
//masked 
	def int_riscv_vslideup_vx_8m1_m : Vector_scalar_v8m1_m;
	def int_riscv_vslideup_vx_8m2_m : Vector_scalar_v8m2_m;
	def int_riscv_vslideup_vx_8m4_m : Vector_scalar_v8m4_m;
	def int_riscv_vslideup_vx_8m8_m : Vector_scalar_v8m8_m;	
	
	def int_riscv_vslideup_vx_16m1_m : Vector_scalar_v16m1_m;
	def int_riscv_vslideup_vx_16m2_m : Vector_scalar_v16m2_m;
	def int_riscv_vslideup_vx_16m4_m : Vector_scalar_v16m4_m;
	def int_riscv_vslideup_vx_16m8_m : Vector_scalar_v16m8_m;		
	
	def int_riscv_vslideup_vx_32m1_m : Vector_scalar_v32m1_m;
	def int_riscv_vslideup_vx_32m2_m : Vector_scalar_v32m2_m;
	def int_riscv_vslideup_vx_32m4_m : Vector_scalar_v32m4_m;
	def int_riscv_vslideup_vx_32m8_m : Vector_scalar_v32m8_m;		

	def int_riscv_vslideup_vx_f32m1_m : Vector_scalar_f32m1_m;
	def int_riscv_vslideup_vx_f32m2_m : Vector_scalar_f32m2_m;
	def int_riscv_vslideup_vx_f32m4_m : Vector_scalar_f32m4_m;
	def int_riscv_vslideup_vx_f32m8_m : Vector_scalar_f32m8_m;		
	
//vslideup.vi
	def int_riscv_vslideup_vi_8m1 : Vector_scalar_v8m1;
	def int_riscv_vslideup_vi_8m2 : Vector_scalar_v8m2;
	def int_riscv_vslideup_vi_8m4 : Vector_scalar_v8m4;
	def int_riscv_vslideup_vi_8m8 : Vector_scalar_v8m8;	
	
	def int_riscv_vslideup_vi_16m1 : Vector_scalar_v16m1;
	def int_riscv_vslideup_vi_16m2 : Vector_scalar_v16m2;
	def int_riscv_vslideup_vi_16m4 : Vector_scalar_v16m4;
	def int_riscv_vslideup_vi_16m8 : Vector_scalar_v16m8;		
	
	def int_riscv_vslideup_vi_32m1 : Vector_scalar_v32m1;
	def int_riscv_vslideup_vi_32m2 : Vector_scalar_v32m2;
	def int_riscv_vslideup_vi_32m4 : Vector_scalar_v32m4;
	def int_riscv_vslideup_vi_32m8 : Vector_scalar_v32m8;		

	def int_riscv_vslideup_vi_f32m1 : Vector_scalar_f32m1;
	def int_riscv_vslideup_vi_f32m2 : Vector_scalar_f32m2;
	def int_riscv_vslideup_vi_f32m4 : Vector_scalar_f32m4;
	def int_riscv_vslideup_vi_f32m8 : Vector_scalar_f32m8;		
	
//masked 
	def int_riscv_vslideup_vi_8m1_m : Vector_scalar_v8m1_m;
	def int_riscv_vslideup_vi_8m2_m : Vector_scalar_v8m2_m;
	def int_riscv_vslideup_vi_8m4_m : Vector_scalar_v8m4_m;
	def int_riscv_vslideup_vi_8m8_m : Vector_scalar_v8m8_m;	
	
	def int_riscv_vslideup_vi_16m1_m : Vector_scalar_v16m1_m;
	def int_riscv_vslideup_vi_16m2_m : Vector_scalar_v16m2_m;
	def int_riscv_vslideup_vi_16m4_m : Vector_scalar_v16m4_m;
	def int_riscv_vslideup_vi_16m8_m : Vector_scalar_v16m8_m;		
	
	def int_riscv_vslideup_vi_32m1_m : Vector_scalar_v32m1_m;
	def int_riscv_vslideup_vi_32m2_m : Vector_scalar_v32m2_m;
	def int_riscv_vslideup_vi_32m4_m : Vector_scalar_v32m4_m;
	def int_riscv_vslideup_vi_32m8_m : Vector_scalar_v32m8_m;		

	def int_riscv_vslideup_vi_f32m1_m : Vector_scalar_f32m1_m;
	def int_riscv_vslideup_vi_f32m2_m : Vector_scalar_f32m2_m;
	def int_riscv_vslideup_vi_f32m4_m : Vector_scalar_f32m4_m;
	def int_riscv_vslideup_vi_f32m8_m : Vector_scalar_f32m8_m;		
	
//vslidedown.vx
	def int_riscv_vslidedown_vx_8m1 : Vector_scalar_v8m1;
	def int_riscv_vslidedown_vx_8m2 : Vector_scalar_v8m2;
	def int_riscv_vslidedown_vx_8m4 : Vector_scalar_v8m4;
	def int_riscv_vslidedown_vx_8m8 : Vector_scalar_v8m8;	
	
	def int_riscv_vslidedown_vx_16m1 : Vector_scalar_v16m1;
	def int_riscv_vslidedown_vx_16m2 : Vector_scalar_v16m2;
	def int_riscv_vslidedown_vx_16m4 : Vector_scalar_v16m4;
	def int_riscv_vslidedown_vx_16m8 : Vector_scalar_v16m8;		
	
	def int_riscv_vslidedown_vx_32m1 : Vector_scalar_v32m1;
	def int_riscv_vslidedown_vx_32m2 : Vector_scalar_v32m2;
	def int_riscv_vslidedown_vx_32m4 : Vector_scalar_v32m4;
	def int_riscv_vslidedown_vx_32m8 : Vector_scalar_v32m8;		

	def int_riscv_vslidedown_vx_f32m1 : Vector_scalar_f32m1;
	def int_riscv_vslidedown_vx_f32m2 : Vector_scalar_f32m2;
	def int_riscv_vslidedown_vx_f32m4 : Vector_scalar_f32m4;
	def int_riscv_vslidedown_vx_f32m8 : Vector_scalar_f32m8;		
	
//masked 
	def int_riscv_vslidedown_vx_8m1_m : Vector_scalar_v8m1_m;
	def int_riscv_vslidedown_vx_8m2_m : Vector_scalar_v8m2_m;
	def int_riscv_vslidedown_vx_8m4_m : Vector_scalar_v8m4_m;
	def int_riscv_vslidedown_vx_8m8_m : Vector_scalar_v8m8_m;	
	
	def int_riscv_vslidedown_vx_16m1_m : Vector_scalar_v16m1_m;
	def int_riscv_vslidedown_vx_16m2_m : Vector_scalar_v16m2_m;
	def int_riscv_vslidedown_vx_16m4_m : Vector_scalar_v16m4_m;
	def int_riscv_vslidedown_vx_16m8_m : Vector_scalar_v16m8_m;		
	
	def int_riscv_vslidedown_vx_32m1_m : Vector_scalar_v32m1_m;
	def int_riscv_vslidedown_vx_32m2_m : Vector_scalar_v32m2_m;
	def int_riscv_vslidedown_vx_32m4_m : Vector_scalar_v32m4_m;
	def int_riscv_vslidedown_vx_32m8_m : Vector_scalar_v32m8_m;		

	def int_riscv_vslidedown_vx_f32m1_m : Vector_scalar_f32m1_m;
	def int_riscv_vslidedown_vx_f32m2_m : Vector_scalar_f32m2_m;
	def int_riscv_vslidedown_vx_f32m4_m : Vector_scalar_f32m4_m;
	def int_riscv_vslidedown_vx_f32m8_m : Vector_scalar_f32m8_m;		
	
//vslidedown.vi
	def int_riscv_vslidedown_vi_8m1 : Vector_scalar_v8m1;
	def int_riscv_vslidedown_vi_8m2 : Vector_scalar_v8m2;
	def int_riscv_vslidedown_vi_8m4 : Vector_scalar_v8m4;
	def int_riscv_vslidedown_vi_8m8 : Vector_scalar_v8m8;	
	
	def int_riscv_vslidedown_vi_16m1 : Vector_scalar_v16m1;
	def int_riscv_vslidedown_vi_16m2 : Vector_scalar_v16m2;
	def int_riscv_vslidedown_vi_16m4 : Vector_scalar_v16m4;
	def int_riscv_vslidedown_vi_16m8 : Vector_scalar_v16m8;		
	
	def int_riscv_vslidedown_vi_32m1 : Vector_scalar_v32m1;
	def int_riscv_vslidedown_vi_32m2 : Vector_scalar_v32m2;
	def int_riscv_vslidedown_vi_32m4 : Vector_scalar_v32m4;
	def int_riscv_vslidedown_vi_32m8 : Vector_scalar_v32m8;		

	def int_riscv_vslidedown_vi_f32m1 : Vector_scalar_f32m1;
	def int_riscv_vslidedown_vi_f32m2 : Vector_scalar_f32m2;
	def int_riscv_vslidedown_vi_f32m4 : Vector_scalar_f32m4;
	def int_riscv_vslidedown_vi_f32m8 : Vector_scalar_f32m8;		
	
//masked 
	def int_riscv_vslidedown_vi_8m1_m : Vector_scalar_v8m1_m;
	def int_riscv_vslidedown_vi_8m2_m : Vector_scalar_v8m2_m;
	def int_riscv_vslidedown_vi_8m4_m : Vector_scalar_v8m4_m;
	def int_riscv_vslidedown_vi_8m8_m : Vector_scalar_v8m8_m;	
	
	def int_riscv_vslidedown_vi_16m1_m : Vector_scalar_v16m1_m;
	def int_riscv_vslidedown_vi_16m2_m : Vector_scalar_v16m2_m;
	def int_riscv_vslidedown_vi_16m4_m : Vector_scalar_v16m4_m;
	def int_riscv_vslidedown_vi_16m8_m : Vector_scalar_v16m8_m;		
	
	def int_riscv_vslidedown_vi_32m1_m : Vector_scalar_v32m1_m;
	def int_riscv_vslidedown_vi_32m2_m : Vector_scalar_v32m2_m;
	def int_riscv_vslidedown_vi_32m4_m : Vector_scalar_v32m4_m;
	def int_riscv_vslidedown_vi_32m8_m : Vector_scalar_v32m8_m;		

	def int_riscv_vslidedown_vi_f32m1_m : Vector_scalar_f32m1_m;
	def int_riscv_vslidedown_vi_f32m2_m : Vector_scalar_f32m2_m;
	def int_riscv_vslidedown_vi_f32m4_m : Vector_scalar_f32m4_m;
	def int_riscv_vslidedown_vi_f32m8_m : Vector_scalar_f32m8_m;		
	
//vslide1up.vx
	def int_riscv_vslide1up_vx_8m1 : Vector_scalar_v8m1;
	def int_riscv_vslide1up_vx_8m2 : Vector_scalar_v8m2;
	def int_riscv_vslide1up_vx_8m4 : Vector_scalar_v8m4;
	def int_riscv_vslide1up_vx_8m8 : Vector_scalar_v8m8;	
	
	def int_riscv_vslide1up_vx_16m1 : Vector_scalar_v16m1;
	def int_riscv_vslide1up_vx_16m2 : Vector_scalar_v16m2;
	def int_riscv_vslide1up_vx_16m4 : Vector_scalar_v16m4;
	def int_riscv_vslide1up_vx_16m8 : Vector_scalar_v16m8;		
	
	def int_riscv_vslide1up_vx_32m1 : Vector_scalar_v32m1;
	def int_riscv_vslide1up_vx_32m2 : Vector_scalar_v32m2;
	def int_riscv_vslide1up_vx_32m4 : Vector_scalar_v32m4;
	def int_riscv_vslide1up_vx_32m8 : Vector_scalar_v32m8;		

	def int_riscv_vslide1up_vx_f32m1 : Vector_scalar_f32m1;
	def int_riscv_vslide1up_vx_f32m2 : Vector_scalar_f32m2;
	def int_riscv_vslide1up_vx_f32m4 : Vector_scalar_f32m4;
	def int_riscv_vslide1up_vx_f32m8 : Vector_scalar_f32m8;		
	
//masked 
	def int_riscv_vslide1up_vx_8m1_m : Vector_scalar_v8m1_m;
	def int_riscv_vslide1up_vx_8m2_m : Vector_scalar_v8m2_m;
	def int_riscv_vslide1up_vx_8m4_m : Vector_scalar_v8m4_m;
	def int_riscv_vslide1up_vx_8m8_m : Vector_scalar_v8m8_m;	
	
	def int_riscv_vslide1up_vx_16m1_m : Vector_scalar_v16m1_m;
	def int_riscv_vslide1up_vx_16m2_m : Vector_scalar_v16m2_m;
	def int_riscv_vslide1up_vx_16m4_m : Vector_scalar_v16m4_m;
	def int_riscv_vslide1up_vx_16m8_m : Vector_scalar_v16m8_m;		
	
	def int_riscv_vslide1up_vx_32m1_m : Vector_scalar_v32m1_m;
	def int_riscv_vslide1up_vx_32m2_m : Vector_scalar_v32m2_m;
	def int_riscv_vslide1up_vx_32m4_m : Vector_scalar_v32m4_m;
	def int_riscv_vslide1up_vx_32m8_m : Vector_scalar_v32m8_m;		

	def int_riscv_vslide1up_vx_f32m1_m : Vector_scalar_f32m1_m;
	def int_riscv_vslide1up_vx_f32m2_m : Vector_scalar_f32m2_m;
	def int_riscv_vslide1up_vx_f32m4_m : Vector_scalar_f32m4_m;
	def int_riscv_vslide1up_vx_f32m8_m : Vector_scalar_f32m8_m;		
	
//vslide1down.vx
	def int_riscv_vslide1down_vx_8m1 : Vector_scalar_v8m1;
	def int_riscv_vslide1down_vx_8m2 : Vector_scalar_v8m2;
	def int_riscv_vslide1down_vx_8m4 : Vector_scalar_v8m4;
	def int_riscv_vslide1down_vx_8m8 : Vector_scalar_v8m8;	
	
	def int_riscv_vslide1down_vx_16m1 : Vector_scalar_v16m1;
	def int_riscv_vslide1down_vx_16m2 : Vector_scalar_v16m2;
	def int_riscv_vslide1down_vx_16m4 : Vector_scalar_v16m4;
	def int_riscv_vslide1down_vx_16m8 : Vector_scalar_v16m8;		
	
	def int_riscv_vslide1down_vx_32m1 : Vector_scalar_v32m1;
	def int_riscv_vslide1down_vx_32m2 : Vector_scalar_v32m2;
	def int_riscv_vslide1down_vx_32m4 : Vector_scalar_v32m4;
	def int_riscv_vslide1down_vx_32m8 : Vector_scalar_v32m8;		
	
	def int_riscv_vslide1down_vx_f32m1 : Vector_scalar_f32m1;
	def int_riscv_vslide1down_vx_f32m2 : Vector_scalar_f32m2;
	def int_riscv_vslide1down_vx_f32m4 : Vector_scalar_f32m4;
	def int_riscv_vslide1down_vx_f32m8 : Vector_scalar_f32m8;		
	
//masked 
	def int_riscv_vslide1down_vx_8m1_m : Vector_scalar_v8m1_m;
	def int_riscv_vslide1down_vx_8m2_m : Vector_scalar_v8m2_m;
	def int_riscv_vslide1down_vx_8m4_m : Vector_scalar_v8m4_m;
	def int_riscv_vslide1down_vx_8m8_m : Vector_scalar_v8m8_m;	
	
	def int_riscv_vslide1down_vx_16m1_m : Vector_scalar_v16m1_m;
	def int_riscv_vslide1down_vx_16m2_m : Vector_scalar_v16m2_m;
	def int_riscv_vslide1down_vx_16m4_m : Vector_scalar_v16m4_m;
	def int_riscv_vslide1down_vx_16m8_m : Vector_scalar_v16m8_m;		
	
	def int_riscv_vslide1down_vx_32m1_m : Vector_scalar_v32m1_m;
	def int_riscv_vslide1down_vx_32m2_m : Vector_scalar_v32m2_m;
	def int_riscv_vslide1down_vx_32m4_m : Vector_scalar_v32m4_m;
	def int_riscv_vslide1down_vx_32m8_m : Vector_scalar_v32m8_m;		

	def int_riscv_vslide1down_vx_f32m1_m : Vector_scalar_f32m1_m;
	def int_riscv_vslide1down_vx_f32m2_m : Vector_scalar_f32m2_m;
	def int_riscv_vslide1down_vx_f32m4_m : Vector_scalar_f32m4_m;
	def int_riscv_vslide1down_vx_f32m8_m : Vector_scalar_f32m8_m;		

//vrgather.vv
	def int_riscv_vrgather_vv_8m1 : Vector_Vector_v8m1;
	def int_riscv_vrgather_vv_8m2 : Vector_Vector_v8m2;
	def int_riscv_vrgather_vv_8m4 : Vector_Vector_v8m4;
	def int_riscv_vrgather_vv_8m8 : Vector_Vector_v8m8;
	
	def int_riscv_vrgather_vv_16m1 : Vector_Vector_v16m1;
	def int_riscv_vrgather_vv_16m2 : Vector_Vector_v16m2;
	def int_riscv_vrgather_vv_16m4 : Vector_Vector_v16m4;
	def int_riscv_vrgather_vv_16m8 : Vector_Vector_v16m8;
	
	def int_riscv_vrgather_vv_32m1 : Vector_Vector_v32m1;
	def int_riscv_vrgather_vv_32m2 : Vector_Vector_v32m2;
	def int_riscv_vrgather_vv_32m4 : Vector_Vector_v32m4;
	def int_riscv_vrgather_vv_32m8 : Vector_Vector_v32m8;

	def int_riscv_vrgather_vv_f32m1 : Vector_VectorInt_f32m1;
	def int_riscv_vrgather_vv_f32m2 : Vector_VectorInt_f32m2;
	def int_riscv_vrgather_vv_f32m4 : Vector_VectorInt_f32m4;
	def int_riscv_vrgather_vv_f32m8 : Vector_VectorInt_f32m8;	
	
//masked 
	def int_riscv_vrgather_vv_8m1_m : Vector_Vector_v8m1_m;
	def int_riscv_vrgather_vv_8m2_m : Vector_Vector_v8m2_m;
	def int_riscv_vrgather_vv_8m4_m : Vector_Vector_v8m4_m;
	def int_riscv_vrgather_vv_8m8_m : Vector_Vector_v8m8_m;
	
	def int_riscv_vrgather_vv_16m1_m : Vector_Vector_v16m1_m;
	def int_riscv_vrgather_vv_16m2_m : Vector_Vector_v16m2_m;
	def int_riscv_vrgather_vv_16m4_m : Vector_Vector_v16m4_m;
	def int_riscv_vrgather_vv_16m8_m : Vector_Vector_v16m8_m;
	
	def int_riscv_vrgather_vv_32m1_m : Vector_Vector_v32m1_m;
	def int_riscv_vrgather_vv_32m2_m : Vector_Vector_v32m2_m;
	def int_riscv_vrgather_vv_32m4_m : Vector_Vector_v32m4_m;
	def int_riscv_vrgather_vv_32m8_m : Vector_Vector_v32m8_m;

	def int_riscv_vrgather_vv_f32m1_m : Vector_VectorInt_f32m1_m;
	def int_riscv_vrgather_vv_f32m2_m : Vector_VectorInt_f32m2_m;
	def int_riscv_vrgather_vv_f32m4_m : Vector_VectorInt_f32m4_m;
	def int_riscv_vrgather_vv_f32m8_m : Vector_VectorInt_f32m8_m;	
		
//vrgather.vx
	def int_riscv_vrgather_vx_8m1 : Vector_scalar_v8m1;
	def int_riscv_vrgather_vx_8m2 : Vector_scalar_v8m2;
	def int_riscv_vrgather_vx_8m4 : Vector_scalar_v8m4;
	def int_riscv_vrgather_vx_8m8 : Vector_scalar_v8m8;	
	
	def int_riscv_vrgather_vx_16m1 : Vector_scalar_v16m1;
	def int_riscv_vrgather_vx_16m2 : Vector_scalar_v16m2;
	def int_riscv_vrgather_vx_16m4 : Vector_scalar_v16m4;
	def int_riscv_vrgather_vx_16m8 : Vector_scalar_v16m8;		
	
	def int_riscv_vrgather_vx_32m1 : Vector_scalar_v32m1;
	def int_riscv_vrgather_vx_32m2 : Vector_scalar_v32m2;
	def int_riscv_vrgather_vx_32m4 : Vector_scalar_v32m4;
	def int_riscv_vrgather_vx_32m8 : Vector_scalar_v32m8;			

	def int_riscv_vrgather_vx_f32m1 : Vector_scalar_f32m1;
	def int_riscv_vrgather_vx_f32m2 : Vector_scalar_f32m2;
	def int_riscv_vrgather_vx_f32m4 : Vector_scalar_f32m4;
	def int_riscv_vrgather_vx_f32m8 : Vector_scalar_f32m8;			
	
//masked 
	def int_riscv_vrgather_vx_8m1_m : Vector_scalar_v8m1_m;
	def int_riscv_vrgather_vx_8m2_m : Vector_scalar_v8m2_m;
	def int_riscv_vrgather_vx_8m4_m : Vector_scalar_v8m4_m;
	def int_riscv_vrgather_vx_8m8_m : Vector_scalar_v8m8_m;	
	
	def int_riscv_vrgather_vx_16m1_m : Vector_scalar_v16m1_m;
	def int_riscv_vrgather_vx_16m2_m : Vector_scalar_v16m2_m;
	def int_riscv_vrgather_vx_16m4_m : Vector_scalar_v16m4_m;
	def int_riscv_vrgather_vx_16m8_m : Vector_scalar_v16m8_m;		
	
	def int_riscv_vrgather_vx_32m1_m : Vector_scalar_v32m1_m;
	def int_riscv_vrgather_vx_32m2_m : Vector_scalar_v32m2_m;
	def int_riscv_vrgather_vx_32m4_m : Vector_scalar_v32m4_m;
	def int_riscv_vrgather_vx_32m8_m : Vector_scalar_v32m8_m;		

	def int_riscv_vrgather_vx_f32m1_m : Vector_scalar_f32m1_m;
	def int_riscv_vrgather_vx_f32m2_m : Vector_scalar_f32m2_m;
	def int_riscv_vrgather_vx_f32m4_m : Vector_scalar_f32m4_m;
	def int_riscv_vrgather_vx_f32m8_m : Vector_scalar_f32m8_m;		
	
//vrgather.vi
	def int_riscv_vrgather_vi_8m1 : Vector_scalar_v8m1;
	def int_riscv_vrgather_vi_8m2 : Vector_scalar_v8m2;
	def int_riscv_vrgather_vi_8m4 : Vector_scalar_v8m4;
	def int_riscv_vrgather_vi_8m8 : Vector_scalar_v8m8;	
	
	def int_riscv_vrgather_vi_16m1 : Vector_scalar_v16m1;
	def int_riscv_vrgather_vi_16m2 : Vector_scalar_v16m2;
	def int_riscv_vrgather_vi_16m4 : Vector_scalar_v16m4;
	def int_riscv_vrgather_vi_16m8 : Vector_scalar_v16m8;		
	
	def int_riscv_vrgather_vi_32m1 : Vector_scalar_v32m1;
	def int_riscv_vrgather_vi_32m2 : Vector_scalar_v32m2;
	def int_riscv_vrgather_vi_32m4 : Vector_scalar_v32m4;
	def int_riscv_vrgather_vi_32m8 : Vector_scalar_v32m8;		

	def int_riscv_vrgather_vi_f32m1 : Vector_scalar_f32m1;
	def int_riscv_vrgather_vi_f32m2 : Vector_scalar_f32m2;
	def int_riscv_vrgather_vi_f32m4 : Vector_scalar_f32m4;
	def int_riscv_vrgather_vi_f32m8 : Vector_scalar_f32m8;		
	
//masked 
	def int_riscv_vrgather_vi_8m1_m : Vector_scalar_v8m1_m;
	def int_riscv_vrgather_vi_8m2_m : Vector_scalar_v8m2_m;
	def int_riscv_vrgather_vi_8m4_m : Vector_scalar_v8m4_m;
	def int_riscv_vrgather_vi_8m8_m : Vector_scalar_v8m8_m;	
	
	def int_riscv_vrgather_vi_16m1_m : Vector_scalar_v16m1_m;
	def int_riscv_vrgather_vi_16m2_m : Vector_scalar_v16m2_m;
	def int_riscv_vrgather_vi_16m4_m : Vector_scalar_v16m4_m;
	def int_riscv_vrgather_vi_16m8_m : Vector_scalar_v16m8_m;		
	
	def int_riscv_vrgather_vi_32m1_m : Vector_scalar_v32m1_m;
	def int_riscv_vrgather_vi_32m2_m : Vector_scalar_v32m2_m;
	def int_riscv_vrgather_vi_32m4_m : Vector_scalar_v32m4_m;
	def int_riscv_vrgather_vi_32m8_m : Vector_scalar_v32m8_m;		

	def int_riscv_vrgather_vi_f32m1_m : Vector_scalar_f32m1_m;
	def int_riscv_vrgather_vi_f32m2_m : Vector_scalar_f32m2_m;
	def int_riscv_vrgather_vi_f32m4_m : Vector_scalar_f32m4_m;
	def int_riscv_vrgather_vi_f32m8_m : Vector_scalar_f32m8_m;		

//vcompress.vm
	def int_riscv_vcompress_vm_8m1 : Vm_Vector_v8m1;
	def int_riscv_vcompress_vm_8m2 : Vm_Vector_v8m2;
	def int_riscv_vcompress_vm_8m4 : Vm_Vector_v8m4;
	def int_riscv_vcompress_vm_8m8 : Vm_Vector_v8m8;
	
	def int_riscv_vcompress_vm_16m1 : Vm_Vector_v16m1;
	def int_riscv_vcompress_vm_16m2 : Vm_Vector_v16m2;
	def int_riscv_vcompress_vm_16m4 : Vm_Vector_v16m4;
	def int_riscv_vcompress_vm_16m8 : Vm_Vector_v16m8;
	
	def int_riscv_vcompress_vm_32m1 : Vm_Vector_v32m1;
	def int_riscv_vcompress_vm_32m2 : Vm_Vector_v32m2;
	def int_riscv_vcompress_vm_32m4 : Vm_Vector_v32m4;
	def int_riscv_vcompress_vm_32m8 : Vm_Vector_v32m8;

	def int_riscv_vcompress_vm_f32m1 : Vm_Vector_f32m1;
	def int_riscv_vcompress_vm_f32m2 : Vm_Vector_f32m2;
	def int_riscv_vcompress_vm_f32m4 : Vm_Vector_f32m4;
	def int_riscv_vcompress_vm_f32m8 : Vm_Vector_f32m8;	
				
} // TargetPrefix = "riscv"
