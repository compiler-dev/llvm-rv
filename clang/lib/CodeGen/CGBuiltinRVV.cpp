//===---- CGBuiltinRVV.cpp - Emit LLVM Code for builtins ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This contains code to emit Builtin calls as LLVM code.
// Contributed by Hunan Compiler Information Technology Co., Ltd, 
// http://www.compiler-dev.com, Email: <info@compiler-dev.com>.
//
//===----------------------------------------------------------------------===//

#include "CGCXXABI.h"
#include "CGObjCRuntime.h"
#include "CGOpenCLRuntime.h"
#include "CGRecordLayout.h"
#include "CodeGenFunction.h"
#include "CodeGenModule.h"
#include "ConstantEmitter.h"
#include "PatternInit.h"
#include "TargetInfo.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Attr.h"
#include "clang/AST/Decl.h"
#include "clang/AST/OSLog.h"
#include "clang/Basic/TargetBuiltins.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/CodeGen/CGFunctionInfo.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IntrinsicsAArch64.h"
#include "llvm/IR/IntrinsicsAMDGPU.h"
#include "llvm/IR/IntrinsicsARM.h"
#include "llvm/IR/IntrinsicsBPF.h"
#include "llvm/IR/IntrinsicsHexagon.h"
#include "llvm/IR/IntrinsicsNVPTX.h"
#include "llvm/IR/IntrinsicsRISCV.h"
#include "llvm/IR/IntrinsicsPowerPC.h"
#include "llvm/IR/IntrinsicsR600.h"
#include "llvm/IR/IntrinsicsS390.h"
#include "llvm/IR/IntrinsicsWebAssembly.h"
#include "llvm/IR/IntrinsicsX86.h"
#include "llvm/IR/MDBuilder.h"
#include "llvm/Support/ConvertUTF.h"
#include "llvm/Support/ScopedPrinter.h"
#include "llvm/Support/TargetParser.h"
#include <sstream>

using namespace clang;
using namespace CodeGen;
using namespace llvm;

Value *CodeGenFunction::EmitRISCVBuiltinExprRVV(unsigned BuiltinID,
						const CallExpr * E)
{
    SmallVector < Value *, 4 > Ops;


    //Find out if any arguments are required to be integer constant expressions.
    unsigned ICEArguments = 0;
    ASTContext::GetBuiltinTypeError Error;
    getContext().GetBuiltinType(BuiltinID, Error, &ICEArguments);
    assert(Error == ASTContext::GE_None && "shoule not codegen an error");

    for (unsigned i = 0, e = E->getNumArgs(); i != e; i++) {
	//If this is a normal argument, just emit it as a scalar.
	if ((ICEArguments & (1 << i)) == 0) {
	    Ops.push_back(EmitScalarExpr(E->getArg(i)));
	    continue;
	}
	//If this is required to be a constant, constant fold it so that we know 
	//that the generated intrinsic gets a ConstantInt.
	llvm::APSInt Result;
	bool IsConst = E->getArg(i)->isIntegerConstantExpr(Result, getContext());
	assert(IsConst && "constant arg isn't actually constant?");
	(void) IsConst;
	Ops.push_back(llvm::ConstantInt::get(getLLVMContext(), Result));
    }

    Intrinsic::ID ID = Intrinsic::not_intrinsic;

    switch (BuiltinID) {
    default:
	return nullptr;

	//vsetvli/vsetvl
    case RISCV::BI__builtin_riscv_vsetvli:
	ID = Intrinsic::riscv_vsetvli;
	break;
    case RISCV::BI__builtin_riscv_vsetvl:
	ID = Intrinsic::riscv_vsetvl;
	break;
	// Vector Single-Width Integer Add and Subtract Functions                               
    case RISCV::BI__builtin_riscv_vadd_vv_i8m1:
    case RISCV::BI__builtin_riscv_vadd_vv_u8m1:
	ID = Intrinsic::riscv_vadd_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i8m2:
    case RISCV::BI__builtin_riscv_vadd_vv_u8m2:
	ID = Intrinsic::riscv_vadd_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i8m4:
    case RISCV::BI__builtin_riscv_vadd_vv_u8m4:
	ID = Intrinsic::riscv_vadd_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i8m8:
    case RISCV::BI__builtin_riscv_vadd_vv_u8m8:
	ID = Intrinsic::riscv_vadd_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i16m1:
    case RISCV::BI__builtin_riscv_vadd_vv_u16m1:
	ID = Intrinsic::riscv_vadd_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i16m2:
    case RISCV::BI__builtin_riscv_vadd_vv_u16m2:
	ID = Intrinsic::riscv_vadd_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i16m4:
    case RISCV::BI__builtin_riscv_vadd_vv_u16m4:
	ID = Intrinsic::riscv_vadd_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i16m8:
    case RISCV::BI__builtin_riscv_vadd_vv_u16m8:
	ID = Intrinsic::riscv_vadd_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i32m1:
    case RISCV::BI__builtin_riscv_vadd_vv_u32m1:
	ID = Intrinsic::riscv_vadd_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i32m2:
    case RISCV::BI__builtin_riscv_vadd_vv_u32m2:
	ID = Intrinsic::riscv_vadd_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i32m4:
    case RISCV::BI__builtin_riscv_vadd_vv_u32m4:
	ID = Intrinsic::riscv_vadd_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i32m8:
    case RISCV::BI__builtin_riscv_vadd_vv_u32m8:
	ID = Intrinsic::riscv_vadd_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i8m1:
    case RISCV::BI__builtin_riscv_vadd_vx_u8m1:
	ID = Intrinsic::riscv_vadd_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i8m2:
    case RISCV::BI__builtin_riscv_vadd_vx_u8m2:
	ID = Intrinsic::riscv_vadd_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i8m4:
    case RISCV::BI__builtin_riscv_vadd_vx_u8m4:
	ID = Intrinsic::riscv_vadd_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i8m8:
    case RISCV::BI__builtin_riscv_vadd_vx_u8m8:
	ID = Intrinsic::riscv_vadd_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i16m1:
    case RISCV::BI__builtin_riscv_vadd_vx_u16m1:
	ID = Intrinsic::riscv_vadd_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i16m2:
    case RISCV::BI__builtin_riscv_vadd_vx_u16m2:
	ID = Intrinsic::riscv_vadd_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i16m4:
    case RISCV::BI__builtin_riscv_vadd_vx_u16m4:
	ID = Intrinsic::riscv_vadd_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i16m8:
    case RISCV::BI__builtin_riscv_vadd_vx_u16m8:
	ID = Intrinsic::riscv_vadd_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i32m1:
    case RISCV::BI__builtin_riscv_vadd_vx_u32m1:
	ID = Intrinsic::riscv_vadd_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i32m2:
    case RISCV::BI__builtin_riscv_vadd_vx_u32m2:
	ID = Intrinsic::riscv_vadd_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i32m4:
    case RISCV::BI__builtin_riscv_vadd_vx_u32m4:
	ID = Intrinsic::riscv_vadd_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i32m8:
    case RISCV::BI__builtin_riscv_vadd_vx_u32m8:
	ID = Intrinsic::riscv_vadd_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i8m1:
    case RISCV::BI__builtin_riscv_vadd_vi_u8m1:
	ID = Intrinsic::riscv_vadd_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i8m2:
    case RISCV::BI__builtin_riscv_vadd_vi_u8m2:
	ID = Intrinsic::riscv_vadd_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i8m4:
    case RISCV::BI__builtin_riscv_vadd_vi_u8m4:
	ID = Intrinsic::riscv_vadd_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i8m8:
    case RISCV::BI__builtin_riscv_vadd_vi_u8m8:
	ID = Intrinsic::riscv_vadd_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i16m1:
    case RISCV::BI__builtin_riscv_vadd_vi_u16m1:
	ID = Intrinsic::riscv_vadd_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i16m2:
    case RISCV::BI__builtin_riscv_vadd_vi_u16m2:
	ID = Intrinsic::riscv_vadd_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i16m4:
    case RISCV::BI__builtin_riscv_vadd_vi_u16m4:
	ID = Intrinsic::riscv_vadd_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i16m8:
    case RISCV::BI__builtin_riscv_vadd_vi_u16m8:
	ID = Intrinsic::riscv_vadd_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i32m1:
    case RISCV::BI__builtin_riscv_vadd_vi_u32m1:
	ID = Intrinsic::riscv_vadd_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i32m2:
    case RISCV::BI__builtin_riscv_vadd_vi_u32m2:
	ID = Intrinsic::riscv_vadd_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i32m4:
    case RISCV::BI__builtin_riscv_vadd_vi_u32m4:
	ID = Intrinsic::riscv_vadd_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i32m8:
    case RISCV::BI__builtin_riscv_vadd_vi_u32m8:
	ID = Intrinsic::riscv_vadd_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i8m1:
    case RISCV::BI__builtin_riscv_vsub_vv_u8m1:
	ID = Intrinsic::riscv_vsub_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i8m2:
    case RISCV::BI__builtin_riscv_vsub_vv_u8m2:
	ID = Intrinsic::riscv_vsub_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i8m4:
    case RISCV::BI__builtin_riscv_vsub_vv_u8m4:
	ID = Intrinsic::riscv_vsub_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i8m8:
    case RISCV::BI__builtin_riscv_vsub_vv_u8m8:
	ID = Intrinsic::riscv_vsub_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i16m1:
    case RISCV::BI__builtin_riscv_vsub_vv_u16m1:
	ID = Intrinsic::riscv_vsub_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i16m2:
    case RISCV::BI__builtin_riscv_vsub_vv_u16m2:
	ID = Intrinsic::riscv_vsub_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i16m4:
    case RISCV::BI__builtin_riscv_vsub_vv_u16m4:
	ID = Intrinsic::riscv_vsub_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i16m8:
    case RISCV::BI__builtin_riscv_vsub_vv_u16m8:
	ID = Intrinsic::riscv_vsub_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i32m1:
    case RISCV::BI__builtin_riscv_vsub_vv_u32m1:
	ID = Intrinsic::riscv_vsub_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i32m2:
    case RISCV::BI__builtin_riscv_vsub_vv_u32m2:
	ID = Intrinsic::riscv_vsub_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i32m4:
    case RISCV::BI__builtin_riscv_vsub_vv_u32m4:
	ID = Intrinsic::riscv_vsub_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i32m8:
    case RISCV::BI__builtin_riscv_vsub_vv_u32m8:
	ID = Intrinsic::riscv_vsub_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i8m1:
    case RISCV::BI__builtin_riscv_vsub_vx_u8m1:
	ID = Intrinsic::riscv_vsub_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i8m2:
    case RISCV::BI__builtin_riscv_vsub_vx_u8m2:
	ID = Intrinsic::riscv_vsub_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i8m4:
    case RISCV::BI__builtin_riscv_vsub_vx_u8m4:
	ID = Intrinsic::riscv_vsub_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i8m8:
    case RISCV::BI__builtin_riscv_vsub_vx_u8m8:
	ID = Intrinsic::riscv_vsub_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i16m1:
    case RISCV::BI__builtin_riscv_vsub_vx_u16m1:
	ID = Intrinsic::riscv_vsub_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i16m2:
    case RISCV::BI__builtin_riscv_vsub_vx_u16m2:
	ID = Intrinsic::riscv_vsub_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i16m4:
    case RISCV::BI__builtin_riscv_vsub_vx_u16m4:
	ID = Intrinsic::riscv_vsub_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i16m8:
    case RISCV::BI__builtin_riscv_vsub_vx_u16m8:
	ID = Intrinsic::riscv_vsub_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i32m1:
    case RISCV::BI__builtin_riscv_vsub_vx_u32m1:
	ID = Intrinsic::riscv_vsub_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i32m2:
    case RISCV::BI__builtin_riscv_vsub_vx_u32m2:
	ID = Intrinsic::riscv_vsub_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i32m4:
    case RISCV::BI__builtin_riscv_vsub_vx_u32m4:
	ID = Intrinsic::riscv_vsub_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i32m8:
    case RISCV::BI__builtin_riscv_vsub_vx_u32m8:
	ID = Intrinsic::riscv_vsub_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i8m1:
    case RISCV::BI__builtin_riscv_vrsub_vx_u8m1:
	ID = Intrinsic::riscv_vrsub_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i8m2:
    case RISCV::BI__builtin_riscv_vrsub_vx_u8m2:
	ID = Intrinsic::riscv_vrsub_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i8m4:
    case RISCV::BI__builtin_riscv_vrsub_vx_u8m4:
	ID = Intrinsic::riscv_vrsub_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i8m8:
    case RISCV::BI__builtin_riscv_vrsub_vx_u8m8:
	ID = Intrinsic::riscv_vrsub_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i16m1:
    case RISCV::BI__builtin_riscv_vrsub_vx_u16m1:
	ID = Intrinsic::riscv_vrsub_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i16m2:
    case RISCV::BI__builtin_riscv_vrsub_vx_u16m2:
	ID = Intrinsic::riscv_vrsub_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i16m4:
    case RISCV::BI__builtin_riscv_vrsub_vx_u16m4:
	ID = Intrinsic::riscv_vrsub_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i16m8:
    case RISCV::BI__builtin_riscv_vrsub_vx_u16m8:
	ID = Intrinsic::riscv_vrsub_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i32m1:
    case RISCV::BI__builtin_riscv_vrsub_vx_u32m1:
	ID = Intrinsic::riscv_vrsub_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i32m2:
    case RISCV::BI__builtin_riscv_vrsub_vx_u32m2:
	ID = Intrinsic::riscv_vrsub_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i32m4:
    case RISCV::BI__builtin_riscv_vrsub_vx_u32m4:
	ID = Intrinsic::riscv_vrsub_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i32m8:
    case RISCV::BI__builtin_riscv_vrsub_vx_u32m8:
	ID = Intrinsic::riscv_vrsub_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i8m1:
    case RISCV::BI__builtin_riscv_vrsub_vi_u8m1:
	ID = Intrinsic::riscv_vrsub_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i8m2:
    case RISCV::BI__builtin_riscv_vrsub_vi_u8m2:
	ID = Intrinsic::riscv_vrsub_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i8m4:
    case RISCV::BI__builtin_riscv_vrsub_vi_u8m4:
	ID = Intrinsic::riscv_vrsub_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i8m8:
    case RISCV::BI__builtin_riscv_vrsub_vi_u8m8:
	ID = Intrinsic::riscv_vrsub_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i16m1:
    case RISCV::BI__builtin_riscv_vrsub_vi_u16m1:
	ID = Intrinsic::riscv_vrsub_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i16m2:
    case RISCV::BI__builtin_riscv_vrsub_vi_u16m2:
	ID = Intrinsic::riscv_vrsub_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i16m4:
    case RISCV::BI__builtin_riscv_vrsub_vi_u16m4:
	ID = Intrinsic::riscv_vrsub_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i16m8:
    case RISCV::BI__builtin_riscv_vrsub_vi_u16m8:
	ID = Intrinsic::riscv_vrsub_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i32m1:
    case RISCV::BI__builtin_riscv_vrsub_vi_u32m1:
	ID = Intrinsic::riscv_vrsub_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i32m2:
    case RISCV::BI__builtin_riscv_vrsub_vi_u32m2:
	ID = Intrinsic::riscv_vrsub_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i32m4:
    case RISCV::BI__builtin_riscv_vrsub_vi_u32m4:
	ID = Intrinsic::riscv_vrsub_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i32m8:
    case RISCV::BI__builtin_riscv_vrsub_vi_u32m8:
	ID = Intrinsic::riscv_vrsub_vx_32m8;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vadd_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u8m1_m:
	ID = Intrinsic::riscv_vadd_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u8m2_m:
	ID = Intrinsic::riscv_vadd_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u8m4_m:
	ID = Intrinsic::riscv_vadd_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u8m8_m:
	ID = Intrinsic::riscv_vadd_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u16m1_m:
	ID = Intrinsic::riscv_vadd_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u16m2_m:
	ID = Intrinsic::riscv_vadd_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u16m4_m:
	ID = Intrinsic::riscv_vadd_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u16m8_m:
	ID = Intrinsic::riscv_vadd_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u32m1_m:
	ID = Intrinsic::riscv_vadd_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u32m2_m:
	ID = Intrinsic::riscv_vadd_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u32m4_m:
	ID = Intrinsic::riscv_vadd_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vadd_vv_u32m8_m:
	ID = Intrinsic::riscv_vadd_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u8m1_m:
	ID = Intrinsic::riscv_vadd_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u8m2_m:
	ID = Intrinsic::riscv_vadd_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u8m4_m:
	ID = Intrinsic::riscv_vadd_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u8m8_m:
	ID = Intrinsic::riscv_vadd_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u16m1_m:
	ID = Intrinsic::riscv_vadd_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u16m2_m:
	ID = Intrinsic::riscv_vadd_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u16m4_m:
	ID = Intrinsic::riscv_vadd_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u16m8_m:
	ID = Intrinsic::riscv_vadd_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u32m1_m:
	ID = Intrinsic::riscv_vadd_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u32m2_m:
	ID = Intrinsic::riscv_vadd_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u32m4_m:
	ID = Intrinsic::riscv_vadd_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vadd_vx_u32m8_m:
	ID = Intrinsic::riscv_vadd_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u8m1_m:
	ID = Intrinsic::riscv_vadd_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u8m2_m:
	ID = Intrinsic::riscv_vadd_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u8m4_m:
	ID = Intrinsic::riscv_vadd_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u8m8_m:
	ID = Intrinsic::riscv_vadd_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u16m1_m:
	ID = Intrinsic::riscv_vadd_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u16m2_m:
	ID = Intrinsic::riscv_vadd_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u16m4_m:
	ID = Intrinsic::riscv_vadd_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u16m8_m:
	ID = Intrinsic::riscv_vadd_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u32m1_m:
	ID = Intrinsic::riscv_vadd_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u32m2_m:
	ID = Intrinsic::riscv_vadd_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u32m4_m:
	ID = Intrinsic::riscv_vadd_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vadd_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vadd_vi_u32m8_m:
	ID = Intrinsic::riscv_vadd_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u8m1_m:
	ID = Intrinsic::riscv_vsub_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u8m2_m:
	ID = Intrinsic::riscv_vsub_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u8m4_m:
	ID = Intrinsic::riscv_vsub_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u8m8_m:
	ID = Intrinsic::riscv_vsub_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u16m1_m:
	ID = Intrinsic::riscv_vsub_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u16m2_m:
	ID = Intrinsic::riscv_vsub_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u16m4_m:
	ID = Intrinsic::riscv_vsub_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u16m8_m:
	ID = Intrinsic::riscv_vsub_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u32m1_m:
	ID = Intrinsic::riscv_vsub_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u32m2_m:
	ID = Intrinsic::riscv_vsub_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u32m4_m:
	ID = Intrinsic::riscv_vsub_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vsub_vv_u32m8_m:
	ID = Intrinsic::riscv_vsub_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u8m1_m:
	ID = Intrinsic::riscv_vsub_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u8m2_m:
	ID = Intrinsic::riscv_vsub_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u8m4_m:
	ID = Intrinsic::riscv_vsub_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u8m8_m:
	ID = Intrinsic::riscv_vsub_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u16m1_m:
	ID = Intrinsic::riscv_vsub_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u16m2_m:
	ID = Intrinsic::riscv_vsub_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u16m4_m:
	ID = Intrinsic::riscv_vsub_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u16m8_m:
	ID = Intrinsic::riscv_vsub_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u32m1_m:
	ID = Intrinsic::riscv_vsub_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u32m2_m:
	ID = Intrinsic::riscv_vsub_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u32m4_m:
	ID = Intrinsic::riscv_vsub_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsub_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vsub_vx_u32m8_m:
	ID = Intrinsic::riscv_vsub_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u8m1_m:
	ID = Intrinsic::riscv_vrsub_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u8m2_m:
	ID = Intrinsic::riscv_vrsub_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u8m4_m:
	ID = Intrinsic::riscv_vrsub_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u8m8_m:
	ID = Intrinsic::riscv_vrsub_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u16m1_m:
	ID = Intrinsic::riscv_vrsub_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u16m2_m:
	ID = Intrinsic::riscv_vrsub_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u16m4_m:
	ID = Intrinsic::riscv_vrsub_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u16m8_m:
	ID = Intrinsic::riscv_vrsub_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u32m1_m:
	ID = Intrinsic::riscv_vrsub_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u32m2_m:
	ID = Intrinsic::riscv_vrsub_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u32m4_m:
	ID = Intrinsic::riscv_vrsub_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vrsub_vx_u32m8_m:
	ID = Intrinsic::riscv_vrsub_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u8m1_m:
	ID = Intrinsic::riscv_vrsub_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u8m2_m:
	ID = Intrinsic::riscv_vrsub_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u8m4_m:
	ID = Intrinsic::riscv_vrsub_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u8m8_m:
	ID = Intrinsic::riscv_vrsub_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u16m1_m:
	ID = Intrinsic::riscv_vrsub_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u16m2_m:
	ID = Intrinsic::riscv_vrsub_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u16m4_m:
	ID = Intrinsic::riscv_vrsub_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u16m8_m:
	ID = Intrinsic::riscv_vrsub_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u32m1_m:
	ID = Intrinsic::riscv_vrsub_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u32m2_m:
	ID = Intrinsic::riscv_vrsub_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u32m4_m:
	ID = Intrinsic::riscv_vrsub_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrsub_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vrsub_vi_u32m8_m:
	ID = Intrinsic::riscv_vrsub_vx_32m8_m;
	break;

	//Vector Widening Integer Add/Subtract Functions
    case RISCV::BI__builtin_riscv_vwaddu_vv_u16m2:
	ID = Intrinsic::riscv_vwaddu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vv_u16m4:
	ID = Intrinsic::riscv_vwaddu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vv_u16m8:
	ID = Intrinsic::riscv_vwaddu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vv_u32m2:
	ID = Intrinsic::riscv_vwaddu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vv_u32m4:
	ID = Intrinsic::riscv_vwaddu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vv_u32m8:
	ID = Intrinsic::riscv_vwaddu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u16m2:
	ID = Intrinsic::riscv_vwaddu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u16m4:
	ID = Intrinsic::riscv_vwaddu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u16m8:
	ID = Intrinsic::riscv_vwaddu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u32m2:
	ID = Intrinsic::riscv_vwaddu_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u32m4:
	ID = Intrinsic::riscv_vwaddu_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u32m8:
	ID = Intrinsic::riscv_vwaddu_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u16m2:
	ID = Intrinsic::riscv_vwsubu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u16m4:
	ID = Intrinsic::riscv_vwsubu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u16m8:
	ID = Intrinsic::riscv_vwsubu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u32m2:
	ID = Intrinsic::riscv_vwsubu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u32m4:
	ID = Intrinsic::riscv_vwsubu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u32m8:
	ID = Intrinsic::riscv_vwsubu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u16m2:
	ID = Intrinsic::riscv_vwsubu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u16m4:
	ID = Intrinsic::riscv_vwsubu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u16m8:
	ID = Intrinsic::riscv_vwsubu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u32m2:
	ID = Intrinsic::riscv_vwsubu_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u32m4:
	ID = Intrinsic::riscv_vwsubu_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u32m8:
	ID = Intrinsic::riscv_vwsubu_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i16m2:
	ID = Intrinsic::riscv_vwadd_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i16m4:
	ID = Intrinsic::riscv_vwadd_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i16m8:
	ID = Intrinsic::riscv_vwadd_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i32m2:
	ID = Intrinsic::riscv_vwadd_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i32m4:
	ID = Intrinsic::riscv_vwadd_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i32m8:
	ID = Intrinsic::riscv_vwadd_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i16m2:
	ID = Intrinsic::riscv_vwadd_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i16m4:
	ID = Intrinsic::riscv_vwadd_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i16m8:
	ID = Intrinsic::riscv_vwadd_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i32m2:
	ID = Intrinsic::riscv_vwadd_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i32m4:
	ID = Intrinsic::riscv_vwadd_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i32m8:
	ID = Intrinsic::riscv_vwadd_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i16m2:
	ID = Intrinsic::riscv_vwsub_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i16m4:
	ID = Intrinsic::riscv_vwsub_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i16m8:
	ID = Intrinsic::riscv_vwsub_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i32m2:
	ID = Intrinsic::riscv_vwsub_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i32m4:
	ID = Intrinsic::riscv_vwsub_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i32m8:
	ID = Intrinsic::riscv_vwsub_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i16m2:
	ID = Intrinsic::riscv_vwsub_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i16m4:
	ID = Intrinsic::riscv_vwsub_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i16m8:
	ID = Intrinsic::riscv_vwsub_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i32m2:
	ID = Intrinsic::riscv_vwsub_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i32m4:
	ID = Intrinsic::riscv_vwsub_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i32m8:
	ID = Intrinsic::riscv_vwsub_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u16m2:
	ID = Intrinsic::riscv_vwaddu_wv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u16m4:
	ID = Intrinsic::riscv_vwaddu_wv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u16m8:
	ID = Intrinsic::riscv_vwaddu_wv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u32m2:
	ID = Intrinsic::riscv_vwaddu_wv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u32m4:
	ID = Intrinsic::riscv_vwaddu_wv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u32m8:
	ID = Intrinsic::riscv_vwaddu_wv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u16m2:
	ID = Intrinsic::riscv_vwaddu_wx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u16m4:
	ID = Intrinsic::riscv_vwaddu_wx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u16m8:
	ID = Intrinsic::riscv_vwaddu_wx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u32m2:
	ID = Intrinsic::riscv_vwaddu_wx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u32m4:
	ID = Intrinsic::riscv_vwaddu_wx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u32m8:
	ID = Intrinsic::riscv_vwaddu_wx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u16m2:
	ID = Intrinsic::riscv_vwsubu_wv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u16m4:
	ID = Intrinsic::riscv_vwsubu_wv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u16m8:
	ID = Intrinsic::riscv_vwsubu_wv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u32m2:
	ID = Intrinsic::riscv_vwsubu_wv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u32m4:
	ID = Intrinsic::riscv_vwsubu_wv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u32m8:
	ID = Intrinsic::riscv_vwsubu_wv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u16m2:
	ID = Intrinsic::riscv_vwsubu_wx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u16m4:
	ID = Intrinsic::riscv_vwsubu_wx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u16m8:
	ID = Intrinsic::riscv_vwsubu_wx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u32m2:
	ID = Intrinsic::riscv_vwsubu_wx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u32m4:
	ID = Intrinsic::riscv_vwsubu_wx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u32m8:
	ID = Intrinsic::riscv_vwsubu_wx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i16m2:
	ID = Intrinsic::riscv_vwadd_wv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i16m4:
	ID = Intrinsic::riscv_vwadd_wv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i16m8:
	ID = Intrinsic::riscv_vwadd_wv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i32m2:
	ID = Intrinsic::riscv_vwadd_wv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i32m4:
	ID = Intrinsic::riscv_vwadd_wv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i32m8:
	ID = Intrinsic::riscv_vwadd_wv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i16m2:
	ID = Intrinsic::riscv_vwadd_wx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i16m4:
	ID = Intrinsic::riscv_vwadd_wx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i16m8:
	ID = Intrinsic::riscv_vwadd_wx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i32m2:
	ID = Intrinsic::riscv_vwadd_wx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i32m4:
	ID = Intrinsic::riscv_vwadd_wx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i32m8:
	ID = Intrinsic::riscv_vwadd_wx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i16m2:
	ID = Intrinsic::riscv_vwsub_wv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i16m4:
	ID = Intrinsic::riscv_vwsub_wv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i16m8:
	ID = Intrinsic::riscv_vwsub_wv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i32m2:
	ID = Intrinsic::riscv_vwsub_wv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i32m4:
	ID = Intrinsic::riscv_vwsub_wv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i32m8:
	ID = Intrinsic::riscv_vwsub_wv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i16m2:
	ID = Intrinsic::riscv_vwsub_wx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i16m4:
	ID = Intrinsic::riscv_vwsub_wx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i16m8:
	ID = Intrinsic::riscv_vwsub_wx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i32m2:
	ID = Intrinsic::riscv_vwsub_wx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i32m4:
	ID = Intrinsic::riscv_vwsub_wx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i32m8:
	ID = Intrinsic::riscv_vwsub_wx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vwaddu_vv_u16m2_m:
	ID = Intrinsic::riscv_vwaddu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vv_u16m4_m:
	ID = Intrinsic::riscv_vwaddu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vv_u16m8_m:
	ID = Intrinsic::riscv_vwaddu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vv_u32m2_m:
	ID = Intrinsic::riscv_vwaddu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vv_u32m4_m:
	ID = Intrinsic::riscv_vwaddu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vv_u32m8_m:
	ID = Intrinsic::riscv_vwaddu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u16m2_m:
	ID = Intrinsic::riscv_vwaddu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u16m4_m:
	ID = Intrinsic::riscv_vwaddu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u16m8_m:
	ID = Intrinsic::riscv_vwaddu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u32m2_m:
	ID = Intrinsic::riscv_vwaddu_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u32m4_m:
	ID = Intrinsic::riscv_vwaddu_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_vx_u32m8_m:
	ID = Intrinsic::riscv_vwaddu_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u16m2_m:
	ID = Intrinsic::riscv_vwsubu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u16m4_m:
	ID = Intrinsic::riscv_vwsubu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u16m8_m:
	ID = Intrinsic::riscv_vwsubu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u32m2_m:
	ID = Intrinsic::riscv_vwsubu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u32m4_m:
	ID = Intrinsic::riscv_vwsubu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vv_u32m8_m:
	ID = Intrinsic::riscv_vwsubu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u16m2_m:
	ID = Intrinsic::riscv_vwsubu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u16m4_m:
	ID = Intrinsic::riscv_vwsubu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u16m8_m:
	ID = Intrinsic::riscv_vwsubu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u32m2_m:
	ID = Intrinsic::riscv_vwsubu_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u32m4_m:
	ID = Intrinsic::riscv_vwsubu_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_vx_u32m8_m:
	ID = Intrinsic::riscv_vwsubu_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i16m2_m:
	ID = Intrinsic::riscv_vwadd_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i16m4_m:
	ID = Intrinsic::riscv_vwadd_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i16m8_m:
	ID = Intrinsic::riscv_vwadd_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i32m2_m:
	ID = Intrinsic::riscv_vwadd_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i32m4_m:
	ID = Intrinsic::riscv_vwadd_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vv_i32m8_m:
	ID = Intrinsic::riscv_vwadd_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i16m2_m:
	ID = Intrinsic::riscv_vwadd_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i16m4_m:
	ID = Intrinsic::riscv_vwadd_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i16m8_m:
	ID = Intrinsic::riscv_vwadd_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i32m2_m:
	ID = Intrinsic::riscv_vwadd_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i32m4_m:
	ID = Intrinsic::riscv_vwadd_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_vx_i32m8_m:
	ID = Intrinsic::riscv_vwadd_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i16m2_m:
	ID = Intrinsic::riscv_vwsub_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i16m4_m:
	ID = Intrinsic::riscv_vwsub_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i16m8_m:
	ID = Intrinsic::riscv_vwsub_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i32m2_m:
	ID = Intrinsic::riscv_vwsub_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i32m4_m:
	ID = Intrinsic::riscv_vwsub_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vv_i32m8_m:
	ID = Intrinsic::riscv_vwsub_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i16m2_m:
	ID = Intrinsic::riscv_vwsub_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i16m4_m:
	ID = Intrinsic::riscv_vwsub_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i16m8_m:
	ID = Intrinsic::riscv_vwsub_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i32m2_m:
	ID = Intrinsic::riscv_vwsub_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i32m4_m:
	ID = Intrinsic::riscv_vwsub_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_vx_i32m8_m:
	ID = Intrinsic::riscv_vwsub_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u16m2_m:
	ID = Intrinsic::riscv_vwaddu_wv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u16m4_m:
	ID = Intrinsic::riscv_vwaddu_wv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u16m8_m:
	ID = Intrinsic::riscv_vwaddu_wv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u32m2_m:
	ID = Intrinsic::riscv_vwaddu_wv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u32m4_m:
	ID = Intrinsic::riscv_vwaddu_wv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wv_u32m8_m:
	ID = Intrinsic::riscv_vwaddu_wv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u16m2_m:
	ID = Intrinsic::riscv_vwaddu_wx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u16m4_m:
	ID = Intrinsic::riscv_vwaddu_wx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u16m8_m:
	ID = Intrinsic::riscv_vwaddu_wx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u32m2_m:
	ID = Intrinsic::riscv_vwaddu_wx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u32m4_m:
	ID = Intrinsic::riscv_vwaddu_wx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwaddu_wx_u32m8_m:
	ID = Intrinsic::riscv_vwaddu_wx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u16m2_m:
	ID = Intrinsic::riscv_vwsubu_wv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u16m4_m:
	ID = Intrinsic::riscv_vwsubu_wv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u16m8_m:
	ID = Intrinsic::riscv_vwsubu_wv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u32m2_m:
	ID = Intrinsic::riscv_vwsubu_wv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u32m4_m:
	ID = Intrinsic::riscv_vwsubu_wv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wv_u32m8_m:
	ID = Intrinsic::riscv_vwsubu_wv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u16m2_m:
	ID = Intrinsic::riscv_vwsubu_wx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u16m4_m:
	ID = Intrinsic::riscv_vwsubu_wx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u16m8_m:
	ID = Intrinsic::riscv_vwsubu_wx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u32m2_m:
	ID = Intrinsic::riscv_vwsubu_wx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u32m4_m:
	ID = Intrinsic::riscv_vwsubu_wx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsubu_wx_u32m8_m:
	ID = Intrinsic::riscv_vwsubu_wx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i16m2_m:
	ID = Intrinsic::riscv_vwadd_wv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i16m4_m:
	ID = Intrinsic::riscv_vwadd_wv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i16m8_m:
	ID = Intrinsic::riscv_vwadd_wv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i32m2_m:
	ID = Intrinsic::riscv_vwadd_wv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i32m4_m:
	ID = Intrinsic::riscv_vwadd_wv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wv_i32m8_m:
	ID = Intrinsic::riscv_vwadd_wv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i16m2_m:
	ID = Intrinsic::riscv_vwadd_wx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i16m4_m:
	ID = Intrinsic::riscv_vwadd_wx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i16m8_m:
	ID = Intrinsic::riscv_vwadd_wx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i32m2_m:
	ID = Intrinsic::riscv_vwadd_wx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i32m4_m:
	ID = Intrinsic::riscv_vwadd_wx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwadd_wx_i32m8_m:
	ID = Intrinsic::riscv_vwadd_wx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i16m2_m:
	ID = Intrinsic::riscv_vwsub_wv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i16m4_m:
	ID = Intrinsic::riscv_vwsub_wv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i16m8_m:
	ID = Intrinsic::riscv_vwsub_wv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i32m2_m:
	ID = Intrinsic::riscv_vwsub_wv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i32m4_m:
	ID = Intrinsic::riscv_vwsub_wv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wv_i32m8_m:
	ID = Intrinsic::riscv_vwsub_wv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i16m2_m:
	ID = Intrinsic::riscv_vwsub_wx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i16m4_m:
	ID = Intrinsic::riscv_vwsub_wx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i16m8_m:
	ID = Intrinsic::riscv_vwsub_wx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i32m2_m:
	ID = Intrinsic::riscv_vwsub_wx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i32m4_m:
	ID = Intrinsic::riscv_vwsub_wx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwsub_wx_i32m8_m:
	ID = Intrinsic::riscv_vwsub_wx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;

	//Vector Integer Add-with-Carry/Subtract-with-Borrow Functions
    case RISCV::BI__builtin_riscv_vadc_vvm_i8m1:
    case RISCV::BI__builtin_riscv_vadc_vvm_u8m1:
	ID = Intrinsic::riscv_vadc_vvm_8m1;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i8m2:
    case RISCV::BI__builtin_riscv_vadc_vvm_u8m2:
	ID = Intrinsic::riscv_vadc_vvm_8m2;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i8m4:
    case RISCV::BI__builtin_riscv_vadc_vvm_u8m4:
	ID = Intrinsic::riscv_vadc_vvm_8m4;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i8m8:
    case RISCV::BI__builtin_riscv_vadc_vvm_u8m8:
	ID = Intrinsic::riscv_vadc_vvm_8m8;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i16m1:
    case RISCV::BI__builtin_riscv_vadc_vvm_u16m1:
	ID = Intrinsic::riscv_vadc_vvm_16m1;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i16m2:
    case RISCV::BI__builtin_riscv_vadc_vvm_u16m2:
	ID = Intrinsic::riscv_vadc_vvm_16m2;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i16m4:
    case RISCV::BI__builtin_riscv_vadc_vvm_u16m4:
	ID = Intrinsic::riscv_vadc_vvm_16m4;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i16m8:
    case RISCV::BI__builtin_riscv_vadc_vvm_u16m8:
	ID = Intrinsic::riscv_vadc_vvm_16m8;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i32m1:
    case RISCV::BI__builtin_riscv_vadc_vvm_u32m1:
	ID = Intrinsic::riscv_vadc_vvm_32m1;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i32m2:
    case RISCV::BI__builtin_riscv_vadc_vvm_u32m2:
	ID = Intrinsic::riscv_vadc_vvm_32m2;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i32m4:
    case RISCV::BI__builtin_riscv_vadc_vvm_u32m4:
	ID = Intrinsic::riscv_vadc_vvm_32m4;
	break;
    case RISCV::BI__builtin_riscv_vadc_vvm_i32m8:
    case RISCV::BI__builtin_riscv_vadc_vvm_u32m8:
	ID = Intrinsic::riscv_vadc_vvm_32m8;
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i8m1:
    case RISCV::BI__builtin_riscv_vadc_vxm_u8m1:
	ID = Intrinsic::riscv_vadc_vxm_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i8m2:
    case RISCV::BI__builtin_riscv_vadc_vxm_u8m2:
	ID = Intrinsic::riscv_vadc_vxm_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i8m4:
    case RISCV::BI__builtin_riscv_vadc_vxm_u8m4:
	ID = Intrinsic::riscv_vadc_vxm_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i8m8:
    case RISCV::BI__builtin_riscv_vadc_vxm_u8m8:
	ID = Intrinsic::riscv_vadc_vxm_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i16m1:
    case RISCV::BI__builtin_riscv_vadc_vxm_u16m1:
	ID = Intrinsic::riscv_vadc_vxm_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i16m2:
    case RISCV::BI__builtin_riscv_vadc_vxm_u16m2:
	ID = Intrinsic::riscv_vadc_vxm_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i16m4:
    case RISCV::BI__builtin_riscv_vadc_vxm_u16m4:
	ID = Intrinsic::riscv_vadc_vxm_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i16m8:
    case RISCV::BI__builtin_riscv_vadc_vxm_u16m8:
	ID = Intrinsic::riscv_vadc_vxm_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i32m1:
    case RISCV::BI__builtin_riscv_vadc_vxm_u32m1:
	ID = Intrinsic::riscv_vadc_vxm_32m1;
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i32m2:
    case RISCV::BI__builtin_riscv_vadc_vxm_u32m2:
	ID = Intrinsic::riscv_vadc_vxm_32m2;
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i32m4:
    case RISCV::BI__builtin_riscv_vadc_vxm_u32m4:
	ID = Intrinsic::riscv_vadc_vxm_32m4;
	break;
    case RISCV::BI__builtin_riscv_vadc_vxm_i32m8:
    case RISCV::BI__builtin_riscv_vadc_vxm_u32m8:
	ID = Intrinsic::riscv_vadc_vxm_32m8;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i8m1:
    case RISCV::BI__builtin_riscv_vadc_vim_u8m1:
	ID = Intrinsic::riscv_vadc_vim_8m1;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i8m2:
    case RISCV::BI__builtin_riscv_vadc_vim_u8m2:
	ID = Intrinsic::riscv_vadc_vim_8m2;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i8m4:
    case RISCV::BI__builtin_riscv_vadc_vim_u8m4:
	ID = Intrinsic::riscv_vadc_vim_8m4;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i8m8:
    case RISCV::BI__builtin_riscv_vadc_vim_u8m8:
	ID = Intrinsic::riscv_vadc_vim_8m8;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i16m1:
    case RISCV::BI__builtin_riscv_vadc_vim_u16m1:
	ID = Intrinsic::riscv_vadc_vim_16m1;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i16m2:
    case RISCV::BI__builtin_riscv_vadc_vim_u16m2:
	ID = Intrinsic::riscv_vadc_vim_16m2;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i16m4:
    case RISCV::BI__builtin_riscv_vadc_vim_u16m4:
	ID = Intrinsic::riscv_vadc_vim_16m4;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i16m8:
    case RISCV::BI__builtin_riscv_vadc_vim_u16m8:
	ID = Intrinsic::riscv_vadc_vim_16m8;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i32m1:
    case RISCV::BI__builtin_riscv_vadc_vim_u32m1:
	ID = Intrinsic::riscv_vadc_vim_32m1;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i32m2:
    case RISCV::BI__builtin_riscv_vadc_vim_u32m2:
	ID = Intrinsic::riscv_vadc_vim_32m2;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i32m4:
    case RISCV::BI__builtin_riscv_vadc_vim_u32m4:
	ID = Intrinsic::riscv_vadc_vim_32m4;
	break;
    case RISCV::BI__builtin_riscv_vadc_vim_i32m8:
    case RISCV::BI__builtin_riscv_vadc_vim_u32m8:
	ID = Intrinsic::riscv_vadc_vim_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i8m1:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u8m1:
	ID = Intrinsic::riscv_vmadc_vvm_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i8m2:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u8m2:
	ID = Intrinsic::riscv_vmadc_vvm_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i8m4:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u8m4:
	ID = Intrinsic::riscv_vmadc_vvm_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i8m8:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u8m8:
	ID = Intrinsic::riscv_vmadc_vvm_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i16m1:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u16m1:
	ID = Intrinsic::riscv_vmadc_vvm_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i16m2:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u16m2:
	ID = Intrinsic::riscv_vmadc_vvm_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i16m4:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u16m4:
	ID = Intrinsic::riscv_vmadc_vvm_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i16m8:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u16m8:
	ID = Intrinsic::riscv_vmadc_vvm_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i32m1:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u32m1:
	ID = Intrinsic::riscv_vmadc_vvm_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i32m2:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u32m2:
	ID = Intrinsic::riscv_vmadc_vvm_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i32m4:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u32m4:
	ID = Intrinsic::riscv_vmadc_vvm_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vvm_i32m8:
    case RISCV::BI__builtin_riscv_vmadc_vvm_u32m8:
	ID = Intrinsic::riscv_vmadc_vvm_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i8m1:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u8m1:
	ID = Intrinsic::riscv_vmadc_vxm_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i8m2:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u8m2:
	ID = Intrinsic::riscv_vmadc_vxm_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i8m4:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u8m4:
	ID = Intrinsic::riscv_vmadc_vxm_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i8m8:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u8m8:
	ID = Intrinsic::riscv_vmadc_vxm_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i16m1:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u16m1:
	ID = Intrinsic::riscv_vmadc_vxm_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i16m2:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u16m2:
	ID = Intrinsic::riscv_vmadc_vxm_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i16m4:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u16m4:
	ID = Intrinsic::riscv_vmadc_vxm_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i16m8:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u16m8:
	ID = Intrinsic::riscv_vmadc_vxm_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i32m1:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u32m1:
	ID = Intrinsic::riscv_vmadc_vxm_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i32m2:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u32m2:
	ID = Intrinsic::riscv_vmadc_vxm_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i32m4:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u32m4:
	ID = Intrinsic::riscv_vmadc_vxm_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vxm_i32m8:
    case RISCV::BI__builtin_riscv_vmadc_vxm_u32m8:
	ID = Intrinsic::riscv_vmadc_vxm_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i8m1:
    case RISCV::BI__builtin_riscv_vmadc_vim_u8m1:
	ID = Intrinsic::riscv_vmadc_vim_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i8m2:
    case RISCV::BI__builtin_riscv_vmadc_vim_u8m2:
	ID = Intrinsic::riscv_vmadc_vim_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i8m4:
    case RISCV::BI__builtin_riscv_vmadc_vim_u8m4:
	ID = Intrinsic::riscv_vmadc_vim_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i8m8:
    case RISCV::BI__builtin_riscv_vmadc_vim_u8m8:
	ID = Intrinsic::riscv_vmadc_vim_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i16m1:
    case RISCV::BI__builtin_riscv_vmadc_vim_u16m1:
	ID = Intrinsic::riscv_vmadc_vim_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i16m2:
    case RISCV::BI__builtin_riscv_vmadc_vim_u16m2:
	ID = Intrinsic::riscv_vmadc_vim_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i16m4:
    case RISCV::BI__builtin_riscv_vmadc_vim_u16m4:
	ID = Intrinsic::riscv_vmadc_vim_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i16m8:
    case RISCV::BI__builtin_riscv_vmadc_vim_u16m8:
	ID = Intrinsic::riscv_vmadc_vim_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i32m1:
    case RISCV::BI__builtin_riscv_vmadc_vim_u32m1:
	ID = Intrinsic::riscv_vmadc_vim_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i32m2:
    case RISCV::BI__builtin_riscv_vmadc_vim_u32m2:
	ID = Intrinsic::riscv_vmadc_vim_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i32m4:
    case RISCV::BI__builtin_riscv_vmadc_vim_u32m4:
	ID = Intrinsic::riscv_vmadc_vim_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vim_i32m8:
    case RISCV::BI__builtin_riscv_vmadc_vim_u32m8:
	ID = Intrinsic::riscv_vmadc_vim_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i8m1:
    case RISCV::BI__builtin_riscv_vmadc_vv_u8m1:
	ID = Intrinsic::riscv_vmadc_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i8m2:
    case RISCV::BI__builtin_riscv_vmadc_vv_u8m2:
	ID = Intrinsic::riscv_vmadc_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i8m4:
    case RISCV::BI__builtin_riscv_vmadc_vv_u8m4:
	ID = Intrinsic::riscv_vmadc_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i8m8:
    case RISCV::BI__builtin_riscv_vmadc_vv_u8m8:
	ID = Intrinsic::riscv_vmadc_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i16m1:
    case RISCV::BI__builtin_riscv_vmadc_vv_u16m1:
	ID = Intrinsic::riscv_vmadc_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i16m2:
    case RISCV::BI__builtin_riscv_vmadc_vv_u16m2:
	ID = Intrinsic::riscv_vmadc_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i16m4:
    case RISCV::BI__builtin_riscv_vmadc_vv_u16m4:
	ID = Intrinsic::riscv_vmadc_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i16m8:
    case RISCV::BI__builtin_riscv_vmadc_vv_u16m8:
	ID = Intrinsic::riscv_vmadc_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i32m1:
    case RISCV::BI__builtin_riscv_vmadc_vv_u32m1:
	ID = Intrinsic::riscv_vmadc_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i32m2:
    case RISCV::BI__builtin_riscv_vmadc_vv_u32m2:
	ID = Intrinsic::riscv_vmadc_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i32m4:
    case RISCV::BI__builtin_riscv_vmadc_vv_u32m4:
	ID = Intrinsic::riscv_vmadc_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vv_i32m8:
    case RISCV::BI__builtin_riscv_vmadc_vv_u32m8:
	ID = Intrinsic::riscv_vmadc_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i8m1:
    case RISCV::BI__builtin_riscv_vmadc_vx_u8m1:
	ID = Intrinsic::riscv_vmadc_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i8m2:
    case RISCV::BI__builtin_riscv_vmadc_vx_u8m2:
	ID = Intrinsic::riscv_vmadc_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i8m4:
    case RISCV::BI__builtin_riscv_vmadc_vx_u8m4:
	ID = Intrinsic::riscv_vmadc_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i8m8:
    case RISCV::BI__builtin_riscv_vmadc_vx_u8m8:
	ID = Intrinsic::riscv_vmadc_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i16m1:
    case RISCV::BI__builtin_riscv_vmadc_vx_u16m1:
	ID = Intrinsic::riscv_vmadc_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i16m2:
    case RISCV::BI__builtin_riscv_vmadc_vx_u16m2:
	ID = Intrinsic::riscv_vmadc_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i16m4:
    case RISCV::BI__builtin_riscv_vmadc_vx_u16m4:
	ID = Intrinsic::riscv_vmadc_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i16m8:
    case RISCV::BI__builtin_riscv_vmadc_vx_u16m8:
	ID = Intrinsic::riscv_vmadc_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i32m1:
    case RISCV::BI__builtin_riscv_vmadc_vx_u32m1:
	ID = Intrinsic::riscv_vmadc_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i32m2:
    case RISCV::BI__builtin_riscv_vmadc_vx_u32m2:
	ID = Intrinsic::riscv_vmadc_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i32m4:
    case RISCV::BI__builtin_riscv_vmadc_vx_u32m4:
	ID = Intrinsic::riscv_vmadc_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vx_i32m8:
    case RISCV::BI__builtin_riscv_vmadc_vx_u32m8:
	ID = Intrinsic::riscv_vmadc_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i8m1:
    case RISCV::BI__builtin_riscv_vmadc_vi_u8m1:
	ID = Intrinsic::riscv_vmadc_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i8m2:
    case RISCV::BI__builtin_riscv_vmadc_vi_u8m2:
	ID = Intrinsic::riscv_vmadc_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i8m4:
    case RISCV::BI__builtin_riscv_vmadc_vi_u8m4:
	ID = Intrinsic::riscv_vmadc_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i8m8:
    case RISCV::BI__builtin_riscv_vmadc_vi_u8m8:
	ID = Intrinsic::riscv_vmadc_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i16m1:
    case RISCV::BI__builtin_riscv_vmadc_vi_u16m1:
	ID = Intrinsic::riscv_vmadc_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i16m2:
    case RISCV::BI__builtin_riscv_vmadc_vi_u16m2:
	ID = Intrinsic::riscv_vmadc_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i16m4:
    case RISCV::BI__builtin_riscv_vmadc_vi_u16m4:
	ID = Intrinsic::riscv_vmadc_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i16m8:
    case RISCV::BI__builtin_riscv_vmadc_vi_u16m8:
	ID = Intrinsic::riscv_vmadc_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i32m1:
    case RISCV::BI__builtin_riscv_vmadc_vi_u32m1:
	ID = Intrinsic::riscv_vmadc_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i32m2:
    case RISCV::BI__builtin_riscv_vmadc_vi_u32m2:
	ID = Intrinsic::riscv_vmadc_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i32m4:
    case RISCV::BI__builtin_riscv_vmadc_vi_u32m4:
	ID = Intrinsic::riscv_vmadc_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmadc_vi_i32m8:
    case RISCV::BI__builtin_riscv_vmadc_vi_u32m8:
	ID = Intrinsic::riscv_vmadc_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i8m1:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u8m1:
	ID = Intrinsic::riscv_vsbc_vvm_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i8m2:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u8m2:
	ID = Intrinsic::riscv_vsbc_vvm_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i8m4:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u8m4:
	ID = Intrinsic::riscv_vsbc_vvm_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i8m8:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u8m8:
	ID = Intrinsic::riscv_vsbc_vvm_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i16m1:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u16m1:
	ID = Intrinsic::riscv_vsbc_vvm_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i16m2:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u16m2:
	ID = Intrinsic::riscv_vsbc_vvm_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i16m4:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u16m4:
	ID = Intrinsic::riscv_vsbc_vvm_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i16m8:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u16m8:
	ID = Intrinsic::riscv_vsbc_vvm_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i32m1:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u32m1:
	ID = Intrinsic::riscv_vsbc_vvm_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i32m2:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u32m2:
	ID = Intrinsic::riscv_vsbc_vvm_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i32m4:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u32m4:
	ID = Intrinsic::riscv_vsbc_vvm_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vvm_i32m8:
    case RISCV::BI__builtin_riscv_vsbc_vvm_u32m8:
	ID = Intrinsic::riscv_vsbc_vvm_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i8m1:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u8m1:
	ID = Intrinsic::riscv_vsbc_vxm_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i8m2:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u8m2:
	ID = Intrinsic::riscv_vsbc_vxm_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i8m4:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u8m4:
	ID = Intrinsic::riscv_vsbc_vxm_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i8m8:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u8m8:
	ID = Intrinsic::riscv_vsbc_vxm_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i16m1:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u16m1:
	ID = Intrinsic::riscv_vsbc_vxm_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i16m2:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u16m2:
	ID = Intrinsic::riscv_vsbc_vxm_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i16m4:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u16m4:
	ID = Intrinsic::riscv_vsbc_vxm_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i16m8:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u16m8:
	ID = Intrinsic::riscv_vsbc_vxm_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i32m1:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u32m1:
	ID = Intrinsic::riscv_vsbc_vxm_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i32m2:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u32m2:
	ID = Intrinsic::riscv_vsbc_vxm_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i32m4:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u32m4:
	ID = Intrinsic::riscv_vsbc_vxm_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsbc_vxm_i32m8:
    case RISCV::BI__builtin_riscv_vsbc_vxm_u32m8:
	ID = Intrinsic::riscv_vsbc_vxm_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i8m1:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u8m1:
	ID = Intrinsic::riscv_vmsbc_vvm_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i8m2:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u8m2:
	ID = Intrinsic::riscv_vmsbc_vvm_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i8m4:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u8m4:
	ID = Intrinsic::riscv_vmsbc_vvm_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i8m8:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u8m8:
	ID = Intrinsic::riscv_vmsbc_vvm_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i16m1:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u16m1:
	ID = Intrinsic::riscv_vmsbc_vvm_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i16m2:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u16m2:
	ID = Intrinsic::riscv_vmsbc_vvm_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i16m4:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u16m4:
	ID = Intrinsic::riscv_vmsbc_vvm_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i16m8:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u16m8:
	ID = Intrinsic::riscv_vmsbc_vvm_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i32m1:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u32m1:
	ID = Intrinsic::riscv_vmsbc_vvm_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i32m2:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u32m2:
	ID = Intrinsic::riscv_vmsbc_vvm_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i32m4:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u32m4:
	ID = Intrinsic::riscv_vmsbc_vvm_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vvm_i32m8:
    case RISCV::BI__builtin_riscv_vmsbc_vvm_u32m8:
	ID = Intrinsic::riscv_vmsbc_vvm_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i8m1:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u8m1:
	ID = Intrinsic::riscv_vmsbc_vxm_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i8m2:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u8m2:
	ID = Intrinsic::riscv_vmsbc_vxm_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i8m4:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u8m4:
	ID = Intrinsic::riscv_vmsbc_vxm_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i8m8:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u8m8:
	ID = Intrinsic::riscv_vmsbc_vxm_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i16m1:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u16m1:
	ID = Intrinsic::riscv_vmsbc_vxm_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i16m2:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u16m2:
	ID = Intrinsic::riscv_vmsbc_vxm_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i16m4:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u16m4:
	ID = Intrinsic::riscv_vmsbc_vxm_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i16m8:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u16m8:
	ID = Intrinsic::riscv_vmsbc_vxm_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i32m1:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u32m1:
	ID = Intrinsic::riscv_vmsbc_vxm_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i32m2:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u32m2:
	ID = Intrinsic::riscv_vmsbc_vxm_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i32m4:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u32m4:
	ID = Intrinsic::riscv_vmsbc_vxm_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vxm_i32m8:
    case RISCV::BI__builtin_riscv_vmsbc_vxm_u32m8:
	ID = Intrinsic::riscv_vmsbc_vxm_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i8m1:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u8m1:
	ID = Intrinsic::riscv_vmsbc_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i8m2:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u8m2:
	ID = Intrinsic::riscv_vmsbc_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i8m4:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u8m4:
	ID = Intrinsic::riscv_vmsbc_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i8m8:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u8m8:
	ID = Intrinsic::riscv_vmsbc_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i16m1:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u16m1:
	ID = Intrinsic::riscv_vmsbc_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i16m2:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u16m2:
	ID = Intrinsic::riscv_vmsbc_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i16m4:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u16m4:
	ID = Intrinsic::riscv_vmsbc_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i16m8:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u16m8:
	ID = Intrinsic::riscv_vmsbc_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i32m1:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u32m1:
	ID = Intrinsic::riscv_vmsbc_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i32m2:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u32m2:
	ID = Intrinsic::riscv_vmsbc_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i32m4:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u32m4:
	ID = Intrinsic::riscv_vmsbc_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vv_i32m8:
    case RISCV::BI__builtin_riscv_vmsbc_vv_u32m8:
	ID = Intrinsic::riscv_vmsbc_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i8m1:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u8m1:
	ID = Intrinsic::riscv_vmsbc_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i8m2:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u8m2:
	ID = Intrinsic::riscv_vmsbc_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i8m4:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u8m4:
	ID = Intrinsic::riscv_vmsbc_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i8m8:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u8m8:
	ID = Intrinsic::riscv_vmsbc_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i16m1:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u16m1:
	ID = Intrinsic::riscv_vmsbc_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i16m2:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u16m2:
	ID = Intrinsic::riscv_vmsbc_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i16m4:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u16m4:
	ID = Intrinsic::riscv_vmsbc_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i16m8:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u16m8:
	ID = Intrinsic::riscv_vmsbc_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i32m1:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u32m1:
	ID = Intrinsic::riscv_vmsbc_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i32m2:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u32m2:
	ID = Intrinsic::riscv_vmsbc_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i32m4:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u32m4:
	ID = Intrinsic::riscv_vmsbc_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsbc_vx_i32m8:
    case RISCV::BI__builtin_riscv_vmsbc_vx_u32m8:
	ID = Intrinsic::riscv_vmsbc_vx_32m8;
	break;

	//Vector Bitwise Logical Functions
    case RISCV::BI__builtin_riscv_vand_vv_i8m1:
    case RISCV::BI__builtin_riscv_vand_vv_u8m1:
	ID = Intrinsic::riscv_vand_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i8m2:
    case RISCV::BI__builtin_riscv_vand_vv_u8m2:
	ID = Intrinsic::riscv_vand_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i8m4:
    case RISCV::BI__builtin_riscv_vand_vv_u8m4:
	ID = Intrinsic::riscv_vand_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i8m8:
    case RISCV::BI__builtin_riscv_vand_vv_u8m8:
	ID = Intrinsic::riscv_vand_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i16m1:
    case RISCV::BI__builtin_riscv_vand_vv_u16m1:
	ID = Intrinsic::riscv_vand_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i16m2:
    case RISCV::BI__builtin_riscv_vand_vv_u16m2:
	ID = Intrinsic::riscv_vand_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i16m4:
    case RISCV::BI__builtin_riscv_vand_vv_u16m4:
	ID = Intrinsic::riscv_vand_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i16m8:
    case RISCV::BI__builtin_riscv_vand_vv_u16m8:
	ID = Intrinsic::riscv_vand_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i32m1:
    case RISCV::BI__builtin_riscv_vand_vv_u32m1:
	ID = Intrinsic::riscv_vand_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i32m2:
    case RISCV::BI__builtin_riscv_vand_vv_u32m2:
	ID = Intrinsic::riscv_vand_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i32m4:
    case RISCV::BI__builtin_riscv_vand_vv_u32m4:
	ID = Intrinsic::riscv_vand_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i32m8:
    case RISCV::BI__builtin_riscv_vand_vv_u32m8:
	ID = Intrinsic::riscv_vand_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i8m1:
    case RISCV::BI__builtin_riscv_vand_vx_u8m1:
	ID = Intrinsic::riscv_vand_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i8m2:
    case RISCV::BI__builtin_riscv_vand_vx_u8m2:
	ID = Intrinsic::riscv_vand_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i8m4:
    case RISCV::BI__builtin_riscv_vand_vx_u8m4:
	ID = Intrinsic::riscv_vand_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i8m8:
    case RISCV::BI__builtin_riscv_vand_vx_u8m8:
	ID = Intrinsic::riscv_vand_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i16m1:
    case RISCV::BI__builtin_riscv_vand_vx_u16m1:
	ID = Intrinsic::riscv_vand_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i16m2:
    case RISCV::BI__builtin_riscv_vand_vx_u16m2:
	ID = Intrinsic::riscv_vand_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i16m4:
    case RISCV::BI__builtin_riscv_vand_vx_u16m4:
	ID = Intrinsic::riscv_vand_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i16m8:
    case RISCV::BI__builtin_riscv_vand_vx_u16m8:
	ID = Intrinsic::riscv_vand_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i32m1:
    case RISCV::BI__builtin_riscv_vand_vx_u32m1:
	ID = Intrinsic::riscv_vand_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i32m2:
    case RISCV::BI__builtin_riscv_vand_vx_u32m2:
	ID = Intrinsic::riscv_vand_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i32m4:
    case RISCV::BI__builtin_riscv_vand_vx_u32m4:
	ID = Intrinsic::riscv_vand_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i32m8:
    case RISCV::BI__builtin_riscv_vand_vx_u32m8:
	ID = Intrinsic::riscv_vand_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i8m1:
    case RISCV::BI__builtin_riscv_vand_vi_u8m1:
	ID = Intrinsic::riscv_vand_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i8m2:
    case RISCV::BI__builtin_riscv_vand_vi_u8m2:
	ID = Intrinsic::riscv_vand_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i8m4:
    case RISCV::BI__builtin_riscv_vand_vi_u8m4:
	ID = Intrinsic::riscv_vand_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i8m8:
    case RISCV::BI__builtin_riscv_vand_vi_u8m8:
	ID = Intrinsic::riscv_vand_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i16m1:
    case RISCV::BI__builtin_riscv_vand_vi_u16m1:
	ID = Intrinsic::riscv_vand_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i16m2:
    case RISCV::BI__builtin_riscv_vand_vi_u16m2:
	ID = Intrinsic::riscv_vand_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i16m4:
    case RISCV::BI__builtin_riscv_vand_vi_u16m4:
	ID = Intrinsic::riscv_vand_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i16m8:
    case RISCV::BI__builtin_riscv_vand_vi_u16m8:
	ID = Intrinsic::riscv_vand_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i32m1:
    case RISCV::BI__builtin_riscv_vand_vi_u32m1:
	ID = Intrinsic::riscv_vand_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i32m2:
    case RISCV::BI__builtin_riscv_vand_vi_u32m2:
	ID = Intrinsic::riscv_vand_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i32m4:
    case RISCV::BI__builtin_riscv_vand_vi_u32m4:
	ID = Intrinsic::riscv_vand_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i32m8:
    case RISCV::BI__builtin_riscv_vand_vi_u32m8:
	ID = Intrinsic::riscv_vand_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i8m1:
    case RISCV::BI__builtin_riscv_vor_vv_u8m1:
	ID = Intrinsic::riscv_vor_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i8m2:
    case RISCV::BI__builtin_riscv_vor_vv_u8m2:
	ID = Intrinsic::riscv_vor_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i8m4:
    case RISCV::BI__builtin_riscv_vor_vv_u8m4:
	ID = Intrinsic::riscv_vor_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i8m8:
    case RISCV::BI__builtin_riscv_vor_vv_u8m8:
	ID = Intrinsic::riscv_vor_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i16m1:
    case RISCV::BI__builtin_riscv_vor_vv_u16m1:
	ID = Intrinsic::riscv_vor_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i16m2:
    case RISCV::BI__builtin_riscv_vor_vv_u16m2:
	ID = Intrinsic::riscv_vor_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i16m4:
    case RISCV::BI__builtin_riscv_vor_vv_u16m4:
	ID = Intrinsic::riscv_vor_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i16m8:
    case RISCV::BI__builtin_riscv_vor_vv_u16m8:
	ID = Intrinsic::riscv_vor_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i32m1:
    case RISCV::BI__builtin_riscv_vor_vv_u32m1:
	ID = Intrinsic::riscv_vor_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i32m2:
    case RISCV::BI__builtin_riscv_vor_vv_u32m2:
	ID = Intrinsic::riscv_vor_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i32m4:
    case RISCV::BI__builtin_riscv_vor_vv_u32m4:
	ID = Intrinsic::riscv_vor_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i32m8:
    case RISCV::BI__builtin_riscv_vor_vv_u32m8:
	ID = Intrinsic::riscv_vor_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i8m1:
    case RISCV::BI__builtin_riscv_vor_vx_u8m1:
	ID = Intrinsic::riscv_vor_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i8m2:
    case RISCV::BI__builtin_riscv_vor_vx_u8m2:
	ID = Intrinsic::riscv_vor_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i8m4:
    case RISCV::BI__builtin_riscv_vor_vx_u8m4:
	ID = Intrinsic::riscv_vor_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i8m8:
    case RISCV::BI__builtin_riscv_vor_vx_u8m8:
	ID = Intrinsic::riscv_vor_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i16m1:
    case RISCV::BI__builtin_riscv_vor_vx_u16m1:
	ID = Intrinsic::riscv_vor_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i16m2:
    case RISCV::BI__builtin_riscv_vor_vx_u16m2:
	ID = Intrinsic::riscv_vor_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i16m4:
    case RISCV::BI__builtin_riscv_vor_vx_u16m4:
	ID = Intrinsic::riscv_vor_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i16m8:
    case RISCV::BI__builtin_riscv_vor_vx_u16m8:
	ID = Intrinsic::riscv_vor_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i32m1:
    case RISCV::BI__builtin_riscv_vor_vx_u32m1:
	ID = Intrinsic::riscv_vor_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i32m2:
    case RISCV::BI__builtin_riscv_vor_vx_u32m2:
	ID = Intrinsic::riscv_vor_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i32m4:
    case RISCV::BI__builtin_riscv_vor_vx_u32m4:
	ID = Intrinsic::riscv_vor_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i32m8:
    case RISCV::BI__builtin_riscv_vor_vx_u32m8:
	ID = Intrinsic::riscv_vor_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i8m1:
    case RISCV::BI__builtin_riscv_vor_vi_u8m1:
	ID = Intrinsic::riscv_vor_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i8m2:
    case RISCV::BI__builtin_riscv_vor_vi_u8m2:
	ID = Intrinsic::riscv_vor_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i8m4:
    case RISCV::BI__builtin_riscv_vor_vi_u8m4:
	ID = Intrinsic::riscv_vor_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i8m8:
    case RISCV::BI__builtin_riscv_vor_vi_u8m8:
	ID = Intrinsic::riscv_vor_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i16m1:
    case RISCV::BI__builtin_riscv_vor_vi_u16m1:
	ID = Intrinsic::riscv_vor_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i16m2:
    case RISCV::BI__builtin_riscv_vor_vi_u16m2:
	ID = Intrinsic::riscv_vor_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i16m4:
    case RISCV::BI__builtin_riscv_vor_vi_u16m4:
	ID = Intrinsic::riscv_vor_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i16m8:
    case RISCV::BI__builtin_riscv_vor_vi_u16m8:
	ID = Intrinsic::riscv_vor_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i32m1:
    case RISCV::BI__builtin_riscv_vor_vi_u32m1:
	ID = Intrinsic::riscv_vor_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i32m2:
    case RISCV::BI__builtin_riscv_vor_vi_u32m2:
	ID = Intrinsic::riscv_vor_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i32m4:
    case RISCV::BI__builtin_riscv_vor_vi_u32m4:
	ID = Intrinsic::riscv_vor_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i32m8:
    case RISCV::BI__builtin_riscv_vor_vi_u32m8:
	ID = Intrinsic::riscv_vor_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i8m1:
    case RISCV::BI__builtin_riscv_vxor_vv_u8m1:
	ID = Intrinsic::riscv_vxor_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i8m2:
    case RISCV::BI__builtin_riscv_vxor_vv_u8m2:
	ID = Intrinsic::riscv_vxor_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i8m4:
    case RISCV::BI__builtin_riscv_vxor_vv_u8m4:
	ID = Intrinsic::riscv_vxor_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i8m8:
    case RISCV::BI__builtin_riscv_vxor_vv_u8m8:
	ID = Intrinsic::riscv_vxor_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i16m1:
    case RISCV::BI__builtin_riscv_vxor_vv_u16m1:
	ID = Intrinsic::riscv_vxor_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i16m2:
    case RISCV::BI__builtin_riscv_vxor_vv_u16m2:
	ID = Intrinsic::riscv_vxor_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i16m4:
    case RISCV::BI__builtin_riscv_vxor_vv_u16m4:
	ID = Intrinsic::riscv_vxor_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i16m8:
    case RISCV::BI__builtin_riscv_vxor_vv_u16m8:
	ID = Intrinsic::riscv_vxor_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i32m1:
    case RISCV::BI__builtin_riscv_vxor_vv_u32m1:
	ID = Intrinsic::riscv_vxor_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i32m2:
    case RISCV::BI__builtin_riscv_vxor_vv_u32m2:
	ID = Intrinsic::riscv_vxor_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i32m4:
    case RISCV::BI__builtin_riscv_vxor_vv_u32m4:
	ID = Intrinsic::riscv_vxor_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i32m8:
    case RISCV::BI__builtin_riscv_vxor_vv_u32m8:
	ID = Intrinsic::riscv_vxor_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i8m1:
    case RISCV::BI__builtin_riscv_vxor_vx_u8m1:
	ID = Intrinsic::riscv_vxor_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i8m2:
    case RISCV::BI__builtin_riscv_vxor_vx_u8m2:
	ID = Intrinsic::riscv_vxor_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i8m4:
    case RISCV::BI__builtin_riscv_vxor_vx_u8m4:
	ID = Intrinsic::riscv_vxor_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i8m8:
    case RISCV::BI__builtin_riscv_vxor_vx_u8m8:
	ID = Intrinsic::riscv_vxor_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i16m1:
    case RISCV::BI__builtin_riscv_vxor_vx_u16m1:
	ID = Intrinsic::riscv_vxor_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i16m2:
    case RISCV::BI__builtin_riscv_vxor_vx_u16m2:
	ID = Intrinsic::riscv_vxor_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i16m4:
    case RISCV::BI__builtin_riscv_vxor_vx_u16m4:
	ID = Intrinsic::riscv_vxor_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i16m8:
    case RISCV::BI__builtin_riscv_vxor_vx_u16m8:
	ID = Intrinsic::riscv_vxor_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i32m1:
    case RISCV::BI__builtin_riscv_vxor_vx_u32m1:
	ID = Intrinsic::riscv_vxor_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i32m2:
    case RISCV::BI__builtin_riscv_vxor_vx_u32m2:
	ID = Intrinsic::riscv_vxor_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i32m4:
    case RISCV::BI__builtin_riscv_vxor_vx_u32m4:
	ID = Intrinsic::riscv_vxor_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i32m8:
    case RISCV::BI__builtin_riscv_vxor_vx_u32m8:
	ID = Intrinsic::riscv_vxor_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i8m1:
    case RISCV::BI__builtin_riscv_vxor_vi_u8m1:
	ID = Intrinsic::riscv_vxor_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i8m2:
    case RISCV::BI__builtin_riscv_vxor_vi_u8m2:
	ID = Intrinsic::riscv_vxor_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i8m4:
    case RISCV::BI__builtin_riscv_vxor_vi_u8m4:
	ID = Intrinsic::riscv_vxor_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i8m8:
    case RISCV::BI__builtin_riscv_vxor_vi_u8m8:
	ID = Intrinsic::riscv_vxor_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i16m1:
    case RISCV::BI__builtin_riscv_vxor_vi_u16m1:
	ID = Intrinsic::riscv_vxor_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i16m2:
    case RISCV::BI__builtin_riscv_vxor_vi_u16m2:
	ID = Intrinsic::riscv_vxor_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i16m4:
    case RISCV::BI__builtin_riscv_vxor_vi_u16m4:
	ID = Intrinsic::riscv_vxor_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i16m8:
    case RISCV::BI__builtin_riscv_vxor_vi_u16m8:
	ID = Intrinsic::riscv_vxor_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i32m1:
    case RISCV::BI__builtin_riscv_vxor_vi_u32m1:
	ID = Intrinsic::riscv_vxor_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i32m2:
    case RISCV::BI__builtin_riscv_vxor_vi_u32m2:
	ID = Intrinsic::riscv_vxor_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i32m4:
    case RISCV::BI__builtin_riscv_vxor_vi_u32m4:
	ID = Intrinsic::riscv_vxor_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i32m8:
    case RISCV::BI__builtin_riscv_vxor_vi_u32m8:
	ID = Intrinsic::riscv_vxor_vi_32m8;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vand_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vand_vv_u8m1_m:
	ID = Intrinsic::riscv_vand_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vand_vv_u8m2_m:
	ID = Intrinsic::riscv_vand_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vand_vv_u8m4_m:
	ID = Intrinsic::riscv_vand_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vand_vv_u8m8_m:
	ID = Intrinsic::riscv_vand_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vand_vv_u16m1_m:
	ID = Intrinsic::riscv_vand_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vand_vv_u16m2_m:
	ID = Intrinsic::riscv_vand_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vand_vv_u16m4_m:
	ID = Intrinsic::riscv_vand_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vand_vv_u16m8_m:
	ID = Intrinsic::riscv_vand_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vand_vv_u32m1_m:
	ID = Intrinsic::riscv_vand_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vand_vv_u32m2_m:
	ID = Intrinsic::riscv_vand_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vand_vv_u32m4_m:
	ID = Intrinsic::riscv_vand_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vand_vv_u32m8_m:
	ID = Intrinsic::riscv_vand_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vand_vx_u8m1_m:
	ID = Intrinsic::riscv_vand_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vand_vx_u8m2_m:
	ID = Intrinsic::riscv_vand_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vand_vx_u8m4_m:
	ID = Intrinsic::riscv_vand_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vand_vx_u8m8_m:
	ID = Intrinsic::riscv_vand_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vand_vx_u16m1_m:
	ID = Intrinsic::riscv_vand_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vand_vx_u16m2_m:
	ID = Intrinsic::riscv_vand_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vand_vx_u16m4_m:
	ID = Intrinsic::riscv_vand_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vand_vx_u16m8_m:
	ID = Intrinsic::riscv_vand_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vand_vx_u32m1_m:
	ID = Intrinsic::riscv_vand_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vand_vx_u32m2_m:
	ID = Intrinsic::riscv_vand_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vand_vx_u32m4_m:
	ID = Intrinsic::riscv_vand_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vand_vx_u32m8_m:
	ID = Intrinsic::riscv_vand_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vand_vi_u8m1_m:
	ID = Intrinsic::riscv_vand_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vand_vi_u8m2_m:
	ID = Intrinsic::riscv_vand_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vand_vi_u8m4_m:
	ID = Intrinsic::riscv_vand_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vand_vi_u8m8_m:
	ID = Intrinsic::riscv_vand_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vand_vi_u16m1_m:
	ID = Intrinsic::riscv_vand_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vand_vi_u16m2_m:
	ID = Intrinsic::riscv_vand_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vand_vi_u16m4_m:
	ID = Intrinsic::riscv_vand_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vand_vi_u16m8_m:
	ID = Intrinsic::riscv_vand_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vand_vi_u32m1_m:
	ID = Intrinsic::riscv_vand_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vand_vi_u32m2_m:
	ID = Intrinsic::riscv_vand_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vand_vi_u32m4_m:
	ID = Intrinsic::riscv_vand_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vand_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vand_vi_u32m8_m:
	ID = Intrinsic::riscv_vand_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vor_vv_u8m1_m:
	ID = Intrinsic::riscv_vor_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vor_vv_u8m2_m:
	ID = Intrinsic::riscv_vor_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vor_vv_u8m4_m:
	ID = Intrinsic::riscv_vor_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vor_vv_u8m8_m:
	ID = Intrinsic::riscv_vor_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vor_vv_u16m1_m:
	ID = Intrinsic::riscv_vor_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vor_vv_u16m2_m:
	ID = Intrinsic::riscv_vor_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vor_vv_u16m4_m:
	ID = Intrinsic::riscv_vor_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vor_vv_u16m8_m:
	ID = Intrinsic::riscv_vor_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vor_vv_u32m1_m:
	ID = Intrinsic::riscv_vor_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vor_vv_u32m2_m:
	ID = Intrinsic::riscv_vor_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vor_vv_u32m4_m:
	ID = Intrinsic::riscv_vor_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vor_vv_u32m8_m:
	ID = Intrinsic::riscv_vor_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vor_vx_u8m1_m:
	ID = Intrinsic::riscv_vor_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vor_vx_u8m2_m:
	ID = Intrinsic::riscv_vor_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vor_vx_u8m4_m:
	ID = Intrinsic::riscv_vor_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vor_vx_u8m8_m:
	ID = Intrinsic::riscv_vor_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vor_vx_u16m1_m:
	ID = Intrinsic::riscv_vor_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vor_vx_u16m2_m:
	ID = Intrinsic::riscv_vor_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vor_vx_u16m4_m:
	ID = Intrinsic::riscv_vor_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vor_vx_u16m8_m:
	ID = Intrinsic::riscv_vor_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vor_vx_u32m1_m:
	ID = Intrinsic::riscv_vor_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vor_vx_u32m2_m:
	ID = Intrinsic::riscv_vor_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vor_vx_u32m4_m:
	ID = Intrinsic::riscv_vor_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vor_vx_u32m8_m:
	ID = Intrinsic::riscv_vor_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vor_vi_u8m1_m:
	ID = Intrinsic::riscv_vor_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vor_vi_u8m2_m:
	ID = Intrinsic::riscv_vor_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vor_vi_u8m4_m:
	ID = Intrinsic::riscv_vor_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vor_vi_u8m8_m:
	ID = Intrinsic::riscv_vor_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vor_vi_u16m1_m:
	ID = Intrinsic::riscv_vor_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vor_vi_u16m2_m:
	ID = Intrinsic::riscv_vor_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vor_vi_u16m4_m:
	ID = Intrinsic::riscv_vor_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vor_vi_u16m8_m:
	ID = Intrinsic::riscv_vor_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vor_vi_u32m1_m:
	ID = Intrinsic::riscv_vor_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vor_vi_u32m2_m:
	ID = Intrinsic::riscv_vor_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vor_vi_u32m4_m:
	ID = Intrinsic::riscv_vor_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vor_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vor_vi_u32m8_m:
	ID = Intrinsic::riscv_vor_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u8m1_m:
	ID = Intrinsic::riscv_vxor_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u8m2_m:
	ID = Intrinsic::riscv_vxor_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u8m4_m:
	ID = Intrinsic::riscv_vxor_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u8m8_m:
	ID = Intrinsic::riscv_vxor_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u16m1_m:
	ID = Intrinsic::riscv_vxor_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u16m2_m:
	ID = Intrinsic::riscv_vxor_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u16m4_m:
	ID = Intrinsic::riscv_vxor_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u16m8_m:
	ID = Intrinsic::riscv_vxor_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u32m1_m:
	ID = Intrinsic::riscv_vxor_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u32m2_m:
	ID = Intrinsic::riscv_vxor_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u32m4_m:
	ID = Intrinsic::riscv_vxor_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vxor_vv_u32m8_m:
	ID = Intrinsic::riscv_vxor_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u8m1_m:
	ID = Intrinsic::riscv_vxor_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u8m2_m:
	ID = Intrinsic::riscv_vxor_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u8m4_m:
	ID = Intrinsic::riscv_vxor_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u8m8_m:
	ID = Intrinsic::riscv_vxor_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u16m1_m:
	ID = Intrinsic::riscv_vxor_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u16m2_m:
	ID = Intrinsic::riscv_vxor_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u16m4_m:
	ID = Intrinsic::riscv_vxor_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u16m8_m:
	ID = Intrinsic::riscv_vxor_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u32m1_m:
	ID = Intrinsic::riscv_vxor_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u32m2_m:
	ID = Intrinsic::riscv_vxor_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u32m4_m:
	ID = Intrinsic::riscv_vxor_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vxor_vx_u32m8_m:
	ID = Intrinsic::riscv_vxor_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u8m1_m:
	ID = Intrinsic::riscv_vxor_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u8m2_m:
	ID = Intrinsic::riscv_vxor_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u8m4_m:
	ID = Intrinsic::riscv_vxor_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u8m8_m:
	ID = Intrinsic::riscv_vxor_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u16m1_m:
	ID = Intrinsic::riscv_vxor_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u16m2_m:
	ID = Intrinsic::riscv_vxor_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u16m4_m:
	ID = Intrinsic::riscv_vxor_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u16m8_m:
	ID = Intrinsic::riscv_vxor_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u32m1_m:
	ID = Intrinsic::riscv_vxor_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u32m2_m:
	ID = Intrinsic::riscv_vxor_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u32m4_m:
	ID = Intrinsic::riscv_vxor_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vxor_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vxor_vi_u32m8_m:
	ID = Intrinsic::riscv_vxor_vi_32m8_m;
	break;

	//Vector Single-Width Bit Shift Functions
    case RISCV::BI__builtin_riscv_vsll_vv_i8m1:
    case RISCV::BI__builtin_riscv_vsll_vv_u8m1:
	ID = Intrinsic::riscv_vsll_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i8m2:
    case RISCV::BI__builtin_riscv_vsll_vv_u8m2:
	ID = Intrinsic::riscv_vsll_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i8m4:
    case RISCV::BI__builtin_riscv_vsll_vv_u8m4:
	ID = Intrinsic::riscv_vsll_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i8m8:
    case RISCV::BI__builtin_riscv_vsll_vv_u8m8:
	ID = Intrinsic::riscv_vsll_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i16m1:
    case RISCV::BI__builtin_riscv_vsll_vv_u16m1:
	ID = Intrinsic::riscv_vsll_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i16m2:
    case RISCV::BI__builtin_riscv_vsll_vv_u16m2:
	ID = Intrinsic::riscv_vsll_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i16m4:
    case RISCV::BI__builtin_riscv_vsll_vv_u16m4:
	ID = Intrinsic::riscv_vsll_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i16m8:
    case RISCV::BI__builtin_riscv_vsll_vv_u16m8:
	ID = Intrinsic::riscv_vsll_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i32m1:
    case RISCV::BI__builtin_riscv_vsll_vv_u32m1:
	ID = Intrinsic::riscv_vsll_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i32m2:
    case RISCV::BI__builtin_riscv_vsll_vv_u32m2:
	ID = Intrinsic::riscv_vsll_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i32m4:
    case RISCV::BI__builtin_riscv_vsll_vv_u32m4:
	ID = Intrinsic::riscv_vsll_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i32m8:
    case RISCV::BI__builtin_riscv_vsll_vv_u32m8:
	ID = Intrinsic::riscv_vsll_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i8m1:
    case RISCV::BI__builtin_riscv_vsll_vx_u8m1:
	ID = Intrinsic::riscv_vsll_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i8m2:
    case RISCV::BI__builtin_riscv_vsll_vx_u8m2:
	ID = Intrinsic::riscv_vsll_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i8m4:
    case RISCV::BI__builtin_riscv_vsll_vx_u8m4:
	ID = Intrinsic::riscv_vsll_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i8m8:
    case RISCV::BI__builtin_riscv_vsll_vx_u8m8:
	ID = Intrinsic::riscv_vsll_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i16m1:
    case RISCV::BI__builtin_riscv_vsll_vx_u16m1:
	ID = Intrinsic::riscv_vsll_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i16m2:
    case RISCV::BI__builtin_riscv_vsll_vx_u16m2:
	ID = Intrinsic::riscv_vsll_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i16m4:
    case RISCV::BI__builtin_riscv_vsll_vx_u16m4:
	ID = Intrinsic::riscv_vsll_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i16m8:
    case RISCV::BI__builtin_riscv_vsll_vx_u16m8:
	ID = Intrinsic::riscv_vsll_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i32m1:
    case RISCV::BI__builtin_riscv_vsll_vx_u32m1:
	ID = Intrinsic::riscv_vsll_vx_32m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i32m2:
    case RISCV::BI__builtin_riscv_vsll_vx_u32m2:
	ID = Intrinsic::riscv_vsll_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i32m4:
    case RISCV::BI__builtin_riscv_vsll_vx_u32m4:
	ID = Intrinsic::riscv_vsll_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i32m8:
    case RISCV::BI__builtin_riscv_vsll_vx_u32m8:
	ID = Intrinsic::riscv_vsll_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i8m1:
    case RISCV::BI__builtin_riscv_vsll_vi_u8m1:
	ID = Intrinsic::riscv_vsll_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i8m2:
    case RISCV::BI__builtin_riscv_vsll_vi_u8m2:
	ID = Intrinsic::riscv_vsll_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i8m4:
    case RISCV::BI__builtin_riscv_vsll_vi_u8m4:
	ID = Intrinsic::riscv_vsll_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i8m8:
    case RISCV::BI__builtin_riscv_vsll_vi_u8m8:
	ID = Intrinsic::riscv_vsll_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i16m1:
    case RISCV::BI__builtin_riscv_vsll_vi_u16m1:
	ID = Intrinsic::riscv_vsll_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i16m2:
    case RISCV::BI__builtin_riscv_vsll_vi_u16m2:
	ID = Intrinsic::riscv_vsll_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i16m4:
    case RISCV::BI__builtin_riscv_vsll_vi_u16m4:
	ID = Intrinsic::riscv_vsll_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i16m8:
    case RISCV::BI__builtin_riscv_vsll_vi_u16m8:
	ID = Intrinsic::riscv_vsll_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i32m1:
    case RISCV::BI__builtin_riscv_vsll_vi_u32m1:
	ID = Intrinsic::riscv_vsll_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i32m2:
    case RISCV::BI__builtin_riscv_vsll_vi_u32m2:
	ID = Intrinsic::riscv_vsll_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i32m4:
    case RISCV::BI__builtin_riscv_vsll_vi_u32m4:
	ID = Intrinsic::riscv_vsll_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i32m8:
    case RISCV::BI__builtin_riscv_vsll_vi_u32m8:
	ID = Intrinsic::riscv_vsll_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u8m1:
	ID = Intrinsic::riscv_vsrl_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u8m2:
	ID = Intrinsic::riscv_vsrl_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u8m4:
	ID = Intrinsic::riscv_vsrl_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u8m8:
	ID = Intrinsic::riscv_vsrl_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u16m1:
	ID = Intrinsic::riscv_vsrl_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u16m2:
	ID = Intrinsic::riscv_vsrl_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u16m4:
	ID = Intrinsic::riscv_vsrl_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u16m8:
	ID = Intrinsic::riscv_vsrl_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u32m1:
	ID = Intrinsic::riscv_vsrl_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u32m2:
	ID = Intrinsic::riscv_vsrl_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u32m4:
	ID = Intrinsic::riscv_vsrl_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u32m8:
	ID = Intrinsic::riscv_vsrl_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u8m1:
	ID = Intrinsic::riscv_vsrl_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u8m2:
	ID = Intrinsic::riscv_vsrl_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u8m4:
	ID = Intrinsic::riscv_vsrl_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u8m8:
	ID = Intrinsic::riscv_vsrl_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u16m1:
	ID = Intrinsic::riscv_vsrl_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u16m2:
	ID = Intrinsic::riscv_vsrl_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u16m4:
	ID = Intrinsic::riscv_vsrl_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u16m8:
	ID = Intrinsic::riscv_vsrl_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u32m1:
	ID = Intrinsic::riscv_vsrl_vx_32m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u32m2:
	ID = Intrinsic::riscv_vsrl_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u32m4:
	ID = Intrinsic::riscv_vsrl_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u32m8:
	ID = Intrinsic::riscv_vsrl_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u8m1:
	ID = Intrinsic::riscv_vsrl_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u8m2:
	ID = Intrinsic::riscv_vsrl_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u8m4:
	ID = Intrinsic::riscv_vsrl_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u8m8:
	ID = Intrinsic::riscv_vsrl_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u16m1:
	ID = Intrinsic::riscv_vsrl_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u16m2:
	ID = Intrinsic::riscv_vsrl_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u16m4:
	ID = Intrinsic::riscv_vsrl_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u16m8:
	ID = Intrinsic::riscv_vsrl_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u32m1:
	ID = Intrinsic::riscv_vsrl_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u32m2:
	ID = Intrinsic::riscv_vsrl_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u32m4:
	ID = Intrinsic::riscv_vsrl_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u32m8:
	ID = Intrinsic::riscv_vsrl_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i8m1:
	ID = Intrinsic::riscv_vsra_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i8m2:
	ID = Intrinsic::riscv_vsra_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i8m4:
	ID = Intrinsic::riscv_vsra_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i8m8:
	ID = Intrinsic::riscv_vsra_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i16m1:
	ID = Intrinsic::riscv_vsra_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i16m2:
	ID = Intrinsic::riscv_vsra_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i16m4:
	ID = Intrinsic::riscv_vsra_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i16m8:
	ID = Intrinsic::riscv_vsra_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i32m1:
	ID = Intrinsic::riscv_vsra_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i32m2:
	ID = Intrinsic::riscv_vsra_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i32m4:
	ID = Intrinsic::riscv_vsra_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i32m8:
	ID = Intrinsic::riscv_vsra_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i8m1:
	ID = Intrinsic::riscv_vsra_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i8m2:
	ID = Intrinsic::riscv_vsra_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i8m4:
	ID = Intrinsic::riscv_vsra_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i8m8:
	ID = Intrinsic::riscv_vsra_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i16m1:
	ID = Intrinsic::riscv_vsra_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i16m2:
	ID = Intrinsic::riscv_vsra_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i16m4:
	ID = Intrinsic::riscv_vsra_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i16m8:
	ID = Intrinsic::riscv_vsra_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i32m1:
	ID = Intrinsic::riscv_vsra_vx_32m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i32m2:
	ID = Intrinsic::riscv_vsra_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i32m4:
	ID = Intrinsic::riscv_vsra_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i32m8:
	ID = Intrinsic::riscv_vsra_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i8m1:
	ID = Intrinsic::riscv_vsra_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i8m2:
	ID = Intrinsic::riscv_vsra_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i8m4:
	ID = Intrinsic::riscv_vsra_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i8m8:
	ID = Intrinsic::riscv_vsra_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i16m1:
	ID = Intrinsic::riscv_vsra_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i16m2:
	ID = Intrinsic::riscv_vsra_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i16m4:
	ID = Intrinsic::riscv_vsra_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i16m8:
	ID = Intrinsic::riscv_vsra_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i32m1:
	ID = Intrinsic::riscv_vsra_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i32m2:
	ID = Intrinsic::riscv_vsra_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i32m4:
	ID = Intrinsic::riscv_vsra_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i32m8:
	ID = Intrinsic::riscv_vsra_vi_32m8;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vsll_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u8m1_m:
	ID = Intrinsic::riscv_vsll_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u8m2_m:
	ID = Intrinsic::riscv_vsll_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u8m4_m:
	ID = Intrinsic::riscv_vsll_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u8m8_m:
	ID = Intrinsic::riscv_vsll_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u16m1_m:
	ID = Intrinsic::riscv_vsll_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u16m2_m:
	ID = Intrinsic::riscv_vsll_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u16m4_m:
	ID = Intrinsic::riscv_vsll_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u16m8_m:
	ID = Intrinsic::riscv_vsll_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u32m1_m:
	ID = Intrinsic::riscv_vsll_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u32m2_m:
	ID = Intrinsic::riscv_vsll_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u32m4_m:
	ID = Intrinsic::riscv_vsll_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vsll_vv_u32m8_m:
	ID = Intrinsic::riscv_vsll_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u8m1_m:
	ID = Intrinsic::riscv_vsll_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u8m2_m:
	ID = Intrinsic::riscv_vsll_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u8m4_m:
	ID = Intrinsic::riscv_vsll_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u8m8_m:
	ID = Intrinsic::riscv_vsll_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u16m1_m:
	ID = Intrinsic::riscv_vsll_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u16m2_m:
	ID = Intrinsic::riscv_vsll_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u16m4_m:
	ID = Intrinsic::riscv_vsll_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u16m8_m:
	ID = Intrinsic::riscv_vsll_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u32m1_m:
	ID = Intrinsic::riscv_vsll_vx_32m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u32m2_m:
	ID = Intrinsic::riscv_vsll_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u32m4_m:
	ID = Intrinsic::riscv_vsll_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vsll_vx_u32m8_m:
	ID = Intrinsic::riscv_vsll_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u8m1_m:
	ID = Intrinsic::riscv_vsll_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u8m2_m:
	ID = Intrinsic::riscv_vsll_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u8m4_m:
	ID = Intrinsic::riscv_vsll_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u8m8_m:
	ID = Intrinsic::riscv_vsll_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u16m1_m:
	ID = Intrinsic::riscv_vsll_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u16m2_m:
	ID = Intrinsic::riscv_vsll_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u16m4_m:
	ID = Intrinsic::riscv_vsll_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u16m8_m:
	ID = Intrinsic::riscv_vsll_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u32m1_m:
	ID = Intrinsic::riscv_vsll_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u32m2_m:
	ID = Intrinsic::riscv_vsll_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u32m4_m:
	ID = Intrinsic::riscv_vsll_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsll_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vsll_vi_u32m8_m:
	ID = Intrinsic::riscv_vsll_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u8m1_m:
	ID = Intrinsic::riscv_vsrl_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u8m2_m:
	ID = Intrinsic::riscv_vsrl_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u8m4_m:
	ID = Intrinsic::riscv_vsrl_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u8m8_m:
	ID = Intrinsic::riscv_vsrl_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u16m1_m:
	ID = Intrinsic::riscv_vsrl_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u16m2_m:
	ID = Intrinsic::riscv_vsrl_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u16m4_m:
	ID = Intrinsic::riscv_vsrl_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u16m8_m:
	ID = Intrinsic::riscv_vsrl_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u32m1_m:
	ID = Intrinsic::riscv_vsrl_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u32m2_m:
	ID = Intrinsic::riscv_vsrl_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u32m4_m:
	ID = Intrinsic::riscv_vsrl_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vv_u32m8_m:
	ID = Intrinsic::riscv_vsrl_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u8m1_m:
	ID = Intrinsic::riscv_vsrl_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u8m2_m:
	ID = Intrinsic::riscv_vsrl_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u8m4_m:
	ID = Intrinsic::riscv_vsrl_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u8m8_m:
	ID = Intrinsic::riscv_vsrl_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u16m1_m:
	ID = Intrinsic::riscv_vsrl_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u16m2_m:
	ID = Intrinsic::riscv_vsrl_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u16m4_m:
	ID = Intrinsic::riscv_vsrl_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u16m8_m:
	ID = Intrinsic::riscv_vsrl_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u32m1_m:
	ID = Intrinsic::riscv_vsrl_vx_32m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u32m2_m:
	ID = Intrinsic::riscv_vsrl_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u32m4_m:
	ID = Intrinsic::riscv_vsrl_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vx_u32m8_m:
	ID = Intrinsic::riscv_vsrl_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u8m1_m:
	ID = Intrinsic::riscv_vsrl_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u8m2_m:
	ID = Intrinsic::riscv_vsrl_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u8m4_m:
	ID = Intrinsic::riscv_vsrl_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u8m8_m:
	ID = Intrinsic::riscv_vsrl_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u16m1_m:
	ID = Intrinsic::riscv_vsrl_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u16m2_m:
	ID = Intrinsic::riscv_vsrl_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u16m4_m:
	ID = Intrinsic::riscv_vsrl_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u16m8_m:
	ID = Intrinsic::riscv_vsrl_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u32m1_m:
	ID = Intrinsic::riscv_vsrl_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u32m2_m:
	ID = Intrinsic::riscv_vsrl_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u32m4_m:
	ID = Intrinsic::riscv_vsrl_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsrl_vi_u32m8_m:
	ID = Intrinsic::riscv_vsrl_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i8m1_m:
	ID = Intrinsic::riscv_vsra_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i8m2_m:
	ID = Intrinsic::riscv_vsra_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i8m4_m:
	ID = Intrinsic::riscv_vsra_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i8m8_m:
	ID = Intrinsic::riscv_vsra_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i16m1_m:
	ID = Intrinsic::riscv_vsra_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i16m2_m:
	ID = Intrinsic::riscv_vsra_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i16m4_m:
	ID = Intrinsic::riscv_vsra_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i16m8_m:
	ID = Intrinsic::riscv_vsra_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i32m1_m:
	ID = Intrinsic::riscv_vsra_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i32m2_m:
	ID = Intrinsic::riscv_vsra_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i32m4_m:
	ID = Intrinsic::riscv_vsra_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vv_i32m8_m:
	ID = Intrinsic::riscv_vsra_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i8m1_m:
	ID = Intrinsic::riscv_vsra_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i8m2_m:
	ID = Intrinsic::riscv_vsra_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i8m4_m:
	ID = Intrinsic::riscv_vsra_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i8m8_m:
	ID = Intrinsic::riscv_vsra_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i16m1_m:
	ID = Intrinsic::riscv_vsra_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i16m2_m:
	ID = Intrinsic::riscv_vsra_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i16m4_m:
	ID = Intrinsic::riscv_vsra_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i16m8_m:
	ID = Intrinsic::riscv_vsra_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i32m1_m:
	ID = Intrinsic::riscv_vsra_vx_32m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i32m2_m:
	ID = Intrinsic::riscv_vsra_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i32m4_m:
	ID = Intrinsic::riscv_vsra_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vx_i32m8_m:
	ID = Intrinsic::riscv_vsra_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i8m1_m:
	ID = Intrinsic::riscv_vsra_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i8m2_m:
	ID = Intrinsic::riscv_vsra_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i8m4_m:
	ID = Intrinsic::riscv_vsra_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i8m8_m:
	ID = Intrinsic::riscv_vsra_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i16m1_m:
	ID = Intrinsic::riscv_vsra_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i16m2_m:
	ID = Intrinsic::riscv_vsra_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i16m4_m:
	ID = Intrinsic::riscv_vsra_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i16m8_m:
	ID = Intrinsic::riscv_vsra_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i32m1_m:
	ID = Intrinsic::riscv_vsra_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i32m2_m:
	ID = Intrinsic::riscv_vsra_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i32m4_m:
	ID = Intrinsic::riscv_vsra_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsra_vi_i32m8_m:
	ID = Intrinsic::riscv_vsra_vi_32m8_m;
	break;

	//Vector Narrowing Integer Right Shift Functions
    case RISCV::BI__builtin_riscv_vnsrl_wv_u8m1:
	ID = Intrinsic::riscv_vnsrl_wv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wv_u8m2:
	ID = Intrinsic::riscv_vnsrl_wv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wv_u8m4:
	ID = Intrinsic::riscv_vnsrl_wv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wv_u16m1:
	ID = Intrinsic::riscv_vnsrl_wv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wv_u16m2:
	ID = Intrinsic::riscv_vnsrl_wv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wv_u16m4:
	ID = Intrinsic::riscv_vnsrl_wv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u8m1:
	ID = Intrinsic::riscv_vnsrl_wx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u8m2:
	ID = Intrinsic::riscv_vnsrl_wx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u8m4:
	ID = Intrinsic::riscv_vnsrl_wx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u16m1:
	ID = Intrinsic::riscv_vnsrl_wx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u16m2:
	ID = Intrinsic::riscv_vnsrl_wx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u16m4:
	ID = Intrinsic::riscv_vnsrl_wx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u8m1:
	ID = Intrinsic::riscv_vnsrl_wi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u8m2:
	ID = Intrinsic::riscv_vnsrl_wi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u8m4:
	ID = Intrinsic::riscv_vnsrl_wi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u16m1:
	ID = Intrinsic::riscv_vnsrl_wi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u16m2:
	ID = Intrinsic::riscv_vnsrl_wi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u16m4:
	ID = Intrinsic::riscv_vnsrl_wi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i8m1:
	ID = Intrinsic::riscv_vnsra_wv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i8m2:
	ID = Intrinsic::riscv_vnsra_wv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i8m4:
	ID = Intrinsic::riscv_vnsra_wv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i16m1:
	ID = Intrinsic::riscv_vnsra_wv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i16m2:
	ID = Intrinsic::riscv_vnsra_wv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i16m4:
	ID = Intrinsic::riscv_vnsra_wv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i8m1:
	ID = Intrinsic::riscv_vnsra_wx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i8m2:
	ID = Intrinsic::riscv_vnsra_wx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i8m4:
	ID = Intrinsic::riscv_vnsra_wx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i16m1:
	ID = Intrinsic::riscv_vnsra_wx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i16m2:
	ID = Intrinsic::riscv_vnsra_wx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i16m4:
	ID = Intrinsic::riscv_vnsra_wx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i8m1:
	ID = Intrinsic::riscv_vnsra_wi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i8m2:
	ID = Intrinsic::riscv_vnsra_wi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i8m4:
	ID = Intrinsic::riscv_vnsra_wi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i16m1:
	ID = Intrinsic::riscv_vnsra_wi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i16m2:
	ID = Intrinsic::riscv_vnsra_wi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i16m4:
	ID = Intrinsic::riscv_vnsra_wi_16m4;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vnsrl_wv_u8m1_m:
	ID = Intrinsic::riscv_vnsrl_wv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wv_u8m2_m:
	ID = Intrinsic::riscv_vnsrl_wv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wv_u8m4_m:
	ID = Intrinsic::riscv_vnsrl_wv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wv_u16m1_m:
	ID = Intrinsic::riscv_vnsrl_wv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wv_u16m2_m:
	ID = Intrinsic::riscv_vnsrl_wv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wv_u16m4_m:
	ID = Intrinsic::riscv_vnsrl_wv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u8m1_m:
	ID = Intrinsic::riscv_vnsrl_wx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u8m2_m:
	ID = Intrinsic::riscv_vnsrl_wx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u8m4_m:
	ID = Intrinsic::riscv_vnsrl_wx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u16m1_m:
	ID = Intrinsic::riscv_vnsrl_wx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u16m2_m:
	ID = Intrinsic::riscv_vnsrl_wx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wx_u16m4_m:
	ID = Intrinsic::riscv_vnsrl_wx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u8m1_m:
	ID = Intrinsic::riscv_vnsrl_wi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u8m2_m:
	ID = Intrinsic::riscv_vnsrl_wi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u8m4_m:
	ID = Intrinsic::riscv_vnsrl_wi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u16m1_m:
	ID = Intrinsic::riscv_vnsrl_wi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u16m2_m:
	ID = Intrinsic::riscv_vnsrl_wi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnsrl_wi_u16m4_m:
	ID = Intrinsic::riscv_vnsrl_wi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i8m1_m:
	ID = Intrinsic::riscv_vnsra_wv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i8m2_m:
	ID = Intrinsic::riscv_vnsra_wv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i8m4_m:
	ID = Intrinsic::riscv_vnsra_wv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i16m1_m:
	ID = Intrinsic::riscv_vnsra_wv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i16m2_m:
	ID = Intrinsic::riscv_vnsra_wv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wv_i16m4_m:
	ID = Intrinsic::riscv_vnsra_wv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i8m1_m:
	ID = Intrinsic::riscv_vnsra_wx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i8m2_m:
	ID = Intrinsic::riscv_vnsra_wx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i8m4_m:
	ID = Intrinsic::riscv_vnsra_wx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i16m1_m:
	ID = Intrinsic::riscv_vnsra_wx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i16m2_m:
	ID = Intrinsic::riscv_vnsra_wx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wx_i16m4_m:
	ID = Intrinsic::riscv_vnsra_wx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i8m1_m:
	ID = Intrinsic::riscv_vnsra_wi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i8m2_m:
	ID = Intrinsic::riscv_vnsra_wi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i8m4_m:
	ID = Intrinsic::riscv_vnsra_wi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i16m1_m:
	ID = Intrinsic::riscv_vnsra_wi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i16m2_m:
	ID = Intrinsic::riscv_vnsra_wi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnsra_wi_i16m4_m:
	ID = Intrinsic::riscv_vnsra_wi_16m4_m;
	break;

	//Vector Integer Comparison Functions
    case RISCV::BI__builtin_riscv_vmseq_vv_i8m1:
    case RISCV::BI__builtin_riscv_vmseq_vv_u8m1:
	ID = Intrinsic::riscv_vmseq_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i8m2:
    case RISCV::BI__builtin_riscv_vmseq_vv_u8m2:
	ID = Intrinsic::riscv_vmseq_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i8m4:
    case RISCV::BI__builtin_riscv_vmseq_vv_u8m4:
	ID = Intrinsic::riscv_vmseq_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i8m8:
    case RISCV::BI__builtin_riscv_vmseq_vv_u8m8:
	ID = Intrinsic::riscv_vmseq_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i16m1:
    case RISCV::BI__builtin_riscv_vmseq_vv_u16m1:
	ID = Intrinsic::riscv_vmseq_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i16m2:
    case RISCV::BI__builtin_riscv_vmseq_vv_u16m2:
	ID = Intrinsic::riscv_vmseq_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i16m4:
    case RISCV::BI__builtin_riscv_vmseq_vv_u16m4:
	ID = Intrinsic::riscv_vmseq_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i16m8:
    case RISCV::BI__builtin_riscv_vmseq_vv_u16m8:
	ID = Intrinsic::riscv_vmseq_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i32m1:
    case RISCV::BI__builtin_riscv_vmseq_vv_u32m1:
	ID = Intrinsic::riscv_vmseq_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i32m2:
    case RISCV::BI__builtin_riscv_vmseq_vv_u32m2:
	ID = Intrinsic::riscv_vmseq_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i32m4:
    case RISCV::BI__builtin_riscv_vmseq_vv_u32m4:
	ID = Intrinsic::riscv_vmseq_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i32m8:
    case RISCV::BI__builtin_riscv_vmseq_vv_u32m8:
	ID = Intrinsic::riscv_vmseq_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i8m1:
    case RISCV::BI__builtin_riscv_vmseq_vx_u8m1:
	ID = Intrinsic::riscv_vmseq_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i8m2:
    case RISCV::BI__builtin_riscv_vmseq_vx_u8m2:
	ID = Intrinsic::riscv_vmseq_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i8m4:
    case RISCV::BI__builtin_riscv_vmseq_vx_u8m4:
	ID = Intrinsic::riscv_vmseq_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i8m8:
    case RISCV::BI__builtin_riscv_vmseq_vx_u8m8:
	ID = Intrinsic::riscv_vmseq_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i16m1:
    case RISCV::BI__builtin_riscv_vmseq_vx_u16m1:
	ID = Intrinsic::riscv_vmseq_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i16m2:
    case RISCV::BI__builtin_riscv_vmseq_vx_u16m2:
	ID = Intrinsic::riscv_vmseq_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i16m4:
    case RISCV::BI__builtin_riscv_vmseq_vx_u16m4:
	ID = Intrinsic::riscv_vmseq_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i16m8:
    case RISCV::BI__builtin_riscv_vmseq_vx_u16m8:
	ID = Intrinsic::riscv_vmseq_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i32m1:
    case RISCV::BI__builtin_riscv_vmseq_vx_u32m1:
	ID = Intrinsic::riscv_vmseq_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i32m2:
    case RISCV::BI__builtin_riscv_vmseq_vx_u32m2:
	ID = Intrinsic::riscv_vmseq_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i32m4:
    case RISCV::BI__builtin_riscv_vmseq_vx_u32m4:
	ID = Intrinsic::riscv_vmseq_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i32m8:
    case RISCV::BI__builtin_riscv_vmseq_vx_u32m8:
	ID = Intrinsic::riscv_vmseq_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i8m1:
    case RISCV::BI__builtin_riscv_vmseq_vi_u8m1:
	ID = Intrinsic::riscv_vmseq_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i8m2:
    case RISCV::BI__builtin_riscv_vmseq_vi_u8m2:
	ID = Intrinsic::riscv_vmseq_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i8m4:
    case RISCV::BI__builtin_riscv_vmseq_vi_u8m4:
	ID = Intrinsic::riscv_vmseq_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i8m8:
    case RISCV::BI__builtin_riscv_vmseq_vi_u8m8:
	ID = Intrinsic::riscv_vmseq_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i16m1:
    case RISCV::BI__builtin_riscv_vmseq_vi_u16m1:
	ID = Intrinsic::riscv_vmseq_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i16m2:
    case RISCV::BI__builtin_riscv_vmseq_vi_u16m2:
	ID = Intrinsic::riscv_vmseq_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i16m4:
    case RISCV::BI__builtin_riscv_vmseq_vi_u16m4:
	ID = Intrinsic::riscv_vmseq_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i16m8:
    case RISCV::BI__builtin_riscv_vmseq_vi_u16m8:
	ID = Intrinsic::riscv_vmseq_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i32m1:
    case RISCV::BI__builtin_riscv_vmseq_vi_u32m1:
	ID = Intrinsic::riscv_vmseq_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i32m2:
    case RISCV::BI__builtin_riscv_vmseq_vi_u32m2:
	ID = Intrinsic::riscv_vmseq_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i32m4:
    case RISCV::BI__builtin_riscv_vmseq_vi_u32m4:
	ID = Intrinsic::riscv_vmseq_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i32m8:
    case RISCV::BI__builtin_riscv_vmseq_vi_u32m8:
	ID = Intrinsic::riscv_vmseq_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i8m1:
    case RISCV::BI__builtin_riscv_vmsne_vv_u8m1:
	ID = Intrinsic::riscv_vmsne_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i8m2:
    case RISCV::BI__builtin_riscv_vmsne_vv_u8m2:
	ID = Intrinsic::riscv_vmsne_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i8m4:
    case RISCV::BI__builtin_riscv_vmsne_vv_u8m4:
	ID = Intrinsic::riscv_vmsne_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i8m8:
    case RISCV::BI__builtin_riscv_vmsne_vv_u8m8:
	ID = Intrinsic::riscv_vmsne_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i16m1:
    case RISCV::BI__builtin_riscv_vmsne_vv_u16m1:
	ID = Intrinsic::riscv_vmsne_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i16m2:
    case RISCV::BI__builtin_riscv_vmsne_vv_u16m2:
	ID = Intrinsic::riscv_vmsne_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i16m4:
    case RISCV::BI__builtin_riscv_vmsne_vv_u16m4:
	ID = Intrinsic::riscv_vmsne_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i16m8:
    case RISCV::BI__builtin_riscv_vmsne_vv_u16m8:
	ID = Intrinsic::riscv_vmsne_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i32m1:
    case RISCV::BI__builtin_riscv_vmsne_vv_u32m1:
	ID = Intrinsic::riscv_vmsne_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i32m2:
    case RISCV::BI__builtin_riscv_vmsne_vv_u32m2:
	ID = Intrinsic::riscv_vmsne_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i32m4:
    case RISCV::BI__builtin_riscv_vmsne_vv_u32m4:
	ID = Intrinsic::riscv_vmsne_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i32m8:
    case RISCV::BI__builtin_riscv_vmsne_vv_u32m8:
	ID = Intrinsic::riscv_vmsne_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i8m1:
    case RISCV::BI__builtin_riscv_vmsne_vx_u8m1:
	ID = Intrinsic::riscv_vmsne_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i8m2:
    case RISCV::BI__builtin_riscv_vmsne_vx_u8m2:
	ID = Intrinsic::riscv_vmsne_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i8m4:
    case RISCV::BI__builtin_riscv_vmsne_vx_u8m4:
	ID = Intrinsic::riscv_vmsne_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i8m8:
    case RISCV::BI__builtin_riscv_vmsne_vx_u8m8:
	ID = Intrinsic::riscv_vmsne_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i16m1:
    case RISCV::BI__builtin_riscv_vmsne_vx_u16m1:
	ID = Intrinsic::riscv_vmsne_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i16m2:
    case RISCV::BI__builtin_riscv_vmsne_vx_u16m2:
	ID = Intrinsic::riscv_vmsne_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i16m4:
    case RISCV::BI__builtin_riscv_vmsne_vx_u16m4:
	ID = Intrinsic::riscv_vmsne_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i16m8:
    case RISCV::BI__builtin_riscv_vmsne_vx_u16m8:
	ID = Intrinsic::riscv_vmsne_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i32m1:
    case RISCV::BI__builtin_riscv_vmsne_vx_u32m1:
	ID = Intrinsic::riscv_vmsne_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i32m2:
    case RISCV::BI__builtin_riscv_vmsne_vx_u32m2:
	ID = Intrinsic::riscv_vmsne_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i32m4:
    case RISCV::BI__builtin_riscv_vmsne_vx_u32m4:
	ID = Intrinsic::riscv_vmsne_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i32m8:
    case RISCV::BI__builtin_riscv_vmsne_vx_u32m8:
	ID = Intrinsic::riscv_vmsne_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i8m1:
    case RISCV::BI__builtin_riscv_vmsne_vi_u8m1:
	ID = Intrinsic::riscv_vmsne_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i8m2:
    case RISCV::BI__builtin_riscv_vmsne_vi_u8m2:
	ID = Intrinsic::riscv_vmsne_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i8m4:
    case RISCV::BI__builtin_riscv_vmsne_vi_u8m4:
	ID = Intrinsic::riscv_vmsne_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i8m8:
    case RISCV::BI__builtin_riscv_vmsne_vi_u8m8:
	ID = Intrinsic::riscv_vmsne_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i16m1:
    case RISCV::BI__builtin_riscv_vmsne_vi_u16m1:
	ID = Intrinsic::riscv_vmsne_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i16m2:
    case RISCV::BI__builtin_riscv_vmsne_vi_u16m2:
	ID = Intrinsic::riscv_vmsne_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i16m4:
    case RISCV::BI__builtin_riscv_vmsne_vi_u16m4:
	ID = Intrinsic::riscv_vmsne_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i16m8:
    case RISCV::BI__builtin_riscv_vmsne_vi_u16m8:
	ID = Intrinsic::riscv_vmsne_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i32m1:
    case RISCV::BI__builtin_riscv_vmsne_vi_u32m1:
	ID = Intrinsic::riscv_vmsne_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i32m2:
    case RISCV::BI__builtin_riscv_vmsne_vi_u32m2:
	ID = Intrinsic::riscv_vmsne_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i32m4:
    case RISCV::BI__builtin_riscv_vmsne_vi_u32m4:
	ID = Intrinsic::riscv_vmsne_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i32m8:
    case RISCV::BI__builtin_riscv_vmsne_vi_u32m8:
	ID = Intrinsic::riscv_vmsne_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u8m1:
	ID = Intrinsic::riscv_vmsltu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u8m2:
	ID = Intrinsic::riscv_vmsltu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u8m4:
	ID = Intrinsic::riscv_vmsltu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u8m8:
	ID = Intrinsic::riscv_vmsltu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u16m1:
	ID = Intrinsic::riscv_vmsltu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u16m2:
	ID = Intrinsic::riscv_vmsltu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u16m4:
	ID = Intrinsic::riscv_vmsltu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u16m8:
	ID = Intrinsic::riscv_vmsltu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u32m1:
	ID = Intrinsic::riscv_vmsltu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u32m2:
	ID = Intrinsic::riscv_vmsltu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u32m4:
	ID = Intrinsic::riscv_vmsltu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u32m8:
	ID = Intrinsic::riscv_vmsltu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u8m1:
	ID = Intrinsic::riscv_vmsltu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u8m2:
	ID = Intrinsic::riscv_vmsltu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u8m4:
	ID = Intrinsic::riscv_vmsltu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u8m8:
	ID = Intrinsic::riscv_vmsltu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u16m1:
	ID = Intrinsic::riscv_vmsltu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u16m2:
	ID = Intrinsic::riscv_vmsltu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u16m4:
	ID = Intrinsic::riscv_vmsltu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u16m8:
	ID = Intrinsic::riscv_vmsltu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u32m1:
	ID = Intrinsic::riscv_vmsltu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u32m2:
	ID = Intrinsic::riscv_vmsltu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u32m4:
	ID = Intrinsic::riscv_vmsltu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u32m8:
	ID = Intrinsic::riscv_vmsltu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i8m1:
	ID = Intrinsic::riscv_vmslt_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i8m2:
	ID = Intrinsic::riscv_vmslt_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i8m4:
	ID = Intrinsic::riscv_vmslt_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i8m8:
	ID = Intrinsic::riscv_vmslt_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i16m1:
	ID = Intrinsic::riscv_vmslt_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i16m2:
	ID = Intrinsic::riscv_vmslt_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i16m4:
	ID = Intrinsic::riscv_vmslt_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i16m8:
	ID = Intrinsic::riscv_vmslt_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i32m1:
	ID = Intrinsic::riscv_vmslt_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i32m2:
	ID = Intrinsic::riscv_vmslt_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i32m4:
	ID = Intrinsic::riscv_vmslt_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i32m8:
	ID = Intrinsic::riscv_vmslt_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i8m1:
	ID = Intrinsic::riscv_vmslt_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i8m2:
	ID = Intrinsic::riscv_vmslt_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i8m4:
	ID = Intrinsic::riscv_vmslt_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i8m8:
	ID = Intrinsic::riscv_vmslt_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i16m1:
	ID = Intrinsic::riscv_vmslt_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i16m2:
	ID = Intrinsic::riscv_vmslt_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i16m4:
	ID = Intrinsic::riscv_vmslt_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i16m8:
	ID = Intrinsic::riscv_vmslt_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i32m1:
	ID = Intrinsic::riscv_vmslt_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i32m2:
	ID = Intrinsic::riscv_vmslt_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i32m4:
	ID = Intrinsic::riscv_vmslt_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i32m8:
	ID = Intrinsic::riscv_vmslt_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u8m1:
	ID = Intrinsic::riscv_vmsleu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u8m2:
	ID = Intrinsic::riscv_vmsleu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u8m4:
	ID = Intrinsic::riscv_vmsleu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u8m8:
	ID = Intrinsic::riscv_vmsleu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u16m1:
	ID = Intrinsic::riscv_vmsleu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u16m2:
	ID = Intrinsic::riscv_vmsleu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u16m4:
	ID = Intrinsic::riscv_vmsleu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u16m8:
	ID = Intrinsic::riscv_vmsleu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u32m1:
	ID = Intrinsic::riscv_vmsleu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u32m2:
	ID = Intrinsic::riscv_vmsleu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u32m4:
	ID = Intrinsic::riscv_vmsleu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u32m8:
	ID = Intrinsic::riscv_vmsleu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u8m1:
	ID = Intrinsic::riscv_vmsleu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u8m2:
	ID = Intrinsic::riscv_vmsleu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u8m4:
	ID = Intrinsic::riscv_vmsleu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u8m8:
	ID = Intrinsic::riscv_vmsleu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u16m1:
	ID = Intrinsic::riscv_vmsleu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u16m2:
	ID = Intrinsic::riscv_vmsleu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u16m4:
	ID = Intrinsic::riscv_vmsleu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u16m8:
	ID = Intrinsic::riscv_vmsleu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u32m1:
	ID = Intrinsic::riscv_vmsleu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u32m2:
	ID = Intrinsic::riscv_vmsleu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u32m4:
	ID = Intrinsic::riscv_vmsleu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u32m8:
	ID = Intrinsic::riscv_vmsleu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u8m1:
	ID = Intrinsic::riscv_vmsleu_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u8m2:
	ID = Intrinsic::riscv_vmsleu_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u8m4:
	ID = Intrinsic::riscv_vmsleu_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u8m8:
	ID = Intrinsic::riscv_vmsleu_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u16m1:
	ID = Intrinsic::riscv_vmsleu_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u16m2:
	ID = Intrinsic::riscv_vmsleu_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u16m4:
	ID = Intrinsic::riscv_vmsleu_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u16m8:
	ID = Intrinsic::riscv_vmsleu_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u32m1:
	ID = Intrinsic::riscv_vmsleu_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u32m2:
	ID = Intrinsic::riscv_vmsleu_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u32m4:
	ID = Intrinsic::riscv_vmsleu_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u32m8:
	ID = Intrinsic::riscv_vmsleu_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i8m1:
	ID = Intrinsic::riscv_vmsle_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i8m2:
	ID = Intrinsic::riscv_vmsle_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i8m4:
	ID = Intrinsic::riscv_vmsle_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i8m8:
	ID = Intrinsic::riscv_vmsle_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i16m1:
	ID = Intrinsic::riscv_vmsle_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i16m2:
	ID = Intrinsic::riscv_vmsle_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i16m4:
	ID = Intrinsic::riscv_vmsle_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i16m8:
	ID = Intrinsic::riscv_vmsle_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i32m1:
	ID = Intrinsic::riscv_vmsle_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i32m2:
	ID = Intrinsic::riscv_vmsle_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i32m4:
	ID = Intrinsic::riscv_vmsle_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i32m8:
	ID = Intrinsic::riscv_vmsle_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i8m1:
	ID = Intrinsic::riscv_vmsle_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i8m2:
	ID = Intrinsic::riscv_vmsle_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i8m4:
	ID = Intrinsic::riscv_vmsle_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i8m8:
	ID = Intrinsic::riscv_vmsle_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i16m1:
	ID = Intrinsic::riscv_vmsle_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i16m2:
	ID = Intrinsic::riscv_vmsle_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i16m4:
	ID = Intrinsic::riscv_vmsle_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i16m8:
	ID = Intrinsic::riscv_vmsle_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i32m1:
	ID = Intrinsic::riscv_vmsle_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i32m2:
	ID = Intrinsic::riscv_vmsle_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i32m4:
	ID = Intrinsic::riscv_vmsle_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i32m8:
	ID = Intrinsic::riscv_vmsle_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i8m1:
	ID = Intrinsic::riscv_vmsle_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i8m2:
	ID = Intrinsic::riscv_vmsle_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i8m4:
	ID = Intrinsic::riscv_vmsle_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i8m8:
	ID = Intrinsic::riscv_vmsle_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i16m1:
	ID = Intrinsic::riscv_vmsle_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i16m2:
	ID = Intrinsic::riscv_vmsle_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i16m4:
	ID = Intrinsic::riscv_vmsle_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i16m8:
	ID = Intrinsic::riscv_vmsle_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i32m1:
	ID = Intrinsic::riscv_vmsle_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i32m2:
	ID = Intrinsic::riscv_vmsle_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i32m4:
	ID = Intrinsic::riscv_vmsle_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i32m8:
	ID = Intrinsic::riscv_vmsle_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u8m1:
	ID = Intrinsic::riscv_vmsgtu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u8m2:
	ID = Intrinsic::riscv_vmsgtu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u8m4:
	ID = Intrinsic::riscv_vmsgtu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u8m8:
	ID = Intrinsic::riscv_vmsgtu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u16m1:
	ID = Intrinsic::riscv_vmsgtu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u16m2:
	ID = Intrinsic::riscv_vmsgtu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u16m4:
	ID = Intrinsic::riscv_vmsgtu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u16m8:
	ID = Intrinsic::riscv_vmsgtu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u32m1:
	ID = Intrinsic::riscv_vmsgtu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u32m2:
	ID = Intrinsic::riscv_vmsgtu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u32m4:
	ID = Intrinsic::riscv_vmsgtu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u32m8:
	ID = Intrinsic::riscv_vmsgtu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u8m1:
	ID = Intrinsic::riscv_vmsgtu_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u8m2:
	ID = Intrinsic::riscv_vmsgtu_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u8m4:
	ID = Intrinsic::riscv_vmsgtu_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u8m8:
	ID = Intrinsic::riscv_vmsgtu_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u16m1:
	ID = Intrinsic::riscv_vmsgtu_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u16m2:
	ID = Intrinsic::riscv_vmsgtu_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u16m4:
	ID = Intrinsic::riscv_vmsgtu_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u16m8:
	ID = Intrinsic::riscv_vmsgtu_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u32m1:
	ID = Intrinsic::riscv_vmsgtu_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u32m2:
	ID = Intrinsic::riscv_vmsgtu_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u32m4:
	ID = Intrinsic::riscv_vmsgtu_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u32m8:
	ID = Intrinsic::riscv_vmsgtu_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i8m1:
	ID = Intrinsic::riscv_vmsgt_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i8m2:
	ID = Intrinsic::riscv_vmsgt_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i8m4:
	ID = Intrinsic::riscv_vmsgt_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i8m8:
	ID = Intrinsic::riscv_vmsgt_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i16m1:
	ID = Intrinsic::riscv_vmsgt_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i16m2:
	ID = Intrinsic::riscv_vmsgt_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i16m4:
	ID = Intrinsic::riscv_vmsgt_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i16m8:
	ID = Intrinsic::riscv_vmsgt_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i32m1:
	ID = Intrinsic::riscv_vmsgt_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i32m2:
	ID = Intrinsic::riscv_vmsgt_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i32m4:
	ID = Intrinsic::riscv_vmsgt_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i32m8:
	ID = Intrinsic::riscv_vmsgt_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i8m1:
	ID = Intrinsic::riscv_vmsgt_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i8m2:
	ID = Intrinsic::riscv_vmsgt_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i8m4:
	ID = Intrinsic::riscv_vmsgt_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i8m8:
	ID = Intrinsic::riscv_vmsgt_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i16m1:
	ID = Intrinsic::riscv_vmsgt_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i16m2:
	ID = Intrinsic::riscv_vmsgt_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i16m4:
	ID = Intrinsic::riscv_vmsgt_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i16m8:
	ID = Intrinsic::riscv_vmsgt_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i32m1:
	ID = Intrinsic::riscv_vmsgt_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i32m2:
	ID = Intrinsic::riscv_vmsgt_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i32m4:
	ID = Intrinsic::riscv_vmsgt_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i32m8:
	ID = Intrinsic::riscv_vmsgt_vi_32m8;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vmseq_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u8m1_m:
	ID = Intrinsic::riscv_vmseq_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u8m2_m:
	ID = Intrinsic::riscv_vmseq_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u8m4_m:
	ID = Intrinsic::riscv_vmseq_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u8m8_m:
	ID = Intrinsic::riscv_vmseq_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u16m1_m:
	ID = Intrinsic::riscv_vmseq_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u16m2_m:
	ID = Intrinsic::riscv_vmseq_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u16m4_m:
	ID = Intrinsic::riscv_vmseq_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u16m8_m:
	ID = Intrinsic::riscv_vmseq_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u32m1_m:
	ID = Intrinsic::riscv_vmseq_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u32m2_m:
	ID = Intrinsic::riscv_vmseq_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u32m4_m:
	ID = Intrinsic::riscv_vmseq_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vmseq_vv_u32m8_m:
	ID = Intrinsic::riscv_vmseq_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u8m1_m:
	ID = Intrinsic::riscv_vmseq_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u8m2_m:
	ID = Intrinsic::riscv_vmseq_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u8m4_m:
	ID = Intrinsic::riscv_vmseq_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u8m8_m:
	ID = Intrinsic::riscv_vmseq_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u16m1_m:
	ID = Intrinsic::riscv_vmseq_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u16m2_m:
	ID = Intrinsic::riscv_vmseq_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u16m4_m:
	ID = Intrinsic::riscv_vmseq_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u16m8_m:
	ID = Intrinsic::riscv_vmseq_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u32m1_m:
	ID = Intrinsic::riscv_vmseq_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u32m2_m:
	ID = Intrinsic::riscv_vmseq_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u32m4_m:
	ID = Intrinsic::riscv_vmseq_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vmseq_vx_u32m8_m:
	ID = Intrinsic::riscv_vmseq_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u8m1_m:
	ID = Intrinsic::riscv_vmseq_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u8m2_m:
	ID = Intrinsic::riscv_vmseq_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u8m4_m:
	ID = Intrinsic::riscv_vmseq_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u8m8_m:
	ID = Intrinsic::riscv_vmseq_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u16m1_m:
	ID = Intrinsic::riscv_vmseq_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u16m2_m:
	ID = Intrinsic::riscv_vmseq_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u16m4_m:
	ID = Intrinsic::riscv_vmseq_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u16m8_m:
	ID = Intrinsic::riscv_vmseq_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u32m1_m:
	ID = Intrinsic::riscv_vmseq_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u32m2_m:
	ID = Intrinsic::riscv_vmseq_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u32m4_m:
	ID = Intrinsic::riscv_vmseq_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmseq_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vmseq_vi_u32m8_m:
	ID = Intrinsic::riscv_vmseq_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u8m1_m:
	ID = Intrinsic::riscv_vmsne_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u8m2_m:
	ID = Intrinsic::riscv_vmsne_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u8m4_m:
	ID = Intrinsic::riscv_vmsne_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u8m8_m:
	ID = Intrinsic::riscv_vmsne_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u16m1_m:
	ID = Intrinsic::riscv_vmsne_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u16m2_m:
	ID = Intrinsic::riscv_vmsne_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u16m4_m:
	ID = Intrinsic::riscv_vmsne_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u16m8_m:
	ID = Intrinsic::riscv_vmsne_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u32m1_m:
	ID = Intrinsic::riscv_vmsne_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u32m2_m:
	ID = Intrinsic::riscv_vmsne_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u32m4_m:
	ID = Intrinsic::riscv_vmsne_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vmsne_vv_u32m8_m:
	ID = Intrinsic::riscv_vmsne_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u8m1_m:
	ID = Intrinsic::riscv_vmsne_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u8m2_m:
	ID = Intrinsic::riscv_vmsne_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u8m4_m:
	ID = Intrinsic::riscv_vmsne_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u8m8_m:
	ID = Intrinsic::riscv_vmsne_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u16m1_m:
	ID = Intrinsic::riscv_vmsne_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u16m2_m:
	ID = Intrinsic::riscv_vmsne_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u16m4_m:
	ID = Intrinsic::riscv_vmsne_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u16m8_m:
	ID = Intrinsic::riscv_vmsne_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u32m1_m:
	ID = Intrinsic::riscv_vmsne_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u32m2_m:
	ID = Intrinsic::riscv_vmsne_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u32m4_m:
	ID = Intrinsic::riscv_vmsne_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vmsne_vx_u32m8_m:
	ID = Intrinsic::riscv_vmsne_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u8m1_m:
	ID = Intrinsic::riscv_vmsne_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u8m2_m:
	ID = Intrinsic::riscv_vmsne_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u8m4_m:
	ID = Intrinsic::riscv_vmsne_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u8m8_m:
	ID = Intrinsic::riscv_vmsne_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u16m1_m:
	ID = Intrinsic::riscv_vmsne_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u16m2_m:
	ID = Intrinsic::riscv_vmsne_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u16m4_m:
	ID = Intrinsic::riscv_vmsne_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u16m8_m:
	ID = Intrinsic::riscv_vmsne_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u32m1_m:
	ID = Intrinsic::riscv_vmsne_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u32m2_m:
	ID = Intrinsic::riscv_vmsne_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u32m4_m:
	ID = Intrinsic::riscv_vmsne_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsne_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vmsne_vi_u32m8_m:
	ID = Intrinsic::riscv_vmsne_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u8m1_m:
	ID = Intrinsic::riscv_vmsltu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u8m2_m:
	ID = Intrinsic::riscv_vmsltu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u8m4_m:
	ID = Intrinsic::riscv_vmsltu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u8m8_m:
	ID = Intrinsic::riscv_vmsltu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u16m1_m:
	ID = Intrinsic::riscv_vmsltu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u16m2_m:
	ID = Intrinsic::riscv_vmsltu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u16m4_m:
	ID = Intrinsic::riscv_vmsltu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u16m8_m:
	ID = Intrinsic::riscv_vmsltu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u32m1_m:
	ID = Intrinsic::riscv_vmsltu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u32m2_m:
	ID = Intrinsic::riscv_vmsltu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u32m4_m:
	ID = Intrinsic::riscv_vmsltu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vv_u32m8_m:
	ID = Intrinsic::riscv_vmsltu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u8m1_m:
	ID = Intrinsic::riscv_vmsltu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u8m2_m:
	ID = Intrinsic::riscv_vmsltu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u8m4_m:
	ID = Intrinsic::riscv_vmsltu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u8m8_m:
	ID = Intrinsic::riscv_vmsltu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u16m1_m:
	ID = Intrinsic::riscv_vmsltu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u16m2_m:
	ID = Intrinsic::riscv_vmsltu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u16m4_m:
	ID = Intrinsic::riscv_vmsltu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u16m8_m:
	ID = Intrinsic::riscv_vmsltu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u32m1_m:
	ID = Intrinsic::riscv_vmsltu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u32m2_m:
	ID = Intrinsic::riscv_vmsltu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u32m4_m:
	ID = Intrinsic::riscv_vmsltu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsltu_vx_u32m8_m:
	ID = Intrinsic::riscv_vmsltu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i8m1_m:
	ID = Intrinsic::riscv_vmslt_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i8m2_m:
	ID = Intrinsic::riscv_vmslt_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i8m4_m:
	ID = Intrinsic::riscv_vmslt_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i8m8_m:
	ID = Intrinsic::riscv_vmslt_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i16m1_m:
	ID = Intrinsic::riscv_vmslt_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i16m2_m:
	ID = Intrinsic::riscv_vmslt_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i16m4_m:
	ID = Intrinsic::riscv_vmslt_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i16m8_m:
	ID = Intrinsic::riscv_vmslt_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i32m1_m:
	ID = Intrinsic::riscv_vmslt_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i32m2_m:
	ID = Intrinsic::riscv_vmslt_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i32m4_m:
	ID = Intrinsic::riscv_vmslt_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vv_i32m8_m:
	ID = Intrinsic::riscv_vmslt_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i8m1_m:
	ID = Intrinsic::riscv_vmslt_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i8m2_m:
	ID = Intrinsic::riscv_vmslt_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i8m4_m:
	ID = Intrinsic::riscv_vmslt_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i8m8_m:
	ID = Intrinsic::riscv_vmslt_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i16m1_m:
	ID = Intrinsic::riscv_vmslt_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i16m2_m:
	ID = Intrinsic::riscv_vmslt_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i16m4_m:
	ID = Intrinsic::riscv_vmslt_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i16m8_m:
	ID = Intrinsic::riscv_vmslt_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i32m1_m:
	ID = Intrinsic::riscv_vmslt_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i32m2_m:
	ID = Intrinsic::riscv_vmslt_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i32m4_m:
	ID = Intrinsic::riscv_vmslt_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmslt_vx_i32m8_m:
	ID = Intrinsic::riscv_vmslt_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u8m1_m:
	ID = Intrinsic::riscv_vmsleu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u8m2_m:
	ID = Intrinsic::riscv_vmsleu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u8m4_m:
	ID = Intrinsic::riscv_vmsleu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u8m8_m:
	ID = Intrinsic::riscv_vmsleu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u16m1_m:
	ID = Intrinsic::riscv_vmsleu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u16m2_m:
	ID = Intrinsic::riscv_vmsleu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u16m4_m:
	ID = Intrinsic::riscv_vmsleu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u16m8_m:
	ID = Intrinsic::riscv_vmsleu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u32m1_m:
	ID = Intrinsic::riscv_vmsleu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u32m2_m:
	ID = Intrinsic::riscv_vmsleu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u32m4_m:
	ID = Intrinsic::riscv_vmsleu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vv_u32m8_m:
	ID = Intrinsic::riscv_vmsleu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u8m1_m:
	ID = Intrinsic::riscv_vmsleu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u8m2_m:
	ID = Intrinsic::riscv_vmsleu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u8m4_m:
	ID = Intrinsic::riscv_vmsleu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u8m8_m:
	ID = Intrinsic::riscv_vmsleu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u16m1_m:
	ID = Intrinsic::riscv_vmsleu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u16m2_m:
	ID = Intrinsic::riscv_vmsleu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u16m4_m:
	ID = Intrinsic::riscv_vmsleu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u16m8_m:
	ID = Intrinsic::riscv_vmsleu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u32m1_m:
	ID = Intrinsic::riscv_vmsleu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u32m2_m:
	ID = Intrinsic::riscv_vmsleu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u32m4_m:
	ID = Intrinsic::riscv_vmsleu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vx_u32m8_m:
	ID = Intrinsic::riscv_vmsleu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u8m1_m:
	ID = Intrinsic::riscv_vmsleu_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u8m2_m:
	ID = Intrinsic::riscv_vmsleu_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u8m4_m:
	ID = Intrinsic::riscv_vmsleu_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u8m8_m:
	ID = Intrinsic::riscv_vmsleu_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u16m1_m:
	ID = Intrinsic::riscv_vmsleu_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u16m2_m:
	ID = Intrinsic::riscv_vmsleu_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u16m4_m:
	ID = Intrinsic::riscv_vmsleu_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u16m8_m:
	ID = Intrinsic::riscv_vmsleu_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u32m1_m:
	ID = Intrinsic::riscv_vmsleu_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u32m2_m:
	ID = Intrinsic::riscv_vmsleu_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u32m4_m:
	ID = Intrinsic::riscv_vmsleu_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsleu_vi_u32m8_m:
	ID = Intrinsic::riscv_vmsleu_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i8m1_m:
	ID = Intrinsic::riscv_vmsle_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i8m2_m:
	ID = Intrinsic::riscv_vmsle_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i8m4_m:
	ID = Intrinsic::riscv_vmsle_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i8m8_m:
	ID = Intrinsic::riscv_vmsle_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i16m1_m:
	ID = Intrinsic::riscv_vmsle_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i16m2_m:
	ID = Intrinsic::riscv_vmsle_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i16m4_m:
	ID = Intrinsic::riscv_vmsle_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i16m8_m:
	ID = Intrinsic::riscv_vmsle_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i32m1_m:
	ID = Intrinsic::riscv_vmsle_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i32m2_m:
	ID = Intrinsic::riscv_vmsle_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i32m4_m:
	ID = Intrinsic::riscv_vmsle_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vv_i32m8_m:
	ID = Intrinsic::riscv_vmsle_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i8m1_m:
	ID = Intrinsic::riscv_vmsle_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i8m2_m:
	ID = Intrinsic::riscv_vmsle_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i8m4_m:
	ID = Intrinsic::riscv_vmsle_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i8m8_m:
	ID = Intrinsic::riscv_vmsle_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i16m1_m:
	ID = Intrinsic::riscv_vmsle_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i16m2_m:
	ID = Intrinsic::riscv_vmsle_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i16m4_m:
	ID = Intrinsic::riscv_vmsle_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i16m8_m:
	ID = Intrinsic::riscv_vmsle_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i32m1_m:
	ID = Intrinsic::riscv_vmsle_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i32m2_m:
	ID = Intrinsic::riscv_vmsle_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i32m4_m:
	ID = Intrinsic::riscv_vmsle_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vx_i32m8_m:
	ID = Intrinsic::riscv_vmsle_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i8m1_m:
	ID = Intrinsic::riscv_vmsle_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i8m2_m:
	ID = Intrinsic::riscv_vmsle_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i8m4_m:
	ID = Intrinsic::riscv_vmsle_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i8m8_m:
	ID = Intrinsic::riscv_vmsle_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i16m1_m:
	ID = Intrinsic::riscv_vmsle_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i16m2_m:
	ID = Intrinsic::riscv_vmsle_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i16m4_m:
	ID = Intrinsic::riscv_vmsle_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i16m8_m:
	ID = Intrinsic::riscv_vmsle_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i32m1_m:
	ID = Intrinsic::riscv_vmsle_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i32m2_m:
	ID = Intrinsic::riscv_vmsle_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i32m4_m:
	ID = Intrinsic::riscv_vmsle_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsle_vi_i32m8_m:
	ID = Intrinsic::riscv_vmsle_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u8m1_m:
	ID = Intrinsic::riscv_vmsgtu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u8m2_m:
	ID = Intrinsic::riscv_vmsgtu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u8m4_m:
	ID = Intrinsic::riscv_vmsgtu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u8m8_m:
	ID = Intrinsic::riscv_vmsgtu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u16m1_m:
	ID = Intrinsic::riscv_vmsgtu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u16m2_m:
	ID = Intrinsic::riscv_vmsgtu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u16m4_m:
	ID = Intrinsic::riscv_vmsgtu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u16m8_m:
	ID = Intrinsic::riscv_vmsgtu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u32m1_m:
	ID = Intrinsic::riscv_vmsgtu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u32m2_m:
	ID = Intrinsic::riscv_vmsgtu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u32m4_m:
	ID = Intrinsic::riscv_vmsgtu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vx_u32m8_m:
	ID = Intrinsic::riscv_vmsgtu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u8m1_m:
	ID = Intrinsic::riscv_vmsgtu_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u8m2_m:
	ID = Intrinsic::riscv_vmsgtu_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u8m4_m:
	ID = Intrinsic::riscv_vmsgtu_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u8m8_m:
	ID = Intrinsic::riscv_vmsgtu_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u16m1_m:
	ID = Intrinsic::riscv_vmsgtu_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u16m2_m:
	ID = Intrinsic::riscv_vmsgtu_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u16m4_m:
	ID = Intrinsic::riscv_vmsgtu_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u16m8_m:
	ID = Intrinsic::riscv_vmsgtu_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u32m1_m:
	ID = Intrinsic::riscv_vmsgtu_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u32m2_m:
	ID = Intrinsic::riscv_vmsgtu_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u32m4_m:
	ID = Intrinsic::riscv_vmsgtu_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgtu_vi_u32m8_m:
	ID = Intrinsic::riscv_vmsgtu_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i8m1_m:
	ID = Intrinsic::riscv_vmsgt_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i8m2_m:
	ID = Intrinsic::riscv_vmsgt_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i8m4_m:
	ID = Intrinsic::riscv_vmsgt_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i8m8_m:
	ID = Intrinsic::riscv_vmsgt_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i16m1_m:
	ID = Intrinsic::riscv_vmsgt_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i16m2_m:
	ID = Intrinsic::riscv_vmsgt_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i16m4_m:
	ID = Intrinsic::riscv_vmsgt_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i16m8_m:
	ID = Intrinsic::riscv_vmsgt_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i32m1_m:
	ID = Intrinsic::riscv_vmsgt_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i32m2_m:
	ID = Intrinsic::riscv_vmsgt_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i32m4_m:
	ID = Intrinsic::riscv_vmsgt_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vx_i32m8_m:
	ID = Intrinsic::riscv_vmsgt_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i8m1_m:
	ID = Intrinsic::riscv_vmsgt_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i8m2_m:
	ID = Intrinsic::riscv_vmsgt_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i8m4_m:
	ID = Intrinsic::riscv_vmsgt_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i8m8_m:
	ID = Intrinsic::riscv_vmsgt_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i16m1_m:
	ID = Intrinsic::riscv_vmsgt_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i16m2_m:
	ID = Intrinsic::riscv_vmsgt_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i16m4_m:
	ID = Intrinsic::riscv_vmsgt_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i16m8_m:
	ID = Intrinsic::riscv_vmsgt_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i32m1_m:
	ID = Intrinsic::riscv_vmsgt_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i32m2_m:
	ID = Intrinsic::riscv_vmsgt_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i32m4_m:
	ID = Intrinsic::riscv_vmsgt_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmsgt_vi_i32m8_m:
	ID = Intrinsic::riscv_vmsgt_vi_32m8_m;
	break;

	//Vector Integer Min/Max Functions
    case RISCV::BI__builtin_riscv_vminu_vv_u8m1:
	ID = Intrinsic::riscv_vminu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u8m2:
	ID = Intrinsic::riscv_vminu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u8m4:
	ID = Intrinsic::riscv_vminu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u8m8:
	ID = Intrinsic::riscv_vminu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u16m1:
	ID = Intrinsic::riscv_vminu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u16m2:
	ID = Intrinsic::riscv_vminu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u16m4:
	ID = Intrinsic::riscv_vminu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u16m8:
	ID = Intrinsic::riscv_vminu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u32m1:
	ID = Intrinsic::riscv_vminu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u32m2:
	ID = Intrinsic::riscv_vminu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u32m4:
	ID = Intrinsic::riscv_vminu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u32m8:
	ID = Intrinsic::riscv_vminu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u8m1:
	ID = Intrinsic::riscv_vminu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u8m2:
	ID = Intrinsic::riscv_vminu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u8m4:
	ID = Intrinsic::riscv_vminu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u8m8:
	ID = Intrinsic::riscv_vminu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u16m1:
	ID = Intrinsic::riscv_vminu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u16m2:
	ID = Intrinsic::riscv_vminu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u16m4:
	ID = Intrinsic::riscv_vminu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u16m8:
	ID = Intrinsic::riscv_vminu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u32m1:
	ID = Intrinsic::riscv_vminu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u32m2:
	ID = Intrinsic::riscv_vminu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u32m4:
	ID = Intrinsic::riscv_vminu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u32m8:
	ID = Intrinsic::riscv_vminu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i8m1:
	ID = Intrinsic::riscv_vmin_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i8m2:
	ID = Intrinsic::riscv_vmin_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i8m4:
	ID = Intrinsic::riscv_vmin_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i8m8:
	ID = Intrinsic::riscv_vmin_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i16m1:
	ID = Intrinsic::riscv_vmin_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i16m2:
	ID = Intrinsic::riscv_vmin_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i16m4:
	ID = Intrinsic::riscv_vmin_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i16m8:
	ID = Intrinsic::riscv_vmin_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i32m1:
	ID = Intrinsic::riscv_vmin_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i32m2:
	ID = Intrinsic::riscv_vmin_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i32m4:
	ID = Intrinsic::riscv_vmin_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i32m8:
	ID = Intrinsic::riscv_vmin_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i8m1:
	ID = Intrinsic::riscv_vmin_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i8m2:
	ID = Intrinsic::riscv_vmin_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i8m4:
	ID = Intrinsic::riscv_vmin_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i8m8:
	ID = Intrinsic::riscv_vmin_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i16m1:
	ID = Intrinsic::riscv_vmin_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i16m2:
	ID = Intrinsic::riscv_vmin_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i16m4:
	ID = Intrinsic::riscv_vmin_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i16m8:
	ID = Intrinsic::riscv_vmin_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i32m1:
	ID = Intrinsic::riscv_vmin_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i32m2:
	ID = Intrinsic::riscv_vmin_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i32m4:
	ID = Intrinsic::riscv_vmin_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i32m8:
	ID = Intrinsic::riscv_vmin_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u8m1:
	ID = Intrinsic::riscv_vmaxu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u8m2:
	ID = Intrinsic::riscv_vmaxu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u8m4:
	ID = Intrinsic::riscv_vmaxu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u8m8:
	ID = Intrinsic::riscv_vmaxu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u16m1:
	ID = Intrinsic::riscv_vmaxu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u16m2:
	ID = Intrinsic::riscv_vmaxu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u16m4:
	ID = Intrinsic::riscv_vmaxu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u16m8:
	ID = Intrinsic::riscv_vmaxu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u32m1:
	ID = Intrinsic::riscv_vmaxu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u32m2:
	ID = Intrinsic::riscv_vmaxu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u32m4:
	ID = Intrinsic::riscv_vmaxu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u32m8:
	ID = Intrinsic::riscv_vmaxu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u8m1:
	ID = Intrinsic::riscv_vmaxu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u8m2:
	ID = Intrinsic::riscv_vmaxu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u8m4:
	ID = Intrinsic::riscv_vmaxu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u8m8:
	ID = Intrinsic::riscv_vmaxu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u16m1:
	ID = Intrinsic::riscv_vmaxu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u16m2:
	ID = Intrinsic::riscv_vmaxu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u16m4:
	ID = Intrinsic::riscv_vmaxu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u16m8:
	ID = Intrinsic::riscv_vmaxu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u32m1:
	ID = Intrinsic::riscv_vmaxu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u32m2:
	ID = Intrinsic::riscv_vmaxu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u32m4:
	ID = Intrinsic::riscv_vmaxu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u32m8:
	ID = Intrinsic::riscv_vmaxu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i8m1:
	ID = Intrinsic::riscv_vmax_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i8m2:
	ID = Intrinsic::riscv_vmax_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i8m4:
	ID = Intrinsic::riscv_vmax_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i8m8:
	ID = Intrinsic::riscv_vmax_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i16m1:
	ID = Intrinsic::riscv_vmax_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i16m2:
	ID = Intrinsic::riscv_vmax_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i16m4:
	ID = Intrinsic::riscv_vmax_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i16m8:
	ID = Intrinsic::riscv_vmax_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i32m1:
	ID = Intrinsic::riscv_vmax_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i32m2:
	ID = Intrinsic::riscv_vmax_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i32m4:
	ID = Intrinsic::riscv_vmax_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i32m8:
	ID = Intrinsic::riscv_vmax_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i8m1:
	ID = Intrinsic::riscv_vmax_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i8m2:
	ID = Intrinsic::riscv_vmax_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i8m4:
	ID = Intrinsic::riscv_vmax_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i8m8:
	ID = Intrinsic::riscv_vmax_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i16m1:
	ID = Intrinsic::riscv_vmax_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i16m2:
	ID = Intrinsic::riscv_vmax_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i16m4:
	ID = Intrinsic::riscv_vmax_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i16m8:
	ID = Intrinsic::riscv_vmax_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i32m1:
	ID = Intrinsic::riscv_vmax_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i32m2:
	ID = Intrinsic::riscv_vmax_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i32m4:
	ID = Intrinsic::riscv_vmax_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i32m8:
	ID = Intrinsic::riscv_vmax_vx_32m8;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vminu_vv_u8m1_m:
	ID = Intrinsic::riscv_vminu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u8m2_m:
	ID = Intrinsic::riscv_vminu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u8m4_m:
	ID = Intrinsic::riscv_vminu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u8m8_m:
	ID = Intrinsic::riscv_vminu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u16m1_m:
	ID = Intrinsic::riscv_vminu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u16m2_m:
	ID = Intrinsic::riscv_vminu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u16m4_m:
	ID = Intrinsic::riscv_vminu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u16m8_m:
	ID = Intrinsic::riscv_vminu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u32m1_m:
	ID = Intrinsic::riscv_vminu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u32m2_m:
	ID = Intrinsic::riscv_vminu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u32m4_m:
	ID = Intrinsic::riscv_vminu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vv_u32m8_m:
	ID = Intrinsic::riscv_vminu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u8m1_m:
	ID = Intrinsic::riscv_vminu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u8m2_m:
	ID = Intrinsic::riscv_vminu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u8m4_m:
	ID = Intrinsic::riscv_vminu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u8m8_m:
	ID = Intrinsic::riscv_vminu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u16m1_m:
	ID = Intrinsic::riscv_vminu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u16m2_m:
	ID = Intrinsic::riscv_vminu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u16m4_m:
	ID = Intrinsic::riscv_vminu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u16m8_m:
	ID = Intrinsic::riscv_vminu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u32m1_m:
	ID = Intrinsic::riscv_vminu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u32m2_m:
	ID = Intrinsic::riscv_vminu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u32m4_m:
	ID = Intrinsic::riscv_vminu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vminu_vx_u32m8_m:
	ID = Intrinsic::riscv_vminu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i8m1_m:
	ID = Intrinsic::riscv_vmin_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i8m2_m:
	ID = Intrinsic::riscv_vmin_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i8m4_m:
	ID = Intrinsic::riscv_vmin_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i8m8_m:
	ID = Intrinsic::riscv_vmin_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i16m1_m:
	ID = Intrinsic::riscv_vmin_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i16m2_m:
	ID = Intrinsic::riscv_vmin_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i16m4_m:
	ID = Intrinsic::riscv_vmin_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i16m8_m:
	ID = Intrinsic::riscv_vmin_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i32m1_m:
	ID = Intrinsic::riscv_vmin_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i32m2_m:
	ID = Intrinsic::riscv_vmin_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i32m4_m:
	ID = Intrinsic::riscv_vmin_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vv_i32m8_m:
	ID = Intrinsic::riscv_vmin_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i8m1_m:
	ID = Intrinsic::riscv_vmin_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i8m2_m:
	ID = Intrinsic::riscv_vmin_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i8m4_m:
	ID = Intrinsic::riscv_vmin_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i8m8_m:
	ID = Intrinsic::riscv_vmin_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i16m1_m:
	ID = Intrinsic::riscv_vmin_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i16m2_m:
	ID = Intrinsic::riscv_vmin_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i16m4_m:
	ID = Intrinsic::riscv_vmin_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i16m8_m:
	ID = Intrinsic::riscv_vmin_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i32m1_m:
	ID = Intrinsic::riscv_vmin_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i32m2_m:
	ID = Intrinsic::riscv_vmin_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i32m4_m:
	ID = Intrinsic::riscv_vmin_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmin_vx_i32m8_m:
	ID = Intrinsic::riscv_vmin_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u8m1_m:
	ID = Intrinsic::riscv_vmaxu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u8m2_m:
	ID = Intrinsic::riscv_vmaxu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u8m4_m:
	ID = Intrinsic::riscv_vmaxu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u8m8_m:
	ID = Intrinsic::riscv_vmaxu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u16m1_m:
	ID = Intrinsic::riscv_vmaxu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u16m2_m:
	ID = Intrinsic::riscv_vmaxu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u16m4_m:
	ID = Intrinsic::riscv_vmaxu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u16m8_m:
	ID = Intrinsic::riscv_vmaxu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u32m1_m:
	ID = Intrinsic::riscv_vmaxu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u32m2_m:
	ID = Intrinsic::riscv_vmaxu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u32m4_m:
	ID = Intrinsic::riscv_vmaxu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vv_u32m8_m:
	ID = Intrinsic::riscv_vmaxu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u8m1_m:
	ID = Intrinsic::riscv_vmaxu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u8m2_m:
	ID = Intrinsic::riscv_vmaxu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u8m4_m:
	ID = Intrinsic::riscv_vmaxu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u8m8_m:
	ID = Intrinsic::riscv_vmaxu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u16m1_m:
	ID = Intrinsic::riscv_vmaxu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u16m2_m:
	ID = Intrinsic::riscv_vmaxu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u16m4_m:
	ID = Intrinsic::riscv_vmaxu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u16m8_m:
	ID = Intrinsic::riscv_vmaxu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u32m1_m:
	ID = Intrinsic::riscv_vmaxu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u32m2_m:
	ID = Intrinsic::riscv_vmaxu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u32m4_m:
	ID = Intrinsic::riscv_vmaxu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmaxu_vx_u32m8_m:
	ID = Intrinsic::riscv_vmaxu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i8m1_m:
	ID = Intrinsic::riscv_vmax_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i8m2_m:
	ID = Intrinsic::riscv_vmax_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i8m4_m:
	ID = Intrinsic::riscv_vmax_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i8m8_m:
	ID = Intrinsic::riscv_vmax_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i16m1_m:
	ID = Intrinsic::riscv_vmax_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i16m2_m:
	ID = Intrinsic::riscv_vmax_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i16m4_m:
	ID = Intrinsic::riscv_vmax_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i16m8_m:
	ID = Intrinsic::riscv_vmax_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i32m1_m:
	ID = Intrinsic::riscv_vmax_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i32m2_m:
	ID = Intrinsic::riscv_vmax_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i32m4_m:
	ID = Intrinsic::riscv_vmax_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vv_i32m8_m:
	ID = Intrinsic::riscv_vmax_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i8m1_m:
	ID = Intrinsic::riscv_vmax_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i8m2_m:
	ID = Intrinsic::riscv_vmax_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i8m4_m:
	ID = Intrinsic::riscv_vmax_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i8m8_m:
	ID = Intrinsic::riscv_vmax_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i16m1_m:
	ID = Intrinsic::riscv_vmax_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i16m2_m:
	ID = Intrinsic::riscv_vmax_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i16m4_m:
	ID = Intrinsic::riscv_vmax_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i16m8_m:
	ID = Intrinsic::riscv_vmax_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i32m1_m:
	ID = Intrinsic::riscv_vmax_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i32m2_m:
	ID = Intrinsic::riscv_vmax_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i32m4_m:
	ID = Intrinsic::riscv_vmax_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmax_vx_i32m8_m:
	ID = Intrinsic::riscv_vmax_vx_32m8_m;
	break;

	//Vector Single-Width Integer Multiply Functions
    case RISCV::BI__builtin_riscv_vmul_vv_i8m1:
    case RISCV::BI__builtin_riscv_vmul_vv_u8m1:
	ID = Intrinsic::riscv_vmul_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i8m2:
    case RISCV::BI__builtin_riscv_vmul_vv_u8m2:
	ID = Intrinsic::riscv_vmul_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i8m4:
    case RISCV::BI__builtin_riscv_vmul_vv_u8m4:
	ID = Intrinsic::riscv_vmul_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i8m8:
    case RISCV::BI__builtin_riscv_vmul_vv_u8m8:
	ID = Intrinsic::riscv_vmul_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i16m1:
    case RISCV::BI__builtin_riscv_vmul_vv_u16m1:
	ID = Intrinsic::riscv_vmul_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i16m2:
    case RISCV::BI__builtin_riscv_vmul_vv_u16m2:
	ID = Intrinsic::riscv_vmul_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i16m4:
    case RISCV::BI__builtin_riscv_vmul_vv_u16m4:
	ID = Intrinsic::riscv_vmul_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i16m8:
    case RISCV::BI__builtin_riscv_vmul_vv_u16m8:
	ID = Intrinsic::riscv_vmul_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i32m1:
    case RISCV::BI__builtin_riscv_vmul_vv_u32m1:
	ID = Intrinsic::riscv_vmul_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i32m2:
    case RISCV::BI__builtin_riscv_vmul_vv_u32m2:
	ID = Intrinsic::riscv_vmul_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i32m4:
    case RISCV::BI__builtin_riscv_vmul_vv_u32m4:
	ID = Intrinsic::riscv_vmul_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i32m8:
    case RISCV::BI__builtin_riscv_vmul_vv_u32m8:
	ID = Intrinsic::riscv_vmul_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i8m1:
    case RISCV::BI__builtin_riscv_vmul_vx_u8m1:
	ID = Intrinsic::riscv_vmul_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i8m2:
    case RISCV::BI__builtin_riscv_vmul_vx_u8m2:
	ID = Intrinsic::riscv_vmul_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i8m4:
    case RISCV::BI__builtin_riscv_vmul_vx_u8m4:
	ID = Intrinsic::riscv_vmul_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i8m8:
    case RISCV::BI__builtin_riscv_vmul_vx_u8m8:
	ID = Intrinsic::riscv_vmul_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i16m1:
    case RISCV::BI__builtin_riscv_vmul_vx_u16m1:
	ID = Intrinsic::riscv_vmul_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i16m2:
    case RISCV::BI__builtin_riscv_vmul_vx_u16m2:
	ID = Intrinsic::riscv_vmul_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i16m4:
    case RISCV::BI__builtin_riscv_vmul_vx_u16m4:
	ID = Intrinsic::riscv_vmul_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i16m8:
    case RISCV::BI__builtin_riscv_vmul_vx_u16m8:
	ID = Intrinsic::riscv_vmul_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i32m1:
    case RISCV::BI__builtin_riscv_vmul_vx_u32m1:
	ID = Intrinsic::riscv_vmul_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i32m2:
    case RISCV::BI__builtin_riscv_vmul_vx_u32m2:
	ID = Intrinsic::riscv_vmul_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i32m4:
    case RISCV::BI__builtin_riscv_vmul_vx_u32m4:
	ID = Intrinsic::riscv_vmul_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i32m8:
    case RISCV::BI__builtin_riscv_vmul_vx_u32m8:
	ID = Intrinsic::riscv_vmul_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i8m1:
	ID = Intrinsic::riscv_vmulh_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i8m2:
	ID = Intrinsic::riscv_vmulh_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i8m4:
	ID = Intrinsic::riscv_vmulh_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i8m8:
	ID = Intrinsic::riscv_vmulh_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i16m1:
	ID = Intrinsic::riscv_vmulh_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i16m2:
	ID = Intrinsic::riscv_vmulh_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i16m4:
	ID = Intrinsic::riscv_vmulh_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i16m8:
	ID = Intrinsic::riscv_vmulh_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i32m1:
	ID = Intrinsic::riscv_vmulh_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i32m2:
	ID = Intrinsic::riscv_vmulh_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i32m4:
	ID = Intrinsic::riscv_vmulh_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i32m8:
	ID = Intrinsic::riscv_vmulh_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i8m1:
	ID = Intrinsic::riscv_vmulh_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i8m2:
	ID = Intrinsic::riscv_vmulh_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i8m4:
	ID = Intrinsic::riscv_vmulh_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i8m8:
	ID = Intrinsic::riscv_vmulh_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i16m1:
	ID = Intrinsic::riscv_vmulh_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i16m2:
	ID = Intrinsic::riscv_vmulh_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i16m4:
	ID = Intrinsic::riscv_vmulh_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i16m8:
	ID = Intrinsic::riscv_vmulh_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i32m1:
	ID = Intrinsic::riscv_vmulh_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i32m2:
	ID = Intrinsic::riscv_vmulh_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i32m4:
	ID = Intrinsic::riscv_vmulh_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i32m8:
	ID = Intrinsic::riscv_vmulh_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u8m1:
	ID = Intrinsic::riscv_vmulhu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u8m2:
	ID = Intrinsic::riscv_vmulhu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u8m4:
	ID = Intrinsic::riscv_vmulhu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u8m8:
	ID = Intrinsic::riscv_vmulhu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u16m1:
	ID = Intrinsic::riscv_vmulhu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u16m2:
	ID = Intrinsic::riscv_vmulhu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u16m4:
	ID = Intrinsic::riscv_vmulhu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u16m8:
	ID = Intrinsic::riscv_vmulhu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u32m1:
	ID = Intrinsic::riscv_vmulhu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u32m2:
	ID = Intrinsic::riscv_vmulhu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u32m4:
	ID = Intrinsic::riscv_vmulhu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u32m8:
	ID = Intrinsic::riscv_vmulhu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u8m1:
	ID = Intrinsic::riscv_vmulhu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u8m2:
	ID = Intrinsic::riscv_vmulhu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u8m4:
	ID = Intrinsic::riscv_vmulhu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u8m8:
	ID = Intrinsic::riscv_vmulhu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u16m1:
	ID = Intrinsic::riscv_vmulhu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u16m2:
	ID = Intrinsic::riscv_vmulhu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u16m4:
	ID = Intrinsic::riscv_vmulhu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u16m8:
	ID = Intrinsic::riscv_vmulhu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u32m1:
	ID = Intrinsic::riscv_vmulhu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u32m2:
	ID = Intrinsic::riscv_vmulhu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u32m4:
	ID = Intrinsic::riscv_vmulhu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u32m8:
	ID = Intrinsic::riscv_vmulhu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i8m1:
	ID = Intrinsic::riscv_vmulhsu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i8m2:
	ID = Intrinsic::riscv_vmulhsu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i8m4:
	ID = Intrinsic::riscv_vmulhsu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i8m8:
	ID = Intrinsic::riscv_vmulhsu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i16m1:
	ID = Intrinsic::riscv_vmulhsu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i16m2:
	ID = Intrinsic::riscv_vmulhsu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i16m4:
	ID = Intrinsic::riscv_vmulhsu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i16m8:
	ID = Intrinsic::riscv_vmulhsu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i32m1:
	ID = Intrinsic::riscv_vmulhsu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i32m2:
	ID = Intrinsic::riscv_vmulhsu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i32m4:
	ID = Intrinsic::riscv_vmulhsu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i32m8:
	ID = Intrinsic::riscv_vmulhsu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i8m1:
	ID = Intrinsic::riscv_vmulhsu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i8m2:
	ID = Intrinsic::riscv_vmulhsu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i8m4:
	ID = Intrinsic::riscv_vmulhsu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i8m8:
	ID = Intrinsic::riscv_vmulhsu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i16m1:
	ID = Intrinsic::riscv_vmulhsu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i16m2:
	ID = Intrinsic::riscv_vmulhsu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i16m4:
	ID = Intrinsic::riscv_vmulhsu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i16m8:
	ID = Intrinsic::riscv_vmulhsu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i32m1:
	ID = Intrinsic::riscv_vmulhsu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i32m2:
	ID = Intrinsic::riscv_vmulhsu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i32m4:
	ID = Intrinsic::riscv_vmulhsu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i32m8:
	ID = Intrinsic::riscv_vmulhsu_vx_32m8;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vmul_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u8m1_m:
	ID = Intrinsic::riscv_vmul_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u8m2_m:
	ID = Intrinsic::riscv_vmul_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u8m4_m:
	ID = Intrinsic::riscv_vmul_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u8m8_m:
	ID = Intrinsic::riscv_vmul_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u16m1_m:
	ID = Intrinsic::riscv_vmul_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u16m2_m:
	ID = Intrinsic::riscv_vmul_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u16m4_m:
	ID = Intrinsic::riscv_vmul_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u16m8_m:
	ID = Intrinsic::riscv_vmul_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u32m1_m:
	ID = Intrinsic::riscv_vmul_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u32m2_m:
	ID = Intrinsic::riscv_vmul_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u32m4_m:
	ID = Intrinsic::riscv_vmul_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vmul_vv_u32m8_m:
	ID = Intrinsic::riscv_vmul_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u8m1_m:
	ID = Intrinsic::riscv_vmul_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u8m2_m:
	ID = Intrinsic::riscv_vmul_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u8m4_m:
	ID = Intrinsic::riscv_vmul_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u8m8_m:
	ID = Intrinsic::riscv_vmul_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u16m1_m:
	ID = Intrinsic::riscv_vmul_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u16m2_m:
	ID = Intrinsic::riscv_vmul_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u16m4_m:
	ID = Intrinsic::riscv_vmul_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u16m8_m:
	ID = Intrinsic::riscv_vmul_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u32m1_m:
	ID = Intrinsic::riscv_vmul_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u32m2_m:
	ID = Intrinsic::riscv_vmul_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u32m4_m:
	ID = Intrinsic::riscv_vmul_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmul_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vmul_vx_u32m8_m:
	ID = Intrinsic::riscv_vmul_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i8m1_m:
	ID = Intrinsic::riscv_vmulh_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i8m2_m:
	ID = Intrinsic::riscv_vmulh_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i8m4_m:
	ID = Intrinsic::riscv_vmulh_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i8m8_m:
	ID = Intrinsic::riscv_vmulh_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i16m1_m:
	ID = Intrinsic::riscv_vmulh_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i16m2_m:
	ID = Intrinsic::riscv_vmulh_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i16m4_m:
	ID = Intrinsic::riscv_vmulh_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i16m8_m:
	ID = Intrinsic::riscv_vmulh_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i32m1_m:
	ID = Intrinsic::riscv_vmulh_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i32m2_m:
	ID = Intrinsic::riscv_vmulh_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i32m4_m:
	ID = Intrinsic::riscv_vmulh_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vv_i32m8_m:
	ID = Intrinsic::riscv_vmulh_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i8m1_m:
	ID = Intrinsic::riscv_vmulh_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i8m2_m:
	ID = Intrinsic::riscv_vmulh_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i8m4_m:
	ID = Intrinsic::riscv_vmulh_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i8m8_m:
	ID = Intrinsic::riscv_vmulh_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i16m1_m:
	ID = Intrinsic::riscv_vmulh_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i16m2_m:
	ID = Intrinsic::riscv_vmulh_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i16m4_m:
	ID = Intrinsic::riscv_vmulh_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i16m8_m:
	ID = Intrinsic::riscv_vmulh_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i32m1_m:
	ID = Intrinsic::riscv_vmulh_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i32m2_m:
	ID = Intrinsic::riscv_vmulh_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i32m4_m:
	ID = Intrinsic::riscv_vmulh_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulh_vx_i32m8_m:
	ID = Intrinsic::riscv_vmulh_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u8m1_m:
	ID = Intrinsic::riscv_vmulhu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u8m2_m:
	ID = Intrinsic::riscv_vmulhu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u8m4_m:
	ID = Intrinsic::riscv_vmulhu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u8m8_m:
	ID = Intrinsic::riscv_vmulhu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u16m1_m:
	ID = Intrinsic::riscv_vmulhu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u16m2_m:
	ID = Intrinsic::riscv_vmulhu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u16m4_m:
	ID = Intrinsic::riscv_vmulhu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u16m8_m:
	ID = Intrinsic::riscv_vmulhu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u32m1_m:
	ID = Intrinsic::riscv_vmulhu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u32m2_m:
	ID = Intrinsic::riscv_vmulhu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u32m4_m:
	ID = Intrinsic::riscv_vmulhu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vv_u32m8_m:
	ID = Intrinsic::riscv_vmulhu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u8m1_m:
	ID = Intrinsic::riscv_vmulhu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u8m2_m:
	ID = Intrinsic::riscv_vmulhu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u8m4_m:
	ID = Intrinsic::riscv_vmulhu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u8m8_m:
	ID = Intrinsic::riscv_vmulhu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u16m1_m:
	ID = Intrinsic::riscv_vmulhu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u16m2_m:
	ID = Intrinsic::riscv_vmulhu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u16m4_m:
	ID = Intrinsic::riscv_vmulhu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u16m8_m:
	ID = Intrinsic::riscv_vmulhu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u32m1_m:
	ID = Intrinsic::riscv_vmulhu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u32m2_m:
	ID = Intrinsic::riscv_vmulhu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u32m4_m:
	ID = Intrinsic::riscv_vmulhu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhu_vx_u32m8_m:
	ID = Intrinsic::riscv_vmulhu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i8m1_m:
	ID = Intrinsic::riscv_vmulhsu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i8m2_m:
	ID = Intrinsic::riscv_vmulhsu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i8m4_m:
	ID = Intrinsic::riscv_vmulhsu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i8m8_m:
	ID = Intrinsic::riscv_vmulhsu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i16m1_m:
	ID = Intrinsic::riscv_vmulhsu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i16m2_m:
	ID = Intrinsic::riscv_vmulhsu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i16m4_m:
	ID = Intrinsic::riscv_vmulhsu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i16m8_m:
	ID = Intrinsic::riscv_vmulhsu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i32m1_m:
	ID = Intrinsic::riscv_vmulhsu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i32m2_m:
	ID = Intrinsic::riscv_vmulhsu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i32m4_m:
	ID = Intrinsic::riscv_vmulhsu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vv_i32m8_m:
	ID = Intrinsic::riscv_vmulhsu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i8m1_m:
	ID = Intrinsic::riscv_vmulhsu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i8m2_m:
	ID = Intrinsic::riscv_vmulhsu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i8m4_m:
	ID = Intrinsic::riscv_vmulhsu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i8m8_m:
	ID = Intrinsic::riscv_vmulhsu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i16m1_m:
	ID = Intrinsic::riscv_vmulhsu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i16m2_m:
	ID = Intrinsic::riscv_vmulhsu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i16m4_m:
	ID = Intrinsic::riscv_vmulhsu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i16m8_m:
	ID = Intrinsic::riscv_vmulhsu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i32m1_m:
	ID = Intrinsic::riscv_vmulhsu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i32m2_m:
	ID = Intrinsic::riscv_vmulhsu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i32m4_m:
	ID = Intrinsic::riscv_vmulhsu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmulhsu_vx_i32m8_m:
	ID = Intrinsic::riscv_vmulhsu_vx_32m8_m;
	break;

	//Vector Integer Divide Functions
    case RISCV::BI__builtin_riscv_vdivu_vv_u8m1:
	ID = Intrinsic::riscv_vdivu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u8m2:
	ID = Intrinsic::riscv_vdivu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u8m4:
	ID = Intrinsic::riscv_vdivu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u8m8:
	ID = Intrinsic::riscv_vdivu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u16m1:
	ID = Intrinsic::riscv_vdivu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u16m2:
	ID = Intrinsic::riscv_vdivu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u16m4:
	ID = Intrinsic::riscv_vdivu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u16m8:
	ID = Intrinsic::riscv_vdivu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u32m1:
	ID = Intrinsic::riscv_vdivu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u32m2:
	ID = Intrinsic::riscv_vdivu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u32m4:
	ID = Intrinsic::riscv_vdivu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u32m8:
	ID = Intrinsic::riscv_vdivu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u8m1:
	ID = Intrinsic::riscv_vdivu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u8m2:
	ID = Intrinsic::riscv_vdivu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u8m4:
	ID = Intrinsic::riscv_vdivu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u8m8:
	ID = Intrinsic::riscv_vdivu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u16m1:
	ID = Intrinsic::riscv_vdivu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u16m2:
	ID = Intrinsic::riscv_vdivu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u16m4:
	ID = Intrinsic::riscv_vdivu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u16m8:
	ID = Intrinsic::riscv_vdivu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u32m1:
	ID = Intrinsic::riscv_vdivu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u32m2:
	ID = Intrinsic::riscv_vdivu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u32m4:
	ID = Intrinsic::riscv_vdivu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u32m8:
	ID = Intrinsic::riscv_vdivu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i8m1:
	ID = Intrinsic::riscv_vdiv_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i8m2:
	ID = Intrinsic::riscv_vdiv_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i8m4:
	ID = Intrinsic::riscv_vdiv_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i8m8:
	ID = Intrinsic::riscv_vdiv_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i16m1:
	ID = Intrinsic::riscv_vdiv_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i16m2:
	ID = Intrinsic::riscv_vdiv_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i16m4:
	ID = Intrinsic::riscv_vdiv_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i16m8:
	ID = Intrinsic::riscv_vdiv_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i32m1:
	ID = Intrinsic::riscv_vdiv_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i32m2:
	ID = Intrinsic::riscv_vdiv_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i32m4:
	ID = Intrinsic::riscv_vdiv_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i32m8:
	ID = Intrinsic::riscv_vdiv_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i8m1:
	ID = Intrinsic::riscv_vdiv_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i8m2:
	ID = Intrinsic::riscv_vdiv_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i8m4:
	ID = Intrinsic::riscv_vdiv_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i8m8:
	ID = Intrinsic::riscv_vdiv_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i16m1:
	ID = Intrinsic::riscv_vdiv_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i16m2:
	ID = Intrinsic::riscv_vdiv_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i16m4:
	ID = Intrinsic::riscv_vdiv_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i16m8:
	ID = Intrinsic::riscv_vdiv_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i32m1:
	ID = Intrinsic::riscv_vdiv_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i32m2:
	ID = Intrinsic::riscv_vdiv_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i32m4:
	ID = Intrinsic::riscv_vdiv_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i32m8:
	ID = Intrinsic::riscv_vdiv_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u8m1:
	ID = Intrinsic::riscv_vremu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u8m2:
	ID = Intrinsic::riscv_vremu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u8m4:
	ID = Intrinsic::riscv_vremu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u8m8:
	ID = Intrinsic::riscv_vremu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u16m1:
	ID = Intrinsic::riscv_vremu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u16m2:
	ID = Intrinsic::riscv_vremu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u16m4:
	ID = Intrinsic::riscv_vremu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u16m8:
	ID = Intrinsic::riscv_vremu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u32m1:
	ID = Intrinsic::riscv_vremu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u32m2:
	ID = Intrinsic::riscv_vremu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u32m4:
	ID = Intrinsic::riscv_vremu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u32m8:
	ID = Intrinsic::riscv_vremu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u8m1:
	ID = Intrinsic::riscv_vremu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u8m2:
	ID = Intrinsic::riscv_vremu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u8m4:
	ID = Intrinsic::riscv_vremu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u8m8:
	ID = Intrinsic::riscv_vremu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u16m1:
	ID = Intrinsic::riscv_vremu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u16m2:
	ID = Intrinsic::riscv_vremu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u16m4:
	ID = Intrinsic::riscv_vremu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u16m8:
	ID = Intrinsic::riscv_vremu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u32m1:
	ID = Intrinsic::riscv_vremu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u32m2:
	ID = Intrinsic::riscv_vremu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u32m4:
	ID = Intrinsic::riscv_vremu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u32m8:
	ID = Intrinsic::riscv_vremu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i8m1:
	ID = Intrinsic::riscv_vrem_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i8m2:
	ID = Intrinsic::riscv_vrem_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i8m4:
	ID = Intrinsic::riscv_vrem_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i8m8:
	ID = Intrinsic::riscv_vrem_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i16m1:
	ID = Intrinsic::riscv_vrem_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i16m2:
	ID = Intrinsic::riscv_vrem_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i16m4:
	ID = Intrinsic::riscv_vrem_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i16m8:
	ID = Intrinsic::riscv_vrem_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i32m1:
	ID = Intrinsic::riscv_vrem_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i32m2:
	ID = Intrinsic::riscv_vrem_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i32m4:
	ID = Intrinsic::riscv_vrem_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i32m8:
	ID = Intrinsic::riscv_vrem_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i8m1:
	ID = Intrinsic::riscv_vrem_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i8m2:
	ID = Intrinsic::riscv_vrem_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i8m4:
	ID = Intrinsic::riscv_vrem_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i8m8:
	ID = Intrinsic::riscv_vrem_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i16m1:
	ID = Intrinsic::riscv_vrem_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i16m2:
	ID = Intrinsic::riscv_vrem_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i16m4:
	ID = Intrinsic::riscv_vrem_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i16m8:
	ID = Intrinsic::riscv_vrem_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i32m1:
	ID = Intrinsic::riscv_vrem_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i32m2:
	ID = Intrinsic::riscv_vrem_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i32m4:
	ID = Intrinsic::riscv_vrem_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i32m8:
	ID = Intrinsic::riscv_vrem_vx_32m8;
	break;
	//masked functions  
    case RISCV::BI__builtin_riscv_vdivu_vv_u8m1_m:
	ID = Intrinsic::riscv_vdivu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u8m2_m:
	ID = Intrinsic::riscv_vdivu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u8m4_m:
	ID = Intrinsic::riscv_vdivu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u8m8_m:
	ID = Intrinsic::riscv_vdivu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u16m1_m:
	ID = Intrinsic::riscv_vdivu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u16m2_m:
	ID = Intrinsic::riscv_vdivu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u16m4_m:
	ID = Intrinsic::riscv_vdivu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u16m8_m:
	ID = Intrinsic::riscv_vdivu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u32m1_m:
	ID = Intrinsic::riscv_vdivu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u32m2_m:
	ID = Intrinsic::riscv_vdivu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u32m4_m:
	ID = Intrinsic::riscv_vdivu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vv_u32m8_m:
	ID = Intrinsic::riscv_vdivu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u8m1_m:
	ID = Intrinsic::riscv_vdivu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u8m2_m:
	ID = Intrinsic::riscv_vdivu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u8m4_m:
	ID = Intrinsic::riscv_vdivu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u8m8_m:
	ID = Intrinsic::riscv_vdivu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u16m1_m:
	ID = Intrinsic::riscv_vdivu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u16m2_m:
	ID = Intrinsic::riscv_vdivu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u16m4_m:
	ID = Intrinsic::riscv_vdivu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u16m8_m:
	ID = Intrinsic::riscv_vdivu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u32m1_m:
	ID = Intrinsic::riscv_vdivu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u32m2_m:
	ID = Intrinsic::riscv_vdivu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u32m4_m:
	ID = Intrinsic::riscv_vdivu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vdivu_vx_u32m8_m:
	ID = Intrinsic::riscv_vdivu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i8m1_m:
	ID = Intrinsic::riscv_vdiv_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i8m2_m:
	ID = Intrinsic::riscv_vdiv_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i8m4_m:
	ID = Intrinsic::riscv_vdiv_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i8m8_m:
	ID = Intrinsic::riscv_vdiv_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i16m1_m:
	ID = Intrinsic::riscv_vdiv_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i16m2_m:
	ID = Intrinsic::riscv_vdiv_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i16m4_m:
	ID = Intrinsic::riscv_vdiv_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i16m8_m:
	ID = Intrinsic::riscv_vdiv_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i32m1_m:
	ID = Intrinsic::riscv_vdiv_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i32m2_m:
	ID = Intrinsic::riscv_vdiv_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i32m4_m:
	ID = Intrinsic::riscv_vdiv_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vv_i32m8_m:
	ID = Intrinsic::riscv_vdiv_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i8m1_m:
	ID = Intrinsic::riscv_vdiv_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i8m2_m:
	ID = Intrinsic::riscv_vdiv_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i8m4_m:
	ID = Intrinsic::riscv_vdiv_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i8m8_m:
	ID = Intrinsic::riscv_vdiv_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i16m1_m:
	ID = Intrinsic::riscv_vdiv_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i16m2_m:
	ID = Intrinsic::riscv_vdiv_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i16m4_m:
	ID = Intrinsic::riscv_vdiv_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i16m8_m:
	ID = Intrinsic::riscv_vdiv_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i32m1_m:
	ID = Intrinsic::riscv_vdiv_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i32m2_m:
	ID = Intrinsic::riscv_vdiv_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i32m4_m:
	ID = Intrinsic::riscv_vdiv_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vdiv_vx_i32m8_m:
	ID = Intrinsic::riscv_vdiv_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u8m1_m:
	ID = Intrinsic::riscv_vremu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u8m2_m:
	ID = Intrinsic::riscv_vremu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u8m4_m:
	ID = Intrinsic::riscv_vremu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u8m8_m:
	ID = Intrinsic::riscv_vremu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u16m1_m:
	ID = Intrinsic::riscv_vremu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u16m2_m:
	ID = Intrinsic::riscv_vremu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u16m4_m:
	ID = Intrinsic::riscv_vremu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u16m8_m:
	ID = Intrinsic::riscv_vremu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u32m1_m:
	ID = Intrinsic::riscv_vremu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u32m2_m:
	ID = Intrinsic::riscv_vremu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u32m4_m:
	ID = Intrinsic::riscv_vremu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vv_u32m8_m:
	ID = Intrinsic::riscv_vremu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u8m1_m:
	ID = Intrinsic::riscv_vremu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u8m2_m:
	ID = Intrinsic::riscv_vremu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u8m4_m:
	ID = Intrinsic::riscv_vremu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u8m8_m:
	ID = Intrinsic::riscv_vremu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u16m1_m:
	ID = Intrinsic::riscv_vremu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u16m2_m:
	ID = Intrinsic::riscv_vremu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u16m4_m:
	ID = Intrinsic::riscv_vremu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u16m8_m:
	ID = Intrinsic::riscv_vremu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u32m1_m:
	ID = Intrinsic::riscv_vremu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u32m2_m:
	ID = Intrinsic::riscv_vremu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u32m4_m:
	ID = Intrinsic::riscv_vremu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vremu_vx_u32m8_m:
	ID = Intrinsic::riscv_vremu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i8m1_m:
	ID = Intrinsic::riscv_vrem_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i8m2_m:
	ID = Intrinsic::riscv_vrem_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i8m4_m:
	ID = Intrinsic::riscv_vrem_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i8m8_m:
	ID = Intrinsic::riscv_vrem_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i16m1_m:
	ID = Intrinsic::riscv_vrem_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i16m2_m:
	ID = Intrinsic::riscv_vrem_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i16m4_m:
	ID = Intrinsic::riscv_vrem_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i16m8_m:
	ID = Intrinsic::riscv_vrem_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i32m1_m:
	ID = Intrinsic::riscv_vrem_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i32m2_m:
	ID = Intrinsic::riscv_vrem_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i32m4_m:
	ID = Intrinsic::riscv_vrem_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vv_i32m8_m:
	ID = Intrinsic::riscv_vrem_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i8m1_m:
	ID = Intrinsic::riscv_vrem_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i8m2_m:
	ID = Intrinsic::riscv_vrem_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i8m4_m:
	ID = Intrinsic::riscv_vrem_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i8m8_m:
	ID = Intrinsic::riscv_vrem_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i16m1_m:
	ID = Intrinsic::riscv_vrem_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i16m2_m:
	ID = Intrinsic::riscv_vrem_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i16m4_m:
	ID = Intrinsic::riscv_vrem_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i16m8_m:
	ID = Intrinsic::riscv_vrem_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i32m1_m:
	ID = Intrinsic::riscv_vrem_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i32m2_m:
	ID = Intrinsic::riscv_vrem_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i32m4_m:
	ID = Intrinsic::riscv_vrem_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrem_vx_i32m8_m:
	ID = Intrinsic::riscv_vrem_vx_32m8_m;
	break;

	//Vector Widening Integer Multiply Functions
    case RISCV::BI__builtin_riscv_vwmul_vv_i16m2:
	ID = Intrinsic::riscv_vwmul_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vv_i16m4:
	ID = Intrinsic::riscv_vwmul_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vv_i16m8:
	ID = Intrinsic::riscv_vwmul_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vv_i32m2:
	ID = Intrinsic::riscv_vwmul_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vv_i32m4:
	ID = Intrinsic::riscv_vwmul_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vv_i32m8:
	ID = Intrinsic::riscv_vwmul_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i16m2:
	ID = Intrinsic::riscv_vwmul_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i16m4:
	ID = Intrinsic::riscv_vwmul_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i16m8:
	ID = Intrinsic::riscv_vwmul_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i32m2:
	ID = Intrinsic::riscv_vwmul_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i32m4:
	ID = Intrinsic::riscv_vwmul_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i32m8:
	ID = Intrinsic::riscv_vwmul_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u16m2:
	ID = Intrinsic::riscv_vwmulu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u16m4:
	ID = Intrinsic::riscv_vwmulu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u16m8:
	ID = Intrinsic::riscv_vwmulu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u32m2:
	ID = Intrinsic::riscv_vwmulu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u32m4:
	ID = Intrinsic::riscv_vwmulu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u32m8:
	ID = Intrinsic::riscv_vwmulu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u16m2:
	ID = Intrinsic::riscv_vwmulu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u16m4:
	ID = Intrinsic::riscv_vwmulu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u16m8:
	ID = Intrinsic::riscv_vwmulu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u32m2:
	ID = Intrinsic::riscv_vwmulu_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u32m4:
	ID = Intrinsic::riscv_vwmulu_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u32m8:
	ID = Intrinsic::riscv_vwmulu_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i16m2:
	ID = Intrinsic::riscv_vwmulsu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i16m4:
	ID = Intrinsic::riscv_vwmulsu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i16m8:
	ID = Intrinsic::riscv_vwmulsu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i32m2:
	ID = Intrinsic::riscv_vwmulsu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i32m4:
	ID = Intrinsic::riscv_vwmulsu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i32m8:
	ID = Intrinsic::riscv_vwmulsu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i16m2:
	ID = Intrinsic::riscv_vwmulsu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i16m4:
	ID = Intrinsic::riscv_vwmulsu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i16m8:
	ID = Intrinsic::riscv_vwmulsu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i32m2:
	ID = Intrinsic::riscv_vwmulsu_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i32m4:
	ID = Intrinsic::riscv_vwmulsu_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i32m8:
	ID = Intrinsic::riscv_vwmulsu_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vwmul_vv_i16m2_m:
	ID = Intrinsic::riscv_vwmul_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vv_i16m4_m:
	ID = Intrinsic::riscv_vwmul_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vv_i16m8_m:
	ID = Intrinsic::riscv_vwmul_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vv_i32m2_m:
	ID = Intrinsic::riscv_vwmul_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vv_i32m4_m:
	ID = Intrinsic::riscv_vwmul_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vv_i32m8_m:
	ID = Intrinsic::riscv_vwmul_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i16m2_m:
	ID = Intrinsic::riscv_vwmul_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i16m4_m:
	ID = Intrinsic::riscv_vwmul_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i16m8_m:
	ID = Intrinsic::riscv_vwmul_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i32m2_m:
	ID = Intrinsic::riscv_vwmul_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i32m4_m:
	ID = Intrinsic::riscv_vwmul_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmul_vx_i32m8_m:
	ID = Intrinsic::riscv_vwmul_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u16m2_m:
	ID = Intrinsic::riscv_vwmulu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u16m4_m:
	ID = Intrinsic::riscv_vwmulu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u16m8_m:
	ID = Intrinsic::riscv_vwmulu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u32m2_m:
	ID = Intrinsic::riscv_vwmulu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u32m4_m:
	ID = Intrinsic::riscv_vwmulu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vv_u32m8_m:
	ID = Intrinsic::riscv_vwmulu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u16m2_m:
	ID = Intrinsic::riscv_vwmulu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u16m4_m:
	ID = Intrinsic::riscv_vwmulu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u16m8_m:
	ID = Intrinsic::riscv_vwmulu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u32m2_m:
	ID = Intrinsic::riscv_vwmulu_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u32m4_m:
	ID = Intrinsic::riscv_vwmulu_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulu_vx_u32m8_m:
	ID = Intrinsic::riscv_vwmulu_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i16m2_m:
	ID = Intrinsic::riscv_vwmulsu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i16m4_m:
	ID = Intrinsic::riscv_vwmulsu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i16m8_m:
	ID = Intrinsic::riscv_vwmulsu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i32m2_m:
	ID = Intrinsic::riscv_vwmulsu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i32m4_m:
	ID = Intrinsic::riscv_vwmulsu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vv_i32m8_m:
	ID = Intrinsic::riscv_vwmulsu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i16m2_m:
	ID = Intrinsic::riscv_vwmulsu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i16m4_m:
	ID = Intrinsic::riscv_vwmulsu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i16m8_m:
	ID = Intrinsic::riscv_vwmulsu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i32m2_m:
	ID = Intrinsic::riscv_vwmulsu_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i32m4_m:
	ID = Intrinsic::riscv_vwmulsu_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmulsu_vx_i32m8_m:
	ID = Intrinsic::riscv_vwmulsu_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;

	//Vector Single-Width Integer Multiply-Add Functions
    case RISCV::BI__builtin_riscv_vmacc_vv_i8m1:
    case RISCV::BI__builtin_riscv_vmacc_vv_u8m1:
	ID = Intrinsic::riscv_vmacc_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i8m2:
    case RISCV::BI__builtin_riscv_vmacc_vv_u8m2:
	ID = Intrinsic::riscv_vmacc_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i8m4:
    case RISCV::BI__builtin_riscv_vmacc_vv_u8m4:
	ID = Intrinsic::riscv_vmacc_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i8m8:
    case RISCV::BI__builtin_riscv_vmacc_vv_u8m8:
	ID = Intrinsic::riscv_vmacc_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i16m1:
    case RISCV::BI__builtin_riscv_vmacc_vv_u16m1:
	ID = Intrinsic::riscv_vmacc_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i16m2:
    case RISCV::BI__builtin_riscv_vmacc_vv_u16m2:
	ID = Intrinsic::riscv_vmacc_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i16m4:
    case RISCV::BI__builtin_riscv_vmacc_vv_u16m4:
	ID = Intrinsic::riscv_vmacc_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i16m8:
    case RISCV::BI__builtin_riscv_vmacc_vv_u16m8:
	ID = Intrinsic::riscv_vmacc_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i32m1:
    case RISCV::BI__builtin_riscv_vmacc_vv_u32m1:
	ID = Intrinsic::riscv_vmacc_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i32m2:
    case RISCV::BI__builtin_riscv_vmacc_vv_u32m2:
	ID = Intrinsic::riscv_vmacc_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i32m4:
    case RISCV::BI__builtin_riscv_vmacc_vv_u32m4:
	ID = Intrinsic::riscv_vmacc_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i32m8:
    case RISCV::BI__builtin_riscv_vmacc_vv_u32m8:
	ID = Intrinsic::riscv_vmacc_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i8m1:
    case RISCV::BI__builtin_riscv_vmacc_vx_u8m1:
	ID = Intrinsic::riscv_vmacc_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i8m2:
    case RISCV::BI__builtin_riscv_vmacc_vx_u8m2:
	ID = Intrinsic::riscv_vmacc_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i8m4:
    case RISCV::BI__builtin_riscv_vmacc_vx_u8m4:
	ID = Intrinsic::riscv_vmacc_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i8m8:
    case RISCV::BI__builtin_riscv_vmacc_vx_u8m8:
	ID = Intrinsic::riscv_vmacc_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i16m1:
    case RISCV::BI__builtin_riscv_vmacc_vx_u16m1:
	ID = Intrinsic::riscv_vmacc_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i16m2:
    case RISCV::BI__builtin_riscv_vmacc_vx_u16m2:
	ID = Intrinsic::riscv_vmacc_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i16m4:
    case RISCV::BI__builtin_riscv_vmacc_vx_u16m4:
	ID = Intrinsic::riscv_vmacc_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i16m8:
    case RISCV::BI__builtin_riscv_vmacc_vx_u16m8:
	ID = Intrinsic::riscv_vmacc_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i32m1:
    case RISCV::BI__builtin_riscv_vmacc_vx_u32m1:
	ID = Intrinsic::riscv_vmacc_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i32m2:
    case RISCV::BI__builtin_riscv_vmacc_vx_u32m2:
	ID = Intrinsic::riscv_vmacc_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i32m4:
    case RISCV::BI__builtin_riscv_vmacc_vx_u32m4:
	ID = Intrinsic::riscv_vmacc_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i32m8:
    case RISCV::BI__builtin_riscv_vmacc_vx_u32m8:
	ID = Intrinsic::riscv_vmacc_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i8m1:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u8m1:
	ID = Intrinsic::riscv_vnmsac_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i8m2:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u8m2:
	ID = Intrinsic::riscv_vnmsac_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i8m4:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u8m4:
	ID = Intrinsic::riscv_vnmsac_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i8m8:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u8m8:
	ID = Intrinsic::riscv_vnmsac_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i16m1:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u16m1:
	ID = Intrinsic::riscv_vnmsac_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i16m2:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u16m2:
	ID = Intrinsic::riscv_vnmsac_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i16m4:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u16m4:
	ID = Intrinsic::riscv_vnmsac_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i16m8:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u16m8:
	ID = Intrinsic::riscv_vnmsac_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i32m1:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u32m1:
	ID = Intrinsic::riscv_vnmsac_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i32m2:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u32m2:
	ID = Intrinsic::riscv_vnmsac_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i32m4:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u32m4:
	ID = Intrinsic::riscv_vnmsac_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i32m8:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u32m8:
	ID = Intrinsic::riscv_vnmsac_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i8m1:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u8m1:
	ID = Intrinsic::riscv_vnmsac_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i8m2:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u8m2:
	ID = Intrinsic::riscv_vnmsac_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i8m4:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u8m4:
	ID = Intrinsic::riscv_vnmsac_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i8m8:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u8m8:
	ID = Intrinsic::riscv_vnmsac_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i16m1:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u16m1:
	ID = Intrinsic::riscv_vnmsac_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i16m2:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u16m2:
	ID = Intrinsic::riscv_vnmsac_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i16m4:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u16m4:
	ID = Intrinsic::riscv_vnmsac_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i16m8:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u16m8:
	ID = Intrinsic::riscv_vnmsac_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i32m1:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u32m1:
	ID = Intrinsic::riscv_vnmsac_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i32m2:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u32m2:
	ID = Intrinsic::riscv_vnmsac_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i32m4:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u32m4:
	ID = Intrinsic::riscv_vnmsac_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i32m8:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u32m8:
	ID = Intrinsic::riscv_vnmsac_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i8m1:
    case RISCV::BI__builtin_riscv_vmadd_vv_u8m1:
	ID = Intrinsic::riscv_vmadd_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i8m2:
    case RISCV::BI__builtin_riscv_vmadd_vv_u8m2:
	ID = Intrinsic::riscv_vmadd_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i8m4:
    case RISCV::BI__builtin_riscv_vmadd_vv_u8m4:
	ID = Intrinsic::riscv_vmadd_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i8m8:
    case RISCV::BI__builtin_riscv_vmadd_vv_u8m8:
	ID = Intrinsic::riscv_vmadd_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i16m1:
    case RISCV::BI__builtin_riscv_vmadd_vv_u16m1:
	ID = Intrinsic::riscv_vmadd_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i16m2:
    case RISCV::BI__builtin_riscv_vmadd_vv_u16m2:
	ID = Intrinsic::riscv_vmadd_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i16m4:
    case RISCV::BI__builtin_riscv_vmadd_vv_u16m4:
	ID = Intrinsic::riscv_vmadd_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i16m8:
    case RISCV::BI__builtin_riscv_vmadd_vv_u16m8:
	ID = Intrinsic::riscv_vmadd_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i32m1:
    case RISCV::BI__builtin_riscv_vmadd_vv_u32m1:
	ID = Intrinsic::riscv_vmadd_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i32m2:
    case RISCV::BI__builtin_riscv_vmadd_vv_u32m2:
	ID = Intrinsic::riscv_vmadd_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i32m4:
    case RISCV::BI__builtin_riscv_vmadd_vv_u32m4:
	ID = Intrinsic::riscv_vmadd_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i32m8:
    case RISCV::BI__builtin_riscv_vmadd_vv_u32m8:
	ID = Intrinsic::riscv_vmadd_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i8m1:
    case RISCV::BI__builtin_riscv_vmadd_vx_u8m1:
	ID = Intrinsic::riscv_vmadd_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i8m2:
    case RISCV::BI__builtin_riscv_vmadd_vx_u8m2:
	ID = Intrinsic::riscv_vmadd_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i8m4:
    case RISCV::BI__builtin_riscv_vmadd_vx_u8m4:
	ID = Intrinsic::riscv_vmadd_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i8m8:
    case RISCV::BI__builtin_riscv_vmadd_vx_u8m8:
	ID = Intrinsic::riscv_vmadd_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i16m1:
    case RISCV::BI__builtin_riscv_vmadd_vx_u16m1:
	ID = Intrinsic::riscv_vmadd_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i16m2:
    case RISCV::BI__builtin_riscv_vmadd_vx_u16m2:
	ID = Intrinsic::riscv_vmadd_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i16m4:
    case RISCV::BI__builtin_riscv_vmadd_vx_u16m4:
	ID = Intrinsic::riscv_vmadd_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i16m8:
    case RISCV::BI__builtin_riscv_vmadd_vx_u16m8:
	ID = Intrinsic::riscv_vmadd_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i32m1:
    case RISCV::BI__builtin_riscv_vmadd_vx_u32m1:
	ID = Intrinsic::riscv_vmadd_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i32m2:
    case RISCV::BI__builtin_riscv_vmadd_vx_u32m2:
	ID = Intrinsic::riscv_vmadd_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i32m4:
    case RISCV::BI__builtin_riscv_vmadd_vx_u32m4:
	ID = Intrinsic::riscv_vmadd_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i32m8:
    case RISCV::BI__builtin_riscv_vmadd_vx_u32m8:
	ID = Intrinsic::riscv_vmadd_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i8m1:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u8m1:
	ID = Intrinsic::riscv_vnmsub_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i8m2:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u8m2:
	ID = Intrinsic::riscv_vnmsub_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i8m4:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u8m4:
	ID = Intrinsic::riscv_vnmsub_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i8m8:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u8m8:
	ID = Intrinsic::riscv_vnmsub_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i16m1:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u16m1:
	ID = Intrinsic::riscv_vnmsub_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i16m2:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u16m2:
	ID = Intrinsic::riscv_vnmsub_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i16m4:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u16m4:
	ID = Intrinsic::riscv_vnmsub_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i16m8:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u16m8:
	ID = Intrinsic::riscv_vnmsub_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i32m1:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u32m1:
	ID = Intrinsic::riscv_vnmsub_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i32m2:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u32m2:
	ID = Intrinsic::riscv_vnmsub_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i32m4:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u32m4:
	ID = Intrinsic::riscv_vnmsub_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i32m8:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u32m8:
	ID = Intrinsic::riscv_vnmsub_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i8m1:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u8m1:
	ID = Intrinsic::riscv_vnmsub_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i8m2:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u8m2:
	ID = Intrinsic::riscv_vnmsub_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i8m4:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u8m4:
	ID = Intrinsic::riscv_vnmsub_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i8m8:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u8m8:
	ID = Intrinsic::riscv_vnmsub_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i16m1:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u16m1:
	ID = Intrinsic::riscv_vnmsub_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i16m2:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u16m2:
	ID = Intrinsic::riscv_vnmsub_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i16m4:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u16m4:
	ID = Intrinsic::riscv_vnmsub_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i16m8:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u16m8:
	ID = Intrinsic::riscv_vnmsub_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i32m1:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u32m1:
	ID = Intrinsic::riscv_vnmsub_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i32m2:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u32m2:
	ID = Intrinsic::riscv_vnmsub_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i32m4:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u32m4:
	ID = Intrinsic::riscv_vnmsub_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i32m8:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u32m8:
	ID = Intrinsic::riscv_vnmsub_vx_32m8;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vmacc_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u8m1_m:
	ID = Intrinsic::riscv_vmacc_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u8m2_m:
	ID = Intrinsic::riscv_vmacc_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u8m4_m:
	ID = Intrinsic::riscv_vmacc_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u8m8_m:
	ID = Intrinsic::riscv_vmacc_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u16m1_m:
	ID = Intrinsic::riscv_vmacc_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u16m2_m:
	ID = Intrinsic::riscv_vmacc_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u16m4_m:
	ID = Intrinsic::riscv_vmacc_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u16m8_m:
	ID = Intrinsic::riscv_vmacc_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u32m1_m:
	ID = Intrinsic::riscv_vmacc_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u32m2_m:
	ID = Intrinsic::riscv_vmacc_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u32m4_m:
	ID = Intrinsic::riscv_vmacc_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vmacc_vv_u32m8_m:
	ID = Intrinsic::riscv_vmacc_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u8m1_m:
	ID = Intrinsic::riscv_vmacc_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u8m2_m:
	ID = Intrinsic::riscv_vmacc_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u8m4_m:
	ID = Intrinsic::riscv_vmacc_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u8m8_m:
	ID = Intrinsic::riscv_vmacc_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u16m1_m:
	ID = Intrinsic::riscv_vmacc_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u16m2_m:
	ID = Intrinsic::riscv_vmacc_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u16m4_m:
	ID = Intrinsic::riscv_vmacc_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u16m8_m:
	ID = Intrinsic::riscv_vmacc_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u32m1_m:
	ID = Intrinsic::riscv_vmacc_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u32m2_m:
	ID = Intrinsic::riscv_vmacc_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u32m4_m:
	ID = Intrinsic::riscv_vmacc_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmacc_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vmacc_vx_u32m8_m:
	ID = Intrinsic::riscv_vmacc_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u8m1_m:
	ID = Intrinsic::riscv_vnmsac_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u8m2_m:
	ID = Intrinsic::riscv_vnmsac_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u8m4_m:
	ID = Intrinsic::riscv_vnmsac_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u8m8_m:
	ID = Intrinsic::riscv_vnmsac_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u16m1_m:
	ID = Intrinsic::riscv_vnmsac_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u16m2_m:
	ID = Intrinsic::riscv_vnmsac_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u16m4_m:
	ID = Intrinsic::riscv_vnmsac_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u16m8_m:
	ID = Intrinsic::riscv_vnmsac_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u32m1_m:
	ID = Intrinsic::riscv_vnmsac_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u32m2_m:
	ID = Intrinsic::riscv_vnmsac_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u32m4_m:
	ID = Intrinsic::riscv_vnmsac_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vnmsac_vv_u32m8_m:
	ID = Intrinsic::riscv_vnmsac_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u8m1_m:
	ID = Intrinsic::riscv_vnmsac_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u8m2_m:
	ID = Intrinsic::riscv_vnmsac_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u8m4_m:
	ID = Intrinsic::riscv_vnmsac_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u8m8_m:
	ID = Intrinsic::riscv_vnmsac_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u16m1_m:
	ID = Intrinsic::riscv_vnmsac_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u16m2_m:
	ID = Intrinsic::riscv_vnmsac_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u16m4_m:
	ID = Intrinsic::riscv_vnmsac_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u16m8_m:
	ID = Intrinsic::riscv_vnmsac_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u32m1_m:
	ID = Intrinsic::riscv_vnmsac_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u32m2_m:
	ID = Intrinsic::riscv_vnmsac_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u32m4_m:
	ID = Intrinsic::riscv_vnmsac_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsac_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vnmsac_vx_u32m8_m:
	ID = Intrinsic::riscv_vnmsac_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u8m1_m:
	ID = Intrinsic::riscv_vmadd_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u8m2_m:
	ID = Intrinsic::riscv_vmadd_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u8m4_m:
	ID = Intrinsic::riscv_vmadd_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u8m8_m:
	ID = Intrinsic::riscv_vmadd_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u16m1_m:
	ID = Intrinsic::riscv_vmadd_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u16m2_m:
	ID = Intrinsic::riscv_vmadd_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u16m4_m:
	ID = Intrinsic::riscv_vmadd_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u16m8_m:
	ID = Intrinsic::riscv_vmadd_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u32m1_m:
	ID = Intrinsic::riscv_vmadd_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u32m2_m:
	ID = Intrinsic::riscv_vmadd_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u32m4_m:
	ID = Intrinsic::riscv_vmadd_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vmadd_vv_u32m8_m:
	ID = Intrinsic::riscv_vmadd_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u8m1_m:
	ID = Intrinsic::riscv_vmadd_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u8m2_m:
	ID = Intrinsic::riscv_vmadd_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u8m4_m:
	ID = Intrinsic::riscv_vmadd_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u8m8_m:
	ID = Intrinsic::riscv_vmadd_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u16m1_m:
	ID = Intrinsic::riscv_vmadd_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u16m2_m:
	ID = Intrinsic::riscv_vmadd_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u16m4_m:
	ID = Intrinsic::riscv_vmadd_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u16m8_m:
	ID = Intrinsic::riscv_vmadd_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u32m1_m:
	ID = Intrinsic::riscv_vmadd_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u32m2_m:
	ID = Intrinsic::riscv_vmadd_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u32m4_m:
	ID = Intrinsic::riscv_vmadd_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmadd_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vmadd_vx_u32m8_m:
	ID = Intrinsic::riscv_vmadd_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u8m1_m:
	ID = Intrinsic::riscv_vnmsub_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u8m2_m:
	ID = Intrinsic::riscv_vnmsub_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u8m4_m:
	ID = Intrinsic::riscv_vnmsub_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u8m8_m:
	ID = Intrinsic::riscv_vnmsub_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u16m1_m:
	ID = Intrinsic::riscv_vnmsub_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u16m2_m:
	ID = Intrinsic::riscv_vnmsub_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u16m4_m:
	ID = Intrinsic::riscv_vnmsub_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u16m8_m:
	ID = Intrinsic::riscv_vnmsub_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u32m1_m:
	ID = Intrinsic::riscv_vnmsub_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u32m2_m:
	ID = Intrinsic::riscv_vnmsub_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u32m4_m:
	ID = Intrinsic::riscv_vnmsub_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vnmsub_vv_u32m8_m:
	ID = Intrinsic::riscv_vnmsub_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u8m1_m:
	ID = Intrinsic::riscv_vnmsub_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u8m2_m:
	ID = Intrinsic::riscv_vnmsub_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u8m4_m:
	ID = Intrinsic::riscv_vnmsub_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u8m8_m:
	ID = Intrinsic::riscv_vnmsub_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u16m1_m:
	ID = Intrinsic::riscv_vnmsub_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u16m2_m:
	ID = Intrinsic::riscv_vnmsub_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u16m4_m:
	ID = Intrinsic::riscv_vnmsub_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u16m8_m:
	ID = Intrinsic::riscv_vnmsub_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u32m1_m:
	ID = Intrinsic::riscv_vnmsub_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u32m2_m:
	ID = Intrinsic::riscv_vnmsub_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u32m4_m:
	ID = Intrinsic::riscv_vnmsub_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnmsub_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vnmsub_vx_u32m8_m:
	ID = Intrinsic::riscv_vnmsub_vx_32m8_m;
	break;

	//masked functions
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u16m2:
	ID = Intrinsic::riscv_vwmaccu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u16m4:
	ID = Intrinsic::riscv_vwmaccu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u16m8:
	ID = Intrinsic::riscv_vwmaccu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u32m2:
	ID = Intrinsic::riscv_vwmaccu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u32m4:
	ID = Intrinsic::riscv_vwmaccu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u32m8:
	ID = Intrinsic::riscv_vwmaccu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u16m2:
	ID = Intrinsic::riscv_vwmaccu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u16m4:
	ID = Intrinsic::riscv_vwmaccu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u16m8:
	ID = Intrinsic::riscv_vwmaccu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u32m2:
	ID = Intrinsic::riscv_vwmaccu_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u32m4:
	ID = Intrinsic::riscv_vwmaccu_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u32m8:
	ID = Intrinsic::riscv_vwmaccu_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i16m2:
	ID = Intrinsic::riscv_vwmacc_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i16m4:
	ID = Intrinsic::riscv_vwmacc_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i16m8:
	ID = Intrinsic::riscv_vwmacc_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i32m2:
	ID = Intrinsic::riscv_vwmacc_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i32m4:
	ID = Intrinsic::riscv_vwmacc_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i32m8:
	ID = Intrinsic::riscv_vwmacc_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i16m2:
	ID = Intrinsic::riscv_vwmacc_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i16m4:
	ID = Intrinsic::riscv_vwmacc_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i16m8:
	ID = Intrinsic::riscv_vwmacc_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i32m2:
	ID = Intrinsic::riscv_vwmacc_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i32m4:
	ID = Intrinsic::riscv_vwmacc_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i32m8:
	ID = Intrinsic::riscv_vwmacc_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i16m2:
	ID = Intrinsic::riscv_vwmaccsu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i16m4:
	ID = Intrinsic::riscv_vwmaccsu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i16m8:
	ID = Intrinsic::riscv_vwmaccsu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i32m2:
	ID = Intrinsic::riscv_vwmaccsu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i32m4:
	ID = Intrinsic::riscv_vwmaccsu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i32m8:
	ID = Intrinsic::riscv_vwmaccsu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i16m2:
	ID = Intrinsic::riscv_vwmaccsu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i16m4:
	ID = Intrinsic::riscv_vwmaccsu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i16m8:
	ID = Intrinsic::riscv_vwmaccsu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i32m2:
	ID = Intrinsic::riscv_vwmaccsu_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i32m4:
	ID = Intrinsic::riscv_vwmaccsu_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i32m8:
	ID = Intrinsic::riscv_vwmaccsu_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i16m2:
	ID = Intrinsic::riscv_vwmaccus_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i16m4:
	ID = Intrinsic::riscv_vwmaccus_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i16m8:
	ID = Intrinsic::riscv_vwmaccus_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i32m2:
	ID = Intrinsic::riscv_vwmaccus_vx_32m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i32m4:
	ID = Intrinsic::riscv_vwmaccus_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i32m8:
	ID = Intrinsic::riscv_vwmaccus_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
	//masked functions 
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u16m2_m:
	ID = Intrinsic::riscv_vwmaccu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u16m4_m:
	ID = Intrinsic::riscv_vwmaccu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u16m8_m:
	ID = Intrinsic::riscv_vwmaccu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u32m2_m:
	ID = Intrinsic::riscv_vwmaccu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u32m4_m:
	ID = Intrinsic::riscv_vwmaccu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vv_u32m8_m:
	ID = Intrinsic::riscv_vwmaccu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u16m2_m:
	ID = Intrinsic::riscv_vwmaccu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u16m4_m:
	ID = Intrinsic::riscv_vwmaccu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u16m8_m:
	ID = Intrinsic::riscv_vwmaccu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u32m2_m:
	ID = Intrinsic::riscv_vwmaccu_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u32m4_m:
	ID = Intrinsic::riscv_vwmaccu_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccu_vx_u32m8_m:
	ID = Intrinsic::riscv_vwmaccu_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i16m2_m:
	ID = Intrinsic::riscv_vwmacc_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i16m4_m:
	ID = Intrinsic::riscv_vwmacc_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i16m8_m:
	ID = Intrinsic::riscv_vwmacc_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i32m2_m:
	ID = Intrinsic::riscv_vwmacc_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i32m4_m:
	ID = Intrinsic::riscv_vwmacc_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vv_i32m8_m:
	ID = Intrinsic::riscv_vwmacc_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i16m2_m:
	ID = Intrinsic::riscv_vwmacc_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i16m4_m:
	ID = Intrinsic::riscv_vwmacc_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i16m8_m:
	ID = Intrinsic::riscv_vwmacc_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i32m2_m:
	ID = Intrinsic::riscv_vwmacc_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i32m4_m:
	ID = Intrinsic::riscv_vwmacc_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmacc_vx_i32m8_m:
	ID = Intrinsic::riscv_vwmacc_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i16m2_m:
	ID = Intrinsic::riscv_vwmaccsu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i16m4_m:
	ID = Intrinsic::riscv_vwmaccsu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i16m8_m:
	ID = Intrinsic::riscv_vwmaccsu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i32m2_m:
	ID = Intrinsic::riscv_vwmaccsu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i32m4_m:
	ID = Intrinsic::riscv_vwmaccsu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vv_i32m8_m:
	ID = Intrinsic::riscv_vwmaccsu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i16m2_m:
	ID = Intrinsic::riscv_vwmaccsu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i16m4_m:
	ID = Intrinsic::riscv_vwmaccsu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i16m8_m:
	ID = Intrinsic::riscv_vwmaccsu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i32m2_m:
	ID = Intrinsic::riscv_vwmaccsu_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i32m4_m:
	ID = Intrinsic::riscv_vwmaccsu_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccsu_vx_i32m8_m:
	ID = Intrinsic::riscv_vwmaccsu_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i16m2_m:
	ID = Intrinsic::riscv_vwmaccus_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i16m4_m:
	ID = Intrinsic::riscv_vwmaccus_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i16m8_m:
	ID = Intrinsic::riscv_vwmaccus_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i32m2_m:
	ID = Intrinsic::riscv_vwmaccus_vx_32m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i32m4_m:
	ID = Intrinsic::riscv_vwmaccus_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vwmaccus_vx_i32m8_m:
	ID = Intrinsic::riscv_vwmaccus_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;

	//Vector Quad-Widening Integer Multiply-Add Functions
    case RISCV::BI__builtin_riscv_vqmaccu_vv_u32m4:
	ID = Intrinsic::riscv_vqmaccu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vqmaccu_vv_u32m8:
	ID = Intrinsic::riscv_vqmaccu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vqmaccu_vx_u32m4:
	ID = Intrinsic::riscv_vqmaccu_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmaccu_vx_u32m8:
	ID = Intrinsic::riscv_vqmaccu_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmacc_vv_i32m4:
	ID = Intrinsic::riscv_vqmacc_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vqmacc_vv_i32m8:
	ID = Intrinsic::riscv_vqmacc_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vqmacc_vx_i32m4:
	ID = Intrinsic::riscv_vqmacc_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmacc_vx_i32m8:
	ID = Intrinsic::riscv_vqmacc_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmaccsu_vv_i32m4:
	ID = Intrinsic::riscv_vqmaccsu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vqmaccsu_vv_i32m8:
	ID = Intrinsic::riscv_vqmaccsu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vqmaccsu_vx_i32m4:
	ID = Intrinsic::riscv_vqmaccsu_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmaccsu_vx_i32m8:
	ID = Intrinsic::riscv_vqmaccsu_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmaccus_vx_i32m4:
	ID = Intrinsic::riscv_vqmaccus_vx_32m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmaccus_vx_i32m8:
	ID = Intrinsic::riscv_vqmaccus_vx_32m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vqmaccu_vv_u32m4_m:
	ID = Intrinsic::riscv_vqmaccu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vqmaccu_vv_u32m8_m:
	ID = Intrinsic::riscv_vqmaccu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vqmaccu_vx_u32m4_m:
	ID = Intrinsic::riscv_vqmaccu_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmaccu_vx_u32m8_m:
	ID = Intrinsic::riscv_vqmaccu_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmacc_vv_i32m4_m:
	ID = Intrinsic::riscv_vqmacc_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vqmacc_vv_i32m8_m:
	ID = Intrinsic::riscv_vqmacc_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vqmacc_vx_i32m4_m:
	ID = Intrinsic::riscv_vqmacc_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmacc_vx_i32m8_m:
	ID = Intrinsic::riscv_vqmacc_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmaccsu_vv_i32m4_m:
	ID = Intrinsic::riscv_vqmaccsu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vqmaccsu_vv_i32m8_m:
	ID = Intrinsic::riscv_vqmaccsu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vqmaccsu_vx_i32m4_m:
	ID = Intrinsic::riscv_vqmaccsu_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmaccsu_vx_i32m8_m:
	ID = Intrinsic::riscv_vqmaccsu_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmaccus_vx_i32m4_m:
	ID = Intrinsic::riscv_vqmaccus_vx_32m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vqmaccus_vx_i32m8_m:
	ID = Intrinsic::riscv_vqmaccus_vx_32m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;

	//Vector Integer Merge Functions
    case RISCV::BI__builtin_riscv_vmerge_vvm_i8m1_m:
	ID = Intrinsic::riscv_vmerge_vvm_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i8m2_m:
	ID = Intrinsic::riscv_vmerge_vvm_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i8m4_m:
	ID = Intrinsic::riscv_vmerge_vvm_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i8m8_m:
	ID = Intrinsic::riscv_vmerge_vvm_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i16m1_m:
	ID = Intrinsic::riscv_vmerge_vvm_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i16m2_m:
	ID = Intrinsic::riscv_vmerge_vvm_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i16m4_m:
	ID = Intrinsic::riscv_vmerge_vvm_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i16m8_m:
	ID = Intrinsic::riscv_vmerge_vvm_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i32m1_m:
	ID = Intrinsic::riscv_vmerge_vvm_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i32m2_m:
	ID = Intrinsic::riscv_vmerge_vvm_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i32m4_m:
	ID = Intrinsic::riscv_vmerge_vvm_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vvm_i32m8_m:
	ID = Intrinsic::riscv_vmerge_vvm_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i8m1_m:
	ID = Intrinsic::riscv_vmerge_vxm_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i8m2_m:
	ID = Intrinsic::riscv_vmerge_vxm_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i8m4_m:
	ID = Intrinsic::riscv_vmerge_vxm_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i8m8_m:
	ID = Intrinsic::riscv_vmerge_vxm_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i16m1_m:
	ID = Intrinsic::riscv_vmerge_vxm_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i16m2_m:
	ID = Intrinsic::riscv_vmerge_vxm_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i16m4_m:
	ID = Intrinsic::riscv_vmerge_vxm_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i16m8_m:
	ID = Intrinsic::riscv_vmerge_vxm_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i32m1_m:
	ID = Intrinsic::riscv_vmerge_vxm_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i32m2_m:
	ID = Intrinsic::riscv_vmerge_vxm_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i32m4_m:
	ID = Intrinsic::riscv_vmerge_vxm_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vxm_i32m8_m:
	ID = Intrinsic::riscv_vmerge_vxm_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i8m1_m:
	ID = Intrinsic::riscv_vmerge_vim_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i8m2_m:
	ID = Intrinsic::riscv_vmerge_vim_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i8m4_m:
	ID = Intrinsic::riscv_vmerge_vim_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i8m8_m:
	ID = Intrinsic::riscv_vmerge_vim_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i16m1_m:
	ID = Intrinsic::riscv_vmerge_vim_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i16m2_m:
	ID = Intrinsic::riscv_vmerge_vim_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i16m4_m:
	ID = Intrinsic::riscv_vmerge_vim_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i16m8_m:
	ID = Intrinsic::riscv_vmerge_vim_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i32m1_m:
	ID = Intrinsic::riscv_vmerge_vim_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i32m2_m:
	ID = Intrinsic::riscv_vmerge_vim_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i32m4_m:
	ID = Intrinsic::riscv_vmerge_vim_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmerge_vim_i32m8_m:
	ID = Intrinsic::riscv_vmerge_vim_32m8_m;
	break;

	//Vector Integer Move Functions
    case RISCV::BI__builtin_riscv_vmv_v_v_i8m1:
    case RISCV::BI__builtin_riscv_vmv_v_v_u8m1:
	ID = Intrinsic::riscv_vmv_v_v_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i8m2:
    case RISCV::BI__builtin_riscv_vmv_v_v_u8m2:
	ID = Intrinsic::riscv_vmv_v_v_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i8m4:
    case RISCV::BI__builtin_riscv_vmv_v_v_u8m4:
	ID = Intrinsic::riscv_vmv_v_v_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i8m8:
    case RISCV::BI__builtin_riscv_vmv_v_v_u8m8:
	ID = Intrinsic::riscv_vmv_v_v_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i16m1:
    case RISCV::BI__builtin_riscv_vmv_v_v_u16m1:
	ID = Intrinsic::riscv_vmv_v_v_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i16m2:
    case RISCV::BI__builtin_riscv_vmv_v_v_u16m2:
	ID = Intrinsic::riscv_vmv_v_v_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i16m4:
    case RISCV::BI__builtin_riscv_vmv_v_v_u16m4:
	ID = Intrinsic::riscv_vmv_v_v_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i16m8:
    case RISCV::BI__builtin_riscv_vmv_v_v_u16m8:
	ID = Intrinsic::riscv_vmv_v_v_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i32m1:
    case RISCV::BI__builtin_riscv_vmv_v_v_u32m1:
	ID = Intrinsic::riscv_vmv_v_v_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i32m2:
    case RISCV::BI__builtin_riscv_vmv_v_v_u32m2:
	ID = Intrinsic::riscv_vmv_v_v_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i32m4:
    case RISCV::BI__builtin_riscv_vmv_v_v_u32m4:
	ID = Intrinsic::riscv_vmv_v_v_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_v_i32m8:
    case RISCV::BI__builtin_riscv_vmv_v_v_u32m8:
	ID = Intrinsic::riscv_vmv_v_v_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i8m1:
    case RISCV::BI__builtin_riscv_vmv_v_x_u8m1:
	ID = Intrinsic::riscv_vmv_v_x_8m1;
	Ops[0] = Builder.CreateSExt(Ops[0], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i8m2:
    case RISCV::BI__builtin_riscv_vmv_v_x_u8m2:
	ID = Intrinsic::riscv_vmv_v_x_8m2;
	Ops[0] = Builder.CreateSExt(Ops[0], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i8m4:
    case RISCV::BI__builtin_riscv_vmv_v_x_u8m4:
	ID = Intrinsic::riscv_vmv_v_x_8m4;
	Ops[0] = Builder.CreateSExt(Ops[0], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i8m8:
    case RISCV::BI__builtin_riscv_vmv_v_x_u8m8:
	ID = Intrinsic::riscv_vmv_v_x_8m8;
	Ops[0] = Builder.CreateSExt(Ops[0], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i16m1:
    case RISCV::BI__builtin_riscv_vmv_v_x_u16m1:
	ID = Intrinsic::riscv_vmv_v_x_16m1;
	Ops[0] = Builder.CreateSExt(Ops[0], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i16m2:
    case RISCV::BI__builtin_riscv_vmv_v_x_u16m2:
	ID = Intrinsic::riscv_vmv_v_x_16m2;
	Ops[0] = Builder.CreateSExt(Ops[0], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i16m4:
    case RISCV::BI__builtin_riscv_vmv_v_x_u16m4:
	ID = Intrinsic::riscv_vmv_v_x_16m4;
	Ops[0] = Builder.CreateSExt(Ops[0], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i16m8:
    case RISCV::BI__builtin_riscv_vmv_v_x_u16m8:
	ID = Intrinsic::riscv_vmv_v_x_16m8;
	Ops[0] = Builder.CreateSExt(Ops[0], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i32m1:
    case RISCV::BI__builtin_riscv_vmv_v_x_u32m1:
	ID = Intrinsic::riscv_vmv_v_x_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i32m2:
    case RISCV::BI__builtin_riscv_vmv_v_x_u32m2:
	ID = Intrinsic::riscv_vmv_v_x_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i32m4:
    case RISCV::BI__builtin_riscv_vmv_v_x_u32m4:
	ID = Intrinsic::riscv_vmv_v_x_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_x_i32m8:
    case RISCV::BI__builtin_riscv_vmv_v_x_u32m8:
	ID = Intrinsic::riscv_vmv_v_x_32m8;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i8m1:
    case RISCV::BI__builtin_riscv_vmv_v_i_u8m1:
	ID = Intrinsic::riscv_vmv_v_i_8m1;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i8m2:
    case RISCV::BI__builtin_riscv_vmv_v_i_u8m2:
	ID = Intrinsic::riscv_vmv_v_i_8m2;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i8m4:
    case RISCV::BI__builtin_riscv_vmv_v_i_u8m4:
	ID = Intrinsic::riscv_vmv_v_i_8m4;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i8m8:
    case RISCV::BI__builtin_riscv_vmv_v_i_u8m8:
	ID = Intrinsic::riscv_vmv_v_i_8m8;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i16m1:
    case RISCV::BI__builtin_riscv_vmv_v_i_u16m1:
	ID = Intrinsic::riscv_vmv_v_i_16m1;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i16m2:
    case RISCV::BI__builtin_riscv_vmv_v_i_u16m2:
	ID = Intrinsic::riscv_vmv_v_i_16m2;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i16m4:
    case RISCV::BI__builtin_riscv_vmv_v_i_u16m4:
	ID = Intrinsic::riscv_vmv_v_i_16m4;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i16m8:
    case RISCV::BI__builtin_riscv_vmv_v_i_u16m8:
	ID = Intrinsic::riscv_vmv_v_i_16m8;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i32m1:
    case RISCV::BI__builtin_riscv_vmv_v_i_u32m1:
	ID = Intrinsic::riscv_vmv_v_i_32m1;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i32m2:
    case RISCV::BI__builtin_riscv_vmv_v_i_u32m2:
	ID = Intrinsic::riscv_vmv_v_i_32m2;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i32m4:
    case RISCV::BI__builtin_riscv_vmv_v_i_u32m4:
	ID = Intrinsic::riscv_vmv_v_i_32m4;
	break;
    case RISCV::BI__builtin_riscv_vmv_v_i_i32m8:
    case RISCV::BI__builtin_riscv_vmv_v_i_u32m8:
	ID = Intrinsic::riscv_vmv_v_i_32m8;
	break;

	//Vector Single-Width Saturating Add and Subtract Functions 
    case RISCV::BI__builtin_riscv_vsaddu_vv_u8m1:
	ID = Intrinsic::riscv_vsaddu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u8m2:
	ID = Intrinsic::riscv_vsaddu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u8m4:
	ID = Intrinsic::riscv_vsaddu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u8m8:
	ID = Intrinsic::riscv_vsaddu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u16m1:
	ID = Intrinsic::riscv_vsaddu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u16m2:
	ID = Intrinsic::riscv_vsaddu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u16m4:
	ID = Intrinsic::riscv_vsaddu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u16m8:
	ID = Intrinsic::riscv_vsaddu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u32m1:
	ID = Intrinsic::riscv_vsaddu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u32m2:
	ID = Intrinsic::riscv_vsaddu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u32m4:
	ID = Intrinsic::riscv_vsaddu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u32m8:
	ID = Intrinsic::riscv_vsaddu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u8m1:
	ID = Intrinsic::riscv_vsaddu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u8m2:
	ID = Intrinsic::riscv_vsaddu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u8m4:
	ID = Intrinsic::riscv_vsaddu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u8m8:
	ID = Intrinsic::riscv_vsaddu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u16m1:
	ID = Intrinsic::riscv_vsaddu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u16m2:
	ID = Intrinsic::riscv_vsaddu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u16m4:
	ID = Intrinsic::riscv_vsaddu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u16m8:
	ID = Intrinsic::riscv_vsaddu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u32m1:
	ID = Intrinsic::riscv_vsaddu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u32m2:
	ID = Intrinsic::riscv_vsaddu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u32m4:
	ID = Intrinsic::riscv_vsaddu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u32m8:
	ID = Intrinsic::riscv_vsaddu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u8m1:
	ID = Intrinsic::riscv_vsaddu_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u8m2:
	ID = Intrinsic::riscv_vsaddu_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u8m4:
	ID = Intrinsic::riscv_vsaddu_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u8m8:
	ID = Intrinsic::riscv_vsaddu_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u16m1:
	ID = Intrinsic::riscv_vsaddu_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u16m2:
	ID = Intrinsic::riscv_vsaddu_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u16m4:
	ID = Intrinsic::riscv_vsaddu_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u16m8:
	ID = Intrinsic::riscv_vsaddu_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u32m1:
	ID = Intrinsic::riscv_vsaddu_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u32m2:
	ID = Intrinsic::riscv_vsaddu_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u32m4:
	ID = Intrinsic::riscv_vsaddu_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u32m8:
	ID = Intrinsic::riscv_vsaddu_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i8m1:
	ID = Intrinsic::riscv_vsadd_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i8m2:
	ID = Intrinsic::riscv_vsadd_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i8m4:
	ID = Intrinsic::riscv_vsadd_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i8m8:
	ID = Intrinsic::riscv_vsadd_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i16m1:
	ID = Intrinsic::riscv_vsadd_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i16m2:
	ID = Intrinsic::riscv_vsadd_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i16m4:
	ID = Intrinsic::riscv_vsadd_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i16m8:
	ID = Intrinsic::riscv_vsadd_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i32m1:
	ID = Intrinsic::riscv_vsadd_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i32m2:
	ID = Intrinsic::riscv_vsadd_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i32m4:
	ID = Intrinsic::riscv_vsadd_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i32m8:
	ID = Intrinsic::riscv_vsadd_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i8m1:
	ID = Intrinsic::riscv_vsadd_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i8m2:
	ID = Intrinsic::riscv_vsadd_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i8m4:
	ID = Intrinsic::riscv_vsadd_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i8m8:
	ID = Intrinsic::riscv_vsadd_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i16m1:
	ID = Intrinsic::riscv_vsadd_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i16m2:
	ID = Intrinsic::riscv_vsadd_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i16m4:
	ID = Intrinsic::riscv_vsadd_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i16m8:
	ID = Intrinsic::riscv_vsadd_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i32m1:
	ID = Intrinsic::riscv_vsadd_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i32m2:
	ID = Intrinsic::riscv_vsadd_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i32m4:
	ID = Intrinsic::riscv_vsadd_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i32m8:
	ID = Intrinsic::riscv_vsadd_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i8m1:
	ID = Intrinsic::riscv_vsadd_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i8m2:
	ID = Intrinsic::riscv_vsadd_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i8m4:
	ID = Intrinsic::riscv_vsadd_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i8m8:
	ID = Intrinsic::riscv_vsadd_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i16m1:
	ID = Intrinsic::riscv_vsadd_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i16m2:
	ID = Intrinsic::riscv_vsadd_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i16m4:
	ID = Intrinsic::riscv_vsadd_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i16m8:
	ID = Intrinsic::riscv_vsadd_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i32m1:
	ID = Intrinsic::riscv_vsadd_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i32m2:
	ID = Intrinsic::riscv_vsadd_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i32m4:
	ID = Intrinsic::riscv_vsadd_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i32m8:
	ID = Intrinsic::riscv_vsadd_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u8m1:
	ID = Intrinsic::riscv_vssubu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u8m2:
	ID = Intrinsic::riscv_vssubu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u8m4:
	ID = Intrinsic::riscv_vssubu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u8m8:
	ID = Intrinsic::riscv_vssubu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u16m1:
	ID = Intrinsic::riscv_vssubu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u16m2:
	ID = Intrinsic::riscv_vssubu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u16m4:
	ID = Intrinsic::riscv_vssubu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u16m8:
	ID = Intrinsic::riscv_vssubu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u32m1:
	ID = Intrinsic::riscv_vssubu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u32m2:
	ID = Intrinsic::riscv_vssubu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u32m4:
	ID = Intrinsic::riscv_vssubu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u32m8:
	ID = Intrinsic::riscv_vssubu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u8m1:
	ID = Intrinsic::riscv_vssubu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u8m2:
	ID = Intrinsic::riscv_vssubu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u8m4:
	ID = Intrinsic::riscv_vssubu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u8m8:
	ID = Intrinsic::riscv_vssubu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u16m1:
	ID = Intrinsic::riscv_vssubu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u16m2:
	ID = Intrinsic::riscv_vssubu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u16m4:
	ID = Intrinsic::riscv_vssubu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u16m8:
	ID = Intrinsic::riscv_vssubu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u32m1:
	ID = Intrinsic::riscv_vssubu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u32m2:
	ID = Intrinsic::riscv_vssubu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u32m4:
	ID = Intrinsic::riscv_vssubu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u32m8:
	ID = Intrinsic::riscv_vssubu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i8m1:
	ID = Intrinsic::riscv_vssub_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i8m2:
	ID = Intrinsic::riscv_vssub_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i8m4:
	ID = Intrinsic::riscv_vssub_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i8m8:
	ID = Intrinsic::riscv_vssub_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i16m1:
	ID = Intrinsic::riscv_vssub_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i16m2:
	ID = Intrinsic::riscv_vssub_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i16m4:
	ID = Intrinsic::riscv_vssub_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i16m8:
	ID = Intrinsic::riscv_vssub_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i32m1:
	ID = Intrinsic::riscv_vssub_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i32m2:
	ID = Intrinsic::riscv_vssub_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i32m4:
	ID = Intrinsic::riscv_vssub_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i32m8:
	ID = Intrinsic::riscv_vssub_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i8m1:
	ID = Intrinsic::riscv_vssub_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i8m2:
	ID = Intrinsic::riscv_vssub_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i8m4:
	ID = Intrinsic::riscv_vssub_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i8m8:
	ID = Intrinsic::riscv_vssub_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i16m1:
	ID = Intrinsic::riscv_vssub_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i16m2:
	ID = Intrinsic::riscv_vssub_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i16m4:
	ID = Intrinsic::riscv_vssub_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i16m8:
	ID = Intrinsic::riscv_vssub_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i32m1:
	ID = Intrinsic::riscv_vssub_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i32m2:
	ID = Intrinsic::riscv_vssub_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i32m4:
	ID = Intrinsic::riscv_vssub_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i32m8:
	ID = Intrinsic::riscv_vssub_vx_32m8;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vsaddu_vv_u8m1_m:
	ID = Intrinsic::riscv_vsaddu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u8m2_m:
	ID = Intrinsic::riscv_vsaddu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u8m4_m:
	ID = Intrinsic::riscv_vsaddu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u8m8_m:
	ID = Intrinsic::riscv_vsaddu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u16m1_m:
	ID = Intrinsic::riscv_vsaddu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u16m2_m:
	ID = Intrinsic::riscv_vsaddu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u16m4_m:
	ID = Intrinsic::riscv_vsaddu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u16m8_m:
	ID = Intrinsic::riscv_vsaddu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u32m1_m:
	ID = Intrinsic::riscv_vsaddu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u32m2_m:
	ID = Intrinsic::riscv_vsaddu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u32m4_m:
	ID = Intrinsic::riscv_vsaddu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vv_u32m8_m:
	ID = Intrinsic::riscv_vsaddu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u8m1_m:
	ID = Intrinsic::riscv_vsaddu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u8m2_m:
	ID = Intrinsic::riscv_vsaddu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u8m4_m:
	ID = Intrinsic::riscv_vsaddu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u8m8_m:
	ID = Intrinsic::riscv_vsaddu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u16m1_m:
	ID = Intrinsic::riscv_vsaddu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u16m2_m:
	ID = Intrinsic::riscv_vsaddu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u16m4_m:
	ID = Intrinsic::riscv_vsaddu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u16m8_m:
	ID = Intrinsic::riscv_vsaddu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u32m1_m:
	ID = Intrinsic::riscv_vsaddu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u32m2_m:
	ID = Intrinsic::riscv_vsaddu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u32m4_m:
	ID = Intrinsic::riscv_vsaddu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vx_u32m8_m:
	ID = Intrinsic::riscv_vsaddu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u8m1_m:
	ID = Intrinsic::riscv_vsaddu_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u8m2_m:
	ID = Intrinsic::riscv_vsaddu_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u8m4_m:
	ID = Intrinsic::riscv_vsaddu_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u8m8_m:
	ID = Intrinsic::riscv_vsaddu_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u16m1_m:
	ID = Intrinsic::riscv_vsaddu_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u16m2_m:
	ID = Intrinsic::riscv_vsaddu_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u16m4_m:
	ID = Intrinsic::riscv_vsaddu_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u16m8_m:
	ID = Intrinsic::riscv_vsaddu_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u32m1_m:
	ID = Intrinsic::riscv_vsaddu_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u32m2_m:
	ID = Intrinsic::riscv_vsaddu_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u32m4_m:
	ID = Intrinsic::riscv_vsaddu_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsaddu_vi_u32m8_m:
	ID = Intrinsic::riscv_vsaddu_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i8m1_m:
	ID = Intrinsic::riscv_vsadd_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i8m2_m:
	ID = Intrinsic::riscv_vsadd_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i8m4_m:
	ID = Intrinsic::riscv_vsadd_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i8m8_m:
	ID = Intrinsic::riscv_vsadd_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i16m1_m:
	ID = Intrinsic::riscv_vsadd_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i16m2_m:
	ID = Intrinsic::riscv_vsadd_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i16m4_m:
	ID = Intrinsic::riscv_vsadd_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i16m8_m:
	ID = Intrinsic::riscv_vsadd_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i32m1_m:
	ID = Intrinsic::riscv_vsadd_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i32m2_m:
	ID = Intrinsic::riscv_vsadd_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i32m4_m:
	ID = Intrinsic::riscv_vsadd_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vv_i32m8_m:
	ID = Intrinsic::riscv_vsadd_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i8m1_m:
	ID = Intrinsic::riscv_vsadd_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i8m2_m:
	ID = Intrinsic::riscv_vsadd_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i8m4_m:
	ID = Intrinsic::riscv_vsadd_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i8m8_m:
	ID = Intrinsic::riscv_vsadd_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i16m1_m:
	ID = Intrinsic::riscv_vsadd_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i16m2_m:
	ID = Intrinsic::riscv_vsadd_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i16m4_m:
	ID = Intrinsic::riscv_vsadd_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i16m8_m:
	ID = Intrinsic::riscv_vsadd_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i32m1_m:
	ID = Intrinsic::riscv_vsadd_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i32m2_m:
	ID = Intrinsic::riscv_vsadd_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i32m4_m:
	ID = Intrinsic::riscv_vsadd_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vx_i32m8_m:
	ID = Intrinsic::riscv_vsadd_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i8m1_m:
	ID = Intrinsic::riscv_vsadd_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i8m2_m:
	ID = Intrinsic::riscv_vsadd_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i8m4_m:
	ID = Intrinsic::riscv_vsadd_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i8m8_m:
	ID = Intrinsic::riscv_vsadd_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i16m1_m:
	ID = Intrinsic::riscv_vsadd_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i16m2_m:
	ID = Intrinsic::riscv_vsadd_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i16m4_m:
	ID = Intrinsic::riscv_vsadd_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i16m8_m:
	ID = Intrinsic::riscv_vsadd_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i32m1_m:
	ID = Intrinsic::riscv_vsadd_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i32m2_m:
	ID = Intrinsic::riscv_vsadd_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i32m4_m:
	ID = Intrinsic::riscv_vsadd_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsadd_vi_i32m8_m:
	ID = Intrinsic::riscv_vsadd_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u8m1_m:
	ID = Intrinsic::riscv_vssubu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u8m2_m:
	ID = Intrinsic::riscv_vssubu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u8m4_m:
	ID = Intrinsic::riscv_vssubu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u8m8_m:
	ID = Intrinsic::riscv_vssubu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u16m1_m:
	ID = Intrinsic::riscv_vssubu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u16m2_m:
	ID = Intrinsic::riscv_vssubu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u16m4_m:
	ID = Intrinsic::riscv_vssubu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u16m8_m:
	ID = Intrinsic::riscv_vssubu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u32m1_m:
	ID = Intrinsic::riscv_vssubu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u32m2_m:
	ID = Intrinsic::riscv_vssubu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u32m4_m:
	ID = Intrinsic::riscv_vssubu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vv_u32m8_m:
	ID = Intrinsic::riscv_vssubu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u8m1_m:
	ID = Intrinsic::riscv_vssubu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u8m2_m:
	ID = Intrinsic::riscv_vssubu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u8m4_m:
	ID = Intrinsic::riscv_vssubu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u8m8_m:
	ID = Intrinsic::riscv_vssubu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u16m1_m:
	ID = Intrinsic::riscv_vssubu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u16m2_m:
	ID = Intrinsic::riscv_vssubu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u16m4_m:
	ID = Intrinsic::riscv_vssubu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u16m8_m:
	ID = Intrinsic::riscv_vssubu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u32m1_m:
	ID = Intrinsic::riscv_vssubu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u32m2_m:
	ID = Intrinsic::riscv_vssubu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u32m4_m:
	ID = Intrinsic::riscv_vssubu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssubu_vx_u32m8_m:
	ID = Intrinsic::riscv_vssubu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i8m1_m:
	ID = Intrinsic::riscv_vssub_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i8m2_m:
	ID = Intrinsic::riscv_vssub_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i8m4_m:
	ID = Intrinsic::riscv_vssub_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i8m8_m:
	ID = Intrinsic::riscv_vssub_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i16m1_m:
	ID = Intrinsic::riscv_vssub_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i16m2_m:
	ID = Intrinsic::riscv_vssub_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i16m4_m:
	ID = Intrinsic::riscv_vssub_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i16m8_m:
	ID = Intrinsic::riscv_vssub_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i32m1_m:
	ID = Intrinsic::riscv_vssub_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i32m2_m:
	ID = Intrinsic::riscv_vssub_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i32m4_m:
	ID = Intrinsic::riscv_vssub_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vv_i32m8_m:
	ID = Intrinsic::riscv_vssub_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i8m1_m:
	ID = Intrinsic::riscv_vssub_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i8m2_m:
	ID = Intrinsic::riscv_vssub_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i8m4_m:
	ID = Intrinsic::riscv_vssub_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i8m8_m:
	ID = Intrinsic::riscv_vssub_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i16m1_m:
	ID = Intrinsic::riscv_vssub_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i16m2_m:
	ID = Intrinsic::riscv_vssub_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i16m4_m:
	ID = Intrinsic::riscv_vssub_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i16m8_m:
	ID = Intrinsic::riscv_vssub_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i32m1_m:
	ID = Intrinsic::riscv_vssub_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i32m2_m:
	ID = Intrinsic::riscv_vssub_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i32m4_m:
	ID = Intrinsic::riscv_vssub_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssub_vx_i32m8_m:
	ID = Intrinsic::riscv_vssub_vx_32m8_m;
	break;

	//Vector Single-Width Averaging Add and Subtract Functions
    case RISCV::BI__builtin_riscv_vaaddu_vv_u8m1:
	ID = Intrinsic::riscv_vaaddu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u8m2:
	ID = Intrinsic::riscv_vaaddu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u8m4:
	ID = Intrinsic::riscv_vaaddu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u8m8:
	ID = Intrinsic::riscv_vaaddu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u16m1:
	ID = Intrinsic::riscv_vaaddu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u16m2:
	ID = Intrinsic::riscv_vaaddu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u16m4:
	ID = Intrinsic::riscv_vaaddu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u16m8:
	ID = Intrinsic::riscv_vaaddu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u32m1:
	ID = Intrinsic::riscv_vaaddu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u32m2:
	ID = Intrinsic::riscv_vaaddu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u32m4:
	ID = Intrinsic::riscv_vaaddu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u32m8:
	ID = Intrinsic::riscv_vaaddu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u8m1:
	ID = Intrinsic::riscv_vaaddu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u8m2:
	ID = Intrinsic::riscv_vaaddu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u8m4:
	ID = Intrinsic::riscv_vaaddu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u8m8:
	ID = Intrinsic::riscv_vaaddu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u16m1:
	ID = Intrinsic::riscv_vaaddu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u16m2:
	ID = Intrinsic::riscv_vaaddu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u16m4:
	ID = Intrinsic::riscv_vaaddu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u16m8:
	ID = Intrinsic::riscv_vaaddu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u32m1:
	ID = Intrinsic::riscv_vaaddu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u32m2:
	ID = Intrinsic::riscv_vaaddu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u32m4:
	ID = Intrinsic::riscv_vaaddu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u32m8:
	ID = Intrinsic::riscv_vaaddu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i8m1:
	ID = Intrinsic::riscv_vaadd_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i8m2:
	ID = Intrinsic::riscv_vaadd_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i8m4:
	ID = Intrinsic::riscv_vaadd_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i8m8:
	ID = Intrinsic::riscv_vaadd_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i16m1:
	ID = Intrinsic::riscv_vaadd_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i16m2:
	ID = Intrinsic::riscv_vaadd_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i16m4:
	ID = Intrinsic::riscv_vaadd_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i16m8:
	ID = Intrinsic::riscv_vaadd_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i32m1:
	ID = Intrinsic::riscv_vaadd_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i32m2:
	ID = Intrinsic::riscv_vaadd_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i32m4:
	ID = Intrinsic::riscv_vaadd_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i32m8:
	ID = Intrinsic::riscv_vaadd_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i8m1:
	ID = Intrinsic::riscv_vaadd_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i8m2:
	ID = Intrinsic::riscv_vaadd_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i8m4:
	ID = Intrinsic::riscv_vaadd_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i8m8:
	ID = Intrinsic::riscv_vaadd_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i16m1:
	ID = Intrinsic::riscv_vaadd_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i16m2:
	ID = Intrinsic::riscv_vaadd_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i16m4:
	ID = Intrinsic::riscv_vaadd_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i16m8:
	ID = Intrinsic::riscv_vaadd_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i32m1:
	ID = Intrinsic::riscv_vaadd_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i32m2:
	ID = Intrinsic::riscv_vaadd_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i32m4:
	ID = Intrinsic::riscv_vaadd_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i32m8:
	ID = Intrinsic::riscv_vaadd_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u8m1:
	ID = Intrinsic::riscv_vasubu_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u8m2:
	ID = Intrinsic::riscv_vasubu_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u8m4:
	ID = Intrinsic::riscv_vasubu_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u8m8:
	ID = Intrinsic::riscv_vasubu_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u16m1:
	ID = Intrinsic::riscv_vasubu_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u16m2:
	ID = Intrinsic::riscv_vasubu_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u16m4:
	ID = Intrinsic::riscv_vasubu_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u16m8:
	ID = Intrinsic::riscv_vasubu_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u32m1:
	ID = Intrinsic::riscv_vasubu_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u32m2:
	ID = Intrinsic::riscv_vasubu_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u32m4:
	ID = Intrinsic::riscv_vasubu_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u32m8:
	ID = Intrinsic::riscv_vasubu_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u8m1:
	ID = Intrinsic::riscv_vasubu_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u8m2:
	ID = Intrinsic::riscv_vasubu_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u8m4:
	ID = Intrinsic::riscv_vasubu_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u8m8:
	ID = Intrinsic::riscv_vasubu_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u16m1:
	ID = Intrinsic::riscv_vasubu_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u16m2:
	ID = Intrinsic::riscv_vasubu_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u16m4:
	ID = Intrinsic::riscv_vasubu_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u16m8:
	ID = Intrinsic::riscv_vasubu_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u32m1:
	ID = Intrinsic::riscv_vasubu_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u32m2:
	ID = Intrinsic::riscv_vasubu_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u32m4:
	ID = Intrinsic::riscv_vasubu_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u32m8:
	ID = Intrinsic::riscv_vasubu_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i8m1:
	ID = Intrinsic::riscv_vasub_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i8m2:
	ID = Intrinsic::riscv_vasub_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i8m4:
	ID = Intrinsic::riscv_vasub_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i8m8:
	ID = Intrinsic::riscv_vasub_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i16m1:
	ID = Intrinsic::riscv_vasub_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i16m2:
	ID = Intrinsic::riscv_vasub_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i16m4:
	ID = Intrinsic::riscv_vasub_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i16m8:
	ID = Intrinsic::riscv_vasub_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i32m1:
	ID = Intrinsic::riscv_vasub_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i32m2:
	ID = Intrinsic::riscv_vasub_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i32m4:
	ID = Intrinsic::riscv_vasub_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i32m8:
	ID = Intrinsic::riscv_vasub_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i8m1:
	ID = Intrinsic::riscv_vasub_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i8m2:
	ID = Intrinsic::riscv_vasub_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i8m4:
	ID = Intrinsic::riscv_vasub_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i8m8:
	ID = Intrinsic::riscv_vasub_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i16m1:
	ID = Intrinsic::riscv_vasub_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i16m2:
	ID = Intrinsic::riscv_vasub_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i16m4:
	ID = Intrinsic::riscv_vasub_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i16m8:
	ID = Intrinsic::riscv_vasub_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i32m1:
	ID = Intrinsic::riscv_vasub_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i32m2:
	ID = Intrinsic::riscv_vasub_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i32m4:
	ID = Intrinsic::riscv_vasub_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i32m8:
	ID = Intrinsic::riscv_vasub_vx_32m8;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vaaddu_vv_u8m1_m:
	ID = Intrinsic::riscv_vaaddu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u8m2_m:
	ID = Intrinsic::riscv_vaaddu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u8m4_m:
	ID = Intrinsic::riscv_vaaddu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u8m8_m:
	ID = Intrinsic::riscv_vaaddu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u16m1_m:
	ID = Intrinsic::riscv_vaaddu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u16m2_m:
	ID = Intrinsic::riscv_vaaddu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u16m4_m:
	ID = Intrinsic::riscv_vaaddu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u16m8_m:
	ID = Intrinsic::riscv_vaaddu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u32m1_m:
	ID = Intrinsic::riscv_vaaddu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u32m2_m:
	ID = Intrinsic::riscv_vaaddu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u32m4_m:
	ID = Intrinsic::riscv_vaaddu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vv_u32m8_m:
	ID = Intrinsic::riscv_vaaddu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u8m1_m:
	ID = Intrinsic::riscv_vaaddu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u8m2_m:
	ID = Intrinsic::riscv_vaaddu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u8m4_m:
	ID = Intrinsic::riscv_vaaddu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u8m8_m:
	ID = Intrinsic::riscv_vaaddu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u16m1_m:
	ID = Intrinsic::riscv_vaaddu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u16m2_m:
	ID = Intrinsic::riscv_vaaddu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u16m4_m:
	ID = Intrinsic::riscv_vaaddu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u16m8_m:
	ID = Intrinsic::riscv_vaaddu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u32m1_m:
	ID = Intrinsic::riscv_vaaddu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u32m2_m:
	ID = Intrinsic::riscv_vaaddu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u32m4_m:
	ID = Intrinsic::riscv_vaaddu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vaaddu_vx_u32m8_m:
	ID = Intrinsic::riscv_vaaddu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i8m1_m:
	ID = Intrinsic::riscv_vaadd_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i8m2_m:
	ID = Intrinsic::riscv_vaadd_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i8m4_m:
	ID = Intrinsic::riscv_vaadd_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i8m8_m:
	ID = Intrinsic::riscv_vaadd_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i16m1_m:
	ID = Intrinsic::riscv_vaadd_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i16m2_m:
	ID = Intrinsic::riscv_vaadd_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i16m4_m:
	ID = Intrinsic::riscv_vaadd_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i16m8_m:
	ID = Intrinsic::riscv_vaadd_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i32m1_m:
	ID = Intrinsic::riscv_vaadd_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i32m2_m:
	ID = Intrinsic::riscv_vaadd_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i32m4_m:
	ID = Intrinsic::riscv_vaadd_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vv_i32m8_m:
	ID = Intrinsic::riscv_vaadd_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i8m1_m:
	ID = Intrinsic::riscv_vaadd_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i8m2_m:
	ID = Intrinsic::riscv_vaadd_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i8m4_m:
	ID = Intrinsic::riscv_vaadd_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i8m8_m:
	ID = Intrinsic::riscv_vaadd_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i16m1_m:
	ID = Intrinsic::riscv_vaadd_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i16m2_m:
	ID = Intrinsic::riscv_vaadd_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i16m4_m:
	ID = Intrinsic::riscv_vaadd_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i16m8_m:
	ID = Intrinsic::riscv_vaadd_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i32m1_m:
	ID = Intrinsic::riscv_vaadd_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i32m2_m:
	ID = Intrinsic::riscv_vaadd_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i32m4_m:
	ID = Intrinsic::riscv_vaadd_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vaadd_vx_i32m8_m:
	ID = Intrinsic::riscv_vaadd_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u8m1_m:
	ID = Intrinsic::riscv_vasubu_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u8m2_m:
	ID = Intrinsic::riscv_vasubu_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u8m4_m:
	ID = Intrinsic::riscv_vasubu_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u8m8_m:
	ID = Intrinsic::riscv_vasubu_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u16m1_m:
	ID = Intrinsic::riscv_vasubu_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u16m2_m:
	ID = Intrinsic::riscv_vasubu_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u16m4_m:
	ID = Intrinsic::riscv_vasubu_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u16m8_m:
	ID = Intrinsic::riscv_vasubu_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u32m1_m:
	ID = Intrinsic::riscv_vasubu_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u32m2_m:
	ID = Intrinsic::riscv_vasubu_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u32m4_m:
	ID = Intrinsic::riscv_vasubu_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vv_u32m8_m:
	ID = Intrinsic::riscv_vasubu_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u8m1_m:
	ID = Intrinsic::riscv_vasubu_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u8m2_m:
	ID = Intrinsic::riscv_vasubu_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u8m4_m:
	ID = Intrinsic::riscv_vasubu_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u8m8_m:
	ID = Intrinsic::riscv_vasubu_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u16m1_m:
	ID = Intrinsic::riscv_vasubu_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u16m2_m:
	ID = Intrinsic::riscv_vasubu_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u16m4_m:
	ID = Intrinsic::riscv_vasubu_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u16m8_m:
	ID = Intrinsic::riscv_vasubu_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u32m1_m:
	ID = Intrinsic::riscv_vasubu_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u32m2_m:
	ID = Intrinsic::riscv_vasubu_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u32m4_m:
	ID = Intrinsic::riscv_vasubu_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vasubu_vx_u32m8_m:
	ID = Intrinsic::riscv_vasubu_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i8m1_m:
	ID = Intrinsic::riscv_vasub_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i8m2_m:
	ID = Intrinsic::riscv_vasub_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i8m4_m:
	ID = Intrinsic::riscv_vasub_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i8m8_m:
	ID = Intrinsic::riscv_vasub_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i16m1_m:
	ID = Intrinsic::riscv_vasub_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i16m2_m:
	ID = Intrinsic::riscv_vasub_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i16m4_m:
	ID = Intrinsic::riscv_vasub_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i16m8_m:
	ID = Intrinsic::riscv_vasub_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i32m1_m:
	ID = Intrinsic::riscv_vasub_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i32m2_m:
	ID = Intrinsic::riscv_vasub_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i32m4_m:
	ID = Intrinsic::riscv_vasub_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vv_i32m8_m:
	ID = Intrinsic::riscv_vasub_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i8m1_m:
	ID = Intrinsic::riscv_vasub_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i8m2_m:
	ID = Intrinsic::riscv_vasub_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i8m4_m:
	ID = Intrinsic::riscv_vasub_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i8m8_m:
	ID = Intrinsic::riscv_vasub_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i16m1_m:
	ID = Intrinsic::riscv_vasub_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i16m2_m:
	ID = Intrinsic::riscv_vasub_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i16m4_m:
	ID = Intrinsic::riscv_vasub_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i16m8_m:
	ID = Intrinsic::riscv_vasub_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i32m1_m:
	ID = Intrinsic::riscv_vasub_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i32m2_m:
	ID = Intrinsic::riscv_vasub_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i32m4_m:
	ID = Intrinsic::riscv_vasub_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vasub_vx_i32m8_m:
	ID = Intrinsic::riscv_vasub_vx_32m8_m;
	break;

	//Vector Single-Width Fractional Multiply with Rounding and Saturation Functions
    case RISCV::BI__builtin_riscv_vsmul_vv_i8m1:
	ID = Intrinsic::riscv_vsmul_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i8m2:
	ID = Intrinsic::riscv_vsmul_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i8m4:
	ID = Intrinsic::riscv_vsmul_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i8m8:
	ID = Intrinsic::riscv_vsmul_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i16m1:
	ID = Intrinsic::riscv_vsmul_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i16m2:
	ID = Intrinsic::riscv_vsmul_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i16m4:
	ID = Intrinsic::riscv_vsmul_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i16m8:
	ID = Intrinsic::riscv_vsmul_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i32m1:
	ID = Intrinsic::riscv_vsmul_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i32m2:
	ID = Intrinsic::riscv_vsmul_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i32m4:
	ID = Intrinsic::riscv_vsmul_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i32m8:
	ID = Intrinsic::riscv_vsmul_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i8m1:
	ID = Intrinsic::riscv_vsmul_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i8m2:
	ID = Intrinsic::riscv_vsmul_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i8m4:
	ID = Intrinsic::riscv_vsmul_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i8m8:
	ID = Intrinsic::riscv_vsmul_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i16m1:
	ID = Intrinsic::riscv_vsmul_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i16m2:
	ID = Intrinsic::riscv_vsmul_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i16m4:
	ID = Intrinsic::riscv_vsmul_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i16m8:
	ID = Intrinsic::riscv_vsmul_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i32m1:
	ID = Intrinsic::riscv_vsmul_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i32m2:
	ID = Intrinsic::riscv_vsmul_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i32m4:
	ID = Intrinsic::riscv_vsmul_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i32m8:
	ID = Intrinsic::riscv_vsmul_vx_32m8;
	break;
	//masked functions 
    case RISCV::BI__builtin_riscv_vsmul_vv_i8m1_m:
	ID = Intrinsic::riscv_vsmul_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i8m2_m:
	ID = Intrinsic::riscv_vsmul_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i8m4_m:
	ID = Intrinsic::riscv_vsmul_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i8m8_m:
	ID = Intrinsic::riscv_vsmul_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i16m1_m:
	ID = Intrinsic::riscv_vsmul_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i16m2_m:
	ID = Intrinsic::riscv_vsmul_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i16m4_m:
	ID = Intrinsic::riscv_vsmul_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i16m8_m:
	ID = Intrinsic::riscv_vsmul_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i32m1_m:
	ID = Intrinsic::riscv_vsmul_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i32m2_m:
	ID = Intrinsic::riscv_vsmul_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i32m4_m:
	ID = Intrinsic::riscv_vsmul_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vv_i32m8_m:
	ID = Intrinsic::riscv_vsmul_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i8m1_m:
	ID = Intrinsic::riscv_vsmul_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i8m2_m:
	ID = Intrinsic::riscv_vsmul_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i8m4_m:
	ID = Intrinsic::riscv_vsmul_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i8m8_m:
	ID = Intrinsic::riscv_vsmul_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i16m1_m:
	ID = Intrinsic::riscv_vsmul_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i16m2_m:
	ID = Intrinsic::riscv_vsmul_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i16m4_m:
	ID = Intrinsic::riscv_vsmul_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i16m8_m:
	ID = Intrinsic::riscv_vsmul_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i32m1_m:
	ID = Intrinsic::riscv_vsmul_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i32m2_m:
	ID = Intrinsic::riscv_vsmul_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i32m4_m:
	ID = Intrinsic::riscv_vsmul_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsmul_vx_i32m8_m:
	ID = Intrinsic::riscv_vsmul_vx_32m8_m;
	break;

	//Vector Single-Width Scaling Shift Functions
    case RISCV::BI__builtin_riscv_vssrl_vv_u8m1:
	ID = Intrinsic::riscv_vssrl_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u8m2:
	ID = Intrinsic::riscv_vssrl_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u8m4:
	ID = Intrinsic::riscv_vssrl_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u8m8:
	ID = Intrinsic::riscv_vssrl_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u16m1:
	ID = Intrinsic::riscv_vssrl_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u16m2:
	ID = Intrinsic::riscv_vssrl_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u16m4:
	ID = Intrinsic::riscv_vssrl_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u16m8:
	ID = Intrinsic::riscv_vssrl_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u32m1:
	ID = Intrinsic::riscv_vssrl_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u32m2:
	ID = Intrinsic::riscv_vssrl_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u32m4:
	ID = Intrinsic::riscv_vssrl_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u32m8:
	ID = Intrinsic::riscv_vssrl_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u8m1:
	ID = Intrinsic::riscv_vssrl_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u8m2:
	ID = Intrinsic::riscv_vssrl_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u8m4:
	ID = Intrinsic::riscv_vssrl_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u8m8:
	ID = Intrinsic::riscv_vssrl_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u16m1:
	ID = Intrinsic::riscv_vssrl_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u16m2:
	ID = Intrinsic::riscv_vssrl_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u16m4:
	ID = Intrinsic::riscv_vssrl_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u16m8:
	ID = Intrinsic::riscv_vssrl_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u32m1:
	ID = Intrinsic::riscv_vssrl_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u32m2:
	ID = Intrinsic::riscv_vssrl_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u32m4:
	ID = Intrinsic::riscv_vssrl_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u32m8:
	ID = Intrinsic::riscv_vssrl_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u8m1:
	ID = Intrinsic::riscv_vssrl_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u8m2:
	ID = Intrinsic::riscv_vssrl_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u8m4:
	ID = Intrinsic::riscv_vssrl_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u8m8:
	ID = Intrinsic::riscv_vssrl_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u16m1:
	ID = Intrinsic::riscv_vssrl_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u16m2:
	ID = Intrinsic::riscv_vssrl_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u16m4:
	ID = Intrinsic::riscv_vssrl_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u16m8:
	ID = Intrinsic::riscv_vssrl_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u32m1:
	ID = Intrinsic::riscv_vssrl_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u32m2:
	ID = Intrinsic::riscv_vssrl_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u32m4:
	ID = Intrinsic::riscv_vssrl_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u32m8:
	ID = Intrinsic::riscv_vssrl_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i8m1:
	ID = Intrinsic::riscv_vssra_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i8m2:
	ID = Intrinsic::riscv_vssra_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i8m4:
	ID = Intrinsic::riscv_vssra_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i8m8:
	ID = Intrinsic::riscv_vssra_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i16m1:
	ID = Intrinsic::riscv_vssra_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i16m2:
	ID = Intrinsic::riscv_vssra_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i16m4:
	ID = Intrinsic::riscv_vssra_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i16m8:
	ID = Intrinsic::riscv_vssra_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i32m1:
	ID = Intrinsic::riscv_vssra_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i32m2:
	ID = Intrinsic::riscv_vssra_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i32m4:
	ID = Intrinsic::riscv_vssra_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i32m8:
	ID = Intrinsic::riscv_vssra_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i8m1:
	ID = Intrinsic::riscv_vssra_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i8m2:
	ID = Intrinsic::riscv_vssra_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i8m4:
	ID = Intrinsic::riscv_vssra_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i8m8:
	ID = Intrinsic::riscv_vssra_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i16m1:
	ID = Intrinsic::riscv_vssra_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i16m2:
	ID = Intrinsic::riscv_vssra_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i16m4:
	ID = Intrinsic::riscv_vssra_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i16m8:
	ID = Intrinsic::riscv_vssra_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i32m1:
	ID = Intrinsic::riscv_vssra_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i32m2:
	ID = Intrinsic::riscv_vssra_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i32m4:
	ID = Intrinsic::riscv_vssra_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i32m8:
	ID = Intrinsic::riscv_vssra_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i8m1:
	ID = Intrinsic::riscv_vssra_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i8m2:
	ID = Intrinsic::riscv_vssra_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i8m4:
	ID = Intrinsic::riscv_vssra_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i8m8:
	ID = Intrinsic::riscv_vssra_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i16m1:
	ID = Intrinsic::riscv_vssra_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i16m2:
	ID = Intrinsic::riscv_vssra_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i16m4:
	ID = Intrinsic::riscv_vssra_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i16m8:
	ID = Intrinsic::riscv_vssra_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i32m1:
	ID = Intrinsic::riscv_vssra_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i32m2:
	ID = Intrinsic::riscv_vssra_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i32m4:
	ID = Intrinsic::riscv_vssra_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i32m8:
	ID = Intrinsic::riscv_vssra_vi_32m8;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vssrl_vv_u8m1_m:
	ID = Intrinsic::riscv_vssrl_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u8m2_m:
	ID = Intrinsic::riscv_vssrl_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u8m4_m:
	ID = Intrinsic::riscv_vssrl_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u8m8_m:
	ID = Intrinsic::riscv_vssrl_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u16m1_m:
	ID = Intrinsic::riscv_vssrl_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u16m2_m:
	ID = Intrinsic::riscv_vssrl_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u16m4_m:
	ID = Intrinsic::riscv_vssrl_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u16m8_m:
	ID = Intrinsic::riscv_vssrl_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u32m1_m:
	ID = Intrinsic::riscv_vssrl_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u32m2_m:
	ID = Intrinsic::riscv_vssrl_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u32m4_m:
	ID = Intrinsic::riscv_vssrl_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vv_u32m8_m:
	ID = Intrinsic::riscv_vssrl_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u8m1_m:
	ID = Intrinsic::riscv_vssrl_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u8m2_m:
	ID = Intrinsic::riscv_vssrl_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u8m4_m:
	ID = Intrinsic::riscv_vssrl_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u8m8_m:
	ID = Intrinsic::riscv_vssrl_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u16m1_m:
	ID = Intrinsic::riscv_vssrl_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u16m2_m:
	ID = Intrinsic::riscv_vssrl_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u16m4_m:
	ID = Intrinsic::riscv_vssrl_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u16m8_m:
	ID = Intrinsic::riscv_vssrl_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u32m1_m:
	ID = Intrinsic::riscv_vssrl_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u32m2_m:
	ID = Intrinsic::riscv_vssrl_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u32m4_m:
	ID = Intrinsic::riscv_vssrl_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vx_u32m8_m:
	ID = Intrinsic::riscv_vssrl_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u8m1_m:
	ID = Intrinsic::riscv_vssrl_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u8m2_m:
	ID = Intrinsic::riscv_vssrl_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u8m4_m:
	ID = Intrinsic::riscv_vssrl_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u8m8_m:
	ID = Intrinsic::riscv_vssrl_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u16m1_m:
	ID = Intrinsic::riscv_vssrl_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u16m2_m:
	ID = Intrinsic::riscv_vssrl_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u16m4_m:
	ID = Intrinsic::riscv_vssrl_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u16m8_m:
	ID = Intrinsic::riscv_vssrl_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u32m1_m:
	ID = Intrinsic::riscv_vssrl_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u32m2_m:
	ID = Intrinsic::riscv_vssrl_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u32m4_m:
	ID = Intrinsic::riscv_vssrl_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssrl_vi_u32m8_m:
	ID = Intrinsic::riscv_vssrl_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i8m1_m:
	ID = Intrinsic::riscv_vssra_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i8m2_m:
	ID = Intrinsic::riscv_vssra_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i8m4_m:
	ID = Intrinsic::riscv_vssra_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i8m8_m:
	ID = Intrinsic::riscv_vssra_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i16m1_m:
	ID = Intrinsic::riscv_vssra_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i16m2_m:
	ID = Intrinsic::riscv_vssra_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i16m4_m:
	ID = Intrinsic::riscv_vssra_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i16m8_m:
	ID = Intrinsic::riscv_vssra_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i32m1_m:
	ID = Intrinsic::riscv_vssra_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i32m2_m:
	ID = Intrinsic::riscv_vssra_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i32m4_m:
	ID = Intrinsic::riscv_vssra_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vv_i32m8_m:
	ID = Intrinsic::riscv_vssra_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i8m1_m:
	ID = Intrinsic::riscv_vssra_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i8m2_m:
	ID = Intrinsic::riscv_vssra_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i8m4_m:
	ID = Intrinsic::riscv_vssra_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i8m8_m:
	ID = Intrinsic::riscv_vssra_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i16m1_m:
	ID = Intrinsic::riscv_vssra_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i16m2_m:
	ID = Intrinsic::riscv_vssra_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i16m4_m:
	ID = Intrinsic::riscv_vssra_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i16m8_m:
	ID = Intrinsic::riscv_vssra_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i32m1_m:
	ID = Intrinsic::riscv_vssra_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i32m2_m:
	ID = Intrinsic::riscv_vssra_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i32m4_m:
	ID = Intrinsic::riscv_vssra_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vx_i32m8_m:
	ID = Intrinsic::riscv_vssra_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i8m1_m:
	ID = Intrinsic::riscv_vssra_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i8m2_m:
	ID = Intrinsic::riscv_vssra_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i8m4_m:
	ID = Intrinsic::riscv_vssra_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i8m8_m:
	ID = Intrinsic::riscv_vssra_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i16m1_m:
	ID = Intrinsic::riscv_vssra_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i16m2_m:
	ID = Intrinsic::riscv_vssra_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i16m4_m:
	ID = Intrinsic::riscv_vssra_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i16m8_m:
	ID = Intrinsic::riscv_vssra_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i32m1_m:
	ID = Intrinsic::riscv_vssra_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i32m2_m:
	ID = Intrinsic::riscv_vssra_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i32m4_m:
	ID = Intrinsic::riscv_vssra_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vssra_vi_i32m8_m:
	ID = Intrinsic::riscv_vssra_vi_32m8_m;
	break;

	//Vector Narrowing Fixed-Point Clip Functions
    case RISCV::BI__builtin_riscv_vnclipu_wv_u8m1:
	ID = Intrinsic::riscv_vnclipu_wv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wv_u8m2:
	ID = Intrinsic::riscv_vnclipu_wv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wv_u8m4:
	ID = Intrinsic::riscv_vnclipu_wv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wv_u16m1:
	ID = Intrinsic::riscv_vnclipu_wv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wv_u16m2:
	ID = Intrinsic::riscv_vnclipu_wv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wv_u16m4:
	ID = Intrinsic::riscv_vnclipu_wv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u8m1:
	ID = Intrinsic::riscv_vnclipu_wx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u8m2:
	ID = Intrinsic::riscv_vnclipu_wx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u8m4:
	ID = Intrinsic::riscv_vnclipu_wx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u16m1:
	ID = Intrinsic::riscv_vnclipu_wx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u16m2:
	ID = Intrinsic::riscv_vnclipu_wx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u16m4:
	ID = Intrinsic::riscv_vnclipu_wx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u8m1:
	ID = Intrinsic::riscv_vnclipu_wi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u8m2:
	ID = Intrinsic::riscv_vnclipu_wi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u8m4:
	ID = Intrinsic::riscv_vnclipu_wi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u16m1:
	ID = Intrinsic::riscv_vnclipu_wi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u16m2:
	ID = Intrinsic::riscv_vnclipu_wi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u16m4:
	ID = Intrinsic::riscv_vnclipu_wi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i8m1:
	ID = Intrinsic::riscv_vnclip_wv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i8m2:
	ID = Intrinsic::riscv_vnclip_wv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i8m4:
	ID = Intrinsic::riscv_vnclip_wv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i16m1:
	ID = Intrinsic::riscv_vnclip_wv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i16m2:
	ID = Intrinsic::riscv_vnclip_wv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i16m4:
	ID = Intrinsic::riscv_vnclip_wv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i8m1:
	ID = Intrinsic::riscv_vnclip_wx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i8m2:
	ID = Intrinsic::riscv_vnclip_wx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i8m4:
	ID = Intrinsic::riscv_vnclip_wx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i16m1:
	ID = Intrinsic::riscv_vnclip_wx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i16m2:
	ID = Intrinsic::riscv_vnclip_wx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i16m4:
	ID = Intrinsic::riscv_vnclip_wx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i8m1:
	ID = Intrinsic::riscv_vnclip_wi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i8m2:
	ID = Intrinsic::riscv_vnclip_wi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i8m4:
	ID = Intrinsic::riscv_vnclip_wi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i16m1:
	ID = Intrinsic::riscv_vnclip_wi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i16m2:
	ID = Intrinsic::riscv_vnclip_wi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i16m4:
	ID = Intrinsic::riscv_vnclip_wi_16m4;
	break;
	//masked functions
    case RISCV::BI__builtin_riscv_vnclipu_wv_u8m1_m:
	ID = Intrinsic::riscv_vnclipu_wv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wv_u8m2_m:
	ID = Intrinsic::riscv_vnclipu_wv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wv_u8m4_m:
	ID = Intrinsic::riscv_vnclipu_wv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wv_u16m1_m:
	ID = Intrinsic::riscv_vnclipu_wv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wv_u16m2_m:
	ID = Intrinsic::riscv_vnclipu_wv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wv_u16m4_m:
	ID = Intrinsic::riscv_vnclipu_wv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u8m1_m:
	ID = Intrinsic::riscv_vnclipu_wx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u8m2_m:
	ID = Intrinsic::riscv_vnclipu_wx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u8m4_m:
	ID = Intrinsic::riscv_vnclipu_wx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u16m1_m:
	ID = Intrinsic::riscv_vnclipu_wx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u16m2_m:
	ID = Intrinsic::riscv_vnclipu_wx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wx_u16m4_m:
	ID = Intrinsic::riscv_vnclipu_wx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u8m1_m:
	ID = Intrinsic::riscv_vnclipu_wi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u8m2_m:
	ID = Intrinsic::riscv_vnclipu_wi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u8m4_m:
	ID = Intrinsic::riscv_vnclipu_wi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u16m1_m:
	ID = Intrinsic::riscv_vnclipu_wi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u16m2_m:
	ID = Intrinsic::riscv_vnclipu_wi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnclipu_wi_u16m4_m:
	ID = Intrinsic::riscv_vnclipu_wi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i8m1_m:
	ID = Intrinsic::riscv_vnclip_wv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i8m2_m:
	ID = Intrinsic::riscv_vnclip_wv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i8m4_m:
	ID = Intrinsic::riscv_vnclip_wv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i16m1_m:
	ID = Intrinsic::riscv_vnclip_wv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i16m2_m:
	ID = Intrinsic::riscv_vnclip_wv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wv_i16m4_m:
	ID = Intrinsic::riscv_vnclip_wv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i8m1_m:
	ID = Intrinsic::riscv_vnclip_wx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i8m2_m:
	ID = Intrinsic::riscv_vnclip_wx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i8m4_m:
	ID = Intrinsic::riscv_vnclip_wx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i16m1_m:
	ID = Intrinsic::riscv_vnclip_wx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i16m2_m:
	ID = Intrinsic::riscv_vnclip_wx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wx_i16m4_m:
	ID = Intrinsic::riscv_vnclip_wx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i8m1_m:
	ID = Intrinsic::riscv_vnclip_wi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i8m2_m:
	ID = Intrinsic::riscv_vnclip_wi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i8m4_m:
	ID = Intrinsic::riscv_vnclip_wi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i16m1_m:
	ID = Intrinsic::riscv_vnclip_wi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i16m2_m:
	ID = Intrinsic::riscv_vnclip_wi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vnclip_wi_i16m4_m:
	ID = Intrinsic::riscv_vnclip_wi_16m4_m;
	break;

	//Vector Unit-Stride Load Functions
    case RISCV::BI__builtin_riscv_vle_v_i8m1:
    case RISCV::BI__builtin_riscv_vle_v_u8m1:
	ID = Intrinsic::riscv_vle_v_8m1;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i8m2:
    case RISCV::BI__builtin_riscv_vle_v_u8m2:
	ID = Intrinsic::riscv_vle_v_8m2;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i8m4:
    case RISCV::BI__builtin_riscv_vle_v_u8m4:
	ID = Intrinsic::riscv_vle_v_8m4;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i8m8:
    case RISCV::BI__builtin_riscv_vle_v_u8m8:
	ID = Intrinsic::riscv_vle_v_8m8;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i16m1:
    case RISCV::BI__builtin_riscv_vle_v_u16m1:
	ID = Intrinsic::riscv_vle_v_16m1;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i16m2:
    case RISCV::BI__builtin_riscv_vle_v_u16m2:
	ID = Intrinsic::riscv_vle_v_16m2;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i16m4:
    case RISCV::BI__builtin_riscv_vle_v_u16m4:
	ID = Intrinsic::riscv_vle_v_16m4;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i16m8:
    case RISCV::BI__builtin_riscv_vle_v_u16m8:
	ID = Intrinsic::riscv_vle_v_16m8;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i32m1:
    case RISCV::BI__builtin_riscv_vle_v_u32m1:
	ID = Intrinsic::riscv_vle_v_32m1;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i32m2:
    case RISCV::BI__builtin_riscv_vle_v_u32m2:
	ID = Intrinsic::riscv_vle_v_32m2;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i32m4:
    case RISCV::BI__builtin_riscv_vle_v_u32m4:
	ID = Intrinsic::riscv_vle_v_32m4;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i32m8:
    case RISCV::BI__builtin_riscv_vle_v_u32m8:
	ID = Intrinsic::riscv_vle_v_32m8;
	break;
    case RISCV::BI__builtin_riscv_vle_v_f32m1:
	ID = Intrinsic::riscv_vle_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vle_v_f32m2:
	ID = Intrinsic::riscv_vle_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vle_v_f32m4:
	ID = Intrinsic::riscv_vle_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vle_v_f32m8:
	ID = Intrinsic::riscv_vle_v_f32m8;
	break;

	//masked functions
    case RISCV::BI__builtin_riscv_vle_v_i8m1_m:
    case RISCV::BI__builtin_riscv_vle_v_u8m1_m:
	ID = Intrinsic::riscv_vle_v_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i8m2_m:
    case RISCV::BI__builtin_riscv_vle_v_u8m2_m:
	ID = Intrinsic::riscv_vle_v_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i8m4_m:
    case RISCV::BI__builtin_riscv_vle_v_u8m4_m:
	ID = Intrinsic::riscv_vle_v_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i8m8_m:
    case RISCV::BI__builtin_riscv_vle_v_u8m8_m:
	ID = Intrinsic::riscv_vle_v_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i16m1_m:
    case RISCV::BI__builtin_riscv_vle_v_u16m1_m:
	ID = Intrinsic::riscv_vle_v_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i16m2_m:
    case RISCV::BI__builtin_riscv_vle_v_u16m2_m:
	ID = Intrinsic::riscv_vle_v_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i16m4_m:
    case RISCV::BI__builtin_riscv_vle_v_u16m4_m:
	ID = Intrinsic::riscv_vle_v_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i16m8_m:
    case RISCV::BI__builtin_riscv_vle_v_u16m8_m:
	ID = Intrinsic::riscv_vle_v_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i32m1_m:
    case RISCV::BI__builtin_riscv_vle_v_u32m1_m:
	ID = Intrinsic::riscv_vle_v_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i32m2_m:
    case RISCV::BI__builtin_riscv_vle_v_u32m2_m:
	ID = Intrinsic::riscv_vle_v_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i32m4_m:
    case RISCV::BI__builtin_riscv_vle_v_u32m4_m:
	ID = Intrinsic::riscv_vle_v_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_i32m8_m:
    case RISCV::BI__builtin_riscv_vle_v_u32m8_m:
	ID = Intrinsic::riscv_vle_v_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_f32m1_m:
	ID = Intrinsic::riscv_vle_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_f32m2_m:
	ID = Intrinsic::riscv_vle_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_f32m4_m:
	ID = Intrinsic::riscv_vle_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vle_v_f32m8_m:
	ID = Intrinsic::riscv_vle_v_f32m8_m;
	break;

	//Vector Unit-Stride Store Functions
    case RISCV::BI__builtin_riscv_vse_v_i8m1:
    case RISCV::BI__builtin_riscv_vse_v_u8m1:
	ID = Intrinsic::riscv_vse_v_8m1;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i8m2:
    case RISCV::BI__builtin_riscv_vse_v_u8m2:
	ID = Intrinsic::riscv_vse_v_8m2;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i8m4:
    case RISCV::BI__builtin_riscv_vse_v_u8m4:
	ID = Intrinsic::riscv_vse_v_8m4;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i8m8:
    case RISCV::BI__builtin_riscv_vse_v_u8m8:
	ID = Intrinsic::riscv_vse_v_8m8;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i16m1:
    case RISCV::BI__builtin_riscv_vse_v_u16m1:
	ID = Intrinsic::riscv_vse_v_16m1;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i16m2:
    case RISCV::BI__builtin_riscv_vse_v_u16m2:
	ID = Intrinsic::riscv_vse_v_16m2;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i16m4:
    case RISCV::BI__builtin_riscv_vse_v_u16m4:
	ID = Intrinsic::riscv_vse_v_16m4;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i16m8:
    case RISCV::BI__builtin_riscv_vse_v_u16m8:
	ID = Intrinsic::riscv_vse_v_16m8;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i32m1:
    case RISCV::BI__builtin_riscv_vse_v_u32m1:
	ID = Intrinsic::riscv_vse_v_32m1;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i32m2:
    case RISCV::BI__builtin_riscv_vse_v_u32m2:
	ID = Intrinsic::riscv_vse_v_32m2;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i32m4:
    case RISCV::BI__builtin_riscv_vse_v_u32m4:
	ID = Intrinsic::riscv_vse_v_32m4;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i32m8:
    case RISCV::BI__builtin_riscv_vse_v_u32m8:
	ID = Intrinsic::riscv_vse_v_32m8;
	break;
    case RISCV::BI__builtin_riscv_vse_v_f32m1:
	ID = Intrinsic::riscv_vse_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vse_v_f32m2:
	ID = Intrinsic::riscv_vse_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vse_v_f32m4:
	ID = Intrinsic::riscv_vse_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vse_v_f32m8:
	ID = Intrinsic::riscv_vse_v_f32m8;
	break;

	//masked functions
    case RISCV::BI__builtin_riscv_vse_v_i8m1_m:
    case RISCV::BI__builtin_riscv_vse_v_u8m1_m:
	ID = Intrinsic::riscv_vse_v_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i8m2_m:
    case RISCV::BI__builtin_riscv_vse_v_u8m2_m:
	ID = Intrinsic::riscv_vse_v_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i8m4_m:
    case RISCV::BI__builtin_riscv_vse_v_u8m4_m:
	ID = Intrinsic::riscv_vse_v_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i8m8_m:
    case RISCV::BI__builtin_riscv_vse_v_u8m8_m:
	ID = Intrinsic::riscv_vse_v_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i16m1_m:
    case RISCV::BI__builtin_riscv_vse_v_u16m1_m:
	ID = Intrinsic::riscv_vse_v_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i16m2_m:
    case RISCV::BI__builtin_riscv_vse_v_u16m2_m:
	ID = Intrinsic::riscv_vse_v_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i16m4_m:
    case RISCV::BI__builtin_riscv_vse_v_u16m4_m:
	ID = Intrinsic::riscv_vse_v_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i16m8_m:
    case RISCV::BI__builtin_riscv_vse_v_u16m8_m:
	ID = Intrinsic::riscv_vse_v_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i32m1_m:
    case RISCV::BI__builtin_riscv_vse_v_u32m1_m:
	ID = Intrinsic::riscv_vse_v_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i32m2_m:
    case RISCV::BI__builtin_riscv_vse_v_u32m2_m:
	ID = Intrinsic::riscv_vse_v_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i32m4_m:
    case RISCV::BI__builtin_riscv_vse_v_u32m4_m:
	ID = Intrinsic::riscv_vse_v_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_i32m8_m:
    case RISCV::BI__builtin_riscv_vse_v_u32m8_m:
	ID = Intrinsic::riscv_vse_v_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_f32m1_m:
	ID = Intrinsic::riscv_vse_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_f32m2_m:
	ID = Intrinsic::riscv_vse_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_f32m4_m:
	ID = Intrinsic::riscv_vse_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vse_v_f32m8_m:
	ID = Intrinsic::riscv_vse_v_f32m8_m;
	break;

//vector stride load
    case RISCV::BI__builtin_riscv_vlse_v_i8m1:
    case RISCV::BI__builtin_riscv_vlse_v_u8m1:
	ID = Intrinsic::riscv_vlse_v_8m1;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i8m2:
    case RISCV::BI__builtin_riscv_vlse_v_u8m2:
	ID = Intrinsic::riscv_vlse_v_8m2;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i8m4:
    case RISCV::BI__builtin_riscv_vlse_v_u8m4:
	ID = Intrinsic::riscv_vlse_v_8m4;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i8m8:
    case RISCV::BI__builtin_riscv_vlse_v_u8m8:
	ID = Intrinsic::riscv_vlse_v_8m8;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i16m1:
    case RISCV::BI__builtin_riscv_vlse_v_u16m1:
	ID = Intrinsic::riscv_vlse_v_16m1;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i16m2:
    case RISCV::BI__builtin_riscv_vlse_v_u16m2:
	ID = Intrinsic::riscv_vlse_v_16m2;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i16m4:
    case RISCV::BI__builtin_riscv_vlse_v_u16m4:
	ID = Intrinsic::riscv_vlse_v_16m4;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i16m8:
    case RISCV::BI__builtin_riscv_vlse_v_u16m8:
	ID = Intrinsic::riscv_vlse_v_16m8;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i32m1:
    case RISCV::BI__builtin_riscv_vlse_v_u32m1:
	ID = Intrinsic::riscv_vlse_v_32m1;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i32m2:
    case RISCV::BI__builtin_riscv_vlse_v_u32m2:
	ID = Intrinsic::riscv_vlse_v_32m2;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i32m4:
    case RISCV::BI__builtin_riscv_vlse_v_u32m4:
	ID = Intrinsic::riscv_vlse_v_32m4;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i32m8:
    case RISCV::BI__builtin_riscv_vlse_v_u32m8:
	ID = Intrinsic::riscv_vlse_v_32m8;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_f32m1:
	ID = Intrinsic::riscv_vlse_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_f32m2:
	ID = Intrinsic::riscv_vlse_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_f32m4:
	ID = Intrinsic::riscv_vlse_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_f32m8:
	ID = Intrinsic::riscv_vlse_v_f32m8;
	break;

//masked
    case RISCV::BI__builtin_riscv_vlse_v_i8m1_m:
    case RISCV::BI__builtin_riscv_vlse_v_u8m1_m:
	ID = Intrinsic::riscv_vlse_v_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i8m2_m:
    case RISCV::BI__builtin_riscv_vlse_v_u8m2_m:
	ID = Intrinsic::riscv_vlse_v_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i8m4_m:
    case RISCV::BI__builtin_riscv_vlse_v_u8m4_m:
	ID = Intrinsic::riscv_vlse_v_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i8m8_m:
    case RISCV::BI__builtin_riscv_vlse_v_u8m8_m:
	ID = Intrinsic::riscv_vlse_v_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i16m1_m:
    case RISCV::BI__builtin_riscv_vlse_v_u16m1_m:
	ID = Intrinsic::riscv_vlse_v_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i16m2_m:
    case RISCV::BI__builtin_riscv_vlse_v_u16m2_m:
	ID = Intrinsic::riscv_vlse_v_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i16m4_m:
    case RISCV::BI__builtin_riscv_vlse_v_u16m4_m:
	ID = Intrinsic::riscv_vlse_v_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i16m8_m:
    case RISCV::BI__builtin_riscv_vlse_v_u16m8_m:
	ID = Intrinsic::riscv_vlse_v_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i32m1_m:
    case RISCV::BI__builtin_riscv_vlse_v_u32m1_m:
	ID = Intrinsic::riscv_vlse_v_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i32m2_m:
    case RISCV::BI__builtin_riscv_vlse_v_u32m2_m:
	ID = Intrinsic::riscv_vlse_v_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i32m4_m:
    case RISCV::BI__builtin_riscv_vlse_v_u32m4_m:
	ID = Intrinsic::riscv_vlse_v_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_i32m8_m:
    case RISCV::BI__builtin_riscv_vlse_v_u32m8_m:
	ID = Intrinsic::riscv_vlse_v_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_f32m1_m:
	ID = Intrinsic::riscv_vlse_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_f32m2_m:
	ID = Intrinsic::riscv_vlse_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_f32m4_m:
	ID = Intrinsic::riscv_vlse_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vlse_v_f32m8_m:
	ID = Intrinsic::riscv_vlse_v_f32m8_m;
	break;

//vector stride store
    case RISCV::BI__builtin_riscv_vsse_v_i8m1:
    case RISCV::BI__builtin_riscv_vsse_v_u8m1:
	ID = Intrinsic::riscv_vsse_v_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i8m2:
    case RISCV::BI__builtin_riscv_vsse_v_u8m2:
	ID = Intrinsic::riscv_vsse_v_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i8m4:
    case RISCV::BI__builtin_riscv_vsse_v_u8m4:
	ID = Intrinsic::riscv_vsse_v_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i8m8:
    case RISCV::BI__builtin_riscv_vsse_v_u8m8:
	ID = Intrinsic::riscv_vsse_v_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i16m1:
    case RISCV::BI__builtin_riscv_vsse_v_u16m1:
	ID = Intrinsic::riscv_vsse_v_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i16m2:
    case RISCV::BI__builtin_riscv_vsse_v_u16m2:
	ID = Intrinsic::riscv_vsse_v_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i16m4:
    case RISCV::BI__builtin_riscv_vsse_v_u16m4:
	ID = Intrinsic::riscv_vsse_v_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i16m8:
    case RISCV::BI__builtin_riscv_vsse_v_u16m8:
	ID = Intrinsic::riscv_vsse_v_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i32m1:
    case RISCV::BI__builtin_riscv_vsse_v_u32m1:
	ID = Intrinsic::riscv_vsse_v_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i32m2:
    case RISCV::BI__builtin_riscv_vsse_v_u32m2:
	ID = Intrinsic::riscv_vsse_v_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i32m4:
    case RISCV::BI__builtin_riscv_vsse_v_u32m4:
	ID = Intrinsic::riscv_vsse_v_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i32m8:
    case RISCV::BI__builtin_riscv_vsse_v_u32m8:
	ID = Intrinsic::riscv_vsse_v_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_f32m1:
	ID = Intrinsic::riscv_vsse_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_f32m2:
	ID = Intrinsic::riscv_vsse_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_f32m4:
	ID = Intrinsic::riscv_vsse_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_f32m8:
	ID = Intrinsic::riscv_vsse_v_f32m8;
	break;

//masked 
    case RISCV::BI__builtin_riscv_vsse_v_i8m1_m:
    case RISCV::BI__builtin_riscv_vsse_v_u8m1_m:
	ID = Intrinsic::riscv_vsse_v_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i8m2_m:
    case RISCV::BI__builtin_riscv_vsse_v_u8m2_m:
	ID = Intrinsic::riscv_vsse_v_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i8m4_m:
    case RISCV::BI__builtin_riscv_vsse_v_u8m4_m:
	ID = Intrinsic::riscv_vsse_v_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i8m8_m:
    case RISCV::BI__builtin_riscv_vsse_v_u8m8_m:
	ID = Intrinsic::riscv_vsse_v_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i16m1_m:
    case RISCV::BI__builtin_riscv_vsse_v_u16m1_m:
	ID = Intrinsic::riscv_vsse_v_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i16m2_m:
    case RISCV::BI__builtin_riscv_vsse_v_u16m2_m:
	ID = Intrinsic::riscv_vsse_v_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i16m4_m:
    case RISCV::BI__builtin_riscv_vsse_v_u16m4_m:
	ID = Intrinsic::riscv_vsse_v_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i16m8_m:
    case RISCV::BI__builtin_riscv_vsse_v_u16m8_m:
	ID = Intrinsic::riscv_vsse_v_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i32m1_m:
    case RISCV::BI__builtin_riscv_vsse_v_u32m1_m:
	ID = Intrinsic::riscv_vsse_v_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i32m2_m:
    case RISCV::BI__builtin_riscv_vsse_v_u32m2_m:
	ID = Intrinsic::riscv_vsse_v_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i32m4_m:
    case RISCV::BI__builtin_riscv_vsse_v_u32m4_m:
	ID = Intrinsic::riscv_vsse_v_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_i32m8_m:
    case RISCV::BI__builtin_riscv_vsse_v_u32m8_m:
	ID = Intrinsic::riscv_vsse_v_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_f32m1_m:
	ID = Intrinsic::riscv_vsse_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_f32m2_m:
	ID = Intrinsic::riscv_vsse_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_f32m4_m:
	ID = Intrinsic::riscv_vsse_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsse_v_f32m8_m:
	ID = Intrinsic::riscv_vsse_v_f32m8_m;
	break;

//vector index load
    case RISCV::BI__builtin_riscv_vlxe_v_i8m1:
    case RISCV::BI__builtin_riscv_vlxe_v_u8m1:
	ID = Intrinsic::riscv_vlxe_v_8m1;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i8m2:
    case RISCV::BI__builtin_riscv_vlxe_v_u8m2:
	ID = Intrinsic::riscv_vlxe_v_8m2;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i8m4:
    case RISCV::BI__builtin_riscv_vlxe_v_u8m4:
	ID = Intrinsic::riscv_vlxe_v_8m4;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i8m8:
    case RISCV::BI__builtin_riscv_vlxe_v_u8m8:
	ID = Intrinsic::riscv_vlxe_v_8m8;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i16m1:
    case RISCV::BI__builtin_riscv_vlxe_v_u16m1:
	ID = Intrinsic::riscv_vlxe_v_16m1;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i16m2:
    case RISCV::BI__builtin_riscv_vlxe_v_u16m2:
	ID = Intrinsic::riscv_vlxe_v_16m2;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i16m4:
    case RISCV::BI__builtin_riscv_vlxe_v_u16m4:
	ID = Intrinsic::riscv_vlxe_v_16m4;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i16m8:
    case RISCV::BI__builtin_riscv_vlxe_v_u16m8:
	ID = Intrinsic::riscv_vlxe_v_16m8;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i32m1:
    case RISCV::BI__builtin_riscv_vlxe_v_u32m1:
	ID = Intrinsic::riscv_vlxe_v_32m1;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i32m2:
    case RISCV::BI__builtin_riscv_vlxe_v_u32m2:
	ID = Intrinsic::riscv_vlxe_v_32m2;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i32m4:
    case RISCV::BI__builtin_riscv_vlxe_v_u32m4:
	ID = Intrinsic::riscv_vlxe_v_32m4;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i32m8:
    case RISCV::BI__builtin_riscv_vlxe_v_u32m8:
	ID = Intrinsic::riscv_vlxe_v_32m8;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_f32m1:
	ID = Intrinsic::riscv_vlxe_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_f32m2:
	ID = Intrinsic::riscv_vlxe_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_f32m4:
	ID = Intrinsic::riscv_vlxe_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_f32m8:
	ID = Intrinsic::riscv_vlxe_v_f32m8;
	break;

//masked
    case RISCV::BI__builtin_riscv_vlxe_v_i8m1_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u8m1_m:
	ID = Intrinsic::riscv_vlxe_v_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i8m2_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u8m2_m:
	ID = Intrinsic::riscv_vlxe_v_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i8m4_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u8m4_m:
	ID = Intrinsic::riscv_vlxe_v_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i8m8_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u8m8_m:
	ID = Intrinsic::riscv_vlxe_v_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i16m1_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u16m1_m:
	ID = Intrinsic::riscv_vlxe_v_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i16m2_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u16m2_m:
	ID = Intrinsic::riscv_vlxe_v_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i16m4_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u16m4_m:
	ID = Intrinsic::riscv_vlxe_v_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i16m8_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u16m8_m:
	ID = Intrinsic::riscv_vlxe_v_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i32m1_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u32m1_m:
	ID = Intrinsic::riscv_vlxe_v_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i32m2_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u32m2_m:
	ID = Intrinsic::riscv_vlxe_v_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i32m4_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u32m4_m:
	ID = Intrinsic::riscv_vlxe_v_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_i32m8_m:
    case RISCV::BI__builtin_riscv_vlxe_v_u32m8_m:
	ID = Intrinsic::riscv_vlxe_v_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_f32m1_m:
	ID = Intrinsic::riscv_vlxe_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_f32m2_m:
	ID = Intrinsic::riscv_vlxe_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_f32m4_m:
	ID = Intrinsic::riscv_vlxe_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vlxe_v_f32m8_m:
	ID = Intrinsic::riscv_vlxe_v_f32m8_m;
	break;

//vector index store
    case RISCV::BI__builtin_riscv_vsxe_v_i8m1:
    case RISCV::BI__builtin_riscv_vsxe_v_u8m1:
	ID = Intrinsic::riscv_vsxe_v_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i8m2:
    case RISCV::BI__builtin_riscv_vsxe_v_u8m2:
	ID = Intrinsic::riscv_vsxe_v_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i8m4:
    case RISCV::BI__builtin_riscv_vsxe_v_u8m4:
	ID = Intrinsic::riscv_vsxe_v_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i8m8:
    case RISCV::BI__builtin_riscv_vsxe_v_u8m8:
	ID = Intrinsic::riscv_vsxe_v_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i16m1:
    case RISCV::BI__builtin_riscv_vsxe_v_u16m1:
	ID = Intrinsic::riscv_vsxe_v_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i16m2:
    case RISCV::BI__builtin_riscv_vsxe_v_u16m2:
	ID = Intrinsic::riscv_vsxe_v_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i16m4:
    case RISCV::BI__builtin_riscv_vsxe_v_u16m4:
	ID = Intrinsic::riscv_vsxe_v_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i16m8:
    case RISCV::BI__builtin_riscv_vsxe_v_u16m8:
	ID = Intrinsic::riscv_vsxe_v_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i32m1:
    case RISCV::BI__builtin_riscv_vsxe_v_u32m1:
	ID = Intrinsic::riscv_vsxe_v_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i32m2:
    case RISCV::BI__builtin_riscv_vsxe_v_u32m2:
	ID = Intrinsic::riscv_vsxe_v_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i32m4:
    case RISCV::BI__builtin_riscv_vsxe_v_u32m4:
	ID = Intrinsic::riscv_vsxe_v_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i32m8:
    case RISCV::BI__builtin_riscv_vsxe_v_u32m8:
	ID = Intrinsic::riscv_vsxe_v_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_f32m1:
	ID = Intrinsic::riscv_vsxe_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_f32m2:
	ID = Intrinsic::riscv_vsxe_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_f32m4:
	ID = Intrinsic::riscv_vsxe_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_f32m8:
	ID = Intrinsic::riscv_vsxe_v_f32m8;
	break;

//masked 
    case RISCV::BI__builtin_riscv_vsxe_v_i8m1_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u8m1_m:
	ID = Intrinsic::riscv_vsxe_v_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i8m2_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u8m2_m:
	ID = Intrinsic::riscv_vsxe_v_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i8m4_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u8m4_m:
	ID = Intrinsic::riscv_vsxe_v_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i8m8_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u8m8_m:
	ID = Intrinsic::riscv_vsxe_v_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i16m1_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u16m1_m:
	ID = Intrinsic::riscv_vsxe_v_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i16m2_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u16m2_m:
	ID = Intrinsic::riscv_vsxe_v_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i16m4_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u16m4_m:
	ID = Intrinsic::riscv_vsxe_v_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i16m8_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u16m8_m:
	ID = Intrinsic::riscv_vsxe_v_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i32m1_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u32m1_m:
	ID = Intrinsic::riscv_vsxe_v_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i32m2_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u32m2_m:
	ID = Intrinsic::riscv_vsxe_v_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i32m4_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u32m4_m:
	ID = Intrinsic::riscv_vsxe_v_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_i32m8_m:
    case RISCV::BI__builtin_riscv_vsxe_v_u32m8_m:
	ID = Intrinsic::riscv_vsxe_v_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_f32m1_m:
	ID = Intrinsic::riscv_vsxe_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_f32m2_m:
	ID = Intrinsic::riscv_vsxe_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_f32m4_m:
	ID = Intrinsic::riscv_vsxe_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsxe_v_f32m8_m:
	ID = Intrinsic::riscv_vsxe_v_f32m8_m;
	break;

//vector unordered index store
    case RISCV::BI__builtin_riscv_vsuxe_v_i8m1:
    case RISCV::BI__builtin_riscv_vsuxe_v_u8m1:
	ID = Intrinsic::riscv_vsuxe_v_8m1;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i8m2:
    case RISCV::BI__builtin_riscv_vsuxe_v_u8m2:
	ID = Intrinsic::riscv_vsuxe_v_8m2;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i8m4:
    case RISCV::BI__builtin_riscv_vsuxe_v_u8m4:
	ID = Intrinsic::riscv_vsuxe_v_8m4;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i8m8:
    case RISCV::BI__builtin_riscv_vsuxe_v_u8m8:
	ID = Intrinsic::riscv_vsuxe_v_8m8;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i16m1:
    case RISCV::BI__builtin_riscv_vsuxe_v_u16m1:
	ID = Intrinsic::riscv_vsuxe_v_16m1;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i16m2:
    case RISCV::BI__builtin_riscv_vsuxe_v_u16m2:
	ID = Intrinsic::riscv_vsuxe_v_16m2;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i16m4:
    case RISCV::BI__builtin_riscv_vsuxe_v_u16m4:
	ID = Intrinsic::riscv_vsuxe_v_16m4;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i16m8:
    case RISCV::BI__builtin_riscv_vsuxe_v_u16m8:
	ID = Intrinsic::riscv_vsuxe_v_16m8;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i32m1:
    case RISCV::BI__builtin_riscv_vsuxe_v_u32m1:
	ID = Intrinsic::riscv_vsuxe_v_32m1;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i32m2:
    case RISCV::BI__builtin_riscv_vsuxe_v_u32m2:
	ID = Intrinsic::riscv_vsuxe_v_32m2;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i32m4:
    case RISCV::BI__builtin_riscv_vsuxe_v_u32m4:
	ID = Intrinsic::riscv_vsuxe_v_32m4;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i32m8:
    case RISCV::BI__builtin_riscv_vsuxe_v_u32m8:
	ID = Intrinsic::riscv_vsuxe_v_32m8;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_f32m1:
	ID = Intrinsic::riscv_vsuxe_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_f32m2:
	ID = Intrinsic::riscv_vsuxe_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_f32m4:
	ID = Intrinsic::riscv_vsuxe_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_f32m8:
	ID = Intrinsic::riscv_vsuxe_v_f32m8;
	break;

//masked 
    case RISCV::BI__builtin_riscv_vsuxe_v_i8m1_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u8m1_m:
	ID = Intrinsic::riscv_vsuxe_v_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i8m2_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u8m2_m:
	ID = Intrinsic::riscv_vsuxe_v_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i8m4_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u8m4_m:
	ID = Intrinsic::riscv_vsuxe_v_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i8m8_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u8m8_m:
	ID = Intrinsic::riscv_vsuxe_v_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i16m1_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u16m1_m:
	ID = Intrinsic::riscv_vsuxe_v_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i16m2_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u16m2_m:
	ID = Intrinsic::riscv_vsuxe_v_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i16m4_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u16m4_m:
	ID = Intrinsic::riscv_vsuxe_v_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i16m8_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u16m8_m:
	ID = Intrinsic::riscv_vsuxe_v_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i32m1_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u32m1_m:
	ID = Intrinsic::riscv_vsuxe_v_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i32m2_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u32m2_m:
	ID = Intrinsic::riscv_vsuxe_v_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i32m4_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u32m4_m:
	ID = Intrinsic::riscv_vsuxe_v_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_i32m8_m:
    case RISCV::BI__builtin_riscv_vsuxe_v_u32m8_m:
	ID = Intrinsic::riscv_vsuxe_v_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_f32m1_m:
	ID = Intrinsic::riscv_vsuxe_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_f32m2_m:
	ID = Intrinsic::riscv_vsuxe_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_f32m4_m:
	ID = Intrinsic::riscv_vsuxe_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vsuxe_v_f32m8_m:
	ID = Intrinsic::riscv_vsuxe_v_f32m8_m;
	break;

//vector fault-only-first
    case RISCV::BI__builtin_riscv_vleff_v_i8m1:
    case RISCV::BI__builtin_riscv_vleff_v_u8m1:
	ID = Intrinsic::riscv_vleff_v_8m1;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i8m2:
    case RISCV::BI__builtin_riscv_vleff_v_u8m2:
	ID = Intrinsic::riscv_vleff_v_8m2;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i8m4:
    case RISCV::BI__builtin_riscv_vleff_v_u8m4:
	ID = Intrinsic::riscv_vleff_v_8m4;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i8m8:
    case RISCV::BI__builtin_riscv_vleff_v_u8m8:
	ID = Intrinsic::riscv_vleff_v_8m8;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i16m1:
    case RISCV::BI__builtin_riscv_vleff_v_u16m1:
	ID = Intrinsic::riscv_vleff_v_16m1;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i16m2:
    case RISCV::BI__builtin_riscv_vleff_v_u16m2:
	ID = Intrinsic::riscv_vleff_v_16m2;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i16m4:
    case RISCV::BI__builtin_riscv_vleff_v_u16m4:
	ID = Intrinsic::riscv_vleff_v_16m4;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i16m8:
    case RISCV::BI__builtin_riscv_vleff_v_u16m8:
	ID = Intrinsic::riscv_vleff_v_16m8;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i32m1:
    case RISCV::BI__builtin_riscv_vleff_v_u32m1:
	ID = Intrinsic::riscv_vleff_v_32m1;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i32m2:
    case RISCV::BI__builtin_riscv_vleff_v_u32m2:
	ID = Intrinsic::riscv_vleff_v_32m2;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i32m4:
    case RISCV::BI__builtin_riscv_vleff_v_u32m4:
	ID = Intrinsic::riscv_vleff_v_32m4;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i32m8:
    case RISCV::BI__builtin_riscv_vleff_v_u32m8:
	ID = Intrinsic::riscv_vleff_v_32m8;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_f32m1:
	ID = Intrinsic::riscv_vleff_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_f32m2:
	ID = Intrinsic::riscv_vleff_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_f32m4:
	ID = Intrinsic::riscv_vleff_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_f32m8:
	ID = Intrinsic::riscv_vleff_v_f32m8;
	break;

//masked 
    case RISCV::BI__builtin_riscv_vleff_v_i8m1_m:
    case RISCV::BI__builtin_riscv_vleff_v_u8m1_m:
	ID = Intrinsic::riscv_vleff_v_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i8m2_m:
    case RISCV::BI__builtin_riscv_vleff_v_u8m2_m:
	ID = Intrinsic::riscv_vleff_v_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i8m4_m:
    case RISCV::BI__builtin_riscv_vleff_v_u8m4_m:
	ID = Intrinsic::riscv_vleff_v_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i8m8_m:
    case RISCV::BI__builtin_riscv_vleff_v_u8m8_m:
	ID = Intrinsic::riscv_vleff_v_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i16m1_m:
    case RISCV::BI__builtin_riscv_vleff_v_u16m1_m:
	ID = Intrinsic::riscv_vleff_v_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i16m2_m:
    case RISCV::BI__builtin_riscv_vleff_v_u16m2_m:
	ID = Intrinsic::riscv_vleff_v_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i16m4_m:
    case RISCV::BI__builtin_riscv_vleff_v_u16m4_m:
	ID = Intrinsic::riscv_vleff_v_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i16m8_m:
    case RISCV::BI__builtin_riscv_vleff_v_u16m8_m:
	ID = Intrinsic::riscv_vleff_v_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i32m1_m:
    case RISCV::BI__builtin_riscv_vleff_v_u32m1_m:
	ID = Intrinsic::riscv_vleff_v_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i32m2_m:
    case RISCV::BI__builtin_riscv_vleff_v_u32m2_m:
	ID = Intrinsic::riscv_vleff_v_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i32m4_m:
    case RISCV::BI__builtin_riscv_vleff_v_u32m4_m:
	ID = Intrinsic::riscv_vleff_v_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_i32m8_m:
    case RISCV::BI__builtin_riscv_vleff_v_u32m8_m:
	ID = Intrinsic::riscv_vleff_v_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_f32m1_m:
	ID = Intrinsic::riscv_vleff_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_f32m2_m:
	ID = Intrinsic::riscv_vleff_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_f32m4_m:
	ID = Intrinsic::riscv_vleff_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vleff_v_f32m8_m:
	ID = Intrinsic::riscv_vleff_v_f32m8_m;
	break;

//vector fadd/fsub
    case RISCV::BI__builtin_riscv_vfadd_vv_f32m1:
	ID = Intrinsic::riscv_vfadd_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vv_f32m2:
	ID = Intrinsic::riscv_vfadd_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vv_f32m4:
	ID = Intrinsic::riscv_vfadd_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vv_f32m8:
	ID = Intrinsic::riscv_vfadd_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vf_f32m1:
	ID = Intrinsic::riscv_vfadd_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vf_f32m2:
	ID = Intrinsic::riscv_vfadd_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vf_f32m4:
	ID = Intrinsic::riscv_vfadd_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vf_f32m8:
	ID = Intrinsic::riscv_vfadd_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vv_f32m1:
	ID = Intrinsic::riscv_vfsub_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vv_f32m2:
	ID = Intrinsic::riscv_vfsub_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vv_f32m4:
	ID = Intrinsic::riscv_vfsub_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vv_f32m8:
	ID = Intrinsic::riscv_vfsub_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vf_f32m1:
	ID = Intrinsic::riscv_vfsub_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vf_f32m2:
	ID = Intrinsic::riscv_vfsub_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vf_f32m4:
	ID = Intrinsic::riscv_vfsub_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vf_f32m8:
	ID = Intrinsic::riscv_vfsub_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfrsub_vf_f32m1:
	ID = Intrinsic::riscv_vfrsub_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfrsub_vf_f32m2:
	ID = Intrinsic::riscv_vfrsub_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfrsub_vf_f32m4:
	ID = Intrinsic::riscv_vfrsub_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfrsub_vf_f32m8:
	ID = Intrinsic::riscv_vfrsub_vf_f32m8;
	break;

//masked    
    case RISCV::BI__builtin_riscv_vfadd_vv_f32m1_m:
	ID = Intrinsic::riscv_vfadd_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vv_f32m2_m:
	ID = Intrinsic::riscv_vfadd_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vv_f32m4_m:
	ID = Intrinsic::riscv_vfadd_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vv_f32m8_m:
	ID = Intrinsic::riscv_vfadd_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vf_f32m1_m:
	ID = Intrinsic::riscv_vfadd_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vf_f32m2_m:
	ID = Intrinsic::riscv_vfadd_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vf_f32m4_m:
	ID = Intrinsic::riscv_vfadd_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfadd_vf_f32m8_m:
	ID = Intrinsic::riscv_vfadd_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vv_f32m1_m:
	ID = Intrinsic::riscv_vfsub_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vv_f32m2_m:
	ID = Intrinsic::riscv_vfsub_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vv_f32m4_m:
	ID = Intrinsic::riscv_vfsub_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vv_f32m8_m:
	ID = Intrinsic::riscv_vfsub_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vf_f32m1_m:
	ID = Intrinsic::riscv_vfsub_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vf_f32m2_m:
	ID = Intrinsic::riscv_vfsub_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vf_f32m4_m:
	ID = Intrinsic::riscv_vfsub_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfsub_vf_f32m8_m:
	ID = Intrinsic::riscv_vfsub_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfrsub_vf_f32m1_m:
	ID = Intrinsic::riscv_vfrsub_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfrsub_vf_f32m2_m:
	ID = Intrinsic::riscv_vfrsub_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfrsub_vf_f32m4_m:
	ID = Intrinsic::riscv_vfrsub_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfrsub_vf_f32m8_m:
	ID = Intrinsic::riscv_vfrsub_vf_f32m8_m;
	break;
//vector  vfmul/vfdiv    
    case RISCV::BI__builtin_riscv_vfmul_vv_f32m1:
	ID = Intrinsic::riscv_vfmul_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vv_f32m2:
	ID = Intrinsic::riscv_vfmul_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vv_f32m4:
	ID = Intrinsic::riscv_vfmul_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vv_f32m8:
	ID = Intrinsic::riscv_vfmul_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vf_f32m1:
	ID = Intrinsic::riscv_vfmul_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vf_f32m2:
	ID = Intrinsic::riscv_vfmul_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vf_f32m4:
	ID = Intrinsic::riscv_vfmul_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vf_f32m8:
	ID = Intrinsic::riscv_vfmul_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vv_f32m1:
	ID = Intrinsic::riscv_vfdiv_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vv_f32m2:
	ID = Intrinsic::riscv_vfdiv_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vv_f32m4:
	ID = Intrinsic::riscv_vfdiv_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vv_f32m8:
	ID = Intrinsic::riscv_vfdiv_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vf_f32m1:
	ID = Intrinsic::riscv_vfdiv_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vf_f32m2:
	ID = Intrinsic::riscv_vfdiv_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vf_f32m4:
	ID = Intrinsic::riscv_vfdiv_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vf_f32m8:
	ID = Intrinsic::riscv_vfdiv_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfrdiv_vf_f32m1:
	ID = Intrinsic::riscv_vfrdiv_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfrdiv_vf_f32m2:
	ID = Intrinsic::riscv_vfrdiv_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfrdiv_vf_f32m4:
	ID = Intrinsic::riscv_vfrdiv_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfrdiv_vf_f32m8:
	ID = Intrinsic::riscv_vfrdiv_vf_f32m8;
	break;

//masked    
    case RISCV::BI__builtin_riscv_vfmul_vv_f32m1_m:
	ID = Intrinsic::riscv_vfmul_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vv_f32m2_m:
	ID = Intrinsic::riscv_vfmul_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vv_f32m4_m:
	ID = Intrinsic::riscv_vfmul_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vv_f32m8_m:
	ID = Intrinsic::riscv_vfmul_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vf_f32m1_m:
	ID = Intrinsic::riscv_vfmul_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vf_f32m2_m:
	ID = Intrinsic::riscv_vfmul_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vf_f32m4_m:
	ID = Intrinsic::riscv_vfmul_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmul_vf_f32m8_m:
	ID = Intrinsic::riscv_vfmul_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vv_f32m1_m:
	ID = Intrinsic::riscv_vfdiv_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vv_f32m2_m:
	ID = Intrinsic::riscv_vfdiv_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vv_f32m4_m:
	ID = Intrinsic::riscv_vfdiv_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vv_f32m8_m:
	ID = Intrinsic::riscv_vfdiv_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vf_f32m1_m:
	ID = Intrinsic::riscv_vfdiv_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vf_f32m2_m:
	ID = Intrinsic::riscv_vfdiv_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vf_f32m4_m:
	ID = Intrinsic::riscv_vfdiv_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfdiv_vf_f32m8_m:
	ID = Intrinsic::riscv_vfdiv_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfrdiv_vf_f32m1_m:
	ID = Intrinsic::riscv_vfrdiv_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfrdiv_vf_f32m2_m:
	ID = Intrinsic::riscv_vfrdiv_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfrdiv_vf_f32m4_m:
	ID = Intrinsic::riscv_vfrdiv_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfrdiv_vf_f32m8_m:
	ID = Intrinsic::riscv_vfrdiv_vf_f32m8_m;
	break;

//vector fmadd/fmsub
    case RISCV::BI__builtin_riscv_vfmacc_vv_f32m1:
	ID = Intrinsic::riscv_vfmacc_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vv_f32m2:
	ID = Intrinsic::riscv_vfmacc_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vv_f32m4:
	ID = Intrinsic::riscv_vfmacc_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vv_f32m8:
	ID = Intrinsic::riscv_vfmacc_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vf_f32m1:
	ID = Intrinsic::riscv_vfmacc_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vf_f32m2:
	ID = Intrinsic::riscv_vfmacc_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vf_f32m4:
	ID = Intrinsic::riscv_vfmacc_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vf_f32m8:
	ID = Intrinsic::riscv_vfmacc_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vv_f32m1:
	ID = Intrinsic::riscv_vfnmacc_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vv_f32m2:
	ID = Intrinsic::riscv_vfnmacc_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vv_f32m4:
	ID = Intrinsic::riscv_vfnmacc_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vv_f32m8:
	ID = Intrinsic::riscv_vfnmacc_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vf_f32m1:
	ID = Intrinsic::riscv_vfnmacc_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vf_f32m2:
	ID = Intrinsic::riscv_vfnmacc_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vf_f32m4:
	ID = Intrinsic::riscv_vfnmacc_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vf_f32m8:
	ID = Intrinsic::riscv_vfnmacc_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vv_f32m1:
	ID = Intrinsic::riscv_vfmsac_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vv_f32m2:
	ID = Intrinsic::riscv_vfmsac_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vv_f32m4:
	ID = Intrinsic::riscv_vfmsac_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vv_f32m8:
	ID = Intrinsic::riscv_vfmsac_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vf_f32m1:
	ID = Intrinsic::riscv_vfmsac_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vf_f32m2:
	ID = Intrinsic::riscv_vfmsac_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vf_f32m4:
	ID = Intrinsic::riscv_vfmsac_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vf_f32m8:
	ID = Intrinsic::riscv_vfmsac_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vv_f32m1:
	ID = Intrinsic::riscv_vfnmsac_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vv_f32m2:
	ID = Intrinsic::riscv_vfnmsac_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vv_f32m4:
	ID = Intrinsic::riscv_vfnmsac_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vv_f32m8:
	ID = Intrinsic::riscv_vfnmsac_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vf_f32m1:
	ID = Intrinsic::riscv_vfnmsac_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vf_f32m2:
	ID = Intrinsic::riscv_vfnmsac_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vf_f32m4:
	ID = Intrinsic::riscv_vfnmsac_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vf_f32m8:
	ID = Intrinsic::riscv_vfnmsac_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vv_f32m1:
	ID = Intrinsic::riscv_vfmadd_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vv_f32m2:
	ID = Intrinsic::riscv_vfmadd_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vv_f32m4:
	ID = Intrinsic::riscv_vfmadd_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vv_f32m8:
	ID = Intrinsic::riscv_vfmadd_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vf_f32m1:
	ID = Intrinsic::riscv_vfmadd_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vf_f32m2:
	ID = Intrinsic::riscv_vfmadd_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vf_f32m4:
	ID = Intrinsic::riscv_vfmadd_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vf_f32m8:
	ID = Intrinsic::riscv_vfmadd_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vv_f32m1:
	ID = Intrinsic::riscv_vfnmadd_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vv_f32m2:
	ID = Intrinsic::riscv_vfnmadd_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vv_f32m4:
	ID = Intrinsic::riscv_vfnmadd_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vv_f32m8:
	ID = Intrinsic::riscv_vfnmadd_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vf_f32m1:
	ID = Intrinsic::riscv_vfnmadd_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vf_f32m2:
	ID = Intrinsic::riscv_vfnmadd_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vf_f32m4:
	ID = Intrinsic::riscv_vfnmadd_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vf_f32m8:
	ID = Intrinsic::riscv_vfnmadd_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vv_f32m1:
	ID = Intrinsic::riscv_vfmsub_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vv_f32m2:
	ID = Intrinsic::riscv_vfmsub_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vv_f32m4:
	ID = Intrinsic::riscv_vfmsub_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vv_f32m8:
	ID = Intrinsic::riscv_vfmsub_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vf_f32m1:
	ID = Intrinsic::riscv_vfmsub_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vf_f32m2:
	ID = Intrinsic::riscv_vfmsub_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vf_f32m4:
	ID = Intrinsic::riscv_vfmsub_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vf_f32m8:
	ID = Intrinsic::riscv_vfmsub_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vv_f32m1:
	ID = Intrinsic::riscv_vfnmsub_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vv_f32m2:
	ID = Intrinsic::riscv_vfnmsub_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vv_f32m4:
	ID = Intrinsic::riscv_vfnmsub_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vv_f32m8:
	ID = Intrinsic::riscv_vfnmsub_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vf_f32m1:
	ID = Intrinsic::riscv_vfnmsub_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vf_f32m2:
	ID = Intrinsic::riscv_vfnmsub_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vf_f32m4:
	ID = Intrinsic::riscv_vfnmsub_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vf_f32m8:
	ID = Intrinsic::riscv_vfnmsub_vf_f32m8;
	break;

//masked     
    case RISCV::BI__builtin_riscv_vfmacc_vv_f32m1_m:
	ID = Intrinsic::riscv_vfmacc_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vv_f32m2_m:
	ID = Intrinsic::riscv_vfmacc_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vv_f32m4_m:
	ID = Intrinsic::riscv_vfmacc_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vv_f32m8_m:
	ID = Intrinsic::riscv_vfmacc_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vf_f32m1_m:
	ID = Intrinsic::riscv_vfmacc_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vf_f32m2_m:
	ID = Intrinsic::riscv_vfmacc_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vf_f32m4_m:
	ID = Intrinsic::riscv_vfmacc_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmacc_vf_f32m8_m:
	ID = Intrinsic::riscv_vfmacc_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vv_f32m1_m:
	ID = Intrinsic::riscv_vfnmacc_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vv_f32m2_m:
	ID = Intrinsic::riscv_vfnmacc_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vv_f32m4_m:
	ID = Intrinsic::riscv_vfnmacc_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vv_f32m8_m:
	ID = Intrinsic::riscv_vfnmacc_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vf_f32m1_m:
	ID = Intrinsic::riscv_vfnmacc_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vf_f32m2_m:
	ID = Intrinsic::riscv_vfnmacc_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vf_f32m4_m:
	ID = Intrinsic::riscv_vfnmacc_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmacc_vf_f32m8_m:
	ID = Intrinsic::riscv_vfnmacc_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vv_f32m1_m:
	ID = Intrinsic::riscv_vfmsac_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vv_f32m2_m:
	ID = Intrinsic::riscv_vfmsac_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vv_f32m4_m:
	ID = Intrinsic::riscv_vfmsac_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vv_f32m8_m:
	ID = Intrinsic::riscv_vfmsac_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vf_f32m1_m:
	ID = Intrinsic::riscv_vfmsac_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vf_f32m2_m:
	ID = Intrinsic::riscv_vfmsac_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vf_f32m4_m:
	ID = Intrinsic::riscv_vfmsac_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsac_vf_f32m8_m:
	ID = Intrinsic::riscv_vfmsac_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vv_f32m1_m:
	ID = Intrinsic::riscv_vfnmsac_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vv_f32m2_m:
	ID = Intrinsic::riscv_vfnmsac_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vv_f32m4_m:
	ID = Intrinsic::riscv_vfnmsac_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vv_f32m8_m:
	ID = Intrinsic::riscv_vfnmsac_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vf_f32m1_m:
	ID = Intrinsic::riscv_vfnmsac_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vf_f32m2_m:
	ID = Intrinsic::riscv_vfnmsac_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vf_f32m4_m:
	ID = Intrinsic::riscv_vfnmsac_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsac_vf_f32m8_m:
	ID = Intrinsic::riscv_vfnmsac_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vv_f32m1_m:
	ID = Intrinsic::riscv_vfmadd_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vv_f32m2_m:
	ID = Intrinsic::riscv_vfmadd_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vv_f32m4_m:
	ID = Intrinsic::riscv_vfmadd_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vv_f32m8_m:
	ID = Intrinsic::riscv_vfmadd_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vf_f32m1_m:
	ID = Intrinsic::riscv_vfmadd_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vf_f32m2_m:
	ID = Intrinsic::riscv_vfmadd_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vf_f32m4_m:
	ID = Intrinsic::riscv_vfmadd_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmadd_vf_f32m8_m:
	ID = Intrinsic::riscv_vfmadd_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vv_f32m1_m:
	ID = Intrinsic::riscv_vfnmadd_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vv_f32m2_m:
	ID = Intrinsic::riscv_vfnmadd_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vv_f32m4_m:
	ID = Intrinsic::riscv_vfnmadd_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vv_f32m8_m:
	ID = Intrinsic::riscv_vfnmadd_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vf_f32m1_m:
	ID = Intrinsic::riscv_vfnmadd_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vf_f32m2_m:
	ID = Intrinsic::riscv_vfnmadd_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vf_f32m4_m:
	ID = Intrinsic::riscv_vfnmadd_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmadd_vf_f32m8_m:
	ID = Intrinsic::riscv_vfnmadd_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vv_f32m1_m:
	ID = Intrinsic::riscv_vfmsub_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vv_f32m2_m:
	ID = Intrinsic::riscv_vfmsub_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vv_f32m4_m:
	ID = Intrinsic::riscv_vfmsub_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vv_f32m8_m:
	ID = Intrinsic::riscv_vfmsub_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vf_f32m1_m:
	ID = Intrinsic::riscv_vfmsub_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vf_f32m2_m:
	ID = Intrinsic::riscv_vfmsub_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vf_f32m4_m:
	ID = Intrinsic::riscv_vfmsub_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmsub_vf_f32m8_m:
	ID = Intrinsic::riscv_vfmsub_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vv_f32m1_m:
	ID = Intrinsic::riscv_vfnmsub_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vv_f32m2_m:
	ID = Intrinsic::riscv_vfnmsub_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vv_f32m4_m:
	ID = Intrinsic::riscv_vfnmsub_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vv_f32m8_m:
	ID = Intrinsic::riscv_vfnmsub_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vf_f32m1_m:
	ID = Intrinsic::riscv_vfnmsub_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vf_f32m2_m:
	ID = Intrinsic::riscv_vfnmsub_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vf_f32m4_m:
	ID = Intrinsic::riscv_vfnmsub_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfnmsub_vf_f32m8_m:
	ID = Intrinsic::riscv_vfnmsub_vf_f32m8_m;
	break;

//vector vfsqrt
    case RISCV::BI__builtin_riscv_vfsqrt_v_f32m1:
	ID = Intrinsic::riscv_vfsqrt_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfsqrt_v_f32m2:
	ID = Intrinsic::riscv_vfsqrt_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfsqrt_v_f32m4:
	ID = Intrinsic::riscv_vfsqrt_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfsqrt_v_f32m8:
	ID = Intrinsic::riscv_vfsqrt_v_f32m8;
	break;

//masked 
    case RISCV::BI__builtin_riscv_vfsqrt_v_f32m1_m:
	ID = Intrinsic::riscv_vfsqrt_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfsqrt_v_f32m2_m:
	ID = Intrinsic::riscv_vfsqrt_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfsqrt_v_f32m4_m:
	ID = Intrinsic::riscv_vfsqrt_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfsqrt_v_f32m8_m:
	ID = Intrinsic::riscv_vfsqrt_v_f32m8_m;
	break;

//vector        vfmin/vfmax             
    case RISCV::BI__builtin_riscv_vfmin_vv_f32m1:
	ID = Intrinsic::riscv_vfmin_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vv_f32m2:
	ID = Intrinsic::riscv_vfmin_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vv_f32m4:
	ID = Intrinsic::riscv_vfmin_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vv_f32m8:
	ID = Intrinsic::riscv_vfmin_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vf_f32m1:
	ID = Intrinsic::riscv_vfmin_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vf_f32m2:
	ID = Intrinsic::riscv_vfmin_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vf_f32m4:
	ID = Intrinsic::riscv_vfmin_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vf_f32m8:
	ID = Intrinsic::riscv_vfmin_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vv_f32m1:
	ID = Intrinsic::riscv_vfmax_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vv_f32m2:
	ID = Intrinsic::riscv_vfmax_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vv_f32m4:
	ID = Intrinsic::riscv_vfmax_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vv_f32m8:
	ID = Intrinsic::riscv_vfmax_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vf_f32m1:
	ID = Intrinsic::riscv_vfmax_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vf_f32m2:
	ID = Intrinsic::riscv_vfmax_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vf_f32m4:
	ID = Intrinsic::riscv_vfmax_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vf_f32m8:
	ID = Intrinsic::riscv_vfmax_vf_f32m8;
	break;

//masked
    case RISCV::BI__builtin_riscv_vfmin_vv_f32m1_m:
	ID = Intrinsic::riscv_vfmin_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vv_f32m2_m:
	ID = Intrinsic::riscv_vfmin_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vv_f32m4_m:
	ID = Intrinsic::riscv_vfmin_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vv_f32m8_m:
	ID = Intrinsic::riscv_vfmin_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vf_f32m1_m:
	ID = Intrinsic::riscv_vfmin_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vf_f32m2_m:
	ID = Intrinsic::riscv_vfmin_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vf_f32m4_m:
	ID = Intrinsic::riscv_vfmin_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmin_vf_f32m8_m:
	ID = Intrinsic::riscv_vfmin_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vv_f32m1_m:
	ID = Intrinsic::riscv_vfmax_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vv_f32m2_m:
	ID = Intrinsic::riscv_vfmax_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vv_f32m4_m:
	ID = Intrinsic::riscv_vfmax_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vv_f32m8_m:
	ID = Intrinsic::riscv_vfmax_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vf_f32m1_m:
	ID = Intrinsic::riscv_vfmax_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vf_f32m2_m:
	ID = Intrinsic::riscv_vfmax_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vf_f32m4_m:
	ID = Intrinsic::riscv_vfmax_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfmax_vf_f32m8_m:
	ID = Intrinsic::riscv_vfmax_vf_f32m8_m;
	break;

//vector float sign-injection                   
    case RISCV::BI__builtin_riscv_vfsgnj_vv_f32m1:
	ID = Intrinsic::riscv_vfsgnj_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vv_f32m2:
	ID = Intrinsic::riscv_vfsgnj_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vv_f32m4:
	ID = Intrinsic::riscv_vfsgnj_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vv_f32m8:
	ID = Intrinsic::riscv_vfsgnj_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vf_f32m1:
	ID = Intrinsic::riscv_vfsgnj_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vf_f32m2:
	ID = Intrinsic::riscv_vfsgnj_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vf_f32m4:
	ID = Intrinsic::riscv_vfsgnj_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vf_f32m8:
	ID = Intrinsic::riscv_vfsgnj_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vv_f32m1:
	ID = Intrinsic::riscv_vfsgnjn_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vv_f32m2:
	ID = Intrinsic::riscv_vfsgnjn_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vv_f32m4:
	ID = Intrinsic::riscv_vfsgnjn_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vv_f32m8:
	ID = Intrinsic::riscv_vfsgnjn_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vf_f32m1:
	ID = Intrinsic::riscv_vfsgnjn_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vf_f32m2:
	ID = Intrinsic::riscv_vfsgnjn_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vf_f32m4:
	ID = Intrinsic::riscv_vfsgnjn_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vf_f32m8:
	ID = Intrinsic::riscv_vfsgnjn_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vv_f32m1:
	ID = Intrinsic::riscv_vfsgnjx_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vv_f32m2:
	ID = Intrinsic::riscv_vfsgnjx_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vv_f32m4:
	ID = Intrinsic::riscv_vfsgnjx_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vv_f32m8:
	ID = Intrinsic::riscv_vfsgnjx_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vf_f32m1:
	ID = Intrinsic::riscv_vfsgnjx_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vf_f32m2:
	ID = Intrinsic::riscv_vfsgnjx_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vf_f32m4:
	ID = Intrinsic::riscv_vfsgnjx_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vf_f32m8:
	ID = Intrinsic::riscv_vfsgnjx_vf_f32m8;
	break;

//masked
    case RISCV::BI__builtin_riscv_vfsgnj_vv_f32m1_m:
	ID = Intrinsic::riscv_vfsgnj_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vv_f32m2_m:
	ID = Intrinsic::riscv_vfsgnj_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vv_f32m4_m:
	ID = Intrinsic::riscv_vfsgnj_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vv_f32m8_m:
	ID = Intrinsic::riscv_vfsgnj_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vf_f32m1_m:
	ID = Intrinsic::riscv_vfsgnj_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vf_f32m2_m:
	ID = Intrinsic::riscv_vfsgnj_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vf_f32m4_m:
	ID = Intrinsic::riscv_vfsgnj_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnj_vf_f32m8_m:
	ID = Intrinsic::riscv_vfsgnj_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vv_f32m1_m:
	ID = Intrinsic::riscv_vfsgnjn_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vv_f32m2_m:
	ID = Intrinsic::riscv_vfsgnjn_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vv_f32m4_m:
	ID = Intrinsic::riscv_vfsgnjn_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vv_f32m8_m:
	ID = Intrinsic::riscv_vfsgnjn_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vf_f32m1_m:
	ID = Intrinsic::riscv_vfsgnjn_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vf_f32m2_m:
	ID = Intrinsic::riscv_vfsgnjn_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vf_f32m4_m:
	ID = Intrinsic::riscv_vfsgnjn_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjn_vf_f32m8_m:
	ID = Intrinsic::riscv_vfsgnjn_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vv_f32m1_m:
	ID = Intrinsic::riscv_vfsgnjx_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vv_f32m2_m:
	ID = Intrinsic::riscv_vfsgnjx_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vv_f32m4_m:
	ID = Intrinsic::riscv_vfsgnjx_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vv_f32m8_m:
	ID = Intrinsic::riscv_vfsgnjx_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vf_f32m1_m:
	ID = Intrinsic::riscv_vfsgnjx_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vf_f32m2_m:
	ID = Intrinsic::riscv_vfsgnjx_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vf_f32m4_m:
	ID = Intrinsic::riscv_vfsgnjx_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfsgnjx_vf_f32m8_m:
	ID = Intrinsic::riscv_vfsgnjx_vf_f32m8_m;
	break;

//vector float compare      
    case RISCV::BI__builtin_riscv_vmfeq_vv_f32m1:
	ID = Intrinsic::riscv_vmfeq_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vv_f32m2:
	ID = Intrinsic::riscv_vmfeq_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vv_f32m4:
	ID = Intrinsic::riscv_vmfeq_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vv_f32m8:
	ID = Intrinsic::riscv_vmfeq_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vf_f32m1:
	ID = Intrinsic::riscv_vmfeq_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vf_f32m2:
	ID = Intrinsic::riscv_vmfeq_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vf_f32m4:
	ID = Intrinsic::riscv_vmfeq_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vf_f32m8:
	ID = Intrinsic::riscv_vmfeq_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vv_f32m1:
	ID = Intrinsic::riscv_vmfne_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vv_f32m2:
	ID = Intrinsic::riscv_vmfne_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vv_f32m4:
	ID = Intrinsic::riscv_vmfne_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vv_f32m8:
	ID = Intrinsic::riscv_vmfne_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vf_f32m1:
	ID = Intrinsic::riscv_vmfne_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vf_f32m2:
	ID = Intrinsic::riscv_vmfne_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vf_f32m4:
	ID = Intrinsic::riscv_vmfne_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vf_f32m8:
	ID = Intrinsic::riscv_vmfne_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vv_f32m1:
	ID = Intrinsic::riscv_vmflt_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vv_f32m2:
	ID = Intrinsic::riscv_vmflt_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vv_f32m4:
	ID = Intrinsic::riscv_vmflt_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vv_f32m8:
	ID = Intrinsic::riscv_vmflt_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vf_f32m1:
	ID = Intrinsic::riscv_vmflt_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vf_f32m2:
	ID = Intrinsic::riscv_vmflt_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vf_f32m4:
	ID = Intrinsic::riscv_vmflt_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vf_f32m8:
	ID = Intrinsic::riscv_vmflt_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vv_f32m1:
	ID = Intrinsic::riscv_vmfle_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vv_f32m2:
	ID = Intrinsic::riscv_vmfle_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vv_f32m4:
	ID = Intrinsic::riscv_vmfle_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vv_f32m8:
	ID = Intrinsic::riscv_vmfle_vv_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vf_f32m1:
	ID = Intrinsic::riscv_vmfle_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vf_f32m2:
	ID = Intrinsic::riscv_vmfle_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vf_f32m4:
	ID = Intrinsic::riscv_vmfle_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vf_f32m8:
	ID = Intrinsic::riscv_vmfle_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vmfgt_vf_f32m1:
	ID = Intrinsic::riscv_vmfgt_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vmfgt_vf_f32m2:
	ID = Intrinsic::riscv_vmfgt_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vmfgt_vf_f32m4:
	ID = Intrinsic::riscv_vmfgt_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vmfgt_vf_f32m8:
	ID = Intrinsic::riscv_vmfgt_vf_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vmfge_vf_f32m1:
	ID = Intrinsic::riscv_vmfge_vf_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vmfge_vf_f32m2:
	ID = Intrinsic::riscv_vmfge_vf_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vmfge_vf_f32m4:
	ID = Intrinsic::riscv_vmfge_vf_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vmfge_vf_f32m8:
	ID = Intrinsic::riscv_vmfge_vf_f32m8;
	break;

//masked
    case RISCV::BI__builtin_riscv_vmfeq_vv_f32m1_m:
	ID = Intrinsic::riscv_vmfeq_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vv_f32m2_m:
	ID = Intrinsic::riscv_vmfeq_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vv_f32m4_m:
	ID = Intrinsic::riscv_vmfeq_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vv_f32m8_m:
	ID = Intrinsic::riscv_vmfeq_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vf_f32m1_m:
	ID = Intrinsic::riscv_vmfeq_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vf_f32m2_m:
	ID = Intrinsic::riscv_vmfeq_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vf_f32m4_m:
	ID = Intrinsic::riscv_vmfeq_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmfeq_vf_f32m8_m:
	ID = Intrinsic::riscv_vmfeq_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vv_f32m1_m:
	ID = Intrinsic::riscv_vmfne_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vv_f32m2_m:
	ID = Intrinsic::riscv_vmfne_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vv_f32m4_m:
	ID = Intrinsic::riscv_vmfne_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vv_f32m8_m:
	ID = Intrinsic::riscv_vmfne_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vf_f32m1_m:
	ID = Intrinsic::riscv_vmfne_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vf_f32m2_m:
	ID = Intrinsic::riscv_vmfne_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vf_f32m4_m:
	ID = Intrinsic::riscv_vmfne_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmfne_vf_f32m8_m:
	ID = Intrinsic::riscv_vmfne_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vv_f32m1_m:
	ID = Intrinsic::riscv_vmflt_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vv_f32m2_m:
	ID = Intrinsic::riscv_vmflt_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vv_f32m4_m:
	ID = Intrinsic::riscv_vmflt_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vv_f32m8_m:
	ID = Intrinsic::riscv_vmflt_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vf_f32m1_m:
	ID = Intrinsic::riscv_vmflt_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vf_f32m2_m:
	ID = Intrinsic::riscv_vmflt_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vf_f32m4_m:
	ID = Intrinsic::riscv_vmflt_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmflt_vf_f32m8_m:
	ID = Intrinsic::riscv_vmflt_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vv_f32m1_m:
	ID = Intrinsic::riscv_vmfle_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vv_f32m2_m:
	ID = Intrinsic::riscv_vmfle_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vv_f32m4_m:
	ID = Intrinsic::riscv_vmfle_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vv_f32m8_m:
	ID = Intrinsic::riscv_vmfle_vv_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vf_f32m1_m:
	ID = Intrinsic::riscv_vmfle_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vf_f32m2_m:
	ID = Intrinsic::riscv_vmfle_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vf_f32m4_m:
	ID = Intrinsic::riscv_vmfle_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmfle_vf_f32m8_m:
	ID = Intrinsic::riscv_vmfle_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmfgt_vf_f32m1_m:
	ID = Intrinsic::riscv_vmfgt_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmfgt_vf_f32m2_m:
	ID = Intrinsic::riscv_vmfgt_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmfgt_vf_f32m4_m:
	ID = Intrinsic::riscv_vmfgt_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmfgt_vf_f32m8_m:
	ID = Intrinsic::riscv_vmfgt_vf_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vmfge_vf_f32m1_m:
	ID = Intrinsic::riscv_vmfge_vf_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vmfge_vf_f32m2_m:
	ID = Intrinsic::riscv_vmfge_vf_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vmfge_vf_f32m4_m:
	ID = Intrinsic::riscv_vmfge_vf_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vmfge_vf_f32m8_m:
	ID = Intrinsic::riscv_vmfge_vf_f32m8_m;
	break;

//vfclass
    case RISCV::BI__builtin_riscv_vfclass_v_f32m1:
	ID = Intrinsic::riscv_vfclass_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfclass_v_f32m2:
	ID = Intrinsic::riscv_vfclass_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfclass_v_f32m4:
	ID = Intrinsic::riscv_vfclass_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfclass_v_f32m8:
	ID = Intrinsic::riscv_vfclass_v_f32m8;
	break;

//masked
    case RISCV::BI__builtin_riscv_vfclass_v_f32m1_m:
	ID = Intrinsic::riscv_vfclass_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfclass_v_f32m2_m:
	ID = Intrinsic::riscv_vfclass_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfclass_v_f32m4_m:
	ID = Intrinsic::riscv_vfclass_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfclass_v_f32m8_m:
	ID = Intrinsic::riscv_vfclass_v_f32m8_m;
	break;

//vfmerge.vfm
    case RISCV::BI__builtin_riscv_vfmerge_vfm_f32m1:
	ID = Intrinsic::riscv_vfmerge_vfm_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmerge_vfm_f32m2:
	ID = Intrinsic::riscv_vfmerge_vfm_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmerge_vfm_f32m4:
	ID = Intrinsic::riscv_vfmerge_vfm_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmerge_vfm_f32m8:
	ID = Intrinsic::riscv_vfmerge_vfm_f32m8;
	break;

//vfmv.v.f
    case RISCV::BI__builtin_riscv_vfmv_v_f32m1:
	ID = Intrinsic::riscv_vfmv_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmv_v_f32m2:
	ID = Intrinsic::riscv_vfmv_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmv_v_f32m4:
	ID = Intrinsic::riscv_vfmv_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmv_v_f32m8:
	ID = Intrinsic::riscv_vfmv_v_f32m8;
	break;

//vector type-convert
    case RISCV::BI__builtin_riscv_vfcvt_xu_f_v_f32m1:
	ID = Intrinsic::riscv_vfcvt_xu_f_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_xu_f_v_f32m2:
	ID = Intrinsic::riscv_vfcvt_xu_f_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_xu_f_v_f32m4:
	ID = Intrinsic::riscv_vfcvt_xu_f_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_xu_f_v_f32m8:
	ID = Intrinsic::riscv_vfcvt_xu_f_v_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_x_f_v_f32m1:
	ID = Intrinsic::riscv_vfcvt_x_f_v_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_x_f_v_f32m2:
	ID = Intrinsic::riscv_vfcvt_x_f_v_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_x_f_v_f32m4:
	ID = Intrinsic::riscv_vfcvt_x_f_v_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_x_f_v_f32m8:
	ID = Intrinsic::riscv_vfcvt_x_f_v_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_xu_v_u32m1:
	ID = Intrinsic::riscv_vfcvt_f_xu_v_u32m1;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_xu_v_u32m2:
	ID = Intrinsic::riscv_vfcvt_f_xu_v_u32m2;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_xu_v_u32m4:
	ID = Intrinsic::riscv_vfcvt_f_xu_v_u32m4;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_xu_v_u32m8:
	ID = Intrinsic::riscv_vfcvt_f_xu_v_u32m8;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_x_v_i32m1:
	ID = Intrinsic::riscv_vfcvt_f_x_v_i32m1;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_x_v_i32m2:
	ID = Intrinsic::riscv_vfcvt_f_x_v_i32m2;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_x_v_i32m4:
	ID = Intrinsic::riscv_vfcvt_f_x_v_i32m4;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_x_v_i32m8:
	ID = Intrinsic::riscv_vfcvt_f_x_v_i32m8;
	break;

//masked
    case RISCV::BI__builtin_riscv_vfcvt_xu_f_v_f32m1_m:
	ID = Intrinsic::riscv_vfcvt_xu_f_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_xu_f_v_f32m2_m:
	ID = Intrinsic::riscv_vfcvt_xu_f_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_xu_f_v_f32m4_m:
	ID = Intrinsic::riscv_vfcvt_xu_f_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_xu_f_v_f32m8_m:
	ID = Intrinsic::riscv_vfcvt_xu_f_v_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_x_f_v_f32m1_m:
	ID = Intrinsic::riscv_vfcvt_x_f_v_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_x_f_v_f32m2_m:
	ID = Intrinsic::riscv_vfcvt_x_f_v_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_x_f_v_f32m4_m:
	ID = Intrinsic::riscv_vfcvt_x_f_v_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_x_f_v_f32m8_m:
	ID = Intrinsic::riscv_vfcvt_x_f_v_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_xu_v_u32m1_m:
	ID = Intrinsic::riscv_vfcvt_f_xu_v_u32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_xu_v_u32m2_m:
	ID = Intrinsic::riscv_vfcvt_f_xu_v_u32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_xu_v_u32m4_m:
	ID = Intrinsic::riscv_vfcvt_f_xu_v_u32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_xu_v_u32m8_m:
	ID = Intrinsic::riscv_vfcvt_f_xu_v_u32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_x_v_i32m1_m:
	ID = Intrinsic::riscv_vfcvt_f_x_v_i32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_x_v_i32m2_m:
	ID = Intrinsic::riscv_vfcvt_f_x_v_i32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_x_v_i32m4_m:
	ID = Intrinsic::riscv_vfcvt_f_x_v_i32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfcvt_f_x_v_i32m8_m:
	ID = Intrinsic::riscv_vfcvt_f_x_v_i32m8_m;
	break;

//vector widening type-convert                  
    case RISCV::BI__builtin_riscv_vfwcvt_f_xu_v_u16m1:
	ID = Intrinsic::riscv_vfwcvt_f_xu_v_u16m1;
	break;
    case RISCV::BI__builtin_riscv_vfwcvt_f_xu_v_u16m2:
	ID = Intrinsic::riscv_vfwcvt_f_xu_v_u16m2;
	break;
    case RISCV::BI__builtin_riscv_vfwcvt_f_xu_v_u16m4:
	ID = Intrinsic::riscv_vfwcvt_f_xu_v_u16m4;
	break;
    case RISCV::BI__builtin_riscv_vfwcvt_f_x_v_i16m1:
	ID = Intrinsic::riscv_vfwcvt_f_x_v_i16m1;
	break;
    case RISCV::BI__builtin_riscv_vfwcvt_f_x_v_i16m2:
	ID = Intrinsic::riscv_vfwcvt_f_x_v_i16m2;
	break;
    case RISCV::BI__builtin_riscv_vfwcvt_f_x_v_i16m4:
	ID = Intrinsic::riscv_vfwcvt_f_x_v_i16m4;
	break;

//masked        
    case RISCV::BI__builtin_riscv_vfwcvt_f_xu_v_u16m1_m:
	ID = Intrinsic::riscv_vfwcvt_f_xu_v_u16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfwcvt_f_xu_v_u16m2_m:
	ID = Intrinsic::riscv_vfwcvt_f_xu_v_u16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfwcvt_f_xu_v_u16m4_m:
	ID = Intrinsic::riscv_vfwcvt_f_xu_v_u16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfwcvt_f_x_v_i16m1_m:
	ID = Intrinsic::riscv_vfwcvt_f_x_v_i16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfwcvt_f_x_v_i16m2_m:
	ID = Intrinsic::riscv_vfwcvt_f_x_v_i16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfwcvt_f_x_v_i16m4_m:
	ID = Intrinsic::riscv_vfwcvt_f_x_v_i16m4_m;
	break;

//vector narrowing type-convert  
    case RISCV::BI__builtin_riscv_vfncvt_xu_f_w_f32m2:
	ID = Intrinsic::riscv_vfncvt_xu_f_w_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfncvt_xu_f_w_f32m4:
	ID = Intrinsic::riscv_vfncvt_xu_f_w_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfncvt_xu_f_w_f32m8:
	ID = Intrinsic::riscv_vfncvt_xu_f_w_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfncvt_x_f_w_f32m2:
	ID = Intrinsic::riscv_vfncvt_x_f_w_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfncvt_x_f_w_f32m4:
	ID = Intrinsic::riscv_vfncvt_x_f_w_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfncvt_x_f_w_f32m8:
	ID = Intrinsic::riscv_vfncvt_x_f_w_f32m8;
	break;

//masked  
    case RISCV::BI__builtin_riscv_vfncvt_xu_f_w_f32m2_m:
	ID = Intrinsic::riscv_vfncvt_xu_f_w_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfncvt_xu_f_w_f32m4_m:
	ID = Intrinsic::riscv_vfncvt_xu_f_w_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfncvt_xu_f_w_f32m8_m:
	ID = Intrinsic::riscv_vfncvt_xu_f_w_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfncvt_x_f_w_f32m2_m:
	ID = Intrinsic::riscv_vfncvt_x_f_w_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfncvt_x_f_w_f32m4_m:
	ID = Intrinsic::riscv_vfncvt_x_f_w_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfncvt_x_f_w_f32m8_m:
	ID = Intrinsic::riscv_vfncvt_x_f_w_f32m8_m;
	break;

//vector integer reduction
    case RISCV::BI__builtin_riscv_vredsum_vs_i8m1:
    case RISCV::BI__builtin_riscv_vredsum_vs_u8m1:
	ID = Intrinsic::riscv_vredsum_vs_8m1;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i8m2:
    case RISCV::BI__builtin_riscv_vredsum_vs_u8m2:
	ID = Intrinsic::riscv_vredsum_vs_8m2;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i8m4:
    case RISCV::BI__builtin_riscv_vredsum_vs_u8m4:
	ID = Intrinsic::riscv_vredsum_vs_8m4;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i8m8:
    case RISCV::BI__builtin_riscv_vredsum_vs_u8m8:
	ID = Intrinsic::riscv_vredsum_vs_8m8;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i16m1:
    case RISCV::BI__builtin_riscv_vredsum_vs_u16m1:
	ID = Intrinsic::riscv_vredsum_vs_16m1;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i16m2:
    case RISCV::BI__builtin_riscv_vredsum_vs_u16m2:
	ID = Intrinsic::riscv_vredsum_vs_16m2;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i16m4:
    case RISCV::BI__builtin_riscv_vredsum_vs_u16m4:
	ID = Intrinsic::riscv_vredsum_vs_16m4;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i16m8:
    case RISCV::BI__builtin_riscv_vredsum_vs_u16m8:
	ID = Intrinsic::riscv_vredsum_vs_16m8;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i32m1:
    case RISCV::BI__builtin_riscv_vredsum_vs_u32m1:
	ID = Intrinsic::riscv_vredsum_vs_32m1;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i32m2:
    case RISCV::BI__builtin_riscv_vredsum_vs_u32m2:
	ID = Intrinsic::riscv_vredsum_vs_32m2;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i32m4:
    case RISCV::BI__builtin_riscv_vredsum_vs_u32m4:
	ID = Intrinsic::riscv_vredsum_vs_32m4;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i32m8:
    case RISCV::BI__builtin_riscv_vredsum_vs_u32m8:
	ID = Intrinsic::riscv_vredsum_vs_32m8;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i8m1:
    case RISCV::BI__builtin_riscv_vredand_vs_u8m1:
	ID = Intrinsic::riscv_vredand_vs_8m1;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i8m2:
    case RISCV::BI__builtin_riscv_vredand_vs_u8m2:
	ID = Intrinsic::riscv_vredand_vs_8m2;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i8m4:
    case RISCV::BI__builtin_riscv_vredand_vs_u8m4:
	ID = Intrinsic::riscv_vredand_vs_8m4;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i8m8:
    case RISCV::BI__builtin_riscv_vredand_vs_u8m8:
	ID = Intrinsic::riscv_vredand_vs_8m8;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i16m1:
    case RISCV::BI__builtin_riscv_vredand_vs_u16m1:
	ID = Intrinsic::riscv_vredand_vs_16m1;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i16m2:
    case RISCV::BI__builtin_riscv_vredand_vs_u16m2:
	ID = Intrinsic::riscv_vredand_vs_16m2;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i16m4:
    case RISCV::BI__builtin_riscv_vredand_vs_u16m4:
	ID = Intrinsic::riscv_vredand_vs_16m4;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i16m8:
    case RISCV::BI__builtin_riscv_vredand_vs_u16m8:
	ID = Intrinsic::riscv_vredand_vs_16m8;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i32m1:
    case RISCV::BI__builtin_riscv_vredand_vs_u32m1:
	ID = Intrinsic::riscv_vredand_vs_32m1;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i32m2:
    case RISCV::BI__builtin_riscv_vredand_vs_u32m2:
	ID = Intrinsic::riscv_vredand_vs_32m2;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i32m4:
    case RISCV::BI__builtin_riscv_vredand_vs_u32m4:
	ID = Intrinsic::riscv_vredand_vs_32m4;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i32m8:
    case RISCV::BI__builtin_riscv_vredand_vs_u32m8:
	ID = Intrinsic::riscv_vredand_vs_32m8;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i8m1:
    case RISCV::BI__builtin_riscv_vredor_vs_u8m1:
	ID = Intrinsic::riscv_vredor_vs_8m1;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i8m2:
    case RISCV::BI__builtin_riscv_vredor_vs_u8m2:
	ID = Intrinsic::riscv_vredor_vs_8m2;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i8m4:
    case RISCV::BI__builtin_riscv_vredor_vs_u8m4:
	ID = Intrinsic::riscv_vredor_vs_8m4;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i8m8:
    case RISCV::BI__builtin_riscv_vredor_vs_u8m8:
	ID = Intrinsic::riscv_vredor_vs_8m8;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i16m1:
    case RISCV::BI__builtin_riscv_vredor_vs_u16m1:
	ID = Intrinsic::riscv_vredor_vs_16m1;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i16m2:
    case RISCV::BI__builtin_riscv_vredor_vs_u16m2:
	ID = Intrinsic::riscv_vredor_vs_16m2;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i16m4:
    case RISCV::BI__builtin_riscv_vredor_vs_u16m4:
	ID = Intrinsic::riscv_vredor_vs_16m4;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i16m8:
    case RISCV::BI__builtin_riscv_vredor_vs_u16m8:
	ID = Intrinsic::riscv_vredor_vs_16m8;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i32m1:
    case RISCV::BI__builtin_riscv_vredor_vs_u32m1:
	ID = Intrinsic::riscv_vredor_vs_32m1;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i32m2:
    case RISCV::BI__builtin_riscv_vredor_vs_u32m2:
	ID = Intrinsic::riscv_vredor_vs_32m2;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i32m4:
    case RISCV::BI__builtin_riscv_vredor_vs_u32m4:
	ID = Intrinsic::riscv_vredor_vs_32m4;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i32m8:
    case RISCV::BI__builtin_riscv_vredor_vs_u32m8:
	ID = Intrinsic::riscv_vredor_vs_32m8;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i8m1:
    case RISCV::BI__builtin_riscv_vredxor_vs_u8m1:
	ID = Intrinsic::riscv_vredxor_vs_8m1;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i8m2:
    case RISCV::BI__builtin_riscv_vredxor_vs_u8m2:
	ID = Intrinsic::riscv_vredxor_vs_8m2;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i8m4:
    case RISCV::BI__builtin_riscv_vredxor_vs_u8m4:
	ID = Intrinsic::riscv_vredxor_vs_8m4;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i8m8:
    case RISCV::BI__builtin_riscv_vredxor_vs_u8m8:
	ID = Intrinsic::riscv_vredxor_vs_8m8;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i16m1:
    case RISCV::BI__builtin_riscv_vredxor_vs_u16m1:
	ID = Intrinsic::riscv_vredxor_vs_16m1;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i16m2:
    case RISCV::BI__builtin_riscv_vredxor_vs_u16m2:
	ID = Intrinsic::riscv_vredxor_vs_16m2;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i16m4:
    case RISCV::BI__builtin_riscv_vredxor_vs_u16m4:
	ID = Intrinsic::riscv_vredxor_vs_16m4;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i16m8:
    case RISCV::BI__builtin_riscv_vredxor_vs_u16m8:
	ID = Intrinsic::riscv_vredxor_vs_16m8;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i32m1:
    case RISCV::BI__builtin_riscv_vredxor_vs_u32m1:
	ID = Intrinsic::riscv_vredxor_vs_32m1;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i32m2:
    case RISCV::BI__builtin_riscv_vredxor_vs_u32m2:
	ID = Intrinsic::riscv_vredxor_vs_32m2;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i32m4:
    case RISCV::BI__builtin_riscv_vredxor_vs_u32m4:
	ID = Intrinsic::riscv_vredxor_vs_32m4;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i32m8:
    case RISCV::BI__builtin_riscv_vredxor_vs_u32m8:
	ID = Intrinsic::riscv_vredxor_vs_32m8;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u8m1:
	ID = Intrinsic::riscv_vredmaxu_vs_u8m1;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u8m2:
	ID = Intrinsic::riscv_vredmaxu_vs_u8m2;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u8m4:
	ID = Intrinsic::riscv_vredmaxu_vs_u8m4;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u8m8:
	ID = Intrinsic::riscv_vredmaxu_vs_u8m8;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u16m1:
	ID = Intrinsic::riscv_vredmaxu_vs_u16m1;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u16m2:
	ID = Intrinsic::riscv_vredmaxu_vs_u16m2;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u16m4:
	ID = Intrinsic::riscv_vredmaxu_vs_u16m4;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u16m8:
	ID = Intrinsic::riscv_vredmaxu_vs_u16m8;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u32m1:
	ID = Intrinsic::riscv_vredmaxu_vs_u32m1;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u32m2:
	ID = Intrinsic::riscv_vredmaxu_vs_u32m2;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u32m4:
	ID = Intrinsic::riscv_vredmaxu_vs_u32m4;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u32m8:
	ID = Intrinsic::riscv_vredmaxu_vs_u32m8;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i8m1:
	ID = Intrinsic::riscv_vredmax_vs_i8m1;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i8m2:
	ID = Intrinsic::riscv_vredmax_vs_i8m2;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i8m4:
	ID = Intrinsic::riscv_vredmax_vs_i8m4;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i8m8:
	ID = Intrinsic::riscv_vredmax_vs_i8m8;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i16m1:
	ID = Intrinsic::riscv_vredmax_vs_i16m1;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i16m2:
	ID = Intrinsic::riscv_vredmax_vs_i16m2;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i16m4:
	ID = Intrinsic::riscv_vredmax_vs_i16m4;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i16m8:
	ID = Intrinsic::riscv_vredmax_vs_i16m8;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i32m1:
	ID = Intrinsic::riscv_vredmax_vs_i32m1;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i32m2:
	ID = Intrinsic::riscv_vredmax_vs_i32m2;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i32m4:
	ID = Intrinsic::riscv_vredmax_vs_i32m4;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i32m8:
	ID = Intrinsic::riscv_vredmax_vs_i32m8;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u8m1:
	ID = Intrinsic::riscv_vredminu_vs_u8m1;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u8m2:
	ID = Intrinsic::riscv_vredminu_vs_u8m2;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u8m4:
	ID = Intrinsic::riscv_vredminu_vs_u8m4;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u8m8:
	ID = Intrinsic::riscv_vredminu_vs_u8m8;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u16m1:
	ID = Intrinsic::riscv_vredminu_vs_u16m1;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u16m2:
	ID = Intrinsic::riscv_vredminu_vs_u16m2;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u16m4:
	ID = Intrinsic::riscv_vredminu_vs_u16m4;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u16m8:
	ID = Intrinsic::riscv_vredminu_vs_u16m8;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u32m1:
	ID = Intrinsic::riscv_vredminu_vs_u32m1;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u32m2:
	ID = Intrinsic::riscv_vredminu_vs_u32m2;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u32m4:
	ID = Intrinsic::riscv_vredminu_vs_u32m4;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u32m8:
	ID = Intrinsic::riscv_vredminu_vs_u32m8;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i8m1:
	ID = Intrinsic::riscv_vredmin_vs_i8m1;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i8m2:
	ID = Intrinsic::riscv_vredmin_vs_i8m2;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i8m4:
	ID = Intrinsic::riscv_vredmin_vs_i8m4;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i8m8:
	ID = Intrinsic::riscv_vredmin_vs_i8m8;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i16m1:
	ID = Intrinsic::riscv_vredmin_vs_i16m1;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i16m2:
	ID = Intrinsic::riscv_vredmin_vs_i16m2;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i16m4:
	ID = Intrinsic::riscv_vredmin_vs_i16m4;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i16m8:
	ID = Intrinsic::riscv_vredmin_vs_i16m8;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i32m1:
	ID = Intrinsic::riscv_vredmin_vs_i32m1;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i32m2:
	ID = Intrinsic::riscv_vredmin_vs_i32m2;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i32m4:
	ID = Intrinsic::riscv_vredmin_vs_i32m4;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i32m8:
	ID = Intrinsic::riscv_vredmin_vs_i32m8;
	break;

//masked
    case RISCV::BI__builtin_riscv_vredsum_vs_i8m1_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u8m1_m:
	ID = Intrinsic::riscv_vredsum_vs_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i8m2_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u8m2_m:
	ID = Intrinsic::riscv_vredsum_vs_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i8m4_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u8m4_m:
	ID = Intrinsic::riscv_vredsum_vs_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i8m8_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u8m8_m:
	ID = Intrinsic::riscv_vredsum_vs_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i16m1_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u16m1_m:
	ID = Intrinsic::riscv_vredsum_vs_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i16m2_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u16m2_m:
	ID = Intrinsic::riscv_vredsum_vs_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i16m4_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u16m4_m:
	ID = Intrinsic::riscv_vredsum_vs_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i16m8_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u16m8_m:
	ID = Intrinsic::riscv_vredsum_vs_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i32m1_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u32m1_m:
	ID = Intrinsic::riscv_vredsum_vs_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i32m2_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u32m2_m:
	ID = Intrinsic::riscv_vredsum_vs_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i32m4_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u32m4_m:
	ID = Intrinsic::riscv_vredsum_vs_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredsum_vs_i32m8_m:
    case RISCV::BI__builtin_riscv_vredsum_vs_u32m8_m:
	ID = Intrinsic::riscv_vredsum_vs_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i8m1_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u8m1_m:
	ID = Intrinsic::riscv_vredand_vs_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i8m2_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u8m2_m:
	ID = Intrinsic::riscv_vredand_vs_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i8m4_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u8m4_m:
	ID = Intrinsic::riscv_vredand_vs_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i8m8_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u8m8_m:
	ID = Intrinsic::riscv_vredand_vs_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i16m1_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u16m1_m:
	ID = Intrinsic::riscv_vredand_vs_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i16m2_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u16m2_m:
	ID = Intrinsic::riscv_vredand_vs_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i16m4_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u16m4_m:
	ID = Intrinsic::riscv_vredand_vs_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i16m8_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u16m8_m:
	ID = Intrinsic::riscv_vredand_vs_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i32m1_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u32m1_m:
	ID = Intrinsic::riscv_vredand_vs_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i32m2_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u32m2_m:
	ID = Intrinsic::riscv_vredand_vs_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i32m4_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u32m4_m:
	ID = Intrinsic::riscv_vredand_vs_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredand_vs_i32m8_m:
    case RISCV::BI__builtin_riscv_vredand_vs_u32m8_m:
	ID = Intrinsic::riscv_vredand_vs_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i8m1_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u8m1_m:
	ID = Intrinsic::riscv_vredor_vs_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i8m2_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u8m2_m:
	ID = Intrinsic::riscv_vredor_vs_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i8m4_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u8m4_m:
	ID = Intrinsic::riscv_vredor_vs_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i8m8_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u8m8_m:
	ID = Intrinsic::riscv_vredor_vs_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i16m1_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u16m1_m:
	ID = Intrinsic::riscv_vredor_vs_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i16m2_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u16m2_m:
	ID = Intrinsic::riscv_vredor_vs_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i16m4_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u16m4_m:
	ID = Intrinsic::riscv_vredor_vs_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i16m8_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u16m8_m:
	ID = Intrinsic::riscv_vredor_vs_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i32m1_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u32m1_m:
	ID = Intrinsic::riscv_vredor_vs_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i32m2_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u32m2_m:
	ID = Intrinsic::riscv_vredor_vs_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i32m4_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u32m4_m:
	ID = Intrinsic::riscv_vredor_vs_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredor_vs_i32m8_m:
    case RISCV::BI__builtin_riscv_vredor_vs_u32m8_m:
	ID = Intrinsic::riscv_vredor_vs_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i8m1_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u8m1_m:
	ID = Intrinsic::riscv_vredxor_vs_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i8m2_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u8m2_m:
	ID = Intrinsic::riscv_vredxor_vs_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i8m4_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u8m4_m:
	ID = Intrinsic::riscv_vredxor_vs_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i8m8_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u8m8_m:
	ID = Intrinsic::riscv_vredxor_vs_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i16m1_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u16m1_m:
	ID = Intrinsic::riscv_vredxor_vs_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i16m2_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u16m2_m:
	ID = Intrinsic::riscv_vredxor_vs_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i16m4_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u16m4_m:
	ID = Intrinsic::riscv_vredxor_vs_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i16m8_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u16m8_m:
	ID = Intrinsic::riscv_vredxor_vs_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i32m1_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u32m1_m:
	ID = Intrinsic::riscv_vredxor_vs_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i32m2_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u32m2_m:
	ID = Intrinsic::riscv_vredxor_vs_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i32m4_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u32m4_m:
	ID = Intrinsic::riscv_vredxor_vs_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredxor_vs_i32m8_m:
    case RISCV::BI__builtin_riscv_vredxor_vs_u32m8_m:
	ID = Intrinsic::riscv_vredxor_vs_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u8m1_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u8m2_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u8m4_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u8m8_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u16m1_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u16m2_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u16m4_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u16m8_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u32m1_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u32m2_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u32m4_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredmaxu_vs_u32m8_m:
	ID = Intrinsic::riscv_vredmaxu_vs_u32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i8m1_m:
	ID = Intrinsic::riscv_vredmax_vs_i8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i8m2_m:
	ID = Intrinsic::riscv_vredmax_vs_i8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i8m4_m:
	ID = Intrinsic::riscv_vredmax_vs_i8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i8m8_m:
	ID = Intrinsic::riscv_vredmax_vs_i8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i16m1_m:
	ID = Intrinsic::riscv_vredmax_vs_i16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i16m2_m:
	ID = Intrinsic::riscv_vredmax_vs_i16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i16m4_m:
	ID = Intrinsic::riscv_vredmax_vs_i16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i16m8_m:
	ID = Intrinsic::riscv_vredmax_vs_i16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i32m1_m:
	ID = Intrinsic::riscv_vredmax_vs_i32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i32m2_m:
	ID = Intrinsic::riscv_vredmax_vs_i32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i32m4_m:
	ID = Intrinsic::riscv_vredmax_vs_i32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredmax_vs_i32m8_m:
	ID = Intrinsic::riscv_vredmax_vs_i32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u8m1_m:
	ID = Intrinsic::riscv_vredminu_vs_u8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u8m2_m:
	ID = Intrinsic::riscv_vredminu_vs_u8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u8m4_m:
	ID = Intrinsic::riscv_vredminu_vs_u8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u8m8_m:
	ID = Intrinsic::riscv_vredminu_vs_u8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u16m1_m:
	ID = Intrinsic::riscv_vredminu_vs_u16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u16m2_m:
	ID = Intrinsic::riscv_vredminu_vs_u16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u16m4_m:
	ID = Intrinsic::riscv_vredminu_vs_u16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u16m8_m:
	ID = Intrinsic::riscv_vredminu_vs_u16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u32m1_m:
	ID = Intrinsic::riscv_vredminu_vs_u32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u32m2_m:
	ID = Intrinsic::riscv_vredminu_vs_u32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u32m4_m:
	ID = Intrinsic::riscv_vredminu_vs_u32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredminu_vs_u32m8_m:
	ID = Intrinsic::riscv_vredminu_vs_u32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i8m1_m:
	ID = Intrinsic::riscv_vredmin_vs_i8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i8m2_m:
	ID = Intrinsic::riscv_vredmin_vs_i8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i8m4_m:
	ID = Intrinsic::riscv_vredmin_vs_i8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i8m8_m:
	ID = Intrinsic::riscv_vredmin_vs_i8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i16m1_m:
	ID = Intrinsic::riscv_vredmin_vs_i16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i16m2_m:
	ID = Intrinsic::riscv_vredmin_vs_i16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i16m4_m:
	ID = Intrinsic::riscv_vredmin_vs_i16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i16m8_m:
	ID = Intrinsic::riscv_vredmin_vs_i16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i32m1_m:
	ID = Intrinsic::riscv_vredmin_vs_i32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i32m2_m:
	ID = Intrinsic::riscv_vredmin_vs_i32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i32m4_m:
	ID = Intrinsic::riscv_vredmin_vs_i32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vredmin_vs_i32m8_m:
	ID = Intrinsic::riscv_vredmin_vs_i32m8_m;
	break;

//vector  widening integer reduction                    
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u8m1:
	ID = Intrinsic::riscv_vwredsumu_vs_u8m1;
	break;
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u8m2:
	ID = Intrinsic::riscv_vwredsumu_vs_u8m2;
	break;
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u8m4:
	ID = Intrinsic::riscv_vwredsumu_vs_u8m4;
	break;
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u16m1:
	ID = Intrinsic::riscv_vwredsumu_vs_u16m1;
	break;
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u16m2:
	ID = Intrinsic::riscv_vwredsumu_vs_u16m2;
	break;
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u16m4:
	ID = Intrinsic::riscv_vwredsumu_vs_u16m4;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i8m1:
	ID = Intrinsic::riscv_vwredsum_vs_i8m1;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i8m2:
	ID = Intrinsic::riscv_vwredsum_vs_i8m2;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i8m4:
	ID = Intrinsic::riscv_vwredsum_vs_i8m4;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i16m1:
	ID = Intrinsic::riscv_vwredsum_vs_i16m1;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i16m2:
	ID = Intrinsic::riscv_vwredsum_vs_i16m2;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i16m4:
	ID = Intrinsic::riscv_vwredsum_vs_i16m4;
	break;

//masked     
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u8m1_m:
	ID = Intrinsic::riscv_vwredsumu_vs_u8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u8m2_m:
	ID = Intrinsic::riscv_vwredsumu_vs_u8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u8m4_m:
	ID = Intrinsic::riscv_vwredsumu_vs_u8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u16m1_m:
	ID = Intrinsic::riscv_vwredsumu_vs_u16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u16m2_m:
	ID = Intrinsic::riscv_vwredsumu_vs_u16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsumu_vs_u16m4_m:
	ID = Intrinsic::riscv_vwredsumu_vs_u16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i8m1_m:
	ID = Intrinsic::riscv_vwredsum_vs_i8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i8m2_m:
	ID = Intrinsic::riscv_vwredsum_vs_i8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i8m4_m:
	ID = Intrinsic::riscv_vwredsum_vs_i8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i16m1_m:
	ID = Intrinsic::riscv_vwredsum_vs_i16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i16m2_m:
	ID = Intrinsic::riscv_vwredsum_vs_i16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vwredsum_vs_i16m4_m:
	ID = Intrinsic::riscv_vwredsum_vs_i16m4_m;
	break;

//vector floatint reduction  
    case RISCV::BI__builtin_riscv_vfredosum_vs_f32m1:
	ID = Intrinsic::riscv_vfredosum_vs_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfredosum_vs_f32m2:
	ID = Intrinsic::riscv_vfredosum_vs_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfredosum_vs_f32m4:
	ID = Intrinsic::riscv_vfredosum_vs_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfredosum_vs_f32m8:
	ID = Intrinsic::riscv_vfredosum_vs_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfredsum_vs_f32m1:
	ID = Intrinsic::riscv_vfredsum_vs_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfredsum_vs_f32m2:
	ID = Intrinsic::riscv_vfredsum_vs_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfredsum_vs_f32m4:
	ID = Intrinsic::riscv_vfredsum_vs_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfredsum_vs_f32m8:
	ID = Intrinsic::riscv_vfredsum_vs_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfredmax_vs_f32m1:
	ID = Intrinsic::riscv_vfredmax_vs_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfredmax_vs_f32m2:
	ID = Intrinsic::riscv_vfredmax_vs_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfredmax_vs_f32m4:
	ID = Intrinsic::riscv_vfredmax_vs_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfredmax_vs_f32m8:
	ID = Intrinsic::riscv_vfredmax_vs_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfredmin_vs_f32m1:
	ID = Intrinsic::riscv_vfredmin_vs_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfredmin_vs_f32m2:
	ID = Intrinsic::riscv_vfredmin_vs_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfredmin_vs_f32m4:
	ID = Intrinsic::riscv_vfredmin_vs_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfredmin_vs_f32m8:
	ID = Intrinsic::riscv_vfredmin_vs_f32m8;
	break;

//masked      
    case RISCV::BI__builtin_riscv_vfredosum_vs_f32m1_m:
	ID = Intrinsic::riscv_vfredosum_vs_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfredosum_vs_f32m2_m:
	ID = Intrinsic::riscv_vfredosum_vs_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfredosum_vs_f32m4_m:
	ID = Intrinsic::riscv_vfredosum_vs_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfredosum_vs_f32m8_m:
	ID = Intrinsic::riscv_vfredosum_vs_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfredsum_vs_f32m1_m:
	ID = Intrinsic::riscv_vfredsum_vs_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfredsum_vs_f32m2_m:
	ID = Intrinsic::riscv_vfredsum_vs_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfredsum_vs_f32m4_m:
	ID = Intrinsic::riscv_vfredsum_vs_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfredsum_vs_f32m8_m:
	ID = Intrinsic::riscv_vfredsum_vs_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfredmax_vs_f32m1_m:
	ID = Intrinsic::riscv_vfredmax_vs_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfredmax_vs_f32m2_m:
	ID = Intrinsic::riscv_vfredmax_vs_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfredmax_vs_f32m4_m:
	ID = Intrinsic::riscv_vfredmax_vs_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfredmax_vs_f32m8_m:
	ID = Intrinsic::riscv_vfredmax_vs_f32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vfredmin_vs_f32m1_m:
	ID = Intrinsic::riscv_vfredmin_vs_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vfredmin_vs_f32m2_m:
	ID = Intrinsic::riscv_vfredmin_vs_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vfredmin_vs_f32m4_m:
	ID = Intrinsic::riscv_vfredmin_vs_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vfredmin_vs_f32m8_m:
	ID = Intrinsic::riscv_vfredmin_vs_f32m8_m;
	break;

//vector  mask
    case RISCV::BI__builtin_riscv_vmand_mm:
	ID = Intrinsic::riscv_vmand_mm;
	break;
    case RISCV::BI__builtin_riscv_vmnand_mm:
	ID = Intrinsic::riscv_vmnand_mm;
	break;
    case RISCV::BI__builtin_riscv_vmandnot_mm:
	ID = Intrinsic::riscv_vmandnot_mm;
	break;
    case RISCV::BI__builtin_riscv_vmxor_mm:
	ID = Intrinsic::riscv_vmxor_mm;
	break;
    case RISCV::BI__builtin_riscv_vmor_mm:
	ID = Intrinsic::riscv_vmor_mm;
	break;
    case RISCV::BI__builtin_riscv_vmnor_mm:
	ID = Intrinsic::riscv_vmnor_mm;
	break;
    case RISCV::BI__builtin_riscv_vmornot_mm:
	ID = Intrinsic::riscv_vmornot_mm;
	break;
    case RISCV::BI__builtin_riscv_vmxnor_mm:
	ID = Intrinsic::riscv_vmxnor_mm;
	break;
    case RISCV::BI__builtin_riscv_vpopc_m:
	ID = Intrinsic::riscv_vpopc_m;
	break;
    case RISCV::BI__builtin_riscv_vpopc_m_m:
	ID = Intrinsic::riscv_vpopc_m_m;
	break;
    case RISCV::BI__builtin_riscv_vfirst_m:
	ID = Intrinsic::riscv_vfirst_m;
	break;
    case RISCV::BI__builtin_riscv_vfirst_m_m:
	ID = Intrinsic::riscv_vfirst_m_m;
	break;
    case RISCV::BI__builtin_riscv_vmsbf_m:
	ID = Intrinsic::riscv_vmsbf_m;
	break;
    case RISCV::BI__builtin_riscv_vmsbf_m_m:
	ID = Intrinsic::riscv_vmsbf_m_m;
	break;
    case RISCV::BI__builtin_riscv_vmsif_m:
	ID = Intrinsic::riscv_vmsif_m;
	break;
    case RISCV::BI__builtin_riscv_vmsif_m_m:
	ID = Intrinsic::riscv_vmsif_m_m;
	break;
    case RISCV::BI__builtin_riscv_vmsof_m:
	ID = Intrinsic::riscv_vmsof_m;
	break;
    case RISCV::BI__builtin_riscv_vmsof_m_m:
	ID = Intrinsic::riscv_vmsof_m_m;
	break;
    case RISCV::BI__builtin_riscv_viota_m:
	ID = Intrinsic::riscv_viota_m;
	break;
    case RISCV::BI__builtin_riscv_viota_m_m:
	ID = Intrinsic::riscv_viota_m_m;
	break;

//vid
    case RISCV::BI__builtin_riscv_vid_v_u8m1:
	ID = Intrinsic::riscv_vid_v_u8m1;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u8m2:
	ID = Intrinsic::riscv_vid_v_u8m2;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u8m4:
	ID = Intrinsic::riscv_vid_v_u8m4;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u8m8:
	ID = Intrinsic::riscv_vid_v_u8m8;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u16m1:
	ID = Intrinsic::riscv_vid_v_u16m1;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u16m2:
	ID = Intrinsic::riscv_vid_v_u16m2;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u16m4:
	ID = Intrinsic::riscv_vid_v_u16m4;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u16m8:
	ID = Intrinsic::riscv_vid_v_u16m8;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u32m1:
	ID = Intrinsic::riscv_vid_v_u32m1;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u32m2:
	ID = Intrinsic::riscv_vid_v_u32m2;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u32m4:
	ID = Intrinsic::riscv_vid_v_u32m4;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u32m8:
	ID = Intrinsic::riscv_vid_v_u32m8;
	break;

//masked
    case RISCV::BI__builtin_riscv_vid_v_u8m1_m:
	ID = Intrinsic::riscv_vid_v_u8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u8m2_m:
	ID = Intrinsic::riscv_vid_v_u8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u8m4_m:
	ID = Intrinsic::riscv_vid_v_u8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u8m8_m:
	ID = Intrinsic::riscv_vid_v_u8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u16m1_m:
	ID = Intrinsic::riscv_vid_v_u16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u16m2_m:
	ID = Intrinsic::riscv_vid_v_u16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u16m4_m:
	ID = Intrinsic::riscv_vid_v_u16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u16m8_m:
	ID = Intrinsic::riscv_vid_v_u16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u32m1_m:
	ID = Intrinsic::riscv_vid_v_u32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u32m2_m:
	ID = Intrinsic::riscv_vid_v_u32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u32m4_m:
	ID = Intrinsic::riscv_vid_v_u32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vid_v_u32m8_m:
	ID = Intrinsic::riscv_vid_v_u32m8_m;
	break;

//vector vfmv      
    case RISCV::BI__builtin_riscv_vfmv_f_s_f32m1:
	ID = Intrinsic::riscv_vfmv_f_s_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmv_f_s_f32m2:
	ID = Intrinsic::riscv_vfmv_f_s_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmv_f_s_f32m4:
	ID = Intrinsic::riscv_vfmv_f_s_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmv_f_s_f32m8:
	ID = Intrinsic::riscv_vfmv_f_s_f32m8;
	break;
    case RISCV::BI__builtin_riscv_vfmv_s_f_f32m1:
	ID = Intrinsic::riscv_vfmv_s_f_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vfmv_s_f_f32m2:
	ID = Intrinsic::riscv_vfmv_s_f_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vfmv_s_f_f32m4:
	ID = Intrinsic::riscv_vfmv_s_f_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vfmv_s_f_f32m8:
	ID = Intrinsic::riscv_vfmv_s_f_f32m8;
	break;

//vector vslideup.vx     
    case RISCV::BI__builtin_riscv_vslideup_vx_i8m1:
    case RISCV::BI__builtin_riscv_vslideup_vx_u8m1:
	ID = Intrinsic::riscv_vslideup_vx_8m1;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i8m2:
    case RISCV::BI__builtin_riscv_vslideup_vx_u8m2:
	ID = Intrinsic::riscv_vslideup_vx_8m2;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i8m4:
    case RISCV::BI__builtin_riscv_vslideup_vx_u8m4:
	ID = Intrinsic::riscv_vslideup_vx_8m4;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i8m8:
    case RISCV::BI__builtin_riscv_vslideup_vx_u8m8:
	ID = Intrinsic::riscv_vslideup_vx_8m8;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i16m1:
    case RISCV::BI__builtin_riscv_vslideup_vx_u16m1:
	ID = Intrinsic::riscv_vslideup_vx_16m1;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i16m2:
    case RISCV::BI__builtin_riscv_vslideup_vx_u16m2:
	ID = Intrinsic::riscv_vslideup_vx_16m2;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i16m4:
    case RISCV::BI__builtin_riscv_vslideup_vx_u16m4:
	ID = Intrinsic::riscv_vslideup_vx_16m4;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i16m8:
    case RISCV::BI__builtin_riscv_vslideup_vx_u16m8:
	ID = Intrinsic::riscv_vslideup_vx_16m8;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i32m1:
    case RISCV::BI__builtin_riscv_vslideup_vx_u32m1:
	ID = Intrinsic::riscv_vslideup_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i32m2:
    case RISCV::BI__builtin_riscv_vslideup_vx_u32m2:
	ID = Intrinsic::riscv_vslideup_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i32m4:
    case RISCV::BI__builtin_riscv_vslideup_vx_u32m4:
	ID = Intrinsic::riscv_vslideup_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i32m8:
    case RISCV::BI__builtin_riscv_vslideup_vx_u32m8:
	ID = Intrinsic::riscv_vslideup_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_f32m1:
	ID = Intrinsic::riscv_vslideup_vx_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_f32m2:
	ID = Intrinsic::riscv_vslideup_vx_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_f32m4:
	ID = Intrinsic::riscv_vslideup_vx_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_f32m8:
	ID = Intrinsic::riscv_vslideup_vx_f32m8;
	break;

//masked                 
    case RISCV::BI__builtin_riscv_vslideup_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u8m1_m:
	ID = Intrinsic::riscv_vslideup_vx_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u8m2_m:
	ID = Intrinsic::riscv_vslideup_vx_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u8m4_m:
	ID = Intrinsic::riscv_vslideup_vx_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u8m8_m:
	ID = Intrinsic::riscv_vslideup_vx_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u16m1_m:
	ID = Intrinsic::riscv_vslideup_vx_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u16m2_m:
	ID = Intrinsic::riscv_vslideup_vx_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u16m4_m:
	ID = Intrinsic::riscv_vslideup_vx_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u16m8_m:
	ID = Intrinsic::riscv_vslideup_vx_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u32m1_m:
	ID = Intrinsic::riscv_vslideup_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u32m2_m:
	ID = Intrinsic::riscv_vslideup_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u32m4_m:
	ID = Intrinsic::riscv_vslideup_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vslideup_vx_u32m8_m:
	ID = Intrinsic::riscv_vslideup_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_f32m1_m:
	ID = Intrinsic::riscv_vslideup_vx_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_f32m2_m:
	ID = Intrinsic::riscv_vslideup_vx_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_f32m4_m:
	ID = Intrinsic::riscv_vslideup_vx_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vx_f32m8_m:
	ID = Intrinsic::riscv_vslideup_vx_f32m8_m;
	break;

//vslideup.vi    
    case RISCV::BI__builtin_riscv_vslideup_vi_i8m1:
    case RISCV::BI__builtin_riscv_vslideup_vi_u8m1:
	ID = Intrinsic::riscv_vslideup_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i8m2:
    case RISCV::BI__builtin_riscv_vslideup_vi_u8m2:
	ID = Intrinsic::riscv_vslideup_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i8m4:
    case RISCV::BI__builtin_riscv_vslideup_vi_u8m4:
	ID = Intrinsic::riscv_vslideup_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i8m8:
    case RISCV::BI__builtin_riscv_vslideup_vi_u8m8:
	ID = Intrinsic::riscv_vslideup_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i16m1:
    case RISCV::BI__builtin_riscv_vslideup_vi_u16m1:
	ID = Intrinsic::riscv_vslideup_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i16m2:
    case RISCV::BI__builtin_riscv_vslideup_vi_u16m2:
	ID = Intrinsic::riscv_vslideup_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i16m4:
    case RISCV::BI__builtin_riscv_vslideup_vi_u16m4:
	ID = Intrinsic::riscv_vslideup_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i16m8:
    case RISCV::BI__builtin_riscv_vslideup_vi_u16m8:
	ID = Intrinsic::riscv_vslideup_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i32m1:
    case RISCV::BI__builtin_riscv_vslideup_vi_u32m1:
	ID = Intrinsic::riscv_vslideup_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i32m2:
    case RISCV::BI__builtin_riscv_vslideup_vi_u32m2:
	ID = Intrinsic::riscv_vslideup_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i32m4:
    case RISCV::BI__builtin_riscv_vslideup_vi_u32m4:
	ID = Intrinsic::riscv_vslideup_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i32m8:
    case RISCV::BI__builtin_riscv_vslideup_vi_u32m8:
	ID = Intrinsic::riscv_vslideup_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_f32m1:
	ID = Intrinsic::riscv_vslideup_vi_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_f32m2:
	ID = Intrinsic::riscv_vslideup_vi_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_f32m4:
	ID = Intrinsic::riscv_vslideup_vi_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_f32m8:
	ID = Intrinsic::riscv_vslideup_vi_f32m8;
	break;
//masked                 
    case RISCV::BI__builtin_riscv_vslideup_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u8m1_m:
	ID = Intrinsic::riscv_vslideup_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u8m2_m:
	ID = Intrinsic::riscv_vslideup_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u8m4_m:
	ID = Intrinsic::riscv_vslideup_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u8m8_m:
	ID = Intrinsic::riscv_vslideup_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u16m1_m:
	ID = Intrinsic::riscv_vslideup_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u16m2_m:
	ID = Intrinsic::riscv_vslideup_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u16m4_m:
	ID = Intrinsic::riscv_vslideup_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u16m8_m:
	ID = Intrinsic::riscv_vslideup_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u32m1_m:
	ID = Intrinsic::riscv_vslideup_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u32m2_m:
	ID = Intrinsic::riscv_vslideup_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u32m4_m:
	ID = Intrinsic::riscv_vslideup_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vslideup_vi_u32m8_m:
	ID = Intrinsic::riscv_vslideup_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_f32m1_m:
	ID = Intrinsic::riscv_vslideup_vi_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_f32m2_m:
	ID = Intrinsic::riscv_vslideup_vi_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_f32m4_m:
	ID = Intrinsic::riscv_vslideup_vi_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslideup_vi_f32m8_m:
	ID = Intrinsic::riscv_vslideup_vi_f32m8_m;
	break;

//vslidedown
    case RISCV::BI__builtin_riscv_vslidedown_vx_i8m1:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u8m1:
	ID = Intrinsic::riscv_vslidedown_vx_8m1;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i8m2:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u8m2:
	ID = Intrinsic::riscv_vslidedown_vx_8m2;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i8m4:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u8m4:
	ID = Intrinsic::riscv_vslidedown_vx_8m4;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i8m8:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u8m8:
	ID = Intrinsic::riscv_vslidedown_vx_8m8;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i16m1:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u16m1:
	ID = Intrinsic::riscv_vslidedown_vx_16m1;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i16m2:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u16m2:
	ID = Intrinsic::riscv_vslidedown_vx_16m2;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i16m4:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u16m4:
	ID = Intrinsic::riscv_vslidedown_vx_16m4;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i16m8:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u16m8:
	ID = Intrinsic::riscv_vslidedown_vx_16m8;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i32m1:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u32m1:
	ID = Intrinsic::riscv_vslidedown_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i32m2:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u32m2:
	ID = Intrinsic::riscv_vslidedown_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i32m4:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u32m4:
	ID = Intrinsic::riscv_vslidedown_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i32m8:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u32m8:
	ID = Intrinsic::riscv_vslidedown_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_f32m1:
	ID = Intrinsic::riscv_vslidedown_vx_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_f32m2:
	ID = Intrinsic::riscv_vslidedown_vx_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_f32m4:
	ID = Intrinsic::riscv_vslidedown_vx_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_f32m8:
	ID = Intrinsic::riscv_vslidedown_vx_f32m8;
	break;

//masked                 
    case RISCV::BI__builtin_riscv_vslidedown_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u8m1_m:
	ID = Intrinsic::riscv_vslidedown_vx_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u8m2_m:
	ID = Intrinsic::riscv_vslidedown_vx_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u8m4_m:
	ID = Intrinsic::riscv_vslidedown_vx_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u8m8_m:
	ID = Intrinsic::riscv_vslidedown_vx_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u16m1_m:
	ID = Intrinsic::riscv_vslidedown_vx_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u16m2_m:
	ID = Intrinsic::riscv_vslidedown_vx_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u16m4_m:
	ID = Intrinsic::riscv_vslidedown_vx_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u16m8_m:
	ID = Intrinsic::riscv_vslidedown_vx_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u32m1_m:
	ID = Intrinsic::riscv_vslidedown_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u32m2_m:
	ID = Intrinsic::riscv_vslidedown_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u32m4_m:
	ID = Intrinsic::riscv_vslidedown_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vslidedown_vx_u32m8_m:
	ID = Intrinsic::riscv_vslidedown_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_f32m1_m:
	ID = Intrinsic::riscv_vslidedown_vx_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_f32m2_m:
	ID = Intrinsic::riscv_vslidedown_vx_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_f32m4_m:
	ID = Intrinsic::riscv_vslidedown_vx_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vx_f32m8_m:
	ID = Intrinsic::riscv_vslidedown_vx_f32m8_m;
	break;

//vector vslidedown.vi
    case RISCV::BI__builtin_riscv_vslidedown_vi_i8m1:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u8m1:
	ID = Intrinsic::riscv_vslidedown_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i8m2:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u8m2:
	ID = Intrinsic::riscv_vslidedown_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i8m4:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u8m4:
	ID = Intrinsic::riscv_vslidedown_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i8m8:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u8m8:
	ID = Intrinsic::riscv_vslidedown_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i16m1:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u16m1:
	ID = Intrinsic::riscv_vslidedown_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i16m2:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u16m2:
	ID = Intrinsic::riscv_vslidedown_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i16m4:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u16m4:
	ID = Intrinsic::riscv_vslidedown_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i16m8:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u16m8:
	ID = Intrinsic::riscv_vslidedown_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i32m1:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u32m1:
	ID = Intrinsic::riscv_vslidedown_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i32m2:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u32m2:
	ID = Intrinsic::riscv_vslidedown_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i32m4:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u32m4:
	ID = Intrinsic::riscv_vslidedown_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i32m8:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u32m8:
	ID = Intrinsic::riscv_vslidedown_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_f32m1:
	ID = Intrinsic::riscv_vslidedown_vi_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_f32m2:
	ID = Intrinsic::riscv_vslidedown_vi_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_f32m4:
	ID = Intrinsic::riscv_vslidedown_vi_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_f32m8:
	ID = Intrinsic::riscv_vslidedown_vi_f32m8;
	break;

//masked                 
    case RISCV::BI__builtin_riscv_vslidedown_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u8m1_m:
	ID = Intrinsic::riscv_vslidedown_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u8m2_m:
	ID = Intrinsic::riscv_vslidedown_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u8m4_m:
	ID = Intrinsic::riscv_vslidedown_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u8m8_m:
	ID = Intrinsic::riscv_vslidedown_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u16m1_m:
	ID = Intrinsic::riscv_vslidedown_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u16m2_m:
	ID = Intrinsic::riscv_vslidedown_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u16m4_m:
	ID = Intrinsic::riscv_vslidedown_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u16m8_m:
	ID = Intrinsic::riscv_vslidedown_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u32m1_m:
	ID = Intrinsic::riscv_vslidedown_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u32m2_m:
	ID = Intrinsic::riscv_vslidedown_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u32m4_m:
	ID = Intrinsic::riscv_vslidedown_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vslidedown_vi_u32m8_m:
	ID = Intrinsic::riscv_vslidedown_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_f32m1_m:
	ID = Intrinsic::riscv_vslidedown_vi_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_f32m2_m:
	ID = Intrinsic::riscv_vslidedown_vi_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_f32m4_m:
	ID = Intrinsic::riscv_vslidedown_vi_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslidedown_vi_f32m8_m:
	ID = Intrinsic::riscv_vslidedown_vi_f32m8_m;
	break;

//vector vslide1up.vx
    case RISCV::BI__builtin_riscv_vslide1up_vx_i8m1:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u8m1:
	ID = Intrinsic::riscv_vslide1up_vx_8m1;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i8m2:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u8m2:
	ID = Intrinsic::riscv_vslide1up_vx_8m2;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i8m4:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u8m4:
	ID = Intrinsic::riscv_vslide1up_vx_8m4;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i8m8:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u8m8:
	ID = Intrinsic::riscv_vslide1up_vx_8m8;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i16m1:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u16m1:
	ID = Intrinsic::riscv_vslide1up_vx_16m1;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i16m2:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u16m2:
	ID = Intrinsic::riscv_vslide1up_vx_16m2;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i16m4:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u16m4:
	ID = Intrinsic::riscv_vslide1up_vx_16m4;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i16m8:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u16m8:
	ID = Intrinsic::riscv_vslide1up_vx_16m8;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i32m1:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u32m1:
	ID = Intrinsic::riscv_vslide1up_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i32m2:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u32m2:
	ID = Intrinsic::riscv_vslide1up_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i32m4:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u32m4:
	ID = Intrinsic::riscv_vslide1up_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i32m8:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u32m8:
	ID = Intrinsic::riscv_vslide1up_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_f32m1:
	ID = Intrinsic::riscv_vslide1up_vx_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_f32m2:
	ID = Intrinsic::riscv_vslide1up_vx_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_f32m4:
	ID = Intrinsic::riscv_vslide1up_vx_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_f32m8:
	ID = Intrinsic::riscv_vslide1up_vx_f32m8;
	break;

//masked                 
    case RISCV::BI__builtin_riscv_vslide1up_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u8m1_m:
	ID = Intrinsic::riscv_vslide1up_vx_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u8m2_m:
	ID = Intrinsic::riscv_vslide1up_vx_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u8m4_m:
	ID = Intrinsic::riscv_vslide1up_vx_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u8m8_m:
	ID = Intrinsic::riscv_vslide1up_vx_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u16m1_m:
	ID = Intrinsic::riscv_vslide1up_vx_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u16m2_m:
	ID = Intrinsic::riscv_vslide1up_vx_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u16m4_m:
	ID = Intrinsic::riscv_vslide1up_vx_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u16m8_m:
	ID = Intrinsic::riscv_vslide1up_vx_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u32m1_m:
	ID = Intrinsic::riscv_vslide1up_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u32m2_m:
	ID = Intrinsic::riscv_vslide1up_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u32m4_m:
	ID = Intrinsic::riscv_vslide1up_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vslide1up_vx_u32m8_m:
	ID = Intrinsic::riscv_vslide1up_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_f32m1_m:
	ID = Intrinsic::riscv_vslide1up_vx_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_f32m2_m:
	ID = Intrinsic::riscv_vslide1up_vx_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_f32m4_m:
	ID = Intrinsic::riscv_vslide1up_vx_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1up_vx_f32m8_m:
	ID = Intrinsic::riscv_vslide1up_vx_f32m8_m;
	break;

//vector vslide1down.vx          
    case RISCV::BI__builtin_riscv_vslide1down_vx_i8m1:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u8m1:
	ID = Intrinsic::riscv_vslide1down_vx_8m1;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i8m2:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u8m2:
	ID = Intrinsic::riscv_vslide1down_vx_8m2;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i8m4:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u8m4:
	ID = Intrinsic::riscv_vslide1down_vx_8m4;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i8m8:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u8m8:
	ID = Intrinsic::riscv_vslide1down_vx_8m8;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i16m1:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u16m1:
	ID = Intrinsic::riscv_vslide1down_vx_16m1;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i16m2:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u16m2:
	ID = Intrinsic::riscv_vslide1down_vx_16m2;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i16m4:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u16m4:
	ID = Intrinsic::riscv_vslide1down_vx_16m4;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i16m8:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u16m8:
	ID = Intrinsic::riscv_vslide1down_vx_16m8;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i32m1:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u32m1:
	ID = Intrinsic::riscv_vslide1down_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i32m2:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u32m2:
	ID = Intrinsic::riscv_vslide1down_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i32m4:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u32m4:
	ID = Intrinsic::riscv_vslide1down_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i32m8:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u32m8:
	ID = Intrinsic::riscv_vslide1down_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_f32m1:
	ID = Intrinsic::riscv_vslide1down_vx_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_f32m2:
	ID = Intrinsic::riscv_vslide1down_vx_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_f32m4:
	ID = Intrinsic::riscv_vslide1down_vx_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_f32m8:
	ID = Intrinsic::riscv_vslide1down_vx_f32m8;
	break;

//masked                 
    case RISCV::BI__builtin_riscv_vslide1down_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u8m1_m:
	ID = Intrinsic::riscv_vslide1down_vx_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u8m2_m:
	ID = Intrinsic::riscv_vslide1down_vx_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u8m4_m:
	ID = Intrinsic::riscv_vslide1down_vx_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u8m8_m:
	ID = Intrinsic::riscv_vslide1down_vx_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u16m1_m:
	ID = Intrinsic::riscv_vslide1down_vx_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u16m2_m:
	ID = Intrinsic::riscv_vslide1down_vx_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u16m4_m:
	ID = Intrinsic::riscv_vslide1down_vx_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u16m8_m:
	ID = Intrinsic::riscv_vslide1down_vx_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u32m1_m:
	ID = Intrinsic::riscv_vslide1down_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u32m2_m:
	ID = Intrinsic::riscv_vslide1down_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u32m4_m:
	ID = Intrinsic::riscv_vslide1down_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vslide1down_vx_u32m8_m:
	ID = Intrinsic::riscv_vslide1down_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_f32m1_m:
	ID = Intrinsic::riscv_vslide1down_vx_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_f32m2_m:
	ID = Intrinsic::riscv_vslide1down_vx_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_f32m4_m:
	ID = Intrinsic::riscv_vslide1down_vx_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vslide1down_vx_f32m8_m:
	ID = Intrinsic::riscv_vslide1down_vx_f32m8_m;
	break;

//vector vrgather.vv
    case RISCV::BI__builtin_riscv_vrgather_vv_i8m1:
    case RISCV::BI__builtin_riscv_vrgather_vv_u8m1:
	ID = Intrinsic::riscv_vrgather_vv_8m1;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i8m2:
    case RISCV::BI__builtin_riscv_vrgather_vv_u8m2:
	ID = Intrinsic::riscv_vrgather_vv_8m2;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i8m4:
    case RISCV::BI__builtin_riscv_vrgather_vv_u8m4:
	ID = Intrinsic::riscv_vrgather_vv_8m4;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i8m8:
    case RISCV::BI__builtin_riscv_vrgather_vv_u8m8:
	ID = Intrinsic::riscv_vrgather_vv_8m8;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i16m1:
    case RISCV::BI__builtin_riscv_vrgather_vv_u16m1:
	ID = Intrinsic::riscv_vrgather_vv_16m1;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i16m2:
    case RISCV::BI__builtin_riscv_vrgather_vv_u16m2:
	ID = Intrinsic::riscv_vrgather_vv_16m2;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i16m4:
    case RISCV::BI__builtin_riscv_vrgather_vv_u16m4:
	ID = Intrinsic::riscv_vrgather_vv_16m4;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i16m8:
    case RISCV::BI__builtin_riscv_vrgather_vv_u16m8:
	ID = Intrinsic::riscv_vrgather_vv_16m8;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i32m1:
    case RISCV::BI__builtin_riscv_vrgather_vv_u32m1:
	ID = Intrinsic::riscv_vrgather_vv_32m1;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i32m2:
    case RISCV::BI__builtin_riscv_vrgather_vv_u32m2:
	ID = Intrinsic::riscv_vrgather_vv_32m2;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i32m4:
    case RISCV::BI__builtin_riscv_vrgather_vv_u32m4:
	ID = Intrinsic::riscv_vrgather_vv_32m4;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i32m8:
    case RISCV::BI__builtin_riscv_vrgather_vv_u32m8:
	ID = Intrinsic::riscv_vrgather_vv_32m8;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_f32m1:
	ID = Intrinsic::riscv_vrgather_vv_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_f32m2:
	ID = Intrinsic::riscv_vrgather_vv_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_f32m4:
	ID = Intrinsic::riscv_vrgather_vv_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_f32m8:
	ID = Intrinsic::riscv_vrgather_vv_f32m8;
	break;

//masked                 
    case RISCV::BI__builtin_riscv_vrgather_vv_i8m1_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u8m1_m:
	ID = Intrinsic::riscv_vrgather_vv_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i8m2_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u8m2_m:
	ID = Intrinsic::riscv_vrgather_vv_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i8m4_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u8m4_m:
	ID = Intrinsic::riscv_vrgather_vv_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i8m8_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u8m8_m:
	ID = Intrinsic::riscv_vrgather_vv_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i16m1_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u16m1_m:
	ID = Intrinsic::riscv_vrgather_vv_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i16m2_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u16m2_m:
	ID = Intrinsic::riscv_vrgather_vv_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i16m4_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u16m4_m:
	ID = Intrinsic::riscv_vrgather_vv_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i16m8_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u16m8_m:
	ID = Intrinsic::riscv_vrgather_vv_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i32m1_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u32m1_m:
	ID = Intrinsic::riscv_vrgather_vv_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i32m2_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u32m2_m:
	ID = Intrinsic::riscv_vrgather_vv_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i32m4_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u32m4_m:
	ID = Intrinsic::riscv_vrgather_vv_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_i32m8_m:
    case RISCV::BI__builtin_riscv_vrgather_vv_u32m8_m:
	ID = Intrinsic::riscv_vrgather_vv_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_f32m1_m:
	ID = Intrinsic::riscv_vrgather_vv_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_f32m2_m:
	ID = Intrinsic::riscv_vrgather_vv_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_f32m4_m:
	ID = Intrinsic::riscv_vrgather_vv_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vv_f32m8_m:
	ID = Intrinsic::riscv_vrgather_vv_f32m8_m;
	break;

//vector vrgather.vx                                                               
    case RISCV::BI__builtin_riscv_vrgather_vx_i8m1:
    case RISCV::BI__builtin_riscv_vrgather_vx_u8m1:
	ID = Intrinsic::riscv_vrgather_vx_8m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i8m2:
    case RISCV::BI__builtin_riscv_vrgather_vx_u8m2:
	ID = Intrinsic::riscv_vrgather_vx_8m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i8m4:
    case RISCV::BI__builtin_riscv_vrgather_vx_u8m4:
	ID = Intrinsic::riscv_vrgather_vx_8m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i8m8:
    case RISCV::BI__builtin_riscv_vrgather_vx_u8m8:
	ID = Intrinsic::riscv_vrgather_vx_8m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i16m1:
    case RISCV::BI__builtin_riscv_vrgather_vx_u16m1:
	ID = Intrinsic::riscv_vrgather_vx_16m1;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i16m2:
    case RISCV::BI__builtin_riscv_vrgather_vx_u16m2:
	ID = Intrinsic::riscv_vrgather_vx_16m2;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i16m4:
    case RISCV::BI__builtin_riscv_vrgather_vx_u16m4:
	ID = Intrinsic::riscv_vrgather_vx_16m4;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i16m8:
    case RISCV::BI__builtin_riscv_vrgather_vx_u16m8:
	ID = Intrinsic::riscv_vrgather_vx_16m8;
	Ops[1] = Builder.CreateSExt(Ops[1], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i32m1:
    case RISCV::BI__builtin_riscv_vrgather_vx_u32m1:
	ID = Intrinsic::riscv_vrgather_vx_32m1;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i32m2:
    case RISCV::BI__builtin_riscv_vrgather_vx_u32m2:
	ID = Intrinsic::riscv_vrgather_vx_32m2;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i32m4:
    case RISCV::BI__builtin_riscv_vrgather_vx_u32m4:
	ID = Intrinsic::riscv_vrgather_vx_32m4;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i32m8:
    case RISCV::BI__builtin_riscv_vrgather_vx_u32m8:
	ID = Intrinsic::riscv_vrgather_vx_32m8;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_f32m1:
	ID = Intrinsic::riscv_vrgather_vx_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_f32m2:
	ID = Intrinsic::riscv_vrgather_vx_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_f32m4:
	ID = Intrinsic::riscv_vrgather_vx_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_f32m8:
	ID = Intrinsic::riscv_vrgather_vx_f32m8;
	break;

//masked                 
    case RISCV::BI__builtin_riscv_vrgather_vx_i8m1_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u8m1_m:
	ID = Intrinsic::riscv_vrgather_vx_8m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i8m2_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u8m2_m:
	ID = Intrinsic::riscv_vrgather_vx_8m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i8m4_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u8m4_m:
	ID = Intrinsic::riscv_vrgather_vx_8m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i8m8_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u8m8_m:
	ID = Intrinsic::riscv_vrgather_vx_8m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i16m1_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u16m1_m:
	ID = Intrinsic::riscv_vrgather_vx_16m1_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i16m2_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u16m2_m:
	ID = Intrinsic::riscv_vrgather_vx_16m2_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i16m4_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u16m4_m:
	ID = Intrinsic::riscv_vrgather_vx_16m4_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i16m8_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u16m8_m:
	ID = Intrinsic::riscv_vrgather_vx_16m8_m;
	Ops[2] = Builder.CreateSExt(Ops[2], Int32Ty);
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i32m1_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u32m1_m:
	ID = Intrinsic::riscv_vrgather_vx_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i32m2_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u32m2_m:
	ID = Intrinsic::riscv_vrgather_vx_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i32m4_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u32m4_m:
	ID = Intrinsic::riscv_vrgather_vx_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_i32m8_m:
    case RISCV::BI__builtin_riscv_vrgather_vx_u32m8_m:
	ID = Intrinsic::riscv_vrgather_vx_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_f32m1_m:
	ID = Intrinsic::riscv_vrgather_vx_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_f32m2_m:
	ID = Intrinsic::riscv_vrgather_vx_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_f32m4_m:
	ID = Intrinsic::riscv_vrgather_vx_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vx_f32m8_m:
	ID = Intrinsic::riscv_vrgather_vx_f32m8_m;
	break;

//vector vrgather.vi               
    case RISCV::BI__builtin_riscv_vrgather_vi_i8m1:
    case RISCV::BI__builtin_riscv_vrgather_vi_u8m1:
	ID = Intrinsic::riscv_vrgather_vi_8m1;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i8m2:
    case RISCV::BI__builtin_riscv_vrgather_vi_u8m2:
	ID = Intrinsic::riscv_vrgather_vi_8m2;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i8m4:
    case RISCV::BI__builtin_riscv_vrgather_vi_u8m4:
	ID = Intrinsic::riscv_vrgather_vi_8m4;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i8m8:
    case RISCV::BI__builtin_riscv_vrgather_vi_u8m8:
	ID = Intrinsic::riscv_vrgather_vi_8m8;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i16m1:
    case RISCV::BI__builtin_riscv_vrgather_vi_u16m1:
	ID = Intrinsic::riscv_vrgather_vi_16m1;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i16m2:
    case RISCV::BI__builtin_riscv_vrgather_vi_u16m2:
	ID = Intrinsic::riscv_vrgather_vi_16m2;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i16m4:
    case RISCV::BI__builtin_riscv_vrgather_vi_u16m4:
	ID = Intrinsic::riscv_vrgather_vi_16m4;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i16m8:
    case RISCV::BI__builtin_riscv_vrgather_vi_u16m8:
	ID = Intrinsic::riscv_vrgather_vi_16m8;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i32m1:
    case RISCV::BI__builtin_riscv_vrgather_vi_u32m1:
	ID = Intrinsic::riscv_vrgather_vi_32m1;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i32m2:
    case RISCV::BI__builtin_riscv_vrgather_vi_u32m2:
	ID = Intrinsic::riscv_vrgather_vi_32m2;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i32m4:
    case RISCV::BI__builtin_riscv_vrgather_vi_u32m4:
	ID = Intrinsic::riscv_vrgather_vi_32m4;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i32m8:
    case RISCV::BI__builtin_riscv_vrgather_vi_u32m8:
	ID = Intrinsic::riscv_vrgather_vi_32m8;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_f32m1:
	ID = Intrinsic::riscv_vrgather_vi_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_f32m2:
	ID = Intrinsic::riscv_vrgather_vi_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_f32m4:
	ID = Intrinsic::riscv_vrgather_vi_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_f32m8:
	ID = Intrinsic::riscv_vrgather_vi_f32m8;
	break;

//masked                 
    case RISCV::BI__builtin_riscv_vrgather_vi_i8m1_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u8m1_m:
	ID = Intrinsic::riscv_vrgather_vi_8m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i8m2_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u8m2_m:
	ID = Intrinsic::riscv_vrgather_vi_8m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i8m4_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u8m4_m:
	ID = Intrinsic::riscv_vrgather_vi_8m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i8m8_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u8m8_m:
	ID = Intrinsic::riscv_vrgather_vi_8m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i16m1_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u16m1_m:
	ID = Intrinsic::riscv_vrgather_vi_16m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i16m2_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u16m2_m:
	ID = Intrinsic::riscv_vrgather_vi_16m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i16m4_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u16m4_m:
	ID = Intrinsic::riscv_vrgather_vi_16m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i16m8_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u16m8_m:
	ID = Intrinsic::riscv_vrgather_vi_16m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i32m1_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u32m1_m:
	ID = Intrinsic::riscv_vrgather_vi_32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i32m2_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u32m2_m:
	ID = Intrinsic::riscv_vrgather_vi_32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i32m4_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u32m4_m:
	ID = Intrinsic::riscv_vrgather_vi_32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_i32m8_m:
    case RISCV::BI__builtin_riscv_vrgather_vi_u32m8_m:
	ID = Intrinsic::riscv_vrgather_vi_32m8_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_f32m1_m:
	ID = Intrinsic::riscv_vrgather_vi_f32m1_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_f32m2_m:
	ID = Intrinsic::riscv_vrgather_vi_f32m2_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_f32m4_m:
	ID = Intrinsic::riscv_vrgather_vi_f32m4_m;
	break;
    case RISCV::BI__builtin_riscv_vrgather_vi_f32m8_m:
	ID = Intrinsic::riscv_vrgather_vi_f32m8_m;
	break;

//vector vcompress               
    case RISCV::BI__builtin_riscv_vcompress_vm_i8m1:
    case RISCV::BI__builtin_riscv_vcompress_vm_u8m1:
	ID = Intrinsic::riscv_vcompress_vm_8m1;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i8m2:
    case RISCV::BI__builtin_riscv_vcompress_vm_u8m2:
	ID = Intrinsic::riscv_vcompress_vm_8m2;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i8m4:
    case RISCV::BI__builtin_riscv_vcompress_vm_u8m4:
	ID = Intrinsic::riscv_vcompress_vm_8m4;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i8m8:
    case RISCV::BI__builtin_riscv_vcompress_vm_u8m8:
	ID = Intrinsic::riscv_vcompress_vm_8m8;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i16m1:
    case RISCV::BI__builtin_riscv_vcompress_vm_u16m1:
	ID = Intrinsic::riscv_vcompress_vm_16m1;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i16m2:
    case RISCV::BI__builtin_riscv_vcompress_vm_u16m2:
	ID = Intrinsic::riscv_vcompress_vm_16m2;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i16m4:
    case RISCV::BI__builtin_riscv_vcompress_vm_u16m4:
	ID = Intrinsic::riscv_vcompress_vm_16m4;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i16m8:
    case RISCV::BI__builtin_riscv_vcompress_vm_u16m8:
	ID = Intrinsic::riscv_vcompress_vm_16m8;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i32m1:
    case RISCV::BI__builtin_riscv_vcompress_vm_u32m1:
	ID = Intrinsic::riscv_vcompress_vm_32m1;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i32m2:
    case RISCV::BI__builtin_riscv_vcompress_vm_u32m2:
	ID = Intrinsic::riscv_vcompress_vm_32m2;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i32m4:
    case RISCV::BI__builtin_riscv_vcompress_vm_u32m4:
	ID = Intrinsic::riscv_vcompress_vm_32m4;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_i32m8:
    case RISCV::BI__builtin_riscv_vcompress_vm_u32m8:
	ID = Intrinsic::riscv_vcompress_vm_32m8;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_f32m1:
	ID = Intrinsic::riscv_vcompress_vm_f32m1;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_f32m2:
	ID = Intrinsic::riscv_vcompress_vm_f32m2;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_f32m4:
	ID = Intrinsic::riscv_vcompress_vm_f32m4;
	break;
    case RISCV::BI__builtin_riscv_vcompress_vm_f32m8:
	ID = Intrinsic::riscv_vcompress_vm_f32m8;
	break;
    }
    llvm::Function * F = CGM.getIntrinsic(ID);
    return Builder.CreateCall(F, Ops, "");
}
