//===- RISCVInstrInfoV.td -  RISCV Vector Extension instructions -*- tblgen-*-----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines all of the RISCV Vector Extension Instructions
// Contributed by Hunan Compiler Information Technology Co., Ltd, 
// http://www.compiler-dev.com, Email: <info@compiler-dev.com>.
//===----------------------------------------------------------------------===//

include "RISCVInstrFormatsV.td"

//===----------------------------------------------------------------------===//
// Operand and SDNode transformation definitions.
//===----------------------------------------------------------------------===//
def VectorRegister : AsmOperandClass{
	let Name = "VectorRegister";
	let ParserMethod = "parseVectorRegister";
	let DiagnosticType = "InvalidVectorRegister";
}

def VReg : Operand<vAny> {
	let ParserMatchClass = VectorRegister;
	let PrintMethod = "printVectorRegister";
	let DecoderMethod = "decodeVectorRegister";
}

def simm5 : Operand<XLenVT>, ImmLeaf<XLenVT, [{return isInt<5>(Imm);}]> {
	let ParserMatchClass = SImmAsmOperand<5>;
	let EncoderMethod = "getImmOpValue";
	let DecoderMethod = "decodeSImmOperand<5>";
}

def uimm7 : Operand<XLenVT>, ImmLeaf<XLenVT, [{return isUInt<7>(Imm);}]> {
	let ParserMatchClass = UImmAsmOperand<7>;
	let EncoderMethod = "getImmOpValue";
	let DecoderMethod = "decodeUImmOperand<7>";
}

def VTypeImmAsmOperand : AsmOperandClass{
	let Name = "VTypeImm";
	let ParserMethod = "parseVTypeImmAsmOperand";
	let DiagnosticType = "InvalidVTypeImmAsmOperand";
}

def VTypeImm : Operand<XLenVT> {
	let ParserMatchClass = VTypeImmAsmOperand;
	let PrintMethod = "printVTypeImm";
	let DecoderMethod = "decodeUImmOperand<7>";
}

//===----------------------------------------------------------------------===//
// RISC-V specific DAG Nodes.
//===----------------------------------------------------------------------===//
def addr   : ComplexPattern<iPTR, 1, "SelectAddr",[], []>;

//===----------------------------------------------------------------------===//
// Instruction class templates
//===----------------------------------------------------------------------===//

let hasSideEffects = 0, mayLoad = 0, mayStore = 1, Uses = [VL] in
multiclass VStore_UnitStride<bits<6> funct6,bits<3> funct3, string opcodestr>{
	def _m : RVInstVStore<funct6,funct3,OPC_STORE_FP,
			(outs),(ins VMASK:$vm, VReg:$vs3, GPR:$rs1),opcodestr,"$vs3, (${rs1}), $vm">,Sched<[]>{
				bits<1> vm;
				let Inst{25} = vm;
				let Inst{24-20} = 0b00000;
	}


	def _um : RVInstVStore<funct6,funct3,OPC_STORE_FP,
			(outs),(ins VReg:$vs3, GPR:$rs1),opcodestr,"$vs3, (${rs1})">,Sched<[]>{
				let Inst{25-20} = 0b100000;
	}

}



let hasSideEffects = 0, mayLoad = 0, mayStore = 1, Uses = [VL] in
multiclass VStore_Strided<bits<6> funct6,bits<3> funct3, string opcodestr>{
	def _m : RVInstVStore<funct6,funct3,OPC_STORE_FP,
			(outs),(ins VMASK:$vm, GPR:$rs1, GPR:$rs2, VReg:$vs3),opcodestr,"$vs3, (${rs1}), $rs2, $vm">,Sched<[]>{
				bits<1> vm;
				bits<5> rs2;
				let Inst{25} = vm;
				let Inst{24-20} = rs2;
	}
	def _um : RVInstVStore<funct6,funct3,OPC_STORE_FP,
			(outs),(ins GPR:$rs1, GPR:$rs2, VReg:$vs3),opcodestr,"$vs3, (${rs1}), $rs2">,Sched<[]>{
				bits<5> rs2;
				let Inst{25} = 0b1;
				let Inst{24-20} = rs2;
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 1, Uses = [VL] in
multiclass VStore_Indexed<bits<6> funct6,bits<3> funct3, string opcodestr>{
	def _m : RVInstVStore<funct6,funct3,OPC_STORE_FP,
			(outs),(ins VMASK:$vm, GPR:$rs1, VReg:$vs2, VReg:$vs3),opcodestr,"$vs3, (${rs1}), $vs2, $vm">,Sched<[]>{
				bits<1> vm;
				bits<5> vs2;
				let Inst{25} = vm;
				let Inst{24-20} = vs2;
	}
	def _um : RVInstVStore<funct6,funct3,OPC_STORE_FP,
			(outs),(ins GPR:$rs1, VReg:$vs2, VReg:$vs3),opcodestr,"$vs3, (${rs1}), $vs2">,Sched<[]>{
				bits<5> vs2;
				let Inst{25} = 0b1;
				let Inst{24-20} = vs2;
	}
}

let hasSideEffects = 0, mayLoad = 1, mayStore = 0, Uses = [VL] in
multiclass VLoad_UnitStride<bits<6> funct6,bits<3> funct3,string opcodestr>{
	def _m : RVInstVLoad<funct6,funct3,OPC_LOAD_FP,
			(outs VReg:$vd),(ins VMASK:$vm, GPR:$rs1),opcodestr,"$vd, (${rs1}), $vm">,Sched<[]>{
				bits<1> vm;
				let Inst{25} = vm;
				let Inst{24-20} = 0b00000;
	}


	def _um : RVInstVLoad<funct6,funct3,OPC_LOAD_FP,
			(outs VReg:$vd),(ins GPR:$rs1),opcodestr,"$vd, (${rs1})">,Sched<[]>{
				let Inst{25-20} = 0b100000;		
	}

}

let hasSideEffects = 0, mayLoad = 1, mayStore = 0, Uses = [VL] in
multiclass VLoad_UnitStride_FF<bits<6> funct6,bits<3> funct3,string opcodestr>{
	def _m : RVInstVLoad<funct6,funct3,OPC_LOAD_FP,
			(outs VReg:$vd),(ins VMASK:$vm, GPR:$rs1),opcodestr,"$vd, (${rs1}), $vm">,Sched<[]>{
				bits<1> vm;
				let Inst{25} = vm;
				let Inst{24-20} = 0b10000;
	}


	def _um : RVInstVLoad<funct6,funct3,OPC_LOAD_FP,
			(outs VReg:$vd),(ins GPR:$rs1),opcodestr,"$vd, (${rs1})">,Sched<[]>{
				let Inst{25-20} = 0b110000;		
	}

}

let hasSideEffects = 0, mayLoad = 1, mayStore = 0, Uses = [VL] in
multiclass VLoad_Strided<bits<6> funct6,bits<3> funct3,string opcodestr>{
	def _m : RVInstVLoad<funct6,funct3,OPC_LOAD_FP,
			(outs VReg:$vd),(ins VMASK:$vm, GPR:$rs1, GPR:$rs2),opcodestr,"$vd, (${rs1}), $rs2, $vm">,Sched<[]>{
				bits<1> vm;
				bits<5> rs2;
				let Inst{25} = vm;
				let Inst{24-20} = rs2;
	}
	def _um : RVInstVLoad<funct6,funct3,OPC_LOAD_FP,
			(outs VReg:$vd),(ins GPR:$rs1, GPR:$rs2),opcodestr,"$vd, (${rs1}), $rs2">,Sched<[]>{
				bits<5> rs2;
				let Inst{25} = 0b1;
				let Inst{24-20} = rs2;		
	}			
}


let hasSideEffects = 0, mayLoad = 1, mayStore = 0, Uses = [VL] in
multiclass VLoad_Indexed<bits<6> funct6,bits<3> funct3,string opcodestr>{
	def _m : RVInstVLoad<funct6,funct3,OPC_LOAD_FP,
			(outs VReg:$vd),(ins VMASK:$vm, GPR:$rs1, VReg:$vs2),opcodestr,"$vd, (${rs1}), $vs2, $vm">,Sched<[]>{
				bits<1> vm;
				bits<5> vs2;
				let Inst{25} = vm;
				let Inst{24-20} = vs2;
	}
	def _um : RVInstVLoad<funct6,funct3,OPC_LOAD_FP,
			(outs VReg:$vd),(ins GPR:$rs1, VReg:$vs2),opcodestr,"$vd, (${rs1}), $vs2">,Sched<[]>{
				bits<5> vs2;
				let Inst{25} = 0b1;
				let Inst{24-20} = vs2;
			}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in {
multiclass VALU_OPFVV<bits<6> funct6, string opcodestr>{
		def _m : RVInstVA<funct6,0b001,OPC_VOP,
				(outs VReg:$vd),(ins VMASK:$vm, VReg:$vs2, VReg:$vs1),opcodestr,"$vd, $vs2, $vs1, $vm">,Sched<[]>{
				bits<1> vm;
				bits<5> vs1;
				let Inst{25} = vm;
				let Inst{19-15} = vs1;
				}
		def _um : RVInstVA<funct6,0b001,OPC_VOP,
				(outs VReg:$vd),(ins VReg:$vs2, VReg:$vs1),opcodestr,"$vd, $vs2, $vs1">,Sched<[]>{
				bits<5> vs1;
				let Inst{25} = 0b1;
				let Inst{19-15} = vs1;
				}
	}		   
	
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in {
multiclass VALU_OPFVF<bits<6> funct6, string opcodestr>{
		def _m : RVInstVA<funct6,0b101,OPC_VOP,
				(outs VReg:$vd),(ins VMASK:$vm, VReg:$vs2, FPR32:$rs1),opcodestr,"$vd, $vs2, $rs1, $vm">,Sched<[]>{
				bits<1> vm;
				bits<5> rs1;
				let Inst{25} = vm;
				let Inst{19-15} = rs1;
				}
		def _um : RVInstVA<funct6,0b101,OPC_VOP,
				(outs VReg:$vd),(ins VReg:$vs2, FPR32:$rs1),opcodestr,"$vd, $vs2, $rs1">,Sched<[]>{
				bits<5> rs1;
				let Inst{25} = 0b1;
				let Inst{19-15} = rs1;
				}
	}		   
	
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Constraints = "$vs3 = $vd", Uses = [VL]  in {
multiclass VALU_OPFVV_MulAdd<bits<6> funct6,string opcodestr>{
		def _m : RVInstVA<funct6,0b001,OPC_VOP,
				(outs VReg:$vd),(ins VMASK:$vm, VReg:$vs3, VReg:$vs1, VReg:$vs2),opcodestr,"$vd, $vs1, $vs2, $vm">,Sched<[]>{
				bits<1> vm;
				bits<5> vs1;
				let Inst{25} = vm;
				let Inst{19-15} = vs1;
				}
		def _um : RVInstVA<funct6,0b001,OPC_VOP,
				(outs VReg:$vd),(ins VReg:$vs3, VReg:$vs1, VReg:$vs2),opcodestr,"$vd, $vs1, $vs2">,Sched<[]>{
				bits<5> vs1;
				let Inst{25} = 0b1;
				let Inst{19-15} = vs1;
				}
	}		   
	
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Constraints = "$vs3 = $vd", Uses = [VL] in {
multiclass VALU_OPFVF_MulAdd<bits<6> funct6,string opcodestr>{
		def _m : RVInstVA<funct6,0b101,OPC_VOP,
				(outs VReg:$vd),(ins VMASK:$vm, VReg:$vs3, FPR32:$rs1, VReg:$vs2),opcodestr,"$vd, $rs1, $vs2, $vm">,Sched<[]>{
				bits<1> vm;
				bits<5> rs1;
				let Inst{25} = vm;
				let Inst{19-15} = rs1;
				}
		def _um : RVInstVA<funct6,0b101,OPC_VOP,
				(outs VReg:$vd),(ins VReg:$vs3, FPR32:$rs1, VReg:$vs2),opcodestr,"$vd, $rs1, $vs2">,Sched<[]>{
				bits<5> rs1;
				let Inst{25} = 0b1;
				let Inst{19-15} = rs1;
				}
	}		   
	
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in {
multiclass VALU_OPFVV_VFUNARY<bits<6> funct6,bits<5> vs1, string opcodestr>{
		def _m : RVInstVA<funct6,0b001,OPC_VOP,
				(outs VReg:$vd),(ins VMASK:$vm, VReg:$vs2),opcodestr,"$vd, $vs2, $vm">,Sched<[]>{
				bits<1> vm;
				let Inst{25} = vm;
				let Inst{19-15} = vs1;
				}
		def _um : RVInstVA<funct6,0b001,OPC_VOP,
				(outs VReg:$vd),(ins VReg:$vs2),opcodestr,"$vd, $vs2">,Sched<[]>{
				let Inst{25} = 0b1;
				let Inst{19-15} = vs1;
				}
	}		   
	
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	multiclass VALU_OPMVV<bits<6> funct6,string opcodestr>{
	def _m : RVInstVA<funct6,0b010,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs2, VReg:$vs1),opcodestr,"$vd, $vs2, $vs1, $vm">,Sched<[]>{
			bits<5> vs1;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = vs1;
			}
	def _um : RVInstVA<funct6,0b010,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, VReg:$vs1),opcodestr,"$vd, $vs2, $vs1">,Sched<[]>{
			bits<5> vs1;
			let Inst{25} = 0b1;
			let Inst{19-15} = vs1;
			}
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	multiclass VALU_OPMVX<bits<6> funct6,string opcodestr>{
	def _m : RVInstVA<funct6,0b110,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs2, GPR:$rs1),opcodestr,"$vd, $vs2, $rs1, $vm">,Sched<[]>{
			bits<5> rs1;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = rs1;
			}
	def _um : RVInstVA<funct6,0b110,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, GPR:$rs1),opcodestr,"$vd, $vs2, $rs1">,Sched<[]>{
			bits<5> rs1;
			let Inst{25} = 0b1;
			let Inst{19-15} = rs1;
			}
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	multiclass VALU_OPIVV<bits<6> funct6,string opcodestr>{
	def _m : RVInstVA<funct6,0b000,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs2, VReg:$vs1),opcodestr,"$vd, $vs2, $vs1, $vm">,Sched<[]>{
			bits<5> vs1;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = vs1;
			}

	def _um : RVInstVA<funct6,0b000,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, VReg:$vs1),opcodestr,"$vd, $vs2, $vs1">,Sched<[]>{
			bits<5> vs1;
			let Inst{25} = 0b1;
			let Inst{19-15} = vs1;
			}

	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	multiclass VALU_OPMVV_VWXUNARY<bits<6> funct6,bits<5> vs1,string opcodestr>{
	def _m : RVInstVAR<funct6,0b010,OPC_VOP,(outs GPR:$rd),
			(ins VMASK:$vm, VReg:$vs2),opcodestr,"$rd, $vs2, $vm">,Sched<[]>{
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = vs1;
			}
	def _um : RVInstVAR<funct6,0b010,OPC_VOP,(outs GPR:$rd),
			(ins VReg:$vs2),opcodestr,"$rd, $vs2">,Sched<[]>{
			let Inst{25} = 0b1;
			let Inst{19-15} = vs1;
			}
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	multiclass VALU_OPMVV_VMUNARY<bits<6> funct6,bits<5> vs1,string opcodestr>{
	def _m : RVInstVA<funct6,0b010,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs2),opcodestr,"$vd, $vs2, $vm">,Sched<[]>{
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = vs1;
			}
	def _um : RVInstVA<funct6,0b010,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2),opcodestr,"$vd, $vs2">,Sched<[]>{
			let Inst{25} = 0b1;
			let Inst{19-15} = vs1;
			}
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
multiclass VALU_OPIVV_VID<bits<5> vs1,string opcodestr>{
		def _m : RVInstVA<0b010100,0b010,OPC_VOP,
				(outs VReg:$vd),(ins VMASK:$vm),opcodestr,"$vd, $vm">,Sched<[]>{
				bits<1> vm;
				let Inst{25} = vm;
				let Inst{19-15} = vs1;
				let vs2 = 0b00000;
				}
		def _um : RVInstVA<0b010100,0b010,OPC_VOP,
				(outs VReg:$vd),(ins),opcodestr,"$vd">,Sched<[]>{
				let Inst{25} = 0b1;
				let Inst{19-15} = vs1;
				let vs2 = 0b00000;
				let Uses = [V0];
				}		
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	multiclass VALU_OPIVX<bits<6> funct6,string opcodestr>{
	def _m : RVInstVA<funct6,0b100,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs2, GPR:$rs1),opcodestr,"$vd, $vs2, $rs1, $vm">,Sched<[]>{
			bits<5> rs1;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = rs1;
			}

	def _um : RVInstVA<funct6,0b100,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, GPR:$rs1),opcodestr,"$vd, $vs2, $rs1">,Sched<[]>{
			bits<5> rs1;
			let Inst{25} = 0b1;
			let Inst{19-15} = rs1;
			}

	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	multiclass VALU_OPIVI_signed<bits<6> funct6,string opcodestr>{
	def _m : RVInstVA<funct6,0b011,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs2, simm5:$simm),opcodestr,"$vd, $vs2, $simm, $vm">,Sched<[]>{
			bits<5> simm;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = simm;
			}

	def _um : RVInstVA<funct6,0b011,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, simm5:$simm),opcodestr,"$vd, $vs2, $simm">,Sched<[]>{
			bits<5> simm;
			let Inst{25} = 0b1;
			let Inst{19-15} = simm;
			}

	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	multiclass VALU_OPIVI_unsigned<bits<6> funct6,string opcodestr>{
	def _m : RVInstVA<funct6,0b011,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs2, uimm5:$uimm),opcodestr,"$vd, $vs2, $uimm, $vm">,Sched<[]>{
			bits<5> uimm;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = uimm;
			}

	def _um : RVInstVA<funct6,0b011,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, uimm5:$uimm),opcodestr,"$vd, $vs2, $uimm">,Sched<[]>{
			bits<5> uimm;
			let Inst{25} = 0b1;
			let Inst{19-15} = uimm;
			}

	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	class VALU_OPIVV_m<bits<6> funct6,string opcodestr>
			:RVInstVA<funct6,0b000,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, VReg:$vs1, VMASK:$vm),opcodestr,"$vd, $vs2, $vs1, $vm">,Sched<[]>{
			bits<5> vs1;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = vs1;
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	class VALU_OPIVX_m<bits<6> funct6,string opcodestr>
			:RVInstVA<funct6,0b100,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, GPR:$rs1, VMASK:$vm),opcodestr,"$vd, $vs2, $rs1, $vm">,Sched<[]>{
			bits<5> rs1;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = rs1;
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	class VALU_OPIVI_m<bits<6> funct6,string opcodestr>
			:RVInstVA<funct6,0b011,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, simm5:$simm, VMASK:$vm),opcodestr,"$vd, $vs2, $simm, $vm">,Sched<[]>{
			bits<5> simm;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = simm;
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	class VALU_OPIVV_um<bits<6> funct6,string opcodestr>
			:RVInstVA<funct6,0b000,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, VReg:$vs1),opcodestr,"$vd, $vs2, $vs1">,Sched<[]>{
			bits<5> vs1;
			let Inst{25} = 0b1;
			let Inst{19-15} = vs1;
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	class VALU_OPIVX_um<bits<6> funct6,string opcodestr>
			:RVInstVA<funct6,0b100,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, GPR:$rs1),opcodestr,"$vd, $vs2, $rs1">,Sched<[]>{
			bits<5> rs1;
			let Inst{25} = 0b1;
			let Inst{19-15} = rs1;
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
	class VALU_OPIVI_um<bits<6> funct6,string opcodestr>
			:RVInstVA<funct6,0b011,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs2, simm5:$simm),opcodestr,"$vd, $vs2, $simm">,Sched<[]>{
			bits<5> simm;
			let Inst{25} = 0b1;
			let Inst{19-15} = simm;
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Constraints = "$vs3 = $vd", Uses = [VL] in{
	multiclass VALU_OPMVV_MulAdd<bits<6> funct6,string opcodestr>{
	def _m : RVInstVA<funct6,0b010,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs3, VReg:$vs1, VReg:$vs2),opcodestr,"$vd, $vs1, $vs2, $vm">,Sched<[]>{
			bits<5> vs1;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = vs1;
			}
	def _um : RVInstVA<funct6,0b010,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs3, VReg:$vs1, VReg:$vs2),opcodestr,"$vd, $vs1, $vs2">,Sched<[]>{
			bits<5> vs1;
			let Inst{25} = 0b1;
			let Inst{19-15} = vs1;
			}
	}
}


let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Constraints = "$vs3 = $vd", Uses = [VL] in{
	multiclass VALU_OPMVX_MulAdd<bits<6> funct6,string opcodestr>{
	def _m : RVInstVA<funct6,0b110,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs3, GPR:$rs1, VReg:$vs2),opcodestr,"$vd, $rs1, $vs2, $vm">,Sched<[]>{
			bits<5> rs1;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = rs1;
			}
	def _um : RVInstVA<funct6,0b110,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs3, GPR:$rs1, VReg:$vs2),opcodestr,"$vd, $rs1, $vs2">,Sched<[]>{
			bits<5> rs1;
			let Inst{25} = 0b1;
			let Inst{19-15} = rs1;
			}
	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Constraints = "$vs3 = $vd", Uses = [VL] in{
	multiclass VALU_OPIVV_MulAdd<bits<6> funct6,string opcodestr>{
	def _m : RVInstVA<funct6,0b000,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs3, VReg:$vs1, VReg:$vs2),opcodestr,"$vd, $vs1, $vs2, $vm">,Sched<[]>{
			bits<5> vs1;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = vs1;
			}

	def _um : RVInstVA<funct6,0b000,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs3, VReg:$vs1, VReg:$vs2),opcodestr,"$vd, $vs1, $vs2">,Sched<[]>{
			bits<5> vs1;
			let Inst{25} = 0b1;
			let Inst{19-15} = vs1;
			}

	}
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Constraints = "$vs3 = $vd", Uses = [VL] in{
	multiclass VALU_OPIVX_MulAdd<bits<6> funct6,string opcodestr>{
	def _m : RVInstVA<funct6,0b100,OPC_VOP,(outs VReg:$vd),
			(ins VMASK:$vm, VReg:$vs3, GPR:$rs1, VReg:$vs2),opcodestr,"$vd, $rs1, $vs2, $vm">,Sched<[]>{
			bits<5> rs1;
			bits<1> vm;
			let Inst{25} = vm;
			let Inst{19-15} = rs1;
			}

	def _um : RVInstVA<funct6,0b100,OPC_VOP,(outs VReg:$vd),
			(ins VReg:$vs3, GPR:$rs1, VReg:$vs2),opcodestr,"$vd, $rs1, $vs2">,Sched<[]>{
			bits<5> rs1;
			let Inst{25} = 0b1;
			let Inst{19-15} = rs1;
			}

	}
}

//===----------------------------------------------------------------------===//
// RISCV Vector Extensions Instructions
//===----------------------------------------------------------------------===//
let Predicates = [HasStdExtV] in {

//set vl and vtype
let hasSideEffects = 1, mayLoad = 0, mayStore = 0, Defs = [VL] in {
	def VSETVLI : RVInstVSet<0b00000, OPC_VOP, (outs GPR:$rd), (ins GPR:$rs1, VTypeImm:$vtypei),
			"vsetvli", "$rd, $rs1, $vtypei",
			[(set i32:$rd, (int_riscv_vsetvli i32:$rs1, uimm7:$vtypei))]>, Sched<[]>{
	bits<7> vtypei;
	let Inst{26-20} = vtypei;
	}
	def VSETVL : RVInstVSet<0b10000, OPC_VOP, (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
		    "vsetvl", "$rd, $rs1, $rs2",
			[(set i32:$rd, (int_riscv_vsetvl i32:$rs1, i32:$rs2))]>, Sched<[]>{
	bits<5> rs2;
	let Inst{26-25} = 0b00;
	let Inst{24-20} = rs2;
	}
}


/********vector unit-stride load/store********/

defm VSE_V : VStore_UnitStride<0b000000,0b111,"vse.v">;

multiclass VStPat<SDPatternOperator StoreOp, RVInst Inst, ValueType VecTy>{
	def : Pat<(StoreOp VecTy:$vs3, addr:$rs1),(Inst VecTy:$vs3, addr:$rs1)>;
	def : Pat<(StoreOp VecTy:$vs3, AddrFI:$rs1),(Inst VecTy:$vs3, AddrFI:$rs1)>;
}

defm : VStPat<store, VSE_V_um, v16i8>;
defm : VStPat<store, VSE_V_um, v8i16>;
defm : VStPat<store, VSE_V_um, v4i32>;
defm : VStPat<store, VSE_V_um, v4f32>;

defm : VStPat<store, VSE_V_um, v32i8>;
defm : VStPat<store, VSE_V_um, v16i16>;
defm : VStPat<store, VSE_V_um, v8i32>;
defm : VStPat<store, VSE_V_um, v8f32>;

defm : VStPat<store, VSE_V_um, v64i8>;
defm : VStPat<store, VSE_V_um, v32i16>;
defm : VStPat<store, VSE_V_um, v16i32>;
defm : VStPat<store, VSE_V_um, v16f32>;

defm : VStPat<store, VSE_V_um, v128i8>;
defm : VStPat<store, VSE_V_um, v64i16>;
defm : VStPat<store, VSE_V_um, v32i32>;
defm : VStPat<store, VSE_V_um, v32f32>;

class PatVgrAddr<SDPatternOperator OpNode, RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs3, addr:$rs1),(Inst VecTy:$vs3, addr:$rs1)>;
	
class PatVmVgrAddr<SDPatternOperator OpNode, RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs3, addr:$rs1),(Inst VMASK:$vm, VecTy:$vs3, addr:$rs1)>;	

def : PatVgrAddr<int_riscv_vse_v_8m1,VSE_V_um,v16i8>;
def : PatVgrAddr<int_riscv_vse_v_8m2,VSE_V_um,v32i8>;
def : PatVgrAddr<int_riscv_vse_v_8m4,VSE_V_um,v64i8>;
def : PatVgrAddr<int_riscv_vse_v_8m8,VSE_V_um,v128i8>;

def : PatVgrAddr<int_riscv_vse_v_16m1,VSE_V_um,v8i16>;
def : PatVgrAddr<int_riscv_vse_v_16m2,VSE_V_um,v16i16>;
def : PatVgrAddr<int_riscv_vse_v_16m4,VSE_V_um,v32i16>;
def : PatVgrAddr<int_riscv_vse_v_16m8,VSE_V_um,v64i16>;

def : PatVgrAddr<int_riscv_vse_v_32m1,VSE_V_um,v4i32>;
def : PatVgrAddr<int_riscv_vse_v_32m2,VSE_V_um,v8i32>;
def : PatVgrAddr<int_riscv_vse_v_32m4,VSE_V_um,v16i32>;
def : PatVgrAddr<int_riscv_vse_v_32m8,VSE_V_um,v32i32>;

def : PatVgrAddr<int_riscv_vse_v_f32m1,VSE_V_um,v4f32>;
def : PatVgrAddr<int_riscv_vse_v_f32m2,VSE_V_um,v8f32>;
def : PatVgrAddr<int_riscv_vse_v_f32m4,VSE_V_um,v16f32>;
def : PatVgrAddr<int_riscv_vse_v_f32m8,VSE_V_um,v32f32>;

def : PatVmVgrAddr<int_riscv_vse_v_8m1_m,VSE_V_m,v16i8>;
def : PatVmVgrAddr<int_riscv_vse_v_8m2_m,VSE_V_m,v32i8>;
def : PatVmVgrAddr<int_riscv_vse_v_8m4_m,VSE_V_m,v64i8>;
def : PatVmVgrAddr<int_riscv_vse_v_8m8_m,VSE_V_m,v128i8>;

def : PatVmVgrAddr<int_riscv_vse_v_16m1_m,VSE_V_m,v8i16>;
def : PatVmVgrAddr<int_riscv_vse_v_16m2_m,VSE_V_m,v16i16>;
def : PatVmVgrAddr<int_riscv_vse_v_16m4_m,VSE_V_m,v32i16>;
def : PatVmVgrAddr<int_riscv_vse_v_16m8_m,VSE_V_m,v64i16>;

def : PatVmVgrAddr<int_riscv_vse_v_32m1_m,VSE_V_m,v4i32>;
def : PatVmVgrAddr<int_riscv_vse_v_32m2_m,VSE_V_m,v8i32>;
def : PatVmVgrAddr<int_riscv_vse_v_32m4_m,VSE_V_m,v16i32>;
def : PatVmVgrAddr<int_riscv_vse_v_32m8_m,VSE_V_m,v32i32>;

def : PatVmVgrAddr<int_riscv_vse_v_f32m1_m,VSE_V_m,v4f32>;
def : PatVmVgrAddr<int_riscv_vse_v_f32m2_m,VSE_V_m,v8f32>;
def : PatVmVgrAddr<int_riscv_vse_v_f32m4_m,VSE_V_m,v16f32>;
def : PatVmVgrAddr<int_riscv_vse_v_f32m8_m,VSE_V_m,v32f32>;

defm VLE_V : VLoad_UnitStride<0b000000,0b111,"vle.v">;

multiclass VLdPat<SDPatternOperator Loadop, RVInst Inst, ValueType VecTy>{
	def : Pat<(VecTy(Loadop addr:$rs1)),(VecTy(Inst addr:$rs1))>;
	def : Pat<(VecTy(Loadop AddrFI:$rs1)),(VecTy(Inst AddrFI:$rs1))>;
}

defm : VLdPat<load, VLE_V_um, v16i8>;
defm : VLdPat<load, VLE_V_um, v8i16>;
defm : VLdPat<load, VLE_V_um, v4i32>;
defm : VLdPat<load, VLE_V_um, v4f32>;

defm : VLdPat<load, VLE_V_um, v32i8>;
defm : VLdPat<load, VLE_V_um, v16i16>;
defm : VLdPat<load, VLE_V_um, v8i32>;
defm : VLdPat<load, VLE_V_um, v8f32>;

defm : VLdPat<load, VLE_V_um, v64i8>;
defm : VLdPat<load, VLE_V_um, v32i16>;
defm : VLdPat<load, VLE_V_um, v16i32>;
defm : VLdPat<load, VLE_V_um, v16f32>;

defm : VLdPat<load, VLE_V_um, v128i8>;
defm : VLdPat<load, VLE_V_um, v64i16>;
defm : VLdPat<load, VLE_V_um, v32i32>;
defm : VLdPat<load, VLE_V_um, v32f32>;

class PatAddr<SDPatternOperator OpNode, RVInst Inst>
		: Pat<(OpNode addr:$rs1),(Inst addr:$rs1)>;
	
class PatVmAddr<SDPatternOperator OpNode, RVInst Inst>
		: Pat<(OpNode VMASK:$vm, addr:$rs1),(Inst VMASK:$vm, addr:$rs1)>;
				
def : PatAddr<int_riscv_vle_v_8m1,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_8m2,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_8m4,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_8m8,VLE_V_um>;

def : PatAddr<int_riscv_vle_v_16m1,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_16m2,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_16m4,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_16m8,VLE_V_um>;

def : PatAddr<int_riscv_vle_v_32m1,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_32m2,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_32m4,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_32m8,VLE_V_um>;

def : PatAddr<int_riscv_vle_v_f32m1,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_f32m2,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_f32m4,VLE_V_um>;
def : PatAddr<int_riscv_vle_v_f32m8,VLE_V_um>;

def : PatVmAddr<int_riscv_vle_v_8m1_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_8m2_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_8m4_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_8m8_m,VLE_V_m>;

def : PatVmAddr<int_riscv_vle_v_16m1_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_16m2_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_16m4_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_16m8_m,VLE_V_m>;

def : PatVmAddr<int_riscv_vle_v_32m1_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_32m2_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_32m4_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_32m8_m,VLE_V_m>;

def : PatVmAddr<int_riscv_vle_v_f32m1_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_f32m2_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_f32m4_m,VLE_V_m>;
def : PatVmAddr<int_riscv_vle_v_f32m8_m,VLE_V_m>;

/********vector strided load/store********/
defm VSSE_V : VStore_Strided<0b000010, 0b111, "vsse.v">;

class PatAddrGprVgr<SDPatternOperator OpNode, RVInst Inst, ValueType VecTy>
	: Pat<(OpNode addr:$rs1, GPR:$rs2, VecTy:$vs3),(Inst addr:$rs1, GPR:$rs2, VecTy:$vs3)>;
	
class PatVmAddrGprVgr<SDPatternOperator OpNode, RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, addr:$rs1, GPR:$rs2, VecTy:$vs3),(Inst VMASK:$vm, addr:$rs1, GPR:$rs2, VecTy:$vs3)>;
	
def : PatAddrGprVgr<int_riscv_vsse_v_8m1,VSSE_V_um,v16i8>;
def : PatAddrGprVgr<int_riscv_vsse_v_8m2,VSSE_V_um,v32i8>;
def : PatAddrGprVgr<int_riscv_vsse_v_8m4,VSSE_V_um,v64i8>;
def : PatAddrGprVgr<int_riscv_vsse_v_8m8,VSSE_V_um,v128i8>;

def : PatAddrGprVgr<int_riscv_vsse_v_16m1,VSSE_V_um,v8i16>;
def : PatAddrGprVgr<int_riscv_vsse_v_16m2,VSSE_V_um,v16i16>;
def : PatAddrGprVgr<int_riscv_vsse_v_16m4,VSSE_V_um,v32i16>;
def : PatAddrGprVgr<int_riscv_vsse_v_16m8,VSSE_V_um,v64i16>;

def : PatAddrGprVgr<int_riscv_vsse_v_32m1,VSSE_V_um,v4i32>;
def : PatAddrGprVgr<int_riscv_vsse_v_32m2,VSSE_V_um,v8i32>;
def : PatAddrGprVgr<int_riscv_vsse_v_32m4,VSSE_V_um,v16i32>;
def : PatAddrGprVgr<int_riscv_vsse_v_32m8,VSSE_V_um,v32i32>;

def : PatAddrGprVgr<int_riscv_vsse_v_f32m1,VSSE_V_um,v4f32>;
def : PatAddrGprVgr<int_riscv_vsse_v_f32m2,VSSE_V_um,v8f32>;
def : PatAddrGprVgr<int_riscv_vsse_v_f32m4,VSSE_V_um,v16f32>;
def : PatAddrGprVgr<int_riscv_vsse_v_f32m8,VSSE_V_um,v32f32>;

def : PatVmAddrGprVgr<int_riscv_vsse_v_8m1_m,VSSE_V_m,v16i8>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_8m2_m,VSSE_V_m,v32i8>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_8m4_m,VSSE_V_m,v64i8>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_8m8_m,VSSE_V_m,v128i8>;

def : PatVmAddrGprVgr<int_riscv_vsse_v_16m1_m,VSSE_V_m,v8i16>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_16m2_m,VSSE_V_m,v16i16>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_16m4_m,VSSE_V_m,v32i16>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_16m8_m,VSSE_V_m,v64i16>;

def : PatVmAddrGprVgr<int_riscv_vsse_v_32m1_m,VSSE_V_m,v4i32>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_32m2_m,VSSE_V_m,v8i32>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_32m4_m,VSSE_V_m,v16i32>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_32m8_m,VSSE_V_m,v32i32>;

def : PatVmAddrGprVgr<int_riscv_vsse_v_f32m1_m,VSSE_V_m,v4f32>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_f32m2_m,VSSE_V_m,v8f32>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_f32m4_m,VSSE_V_m,v16f32>;
def : PatVmAddrGprVgr<int_riscv_vsse_v_f32m8_m,VSSE_V_m,v32f32>;


defm VLSE_V : VLoad_Strided<0b000010, 0b111, "vlse.v">;

class PatAddrGpr<SDPatternOperator OpNode, RVInst Inst>
	: Pat<(OpNode addr:$rs1, GPR:$rs2),(Inst addr:$rs1, GPR:$rs2)>;

class PatVmAddrGpr<SDPatternOperator OpNode, RVInst Inst>
	: Pat<(OpNode VMASK:$vm, addr:$rs1, GPR:$rs2),(Inst VMASK:$vm, addr:$rs1, GPR:$rs2)>;
	
def : PatAddrGpr<int_riscv_vlse_v_8m1,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_8m2,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_8m4,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_8m8,VLSE_V_um>;

def : PatAddrGpr<int_riscv_vlse_v_16m1,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_16m2,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_16m4,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_16m8,VLSE_V_um>;

def : PatAddrGpr<int_riscv_vlse_v_32m1,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_32m2,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_32m4,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_32m8,VLSE_V_um>;

def : PatAddrGpr<int_riscv_vlse_v_f32m1,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_f32m2,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_f32m4,VLSE_V_um>;
def : PatAddrGpr<int_riscv_vlse_v_f32m8,VLSE_V_um>;

def : PatVmAddrGpr<int_riscv_vlse_v_8m1_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_8m2_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_8m4_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_8m8_m,VLSE_V_m>;

def : PatVmAddrGpr<int_riscv_vlse_v_16m1_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_16m2_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_16m4_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_16m8_m,VLSE_V_m>;

def : PatVmAddrGpr<int_riscv_vlse_v_32m1_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_32m2_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_32m4_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_32m8_m,VLSE_V_m>;

def : PatVmAddrGpr<int_riscv_vlse_v_f32m1_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_f32m2_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_f32m4_m,VLSE_V_m>;
def : PatVmAddrGpr<int_riscv_vlse_v_f32m8_m,VLSE_V_m>;

defm VSXE_V : VStore_Indexed<0b000011, 0b111, "vsxe.v">;

class PatAddrVgrVgr<SDPatternOperator OpNode, RVInst Inst, ValueType VecTy>
	: Pat<(OpNode addr:$rs1, VecTy:$vs2, VecTy:$vs3),(Inst addr:$rs1, VecTy:$vs2, VecTy:$vs3)>;

class PatVmAddrVgrVgr<SDPatternOperator OpNode, RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, addr:$rs1, VecTy:$vs2, VecTy:$vs3),(Inst VMASK:$vm, addr:$rs1, VecTy:$vs2, VecTy:$vs3)>;
	
class PatAddrVgrVgrIndex<SDPatternOperator OpNode, RVInst Inst, ValueType VecTy, ValueType VecTy1>
	: Pat<(OpNode addr:$rs1, VecTy:$vs2, VecTy1:$vs3),(Inst addr:$rs1, VecTy:$vs2, VecTy1:$vs3)>;
	
class PatVmAddrVgrVgrIndex<SDPatternOperator OpNode, RVInst Inst, ValueType VecTy, ValueType VecTy1>
	: Pat<(OpNode VMASK:$vm, addr:$rs1, VecTy:$vs2, VecTy1:$vs3),(Inst VMASK:$vm, addr:$rs1, VecTy:$vs2, VecTy1:$vs3)>;

def : PatAddrVgrVgr<int_riscv_vsxe_v_8m1,VSXE_V_um,v16i8>;
def : PatAddrVgrVgr<int_riscv_vsxe_v_8m2,VSXE_V_um,v32i8>;
def : PatAddrVgrVgr<int_riscv_vsxe_v_8m4,VSXE_V_um,v64i8>;
def : PatAddrVgrVgr<int_riscv_vsxe_v_8m8,VSXE_V_um,v128i8>;

def : PatAddrVgrVgr<int_riscv_vsxe_v_16m1,VSXE_V_um,v8i16>;
def : PatAddrVgrVgr<int_riscv_vsxe_v_16m2,VSXE_V_um,v16i16>;
def : PatAddrVgrVgr<int_riscv_vsxe_v_16m4,VSXE_V_um,v32i16>;
def : PatAddrVgrVgr<int_riscv_vsxe_v_16m8,VSXE_V_um,v64i16>;

def : PatAddrVgrVgr<int_riscv_vsxe_v_32m1,VSXE_V_um,v4i32>;
def : PatAddrVgrVgr<int_riscv_vsxe_v_32m2,VSXE_V_um,v8i32>;
def : PatAddrVgrVgr<int_riscv_vsxe_v_32m4,VSXE_V_um,v16i32>;
def : PatAddrVgrVgr<int_riscv_vsxe_v_32m8,VSXE_V_um,v32i32>;

def : PatAddrVgrVgrIndex<int_riscv_vsxe_v_f32m1,VSXE_V_um,v4i32,v4f32>;
def : PatAddrVgrVgrIndex<int_riscv_vsxe_v_f32m2,VSXE_V_um,v8i32,v8f32>;
def : PatAddrVgrVgrIndex<int_riscv_vsxe_v_f32m4,VSXE_V_um,v16i32,v16f32>;
def : PatAddrVgrVgrIndex<int_riscv_vsxe_v_f32m8,VSXE_V_um,v32i32,v32f32>;

def : PatVmAddrVgrVgr<int_riscv_vsxe_v_8m1_m,VSXE_V_m,v16i8>;
def : PatVmAddrVgrVgr<int_riscv_vsxe_v_8m2_m,VSXE_V_m,v32i8>;
def : PatVmAddrVgrVgr<int_riscv_vsxe_v_8m4_m,VSXE_V_m,v64i8>;
def : PatVmAddrVgrVgr<int_riscv_vsxe_v_8m8_m,VSXE_V_m,v128i8>;

def : PatVmAddrVgrVgr<int_riscv_vsxe_v_16m1_m,VSXE_V_m,v8i16>;
def : PatVmAddrVgrVgr<int_riscv_vsxe_v_16m2_m,VSXE_V_m,v16i16>;
def : PatVmAddrVgrVgr<int_riscv_vsxe_v_16m4_m,VSXE_V_m,v32i16>;
def : PatVmAddrVgrVgr<int_riscv_vsxe_v_16m8_m,VSXE_V_m,v64i16>;

def : PatVmAddrVgrVgr<int_riscv_vsxe_v_32m1_m,VSXE_V_m,v4i32>;
def : PatVmAddrVgrVgr<int_riscv_vsxe_v_32m2_m,VSXE_V_m,v8i32>;
def : PatVmAddrVgrVgr<int_riscv_vsxe_v_32m4_m,VSXE_V_m,v16i32>;
def : PatVmAddrVgrVgr<int_riscv_vsxe_v_32m8_m,VSXE_V_m,v32i32>;

def : PatVmAddrVgrVgrIndex<int_riscv_vsxe_v_f32m1_m,VSXE_V_m,v4i32,v4f32>;
def : PatVmAddrVgrVgrIndex<int_riscv_vsxe_v_f32m2_m,VSXE_V_m,v8i32,v8f32>;
def : PatVmAddrVgrVgrIndex<int_riscv_vsxe_v_f32m4_m,VSXE_V_m,v16i32,v16f32>;
def : PatVmAddrVgrVgrIndex<int_riscv_vsxe_v_f32m8_m,VSXE_V_m,v32i32,v32f32>;

defm VSUXE_V : VStore_Indexed<0b000111, 0b111, "vsuxe.v">;
def : PatAddrVgrVgr<int_riscv_vsuxe_v_8m1,VSUXE_V_um,v16i8>;
def : PatAddrVgrVgr<int_riscv_vsuxe_v_8m2,VSUXE_V_um,v32i8>;
def : PatAddrVgrVgr<int_riscv_vsuxe_v_8m4,VSUXE_V_um,v64i8>;
def : PatAddrVgrVgr<int_riscv_vsuxe_v_8m8,VSUXE_V_um,v128i8>;

def : PatAddrVgrVgr<int_riscv_vsuxe_v_16m1,VSUXE_V_um,v8i16>;
def : PatAddrVgrVgr<int_riscv_vsuxe_v_16m2,VSUXE_V_um,v16i16>;
def : PatAddrVgrVgr<int_riscv_vsuxe_v_16m4,VSUXE_V_um,v32i16>;
def : PatAddrVgrVgr<int_riscv_vsuxe_v_16m8,VSUXE_V_um,v64i16>;

def : PatAddrVgrVgr<int_riscv_vsuxe_v_32m1,VSUXE_V_um,v4i32>;
def : PatAddrVgrVgr<int_riscv_vsuxe_v_32m2,VSUXE_V_um,v8i32>;
def : PatAddrVgrVgr<int_riscv_vsuxe_v_32m4,VSUXE_V_um,v16i32>;
def : PatAddrVgrVgr<int_riscv_vsuxe_v_32m8,VSUXE_V_um,v32i32>;

def : PatAddrVgrVgrIndex<int_riscv_vsuxe_v_f32m1,VSUXE_V_um,v4i32,v4f32>;
def : PatAddrVgrVgrIndex<int_riscv_vsuxe_v_f32m2,VSUXE_V_um,v8i32,v8f32>;
def : PatAddrVgrVgrIndex<int_riscv_vsuxe_v_f32m4,VSUXE_V_um,v16i32,v16f32>;
def : PatAddrVgrVgrIndex<int_riscv_vsuxe_v_f32m8,VSUXE_V_um,v32i32,v32f32>;

def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_8m1_m,VSUXE_V_m,v16i8>;
def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_8m2_m,VSUXE_V_m,v32i8>;
def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_8m4_m,VSUXE_V_m,v64i8>;
def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_8m8_m,VSUXE_V_m,v128i8>;

def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_16m1_m,VSUXE_V_m,v8i16>;
def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_16m2_m,VSUXE_V_m,v16i16>;
def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_16m4_m,VSUXE_V_m,v32i16>;
def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_16m8_m,VSUXE_V_m,v64i16>;

def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_32m1_m,VSUXE_V_m,v4i32>;
def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_32m2_m,VSUXE_V_m,v8i32>;
def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_32m4_m,VSUXE_V_m,v16i32>;
def : PatVmAddrVgrVgr<int_riscv_vsuxe_v_32m8_m,VSUXE_V_m,v32i32>;

def : PatVmAddrVgrVgrIndex<int_riscv_vsuxe_v_f32m1_m,VSUXE_V_m,v4i32,v4f32>;
def : PatVmAddrVgrVgrIndex<int_riscv_vsuxe_v_f32m2_m,VSUXE_V_m,v8i32,v8f32>;
def : PatVmAddrVgrVgrIndex<int_riscv_vsuxe_v_f32m4_m,VSUXE_V_m,v16i32,v16f32>;
def : PatVmAddrVgrVgrIndex<int_riscv_vsuxe_v_f32m8_m,VSUXE_V_m,v32i32,v32f32>;

defm VLXE_V : VLoad_Indexed<0b000011, 0b111, "vlxe.v">;

class PatAddrVgr<SDPatternOperator OpNode, RVInst Inst, ValueType VecTy>
	: Pat<(OpNode addr:$rs1, VecTy:$vs2),(Inst addr:$rs1, VecTy:$vs2)>;
	
class PatVmAddrVgr<SDPatternOperator OpNode, RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, addr:$rs1, VecTy:$vs2),(Inst VMASK:$vm, addr:$rs1, VecTy:$vs2)>;	

def : PatAddrVgr<int_riscv_vlxe_v_8m1,VLXE_V_um,v16i8>;
def : PatAddrVgr<int_riscv_vlxe_v_8m2,VLXE_V_um,v32i8>;
def : PatAddrVgr<int_riscv_vlxe_v_8m4,VLXE_V_um,v64i8>;
def : PatAddrVgr<int_riscv_vlxe_v_8m8,VLXE_V_um,v128i8>;

def : PatAddrVgr<int_riscv_vlxe_v_16m1,VLXE_V_um,v8i16>;
def : PatAddrVgr<int_riscv_vlxe_v_16m2,VLXE_V_um,v16i16>;
def : PatAddrVgr<int_riscv_vlxe_v_16m4,VLXE_V_um,v32i16>;
def : PatAddrVgr<int_riscv_vlxe_v_16m8,VLXE_V_um,v64i16>;

def : PatAddrVgr<int_riscv_vlxe_v_32m1,VLXE_V_um,v4i32>;
def : PatAddrVgr<int_riscv_vlxe_v_32m2,VLXE_V_um,v8i32>;
def : PatAddrVgr<int_riscv_vlxe_v_32m4,VLXE_V_um,v16i32>;
def : PatAddrVgr<int_riscv_vlxe_v_32m8,VLXE_V_um,v32i32>;

def : PatAddrVgr<int_riscv_vlxe_v_f32m1,VLXE_V_um,v4i32>;
def : PatAddrVgr<int_riscv_vlxe_v_f32m2,VLXE_V_um,v8i32>;
def : PatAddrVgr<int_riscv_vlxe_v_f32m4,VLXE_V_um,v16i32>;
def : PatAddrVgr<int_riscv_vlxe_v_f32m8,VLXE_V_um,v32i32>;

def : PatVmAddrVgr<int_riscv_vlxe_v_8m1_m,VLXE_V_m,v16i8>;
def : PatVmAddrVgr<int_riscv_vlxe_v_8m2_m,VLXE_V_m,v32i8>;
def : PatVmAddrVgr<int_riscv_vlxe_v_8m4_m,VLXE_V_m,v64i8>;
def : PatVmAddrVgr<int_riscv_vlxe_v_8m8_m,VLXE_V_m,v128i8>;

def : PatVmAddrVgr<int_riscv_vlxe_v_16m1_m,VLXE_V_m,v8i16>;
def : PatVmAddrVgr<int_riscv_vlxe_v_16m2_m,VLXE_V_m,v16i16>;
def : PatVmAddrVgr<int_riscv_vlxe_v_16m4_m,VLXE_V_m,v32i16>;
def : PatVmAddrVgr<int_riscv_vlxe_v_16m8_m,VLXE_V_m,v64i16>;

def : PatVmAddrVgr<int_riscv_vlxe_v_32m1_m,VLXE_V_m,v4i32>;
def : PatVmAddrVgr<int_riscv_vlxe_v_32m2_m,VLXE_V_m,v8i32>;
def : PatVmAddrVgr<int_riscv_vlxe_v_32m4_m,VLXE_V_m,v16i32>;
def : PatVmAddrVgr<int_riscv_vlxe_v_32m8_m,VLXE_V_m,v32i32>;

def : PatVmAddrVgr<int_riscv_vlxe_v_f32m1_m,VLXE_V_m,v4i32>;
def : PatVmAddrVgr<int_riscv_vlxe_v_f32m2_m,VLXE_V_m,v8i32>;
def : PatVmAddrVgr<int_riscv_vlxe_v_f32m4_m,VLXE_V_m,v16i32>;
def : PatVmAddrVgr<int_riscv_vlxe_v_f32m8_m,VLXE_V_m,v32i32>;

/********Vector Unit Stride Fault-Only-First Loads Functions************/
defm VLEFF_V : VLoad_UnitStride_FF<0b000000, 0b111, "vleff.v">;
def : PatAddr<int_riscv_vleff_v_8m1,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_8m2,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_8m4,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_8m8,VLEFF_V_um>;

def : PatAddr<int_riscv_vleff_v_16m1,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_16m2,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_16m4,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_16m8,VLEFF_V_um>;

def : PatAddr<int_riscv_vleff_v_32m1,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_32m2,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_32m4,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_32m8,VLEFF_V_um>;

def : PatAddr<int_riscv_vleff_v_f32m1,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_f32m2,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_f32m4,VLEFF_V_um>;
def : PatAddr<int_riscv_vleff_v_f32m8,VLEFF_V_um>;

def : PatVmAddr<int_riscv_vleff_v_8m1_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_8m2_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_8m4_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_8m8_m,VLEFF_V_m>;

def : PatVmAddr<int_riscv_vleff_v_16m1_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_16m2_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_16m4_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_16m8_m,VLEFF_V_m>;

def : PatVmAddr<int_riscv_vleff_v_32m1_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_32m2_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_32m4_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_32m8_m,VLEFF_V_m>;

def : PatVmAddr<int_riscv_vleff_v_f32m1_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_f32m2_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_f32m4_m,VLEFF_V_m>;
def : PatVmAddr<int_riscv_vleff_v_f32m8_m,VLEFF_V_m>;


class PatFloat<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$rs1),(Inst VecTy:$rs1)>;

class PatGpr<SDPatternOperator OpNode,RVInst Inst>
	: Pat<(OpNode GPR:$rs1),(Inst GPR:$rs1)>;
	
class PatSimm5<SDPatternOperator OpNode,RVInst Inst>
	: Pat<(OpNode simm5:$simm),(Inst simm5:$simm)>;	
		
class PatVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs2),(Inst VecTy:$vs2)>;
	
class PatVmVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs2),(Inst VMASK:$vm, VecTy:$vs2)>;
	
class PatVgrVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs2, VecTy:$vs1),(Inst VecTy:$vs2, VecTy:$vs1)>;

class PatVmVgrVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs2, VecTy:$vs1),(Inst VMASK:$vm, VecTy:$vs2, VecTy:$vs1)>;
	
class PatVgr1Vgr2<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy1, ValueType VecTy2>
	: Pat<(OpNode VecTy1:$vs1, VecTy2:$vs2),(Inst VecTy1:$vs1, VecTy2:$vs2)>;

class PatVmVgr1Vgr2<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy1, ValueType VecTy2>
	: Pat<(OpNode VMASK:$vm, VecTy1:$vs1, VecTy2:$vs2),(Inst VMASK:$vm, VecTy1:$vs1, VecTy2:$vs2)>;
		
class PatVgrVgrVm<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs2, VecTy:$vs1, VMASK:$vm),(Inst VecTy:$vs2, VecTy:$vs1, VMASK:$vm)>;	
	
class PatWidVgrVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy, ValueType VecTy1>
	: Pat<(OpNode VecTy:$vs2, VecTy1:$vs1),(Inst VecTy:$vs2, VecTy1:$vs1)>;
	
class PatVmWidVgrVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy, ValueType VecTy1>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs2, VecTy1:$vs1),(Inst VMASK:$vm, VecTy:$vs2, VecTy1:$vs1)>;	
	
class PatVgrGpr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs2, GPR:$rs1),(Inst VecTy:$vs2, GPR:$rs1)>;	
	
class PatVmVgrGpr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs2, GPR:$rs1),(Inst VMASK:$vm, VecTy:$vs2, GPR:$rs1)>;
	
class PatVgrGprVm<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs2, GPR:$rs1, VMASK:$vm),(Inst VecTy:$vs2, GPR:$rs1, VMASK:$vm)>;
	
class PatWidVgrGpr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs2, GPR:$rs1),(Inst VecTy:$vs2, GPR:$rs1)>;		

class PatVmWidVgrGpr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs2, GPR:$rs1),(Inst VMASK:$vm, VecTy:$vs2, GPR:$rs1)>;
	
class PatVgrSimm5<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs2, simm5:$simm),(Inst VecTy:$vs2, simm5:$simm)>;
	
class PatVmVgrSimm5<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs2, simm5:$simm),(Inst VMASK:$vm, VecTy:$vs2, simm5:$simm)>;
	
class PatVgrSimm5Vm<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs2, simm5:$simm, VMASK:$vm),(Inst VecTy:$vs2, simm5:$simm, VMASK:$vm)>;
	
class PatVgrUimm5<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs2, uimm5:$rs1),(Inst VecTy:$vs2, uimm5:$rs1)>;	
	
class PatVmVgrUimm5<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs2, uimm5:$rs1),(Inst VMASK:$vm, VecTy:$vs2, uimm5:$rs1)>;	
		
class PatVgrFloat<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs2, FPR32:$rs1),(Inst VecTy:$vs2, FPR32:$rs1)>;	

class PatVmVgrFloat<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs2, FPR32:$rs1),(Inst VMASK:$vm, VecTy:$vs2, FPR32:$rs1)>;		
	
class PatVgrVgrVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs3, VecTy:$vs1, VecTy:$vs2),(Inst VecTy:$vs3, VecTy:$vs1, VecTy:$vs2)>;	
	
class PatVmVgrVgrVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs3, VecTy:$vs1, VecTy:$vs2),(Inst VMASK:$vm, VecTy:$vs3, VecTy:$vs1, VecTy:$vs2)>;	
	
class PatVgrGprVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs3, GPR:$rs1, VecTy:$vs2),(Inst VecTy:$vs3, GPR:$rs1, VecTy:$vs2)>;	
	
class PatVmVgrGprVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs3, GPR:$rs1, VecTy:$vs2),(Inst VMASK:$vm, VecTy:$vs3, GPR:$rs1, VecTy:$vs2)>;		
	
class PatWidVgrVgrVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy, ValueType VecTy1>
	: Pat<(OpNode VecTy:$vs3, VecTy1:$vs1, VecTy1:$vs2),(Inst VecTy:$vs3, VecTy1:$vs1, VecTy1:$vs2)>;		
	
class PatVmWidVgrVgrVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy, ValueType VecTy1>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs3, VecTy1:$vs1, VecTy1:$vs2),(Inst VMASK:$vm, VecTy:$vs3, VecTy1:$vs1, VecTy1:$vs2)>;		
	
class PatWidVgrGprVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy, ValueType VecTy1>
	: Pat<(OpNode VecTy:$vs3, GPR:$rs1, VecTy1:$vs2),(Inst VecTy:$vs3, GPR:$rs1, VecTy1:$vs2)>;		
	
class PatVmWidVgrGprVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy, ValueType VecTy1>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs3, GPR:$rs1, VecTy1:$vs2),(Inst VMASK:$vm, VecTy:$vs3, GPR:$rs1, VecTy1:$vs2)>;		
	
class PatVgrFloatVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VecTy:$vs3, FPR32:$rs1, VecTy:$vs2),(Inst VecTy:$vs3, FPR32:$rs1, VecTy:$vs2)>;
	
class PatVmVgrFloatVgr<SDPatternOperator OpNode,RVInst Inst, ValueType VecTy>
	: Pat<(OpNode VMASK:$vm, VecTy:$vs3, FPR32:$rs1, VecTy:$vs2),(Inst VMASK:$vm, VecTy:$vs3, FPR32:$rs1, VecTy:$vs2)>;
	
/*******Vector Single-Width Integer Add and Subtract Instructions**************/

defm  VADD_VV : VALU_OPIVV<0b000000,"vadd.vv">;

def : PatVgrVgr<int_riscv_vadd_vv_8m1,VADD_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vadd_vv_8m2,VADD_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vadd_vv_8m4,VADD_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vadd_vv_8m8,VADD_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vadd_vv_16m1,VADD_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vadd_vv_16m2,VADD_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vadd_vv_16m4,VADD_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vadd_vv_16m8,VADD_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vadd_vv_32m1,VADD_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vadd_vv_32m2,VADD_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vadd_vv_32m4,VADD_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vadd_vv_32m8,VADD_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vadd_vv_8m1_m,VADD_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vadd_vv_8m2_m,VADD_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vadd_vv_8m4_m,VADD_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vadd_vv_8m8_m,VADD_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vadd_vv_16m1_m,VADD_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vadd_vv_16m2_m,VADD_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vadd_vv_16m4_m,VADD_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vadd_vv_16m8_m,VADD_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vadd_vv_32m1_m,VADD_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vadd_vv_32m2_m,VADD_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vadd_vv_32m4_m,VADD_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vadd_vv_32m8_m,VADD_VV_m,v32i32>;

defm VADD_VX : VALU_OPIVX<0b000000,"vadd.vx">;

def : PatVgrGpr<int_riscv_vadd_vx_8m1,VADD_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vadd_vx_8m2,VADD_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vadd_vx_8m4,VADD_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vadd_vx_8m8,VADD_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vadd_vx_16m1,VADD_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vadd_vx_16m2,VADD_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vadd_vx_16m4,VADD_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vadd_vx_16m8,VADD_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vadd_vx_32m1,VADD_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vadd_vx_32m2,VADD_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vadd_vx_32m4,VADD_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vadd_vx_32m8,VADD_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vadd_vx_8m1_m,VADD_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vadd_vx_8m2_m,VADD_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vadd_vx_8m4_m,VADD_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vadd_vx_8m8_m,VADD_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vadd_vx_16m1_m,VADD_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vadd_vx_16m2_m,VADD_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vadd_vx_16m4_m,VADD_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vadd_vx_16m8_m,VADD_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vadd_vx_32m1_m,VADD_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vadd_vx_32m2_m,VADD_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vadd_vx_32m4_m,VADD_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vadd_vx_32m8_m,VADD_VX_m,v32i32>;

defm VADD_VI : VALU_OPIVI_signed<0b000000,"vadd.vi">;

def : PatVgrSimm5<int_riscv_vadd_vi_8m1,VADD_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vadd_vi_8m2,VADD_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vadd_vi_8m4,VADD_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vadd_vi_8m8,VADD_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vadd_vi_16m1,VADD_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vadd_vi_16m2,VADD_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vadd_vi_16m4,VADD_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vadd_vi_16m8,VADD_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vadd_vi_32m1,VADD_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vadd_vi_32m2,VADD_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vadd_vi_32m4,VADD_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vadd_vi_32m8,VADD_VI_um,v32i32>;


def : PatVmVgrSimm5<int_riscv_vadd_vi_8m1_m,VADD_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vadd_vi_8m2_m,VADD_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vadd_vi_8m4_m,VADD_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vadd_vi_8m8_m,VADD_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vadd_vi_16m1_m,VADD_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vadd_vi_16m2_m,VADD_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vadd_vi_16m4_m,VADD_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vadd_vi_16m8_m,VADD_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vadd_vi_32m1_m,VADD_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vadd_vi_32m2_m,VADD_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vadd_vi_32m4_m,VADD_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vadd_vi_32m8_m,VADD_VI_m,v32i32>;

defm VSUB_VV : VALU_OPIVV<0b000010,"vsub.vv">;

def : PatVgrVgr<int_riscv_vsub_vv_8m1,VSUB_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vsub_vv_8m2,VSUB_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vsub_vv_8m4,VSUB_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vsub_vv_8m8,VSUB_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vsub_vv_16m1,VSUB_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vsub_vv_16m2,VSUB_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vsub_vv_16m4,VSUB_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vsub_vv_16m8,VSUB_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vsub_vv_32m1,VSUB_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vsub_vv_32m2,VSUB_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vsub_vv_32m4,VSUB_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vsub_vv_32m8,VSUB_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vsub_vv_8m1_m,VSUB_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vsub_vv_8m2_m,VSUB_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vsub_vv_8m4_m,VSUB_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vsub_vv_8m8_m,VSUB_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vsub_vv_16m1_m,VSUB_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vsub_vv_16m2_m,VSUB_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vsub_vv_16m4_m,VSUB_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vsub_vv_16m8_m,VSUB_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vsub_vv_32m1_m,VSUB_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vsub_vv_32m2_m,VSUB_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vsub_vv_32m4_m,VSUB_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vsub_vv_32m8_m,VSUB_VV_m,v32i32>;

defm VSUB_VX : VALU_OPIVX<0b000010,"vsub.vx">;

def : PatVgrGpr<int_riscv_vsub_vx_8m1,VSUB_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vsub_vx_8m2,VSUB_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vsub_vx_8m4,VSUB_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vsub_vx_8m8,VSUB_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vsub_vx_16m1,VSUB_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vsub_vx_16m2,VSUB_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vsub_vx_16m4,VSUB_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vsub_vx_16m8,VSUB_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vsub_vx_32m1,VSUB_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vsub_vx_32m2,VSUB_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vsub_vx_32m4,VSUB_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vsub_vx_32m8,VSUB_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vsub_vx_8m1_m,VSUB_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vsub_vx_8m2_m,VSUB_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vsub_vx_8m4_m,VSUB_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vsub_vx_8m8_m,VSUB_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vsub_vx_16m1_m,VSUB_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vsub_vx_16m2_m,VSUB_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vsub_vx_16m4_m,VSUB_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vsub_vx_16m8_m,VSUB_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vsub_vx_32m1_m,VSUB_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vsub_vx_32m2_m,VSUB_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vsub_vx_32m4_m,VSUB_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vsub_vx_32m8_m,VSUB_VX_m,v32i32>;

defm VRSUB_VX : VALU_OPIVX<0b000011,"vrsub.vx">;

def : PatVgrGpr<int_riscv_vrsub_vx_8m1,VRSUB_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vrsub_vx_8m2,VRSUB_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vrsub_vx_8m4,VRSUB_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vrsub_vx_8m8,VRSUB_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vrsub_vx_16m1,VRSUB_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vrsub_vx_16m2,VRSUB_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vrsub_vx_16m4,VRSUB_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vrsub_vx_16m8,VRSUB_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vrsub_vx_32m1,VRSUB_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vrsub_vx_32m2,VRSUB_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vrsub_vx_32m4,VRSUB_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vrsub_vx_32m8,VRSUB_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vrsub_vx_8m1_m,VRSUB_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vrsub_vx_8m2_m,VRSUB_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vrsub_vx_8m4_m,VRSUB_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vrsub_vx_8m8_m,VRSUB_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vrsub_vx_16m1_m,VRSUB_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vrsub_vx_16m2_m,VRSUB_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vrsub_vx_16m4_m,VRSUB_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vrsub_vx_16m8_m,VRSUB_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vrsub_vx_32m1_m,VRSUB_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vrsub_vx_32m2_m,VRSUB_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vrsub_vx_32m4_m,VRSUB_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vrsub_vx_32m8_m,VRSUB_VX_m,v32i32>;

defm VRSUB_VI : VALU_OPIVI_signed<0b000011,"vrsub.vi">;

def : PatVgrSimm5<int_riscv_vrsub_vi_8m1,VRSUB_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vrsub_vi_8m2,VRSUB_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vrsub_vi_8m4,VRSUB_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vrsub_vi_8m8,VRSUB_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vrsub_vi_16m1,VRSUB_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vrsub_vi_16m2,VRSUB_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vrsub_vi_16m4,VRSUB_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vrsub_vi_16m8,VRSUB_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vrsub_vi_32m1,VRSUB_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vrsub_vi_32m2,VRSUB_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vrsub_vi_32m4,VRSUB_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vrsub_vi_32m8,VRSUB_VI_um,v32i32>;


def : PatVmVgrSimm5<int_riscv_vrsub_vi_8m1_m,VRSUB_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vrsub_vi_8m2_m,VRSUB_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vrsub_vi_8m4_m,VRSUB_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vrsub_vi_8m8_m,VRSUB_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vrsub_vi_16m1_m,VRSUB_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vrsub_vi_16m2_m,VRSUB_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vrsub_vi_16m4_m,VRSUB_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vrsub_vi_16m8_m,VRSUB_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vrsub_vi_32m1_m,VRSUB_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vrsub_vi_32m2_m,VRSUB_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vrsub_vi_32m4_m,VRSUB_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vrsub_vi_32m8_m,VRSUB_VI_m,v32i32>;


/*******Vector Widening Integer Add/Subtract Functions*******/
defm VWADDU_VV : VALU_OPMVV<0b110000,"vwaddu.vv">;

def : PatVgrVgr<int_riscv_vwaddu_vv_16m2,VWADDU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vwaddu_vv_16m4,VWADDU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vwaddu_vv_16m8,VWADDU_VV_um,v64i8>;

def : PatVgrVgr<int_riscv_vwaddu_vv_32m2,VWADDU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vwaddu_vv_32m4,VWADDU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vwaddu_vv_32m8,VWADDU_VV_um,v32i16>;

def : PatVmVgrVgr<int_riscv_vwaddu_vv_16m2_m,VWADDU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vwaddu_vv_16m4_m,VWADDU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vwaddu_vv_16m8_m,VWADDU_VV_m,v64i8>;

def : PatVmVgrVgr<int_riscv_vwaddu_vv_32m2_m,VWADDU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vwaddu_vv_32m4_m,VWADDU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vwaddu_vv_32m8_m,VWADDU_VV_m,v32i16>;

defm VWADDU_VX : VALU_OPMVX<0b110000,"vwaddu.vx">;

def : PatVgrGpr<int_riscv_vwaddu_vx_16m2,VWADDU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vwaddu_vx_16m4,VWADDU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vwaddu_vx_16m8,VWADDU_VX_um,v64i8>;

def : PatVgrGpr<int_riscv_vwaddu_vx_32m2,VWADDU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vwaddu_vx_32m4,VWADDU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vwaddu_vx_32m8,VWADDU_VX_um,v32i16>;

def : PatVmVgrGpr<int_riscv_vwaddu_vx_16m2_m,VWADDU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vwaddu_vx_16m4_m,VWADDU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vwaddu_vx_16m8_m,VWADDU_VX_m,v64i8>;

def : PatVmVgrGpr<int_riscv_vwaddu_vx_32m2_m,VWADDU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vwaddu_vx_32m4_m,VWADDU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vwaddu_vx_32m8_m,VWADDU_VX_m,v32i16>;

defm VWSUBU_VV : VALU_OPMVV<0b110010,"vwsubu.vv">;

def : PatVgrVgr<int_riscv_vwsubu_vv_16m2,VWSUBU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vwsubu_vv_16m4,VWSUBU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vwsubu_vv_16m8,VWSUBU_VV_um,v64i8>;

def : PatVgrVgr<int_riscv_vwsubu_vv_32m2,VWSUBU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vwsubu_vv_32m4,VWSUBU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vwsubu_vv_32m8,VWSUBU_VV_um,v32i16>;

def : PatVmVgrVgr<int_riscv_vwsubu_vv_16m2_m,VWSUBU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vwsubu_vv_16m4_m,VWSUBU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vwsubu_vv_16m8_m,VWSUBU_VV_m,v64i8>;

def : PatVmVgrVgr<int_riscv_vwsubu_vv_32m2_m,VWSUBU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vwsubu_vv_32m4_m,VWSUBU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vwsubu_vv_32m8_m,VWSUBU_VV_m,v32i16>;

defm VWSUBU_VX : VALU_OPMVX<0b110010,"vwsubu.vx">;

def : PatVgrGpr<int_riscv_vwsubu_vx_16m2,VWSUBU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vwsubu_vx_16m4,VWSUBU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vwsubu_vx_16m8,VWSUBU_VX_um,v64i8>;

def : PatVgrGpr<int_riscv_vwsubu_vx_32m2,VWSUBU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vwsubu_vx_32m4,VWSUBU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vwsubu_vx_32m8,VWSUBU_VX_um,v32i16>;

def : PatVmVgrGpr<int_riscv_vwsubu_vx_16m2_m,VWSUBU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vwsubu_vx_16m4_m,VWSUBU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vwsubu_vx_16m8_m,VWSUBU_VX_m,v64i8>;

def : PatVmVgrGpr<int_riscv_vwsubu_vx_32m2_m,VWSUBU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vwsubu_vx_32m4_m,VWSUBU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vwsubu_vx_32m8_m,VWSUBU_VX_m,v32i16>;

defm VWADD_VV : VALU_OPMVV<0b110001,"vwadd.vv">;

def : PatVgrVgr<int_riscv_vwadd_vv_16m2,VWADD_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vwadd_vv_16m4,VWADD_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vwadd_vv_16m8,VWADD_VV_um,v64i8>;

def : PatVgrVgr<int_riscv_vwadd_vv_32m2,VWADD_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vwadd_vv_32m4,VWADD_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vwadd_vv_32m8,VWADD_VV_um,v32i16>;

def : PatVmVgrVgr<int_riscv_vwadd_vv_16m2_m,VWADD_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vwadd_vv_16m4_m,VWADD_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vwadd_vv_16m8_m,VWADD_VV_m,v64i8>;

def : PatVmVgrVgr<int_riscv_vwadd_vv_32m2_m,VWADD_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vwadd_vv_32m4_m,VWADD_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vwadd_vv_32m8_m,VWADD_VV_m,v32i16>;

defm VWADD_VX : VALU_OPMVX<0b110001,"vwadd.vx">;

def : PatVgrGpr<int_riscv_vwadd_vx_16m2,VWADD_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vwadd_vx_16m4,VWADD_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vwadd_vx_16m8,VWADD_VX_um,v64i8>;

def : PatVgrGpr<int_riscv_vwadd_vx_32m2,VWADD_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vwadd_vx_32m4,VWADD_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vwadd_vx_32m8,VWADD_VX_um,v32i16>;

def : PatVmVgrGpr<int_riscv_vwadd_vx_16m2_m,VWADD_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vwadd_vx_16m4_m,VWADD_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vwadd_vx_16m8_m,VWADD_VX_m,v64i8>;

def : PatVmVgrGpr<int_riscv_vwadd_vx_32m2_m,VWADD_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vwadd_vx_32m4_m,VWADD_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vwadd_vx_32m8_m,VWADD_VX_m,v32i16>;

defm VWSUB_VV : VALU_OPMVV<0b110011,"vwsub.vv">;

def : PatVgrVgr<int_riscv_vwsub_vv_16m2,VWSUB_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vwsub_vv_16m4,VWSUB_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vwsub_vv_16m8,VWSUB_VV_um,v64i8>;

def : PatVgrVgr<int_riscv_vwsub_vv_32m2,VWSUB_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vwsub_vv_32m4,VWSUB_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vwsub_vv_32m8,VWSUB_VV_um,v32i16>;

def : PatVmVgrVgr<int_riscv_vwsub_vv_16m2_m,VWSUB_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vwsub_vv_16m4_m,VWSUB_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vwsub_vv_16m8_m,VWSUB_VV_m,v64i8>;

def : PatVmVgrVgr<int_riscv_vwsub_vv_32m2_m,VWSUB_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vwsub_vv_32m4_m,VWSUB_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vwsub_vv_32m8_m,VWSUB_VV_m,v32i16>;

defm VWSUB_VX : VALU_OPMVX<0b110011,"vwsub.vx">;

def : PatVgrGpr<int_riscv_vwsub_vx_16m2,VWSUB_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vwsub_vx_16m4,VWSUB_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vwsub_vx_16m8,VWSUB_VX_um,v64i8>;

def : PatVgrGpr<int_riscv_vwsub_vx_32m2,VWSUB_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vwsub_vx_32m4,VWSUB_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vwsub_vx_32m8,VWSUB_VX_um,v32i16>;

def : PatVmVgrGpr<int_riscv_vwsub_vx_16m2_m,VWSUB_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vwsub_vx_16m4_m,VWSUB_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vwsub_vx_16m8_m,VWSUB_VX_m,v64i8>;

def : PatVmVgrGpr<int_riscv_vwsub_vx_32m2_m,VWSUB_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vwsub_vx_32m4_m,VWSUB_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vwsub_vx_32m8_m,VWSUB_VX_m,v32i16>;

defm VWADDU_WV : VALU_OPMVV<0b110100,"vwaddu.wv">;

def : PatWidVgrVgr<int_riscv_vwaddu_wv_16m2,VWADDU_WV_um,v16i16,v16i8>;
def : PatWidVgrVgr<int_riscv_vwaddu_wv_16m4,VWADDU_WV_um,v32i16,v32i8>;
def : PatWidVgrVgr<int_riscv_vwaddu_wv_16m8,VWADDU_WV_um,v64i16,v64i8>;

def : PatWidVgrVgr<int_riscv_vwaddu_wv_32m2,VWADDU_WV_um,v8i32,v8i16>;
def : PatWidVgrVgr<int_riscv_vwaddu_wv_32m4,VWADDU_WV_um,v16i32,v16i16>;
def : PatWidVgrVgr<int_riscv_vwaddu_wv_32m8,VWADDU_WV_um,v32i32,v32i16>;

def : PatVmWidVgrVgr<int_riscv_vwaddu_wv_16m2_m,VWADDU_WV_m,v16i16,v16i8>;
def : PatVmWidVgrVgr<int_riscv_vwaddu_wv_16m4_m,VWADDU_WV_m,v32i16,v32i8>;
def : PatVmWidVgrVgr<int_riscv_vwaddu_wv_16m8_m,VWADDU_WV_m,v64i16,v64i8>;

def : PatVmWidVgrVgr<int_riscv_vwaddu_wv_32m2_m,VWADDU_WV_m,v8i32,v8i16>;
def : PatVmWidVgrVgr<int_riscv_vwaddu_wv_32m4_m,VWADDU_WV_m,v16i32,v16i16>;
def : PatVmWidVgrVgr<int_riscv_vwaddu_wv_32m8_m,VWADDU_WV_m,v32i32,v32i16>;

defm VWADDU_WX : VALU_OPMVX<0b110100,"vwaddu.wx">;

def : PatWidVgrGpr<int_riscv_vwaddu_wx_16m2,VWADDU_WX_um,v16i16>;
def : PatWidVgrGpr<int_riscv_vwaddu_wx_16m4,VWADDU_WX_um,v32i16>;
def : PatWidVgrGpr<int_riscv_vwaddu_wx_16m8,VWADDU_WX_um,v64i16>;

def : PatWidVgrGpr<int_riscv_vwaddu_wx_32m2,VWADDU_WX_um,v8i32>;
def : PatWidVgrGpr<int_riscv_vwaddu_wx_32m4,VWADDU_WX_um,v16i32>;
def : PatWidVgrGpr<int_riscv_vwaddu_wx_32m8,VWADDU_WX_um,v32i32>;

def : PatVmWidVgrGpr<int_riscv_vwaddu_wx_16m2_m,VWADDU_WX_m,v16i16>;
def : PatVmWidVgrGpr<int_riscv_vwaddu_wx_16m4_m,VWADDU_WX_m,v32i16>;
def : PatVmWidVgrGpr<int_riscv_vwaddu_wx_16m8_m,VWADDU_WX_m,v64i16>;

def : PatVmWidVgrGpr<int_riscv_vwaddu_wx_32m2_m,VWADDU_WX_m,v8i32>;
def : PatVmWidVgrGpr<int_riscv_vwaddu_wx_32m4_m,VWADDU_WX_m,v16i32>;
def : PatVmWidVgrGpr<int_riscv_vwaddu_wx_32m8_m,VWADDU_WX_m,v32i32>;

defm VWSUBU_WV : VALU_OPMVV<0b110110,"vwsubu.wv">;

def : PatWidVgrVgr<int_riscv_vwsubu_wv_16m2,VWSUBU_WV_um,v16i16,v16i8>;
def : PatWidVgrVgr<int_riscv_vwsubu_wv_16m4,VWSUBU_WV_um,v32i16,v32i8>;
def : PatWidVgrVgr<int_riscv_vwsubu_wv_16m8,VWSUBU_WV_um,v64i16,v64i8>;

def : PatWidVgrVgr<int_riscv_vwsubu_wv_32m2,VWSUBU_WV_um,v8i32,v8i16>;
def : PatWidVgrVgr<int_riscv_vwsubu_wv_32m4,VWSUBU_WV_um,v16i32,v16i16>;
def : PatWidVgrVgr<int_riscv_vwsubu_wv_32m8,VWSUBU_WV_um,v32i32,v32i16>;

def : PatVmWidVgrVgr<int_riscv_vwsubu_wv_16m2_m,VWSUBU_WV_m,v16i16,v16i8>;
def : PatVmWidVgrVgr<int_riscv_vwsubu_wv_16m4_m,VWSUBU_WV_m,v32i16,v32i8>;
def : PatVmWidVgrVgr<int_riscv_vwsubu_wv_16m8_m,VWSUBU_WV_m,v64i16,v64i8>;

def : PatVmWidVgrVgr<int_riscv_vwsubu_wv_32m2_m,VWSUBU_WV_m,v8i32,v8i16>;
def : PatVmWidVgrVgr<int_riscv_vwsubu_wv_32m4_m,VWSUBU_WV_m,v16i32,v16i16>;
def : PatVmWidVgrVgr<int_riscv_vwsubu_wv_32m8_m,VWSUBU_WV_m,v32i32,v32i16>;

defm VWSUBU_WX : VALU_OPMVX<0b110110,"vwsubu.wx">;

def : PatWidVgrGpr<int_riscv_vwsubu_wx_16m2,VWSUBU_WX_um,v16i16>;
def : PatWidVgrGpr<int_riscv_vwsubu_wx_16m4,VWSUBU_WX_um,v32i16>;
def : PatWidVgrGpr<int_riscv_vwsubu_wx_16m8,VWSUBU_WX_um,v64i16>;

def : PatWidVgrGpr<int_riscv_vwsubu_wx_32m2,VWSUBU_WX_um,v8i32>;
def : PatWidVgrGpr<int_riscv_vwsubu_wx_32m4,VWSUBU_WX_um,v16i32>;
def : PatWidVgrGpr<int_riscv_vwsubu_wx_32m8,VWSUBU_WX_um,v32i32>;

def : PatVmWidVgrGpr<int_riscv_vwsubu_wx_16m2_m,VWSUBU_WX_m,v16i16>;
def : PatVmWidVgrGpr<int_riscv_vwsubu_wx_16m4_m,VWSUBU_WX_m,v32i16>;
def : PatVmWidVgrGpr<int_riscv_vwsubu_wx_16m8_m,VWSUBU_WX_m,v64i16>;

def : PatVmWidVgrGpr<int_riscv_vwsubu_wx_32m2_m,VWSUBU_WX_m,v8i32>;
def : PatVmWidVgrGpr<int_riscv_vwsubu_wx_32m4_m,VWSUBU_WX_m,v16i32>;
def : PatVmWidVgrGpr<int_riscv_vwsubu_wx_32m8_m,VWSUBU_WX_m,v32i32>;

defm VWADD_WV : VALU_OPMVV<0b110101,"vwadd.wv">;

def : PatWidVgrVgr<int_riscv_vwadd_wv_16m2,VWADD_WV_um,v16i16,v16i8>;
def : PatWidVgrVgr<int_riscv_vwadd_wv_16m4,VWADD_WV_um,v32i16,v32i8>;
def : PatWidVgrVgr<int_riscv_vwadd_wv_16m8,VWADD_WV_um,v64i16,v64i8>;

def : PatWidVgrVgr<int_riscv_vwadd_wv_32m2,VWADD_WV_um,v8i32,v8i16>;
def : PatWidVgrVgr<int_riscv_vwadd_wv_32m4,VWADD_WV_um,v16i32,v16i16>;
def : PatWidVgrVgr<int_riscv_vwadd_wv_32m8,VWADD_WV_um,v32i32,v32i16>;

def : PatVmWidVgrVgr<int_riscv_vwadd_wv_16m2_m,VWADD_WV_m,v16i16,v16i8>;
def : PatVmWidVgrVgr<int_riscv_vwadd_wv_16m4_m,VWADD_WV_m,v32i16,v32i8>;
def : PatVmWidVgrVgr<int_riscv_vwadd_wv_16m8_m,VWADD_WV_m,v64i16,v64i8>;

def : PatVmWidVgrVgr<int_riscv_vwadd_wv_32m2_m,VWADD_WV_m,v8i32,v8i16>;
def : PatVmWidVgrVgr<int_riscv_vwadd_wv_32m4_m,VWADD_WV_m,v16i32,v16i16>;
def : PatVmWidVgrVgr<int_riscv_vwadd_wv_32m8_m,VWADD_WV_m,v32i32,v32i16>;

defm VWADD_WX : VALU_OPMVX<0b110101,"vwadd.wx">;

def : PatWidVgrGpr<int_riscv_vwadd_wx_16m2,VWADD_WX_um,v16i16>;
def : PatWidVgrGpr<int_riscv_vwadd_wx_16m4,VWADD_WX_um,v32i16>;
def : PatWidVgrGpr<int_riscv_vwadd_wx_16m8,VWADD_WX_um,v64i16>;

def : PatWidVgrGpr<int_riscv_vwadd_wx_32m2,VWADD_WX_um,v8i32>;
def : PatWidVgrGpr<int_riscv_vwadd_wx_32m4,VWADD_WX_um,v16i32>;
def : PatWidVgrGpr<int_riscv_vwadd_wx_32m8,VWADD_WX_um,v32i32>;

def : PatVmWidVgrGpr<int_riscv_vwadd_wx_16m2_m,VWADD_WX_m,v16i16>;
def : PatVmWidVgrGpr<int_riscv_vwadd_wx_16m4_m,VWADD_WX_m,v32i16>;
def : PatVmWidVgrGpr<int_riscv_vwadd_wx_16m8_m,VWADD_WX_m,v64i16>;

def : PatVmWidVgrGpr<int_riscv_vwadd_wx_32m2_m,VWADD_WX_m,v8i32>;
def : PatVmWidVgrGpr<int_riscv_vwadd_wx_32m4_m,VWADD_WX_m,v16i32>;
def : PatVmWidVgrGpr<int_riscv_vwadd_wx_32m8_m,VWADD_WX_m,v32i32>;

defm VWSUB_WV : VALU_OPMVV<0b110111,"vwsub.wv">;

def : PatWidVgrVgr<int_riscv_vwsub_wv_16m2,VWSUB_WV_um,v16i16,v16i8>;
def : PatWidVgrVgr<int_riscv_vwsub_wv_16m4,VWSUB_WV_um,v32i16,v32i8>;
def : PatWidVgrVgr<int_riscv_vwsub_wv_16m8,VWSUB_WV_um,v64i16,v64i8>;

def : PatWidVgrVgr<int_riscv_vwsub_wv_32m2,VWSUB_WV_um,v8i32,v8i16>;
def : PatWidVgrVgr<int_riscv_vwsub_wv_32m4,VWSUB_WV_um,v16i32,v16i16>;
def : PatWidVgrVgr<int_riscv_vwsub_wv_32m8,VWSUB_WV_um,v32i32,v32i16>;

def : PatVmWidVgrVgr<int_riscv_vwsub_wv_16m2_m,VWSUB_WV_m,v16i16,v16i8>;
def : PatVmWidVgrVgr<int_riscv_vwsub_wv_16m4_m,VWSUB_WV_m,v32i16,v32i8>;
def : PatVmWidVgrVgr<int_riscv_vwsub_wv_16m8_m,VWSUB_WV_m,v64i16,v64i8>;

def : PatVmWidVgrVgr<int_riscv_vwsub_wv_32m2_m,VWSUB_WV_m,v8i32,v8i16>;
def : PatVmWidVgrVgr<int_riscv_vwsub_wv_32m4_m,VWSUB_WV_m,v16i32,v16i16>;
def : PatVmWidVgrVgr<int_riscv_vwsub_wv_32m8_m,VWSUB_WV_m,v32i32,v32i16>;

defm VWSUB_WX : VALU_OPMVX<0b110111,"vwsub.wx">;

def : PatWidVgrGpr<int_riscv_vwsub_wx_16m2,VWSUB_WX_um,v16i16>;
def : PatWidVgrGpr<int_riscv_vwsub_wx_16m4,VWSUB_WX_um,v32i16>;
def : PatWidVgrGpr<int_riscv_vwsub_wx_16m8,VWSUB_WX_um,v64i16>;

def : PatWidVgrGpr<int_riscv_vwsub_wx_32m2,VWSUB_WX_um,v8i32>;
def : PatWidVgrGpr<int_riscv_vwsub_wx_32m4,VWSUB_WX_um,v16i32>;
def : PatWidVgrGpr<int_riscv_vwsub_wx_32m8,VWSUB_WX_um,v32i32>;

def : PatVmWidVgrGpr<int_riscv_vwsub_wx_16m2_m,VWSUB_WX_m,v16i16>;
def : PatVmWidVgrGpr<int_riscv_vwsub_wx_16m4_m,VWSUB_WX_m,v32i16>;
def : PatVmWidVgrGpr<int_riscv_vwsub_wx_16m8_m,VWSUB_WX_m,v64i16>;

def : PatVmWidVgrGpr<int_riscv_vwsub_wx_32m2_m,VWSUB_WX_m,v8i32>;
def : PatVmWidVgrGpr<int_riscv_vwsub_wx_32m4_m,VWSUB_WX_m,v16i32>;
def : PatVmWidVgrGpr<int_riscv_vwsub_wx_32m8_m,VWSUB_WX_m,v32i32>;


def VADC_VVM  : VALU_OPIVV_m<0b010000,"vadc.vvm">;

def : PatVgrVgrVm<int_riscv_vadc_vvm_8m1,VADC_VVM,v16i8>;
def : PatVgrVgrVm<int_riscv_vadc_vvm_8m2,VADC_VVM,v32i8>;
def : PatVgrVgrVm<int_riscv_vadc_vvm_8m4,VADC_VVM,v64i8>;
def : PatVgrVgrVm<int_riscv_vadc_vvm_8m8,VADC_VVM,v128i8>;

def : PatVgrVgrVm<int_riscv_vadc_vvm_16m1,VADC_VVM,v8i16>;
def : PatVgrVgrVm<int_riscv_vadc_vvm_16m2,VADC_VVM,v16i16>;
def : PatVgrVgrVm<int_riscv_vadc_vvm_16m4,VADC_VVM,v32i16>;
def : PatVgrVgrVm<int_riscv_vadc_vvm_16m8,VADC_VVM,v64i16>;

def : PatVgrVgrVm<int_riscv_vadc_vvm_32m1,VADC_VVM,v4i32>;
def : PatVgrVgrVm<int_riscv_vadc_vvm_32m2,VADC_VVM,v8i32>;
def : PatVgrVgrVm<int_riscv_vadc_vvm_32m4,VADC_VVM,v16i32>;
def : PatVgrVgrVm<int_riscv_vadc_vvm_32m8,VADC_VVM,v32i32>;

def VADC_VXM : VALU_OPIVX_m<0b010000,"vadc.vxm">;

def : PatVgrGprVm<int_riscv_vadc_vxm_8m1,VADC_VXM,v16i8>;
def : PatVgrGprVm<int_riscv_vadc_vxm_8m2,VADC_VXM,v32i8>;
def : PatVgrGprVm<int_riscv_vadc_vxm_8m4,VADC_VXM,v64i8>;
def : PatVgrGprVm<int_riscv_vadc_vxm_8m8,VADC_VXM,v128i8>;

def : PatVgrGprVm<int_riscv_vadc_vxm_16m1,VADC_VXM,v8i16>;
def : PatVgrGprVm<int_riscv_vadc_vxm_16m2,VADC_VXM,v16i16>;
def : PatVgrGprVm<int_riscv_vadc_vxm_16m4,VADC_VXM,v32i16>;
def : PatVgrGprVm<int_riscv_vadc_vxm_16m8,VADC_VXM,v64i16>;

def : PatVgrGprVm<int_riscv_vadc_vxm_32m1,VADC_VXM,v4i32>;
def : PatVgrGprVm<int_riscv_vadc_vxm_32m2,VADC_VXM,v8i32>;
def : PatVgrGprVm<int_riscv_vadc_vxm_32m4,VADC_VXM,v16i32>;
def : PatVgrGprVm<int_riscv_vadc_vxm_32m8,VADC_VXM,v32i32>;

def VADC_VIM : VALU_OPIVI_m<0b010000,"vadc.vim">;

def : PatVgrSimm5Vm<int_riscv_vadc_vim_8m1,VADC_VIM,v16i8>;
def : PatVgrSimm5Vm<int_riscv_vadc_vim_8m2,VADC_VIM,v32i8>;
def : PatVgrSimm5Vm<int_riscv_vadc_vim_8m4,VADC_VIM,v64i8>;
def : PatVgrSimm5Vm<int_riscv_vadc_vim_8m8,VADC_VIM,v128i8>;

def : PatVgrSimm5Vm<int_riscv_vadc_vim_16m1,VADC_VIM,v8i16>;
def : PatVgrSimm5Vm<int_riscv_vadc_vim_16m2,VADC_VIM,v16i16>;
def : PatVgrSimm5Vm<int_riscv_vadc_vim_16m4,VADC_VIM,v32i16>;
def : PatVgrSimm5Vm<int_riscv_vadc_vim_16m8,VADC_VIM,v64i16>;

def : PatVgrSimm5Vm<int_riscv_vadc_vim_32m1,VADC_VIM,v4i32>;
def : PatVgrSimm5Vm<int_riscv_vadc_vim_32m2,VADC_VIM,v8i32>;
def : PatVgrSimm5Vm<int_riscv_vadc_vim_32m4,VADC_VIM,v16i32>;
def : PatVgrSimm5Vm<int_riscv_vadc_vim_32m8,VADC_VIM,v32i32>;

def VMADC_VVM : VALU_OPIVV_m<0b010001,"vmadc.vvm">;

def : PatVgrVgrVm<int_riscv_vmadc_vvm_8m1,VMADC_VVM,v16i8>;
def : PatVgrVgrVm<int_riscv_vmadc_vvm_8m2,VMADC_VVM,v32i8>;
def : PatVgrVgrVm<int_riscv_vmadc_vvm_8m4,VMADC_VVM,v64i8>;
def : PatVgrVgrVm<int_riscv_vmadc_vvm_8m8,VMADC_VVM,v128i8>;

def : PatVgrVgrVm<int_riscv_vmadc_vvm_16m1,VMADC_VVM,v8i16>;
def : PatVgrVgrVm<int_riscv_vmadc_vvm_16m2,VMADC_VVM,v16i16>;
def : PatVgrVgrVm<int_riscv_vmadc_vvm_16m4,VMADC_VVM,v32i16>;
def : PatVgrVgrVm<int_riscv_vmadc_vvm_16m8,VMADC_VVM,v64i16>;

def : PatVgrVgrVm<int_riscv_vmadc_vvm_32m1,VMADC_VVM,v4i32>;
def : PatVgrVgrVm<int_riscv_vmadc_vvm_32m2,VMADC_VVM,v8i32>;
def : PatVgrVgrVm<int_riscv_vmadc_vvm_32m4,VMADC_VVM,v16i32>;
def : PatVgrVgrVm<int_riscv_vmadc_vvm_32m8,VMADC_VVM,v32i32>;

def VMADC_VXM : VALU_OPIVX_m<0b010001,"vmadc.vxm">;

def : PatVgrGprVm<int_riscv_vmadc_vxm_8m1,VMADC_VXM,v16i8>;
def : PatVgrGprVm<int_riscv_vmadc_vxm_8m2,VMADC_VXM,v32i8>;
def : PatVgrGprVm<int_riscv_vmadc_vxm_8m4,VMADC_VXM,v64i8>;
def : PatVgrGprVm<int_riscv_vmadc_vxm_8m8,VMADC_VXM,v128i8>;

def : PatVgrGprVm<int_riscv_vmadc_vxm_16m1,VMADC_VXM,v8i16>;
def : PatVgrGprVm<int_riscv_vmadc_vxm_16m2,VMADC_VXM,v16i16>;
def : PatVgrGprVm<int_riscv_vmadc_vxm_16m4,VMADC_VXM,v32i16>;
def : PatVgrGprVm<int_riscv_vmadc_vxm_16m8,VMADC_VXM,v64i16>;

def : PatVgrGprVm<int_riscv_vmadc_vxm_32m1,VMADC_VXM,v4i32>;
def : PatVgrGprVm<int_riscv_vmadc_vxm_32m2,VMADC_VXM,v8i32>;
def : PatVgrGprVm<int_riscv_vmadc_vxm_32m4,VMADC_VXM,v16i32>;
def : PatVgrGprVm<int_riscv_vmadc_vxm_32m8,VMADC_VXM,v32i32>;

def VMADC_VIM : VALU_OPIVI_m<0b010001,"vmadc.vim">;

def : PatVgrSimm5Vm<int_riscv_vmadc_vim_8m1,VMADC_VIM,v16i8>;
def : PatVgrSimm5Vm<int_riscv_vmadc_vim_8m2,VMADC_VIM,v32i8>;
def : PatVgrSimm5Vm<int_riscv_vmadc_vim_8m4,VMADC_VIM,v64i8>;
def : PatVgrSimm5Vm<int_riscv_vmadc_vim_8m8,VMADC_VIM,v128i8>;

def : PatVgrSimm5Vm<int_riscv_vmadc_vim_16m1,VMADC_VIM,v8i16>;
def : PatVgrSimm5Vm<int_riscv_vmadc_vim_16m2,VMADC_VIM,v16i16>;
def : PatVgrSimm5Vm<int_riscv_vmadc_vim_16m4,VMADC_VIM,v32i16>;
def : PatVgrSimm5Vm<int_riscv_vmadc_vim_16m8,VMADC_VIM,v64i16>;

def : PatVgrSimm5Vm<int_riscv_vmadc_vim_32m1,VMADC_VIM,v4i32>;
def : PatVgrSimm5Vm<int_riscv_vmadc_vim_32m2,VMADC_VIM,v8i32>;
def : PatVgrSimm5Vm<int_riscv_vmadc_vim_32m4,VMADC_VIM,v16i32>;
def : PatVgrSimm5Vm<int_riscv_vmadc_vim_32m8,VMADC_VIM,v32i32>;

def VMADC_VV : VALU_OPIVV_um<0b010001,"vmadc.vv">;

def : PatVgrVgr<int_riscv_vmadc_vv_8m1,VMADC_VV,v16i8>;
def : PatVgrVgr<int_riscv_vmadc_vv_8m2,VMADC_VV,v32i8>;
def : PatVgrVgr<int_riscv_vmadc_vv_8m4,VMADC_VV,v64i8>;
def : PatVgrVgr<int_riscv_vmadc_vv_8m8,VMADC_VV,v128i8>;

def : PatVgrVgr<int_riscv_vmadc_vv_16m1,VMADC_VV,v8i16>;
def : PatVgrVgr<int_riscv_vmadc_vv_16m2,VMADC_VV,v16i16>;
def : PatVgrVgr<int_riscv_vmadc_vv_16m4,VMADC_VV,v32i16>;
def : PatVgrVgr<int_riscv_vmadc_vv_16m8,VMADC_VV,v64i16>;

def : PatVgrVgr<int_riscv_vmadc_vv_32m1,VMADC_VV,v4i32>;
def : PatVgrVgr<int_riscv_vmadc_vv_32m2,VMADC_VV,v8i32>;
def : PatVgrVgr<int_riscv_vmadc_vv_32m4,VMADC_VV,v16i32>;
def : PatVgrVgr<int_riscv_vmadc_vv_32m8,VMADC_VV,v32i32>;

def VMADC_VX : VALU_OPIVX_um<0b010001,"vmadc.vx">;

def : PatVgrGpr<int_riscv_vmadc_vx_8m1,VMADC_VX,v16i8>;
def : PatVgrGpr<int_riscv_vmadc_vx_8m2,VMADC_VX,v32i8>;
def : PatVgrGpr<int_riscv_vmadc_vx_8m4,VMADC_VX,v64i8>;
def : PatVgrGpr<int_riscv_vmadc_vx_8m8,VMADC_VX,v128i8>;

def : PatVgrGpr<int_riscv_vmadc_vx_16m1,VMADC_VX,v8i16>;
def : PatVgrGpr<int_riscv_vmadc_vx_16m2,VMADC_VX,v16i16>;
def : PatVgrGpr<int_riscv_vmadc_vx_16m4,VMADC_VX,v32i16>;
def : PatVgrGpr<int_riscv_vmadc_vx_16m8,VMADC_VX,v64i16>;

def : PatVgrGpr<int_riscv_vmadc_vx_32m1,VMADC_VX,v4i32>;
def : PatVgrGpr<int_riscv_vmadc_vx_32m2,VMADC_VX,v8i32>;
def : PatVgrGpr<int_riscv_vmadc_vx_32m4,VMADC_VX,v16i32>;
def : PatVgrGpr<int_riscv_vmadc_vx_32m8,VMADC_VX,v32i32>;

def VMADC_VI : VALU_OPIVI_um<0b010001,"vmadc.vi">;

def : PatVgrSimm5<int_riscv_vmadc_vi_8m1,VMADC_VI,v16i8>;
def : PatVgrSimm5<int_riscv_vmadc_vi_8m2,VMADC_VI,v32i8>;
def : PatVgrSimm5<int_riscv_vmadc_vi_8m4,VMADC_VI,v64i8>;
def : PatVgrSimm5<int_riscv_vmadc_vi_8m8,VMADC_VI,v128i8>;

def : PatVgrSimm5<int_riscv_vmadc_vi_16m1,VMADC_VI,v8i16>;
def : PatVgrSimm5<int_riscv_vmadc_vi_16m2,VMADC_VI,v16i16>;
def : PatVgrSimm5<int_riscv_vmadc_vi_16m4,VMADC_VI,v32i16>;
def : PatVgrSimm5<int_riscv_vmadc_vi_16m8,VMADC_VI,v64i16>;

def : PatVgrSimm5<int_riscv_vmadc_vi_32m1,VMADC_VI,v4i32>;
def : PatVgrSimm5<int_riscv_vmadc_vi_32m2,VMADC_VI,v8i32>;
def : PatVgrSimm5<int_riscv_vmadc_vi_32m4,VMADC_VI,v16i32>;
def : PatVgrSimm5<int_riscv_vmadc_vi_32m8,VMADC_VI,v32i32>;


def VSBC_VVM : VALU_OPIVV_m<0b010010,"vsbc.vvm">;

def : PatVgrVgrVm<int_riscv_vsbc_vvm_8m1,VSBC_VVM,v16i8>;
def : PatVgrVgrVm<int_riscv_vsbc_vvm_8m2,VSBC_VVM,v32i8>;
def : PatVgrVgrVm<int_riscv_vsbc_vvm_8m4,VSBC_VVM,v64i8>;
def : PatVgrVgrVm<int_riscv_vsbc_vvm_8m8,VSBC_VVM,v128i8>;

def : PatVgrVgrVm<int_riscv_vsbc_vvm_16m1,VSBC_VVM,v8i16>;
def : PatVgrVgrVm<int_riscv_vsbc_vvm_16m2,VSBC_VVM,v16i16>;
def : PatVgrVgrVm<int_riscv_vsbc_vvm_16m4,VSBC_VVM,v32i16>;
def : PatVgrVgrVm<int_riscv_vsbc_vvm_16m8,VSBC_VVM,v64i16>;

def : PatVgrVgrVm<int_riscv_vsbc_vvm_32m1,VSBC_VVM,v4i32>;
def : PatVgrVgrVm<int_riscv_vsbc_vvm_32m2,VSBC_VVM,v8i32>;
def : PatVgrVgrVm<int_riscv_vsbc_vvm_32m4,VSBC_VVM,v16i32>;
def : PatVgrVgrVm<int_riscv_vsbc_vvm_32m8,VSBC_VVM,v32i32>;

def VSBC_VXM : VALU_OPIVX_m<0b010010,"vsbc.vxm">;

def : PatVgrGprVm<int_riscv_vsbc_vxm_8m1,VSBC_VXM,v16i8>;
def : PatVgrGprVm<int_riscv_vsbc_vxm_8m2,VSBC_VXM,v32i8>;
def : PatVgrGprVm<int_riscv_vsbc_vxm_8m4,VSBC_VXM,v64i8>;
def : PatVgrGprVm<int_riscv_vsbc_vxm_8m8,VSBC_VXM,v128i8>;

def : PatVgrGprVm<int_riscv_vsbc_vxm_16m1,VSBC_VXM,v8i16>;
def : PatVgrGprVm<int_riscv_vsbc_vxm_16m2,VSBC_VXM,v16i16>;
def : PatVgrGprVm<int_riscv_vsbc_vxm_16m4,VSBC_VXM,v32i16>;
def : PatVgrGprVm<int_riscv_vsbc_vxm_16m8,VSBC_VXM,v64i16>;

def : PatVgrGprVm<int_riscv_vsbc_vxm_32m1,VSBC_VXM,v4i32>;
def : PatVgrGprVm<int_riscv_vsbc_vxm_32m2,VSBC_VXM,v8i32>;
def : PatVgrGprVm<int_riscv_vsbc_vxm_32m4,VSBC_VXM,v16i32>;
def : PatVgrGprVm<int_riscv_vsbc_vxm_32m8,VSBC_VXM,v32i32>;

def VMSBC_VVM : VALU_OPIVV_m<0b010011,"vmsbc.vvm">;

def : PatVgrVgrVm<int_riscv_vmsbc_vvm_8m1,VMSBC_VVM,v16i8>;
def : PatVgrVgrVm<int_riscv_vmsbc_vvm_8m2,VMSBC_VVM,v32i8>;
def : PatVgrVgrVm<int_riscv_vmsbc_vvm_8m4,VMSBC_VVM,v64i8>;
def : PatVgrVgrVm<int_riscv_vmsbc_vvm_8m8,VMSBC_VVM,v128i8>;

def : PatVgrVgrVm<int_riscv_vmsbc_vvm_16m1,VMSBC_VVM,v8i16>;
def : PatVgrVgrVm<int_riscv_vmsbc_vvm_16m2,VMSBC_VVM,v16i16>;
def : PatVgrVgrVm<int_riscv_vmsbc_vvm_16m4,VMSBC_VVM,v32i16>;
def : PatVgrVgrVm<int_riscv_vmsbc_vvm_16m8,VMSBC_VVM,v64i16>;

def : PatVgrVgrVm<int_riscv_vmsbc_vvm_32m1,VMSBC_VVM,v4i32>;
def : PatVgrVgrVm<int_riscv_vmsbc_vvm_32m2,VMSBC_VVM,v8i32>;
def : PatVgrVgrVm<int_riscv_vmsbc_vvm_32m4,VMSBC_VVM,v16i32>;
def : PatVgrVgrVm<int_riscv_vmsbc_vvm_32m8,VMSBC_VVM,v32i32>;

def VMSBC_VXM : VALU_OPIVX_m<0b010011,"vmsbc.vxm">;

def : PatVgrGprVm<int_riscv_vmsbc_vxm_8m1,VMSBC_VXM,v16i8>;
def : PatVgrGprVm<int_riscv_vmsbc_vxm_8m2,VMSBC_VXM,v32i8>;
def : PatVgrGprVm<int_riscv_vmsbc_vxm_8m4,VMSBC_VXM,v64i8>;
def : PatVgrGprVm<int_riscv_vmsbc_vxm_8m8,VMSBC_VXM,v128i8>;

def : PatVgrGprVm<int_riscv_vmsbc_vxm_16m1,VMSBC_VXM,v8i16>;
def : PatVgrGprVm<int_riscv_vmsbc_vxm_16m2,VMSBC_VXM,v16i16>;
def : PatVgrGprVm<int_riscv_vmsbc_vxm_16m4,VMSBC_VXM,v32i16>;
def : PatVgrGprVm<int_riscv_vmsbc_vxm_16m8,VMSBC_VXM,v64i16>;

def : PatVgrGprVm<int_riscv_vmsbc_vxm_32m1,VMSBC_VXM,v4i32>;
def : PatVgrGprVm<int_riscv_vmsbc_vxm_32m2,VMSBC_VXM,v8i32>;
def : PatVgrGprVm<int_riscv_vmsbc_vxm_32m4,VMSBC_VXM,v16i32>;
def : PatVgrGprVm<int_riscv_vmsbc_vxm_32m8,VMSBC_VXM,v32i32>;

def VMSBC_VV : VALU_OPIVV_um<0b010011,"vmsbc.vv">;

def : PatVgrVgr<int_riscv_vmsbc_vv_8m1,VMSBC_VV,v16i8>;
def : PatVgrVgr<int_riscv_vmsbc_vv_8m2,VMSBC_VV,v32i8>;
def : PatVgrVgr<int_riscv_vmsbc_vv_8m4,VMSBC_VV,v64i8>;
def : PatVgrVgr<int_riscv_vmsbc_vv_8m8,VMSBC_VV,v128i8>;

def : PatVgrVgr<int_riscv_vmsbc_vv_16m1,VMSBC_VV,v8i16>;
def : PatVgrVgr<int_riscv_vmsbc_vv_16m2,VMSBC_VV,v16i16>;
def : PatVgrVgr<int_riscv_vmsbc_vv_16m4,VMSBC_VV,v32i16>;
def : PatVgrVgr<int_riscv_vmsbc_vv_16m8,VMSBC_VV,v64i16>;

def : PatVgrVgr<int_riscv_vmsbc_vv_32m1,VMSBC_VV,v4i32>;
def : PatVgrVgr<int_riscv_vmsbc_vv_32m2,VMSBC_VV,v8i32>;
def : PatVgrVgr<int_riscv_vmsbc_vv_32m4,VMSBC_VV,v16i32>;
def : PatVgrVgr<int_riscv_vmsbc_vv_32m8,VMSBC_VV,v32i32>;

def VMSBC_VX : VALU_OPIVX_um<0b010011,"vmsbc.vx">;

def : PatVgrGpr<int_riscv_vmsbc_vx_8m1,VMSBC_VX,v16i8>;
def : PatVgrGpr<int_riscv_vmsbc_vx_8m2,VMSBC_VX,v32i8>;
def : PatVgrGpr<int_riscv_vmsbc_vx_8m4,VMSBC_VX,v64i8>;
def : PatVgrGpr<int_riscv_vmsbc_vx_8m8,VMSBC_VX,v128i8>;

def : PatVgrGpr<int_riscv_vmsbc_vx_16m1,VMSBC_VX,v8i16>;
def : PatVgrGpr<int_riscv_vmsbc_vx_16m2,VMSBC_VX,v16i16>;
def : PatVgrGpr<int_riscv_vmsbc_vx_16m4,VMSBC_VX,v32i16>;
def : PatVgrGpr<int_riscv_vmsbc_vx_16m8,VMSBC_VX,v64i16>;

def : PatVgrGpr<int_riscv_vmsbc_vx_32m1,VMSBC_VX,v4i32>;
def : PatVgrGpr<int_riscv_vmsbc_vx_32m2,VMSBC_VX,v8i32>;
def : PatVgrGpr<int_riscv_vmsbc_vx_32m4,VMSBC_VX,v16i32>;
def : PatVgrGpr<int_riscv_vmsbc_vx_32m8,VMSBC_VX,v32i32>;

/*******Vector Bitwise Logical Functions*********/
defm VAND_VV : VALU_OPIVV<0b001001,"vand.vv">;

def : PatVgrVgr<int_riscv_vand_vv_8m1,VAND_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vand_vv_8m2,VAND_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vand_vv_8m4,VAND_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vand_vv_8m8,VAND_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vand_vv_16m1,VAND_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vand_vv_16m2,VAND_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vand_vv_16m4,VAND_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vand_vv_16m8,VAND_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vand_vv_32m1,VAND_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vand_vv_32m2,VAND_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vand_vv_32m4,VAND_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vand_vv_32m8,VAND_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vand_vv_8m1_m,VAND_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vand_vv_8m2_m,VAND_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vand_vv_8m4_m,VAND_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vand_vv_8m8_m,VAND_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vand_vv_16m1_m,VAND_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vand_vv_16m2_m,VAND_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vand_vv_16m4_m,VAND_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vand_vv_16m8_m,VAND_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vand_vv_32m1_m,VAND_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vand_vv_32m2_m,VAND_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vand_vv_32m4_m,VAND_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vand_vv_32m8_m,VAND_VV_m,v32i32>;

defm VAND_VX : VALU_OPIVX<0b001001,"vand.vx">;

def : PatVgrGpr<int_riscv_vand_vx_8m1,VAND_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vand_vx_8m2,VAND_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vand_vx_8m4,VAND_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vand_vx_8m8,VAND_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vand_vx_16m1,VAND_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vand_vx_16m2,VAND_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vand_vx_16m4,VAND_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vand_vx_16m8,VAND_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vand_vx_32m1,VAND_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vand_vx_32m2,VAND_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vand_vx_32m4,VAND_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vand_vx_32m8,VAND_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vand_vx_8m1_m,VAND_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vand_vx_8m2_m,VAND_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vand_vx_8m4_m,VAND_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vand_vx_8m8_m,VAND_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vand_vx_16m1_m,VAND_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vand_vx_16m2_m,VAND_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vand_vx_16m4_m,VAND_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vand_vx_16m8_m,VAND_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vand_vx_32m1_m,VAND_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vand_vx_32m2_m,VAND_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vand_vx_32m4_m,VAND_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vand_vx_32m8_m,VAND_VX_m,v32i32>;

defm VAND_VI : VALU_OPIVI_signed<0b001001,"vand.vi">;

def : PatVgrSimm5<int_riscv_vand_vi_8m1,VAND_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vand_vi_8m2,VAND_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vand_vi_8m4,VAND_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vand_vi_8m8,VAND_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vand_vi_16m1,VAND_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vand_vi_16m2,VAND_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vand_vi_16m4,VAND_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vand_vi_16m8,VAND_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vand_vi_32m1,VAND_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vand_vi_32m2,VAND_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vand_vi_32m4,VAND_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vand_vi_32m8,VAND_VI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vand_vi_8m1_m,VAND_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vand_vi_8m2_m,VAND_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vand_vi_8m4_m,VAND_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vand_vi_8m8_m,VAND_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vand_vi_16m1_m,VAND_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vand_vi_16m2_m,VAND_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vand_vi_16m4_m,VAND_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vand_vi_16m8_m,VAND_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vand_vi_32m1_m,VAND_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vand_vi_32m2_m,VAND_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vand_vi_32m4_m,VAND_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vand_vi_32m8_m,VAND_VI_m,v32i32>;

defm VOR_VV : VALU_OPIVV<0b001010,"vor.vv">;

def : PatVgrVgr<int_riscv_vor_vv_8m1,VOR_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vor_vv_8m2,VOR_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vor_vv_8m4,VOR_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vor_vv_8m8,VOR_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vor_vv_16m1,VOR_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vor_vv_16m2,VOR_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vor_vv_16m4,VOR_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vor_vv_16m8,VOR_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vor_vv_32m1,VOR_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vor_vv_32m2,VOR_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vor_vv_32m4,VOR_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vor_vv_32m8,VOR_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vor_vv_8m1_m,VOR_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vor_vv_8m2_m,VOR_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vor_vv_8m4_m,VOR_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vor_vv_8m8_m,VOR_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vor_vv_16m1_m,VOR_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vor_vv_16m2_m,VOR_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vor_vv_16m4_m,VOR_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vor_vv_16m8_m,VOR_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vor_vv_32m1_m,VOR_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vor_vv_32m2_m,VOR_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vor_vv_32m4_m,VOR_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vor_vv_32m8_m,VOR_VV_m,v32i32>;

defm VOR_VX : VALU_OPIVX<0b001010,"vor.vx">;

def : PatVgrGpr<int_riscv_vor_vx_8m1,VOR_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vor_vx_8m2,VOR_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vor_vx_8m4,VOR_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vor_vx_8m8,VOR_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vor_vx_16m1,VOR_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vor_vx_16m2,VOR_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vor_vx_16m4,VOR_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vor_vx_16m8,VOR_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vor_vx_32m1,VOR_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vor_vx_32m2,VOR_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vor_vx_32m4,VOR_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vor_vx_32m8,VOR_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vor_vx_8m1_m,VOR_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vor_vx_8m2_m,VOR_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vor_vx_8m4_m,VOR_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vor_vx_8m8_m,VOR_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vor_vx_16m1_m,VOR_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vor_vx_16m2_m,VOR_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vor_vx_16m4_m,VOR_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vor_vx_16m8_m,VOR_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vor_vx_32m1_m,VOR_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vor_vx_32m2_m,VOR_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vor_vx_32m4_m,VOR_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vor_vx_32m8_m,VOR_VX_m,v32i32>;

defm VOR_VI : VALU_OPIVI_signed<0b001010,"vor.vi">;

def : PatVgrSimm5<int_riscv_vor_vi_8m1,VOR_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vor_vi_8m2,VOR_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vor_vi_8m4,VOR_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vor_vi_8m8,VOR_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vor_vi_16m1,VOR_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vor_vi_16m2,VOR_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vor_vi_16m4,VOR_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vor_vi_16m8,VOR_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vor_vi_32m1,VOR_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vor_vi_32m2,VOR_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vor_vi_32m4,VOR_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vor_vi_32m8,VOR_VI_um,v32i32>;


def : PatVmVgrSimm5<int_riscv_vor_vi_8m1_m,VOR_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vor_vi_8m2_m,VOR_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vor_vi_8m4_m,VOR_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vor_vi_8m8_m,VOR_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vor_vi_16m1_m,VOR_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vor_vi_16m2_m,VOR_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vor_vi_16m4_m,VOR_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vor_vi_16m8_m,VOR_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vor_vi_32m1_m,VOR_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vor_vi_32m2_m,VOR_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vor_vi_32m4_m,VOR_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vor_vi_32m8_m,VOR_VI_m,v32i32>;

defm VXOR_VV : VALU_OPIVV<0b001011,"vxor.vv">;

def : PatVgrVgr<int_riscv_vxor_vv_8m1,VXOR_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vxor_vv_8m2,VXOR_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vxor_vv_8m4,VXOR_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vxor_vv_8m8,VXOR_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vxor_vv_16m1,VXOR_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vxor_vv_16m2,VXOR_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vxor_vv_16m4,VXOR_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vxor_vv_16m8,VXOR_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vxor_vv_32m1,VXOR_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vxor_vv_32m2,VXOR_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vxor_vv_32m4,VXOR_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vxor_vv_32m8,VXOR_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vxor_vv_8m1_m,VXOR_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vxor_vv_8m2_m,VXOR_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vxor_vv_8m4_m,VXOR_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vxor_vv_8m8_m,VXOR_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vxor_vv_16m1_m,VXOR_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vxor_vv_16m2_m,VXOR_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vxor_vv_16m4_m,VXOR_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vxor_vv_16m8_m,VXOR_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vxor_vv_32m1_m,VXOR_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vxor_vv_32m2_m,VXOR_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vxor_vv_32m4_m,VXOR_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vxor_vv_32m8_m,VXOR_VV_m,v32i32>;

defm VXOR_VX : VALU_OPIVX<0b001011,"vxor.vx">;

def : PatVgrGpr<int_riscv_vxor_vx_8m1,VXOR_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vxor_vx_8m2,VXOR_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vxor_vx_8m4,VXOR_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vxor_vx_8m8,VXOR_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vxor_vx_16m1,VXOR_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vxor_vx_16m2,VXOR_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vxor_vx_16m4,VXOR_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vxor_vx_16m8,VXOR_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vxor_vx_32m1,VXOR_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vxor_vx_32m2,VXOR_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vxor_vx_32m4,VXOR_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vxor_vx_32m8,VXOR_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vxor_vx_8m1_m,VXOR_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vxor_vx_8m2_m,VXOR_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vxor_vx_8m4_m,VXOR_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vxor_vx_8m8_m,VXOR_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vxor_vx_16m1_m,VXOR_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vxor_vx_16m2_m,VXOR_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vxor_vx_16m4_m,VXOR_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vxor_vx_16m8_m,VXOR_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vxor_vx_32m1_m,VXOR_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vxor_vx_32m2_m,VXOR_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vxor_vx_32m4_m,VXOR_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vxor_vx_32m8_m,VXOR_VX_m,v32i32>;

defm VXOR_VI : VALU_OPIVI_signed<0b001011,"vxor.vi">;

def : PatVgrSimm5<int_riscv_vxor_vi_8m1,VXOR_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vxor_vi_8m2,VXOR_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vxor_vi_8m4,VXOR_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vxor_vi_8m8,VXOR_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vxor_vi_16m1,VXOR_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vxor_vi_16m2,VXOR_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vxor_vi_16m4,VXOR_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vxor_vi_16m8,VXOR_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vxor_vi_32m1,VXOR_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vxor_vi_32m2,VXOR_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vxor_vi_32m4,VXOR_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vxor_vi_32m8,VXOR_VI_um,v32i32>;


def : PatVmVgrSimm5<int_riscv_vxor_vi_8m1_m,VXOR_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vxor_vi_8m2_m,VXOR_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vxor_vi_8m4_m,VXOR_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vxor_vi_8m8_m,VXOR_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vxor_vi_16m1_m,VXOR_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vxor_vi_16m2_m,VXOR_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vxor_vi_16m4_m,VXOR_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vxor_vi_16m8_m,VXOR_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vxor_vi_32m1_m,VXOR_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vxor_vi_32m2_m,VXOR_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vxor_vi_32m4_m,VXOR_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vxor_vi_32m8_m,VXOR_VI_m,v32i32>;

/********Vector Single-Width Bit Shift Function**********/

defm VSLL_VV : VALU_OPIVV<0b100101,"vsll.vv">;

def : PatVgrVgr<int_riscv_vsll_vv_8m1,VSLL_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vsll_vv_8m2,VSLL_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vsll_vv_8m4,VSLL_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vsll_vv_8m8,VSLL_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vsll_vv_16m1,VSLL_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vsll_vv_16m2,VSLL_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vsll_vv_16m4,VSLL_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vsll_vv_16m8,VSLL_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vsll_vv_32m1,VSLL_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vsll_vv_32m2,VSLL_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vsll_vv_32m4,VSLL_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vsll_vv_32m8,VSLL_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vsll_vv_8m1_m,VSLL_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vsll_vv_8m2_m,VSLL_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vsll_vv_8m4_m,VSLL_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vsll_vv_8m8_m,VSLL_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vsll_vv_16m1_m,VSLL_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vsll_vv_16m2_m,VSLL_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vsll_vv_16m4_m,VSLL_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vsll_vv_16m8_m,VSLL_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vsll_vv_32m1_m,VSLL_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vsll_vv_32m2_m,VSLL_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vsll_vv_32m4_m,VSLL_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vsll_vv_32m8_m,VSLL_VV_m,v32i32>;

defm VSLL_VX : VALU_OPIVX<0b100101,"vsll.vx">;

def : PatVgrGpr<int_riscv_vsll_vx_8m1,VSLL_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vsll_vx_8m2,VSLL_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vsll_vx_8m4,VSLL_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vsll_vx_8m8,VSLL_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vsll_vx_16m1,VSLL_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vsll_vx_16m2,VSLL_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vsll_vx_16m4,VSLL_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vsll_vx_16m8,VSLL_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vsll_vx_32m1,VSLL_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vsll_vx_32m2,VSLL_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vsll_vx_32m4,VSLL_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vsll_vx_32m8,VSLL_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vsll_vx_8m1_m,VSLL_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vsll_vx_8m2_m,VSLL_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vsll_vx_8m4_m,VSLL_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vsll_vx_8m8_m,VSLL_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vsll_vx_16m1_m,VSLL_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vsll_vx_16m2_m,VSLL_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vsll_vx_16m4_m,VSLL_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vsll_vx_16m8_m,VSLL_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vsll_vx_32m1_m,VSLL_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vsll_vx_32m2_m,VSLL_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vsll_vx_32m4_m,VSLL_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vsll_vx_32m8_m,VSLL_VX_m,v32i32>;

defm VSLL_VI : VALU_OPIVI_unsigned<0b100101,"vsll.vi">;

def : PatVgrUimm5<int_riscv_vsll_vi_8m1,VSLL_VI_um,v16i8>;
def : PatVgrUimm5<int_riscv_vsll_vi_8m2,VSLL_VI_um,v32i8>;
def : PatVgrUimm5<int_riscv_vsll_vi_8m4,VSLL_VI_um,v64i8>;
def : PatVgrUimm5<int_riscv_vsll_vi_8m8,VSLL_VI_um,v128i8>;

def : PatVgrUimm5<int_riscv_vsll_vi_16m1,VSLL_VI_um,v8i16>;
def : PatVgrUimm5<int_riscv_vsll_vi_16m2,VSLL_VI_um,v16i16>;
def : PatVgrUimm5<int_riscv_vsll_vi_16m4,VSLL_VI_um,v32i16>;
def : PatVgrUimm5<int_riscv_vsll_vi_16m8,VSLL_VI_um,v64i16>;

def : PatVgrUimm5<int_riscv_vsll_vi_32m1,VSLL_VI_um,v4i32>;
def : PatVgrUimm5<int_riscv_vsll_vi_32m2,VSLL_VI_um,v8i32>;
def : PatVgrUimm5<int_riscv_vsll_vi_32m4,VSLL_VI_um,v16i32>;
def : PatVgrUimm5<int_riscv_vsll_vi_32m8,VSLL_VI_um,v32i32>;

def : PatVmVgrUimm5<int_riscv_vsll_vi_8m1_m,VSLL_VI_m,v16i8>;
def : PatVmVgrUimm5<int_riscv_vsll_vi_8m2_m,VSLL_VI_m,v32i8>;
def : PatVmVgrUimm5<int_riscv_vsll_vi_8m4_m,VSLL_VI_m,v64i8>;
def : PatVmVgrUimm5<int_riscv_vsll_vi_8m8_m,VSLL_VI_m,v128i8>;

def : PatVmVgrUimm5<int_riscv_vsll_vi_16m1_m,VSLL_VI_m,v8i16>;
def : PatVmVgrUimm5<int_riscv_vsll_vi_16m2_m,VSLL_VI_m,v16i16>;
def : PatVmVgrUimm5<int_riscv_vsll_vi_16m4_m,VSLL_VI_m,v32i16>;
def : PatVmVgrUimm5<int_riscv_vsll_vi_16m8_m,VSLL_VI_m,v64i16>;

def : PatVmVgrUimm5<int_riscv_vsll_vi_32m1_m,VSLL_VI_m,v4i32>;
def : PatVmVgrUimm5<int_riscv_vsll_vi_32m2_m,VSLL_VI_m,v8i32>;
def : PatVmVgrUimm5<int_riscv_vsll_vi_32m4_m,VSLL_VI_m,v16i32>;
def : PatVmVgrUimm5<int_riscv_vsll_vi_32m8_m,VSLL_VI_m,v32i32>;

defm VSRL_VV : VALU_OPIVV<0b101000,"vsrl.vv">;

def : PatVgrVgr<int_riscv_vsrl_vv_8m1,VSRL_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vsrl_vv_8m2,VSRL_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vsrl_vv_8m4,VSRL_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vsrl_vv_8m8,VSRL_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vsrl_vv_16m1,VSRL_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vsrl_vv_16m2,VSRL_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vsrl_vv_16m4,VSRL_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vsrl_vv_16m8,VSRL_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vsrl_vv_32m1,VSRL_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vsrl_vv_32m2,VSRL_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vsrl_vv_32m4,VSRL_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vsrl_vv_32m8,VSRL_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vsrl_vv_8m1_m,VSRL_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vsrl_vv_8m2_m,VSRL_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vsrl_vv_8m4_m,VSRL_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vsrl_vv_8m8_m,VSRL_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vsrl_vv_16m1_m,VSRL_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vsrl_vv_16m2_m,VSRL_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vsrl_vv_16m4_m,VSRL_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vsrl_vv_16m8_m,VSRL_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vsrl_vv_32m1_m,VSRL_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vsrl_vv_32m2_m,VSRL_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vsrl_vv_32m4_m,VSRL_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vsrl_vv_32m8_m,VSRL_VV_m,v32i32>;

defm VSRL_VX : VALU_OPIVX<0b101000,"vsrl.vx">;

def : PatVgrGpr<int_riscv_vsrl_vx_8m1,VSRL_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vsrl_vx_8m2,VSRL_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vsrl_vx_8m4,VSRL_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vsrl_vx_8m8,VSRL_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vsrl_vx_16m1,VSRL_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vsrl_vx_16m2,VSRL_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vsrl_vx_16m4,VSRL_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vsrl_vx_16m8,VSRL_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vsrl_vx_32m1,VSRL_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vsrl_vx_32m2,VSRL_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vsrl_vx_32m4,VSRL_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vsrl_vx_32m8,VSRL_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vsrl_vx_8m1_m,VSRL_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vsrl_vx_8m2_m,VSRL_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vsrl_vx_8m4_m,VSRL_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vsrl_vx_8m8_m,VSRL_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vsrl_vx_16m1_m,VSRL_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vsrl_vx_16m2_m,VSRL_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vsrl_vx_16m4_m,VSRL_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vsrl_vx_16m8_m,VSRL_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vsrl_vx_32m1_m,VSRL_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vsrl_vx_32m2_m,VSRL_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vsrl_vx_32m4_m,VSRL_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vsrl_vx_32m8_m,VSRL_VX_m,v32i32>;

defm VSRL_VI : VALU_OPIVI_unsigned<0b101000,"vsrl.vi">;

def : PatVgrUimm5<int_riscv_vsrl_vi_8m1,VSRL_VI_um,v16i8>;
def : PatVgrUimm5<int_riscv_vsrl_vi_8m2,VSRL_VI_um,v32i8>;
def : PatVgrUimm5<int_riscv_vsrl_vi_8m4,VSRL_VI_um,v64i8>;
def : PatVgrUimm5<int_riscv_vsrl_vi_8m8,VSRL_VI_um,v128i8>;

def : PatVgrUimm5<int_riscv_vsrl_vi_16m1,VSRL_VI_um,v8i16>;
def : PatVgrUimm5<int_riscv_vsrl_vi_16m2,VSRL_VI_um,v16i16>;
def : PatVgrUimm5<int_riscv_vsrl_vi_16m4,VSRL_VI_um,v32i16>;
def : PatVgrUimm5<int_riscv_vsrl_vi_16m8,VSRL_VI_um,v64i16>;

def : PatVgrUimm5<int_riscv_vsrl_vi_32m1,VSRL_VI_um,v4i32>;
def : PatVgrUimm5<int_riscv_vsrl_vi_32m2,VSRL_VI_um,v8i32>;
def : PatVgrUimm5<int_riscv_vsrl_vi_32m4,VSRL_VI_um,v16i32>;
def : PatVgrUimm5<int_riscv_vsrl_vi_32m8,VSRL_VI_um,v32i32>;

def : PatVmVgrUimm5<int_riscv_vsrl_vi_8m1_m,VSRL_VI_m,v16i8>;
def : PatVmVgrUimm5<int_riscv_vsrl_vi_8m2_m,VSRL_VI_m,v32i8>;
def : PatVmVgrUimm5<int_riscv_vsrl_vi_8m4_m,VSRL_VI_m,v64i8>;
def : PatVmVgrUimm5<int_riscv_vsrl_vi_8m8_m,VSRL_VI_m,v128i8>;

def : PatVmVgrUimm5<int_riscv_vsrl_vi_16m1_m,VSRL_VI_m,v8i16>;
def : PatVmVgrUimm5<int_riscv_vsrl_vi_16m2_m,VSRL_VI_m,v16i16>;
def : PatVmVgrUimm5<int_riscv_vsrl_vi_16m4_m,VSRL_VI_m,v32i16>;
def : PatVmVgrUimm5<int_riscv_vsrl_vi_16m8_m,VSRL_VI_m,v64i16>;

def : PatVmVgrUimm5<int_riscv_vsrl_vi_32m1_m,VSRL_VI_m,v4i32>;
def : PatVmVgrUimm5<int_riscv_vsrl_vi_32m2_m,VSRL_VI_m,v8i32>;
def : PatVmVgrUimm5<int_riscv_vsrl_vi_32m4_m,VSRL_VI_m,v16i32>;
def : PatVmVgrUimm5<int_riscv_vsrl_vi_32m8_m,VSRL_VI_m,v32i32>;

defm VSRA_VV : VALU_OPIVV<0b101001,"vsra.vv">;

def : PatVgrVgr<int_riscv_vsra_vv_8m1,VSRA_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vsra_vv_8m2,VSRA_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vsra_vv_8m4,VSRA_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vsra_vv_8m8,VSRA_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vsra_vv_16m1,VSRA_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vsra_vv_16m2,VSRA_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vsra_vv_16m4,VSRA_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vsra_vv_16m8,VSRA_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vsra_vv_32m1,VSRA_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vsra_vv_32m2,VSRA_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vsra_vv_32m4,VSRA_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vsra_vv_32m8,VSRA_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vsra_vv_8m1_m,VSRA_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vsra_vv_8m2_m,VSRA_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vsra_vv_8m4_m,VSRA_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vsra_vv_8m8_m,VSRA_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vsra_vv_16m1_m,VSRA_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vsra_vv_16m2_m,VSRA_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vsra_vv_16m4_m,VSRA_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vsra_vv_16m8_m,VSRA_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vsra_vv_32m1_m,VSRA_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vsra_vv_32m2_m,VSRA_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vsra_vv_32m4_m,VSRA_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vsra_vv_32m8_m,VSRA_VV_m,v32i32>;

defm VSRA_VX : VALU_OPIVX<0b101001,"vsra.vx">;

def : PatVgrGpr<int_riscv_vsra_vx_8m1,VSRA_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vsra_vx_8m2,VSRA_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vsra_vx_8m4,VSRA_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vsra_vx_8m8,VSRA_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vsra_vx_16m1,VSRA_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vsra_vx_16m2,VSRA_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vsra_vx_16m4,VSRA_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vsra_vx_16m8,VSRA_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vsra_vx_32m1,VSRA_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vsra_vx_32m2,VSRA_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vsra_vx_32m4,VSRA_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vsra_vx_32m8,VSRA_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vsra_vx_8m1_m,VSRA_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vsra_vx_8m2_m,VSRA_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vsra_vx_8m4_m,VSRA_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vsra_vx_8m8_m,VSRA_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vsra_vx_16m1_m,VSRA_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vsra_vx_16m2_m,VSRA_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vsra_vx_16m4_m,VSRA_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vsra_vx_16m8_m,VSRA_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vsra_vx_32m1_m,VSRA_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vsra_vx_32m2_m,VSRA_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vsra_vx_32m4_m,VSRA_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vsra_vx_32m8_m,VSRA_VX_m,v32i32>;

defm VSRA_VI : VALU_OPIVI_unsigned<0b101001,"vsra.vi">;

def : PatVgrUimm5<int_riscv_vsra_vi_8m1,VSRA_VI_um,v16i8>;
def : PatVgrUimm5<int_riscv_vsra_vi_8m2,VSRA_VI_um,v32i8>;
def : PatVgrUimm5<int_riscv_vsra_vi_8m4,VSRA_VI_um,v64i8>;
def : PatVgrUimm5<int_riscv_vsra_vi_8m8,VSRA_VI_um,v128i8>;

def : PatVgrUimm5<int_riscv_vsra_vi_16m1,VSRA_VI_um,v8i16>;
def : PatVgrUimm5<int_riscv_vsra_vi_16m2,VSRA_VI_um,v16i16>;
def : PatVgrUimm5<int_riscv_vsra_vi_16m4,VSRA_VI_um,v32i16>;
def : PatVgrUimm5<int_riscv_vsra_vi_16m8,VSRA_VI_um,v64i16>;

def : PatVgrUimm5<int_riscv_vsra_vi_32m1,VSRA_VI_um,v4i32>;
def : PatVgrUimm5<int_riscv_vsra_vi_32m2,VSRA_VI_um,v8i32>;
def : PatVgrUimm5<int_riscv_vsra_vi_32m4,VSRA_VI_um,v16i32>;
def : PatVgrUimm5<int_riscv_vsra_vi_32m8,VSRA_VI_um,v32i32>;

def : PatVmVgrUimm5<int_riscv_vsra_vi_8m1_m,VSRA_VI_m,v16i8>;
def : PatVmVgrUimm5<int_riscv_vsra_vi_8m2_m,VSRA_VI_m,v32i8>;
def : PatVmVgrUimm5<int_riscv_vsra_vi_8m4_m,VSRA_VI_m,v64i8>;
def : PatVmVgrUimm5<int_riscv_vsra_vi_8m8_m,VSRA_VI_m,v128i8>;

def : PatVmVgrUimm5<int_riscv_vsra_vi_16m1_m,VSRA_VI_m,v8i16>;
def : PatVmVgrUimm5<int_riscv_vsra_vi_16m2_m,VSRA_VI_m,v16i16>;
def : PatVmVgrUimm5<int_riscv_vsra_vi_16m4_m,VSRA_VI_m,v32i16>;
def : PatVmVgrUimm5<int_riscv_vsra_vi_16m8_m,VSRA_VI_m,v64i16>;

def : PatVmVgrUimm5<int_riscv_vsra_vi_32m1_m,VSRA_VI_m,v4i32>;
def : PatVmVgrUimm5<int_riscv_vsra_vi_32m2_m,VSRA_VI_m,v8i32>;
def : PatVmVgrUimm5<int_riscv_vsra_vi_32m4_m,VSRA_VI_m,v16i32>;
def : PatVmVgrUimm5<int_riscv_vsra_vi_32m8_m,VSRA_VI_m,v32i32>;

/*********Vector Narrowing Integer Right Shift Functions************/

defm VNSRL_WV : VALU_OPIVV<0b101100,"vnsrl.wv">;

def : PatWidVgrVgr<int_riscv_vnsrl_wv_8m1,VNSRL_WV_um,v16i16,v16i8>;
def : PatWidVgrVgr<int_riscv_vnsrl_wv_8m2,VNSRL_WV_um,v32i16,v32i8>;
def : PatWidVgrVgr<int_riscv_vnsrl_wv_8m4,VNSRL_WV_um,v64i16,v64i8>;

def : PatWidVgrVgr<int_riscv_vnsrl_wv_16m1,VNSRL_WV_um,v8i32,v8i16>;
def : PatWidVgrVgr<int_riscv_vnsrl_wv_16m2,VNSRL_WV_um,v16i32,v16i16>;
def : PatWidVgrVgr<int_riscv_vnsrl_wv_16m4,VNSRL_WV_um,v32i32,v32i16>;

def : PatVmWidVgrVgr<int_riscv_vnsrl_wv_8m1_m,VNSRL_WV_m,v16i16,v16i8>;
def : PatVmWidVgrVgr<int_riscv_vnsrl_wv_8m2_m,VNSRL_WV_m,v32i16,v32i8>;
def : PatVmWidVgrVgr<int_riscv_vnsrl_wv_8m4_m,VNSRL_WV_m,v64i16,v64i8>;

def : PatVmWidVgrVgr<int_riscv_vnsrl_wv_16m1_m,VNSRL_WV_m,v8i32,v8i16>;
def : PatVmWidVgrVgr<int_riscv_vnsrl_wv_16m2_m,VNSRL_WV_m,v16i32,v16i16>;
def : PatVmWidVgrVgr<int_riscv_vnsrl_wv_16m4_m,VNSRL_WV_m,v32i32,v32i16>;

defm VNSRL_WX : VALU_OPIVX<0b101100,"vnsrl.wx">;

def : PatVgrGpr<int_riscv_vnsrl_wx_8m1,VNSRL_WX_um,v16i16>;
def : PatVgrGpr<int_riscv_vnsrl_wx_8m2,VNSRL_WX_um,v32i16>;
def : PatVgrGpr<int_riscv_vnsrl_wx_8m4,VNSRL_WX_um,v64i16>;

def : PatVgrGpr<int_riscv_vnsrl_wx_16m1,VNSRL_WX_um,v8i32>;
def : PatVgrGpr<int_riscv_vnsrl_wx_16m2,VNSRL_WX_um,v16i32>;
def : PatVgrGpr<int_riscv_vnsrl_wx_16m4,VNSRL_WX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vnsrl_wx_8m1_m,VNSRL_WX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vnsrl_wx_8m2_m,VNSRL_WX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vnsrl_wx_8m4_m,VNSRL_WX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vnsrl_wx_16m1_m,VNSRL_WX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vnsrl_wx_16m2_m,VNSRL_WX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vnsrl_wx_16m4_m,VNSRL_WX_m,v32i32>;

defm VNSRL_WI : VALU_OPIVI_unsigned<0b101100,"vnsrl.wi">;

def : PatVgrUimm5<int_riscv_vnsrl_wi_8m1,VNSRL_WI_um,v16i16>;
def : PatVgrUimm5<int_riscv_vnsrl_wi_8m2,VNSRL_WI_um,v32i16>;
def : PatVgrUimm5<int_riscv_vnsrl_wi_8m4,VNSRL_WI_um,v64i16>;

def : PatVgrUimm5<int_riscv_vnsrl_wi_16m1,VNSRL_WI_um,v8i32>;
def : PatVgrUimm5<int_riscv_vnsrl_wi_16m2,VNSRL_WI_um,v16i32>;
def : PatVgrUimm5<int_riscv_vnsrl_wi_16m4,VNSRL_WI_um,v32i32>;

def : PatVmVgrUimm5<int_riscv_vnsrl_wi_8m1_m,VNSRL_WI_m,v16i16>;
def : PatVmVgrUimm5<int_riscv_vnsrl_wi_8m2_m,VNSRL_WI_m,v32i16>;
def : PatVmVgrUimm5<int_riscv_vnsrl_wi_8m4_m,VNSRL_WI_m,v64i16>;

def : PatVmVgrUimm5<int_riscv_vnsrl_wi_16m1_m,VNSRL_WI_m,v8i32>;
def : PatVmVgrUimm5<int_riscv_vnsrl_wi_16m2_m,VNSRL_WI_m,v16i32>;
def : PatVmVgrUimm5<int_riscv_vnsrl_wi_16m4_m,VNSRL_WI_m,v32i32>;

defm VNSRA_WV : VALU_OPIVV<0b101101,"vnsra.wv">;

def : PatWidVgrVgr<int_riscv_vnsra_wv_8m1,VNSRA_WV_um,v16i16,v16i8>;
def : PatWidVgrVgr<int_riscv_vnsra_wv_8m2,VNSRA_WV_um,v32i16,v32i8>;
def : PatWidVgrVgr<int_riscv_vnsra_wv_8m4,VNSRA_WV_um,v64i16,v64i8>;

def : PatWidVgrVgr<int_riscv_vnsra_wv_16m1,VNSRA_WV_um,v8i32,v8i16>;
def : PatWidVgrVgr<int_riscv_vnsra_wv_16m2,VNSRA_WV_um,v16i32,v16i16>;
def : PatWidVgrVgr<int_riscv_vnsra_wv_16m4,VNSRA_WV_um,v32i32,v32i16>;

def : PatVmWidVgrVgr<int_riscv_vnsra_wv_8m1_m,VNSRA_WV_m,v16i16,v16i8>;
def : PatVmWidVgrVgr<int_riscv_vnsra_wv_8m2_m,VNSRA_WV_m,v32i16,v32i8>;
def : PatVmWidVgrVgr<int_riscv_vnsra_wv_8m4_m,VNSRA_WV_m,v64i16,v64i8>;

def : PatVmWidVgrVgr<int_riscv_vnsra_wv_16m1_m,VNSRA_WV_m,v8i32,v8i16>;
def : PatVmWidVgrVgr<int_riscv_vnsra_wv_16m2_m,VNSRA_WV_m,v16i32,v16i16>;
def : PatVmWidVgrVgr<int_riscv_vnsra_wv_16m4_m,VNSRA_WV_m,v32i32,v32i16>;

defm VNSRA_WX : VALU_OPIVX<0b101101,"vnsra.wx">;

def : PatVgrGpr<int_riscv_vnsra_wx_8m1,VNSRA_WX_um,v16i16>;
def : PatVgrGpr<int_riscv_vnsra_wx_8m2,VNSRA_WX_um,v32i16>;
def : PatVgrGpr<int_riscv_vnsra_wx_8m4,VNSRA_WX_um,v64i16>;

def : PatVgrGpr<int_riscv_vnsra_wx_16m1,VNSRA_WX_um,v8i32>;
def : PatVgrGpr<int_riscv_vnsra_wx_16m2,VNSRA_WX_um,v16i32>;
def : PatVgrGpr<int_riscv_vnsra_wx_16m4,VNSRA_WX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vnsra_wx_8m1_m,VNSRA_WX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vnsra_wx_8m2_m,VNSRA_WX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vnsra_wx_8m4_m,VNSRA_WX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vnsra_wx_16m1_m,VNSRA_WX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vnsra_wx_16m2_m,VNSRA_WX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vnsra_wx_16m4_m,VNSRA_WX_m,v32i32>;

defm VNSRA_WI : VALU_OPIVI_unsigned<0b101101,"vnsra.wi">;

def : PatVgrUimm5<int_riscv_vnsra_wi_8m1,VNSRA_WI_um,v16i16>;
def : PatVgrUimm5<int_riscv_vnsra_wi_8m2,VNSRA_WI_um,v32i16>;
def : PatVgrUimm5<int_riscv_vnsra_wi_8m4,VNSRA_WI_um,v64i16>;

def : PatVgrUimm5<int_riscv_vnsra_wi_16m1,VNSRA_WI_um,v8i32>;
def : PatVgrUimm5<int_riscv_vnsra_wi_16m2,VNSRA_WI_um,v16i32>;
def : PatVgrUimm5<int_riscv_vnsra_wi_16m4,VNSRA_WI_um,v32i32>;

def : PatVmVgrUimm5<int_riscv_vnsra_wi_8m1_m,VNSRA_WI_m,v16i16>;
def : PatVmVgrUimm5<int_riscv_vnsra_wi_8m2_m,VNSRA_WI_m,v32i16>;
def : PatVmVgrUimm5<int_riscv_vnsra_wi_8m4_m,VNSRA_WI_m,v64i16>;

def : PatVmVgrUimm5<int_riscv_vnsra_wi_16m1_m,VNSRA_WI_m,v8i32>;
def : PatVmVgrUimm5<int_riscv_vnsra_wi_16m2_m,VNSRA_WI_m,v16i32>;
def : PatVmVgrUimm5<int_riscv_vnsra_wi_16m4_m,VNSRA_WI_m,v32i32>;

/************Vector Integer Comparison Functions***************/

defm VMSEQ_VV : VALU_OPIVV<0b011000,"vmseq.vv">;

def : PatVgrVgr<int_riscv_vmseq_vv_8m1,VMSEQ_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmseq_vv_8m2,VMSEQ_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmseq_vv_8m4,VMSEQ_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmseq_vv_8m8,VMSEQ_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmseq_vv_16m1,VMSEQ_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmseq_vv_16m2,VMSEQ_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmseq_vv_16m4,VMSEQ_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmseq_vv_16m8,VMSEQ_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmseq_vv_32m1,VMSEQ_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmseq_vv_32m2,VMSEQ_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmseq_vv_32m4,VMSEQ_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmseq_vv_32m8,VMSEQ_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmseq_vv_8m1_m,VMSEQ_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmseq_vv_8m2_m,VMSEQ_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmseq_vv_8m4_m,VMSEQ_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmseq_vv_8m8_m,VMSEQ_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmseq_vv_16m1_m,VMSEQ_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmseq_vv_16m2_m,VMSEQ_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmseq_vv_16m4_m,VMSEQ_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmseq_vv_16m8_m,VMSEQ_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmseq_vv_32m1_m,VMSEQ_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmseq_vv_32m2_m,VMSEQ_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmseq_vv_32m4_m,VMSEQ_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmseq_vv_32m8_m,VMSEQ_VV_m,v32i32>;

defm VMSEQ_VX : VALU_OPIVX<0b011000,"vmseq.vx">;

def : PatVgrGpr<int_riscv_vmseq_vx_8m1,VMSEQ_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmseq_vx_8m2,VMSEQ_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmseq_vx_8m4,VMSEQ_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmseq_vx_8m8,VMSEQ_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmseq_vx_16m1,VMSEQ_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmseq_vx_16m2,VMSEQ_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmseq_vx_16m4,VMSEQ_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmseq_vx_16m8,VMSEQ_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmseq_vx_32m1,VMSEQ_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmseq_vx_32m2,VMSEQ_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmseq_vx_32m4,VMSEQ_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmseq_vx_32m8,VMSEQ_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vmseq_vx_8m1_m,VMSEQ_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmseq_vx_8m2_m,VMSEQ_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmseq_vx_8m4_m,VMSEQ_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmseq_vx_8m8_m,VMSEQ_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmseq_vx_16m1_m,VMSEQ_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmseq_vx_16m2_m,VMSEQ_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmseq_vx_16m4_m,VMSEQ_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmseq_vx_16m8_m,VMSEQ_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmseq_vx_32m1_m,VMSEQ_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmseq_vx_32m2_m,VMSEQ_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmseq_vx_32m4_m,VMSEQ_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmseq_vx_32m8_m,VMSEQ_VX_m,v32i32>;

defm VMSEQ_VI : VALU_OPIVI_signed<0b011000,"vmseq.vi">;

def : PatVgrSimm5<int_riscv_vmseq_vi_8m1,VMSEQ_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vmseq_vi_8m2,VMSEQ_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vmseq_vi_8m4,VMSEQ_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vmseq_vi_8m8,VMSEQ_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vmseq_vi_16m1,VMSEQ_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vmseq_vi_16m2,VMSEQ_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vmseq_vi_16m4,VMSEQ_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vmseq_vi_16m8,VMSEQ_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vmseq_vi_32m1,VMSEQ_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vmseq_vi_32m2,VMSEQ_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vmseq_vi_32m4,VMSEQ_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vmseq_vi_32m8,VMSEQ_VI_um,v32i32>;


def : PatVmVgrSimm5<int_riscv_vmseq_vi_8m1_m,VMSEQ_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vmseq_vi_8m2_m,VMSEQ_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vmseq_vi_8m4_m,VMSEQ_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vmseq_vi_8m8_m,VMSEQ_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vmseq_vi_16m1_m,VMSEQ_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vmseq_vi_16m2_m,VMSEQ_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vmseq_vi_16m4_m,VMSEQ_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vmseq_vi_16m8_m,VMSEQ_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vmseq_vi_32m1_m,VMSEQ_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vmseq_vi_32m2_m,VMSEQ_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vmseq_vi_32m4_m,VMSEQ_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vmseq_vi_32m8_m,VMSEQ_VI_m,v32i32>;

defm VMSNE_VV : VALU_OPIVV<0b011001,"vmsne.vv">;

def : PatVgrVgr<int_riscv_vmsne_vv_8m1,VMSNE_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmsne_vv_8m2,VMSNE_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmsne_vv_8m4,VMSNE_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmsne_vv_8m8,VMSNE_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmsne_vv_16m1,VMSNE_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmsne_vv_16m2,VMSNE_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmsne_vv_16m4,VMSNE_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmsne_vv_16m8,VMSNE_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmsne_vv_32m1,VMSNE_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmsne_vv_32m2,VMSNE_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmsne_vv_32m4,VMSNE_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmsne_vv_32m8,VMSNE_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmsne_vv_8m1_m,VMSNE_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmsne_vv_8m2_m,VMSNE_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmsne_vv_8m4_m,VMSNE_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmsne_vv_8m8_m,VMSNE_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmsne_vv_16m1_m,VMSNE_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmsne_vv_16m2_m,VMSNE_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmsne_vv_16m4_m,VMSNE_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmsne_vv_16m8_m,VMSNE_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmsne_vv_32m1_m,VMSNE_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmsne_vv_32m2_m,VMSNE_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmsne_vv_32m4_m,VMSNE_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmsne_vv_32m8_m,VMSNE_VV_m,v32i32>;

defm VMSNE_VX : VALU_OPIVX<0b011001,"vmsne.vx">;

def : PatVgrGpr<int_riscv_vmsne_vx_8m1,VMSNE_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmsne_vx_8m2,VMSNE_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmsne_vx_8m4,VMSNE_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmsne_vx_8m8,VMSNE_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmsne_vx_16m1,VMSNE_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmsne_vx_16m2,VMSNE_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmsne_vx_16m4,VMSNE_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmsne_vx_16m8,VMSNE_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmsne_vx_32m1,VMSNE_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmsne_vx_32m2,VMSNE_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmsne_vx_32m4,VMSNE_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmsne_vx_32m8,VMSNE_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vmsne_vx_8m1_m,VMSNE_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmsne_vx_8m2_m,VMSNE_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmsne_vx_8m4_m,VMSNE_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmsne_vx_8m8_m,VMSNE_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmsne_vx_16m1_m,VMSNE_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmsne_vx_16m2_m,VMSNE_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmsne_vx_16m4_m,VMSNE_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmsne_vx_16m8_m,VMSNE_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmsne_vx_32m1_m,VMSNE_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmsne_vx_32m2_m,VMSNE_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmsne_vx_32m4_m,VMSNE_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmsne_vx_32m8_m,VMSNE_VX_m,v32i32>;

defm VMSNE_VI : VALU_OPIVI_signed<0b011001,"vmsne.vi">;

def : PatVgrSimm5<int_riscv_vmsne_vi_8m1,VMSNE_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vmsne_vi_8m2,VMSNE_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vmsne_vi_8m4,VMSNE_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vmsne_vi_8m8,VMSNE_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vmsne_vi_16m1,VMSNE_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vmsne_vi_16m2,VMSNE_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vmsne_vi_16m4,VMSNE_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vmsne_vi_16m8,VMSNE_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vmsne_vi_32m1,VMSNE_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vmsne_vi_32m2,VMSNE_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vmsne_vi_32m4,VMSNE_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vmsne_vi_32m8,VMSNE_VI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vmsne_vi_8m1_m,VMSNE_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vmsne_vi_8m2_m,VMSNE_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vmsne_vi_8m4_m,VMSNE_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vmsne_vi_8m8_m,VMSNE_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vmsne_vi_16m1_m,VMSNE_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vmsne_vi_16m2_m,VMSNE_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vmsne_vi_16m4_m,VMSNE_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vmsne_vi_16m8_m,VMSNE_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vmsne_vi_32m1_m,VMSNE_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vmsne_vi_32m2_m,VMSNE_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vmsne_vi_32m4_m,VMSNE_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vmsne_vi_32m8_m,VMSNE_VI_m,v32i32>;

defm VMSLTU_VV : VALU_OPIVV<0b011010,"vmsltu.vv">;

def : PatVgrVgr<int_riscv_vmsltu_vv_8m1,VMSLTU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmsltu_vv_8m2,VMSLTU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmsltu_vv_8m4,VMSLTU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmsltu_vv_8m8,VMSLTU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmsltu_vv_16m1,VMSLTU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmsltu_vv_16m2,VMSLTU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmsltu_vv_16m4,VMSLTU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmsltu_vv_16m8,VMSLTU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmsltu_vv_32m1,VMSLTU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmsltu_vv_32m2,VMSLTU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmsltu_vv_32m4,VMSLTU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmsltu_vv_32m8,VMSLTU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmsltu_vv_8m1_m,VMSLTU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmsltu_vv_8m2_m,VMSLTU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmsltu_vv_8m4_m,VMSLTU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmsltu_vv_8m8_m,VMSLTU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmsltu_vv_16m1_m,VMSLTU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmsltu_vv_16m2_m,VMSLTU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmsltu_vv_16m4_m,VMSLTU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmsltu_vv_16m8_m,VMSLTU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmsltu_vv_32m1_m,VMSLTU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmsltu_vv_32m2_m,VMSLTU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmsltu_vv_32m4_m,VMSLTU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmsltu_vv_32m8_m,VMSLTU_VV_m,v32i32>;

defm VMSLTU_VX : VALU_OPIVX<0b011010,"vmsltu.vx">;

def : PatVgrGpr<int_riscv_vmsltu_vx_8m1,VMSLTU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmsltu_vx_8m2,VMSLTU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmsltu_vx_8m4,VMSLTU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmsltu_vx_8m8,VMSLTU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmsltu_vx_16m1,VMSLTU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmsltu_vx_16m2,VMSLTU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmsltu_vx_16m4,VMSLTU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmsltu_vx_16m8,VMSLTU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmsltu_vx_32m1,VMSLTU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmsltu_vx_32m2,VMSLTU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmsltu_vx_32m4,VMSLTU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmsltu_vx_32m8,VMSLTU_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vmsltu_vx_8m1_m,VMSLTU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmsltu_vx_8m2_m,VMSLTU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmsltu_vx_8m4_m,VMSLTU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmsltu_vx_8m8_m,VMSLTU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmsltu_vx_16m1_m,VMSLTU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmsltu_vx_16m2_m,VMSLTU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmsltu_vx_16m4_m,VMSLTU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmsltu_vx_16m8_m,VMSLTU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmsltu_vx_32m1_m,VMSLTU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmsltu_vx_32m2_m,VMSLTU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmsltu_vx_32m4_m,VMSLTU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmsltu_vx_32m8_m,VMSLTU_VX_m,v32i32>;

defm VMSLT_VV : VALU_OPIVV<0b011011,"vmslt.vv">;

def : PatVgrVgr<int_riscv_vmslt_vv_8m1,VMSLT_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmslt_vv_8m2,VMSLT_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmslt_vv_8m4,VMSLT_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmslt_vv_8m8,VMSLT_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmslt_vv_16m1,VMSLT_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmslt_vv_16m2,VMSLT_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmslt_vv_16m4,VMSLT_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmslt_vv_16m8,VMSLT_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmslt_vv_32m1,VMSLT_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmslt_vv_32m2,VMSLT_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmslt_vv_32m4,VMSLT_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmslt_vv_32m8,VMSLT_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmslt_vv_8m1_m,VMSLT_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmslt_vv_8m2_m,VMSLT_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmslt_vv_8m4_m,VMSLT_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmslt_vv_8m8_m,VMSLT_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmslt_vv_16m1_m,VMSLT_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmslt_vv_16m2_m,VMSLT_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmslt_vv_16m4_m,VMSLT_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmslt_vv_16m8_m,VMSLT_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmslt_vv_32m1_m,VMSLT_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmslt_vv_32m2_m,VMSLT_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmslt_vv_32m4_m,VMSLT_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmslt_vv_32m8_m,VMSLT_VV_m,v32i32>;

defm VMSLT_VX : VALU_OPIVX<0b011011,"vmslt.vx">;

def : PatVgrGpr<int_riscv_vmslt_vx_8m1,VMSLT_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmslt_vx_8m2,VMSLT_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmslt_vx_8m4,VMSLT_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmslt_vx_8m8,VMSLT_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmslt_vx_16m1,VMSLT_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmslt_vx_16m2,VMSLT_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmslt_vx_16m4,VMSLT_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmslt_vx_16m8,VMSLT_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmslt_vx_32m1,VMSLT_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmslt_vx_32m2,VMSLT_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmslt_vx_32m4,VMSLT_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmslt_vx_32m8,VMSLT_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vmslt_vx_8m1_m,VMSLT_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmslt_vx_8m2_m,VMSLT_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmslt_vx_8m4_m,VMSLT_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmslt_vx_8m8_m,VMSLT_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmslt_vx_16m1_m,VMSLT_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmslt_vx_16m2_m,VMSLT_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmslt_vx_16m4_m,VMSLT_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmslt_vx_16m8_m,VMSLT_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmslt_vx_32m1_m,VMSLT_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmslt_vx_32m2_m,VMSLT_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmslt_vx_32m4_m,VMSLT_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmslt_vx_32m8_m,VMSLT_VX_m,v32i32>;

defm VMSLEU_VV : VALU_OPIVV<0b011100,"vmsleu.vv">;

def : PatVgrVgr<int_riscv_vmsleu_vv_8m1,VMSLEU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmsleu_vv_8m2,VMSLEU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmsleu_vv_8m4,VMSLEU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmsleu_vv_8m8,VMSLEU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmsleu_vv_16m1,VMSLEU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmsleu_vv_16m2,VMSLEU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmsleu_vv_16m4,VMSLEU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmsleu_vv_16m8,VMSLEU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmsleu_vv_32m1,VMSLEU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmsleu_vv_32m2,VMSLEU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmsleu_vv_32m4,VMSLEU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmsleu_vv_32m8,VMSLEU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmsleu_vv_8m1_m,VMSLEU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmsleu_vv_8m2_m,VMSLEU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmsleu_vv_8m4_m,VMSLEU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmsleu_vv_8m8_m,VMSLEU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmsleu_vv_16m1_m,VMSLEU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmsleu_vv_16m2_m,VMSLEU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmsleu_vv_16m4_m,VMSLEU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmsleu_vv_16m8_m,VMSLEU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmsleu_vv_32m1_m,VMSLEU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmsleu_vv_32m2_m,VMSLEU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmsleu_vv_32m4_m,VMSLEU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmsleu_vv_32m8_m,VMSLEU_VV_m,v32i32>;

defm VMSLEU_VX : VALU_OPIVX<0b011100,"vmsleu.vx">;

def : PatVgrGpr<int_riscv_vmsleu_vx_8m1,VMSLEU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmsleu_vx_8m2,VMSLEU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmsleu_vx_8m4,VMSLEU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmsleu_vx_8m8,VMSLEU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmsleu_vx_16m1,VMSLEU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmsleu_vx_16m2,VMSLEU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmsleu_vx_16m4,VMSLEU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmsleu_vx_16m8,VMSLEU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmsleu_vx_32m1,VMSLEU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmsleu_vx_32m2,VMSLEU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmsleu_vx_32m4,VMSLEU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmsleu_vx_32m8,VMSLEU_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmsleu_vx_8m1_m,VMSLEU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmsleu_vx_8m2_m,VMSLEU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmsleu_vx_8m4_m,VMSLEU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmsleu_vx_8m8_m,VMSLEU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmsleu_vx_16m1_m,VMSLEU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmsleu_vx_16m2_m,VMSLEU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmsleu_vx_16m4_m,VMSLEU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmsleu_vx_16m8_m,VMSLEU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmsleu_vx_32m1_m,VMSLEU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmsleu_vx_32m2_m,VMSLEU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmsleu_vx_32m4_m,VMSLEU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmsleu_vx_32m8_m,VMSLEU_VX_m,v32i32>;


defm VMSLEU_VI : VALU_OPIVI_signed<0b011100,"vmsleu.vi">;

def : PatVgrSimm5<int_riscv_vmsleu_vi_8m1,VMSLEU_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vmsleu_vi_8m2,VMSLEU_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vmsleu_vi_8m4,VMSLEU_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vmsleu_vi_8m8,VMSLEU_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vmsleu_vi_16m1,VMSLEU_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vmsleu_vi_16m2,VMSLEU_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vmsleu_vi_16m4,VMSLEU_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vmsleu_vi_16m8,VMSLEU_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vmsleu_vi_32m1,VMSLEU_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vmsleu_vi_32m2,VMSLEU_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vmsleu_vi_32m4,VMSLEU_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vmsleu_vi_32m8,VMSLEU_VI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vmsleu_vi_8m1_m,VMSLEU_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vmsleu_vi_8m2_m,VMSLEU_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vmsleu_vi_8m4_m,VMSLEU_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vmsleu_vi_8m8_m,VMSLEU_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vmsleu_vi_16m1_m,VMSLEU_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vmsleu_vi_16m2_m,VMSLEU_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vmsleu_vi_16m4_m,VMSLEU_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vmsleu_vi_16m8_m,VMSLEU_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vmsleu_vi_32m1_m,VMSLEU_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vmsleu_vi_32m2_m,VMSLEU_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vmsleu_vi_32m4_m,VMSLEU_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vmsleu_vi_32m8_m,VMSLEU_VI_m,v32i32>;

defm VMSLE_VV : VALU_OPIVV<0b011101,"vmsle.vv">;

def : PatVgrVgr<int_riscv_vmsle_vv_8m1,VMSLE_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmsle_vv_8m2,VMSLE_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmsle_vv_8m4,VMSLE_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmsle_vv_8m8,VMSLE_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmsle_vv_16m1,VMSLE_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmsle_vv_16m2,VMSLE_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmsle_vv_16m4,VMSLE_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmsle_vv_16m8,VMSLE_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmsle_vv_32m1,VMSLE_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmsle_vv_32m2,VMSLE_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmsle_vv_32m4,VMSLE_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmsle_vv_32m8,VMSLE_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmsle_vv_8m1_m,VMSLE_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmsle_vv_8m2_m,VMSLE_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmsle_vv_8m4_m,VMSLE_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmsle_vv_8m8_m,VMSLE_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmsle_vv_16m1_m,VMSLE_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmsle_vv_16m2_m,VMSLE_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmsle_vv_16m4_m,VMSLE_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmsle_vv_16m8_m,VMSLE_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmsle_vv_32m1_m,VMSLE_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmsle_vv_32m2_m,VMSLE_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmsle_vv_32m4_m,VMSLE_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmsle_vv_32m8_m,VMSLE_VV_m,v32i32>;

defm VMSLE_VX : VALU_OPIVX<0b011101,"vmsle.vx">;

def : PatVgrGpr<int_riscv_vmsle_vx_8m1,VMSLE_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmsle_vx_8m2,VMSLE_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmsle_vx_8m4,VMSLE_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmsle_vx_8m8,VMSLE_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmsle_vx_16m1,VMSLE_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmsle_vx_16m2,VMSLE_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmsle_vx_16m4,VMSLE_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmsle_vx_16m8,VMSLE_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmsle_vx_32m1,VMSLE_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmsle_vx_32m2,VMSLE_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmsle_vx_32m4,VMSLE_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmsle_vx_32m8,VMSLE_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmsle_vx_8m1_m,VMSLE_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmsle_vx_8m2_m,VMSLE_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmsle_vx_8m4_m,VMSLE_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmsle_vx_8m8_m,VMSLE_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmsle_vx_16m1_m,VMSLE_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmsle_vx_16m2_m,VMSLE_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmsle_vx_16m4_m,VMSLE_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmsle_vx_16m8_m,VMSLE_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmsle_vx_32m1_m,VMSLE_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmsle_vx_32m2_m,VMSLE_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmsle_vx_32m4_m,VMSLE_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmsle_vx_32m8_m,VMSLE_VX_m,v32i32>;

defm VMSLE_VI : VALU_OPIVI_signed<0b011101,"vmsle.vi">;

def : PatVgrSimm5<int_riscv_vmsle_vi_8m1,VMSLE_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vmsle_vi_8m2,VMSLE_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vmsle_vi_8m4,VMSLE_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vmsle_vi_8m8,VMSLE_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vmsle_vi_16m1,VMSLE_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vmsle_vi_16m2,VMSLE_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vmsle_vi_16m4,VMSLE_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vmsle_vi_16m8,VMSLE_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vmsle_vi_32m1,VMSLE_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vmsle_vi_32m2,VMSLE_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vmsle_vi_32m4,VMSLE_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vmsle_vi_32m8,VMSLE_VI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vmsle_vi_8m1_m,VMSLE_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vmsle_vi_8m2_m,VMSLE_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vmsle_vi_8m4_m,VMSLE_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vmsle_vi_8m8_m,VMSLE_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vmsle_vi_16m1_m,VMSLE_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vmsle_vi_16m2_m,VMSLE_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vmsle_vi_16m4_m,VMSLE_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vmsle_vi_16m8_m,VMSLE_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vmsle_vi_32m1_m,VMSLE_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vmsle_vi_32m2_m,VMSLE_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vmsle_vi_32m4_m,VMSLE_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vmsle_vi_32m8_m,VMSLE_VI_m,v32i32>;

defm VMSGTU_VX : VALU_OPIVX<0b011110,"vmsgtu.vx">;

def : PatVgrGpr<int_riscv_vmsgtu_vx_8m1,VMSGTU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmsgtu_vx_8m2,VMSGTU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmsgtu_vx_8m4,VMSGTU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmsgtu_vx_8m8,VMSGTU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmsgtu_vx_16m1,VMSGTU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmsgtu_vx_16m2,VMSGTU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmsgtu_vx_16m4,VMSGTU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmsgtu_vx_16m8,VMSGTU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmsgtu_vx_32m1,VMSGTU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmsgtu_vx_32m2,VMSGTU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmsgtu_vx_32m4,VMSGTU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmsgtu_vx_32m8,VMSGTU_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmsgtu_vx_8m1_m,VMSGTU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmsgtu_vx_8m2_m,VMSGTU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmsgtu_vx_8m4_m,VMSGTU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmsgtu_vx_8m8_m,VMSGTU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmsgtu_vx_16m1_m,VMSGTU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmsgtu_vx_16m2_m,VMSGTU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmsgtu_vx_16m4_m,VMSGTU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmsgtu_vx_16m8_m,VMSGTU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmsgtu_vx_32m1_m,VMSGTU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmsgtu_vx_32m2_m,VMSGTU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmsgtu_vx_32m4_m,VMSGTU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmsgtu_vx_32m8_m,VMSGTU_VX_m,v32i32>;

defm VMSGTU_VI : VALU_OPIVI_signed<0b011110,"vmsgtu.vi">;

def : PatVgrSimm5<int_riscv_vmsgtu_vi_8m1,VMSGTU_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vmsgtu_vi_8m2,VMSGTU_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vmsgtu_vi_8m4,VMSGTU_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vmsgtu_vi_8m8,VMSGTU_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vmsgtu_vi_16m1,VMSGTU_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vmsgtu_vi_16m2,VMSGTU_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vmsgtu_vi_16m4,VMSGTU_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vmsgtu_vi_16m8,VMSGTU_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vmsgtu_vi_32m1,VMSGTU_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vmsgtu_vi_32m2,VMSGTU_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vmsgtu_vi_32m4,VMSGTU_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vmsgtu_vi_32m8,VMSGTU_VI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_8m1_m,VMSGTU_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_8m2_m,VMSGTU_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_8m4_m,VMSGTU_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_8m8_m,VMSGTU_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_16m1_m,VMSGTU_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_16m2_m,VMSGTU_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_16m4_m,VMSGTU_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_16m8_m,VMSGTU_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_32m1_m,VMSGTU_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_32m2_m,VMSGTU_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_32m4_m,VMSGTU_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vmsgtu_vi_32m8_m,VMSGTU_VI_m,v32i32>;

defm VMSGT_VX : VALU_OPIVX<0b011111,"vmsgt.vx">;

def : PatVgrGpr<int_riscv_vmsgt_vx_8m1,VMSGT_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmsgt_vx_8m2,VMSGT_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmsgt_vx_8m4,VMSGT_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmsgt_vx_8m8,VMSGT_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmsgt_vx_16m1,VMSGT_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmsgt_vx_16m2,VMSGT_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmsgt_vx_16m4,VMSGT_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmsgt_vx_16m8,VMSGT_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmsgt_vx_32m1,VMSGT_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmsgt_vx_32m2,VMSGT_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmsgt_vx_32m4,VMSGT_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmsgt_vx_32m8,VMSGT_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmsgt_vx_8m1_m,VMSGT_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmsgt_vx_8m2_m,VMSGT_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmsgt_vx_8m4_m,VMSGT_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmsgt_vx_8m8_m,VMSGT_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmsgt_vx_16m1_m,VMSGT_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmsgt_vx_16m2_m,VMSGT_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmsgt_vx_16m4_m,VMSGT_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmsgt_vx_16m8_m,VMSGT_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmsgt_vx_32m1_m,VMSGT_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmsgt_vx_32m2_m,VMSGT_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmsgt_vx_32m4_m,VMSGT_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmsgt_vx_32m8_m,VMSGT_VX_m,v32i32>;

defm VMSGT_VI : VALU_OPIVI_signed<0b011111,"vmsgt.vi">;

def : PatVgrSimm5<int_riscv_vmsgt_vi_8m1,VMSGT_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vmsgt_vi_8m2,VMSGT_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vmsgt_vi_8m4,VMSGT_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vmsgt_vi_8m8,VMSGT_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vmsgt_vi_16m1,VMSGT_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vmsgt_vi_16m2,VMSGT_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vmsgt_vi_16m4,VMSGT_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vmsgt_vi_16m8,VMSGT_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vmsgt_vi_32m1,VMSGT_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vmsgt_vi_32m2,VMSGT_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vmsgt_vi_32m4,VMSGT_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vmsgt_vi_32m8,VMSGT_VI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vmsgt_vi_8m1_m,VMSGT_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vmsgt_vi_8m2_m,VMSGT_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vmsgt_vi_8m4_m,VMSGT_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vmsgt_vi_8m8_m,VMSGT_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vmsgt_vi_16m1_m,VMSGT_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vmsgt_vi_16m2_m,VMSGT_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vmsgt_vi_16m4_m,VMSGT_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vmsgt_vi_16m8_m,VMSGT_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vmsgt_vi_32m1_m,VMSGT_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vmsgt_vi_32m2_m,VMSGT_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vmsgt_vi_32m4_m,VMSGT_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vmsgt_vi_32m8_m,VMSGT_VI_m,v32i32>;

defm VMINU_VV : VALU_OPIVV<0b000100,"vminu.vv">;

def : PatVgrVgr<int_riscv_vminu_vv_8m1,VMINU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vminu_vv_8m2,VMINU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vminu_vv_8m4,VMINU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vminu_vv_8m8,VMINU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vminu_vv_16m1,VMINU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vminu_vv_16m2,VMINU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vminu_vv_16m4,VMINU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vminu_vv_16m8,VMINU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vminu_vv_32m1,VMINU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vminu_vv_32m2,VMINU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vminu_vv_32m4,VMINU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vminu_vv_32m8,VMINU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vminu_vv_8m1_m,VMINU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vminu_vv_8m2_m,VMINU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vminu_vv_8m4_m,VMINU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vminu_vv_8m8_m,VMINU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vminu_vv_16m1_m,VMINU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vminu_vv_16m2_m,VMINU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vminu_vv_16m4_m,VMINU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vminu_vv_16m8_m,VMINU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vminu_vv_32m1_m,VMINU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vminu_vv_32m2_m,VMINU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vminu_vv_32m4_m,VMINU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vminu_vv_32m8_m,VMINU_VV_m,v32i32>;

defm VMINU_VX : VALU_OPIVX<0b000100,"vminu.vx">;

def : PatVgrGpr<int_riscv_vminu_vx_8m1,VMINU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vminu_vx_8m2,VMINU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vminu_vx_8m4,VMINU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vminu_vx_8m8,VMINU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vminu_vx_16m1,VMINU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vminu_vx_16m2,VMINU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vminu_vx_16m4,VMINU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vminu_vx_16m8,VMINU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vminu_vx_32m1,VMINU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vminu_vx_32m2,VMINU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vminu_vx_32m4,VMINU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vminu_vx_32m8,VMINU_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vminu_vx_8m1_m,VMINU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vminu_vx_8m2_m,VMINU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vminu_vx_8m4_m,VMINU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vminu_vx_8m8_m,VMINU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vminu_vx_16m1_m,VMINU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vminu_vx_16m2_m,VMINU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vminu_vx_16m4_m,VMINU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vminu_vx_16m8_m,VMINU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vminu_vx_32m1_m,VMINU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vminu_vx_32m2_m,VMINU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vminu_vx_32m4_m,VMINU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vminu_vx_32m8_m,VMINU_VX_m,v32i32>;

defm VMIN_VV : VALU_OPIVV<0b000101,"vmin.vv">;

def : PatVgrVgr<int_riscv_vmin_vv_8m1,VMIN_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmin_vv_8m2,VMIN_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmin_vv_8m4,VMIN_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmin_vv_8m8,VMIN_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmin_vv_16m1,VMIN_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmin_vv_16m2,VMIN_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmin_vv_16m4,VMIN_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmin_vv_16m8,VMIN_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmin_vv_32m1,VMIN_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmin_vv_32m2,VMIN_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmin_vv_32m4,VMIN_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmin_vv_32m8,VMIN_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmin_vv_8m1_m,VMIN_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmin_vv_8m2_m,VMIN_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmin_vv_8m4_m,VMIN_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmin_vv_8m8_m,VMIN_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmin_vv_16m1_m,VMIN_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmin_vv_16m2_m,VMIN_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmin_vv_16m4_m,VMIN_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmin_vv_16m8_m,VMIN_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmin_vv_32m1_m,VMIN_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmin_vv_32m2_m,VMIN_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmin_vv_32m4_m,VMIN_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmin_vv_32m8_m,VMIN_VV_m,v32i32>;

defm VMIN_VX : VALU_OPIVX<0b000101,"vmin.vx">;

def : PatVgrGpr<int_riscv_vmin_vx_8m1,VMIN_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmin_vx_8m2,VMIN_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmin_vx_8m4,VMIN_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmin_vx_8m8,VMIN_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmin_vx_16m1,VMIN_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmin_vx_16m2,VMIN_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmin_vx_16m4,VMIN_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmin_vx_16m8,VMIN_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmin_vx_32m1,VMIN_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmin_vx_32m2,VMIN_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmin_vx_32m4,VMIN_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmin_vx_32m8,VMIN_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmin_vx_8m1_m,VMIN_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmin_vx_8m2_m,VMIN_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmin_vx_8m4_m,VMIN_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmin_vx_8m8_m,VMIN_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmin_vx_16m1_m,VMIN_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmin_vx_16m2_m,VMIN_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmin_vx_16m4_m,VMIN_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmin_vx_16m8_m,VMIN_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmin_vx_32m1_m,VMIN_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmin_vx_32m2_m,VMIN_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmin_vx_32m4_m,VMIN_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmin_vx_32m8_m,VMIN_VX_m,v32i32>;

defm VMAXU_VV : VALU_OPIVV<0b000110,"vmaxu.vv">;

def : PatVgrVgr<int_riscv_vmaxu_vv_8m1,VMAXU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmaxu_vv_8m2,VMAXU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmaxu_vv_8m4,VMAXU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmaxu_vv_8m8,VMAXU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmaxu_vv_16m1,VMAXU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmaxu_vv_16m2,VMAXU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmaxu_vv_16m4,VMAXU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmaxu_vv_16m8,VMAXU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmaxu_vv_32m1,VMAXU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmaxu_vv_32m2,VMAXU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmaxu_vv_32m4,VMAXU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmaxu_vv_32m8,VMAXU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmaxu_vv_8m1_m,VMAXU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmaxu_vv_8m2_m,VMAXU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmaxu_vv_8m4_m,VMAXU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmaxu_vv_8m8_m,VMAXU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmaxu_vv_16m1_m,VMAXU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmaxu_vv_16m2_m,VMAXU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmaxu_vv_16m4_m,VMAXU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmaxu_vv_16m8_m,VMAXU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmaxu_vv_32m1_m,VMAXU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmaxu_vv_32m2_m,VMAXU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmaxu_vv_32m4_m,VMAXU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmaxu_vv_32m8_m,VMAXU_VV_m,v32i32>;

defm VMAXU_VX : VALU_OPIVX<0b000110,"vmaxu.vx">;

def : PatVgrGpr<int_riscv_vmaxu_vx_8m1,VMAXU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmaxu_vx_8m2,VMAXU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmaxu_vx_8m4,VMAXU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmaxu_vx_8m8,VMAXU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmaxu_vx_16m1,VMAXU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmaxu_vx_16m2,VMAXU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmaxu_vx_16m4,VMAXU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmaxu_vx_16m8,VMAXU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmaxu_vx_32m1,VMAXU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmaxu_vx_32m2,VMAXU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmaxu_vx_32m4,VMAXU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmaxu_vx_32m8,VMAXU_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmaxu_vx_8m1_m,VMAXU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmaxu_vx_8m2_m,VMAXU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmaxu_vx_8m4_m,VMAXU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmaxu_vx_8m8_m,VMAXU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmaxu_vx_16m1_m,VMAXU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmaxu_vx_16m2_m,VMAXU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmaxu_vx_16m4_m,VMAXU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmaxu_vx_16m8_m,VMAXU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmaxu_vx_32m1_m,VMAXU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmaxu_vx_32m2_m,VMAXU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmaxu_vx_32m4_m,VMAXU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmaxu_vx_32m8_m,VMAXU_VX_m,v32i32>;

defm VMAX_VV : VALU_OPIVV<0b000111,"vmax.vv">;

def : PatVgrVgr<int_riscv_vmax_vv_8m1,VMAX_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmax_vv_8m2,VMAX_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmax_vv_8m4,VMAX_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmax_vv_8m8,VMAX_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmax_vv_16m1,VMAX_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmax_vv_16m2,VMAX_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmax_vv_16m4,VMAX_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmax_vv_16m8,VMAX_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmax_vv_32m1,VMAX_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmax_vv_32m2,VMAX_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmax_vv_32m4,VMAX_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmax_vv_32m8,VMAX_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmax_vv_8m1_m,VMAX_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmax_vv_8m2_m,VMAX_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmax_vv_8m4_m,VMAX_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmax_vv_8m8_m,VMAX_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmax_vv_16m1_m,VMAX_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmax_vv_16m2_m,VMAX_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmax_vv_16m4_m,VMAX_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmax_vv_16m8_m,VMAX_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmax_vv_32m1_m,VMAX_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmax_vv_32m2_m,VMAX_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmax_vv_32m4_m,VMAX_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmax_vv_32m8_m,VMAX_VV_m,v32i32>;

defm VMAX_VX : VALU_OPIVX<0b000111,"vmax.vx">;

def : PatVgrGpr<int_riscv_vmax_vx_8m1,VMAX_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmax_vx_8m2,VMAX_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmax_vx_8m4,VMAX_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmax_vx_8m8,VMAX_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmax_vx_16m1,VMAX_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmax_vx_16m2,VMAX_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmax_vx_16m4,VMAX_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmax_vx_16m8,VMAX_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmax_vx_32m1,VMAX_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmax_vx_32m2,VMAX_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmax_vx_32m4,VMAX_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmax_vx_32m8,VMAX_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmax_vx_8m1_m,VMAX_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmax_vx_8m2_m,VMAX_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmax_vx_8m4_m,VMAX_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmax_vx_8m8_m,VMAX_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmax_vx_16m1_m,VMAX_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmax_vx_16m2_m,VMAX_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmax_vx_16m4_m,VMAX_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmax_vx_16m8_m,VMAX_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmax_vx_32m1_m,VMAX_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmax_vx_32m2_m,VMAX_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmax_vx_32m4_m,VMAX_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmax_vx_32m8_m,VMAX_VX_m,v32i32>;

/*************Vector Single-Width Integer Multiply Functions****************/

defm VMUL_VV : VALU_OPMVV<0b100101,"vmul.vv">;

def : PatVgrVgr<int_riscv_vmul_vv_8m1,VMUL_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmul_vv_8m2,VMUL_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmul_vv_8m4,VMUL_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmul_vv_8m8,VMUL_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmul_vv_16m1,VMUL_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmul_vv_16m2,VMUL_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmul_vv_16m4,VMUL_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmul_vv_16m8,VMUL_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmul_vv_32m1,VMUL_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmul_vv_32m2,VMUL_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmul_vv_32m4,VMUL_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmul_vv_32m8,VMUL_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmul_vv_8m1_m,VMUL_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmul_vv_8m2_m,VMUL_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmul_vv_8m4_m,VMUL_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmul_vv_8m8_m,VMUL_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmul_vv_16m1_m,VMUL_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmul_vv_16m2_m,VMUL_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmul_vv_16m4_m,VMUL_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmul_vv_16m8_m,VMUL_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmul_vv_32m1_m,VMUL_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmul_vv_32m2_m,VMUL_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmul_vv_32m4_m,VMUL_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmul_vv_32m8_m,VMUL_VV_m,v32i32>;

defm VMUL_VX : VALU_OPMVX<0b100101,"vmul.vx">;

def : PatVgrGpr<int_riscv_vmul_vx_8m1,VMUL_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmul_vx_8m2,VMUL_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmul_vx_8m4,VMUL_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmul_vx_8m8,VMUL_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmul_vx_16m1,VMUL_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmul_vx_16m2,VMUL_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmul_vx_16m4,VMUL_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmul_vx_16m8,VMUL_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmul_vx_32m1,VMUL_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmul_vx_32m2,VMUL_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmul_vx_32m4,VMUL_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmul_vx_32m8,VMUL_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmul_vx_8m1_m,VMUL_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmul_vx_8m2_m,VMUL_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmul_vx_8m4_m,VMUL_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmul_vx_8m8_m,VMUL_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmul_vx_16m1_m,VMUL_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmul_vx_16m2_m,VMUL_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmul_vx_16m4_m,VMUL_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmul_vx_16m8_m,VMUL_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmul_vx_32m1_m,VMUL_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmul_vx_32m2_m,VMUL_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmul_vx_32m4_m,VMUL_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmul_vx_32m8_m,VMUL_VX_m,v32i32>;

defm VMULH_VV : VALU_OPMVV<0b100111,"vmulh.vv">;

def : PatVgrVgr<int_riscv_vmulh_vv_8m1,VMULH_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmulh_vv_8m2,VMULH_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmulh_vv_8m4,VMULH_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmulh_vv_8m8,VMULH_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmulh_vv_16m1,VMULH_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmulh_vv_16m2,VMULH_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmulh_vv_16m4,VMULH_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmulh_vv_16m8,VMULH_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmulh_vv_32m1,VMULH_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmulh_vv_32m2,VMULH_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmulh_vv_32m4,VMULH_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmulh_vv_32m8,VMULH_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmulh_vv_8m1_m,VMULH_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmulh_vv_8m2_m,VMULH_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmulh_vv_8m4_m,VMULH_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmulh_vv_8m8_m,VMULH_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmulh_vv_16m1_m,VMULH_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmulh_vv_16m2_m,VMULH_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmulh_vv_16m4_m,VMULH_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmulh_vv_16m8_m,VMULH_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmulh_vv_32m1_m,VMULH_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmulh_vv_32m2_m,VMULH_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmulh_vv_32m4_m,VMULH_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmulh_vv_32m8_m,VMULH_VV_m,v32i32>;

defm VMULH_VX : VALU_OPMVX<0b100111,"vmulh.vx">;


def : PatVgrGpr<int_riscv_vmulh_vx_8m1,VMULH_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmulh_vx_8m2,VMULH_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmulh_vx_8m4,VMULH_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmulh_vx_8m8,VMULH_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmulh_vx_16m1,VMULH_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmulh_vx_16m2,VMULH_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmulh_vx_16m4,VMULH_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmulh_vx_16m8,VMULH_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmulh_vx_32m1,VMULH_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmulh_vx_32m2,VMULH_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmulh_vx_32m4,VMULH_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmulh_vx_32m8,VMULH_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmulh_vx_8m1_m,VMULH_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmulh_vx_8m2_m,VMULH_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmulh_vx_8m4_m,VMULH_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmulh_vx_8m8_m,VMULH_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmulh_vx_16m1_m,VMULH_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmulh_vx_16m2_m,VMULH_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmulh_vx_16m4_m,VMULH_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmulh_vx_16m8_m,VMULH_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmulh_vx_32m1_m,VMULH_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmulh_vx_32m2_m,VMULH_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmulh_vx_32m4_m,VMULH_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmulh_vx_32m8_m,VMULH_VX_m,v32i32>;

defm VMULHU_VV : VALU_OPMVV<0b100100,"vmulhu.vv">;

def : PatVgrVgr<int_riscv_vmulhu_vv_8m1,VMULHU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmulhu_vv_8m2,VMULHU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmulhu_vv_8m4,VMULHU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmulhu_vv_8m8,VMULHU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmulhu_vv_16m1,VMULHU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmulhu_vv_16m2,VMULHU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmulhu_vv_16m4,VMULHU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmulhu_vv_16m8,VMULHU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmulhu_vv_32m1,VMULHU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmulhu_vv_32m2,VMULHU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmulhu_vv_32m4,VMULHU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmulhu_vv_32m8,VMULHU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmulhu_vv_8m1_m,VMULHU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmulhu_vv_8m2_m,VMULHU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmulhu_vv_8m4_m,VMULHU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmulhu_vv_8m8_m,VMULHU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmulhu_vv_16m1_m,VMULHU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmulhu_vv_16m2_m,VMULHU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmulhu_vv_16m4_m,VMULHU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmulhu_vv_16m8_m,VMULHU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmulhu_vv_32m1_m,VMULHU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmulhu_vv_32m2_m,VMULHU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmulhu_vv_32m4_m,VMULHU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmulhu_vv_32m8_m,VMULHU_VV_m,v32i32>;

defm VMULHU_VX : VALU_OPMVX<0b100100,"vmulhu.vx">;

def : PatVgrGpr<int_riscv_vmulhu_vx_8m1,VMULHU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmulhu_vx_8m2,VMULHU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmulhu_vx_8m4,VMULHU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmulhu_vx_8m8,VMULHU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmulhu_vx_16m1,VMULHU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmulhu_vx_16m2,VMULHU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmulhu_vx_16m4,VMULHU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmulhu_vx_16m8,VMULHU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmulhu_vx_32m1,VMULHU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmulhu_vx_32m2,VMULHU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmulhu_vx_32m4,VMULHU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmulhu_vx_32m8,VMULHU_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmulhu_vx_8m1_m,VMULHU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmulhu_vx_8m2_m,VMULHU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmulhu_vx_8m4_m,VMULHU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmulhu_vx_8m8_m,VMULHU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmulhu_vx_16m1_m,VMULHU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmulhu_vx_16m2_m,VMULHU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmulhu_vx_16m4_m,VMULHU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmulhu_vx_16m8_m,VMULHU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmulhu_vx_32m1_m,VMULHU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmulhu_vx_32m2_m,VMULHU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmulhu_vx_32m4_m,VMULHU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmulhu_vx_32m8_m,VMULHU_VX_m,v32i32>;

defm VMULHSU_VV : VALU_OPMVV<0b100110,"vmulhsu.vv">;

def : PatVgrVgr<int_riscv_vmulhsu_vv_8m1,VMULHSU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vmulhsu_vv_8m2,VMULHSU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vmulhsu_vv_8m4,VMULHSU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vmulhsu_vv_8m8,VMULHSU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vmulhsu_vv_16m1,VMULHSU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vmulhsu_vv_16m2,VMULHSU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vmulhsu_vv_16m4,VMULHSU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vmulhsu_vv_16m8,VMULHSU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vmulhsu_vv_32m1,VMULHSU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vmulhsu_vv_32m2,VMULHSU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vmulhsu_vv_32m4,VMULHSU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vmulhsu_vv_32m8,VMULHSU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vmulhsu_vv_8m1_m,VMULHSU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vmulhsu_vv_8m2_m,VMULHSU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vmulhsu_vv_8m4_m,VMULHSU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vmulhsu_vv_8m8_m,VMULHSU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vmulhsu_vv_16m1_m,VMULHSU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vmulhsu_vv_16m2_m,VMULHSU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vmulhsu_vv_16m4_m,VMULHSU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vmulhsu_vv_16m8_m,VMULHSU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vmulhsu_vv_32m1_m,VMULHSU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vmulhsu_vv_32m2_m,VMULHSU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vmulhsu_vv_32m4_m,VMULHSU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vmulhsu_vv_32m8_m,VMULHSU_VV_m,v32i32>;

defm VMULHSU_VX : VALU_OPMVX<0b100110,"vmulhsu.vx">;

def : PatVgrGpr<int_riscv_vmulhsu_vx_8m1,VMULHSU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vmulhsu_vx_8m2,VMULHSU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vmulhsu_vx_8m4,VMULHSU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vmulhsu_vx_8m8,VMULHSU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vmulhsu_vx_16m1,VMULHSU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vmulhsu_vx_16m2,VMULHSU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vmulhsu_vx_16m4,VMULHSU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vmulhsu_vx_16m8,VMULHSU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vmulhsu_vx_32m1,VMULHSU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vmulhsu_vx_32m2,VMULHSU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vmulhsu_vx_32m4,VMULHSU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vmulhsu_vx_32m8,VMULHSU_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vmulhsu_vx_8m1_m,VMULHSU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vmulhsu_vx_8m2_m,VMULHSU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vmulhsu_vx_8m4_m,VMULHSU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vmulhsu_vx_8m8_m,VMULHSU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vmulhsu_vx_16m1_m,VMULHSU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vmulhsu_vx_16m2_m,VMULHSU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vmulhsu_vx_16m4_m,VMULHSU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vmulhsu_vx_16m8_m,VMULHSU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vmulhsu_vx_32m1_m,VMULHSU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vmulhsu_vx_32m2_m,VMULHSU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vmulhsu_vx_32m4_m,VMULHSU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vmulhsu_vx_32m8_m,VMULHSU_VX_m,v32i32>;

/*****************Vector Integer Divide Functions*******************/
defm VDIVU_VV : VALU_OPMVV<0b100000,"vdivu.vv">;

def : PatVgrVgr<int_riscv_vdivu_vv_8m1,VDIVU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vdivu_vv_8m2,VDIVU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vdivu_vv_8m4,VDIVU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vdivu_vv_8m8,VDIVU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vdivu_vv_16m1,VDIVU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vdivu_vv_16m2,VDIVU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vdivu_vv_16m4,VDIVU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vdivu_vv_16m8,VDIVU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vdivu_vv_32m1,VDIVU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vdivu_vv_32m2,VDIVU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vdivu_vv_32m4,VDIVU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vdivu_vv_32m8,VDIVU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vdivu_vv_8m1_m,VDIVU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vdivu_vv_8m2_m,VDIVU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vdivu_vv_8m4_m,VDIVU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vdivu_vv_8m8_m,VDIVU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vdivu_vv_16m1_m,VDIVU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vdivu_vv_16m2_m,VDIVU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vdivu_vv_16m4_m,VDIVU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vdivu_vv_16m8_m,VDIVU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vdivu_vv_32m1_m,VDIVU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vdivu_vv_32m2_m,VDIVU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vdivu_vv_32m4_m,VDIVU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vdivu_vv_32m8_m,VDIVU_VV_m,v32i32>;

defm VDIVU_VX : VALU_OPMVX<0b100000,"vdivu.vx">;

def : PatVgrGpr<int_riscv_vdivu_vx_8m1,VDIVU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vdivu_vx_8m2,VDIVU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vdivu_vx_8m4,VDIVU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vdivu_vx_8m8,VDIVU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vdivu_vx_16m1,VDIVU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vdivu_vx_16m2,VDIVU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vdivu_vx_16m4,VDIVU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vdivu_vx_16m8,VDIVU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vdivu_vx_32m1,VDIVU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vdivu_vx_32m2,VDIVU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vdivu_vx_32m4,VDIVU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vdivu_vx_32m8,VDIVU_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vdivu_vx_8m1_m,VDIVU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vdivu_vx_8m2_m,VDIVU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vdivu_vx_8m4_m,VDIVU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vdivu_vx_8m8_m,VDIVU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vdivu_vx_16m1_m,VDIVU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vdivu_vx_16m2_m,VDIVU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vdivu_vx_16m4_m,VDIVU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vdivu_vx_16m8_m,VDIVU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vdivu_vx_32m1_m,VDIVU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vdivu_vx_32m2_m,VDIVU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vdivu_vx_32m4_m,VDIVU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vdivu_vx_32m8_m,VDIVU_VX_m,v32i32>;

defm VDIV_VV : VALU_OPMVV<0b100001,"vdiv.vv">;

def : PatVgrVgr<int_riscv_vdiv_vv_8m1,VDIV_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vdiv_vv_8m2,VDIV_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vdiv_vv_8m4,VDIV_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vdiv_vv_8m8,VDIV_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vdiv_vv_16m1,VDIV_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vdiv_vv_16m2,VDIV_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vdiv_vv_16m4,VDIV_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vdiv_vv_16m8,VDIV_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vdiv_vv_32m1,VDIV_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vdiv_vv_32m2,VDIV_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vdiv_vv_32m4,VDIV_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vdiv_vv_32m8,VDIV_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vdiv_vv_8m1_m,VDIV_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vdiv_vv_8m2_m,VDIV_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vdiv_vv_8m4_m,VDIV_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vdiv_vv_8m8_m,VDIV_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vdiv_vv_16m1_m,VDIV_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vdiv_vv_16m2_m,VDIV_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vdiv_vv_16m4_m,VDIV_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vdiv_vv_16m8_m,VDIV_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vdiv_vv_32m1_m,VDIV_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vdiv_vv_32m2_m,VDIV_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vdiv_vv_32m4_m,VDIV_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vdiv_vv_32m8_m,VDIV_VV_m,v32i32>;


defm VDIV_VX : VALU_OPMVX<0b100001,"vdiv.vx">;

def : PatVgrGpr<int_riscv_vdiv_vx_8m1,VDIV_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vdiv_vx_8m2,VDIV_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vdiv_vx_8m4,VDIV_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vdiv_vx_8m8,VDIV_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vdiv_vx_16m1,VDIV_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vdiv_vx_16m2,VDIV_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vdiv_vx_16m4,VDIV_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vdiv_vx_16m8,VDIV_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vdiv_vx_32m1,VDIV_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vdiv_vx_32m2,VDIV_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vdiv_vx_32m4,VDIV_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vdiv_vx_32m8,VDIV_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vdiv_vx_8m1_m,VDIV_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vdiv_vx_8m2_m,VDIV_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vdiv_vx_8m4_m,VDIV_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vdiv_vx_8m8_m,VDIV_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vdiv_vx_16m1_m,VDIV_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vdiv_vx_16m2_m,VDIV_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vdiv_vx_16m4_m,VDIV_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vdiv_vx_16m8_m,VDIV_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vdiv_vx_32m1_m,VDIV_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vdiv_vx_32m2_m,VDIV_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vdiv_vx_32m4_m,VDIV_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vdiv_vx_32m8_m,VDIV_VX_m,v32i32>;

defm VREMU_VV : VALU_OPMVV<0b100010,"vremu.vv">;

def : PatVgrVgr<int_riscv_vremu_vv_8m1,VREMU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vremu_vv_8m2,VREMU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vremu_vv_8m4,VREMU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vremu_vv_8m8,VREMU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vremu_vv_16m1,VREMU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vremu_vv_16m2,VREMU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vremu_vv_16m4,VREMU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vremu_vv_16m8,VREMU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vremu_vv_32m1,VREMU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vremu_vv_32m2,VREMU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vremu_vv_32m4,VREMU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vremu_vv_32m8,VREMU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vremu_vv_8m1_m,VREMU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vremu_vv_8m2_m,VREMU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vremu_vv_8m4_m,VREMU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vremu_vv_8m8_m,VREMU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vremu_vv_16m1_m,VREMU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vremu_vv_16m2_m,VREMU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vremu_vv_16m4_m,VREMU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vremu_vv_16m8_m,VREMU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vremu_vv_32m1_m,VREMU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vremu_vv_32m2_m,VREMU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vremu_vv_32m4_m,VREMU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vremu_vv_32m8_m,VREMU_VV_m,v32i32>;

defm VREMU_VX : VALU_OPMVX<0b100010,"vremu.vx">;

def : PatVgrGpr<int_riscv_vremu_vx_8m1,VREMU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vremu_vx_8m2,VREMU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vremu_vx_8m4,VREMU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vremu_vx_8m8,VREMU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vremu_vx_16m1,VREMU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vremu_vx_16m2,VREMU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vremu_vx_16m4,VREMU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vremu_vx_16m8,VREMU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vremu_vx_32m1,VREMU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vremu_vx_32m2,VREMU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vremu_vx_32m4,VREMU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vremu_vx_32m8,VREMU_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vremu_vx_8m1_m,VREMU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vremu_vx_8m2_m,VREMU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vremu_vx_8m4_m,VREMU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vremu_vx_8m8_m,VREMU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vremu_vx_16m1_m,VREMU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vremu_vx_16m2_m,VREMU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vremu_vx_16m4_m,VREMU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vremu_vx_16m8_m,VREMU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vremu_vx_32m1_m,VREMU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vremu_vx_32m2_m,VREMU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vremu_vx_32m4_m,VREMU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vremu_vx_32m8_m,VREMU_VX_m,v32i32>;

defm VREM_VV : VALU_OPMVV<0b100011,"vrem.vv">;

def : PatVgrVgr<int_riscv_vrem_vv_8m1,VREM_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vrem_vv_8m2,VREM_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vrem_vv_8m4,VREM_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vrem_vv_8m8,VREM_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vrem_vv_16m1,VREM_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vrem_vv_16m2,VREM_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vrem_vv_16m4,VREM_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vrem_vv_16m8,VREM_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vrem_vv_32m1,VREM_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vrem_vv_32m2,VREM_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vrem_vv_32m4,VREM_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vrem_vv_32m8,VREM_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vrem_vv_8m1_m,VREM_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vrem_vv_8m2_m,VREM_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vrem_vv_8m4_m,VREM_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vrem_vv_8m8_m,VREM_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vrem_vv_16m1_m,VREM_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vrem_vv_16m2_m,VREM_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vrem_vv_16m4_m,VREM_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vrem_vv_16m8_m,VREM_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vrem_vv_32m1_m,VREM_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vrem_vv_32m2_m,VREM_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vrem_vv_32m4_m,VREM_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vrem_vv_32m8_m,VREM_VV_m,v32i32>;


defm VREM_VX : VALU_OPMVX<0b100011,"vrem.vx">;

def : PatVgrGpr<int_riscv_vrem_vx_8m1,VREM_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vrem_vx_8m2,VREM_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vrem_vx_8m4,VREM_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vrem_vx_8m8,VREM_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vrem_vx_16m1,VREM_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vrem_vx_16m2,VREM_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vrem_vx_16m4,VREM_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vrem_vx_16m8,VREM_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vrem_vx_32m1,VREM_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vrem_vx_32m2,VREM_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vrem_vx_32m4,VREM_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vrem_vx_32m8,VREM_VX_um,v32i32>;


def : PatVmVgrGpr<int_riscv_vrem_vx_8m1_m,VREM_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vrem_vx_8m2_m,VREM_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vrem_vx_8m4_m,VREM_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vrem_vx_8m8_m,VREM_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vrem_vx_16m1_m,VREM_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vrem_vx_16m2_m,VREM_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vrem_vx_16m4_m,VREM_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vrem_vx_16m8_m,VREM_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vrem_vx_32m1_m,VREM_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vrem_vx_32m2_m,VREM_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vrem_vx_32m4_m,VREM_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vrem_vx_32m8_m,VREM_VX_m,v32i32>;

/************Vector Widening Integer Multiply Funtions***************/

defm VWMUL_VV : VALU_OPMVV<0b111011,"vwmul.vv">;

def : PatVgrVgr<int_riscv_vwmul_vv_16m2,VWMUL_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vwmul_vv_16m4,VWMUL_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vwmul_vv_16m8,VWMUL_VV_um,v64i8>;

def : PatVgrVgr<int_riscv_vwmul_vv_32m2,VWMUL_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vwmul_vv_32m4,VWMUL_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vwmul_vv_32m8,VWMUL_VV_um,v32i16>;

def : PatVmVgrVgr<int_riscv_vwmul_vv_16m2_m,VWMUL_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vwmul_vv_16m4_m,VWMUL_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vwmul_vv_16m8_m,VWMUL_VV_m,v64i8>;

def : PatVmVgrVgr<int_riscv_vwmul_vv_32m2_m,VWMUL_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vwmul_vv_32m4_m,VWMUL_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vwmul_vv_32m8_m,VWMUL_VV_m,v32i16>;


defm VWMUL_VX : VALU_OPMVX<0b111011,"vwmul.vx">;

def : PatVgrGpr<int_riscv_vwmul_vx_16m2,VWMUL_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vwmul_vx_16m4,VWMUL_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vwmul_vx_16m8,VWMUL_VX_um,v64i8>;

def : PatVgrGpr<int_riscv_vwmul_vx_32m2,VWMUL_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vwmul_vx_32m4,VWMUL_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vwmul_vx_32m8,VWMUL_VX_um,v32i16>;

def : PatVmVgrGpr<int_riscv_vwmul_vx_16m2_m,VWMUL_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vwmul_vx_16m4_m,VWMUL_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vwmul_vx_16m8_m,VWMUL_VX_m,v64i8>;

def : PatVmVgrGpr<int_riscv_vwmul_vx_32m2_m,VWMUL_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vwmul_vx_32m4_m,VWMUL_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vwmul_vx_32m8_m,VWMUL_VX_m,v32i16>;



defm VWMULU_VV : VALU_OPMVV<0b111000,"vwmulu.vv">;

def : PatVgrVgr<int_riscv_vwmulu_vv_16m2,VWMULU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vwmulu_vv_16m4,VWMULU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vwmulu_vv_16m8,VWMULU_VV_um,v64i8>;

def : PatVgrVgr<int_riscv_vwmulu_vv_32m2,VWMULU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vwmulu_vv_32m4,VWMULU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vwmulu_vv_32m8,VWMULU_VV_um,v32i16>;

def : PatVmVgrVgr<int_riscv_vwmulu_vv_16m2_m,VWMULU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vwmulu_vv_16m4_m,VWMULU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vwmulu_vv_16m8_m,VWMULU_VV_m,v64i8>;

def : PatVmVgrVgr<int_riscv_vwmulu_vv_32m2_m,VWMULU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vwmulu_vv_32m4_m,VWMULU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vwmulu_vv_32m8_m,VWMULU_VV_m,v32i16>;


defm VWMULU_VX : VALU_OPMVX<0b111000,"vwmulu.vx">;

def : PatVgrGpr<int_riscv_vwmulu_vx_16m2,VWMULU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vwmulu_vx_16m4,VWMULU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vwmulu_vx_16m8,VWMULU_VX_um,v64i8>;

def : PatVgrGpr<int_riscv_vwmulu_vx_32m2,VWMULU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vwmulu_vx_32m4,VWMULU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vwmulu_vx_32m8,VWMULU_VX_um,v32i16>;

def : PatVmVgrGpr<int_riscv_vwmulu_vx_16m2_m,VWMULU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vwmulu_vx_16m4_m,VWMULU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vwmulu_vx_16m8_m,VWMULU_VX_m,v64i8>;

def : PatVmVgrGpr<int_riscv_vwmulu_vx_32m2_m,VWMULU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vwmulu_vx_32m4_m,VWMULU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vwmulu_vx_32m8_m,VWMULU_VX_m,v32i16>;

defm VWMULSU_VV : VALU_OPMVV<0b111010,"vwmulsu.vv">;

def : PatVgrVgr<int_riscv_vwmulsu_vv_16m2,VWMULSU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vwmulsu_vv_16m4,VWMULSU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vwmulsu_vv_16m8,VWMULSU_VV_um,v64i8>;

def : PatVgrVgr<int_riscv_vwmulsu_vv_32m2,VWMULSU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vwmulsu_vv_32m4,VWMULSU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vwmulsu_vv_32m8,VWMULSU_VV_um,v32i16>;

def : PatVmVgrVgr<int_riscv_vwmulsu_vv_16m2_m,VWMULSU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vwmulsu_vv_16m4_m,VWMULSU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vwmulsu_vv_16m8_m,VWMULSU_VV_m,v64i8>;

def : PatVmVgrVgr<int_riscv_vwmulsu_vv_32m2_m,VWMULSU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vwmulsu_vv_32m4_m,VWMULSU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vwmulsu_vv_32m8_m,VWMULSU_VV_m,v32i16>;


defm VWMULSU_VX : VALU_OPMVX<0b111010,"vwmulsu.vx">;

def : PatVgrGpr<int_riscv_vwmulsu_vx_16m2,VWMULSU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vwmulsu_vx_16m4,VWMULSU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vwmulsu_vx_16m8,VWMULSU_VX_um,v64i8>;

def : PatVgrGpr<int_riscv_vwmulsu_vx_32m2,VWMULSU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vwmulsu_vx_32m4,VWMULSU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vwmulsu_vx_32m8,VWMULSU_VX_um,v32i16>;

def : PatVmVgrGpr<int_riscv_vwmulsu_vx_16m2_m,VWMULSU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vwmulsu_vx_16m4_m,VWMULSU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vwmulsu_vx_16m8_m,VWMULSU_VX_m,v64i8>;

def : PatVmVgrGpr<int_riscv_vwmulsu_vx_32m2_m,VWMULSU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vwmulsu_vx_32m4_m,VWMULSU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vwmulsu_vx_32m8_m,VWMULSU_VX_m,v32i16>;

/***********Vector Single-Width Integer Multiply-Add Functions************/

defm VMACC_VV : VALU_OPMVV_MulAdd<0b101101,"vmacc.vv">;

def : PatVgrVgrVgr<int_riscv_vmacc_vv_8m1,VMACC_VV_um,v16i8>;
def : PatVgrVgrVgr<int_riscv_vmacc_vv_8m2,VMACC_VV_um,v32i8>;
def : PatVgrVgrVgr<int_riscv_vmacc_vv_8m4,VMACC_VV_um,v64i8>;
def : PatVgrVgrVgr<int_riscv_vmacc_vv_8m8,VMACC_VV_um,v128i8>;

def : PatVgrVgrVgr<int_riscv_vmacc_vv_16m1,VMACC_VV_um,v8i16>;
def : PatVgrVgrVgr<int_riscv_vmacc_vv_16m2,VMACC_VV_um,v16i16>;
def : PatVgrVgrVgr<int_riscv_vmacc_vv_16m4,VMACC_VV_um,v32i16>;
def : PatVgrVgrVgr<int_riscv_vmacc_vv_16m8,VMACC_VV_um,v64i16>;

def : PatVgrVgrVgr<int_riscv_vmacc_vv_32m1,VMACC_VV_um,v4i32>;
def : PatVgrVgrVgr<int_riscv_vmacc_vv_32m2,VMACC_VV_um,v8i32>;
def : PatVgrVgrVgr<int_riscv_vmacc_vv_32m4,VMACC_VV_um,v16i32>;
def : PatVgrVgrVgr<int_riscv_vmacc_vv_32m8,VMACC_VV_um,v32i32>;

def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_8m1_m,VMACC_VV_m,v16i8>;
def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_8m2_m,VMACC_VV_m,v32i8>;
def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_8m4_m,VMACC_VV_m,v64i8>;
def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_8m8_m,VMACC_VV_m,v128i8>;

def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_16m1_m,VMACC_VV_m,v8i16>;
def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_16m2_m,VMACC_VV_m,v16i16>;
def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_16m4_m,VMACC_VV_m,v32i16>;
def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_16m8_m,VMACC_VV_m,v64i16>;

def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_32m1_m,VMACC_VV_m,v4i32>;
def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_32m2_m,VMACC_VV_m,v8i32>;
def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_32m4_m,VMACC_VV_m,v16i32>;
def : PatVmVgrVgrVgr<int_riscv_vmacc_vv_32m8_m,VMACC_VV_m,v32i32>;

defm VMACC_VX : VALU_OPMVX_MulAdd<0b101101,"vmacc.vx">;

def : PatVgrGprVgr<int_riscv_vmacc_vx_8m1,VMACC_VX_um,v16i8>;
def : PatVgrGprVgr<int_riscv_vmacc_vx_8m2,VMACC_VX_um,v32i8>;
def : PatVgrGprVgr<int_riscv_vmacc_vx_8m4,VMACC_VX_um,v64i8>;
def : PatVgrGprVgr<int_riscv_vmacc_vx_8m8,VMACC_VX_um,v128i8>;

def : PatVgrGprVgr<int_riscv_vmacc_vx_16m1,VMACC_VX_um,v8i16>;
def : PatVgrGprVgr<int_riscv_vmacc_vx_16m2,VMACC_VX_um,v16i16>;
def : PatVgrGprVgr<int_riscv_vmacc_vx_16m4,VMACC_VX_um,v32i16>;
def : PatVgrGprVgr<int_riscv_vmacc_vx_16m8,VMACC_VX_um,v64i16>;

def : PatVgrGprVgr<int_riscv_vmacc_vx_32m1,VMACC_VX_um,v4i32>;
def : PatVgrGprVgr<int_riscv_vmacc_vx_32m2,VMACC_VX_um,v8i32>;
def : PatVgrGprVgr<int_riscv_vmacc_vx_32m4,VMACC_VX_um,v16i32>;
def : PatVgrGprVgr<int_riscv_vmacc_vx_32m8,VMACC_VX_um,v32i32>;

def : PatVmVgrGprVgr<int_riscv_vmacc_vx_8m1_m,VMACC_VX_m,v16i8>;
def : PatVmVgrGprVgr<int_riscv_vmacc_vx_8m2_m,VMACC_VX_m,v32i8>;
def : PatVmVgrGprVgr<int_riscv_vmacc_vx_8m4_m,VMACC_VX_m,v64i8>;
def : PatVmVgrGprVgr<int_riscv_vmacc_vx_8m8_m,VMACC_VX_m,v128i8>;

def : PatVmVgrGprVgr<int_riscv_vmacc_vx_16m1_m,VMACC_VX_m,v8i16>;
def : PatVmVgrGprVgr<int_riscv_vmacc_vx_16m2_m,VMACC_VX_m,v16i16>;
def : PatVmVgrGprVgr<int_riscv_vmacc_vx_16m4_m,VMACC_VX_m,v32i16>;
def : PatVmVgrGprVgr<int_riscv_vmacc_vx_16m8_m,VMACC_VX_m,v64i16>;

def : PatVmVgrGprVgr<int_riscv_vmacc_vx_32m1_m,VMACC_VX_m,v4i32>;
def : PatVmVgrGprVgr<int_riscv_vmacc_vx_32m2_m,VMACC_VX_m,v8i32>;
def : PatVmVgrGprVgr<int_riscv_vmacc_vx_32m4_m,VMACC_VX_m,v16i32>;
def : PatVmVgrGprVgr<int_riscv_vmacc_vx_32m8_m,VMACC_VX_m,v32i32>;

defm VNMSAC_VV : VALU_OPMVV_MulAdd<0b101111,"vnmsac.vv">;

def : PatVgrVgrVgr<int_riscv_vnmsac_vv_8m1,VNMSAC_VV_um,v16i8>;
def : PatVgrVgrVgr<int_riscv_vnmsac_vv_8m2,VNMSAC_VV_um,v32i8>;
def : PatVgrVgrVgr<int_riscv_vnmsac_vv_8m4,VNMSAC_VV_um,v64i8>;
def : PatVgrVgrVgr<int_riscv_vnmsac_vv_8m8,VNMSAC_VV_um,v128i8>;

def : PatVgrVgrVgr<int_riscv_vnmsac_vv_16m1,VNMSAC_VV_um,v8i16>;
def : PatVgrVgrVgr<int_riscv_vnmsac_vv_16m2,VNMSAC_VV_um,v16i16>;
def : PatVgrVgrVgr<int_riscv_vnmsac_vv_16m4,VNMSAC_VV_um,v32i16>;
def : PatVgrVgrVgr<int_riscv_vnmsac_vv_16m8,VNMSAC_VV_um,v64i16>;

def : PatVgrVgrVgr<int_riscv_vnmsac_vv_32m1,VNMSAC_VV_um,v4i32>;
def : PatVgrVgrVgr<int_riscv_vnmsac_vv_32m2,VNMSAC_VV_um,v8i32>;
def : PatVgrVgrVgr<int_riscv_vnmsac_vv_32m4,VNMSAC_VV_um,v16i32>;
def : PatVgrVgrVgr<int_riscv_vnmsac_vv_32m8,VNMSAC_VV_um,v32i32>;

def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_8m1_m,VNMSAC_VV_m,v16i8>;
def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_8m2_m,VNMSAC_VV_m,v32i8>;
def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_8m4_m,VNMSAC_VV_m,v64i8>;
def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_8m8_m,VNMSAC_VV_m,v128i8>;

def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_16m1_m,VNMSAC_VV_m,v8i16>;
def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_16m2_m,VNMSAC_VV_m,v16i16>;
def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_16m4_m,VNMSAC_VV_m,v32i16>;
def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_16m8_m,VNMSAC_VV_m,v64i16>;

def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_32m1_m,VNMSAC_VV_m,v4i32>;
def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_32m2_m,VNMSAC_VV_m,v8i32>;
def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_32m4_m,VNMSAC_VV_m,v16i32>;
def : PatVmVgrVgrVgr<int_riscv_vnmsac_vv_32m8_m,VNMSAC_VV_m,v32i32>;

defm VNMSAC_VX : VALU_OPMVX_MulAdd<0b101111,"vnmsac.vx">;

def : PatVgrGprVgr<int_riscv_vnmsac_vx_8m1,VNMSAC_VX_um,v16i8>;
def : PatVgrGprVgr<int_riscv_vnmsac_vx_8m2,VNMSAC_VX_um,v32i8>;
def : PatVgrGprVgr<int_riscv_vnmsac_vx_8m4,VNMSAC_VX_um,v64i8>;
def : PatVgrGprVgr<int_riscv_vnmsac_vx_8m8,VNMSAC_VX_um,v128i8>;

def : PatVgrGprVgr<int_riscv_vnmsac_vx_16m1,VNMSAC_VX_um,v8i16>;
def : PatVgrGprVgr<int_riscv_vnmsac_vx_16m2,VNMSAC_VX_um,v16i16>;
def : PatVgrGprVgr<int_riscv_vnmsac_vx_16m4,VNMSAC_VX_um,v32i16>;
def : PatVgrGprVgr<int_riscv_vnmsac_vx_16m8,VNMSAC_VX_um,v64i16>;

def : PatVgrGprVgr<int_riscv_vnmsac_vx_32m1,VNMSAC_VX_um,v4i32>;
def : PatVgrGprVgr<int_riscv_vnmsac_vx_32m2,VNMSAC_VX_um,v8i32>;
def : PatVgrGprVgr<int_riscv_vnmsac_vx_32m4,VNMSAC_VX_um,v16i32>;
def : PatVgrGprVgr<int_riscv_vnmsac_vx_32m8,VNMSAC_VX_um,v32i32>;

def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_8m1_m,VNMSAC_VX_m,v16i8>;
def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_8m2_m,VNMSAC_VX_m,v32i8>;
def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_8m4_m,VNMSAC_VX_m,v64i8>;
def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_8m8_m,VNMSAC_VX_m,v128i8>;

def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_16m1_m,VNMSAC_VX_m,v8i16>;
def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_16m2_m,VNMSAC_VX_m,v16i16>;
def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_16m4_m,VNMSAC_VX_m,v32i16>;
def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_16m8_m,VNMSAC_VX_m,v64i16>;

def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_32m1_m,VNMSAC_VX_m,v4i32>;
def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_32m2_m,VNMSAC_VX_m,v8i32>;
def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_32m4_m,VNMSAC_VX_m,v16i32>;
def : PatVmVgrGprVgr<int_riscv_vnmsac_vx_32m8_m,VNMSAC_VX_m,v32i32>;

defm VMADD_VV : VALU_OPMVV_MulAdd<0b101001,"vmadd.vv">;

def : PatVgrVgrVgr<int_riscv_vmadd_vv_8m1,VMADD_VV_um,v16i8>;
def : PatVgrVgrVgr<int_riscv_vmadd_vv_8m2,VMADD_VV_um,v32i8>;
def : PatVgrVgrVgr<int_riscv_vmadd_vv_8m4,VMADD_VV_um,v64i8>;
def : PatVgrVgrVgr<int_riscv_vmadd_vv_8m8,VMADD_VV_um,v128i8>;

def : PatVgrVgrVgr<int_riscv_vmadd_vv_16m1,VMADD_VV_um,v8i16>;
def : PatVgrVgrVgr<int_riscv_vmadd_vv_16m2,VMADD_VV_um,v16i16>;
def : PatVgrVgrVgr<int_riscv_vmadd_vv_16m4,VMADD_VV_um,v32i16>;
def : PatVgrVgrVgr<int_riscv_vmadd_vv_16m8,VMADD_VV_um,v64i16>;

def : PatVgrVgrVgr<int_riscv_vmadd_vv_32m1,VMADD_VV_um,v4i32>;
def : PatVgrVgrVgr<int_riscv_vmadd_vv_32m2,VMADD_VV_um,v8i32>;
def : PatVgrVgrVgr<int_riscv_vmadd_vv_32m4,VMADD_VV_um,v16i32>;
def : PatVgrVgrVgr<int_riscv_vmadd_vv_32m8,VMADD_VV_um,v32i32>;

def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_8m1_m,VMADD_VV_m,v16i8>;
def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_8m2_m,VMADD_VV_m,v32i8>;
def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_8m4_m,VMADD_VV_m,v64i8>;
def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_8m8_m,VMADD_VV_m,v128i8>;

def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_16m1_m,VMADD_VV_m,v8i16>;
def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_16m2_m,VMADD_VV_m,v16i16>;
def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_16m4_m,VMADD_VV_m,v32i16>;
def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_16m8_m,VMADD_VV_m,v64i16>;

def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_32m1_m,VMADD_VV_m,v4i32>;
def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_32m2_m,VMADD_VV_m,v8i32>;
def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_32m4_m,VMADD_VV_m,v16i32>;
def : PatVmVgrVgrVgr<int_riscv_vmadd_vv_32m8_m,VMADD_VV_m,v32i32>;


defm VMADD_VX : VALU_OPMVX_MulAdd<0b101001,"vmadd.vx">;

def : PatVgrGprVgr<int_riscv_vmadd_vx_8m1,VMADD_VX_um,v16i8>;
def : PatVgrGprVgr<int_riscv_vmadd_vx_8m2,VMADD_VX_um,v32i8>;
def : PatVgrGprVgr<int_riscv_vmadd_vx_8m4,VMADD_VX_um,v64i8>;
def : PatVgrGprVgr<int_riscv_vmadd_vx_8m8,VMADD_VX_um,v128i8>;

def : PatVgrGprVgr<int_riscv_vmadd_vx_16m1,VMADD_VX_um,v8i16>;
def : PatVgrGprVgr<int_riscv_vmadd_vx_16m2,VMADD_VX_um,v16i16>;
def : PatVgrGprVgr<int_riscv_vmadd_vx_16m4,VMADD_VX_um,v32i16>;
def : PatVgrGprVgr<int_riscv_vmadd_vx_16m8,VMADD_VX_um,v64i16>;

def : PatVgrGprVgr<int_riscv_vmadd_vx_32m1,VMADD_VX_um,v4i32>;
def : PatVgrGprVgr<int_riscv_vmadd_vx_32m2,VMADD_VX_um,v8i32>;
def : PatVgrGprVgr<int_riscv_vmadd_vx_32m4,VMADD_VX_um,v16i32>;
def : PatVgrGprVgr<int_riscv_vmadd_vx_32m8,VMADD_VX_um,v32i32>;

def : PatVmVgrGprVgr<int_riscv_vmadd_vx_8m1_m,VMADD_VX_m,v16i8>;
def : PatVmVgrGprVgr<int_riscv_vmadd_vx_8m2_m,VMADD_VX_m,v32i8>;
def : PatVmVgrGprVgr<int_riscv_vmadd_vx_8m4_m,VMADD_VX_m,v64i8>;
def : PatVmVgrGprVgr<int_riscv_vmadd_vx_8m8_m,VMADD_VX_m,v128i8>;

def : PatVmVgrGprVgr<int_riscv_vmadd_vx_16m1_m,VMADD_VX_m,v8i16>;
def : PatVmVgrGprVgr<int_riscv_vmadd_vx_16m2_m,VMADD_VX_m,v16i16>;
def : PatVmVgrGprVgr<int_riscv_vmadd_vx_16m4_m,VMADD_VX_m,v32i16>;
def : PatVmVgrGprVgr<int_riscv_vmadd_vx_16m8_m,VMADD_VX_m,v64i16>;

def : PatVmVgrGprVgr<int_riscv_vmadd_vx_32m1_m,VMADD_VX_m,v4i32>;
def : PatVmVgrGprVgr<int_riscv_vmadd_vx_32m2_m,VMADD_VX_m,v8i32>;
def : PatVmVgrGprVgr<int_riscv_vmadd_vx_32m4_m,VMADD_VX_m,v16i32>;
def : PatVmVgrGprVgr<int_riscv_vmadd_vx_32m8_m,VMADD_VX_m,v32i32>;

defm VNMSUB_VV : VALU_OPMVV_MulAdd<0b101011,"vnmsub.vv">;

def : PatVgrVgrVgr<int_riscv_vnmsub_vv_8m1,VNMSUB_VV_um,v16i8>;
def : PatVgrVgrVgr<int_riscv_vnmsub_vv_8m2,VNMSUB_VV_um,v32i8>;
def : PatVgrVgrVgr<int_riscv_vnmsub_vv_8m4,VNMSUB_VV_um,v64i8>;
def : PatVgrVgrVgr<int_riscv_vnmsub_vv_8m8,VNMSUB_VV_um,v128i8>;

def : PatVgrVgrVgr<int_riscv_vnmsub_vv_16m1,VNMSUB_VV_um,v8i16>;
def : PatVgrVgrVgr<int_riscv_vnmsub_vv_16m2,VNMSUB_VV_um,v16i16>;
def : PatVgrVgrVgr<int_riscv_vnmsub_vv_16m4,VNMSUB_VV_um,v32i16>;
def : PatVgrVgrVgr<int_riscv_vnmsub_vv_16m8,VNMSUB_VV_um,v64i16>;

def : PatVgrVgrVgr<int_riscv_vnmsub_vv_32m1,VNMSUB_VV_um,v4i32>;
def : PatVgrVgrVgr<int_riscv_vnmsub_vv_32m2,VNMSUB_VV_um,v8i32>;
def : PatVgrVgrVgr<int_riscv_vnmsub_vv_32m4,VNMSUB_VV_um,v16i32>;
def : PatVgrVgrVgr<int_riscv_vnmsub_vv_32m8,VNMSUB_VV_um,v32i32>;

def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_8m1_m,VNMSUB_VV_m,v16i8>;
def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_8m2_m,VNMSUB_VV_m,v32i8>;
def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_8m4_m,VNMSUB_VV_m,v64i8>;
def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_8m8_m,VNMSUB_VV_m,v128i8>;

def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_16m1_m,VNMSUB_VV_m,v8i16>;
def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_16m2_m,VNMSUB_VV_m,v16i16>;
def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_16m4_m,VNMSUB_VV_m,v32i16>;
def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_16m8_m,VNMSUB_VV_m,v64i16>;

def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_32m1_m,VNMSUB_VV_m,v4i32>;
def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_32m2_m,VNMSUB_VV_m,v8i32>;
def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_32m4_m,VNMSUB_VV_m,v16i32>;
def : PatVmVgrVgrVgr<int_riscv_vnmsub_vv_32m8_m,VNMSUB_VV_m,v32i32>;


defm VNMSUB_VX : VALU_OPMVX_MulAdd<0b101011,"vnmsub.vx">;

def : PatVgrGprVgr<int_riscv_vnmsub_vx_8m1,VNMSUB_VX_um,v16i8>;
def : PatVgrGprVgr<int_riscv_vnmsub_vx_8m2,VNMSUB_VX_um,v32i8>;
def : PatVgrGprVgr<int_riscv_vnmsub_vx_8m4,VNMSUB_VX_um,v64i8>;
def : PatVgrGprVgr<int_riscv_vnmsub_vx_8m8,VNMSUB_VX_um,v128i8>;

def : PatVgrGprVgr<int_riscv_vnmsub_vx_16m1,VNMSUB_VX_um,v8i16>;
def : PatVgrGprVgr<int_riscv_vnmsub_vx_16m2,VNMSUB_VX_um,v16i16>;
def : PatVgrGprVgr<int_riscv_vnmsub_vx_16m4,VNMSUB_VX_um,v32i16>;
def : PatVgrGprVgr<int_riscv_vnmsub_vx_16m8,VNMSUB_VX_um,v64i16>;

def : PatVgrGprVgr<int_riscv_vnmsub_vx_32m1,VNMSUB_VX_um,v4i32>;
def : PatVgrGprVgr<int_riscv_vnmsub_vx_32m2,VNMSUB_VX_um,v8i32>;
def : PatVgrGprVgr<int_riscv_vnmsub_vx_32m4,VNMSUB_VX_um,v16i32>;
def : PatVgrGprVgr<int_riscv_vnmsub_vx_32m8,VNMSUB_VX_um,v32i32>;

def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_8m1_m,VNMSUB_VX_m,v16i8>;
def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_8m2_m,VNMSUB_VX_m,v32i8>;
def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_8m4_m,VNMSUB_VX_m,v64i8>;
def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_8m8_m,VNMSUB_VX_m,v128i8>;

def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_16m1_m,VNMSUB_VX_m,v8i16>;
def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_16m2_m,VNMSUB_VX_m,v16i16>;
def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_16m4_m,VNMSUB_VX_m,v32i16>;
def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_16m8_m,VNMSUB_VX_m,v64i16>;

def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_32m1_m,VNMSUB_VX_m,v4i32>;
def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_32m2_m,VNMSUB_VX_m,v8i32>;
def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_32m4_m,VNMSUB_VX_m,v16i32>;
def : PatVmVgrGprVgr<int_riscv_vnmsub_vx_32m8_m,VNMSUB_VX_m,v32i32>;

/************Vector Widening Integer Multiply-Add Functions****************/

defm VWMACCU_VV : VALU_OPMVV_MulAdd<0b111100,"vwmaccu.vv">;

def : PatWidVgrVgrVgr<int_riscv_vwmaccu_vv_16m2,VWMACCU_VV_um,v16i16,v16i8>;
def : PatWidVgrVgrVgr<int_riscv_vwmaccu_vv_16m4,VWMACCU_VV_um,v32i16,v32i8>;
def : PatWidVgrVgrVgr<int_riscv_vwmaccu_vv_16m8,VWMACCU_VV_um,v64i16,v64i8>;

def : PatWidVgrVgrVgr<int_riscv_vwmaccu_vv_32m2,VWMACCU_VV_um,v8i32,v8i16>;
def : PatWidVgrVgrVgr<int_riscv_vwmaccu_vv_32m4,VWMACCU_VV_um,v16i32,v16i16>;
def : PatWidVgrVgrVgr<int_riscv_vwmaccu_vv_32m8,VWMACCU_VV_um,v32i32,v32i16>;

def : PatVmWidVgrVgrVgr<int_riscv_vwmaccu_vv_16m2_m,VWMACCU_VV_m,v16i16,v16i8>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmaccu_vv_16m4_m,VWMACCU_VV_m,v32i16,v32i8>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmaccu_vv_16m8_m,VWMACCU_VV_m,v64i16,v64i8>;

def : PatVmWidVgrVgrVgr<int_riscv_vwmaccu_vv_32m2_m,VWMACCU_VV_m,v8i32,v8i16>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmaccu_vv_32m4_m,VWMACCU_VV_m,v16i32,v16i16>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmaccu_vv_32m8_m,VWMACCU_VV_m,v32i32,v32i16>;

defm VWMACCU_VX : VALU_OPMVX_MulAdd<0b111100,"vwmaccu.vx">;

def : PatWidVgrGprVgr<int_riscv_vwmaccu_vx_16m2,VWMACCU_VX_um,v16i16,v16i8>;
def : PatWidVgrGprVgr<int_riscv_vwmaccu_vx_16m4,VWMACCU_VX_um,v32i16,v32i8>;
def : PatWidVgrGprVgr<int_riscv_vwmaccu_vx_16m8,VWMACCU_VX_um,v64i16,v64i8>;

def : PatWidVgrGprVgr<int_riscv_vwmaccu_vx_32m2,VWMACCU_VX_um,v8i32,v8i16>;
def : PatWidVgrGprVgr<int_riscv_vwmaccu_vx_32m4,VWMACCU_VX_um,v16i32,v16i16>;
def : PatWidVgrGprVgr<int_riscv_vwmaccu_vx_32m8,VWMACCU_VX_um,v32i32,v32i16>;

def : PatVmWidVgrGprVgr<int_riscv_vwmaccu_vx_16m2_m,VWMACCU_VX_m,v16i16,v16i8>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccu_vx_16m4_m,VWMACCU_VX_m,v32i16,v32i8>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccu_vx_16m8_m,VWMACCU_VX_m,v64i16,v64i8>;

def : PatVmWidVgrGprVgr<int_riscv_vwmaccu_vx_32m2_m,VWMACCU_VX_m,v8i32,v8i16>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccu_vx_32m4_m,VWMACCU_VX_m,v16i32,v16i16>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccu_vx_32m8_m,VWMACCU_VX_m,v32i32,v32i16>;

defm VWMACC_VV : VALU_OPMVV_MulAdd<0b111101,"vwmacc.vv">;

def : PatWidVgrVgrVgr<int_riscv_vwmacc_vv_16m2,VWMACC_VV_um,v16i16,v16i8>;
def : PatWidVgrVgrVgr<int_riscv_vwmacc_vv_16m4,VWMACC_VV_um,v32i16,v32i8>;
def : PatWidVgrVgrVgr<int_riscv_vwmacc_vv_16m8,VWMACC_VV_um,v64i16,v64i8>;

def : PatWidVgrVgrVgr<int_riscv_vwmacc_vv_32m2,VWMACC_VV_um,v8i32,v8i16>;
def : PatWidVgrVgrVgr<int_riscv_vwmacc_vv_32m4,VWMACC_VV_um,v16i32,v16i16>;
def : PatWidVgrVgrVgr<int_riscv_vwmacc_vv_32m8,VWMACC_VV_um,v32i32,v32i16>;

def : PatVmWidVgrVgrVgr<int_riscv_vwmacc_vv_16m2_m,VWMACC_VV_m,v16i16,v16i8>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmacc_vv_16m4_m,VWMACC_VV_m,v32i16,v32i8>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmacc_vv_16m8_m,VWMACC_VV_m,v64i16,v64i8>;

def : PatVmWidVgrVgrVgr<int_riscv_vwmacc_vv_32m2_m,VWMACC_VV_m,v8i32,v8i16>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmacc_vv_32m4_m,VWMACC_VV_m,v16i32,v16i16>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmacc_vv_32m8_m,VWMACC_VV_m,v32i32,v32i16>;

defm VWMACC_VX : VALU_OPMVX_MulAdd<0b111101,"vwmacc.vx">;

def : PatWidVgrGprVgr<int_riscv_vwmacc_vx_16m2,VWMACC_VX_um,v16i16,v16i8>;
def : PatWidVgrGprVgr<int_riscv_vwmacc_vx_16m4,VWMACC_VX_um,v32i16,v32i8>;
def : PatWidVgrGprVgr<int_riscv_vwmacc_vx_16m8,VWMACC_VX_um,v64i16,v64i8>;

def : PatWidVgrGprVgr<int_riscv_vwmacc_vx_32m2,VWMACC_VX_um,v8i32,v8i16>;
def : PatWidVgrGprVgr<int_riscv_vwmacc_vx_32m4,VWMACC_VX_um,v16i32,v16i16>;
def : PatWidVgrGprVgr<int_riscv_vwmacc_vx_32m8,VWMACC_VX_um,v32i32,v32i16>;

def : PatVmWidVgrGprVgr<int_riscv_vwmacc_vx_16m2_m,VWMACC_VX_m,v16i16,v16i8>;
def : PatVmWidVgrGprVgr<int_riscv_vwmacc_vx_16m4_m,VWMACC_VX_m,v32i16,v32i8>;
def : PatVmWidVgrGprVgr<int_riscv_vwmacc_vx_16m8_m,VWMACC_VX_m,v64i16,v64i8>;

def : PatVmWidVgrGprVgr<int_riscv_vwmacc_vx_32m2_m,VWMACC_VX_m,v8i32,v8i16>;
def : PatVmWidVgrGprVgr<int_riscv_vwmacc_vx_32m4_m,VWMACC_VX_m,v16i32,v16i16>;
def : PatVmWidVgrGprVgr<int_riscv_vwmacc_vx_32m8_m,VWMACC_VX_m,v32i32,v32i16>;

defm VWMACCSU_VV : VALU_OPMVV_MulAdd<0b111111,"vwmaccsu.vv">;

def : PatWidVgrVgrVgr<int_riscv_vwmaccsu_vv_16m2,VWMACCSU_VV_um,v16i16,v16i8>;
def : PatWidVgrVgrVgr<int_riscv_vwmaccsu_vv_16m4,VWMACCSU_VV_um,v32i16,v32i8>;
def : PatWidVgrVgrVgr<int_riscv_vwmaccsu_vv_16m8,VWMACCSU_VV_um,v64i16,v64i8>;

def : PatWidVgrVgrVgr<int_riscv_vwmaccsu_vv_32m2,VWMACCSU_VV_um,v8i32,v8i16>;
def : PatWidVgrVgrVgr<int_riscv_vwmaccsu_vv_32m4,VWMACCSU_VV_um,v16i32,v16i16>;
def : PatWidVgrVgrVgr<int_riscv_vwmaccsu_vv_32m8,VWMACCSU_VV_um,v32i32,v32i16>;

def : PatVmWidVgrVgrVgr<int_riscv_vwmaccsu_vv_16m2_m,VWMACCSU_VV_m,v16i16,v16i8>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmaccsu_vv_16m4_m,VWMACCSU_VV_m,v32i16,v32i8>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmaccsu_vv_16m8_m,VWMACCSU_VV_m,v64i16,v64i8>;

def : PatVmWidVgrVgrVgr<int_riscv_vwmaccsu_vv_32m2_m,VWMACCSU_VV_m,v8i32,v8i16>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmaccsu_vv_32m4_m,VWMACCSU_VV_m,v16i32,v16i16>;
def : PatVmWidVgrVgrVgr<int_riscv_vwmaccsu_vv_32m8_m,VWMACCSU_VV_m,v32i32,v32i16>;

defm VWMACCSU_VX : VALU_OPMVX_MulAdd<0b111111,"vwmaccsu.vx">;

def : PatWidVgrGprVgr<int_riscv_vwmaccsu_vx_16m2,VWMACCSU_VX_um,v16i16,v16i8>;
def : PatWidVgrGprVgr<int_riscv_vwmaccsu_vx_16m4,VWMACCSU_VX_um,v32i16,v32i8>;
def : PatWidVgrGprVgr<int_riscv_vwmaccsu_vx_16m8,VWMACCSU_VX_um,v64i16,v64i8>;

def : PatWidVgrGprVgr<int_riscv_vwmaccsu_vx_32m2,VWMACCSU_VX_um,v8i32,v8i16>;
def : PatWidVgrGprVgr<int_riscv_vwmaccsu_vx_32m4,VWMACCSU_VX_um,v16i32,v16i16>;
def : PatWidVgrGprVgr<int_riscv_vwmaccsu_vx_32m8,VWMACCSU_VX_um,v32i32,v32i16>;

def : PatVmWidVgrGprVgr<int_riscv_vwmaccsu_vx_16m2_m,VWMACCSU_VX_m,v16i16,v16i8>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccsu_vx_16m4_m,VWMACCSU_VX_m,v32i16,v32i8>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccsu_vx_16m8_m,VWMACCSU_VX_m,v64i16,v64i8>;

def : PatVmWidVgrGprVgr<int_riscv_vwmaccsu_vx_32m2_m,VWMACCSU_VX_m,v8i32,v8i16>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccsu_vx_32m4_m,VWMACCSU_VX_m,v16i32,v16i16>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccsu_vx_32m8_m,VWMACCSU_VX_m,v32i32,v32i16>;

defm VWMACCUS_VX : VALU_OPMVX_MulAdd<0b111110,"vwmaccus.vx">;

def : PatWidVgrGprVgr<int_riscv_vwmaccus_vx_16m2,VWMACCUS_VX_um,v16i16,v16i8>;
def : PatWidVgrGprVgr<int_riscv_vwmaccus_vx_16m4,VWMACCUS_VX_um,v32i16,v32i8>;
def : PatWidVgrGprVgr<int_riscv_vwmaccus_vx_16m8,VWMACCUS_VX_um,v64i16,v64i8>;

def : PatWidVgrGprVgr<int_riscv_vwmaccus_vx_32m2,VWMACCUS_VX_um,v8i32,v8i16>;
def : PatWidVgrGprVgr<int_riscv_vwmaccus_vx_32m4,VWMACCUS_VX_um,v16i32,v16i16>;
def : PatWidVgrGprVgr<int_riscv_vwmaccus_vx_32m8,VWMACCUS_VX_um,v32i32,v32i16>;

def : PatVmWidVgrGprVgr<int_riscv_vwmaccus_vx_16m2_m,VWMACCUS_VX_m,v16i16,v16i8>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccus_vx_16m4_m,VWMACCUS_VX_m,v32i16,v32i8>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccus_vx_16m8_m,VWMACCUS_VX_m,v64i16,v64i8>;

def : PatVmWidVgrGprVgr<int_riscv_vwmaccus_vx_32m2_m,VWMACCUS_VX_m,v8i32,v8i16>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccus_vx_32m4_m,VWMACCUS_VX_m,v16i32,v16i16>;
def : PatVmWidVgrGprVgr<int_riscv_vwmaccus_vx_32m8_m,VWMACCUS_VX_m,v32i32,v32i16>;

/***********Vector Quad-Widening Integer Multiply-Add Functions*************/

defm VQMACCU_VV : VALU_OPIVV_MulAdd<0b111100,"vqmaccu.vv">;

def : PatWidVgrVgrVgr<int_riscv_vqmaccu_vv_32m4,VQMACCU_VV_um,v16i32,v16i8>;
def : PatWidVgrVgrVgr<int_riscv_vqmaccu_vv_32m8,VQMACCU_VV_um,v32i32,v32i8>;

def : PatVmWidVgrVgrVgr<int_riscv_vqmaccu_vv_32m4_m,VQMACCU_VV_m,v16i32,v16i8>;
def : PatVmWidVgrVgrVgr<int_riscv_vqmaccu_vv_32m8_m,VQMACCU_VV_m,v32i32,v32i8>;

defm VQMACCU_VX : VALU_OPIVX_MulAdd<0b111100,"vqmaccu.vx">;

def : PatWidVgrGprVgr<int_riscv_vqmaccu_vx_32m4,VQMACCU_VX_um,v16i32,v16i8>;
def : PatWidVgrGprVgr<int_riscv_vqmaccu_vx_32m8,VQMACCU_VX_um,v32i32,v32i8>;

def : PatVmWidVgrGprVgr<int_riscv_vqmaccu_vx_32m4_m,VQMACCU_VX_m,v16i32,v16i8>;
def : PatVmWidVgrGprVgr<int_riscv_vqmaccu_vx_32m8_m,VQMACCU_VX_m,v32i32,v32i8>;

defm VQMACC_VV : VALU_OPIVV_MulAdd<0b111101,"vqmacc.vv">;

def : PatWidVgrVgrVgr<int_riscv_vqmacc_vv_32m4,VQMACC_VV_um,v16i32,v16i8>;
def : PatWidVgrVgrVgr<int_riscv_vqmacc_vv_32m8,VQMACC_VV_um,v32i32,v32i8>;

def : PatVmWidVgrVgrVgr<int_riscv_vqmacc_vv_32m4_m,VQMACC_VV_m,v16i32,v16i8>;
def : PatVmWidVgrVgrVgr<int_riscv_vqmacc_vv_32m8_m,VQMACC_VV_m,v32i32,v32i8>;

defm VQMACC_VX : VALU_OPIVX_MulAdd<0b111101,"vqmacc.vx">;

def : PatWidVgrGprVgr<int_riscv_vqmacc_vx_32m4,VQMACC_VX_um,v16i32,v16i8>;
def : PatWidVgrGprVgr<int_riscv_vqmacc_vx_32m8,VQMACC_VX_um,v32i32,v32i8>;

def : PatVmWidVgrGprVgr<int_riscv_vqmacc_vx_32m4_m,VQMACC_VX_m,v16i32,v16i8>;
def : PatVmWidVgrGprVgr<int_riscv_vqmacc_vx_32m8_m,VQMACC_VX_m,v32i32,v32i8>;

defm VQMACCSU_VV : VALU_OPIVV_MulAdd<0b111111,"vqmaccsu.vv">;

def : PatWidVgrVgrVgr<int_riscv_vqmaccsu_vv_32m4,VQMACCSU_VV_um,v16i32,v16i8>;
def : PatWidVgrVgrVgr<int_riscv_vqmaccsu_vv_32m8,VQMACCSU_VV_um,v32i32,v32i8>;

def : PatVmWidVgrVgrVgr<int_riscv_vqmaccsu_vv_32m4_m,VQMACCSU_VV_m,v16i32,v16i8>;
def : PatVmWidVgrVgrVgr<int_riscv_vqmaccsu_vv_32m8_m,VQMACCSU_VV_m,v32i32,v32i8>;

defm VQMACCSU_VX : VALU_OPIVX_MulAdd<0b111111,"vqmaccsu.vx">;

def : PatWidVgrGprVgr<int_riscv_vqmaccsu_vx_32m4,VQMACCSU_VX_um,v16i32,v16i8>;
def : PatWidVgrGprVgr<int_riscv_vqmaccsu_vx_32m8,VQMACCSU_VX_um,v32i32,v32i8>;

def : PatVmWidVgrGprVgr<int_riscv_vqmaccsu_vx_32m4_m,VQMACCSU_VX_m,v16i32,v16i8>;
def : PatVmWidVgrGprVgr<int_riscv_vqmaccsu_vx_32m8_m,VQMACCSU_VX_m,v32i32,v32i8>;

defm VQMACCUS_VX : VALU_OPIVX_MulAdd<0b111110,"vqmaccus.vx">;

def : PatWidVgrGprVgr<int_riscv_vqmaccus_vx_32m4,VQMACCUS_VX_um,v16i32,v16i8>;
def : PatWidVgrGprVgr<int_riscv_vqmaccus_vx_32m8,VQMACCUS_VX_um,v32i32,v32i8>;

def : PatVmWidVgrGprVgr<int_riscv_vqmaccus_vx_32m4_m,VQMACCUS_VX_m,v16i32,v16i8>;
def : PatVmWidVgrGprVgr<int_riscv_vqmaccus_vx_32m8_m,VQMACCUS_VX_m,v32i32,v32i8>;

/***********Vector Integer Merge Functions************/

//defm VMERGE_VVM : VALU_OPIVV<0b010111,"vmerge.vvm">;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in
def VMERGE_VVM : RVInstVA<0b010111, 0b000, OPC_VOP,
               (outs VReg:$vd), (ins VMASK:$vm, VReg:$vs2, VReg:$vs1),
               "vmerge.vvm", "$vd, $vs2, $vs1, $vm">,Sched<[]>{
  bits<5> vs1;
  bits<1> vm;
  let Inst{25} = vm;
  let Inst{19-15} = vs1;
}

def : PatVmVgrVgr<int_riscv_vmerge_vvm_8m1_m,VMERGE_VVM,v16i8>;
def : PatVmVgrVgr<int_riscv_vmerge_vvm_8m2_m,VMERGE_VVM,v32i8>;
def : PatVmVgrVgr<int_riscv_vmerge_vvm_8m4_m,VMERGE_VVM,v64i8>;
def : PatVmVgrVgr<int_riscv_vmerge_vvm_8m8_m,VMERGE_VVM,v128i8>;

def : PatVmVgrVgr<int_riscv_vmerge_vvm_16m1_m,VMERGE_VVM,v8i16>;
def : PatVmVgrVgr<int_riscv_vmerge_vvm_16m2_m,VMERGE_VVM,v16i16>;
def : PatVmVgrVgr<int_riscv_vmerge_vvm_16m4_m,VMERGE_VVM,v32i16>;
def : PatVmVgrVgr<int_riscv_vmerge_vvm_16m8_m,VMERGE_VVM,v64i16>;

def : PatVmVgrVgr<int_riscv_vmerge_vvm_32m1_m,VMERGE_VVM,v4i32>;
def : PatVmVgrVgr<int_riscv_vmerge_vvm_32m2_m,VMERGE_VVM,v8i32>;
def : PatVmVgrVgr<int_riscv_vmerge_vvm_32m4_m,VMERGE_VVM,v16i32>;
def : PatVmVgrVgr<int_riscv_vmerge_vvm_32m8_m,VMERGE_VVM,v32i32>;

//defm VMERGE_VXM : VALU_OPIVX<0b010111,"vmerge.vxm">;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in
def VMERGE_VXM : RVInstVA<0b010111, 0b100, OPC_VOP,
               (outs VReg:$vd), (ins VMASK:$vm, VReg:$vs2, GPR:$rs1),
               "vmerge.vxm", "$vd, $vs2, $rs1, $vm">,Sched<[]>{
  bits<5> rs1;
  bits<1> vm;
  let Inst{25} = vm;
  let Inst{19-15} = rs1;
}

def : PatVmVgrGpr<int_riscv_vmerge_vxm_8m1_m,VMERGE_VXM,v16i8>;
def : PatVmVgrGpr<int_riscv_vmerge_vxm_8m2_m,VMERGE_VXM,v32i8>;
def : PatVmVgrGpr<int_riscv_vmerge_vxm_8m4_m,VMERGE_VXM,v64i8>;
def : PatVmVgrGpr<int_riscv_vmerge_vxm_8m8_m,VMERGE_VXM,v128i8>;

def : PatVmVgrGpr<int_riscv_vmerge_vxm_16m1_m,VMERGE_VXM,v8i16>;
def : PatVmVgrGpr<int_riscv_vmerge_vxm_16m2_m,VMERGE_VXM,v16i16>;
def : PatVmVgrGpr<int_riscv_vmerge_vxm_16m4_m,VMERGE_VXM,v32i16>;
def : PatVmVgrGpr<int_riscv_vmerge_vxm_16m8_m,VMERGE_VXM,v64i16>;

def : PatVmVgrGpr<int_riscv_vmerge_vxm_32m1_m,VMERGE_VXM,v4i32>;
def : PatVmVgrGpr<int_riscv_vmerge_vxm_32m2_m,VMERGE_VXM,v8i32>;
def : PatVmVgrGpr<int_riscv_vmerge_vxm_32m4_m,VMERGE_VXM,v16i32>;
def : PatVmVgrGpr<int_riscv_vmerge_vxm_32m8_m,VMERGE_VXM,v32i32>;

//defm VMERGE_VIM : VALU_OPIVI_signed<0b010111,0b011,"vmerge.vim">;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in
def VMERGE_VIM : RVInstVA<0b010111, 0b011, OPC_VOP,
               (outs VReg:$vd), (ins VMASK:$vm, VReg:$vs2, simm5:$simm),
               "vmerge.vim", "$vd, $vs2, $simm, $vm">,Sched<[]>{
  bits<5> simm;
  bits<1> vm;
  let Inst{25} = vm;
  let Inst{19-15} = simm;
}

def : PatVmVgrSimm5<int_riscv_vmerge_vim_8m1_m,VMERGE_VIM,v16i8>;
def : PatVmVgrSimm5<int_riscv_vmerge_vim_8m2_m,VMERGE_VIM,v32i8>;
def : PatVmVgrSimm5<int_riscv_vmerge_vim_8m4_m,VMERGE_VIM,v64i8>;
def : PatVmVgrSimm5<int_riscv_vmerge_vim_8m8_m,VMERGE_VIM,v128i8>;

def : PatVmVgrSimm5<int_riscv_vmerge_vim_16m1_m,VMERGE_VIM,v8i16>;
def : PatVmVgrSimm5<int_riscv_vmerge_vim_16m2_m,VMERGE_VIM,v16i16>;
def : PatVmVgrSimm5<int_riscv_vmerge_vim_16m4_m,VMERGE_VIM,v32i16>;
def : PatVmVgrSimm5<int_riscv_vmerge_vim_16m8_m,VMERGE_VIM,v64i16>;

def : PatVmVgrSimm5<int_riscv_vmerge_vim_32m1_m,VMERGE_VIM,v4i32>;
def : PatVmVgrSimm5<int_riscv_vmerge_vim_32m2_m,VMERGE_VIM,v8i32>;
def : PatVmVgrSimm5<int_riscv_vmerge_vim_32m4_m,VMERGE_VIM,v16i32>;
def : PatVmVgrSimm5<int_riscv_vmerge_vim_32m8_m,VMERGE_VIM,v32i32>;

/***********Vector Integer Move Functions************/
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
def VMV_V_V : RVInstVA<0b010111, 0b000, OPC_VOP,
               (outs VReg:$vd), (ins VReg:$vs1),
               "vmv.v.v", "$vd, $vs1">,Sched<[]> {
  bits<5> vs1;
	let Inst{25} = 0b1;
  let vs2 = 0b00000;
  let Inst{19-15} = vs1;
	}
}

def : PatVgr<int_riscv_vmv_v_v_8m1,VMV_V_V,v16i8>;
def : PatVgr<int_riscv_vmv_v_v_8m2,VMV_V_V,v32i8>;
def : PatVgr<int_riscv_vmv_v_v_8m4,VMV_V_V,v64i8>;
def : PatVgr<int_riscv_vmv_v_v_8m8,VMV_V_V,v128i8>;

def : PatVgr<int_riscv_vmv_v_v_16m1,VMV_V_V,v8i16>;
def : PatVgr<int_riscv_vmv_v_v_16m2,VMV_V_V,v16i16>;
def : PatVgr<int_riscv_vmv_v_v_16m4,VMV_V_V,v32i16>;
def : PatVgr<int_riscv_vmv_v_v_16m8,VMV_V_V,v64i16>;

def : PatVgr<int_riscv_vmv_v_v_32m1,VMV_V_V,v4i32>;
def : PatVgr<int_riscv_vmv_v_v_32m2,VMV_V_V,v8i32>;
def : PatVgr<int_riscv_vmv_v_v_32m4,VMV_V_V,v16i32>;
def : PatVgr<int_riscv_vmv_v_v_32m8,VMV_V_V,v32i32>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
def VMV_V_X : RVInstVA<0b010111, 0b100, OPC_VOP,
               (outs VReg:$vd), (ins GPR:$rs1),
               "vmv.v.x", "$vd, $rs1">,Sched<[]> {
  bits<5> rs1;
	let Inst{25} = 0b1;
  let vs2 = 0b00000;
  let Inst{19-15} = rs1;
	}
}

def : PatGpr<int_riscv_vmv_v_x_8m1,VMV_V_X>;
def : PatGpr<int_riscv_vmv_v_x_8m2,VMV_V_X>;
def : PatGpr<int_riscv_vmv_v_x_8m4,VMV_V_X>;
def : PatGpr<int_riscv_vmv_v_x_8m8,VMV_V_X>;

def : PatGpr<int_riscv_vmv_v_x_16m1,VMV_V_X>;
def : PatGpr<int_riscv_vmv_v_x_16m2,VMV_V_X>;
def : PatGpr<int_riscv_vmv_v_x_16m4,VMV_V_X>;
def : PatGpr<int_riscv_vmv_v_x_16m8,VMV_V_X>;

def : PatGpr<int_riscv_vmv_v_x_32m1,VMV_V_X>;
def : PatGpr<int_riscv_vmv_v_x_32m2,VMV_V_X>;
def : PatGpr<int_riscv_vmv_v_x_32m4,VMV_V_X>;
def : PatGpr<int_riscv_vmv_v_x_32m8,VMV_V_X>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
def VMV_V_I : RVInstVA<0b010111, 0b011, OPC_VOP,
               (outs VReg:$vd), (ins simm5:$simm),
               "vmv.v.i", "$vd, $simm">,Sched<[]> {
  bits<5> simm;
	let Inst{25} = 0b1;
  let vs2 = 0b00000;
  let Inst{19-15} = simm;
	}
}

def : PatSimm5<int_riscv_vmv_v_i_8m1,VMV_V_I>;
def : PatSimm5<int_riscv_vmv_v_i_8m2,VMV_V_I>;
def : PatSimm5<int_riscv_vmv_v_i_8m4,VMV_V_I>;
def : PatSimm5<int_riscv_vmv_v_i_8m8,VMV_V_I>;

def : PatSimm5<int_riscv_vmv_v_i_16m1,VMV_V_I>;
def : PatSimm5<int_riscv_vmv_v_i_16m2,VMV_V_I>;
def : PatSimm5<int_riscv_vmv_v_i_16m4,VMV_V_I>;
def : PatSimm5<int_riscv_vmv_v_i_16m8,VMV_V_I>;

def : PatSimm5<int_riscv_vmv_v_i_32m1,VMV_V_I>;
def : PatSimm5<int_riscv_vmv_v_i_32m2,VMV_V_I>;
def : PatSimm5<int_riscv_vmv_v_i_32m4,VMV_V_I>;
def : PatSimm5<int_riscv_vmv_v_i_32m8,VMV_V_I>;

/**************Vector Single-Width Saturating Add and Subtract Functions****************/

defm VSADDU_VV : VALU_OPIVV<0b100000,"vsaddu.vv">;

def : PatVgrVgr<int_riscv_vsaddu_vv_8m1,VSADDU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vsaddu_vv_8m2,VSADDU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vsaddu_vv_8m4,VSADDU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vsaddu_vv_8m8,VSADDU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vsaddu_vv_16m1,VSADDU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vsaddu_vv_16m2,VSADDU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vsaddu_vv_16m4,VSADDU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vsaddu_vv_16m8,VSADDU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vsaddu_vv_32m1,VSADDU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vsaddu_vv_32m2,VSADDU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vsaddu_vv_32m4,VSADDU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vsaddu_vv_32m8,VSADDU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vsaddu_vv_8m1_m,VSADDU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vsaddu_vv_8m2_m,VSADDU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vsaddu_vv_8m4_m,VSADDU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vsaddu_vv_8m8_m,VSADDU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vsaddu_vv_16m1_m,VSADDU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vsaddu_vv_16m2_m,VSADDU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vsaddu_vv_16m4_m,VSADDU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vsaddu_vv_16m8_m,VSADDU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vsaddu_vv_32m1_m,VSADDU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vsaddu_vv_32m2_m,VSADDU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vsaddu_vv_32m4_m,VSADDU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vsaddu_vv_32m8_m,VSADDU_VV_m,v32i32>;

defm VSADDU_VX : VALU_OPIVX<0b100000,"vsaddu.vx">;

def : PatVgrGpr<int_riscv_vsaddu_vx_8m1,VSADDU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vsaddu_vx_8m2,VSADDU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vsaddu_vx_8m4,VSADDU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vsaddu_vx_8m8,VSADDU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vsaddu_vx_16m1,VSADDU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vsaddu_vx_16m2,VSADDU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vsaddu_vx_16m4,VSADDU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vsaddu_vx_16m8,VSADDU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vsaddu_vx_32m1,VSADDU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vsaddu_vx_32m2,VSADDU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vsaddu_vx_32m4,VSADDU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vsaddu_vx_32m8,VSADDU_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vsaddu_vx_8m1_m,VSADDU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vsaddu_vx_8m2_m,VSADDU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vsaddu_vx_8m4_m,VSADDU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vsaddu_vx_8m8_m,VSADDU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vsaddu_vx_16m1_m,VSADDU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vsaddu_vx_16m2_m,VSADDU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vsaddu_vx_16m4_m,VSADDU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vsaddu_vx_16m8_m,VSADDU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vsaddu_vx_32m1_m,VSADDU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vsaddu_vx_32m2_m,VSADDU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vsaddu_vx_32m4_m,VSADDU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vsaddu_vx_32m8_m,VSADDU_VX_m,v32i32>;

defm VSADDU_VI : VALU_OPIVI_signed<0b100000,"vsaddu.vi">;

def : PatVgrSimm5<int_riscv_vsaddu_vi_8m1,VSADDU_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vsaddu_vi_8m2,VSADDU_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vsaddu_vi_8m4,VSADDU_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vsaddu_vi_8m8,VSADDU_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vsaddu_vi_16m1,VSADDU_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vsaddu_vi_16m2,VSADDU_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vsaddu_vi_16m4,VSADDU_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vsaddu_vi_16m8,VSADDU_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vsaddu_vi_32m1,VSADDU_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vsaddu_vi_32m2,VSADDU_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vsaddu_vi_32m4,VSADDU_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vsaddu_vi_32m8,VSADDU_VI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vsaddu_vi_8m1_m,VSADDU_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vsaddu_vi_8m2_m,VSADDU_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vsaddu_vi_8m4_m,VSADDU_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vsaddu_vi_8m8_m,VSADDU_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vsaddu_vi_16m1_m,VSADDU_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vsaddu_vi_16m2_m,VSADDU_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vsaddu_vi_16m4_m,VSADDU_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vsaddu_vi_16m8_m,VSADDU_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vsaddu_vi_32m1_m,VSADDU_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vsaddu_vi_32m2_m,VSADDU_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vsaddu_vi_32m4_m,VSADDU_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vsaddu_vi_32m8_m,VSADDU_VI_m,v32i32>;

defm VSADD_VV : VALU_OPIVV<0b100001,"vsadd.vv">;

def : PatVgrVgr<int_riscv_vsadd_vv_8m1,VSADD_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vsadd_vv_8m2,VSADD_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vsadd_vv_8m4,VSADD_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vsadd_vv_8m8,VSADD_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vsadd_vv_16m1,VSADD_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vsadd_vv_16m2,VSADD_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vsadd_vv_16m4,VSADD_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vsadd_vv_16m8,VSADD_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vsadd_vv_32m1,VSADD_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vsadd_vv_32m2,VSADD_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vsadd_vv_32m4,VSADD_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vsadd_vv_32m8,VSADD_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vsadd_vv_8m1_m,VSADD_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vsadd_vv_8m2_m,VSADD_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vsadd_vv_8m4_m,VSADD_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vsadd_vv_8m8_m,VSADD_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vsadd_vv_16m1_m,VSADD_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vsadd_vv_16m2_m,VSADD_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vsadd_vv_16m4_m,VSADD_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vsadd_vv_16m8_m,VSADD_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vsadd_vv_32m1_m,VSADD_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vsadd_vv_32m2_m,VSADD_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vsadd_vv_32m4_m,VSADD_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vsadd_vv_32m8_m,VSADD_VV_m,v32i32>;


defm VSADD_VX : VALU_OPIVX<0b100001,"vsadd.vx">;

def : PatVgrGpr<int_riscv_vsadd_vx_8m1,VSADD_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vsadd_vx_8m2,VSADD_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vsadd_vx_8m4,VSADD_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vsadd_vx_8m8,VSADD_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vsadd_vx_16m1,VSADD_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vsadd_vx_16m2,VSADD_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vsadd_vx_16m4,VSADD_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vsadd_vx_16m8,VSADD_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vsadd_vx_32m1,VSADD_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vsadd_vx_32m2,VSADD_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vsadd_vx_32m4,VSADD_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vsadd_vx_32m8,VSADD_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vsadd_vx_8m1_m,VSADD_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vsadd_vx_8m2_m,VSADD_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vsadd_vx_8m4_m,VSADD_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vsadd_vx_8m8_m,VSADD_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vsadd_vx_16m1_m,VSADD_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vsadd_vx_16m2_m,VSADD_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vsadd_vx_16m4_m,VSADD_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vsadd_vx_16m8_m,VSADD_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vsadd_vx_32m1_m,VSADD_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vsadd_vx_32m2_m,VSADD_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vsadd_vx_32m4_m,VSADD_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vsadd_vx_32m8_m,VSADD_VX_m,v32i32>;

defm VSADD_VI : VALU_OPIVI_signed<0b100001,"vsadd.vi">;

def : PatVgrSimm5<int_riscv_vsadd_vi_8m1,VSADD_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vsadd_vi_8m2,VSADD_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vsadd_vi_8m4,VSADD_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vsadd_vi_8m8,VSADD_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vsadd_vi_16m1,VSADD_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vsadd_vi_16m2,VSADD_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vsadd_vi_16m4,VSADD_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vsadd_vi_16m8,VSADD_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vsadd_vi_32m1,VSADD_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vsadd_vi_32m2,VSADD_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vsadd_vi_32m4,VSADD_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vsadd_vi_32m8,VSADD_VI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vsadd_vi_8m1_m,VSADD_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vsadd_vi_8m2_m,VSADD_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vsadd_vi_8m4_m,VSADD_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vsadd_vi_8m8_m,VSADD_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vsadd_vi_16m1_m,VSADD_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vsadd_vi_16m2_m,VSADD_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vsadd_vi_16m4_m,VSADD_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vsadd_vi_16m8_m,VSADD_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vsadd_vi_32m1_m,VSADD_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vsadd_vi_32m2_m,VSADD_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vsadd_vi_32m4_m,VSADD_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vsadd_vi_32m8_m,VSADD_VI_m,v32i32>;

defm VSSUBU_VV : VALU_OPIVV<0b100010,"vssubu.vv">;

def : PatVgrVgr<int_riscv_vssubu_vv_8m1,VSSUBU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vssubu_vv_8m2,VSSUBU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vssubu_vv_8m4,VSSUBU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vssubu_vv_8m8,VSSUBU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vssubu_vv_16m1,VSSUBU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vssubu_vv_16m2,VSSUBU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vssubu_vv_16m4,VSSUBU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vssubu_vv_16m8,VSSUBU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vssubu_vv_32m1,VSSUBU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vssubu_vv_32m2,VSSUBU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vssubu_vv_32m4,VSSUBU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vssubu_vv_32m8,VSSUBU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vssubu_vv_8m1_m,VSSUBU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vssubu_vv_8m2_m,VSSUBU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vssubu_vv_8m4_m,VSSUBU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vssubu_vv_8m8_m,VSSUBU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vssubu_vv_16m1_m,VSSUBU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vssubu_vv_16m2_m,VSSUBU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vssubu_vv_16m4_m,VSSUBU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vssubu_vv_16m8_m,VSSUBU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vssubu_vv_32m1_m,VSSUBU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vssubu_vv_32m2_m,VSSUBU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vssubu_vv_32m4_m,VSSUBU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vssubu_vv_32m8_m,VSSUBU_VV_m,v32i32>;


defm VSSUBU_VX : VALU_OPIVX<0b100010,"vssubu.vx">;

def : PatVgrGpr<int_riscv_vssubu_vx_8m1,VSSUBU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vssubu_vx_8m2,VSSUBU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vssubu_vx_8m4,VSSUBU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vssubu_vx_8m8,VSSUBU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vssubu_vx_16m1,VSSUBU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vssubu_vx_16m2,VSSUBU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vssubu_vx_16m4,VSSUBU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vssubu_vx_16m8,VSSUBU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vssubu_vx_32m1,VSSUBU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vssubu_vx_32m2,VSSUBU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vssubu_vx_32m4,VSSUBU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vssubu_vx_32m8,VSSUBU_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vssubu_vx_8m1_m,VSSUBU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vssubu_vx_8m2_m,VSSUBU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vssubu_vx_8m4_m,VSSUBU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vssubu_vx_8m8_m,VSSUBU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vssubu_vx_16m1_m,VSSUBU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vssubu_vx_16m2_m,VSSUBU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vssubu_vx_16m4_m,VSSUBU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vssubu_vx_16m8_m,VSSUBU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vssubu_vx_32m1_m,VSSUBU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vssubu_vx_32m2_m,VSSUBU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vssubu_vx_32m4_m,VSSUBU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vssubu_vx_32m8_m,VSSUBU_VX_m,v32i32>;

defm VSSUB_VV : VALU_OPIVV<0b100011,"vssub.vv">;

def : PatVgrVgr<int_riscv_vssub_vv_8m1,VSSUB_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vssub_vv_8m2,VSSUB_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vssub_vv_8m4,VSSUB_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vssub_vv_8m8,VSSUB_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vssub_vv_16m1,VSSUB_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vssub_vv_16m2,VSSUB_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vssub_vv_16m4,VSSUB_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vssub_vv_16m8,VSSUB_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vssub_vv_32m1,VSSUB_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vssub_vv_32m2,VSSUB_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vssub_vv_32m4,VSSUB_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vssub_vv_32m8,VSSUB_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vssub_vv_8m1_m,VSSUB_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vssub_vv_8m2_m,VSSUB_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vssub_vv_8m4_m,VSSUB_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vssub_vv_8m8_m,VSSUB_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vssub_vv_16m1_m,VSSUB_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vssub_vv_16m2_m,VSSUB_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vssub_vv_16m4_m,VSSUB_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vssub_vv_16m8_m,VSSUB_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vssub_vv_32m1_m,VSSUB_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vssub_vv_32m2_m,VSSUB_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vssub_vv_32m4_m,VSSUB_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vssub_vv_32m8_m,VSSUB_VV_m,v32i32>;


defm VSSUB_VX : VALU_OPIVX<0b100011,"vssub.vx">;

def : PatVgrGpr<int_riscv_vssub_vx_8m1,VSSUB_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vssub_vx_8m2,VSSUB_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vssub_vx_8m4,VSSUB_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vssub_vx_8m8,VSSUB_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vssub_vx_16m1,VSSUB_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vssub_vx_16m2,VSSUB_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vssub_vx_16m4,VSSUB_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vssub_vx_16m8,VSSUB_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vssub_vx_32m1,VSSUB_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vssub_vx_32m2,VSSUB_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vssub_vx_32m4,VSSUB_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vssub_vx_32m8,VSSUB_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vssub_vx_8m1_m,VSSUB_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vssub_vx_8m2_m,VSSUB_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vssub_vx_8m4_m,VSSUB_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vssub_vx_8m8_m,VSSUB_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vssub_vx_16m1_m,VSSUB_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vssub_vx_16m2_m,VSSUB_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vssub_vx_16m4_m,VSSUB_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vssub_vx_16m8_m,VSSUB_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vssub_vx_32m1_m,VSSUB_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vssub_vx_32m2_m,VSSUB_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vssub_vx_32m4_m,VSSUB_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vssub_vx_32m8_m,VSSUB_VX_m,v32i32>;

defm VAADDU_VV : VALU_OPMVV<0b001000,"vaaddu.vv">;

def : PatVgrVgr<int_riscv_vaaddu_vv_8m1,VAADDU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vaaddu_vv_8m2,VAADDU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vaaddu_vv_8m4,VAADDU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vaaddu_vv_8m8,VAADDU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vaaddu_vv_16m1,VAADDU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vaaddu_vv_16m2,VAADDU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vaaddu_vv_16m4,VAADDU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vaaddu_vv_16m8,VAADDU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vaaddu_vv_32m1,VAADDU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vaaddu_vv_32m2,VAADDU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vaaddu_vv_32m4,VAADDU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vaaddu_vv_32m8,VAADDU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vaaddu_vv_8m1_m,VAADDU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vaaddu_vv_8m2_m,VAADDU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vaaddu_vv_8m4_m,VAADDU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vaaddu_vv_8m8_m,VAADDU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vaaddu_vv_16m1_m,VAADDU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vaaddu_vv_16m2_m,VAADDU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vaaddu_vv_16m4_m,VAADDU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vaaddu_vv_16m8_m,VAADDU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vaaddu_vv_32m1_m,VAADDU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vaaddu_vv_32m2_m,VAADDU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vaaddu_vv_32m4_m,VAADDU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vaaddu_vv_32m8_m,VAADDU_VV_m,v32i32>;


defm VAADDU_VX : VALU_OPMVX<0b001000,"vaaddu.vx">;

def : PatVgrGpr<int_riscv_vaaddu_vx_8m1,VAADDU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vaaddu_vx_8m2,VAADDU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vaaddu_vx_8m4,VAADDU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vaaddu_vx_8m8,VAADDU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vaaddu_vx_16m1,VAADDU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vaaddu_vx_16m2,VAADDU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vaaddu_vx_16m4,VAADDU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vaaddu_vx_16m8,VAADDU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vaaddu_vx_32m1,VAADDU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vaaddu_vx_32m2,VAADDU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vaaddu_vx_32m4,VAADDU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vaaddu_vx_32m8,VAADDU_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vaaddu_vx_8m1_m,VAADDU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vaaddu_vx_8m2_m,VAADDU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vaaddu_vx_8m4_m,VAADDU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vaaddu_vx_8m8_m,VAADDU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vaaddu_vx_16m1_m,VAADDU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vaaddu_vx_16m2_m,VAADDU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vaaddu_vx_16m4_m,VAADDU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vaaddu_vx_16m8_m,VAADDU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vaaddu_vx_32m1_m,VAADDU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vaaddu_vx_32m2_m,VAADDU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vaaddu_vx_32m4_m,VAADDU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vaaddu_vx_32m8_m,VAADDU_VX_m,v32i32>;

defm VAADD_VV : VALU_OPMVV<0b001001,"vaadd.vv">;

def : PatVgrVgr<int_riscv_vaadd_vv_8m1,VAADD_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vaadd_vv_8m2,VAADD_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vaadd_vv_8m4,VAADD_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vaadd_vv_8m8,VAADD_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vaadd_vv_16m1,VAADD_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vaadd_vv_16m2,VAADD_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vaadd_vv_16m4,VAADD_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vaadd_vv_16m8,VAADD_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vaadd_vv_32m1,VAADD_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vaadd_vv_32m2,VAADD_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vaadd_vv_32m4,VAADD_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vaadd_vv_32m8,VAADD_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vaadd_vv_8m1_m,VAADD_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vaadd_vv_8m2_m,VAADD_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vaadd_vv_8m4_m,VAADD_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vaadd_vv_8m8_m,VAADD_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vaadd_vv_16m1_m,VAADD_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vaadd_vv_16m2_m,VAADD_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vaadd_vv_16m4_m,VAADD_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vaadd_vv_16m8_m,VAADD_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vaadd_vv_32m1_m,VAADD_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vaadd_vv_32m2_m,VAADD_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vaadd_vv_32m4_m,VAADD_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vaadd_vv_32m8_m,VAADD_VV_m,v32i32>;

defm VAADD_VX : VALU_OPMVX<0b001001,"vaadd.vx">;

def : PatVgrGpr<int_riscv_vaadd_vx_8m1,VAADD_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vaadd_vx_8m2,VAADD_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vaadd_vx_8m4,VAADD_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vaadd_vx_8m8,VAADD_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vaadd_vx_16m1,VAADD_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vaadd_vx_16m2,VAADD_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vaadd_vx_16m4,VAADD_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vaadd_vx_16m8,VAADD_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vaadd_vx_32m1,VAADD_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vaadd_vx_32m2,VAADD_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vaadd_vx_32m4,VAADD_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vaadd_vx_32m8,VAADD_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vaadd_vx_8m1_m,VAADD_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vaadd_vx_8m2_m,VAADD_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vaadd_vx_8m4_m,VAADD_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vaadd_vx_8m8_m,VAADD_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vaadd_vx_16m1_m,VAADD_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vaadd_vx_16m2_m,VAADD_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vaadd_vx_16m4_m,VAADD_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vaadd_vx_16m8_m,VAADD_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vaadd_vx_32m1_m,VAADD_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vaadd_vx_32m2_m,VAADD_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vaadd_vx_32m4_m,VAADD_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vaadd_vx_32m8_m,VAADD_VX_m,v32i32>;

defm VASUBU_VV : VALU_OPMVV<0b001010,"vasubu.vv">;

def : PatVgrVgr<int_riscv_vasubu_vv_8m1,VASUBU_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vasubu_vv_8m2,VASUBU_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vasubu_vv_8m4,VASUBU_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vasubu_vv_8m8,VASUBU_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vasubu_vv_16m1,VASUBU_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vasubu_vv_16m2,VASUBU_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vasubu_vv_16m4,VASUBU_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vasubu_vv_16m8,VASUBU_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vasubu_vv_32m1,VASUBU_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vasubu_vv_32m2,VASUBU_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vasubu_vv_32m4,VASUBU_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vasubu_vv_32m8,VASUBU_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vasubu_vv_8m1_m,VASUBU_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vasubu_vv_8m2_m,VASUBU_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vasubu_vv_8m4_m,VASUBU_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vasubu_vv_8m8_m,VASUBU_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vasubu_vv_16m1_m,VASUBU_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vasubu_vv_16m2_m,VASUBU_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vasubu_vv_16m4_m,VASUBU_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vasubu_vv_16m8_m,VASUBU_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vasubu_vv_32m1_m,VASUBU_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vasubu_vv_32m2_m,VASUBU_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vasubu_vv_32m4_m,VASUBU_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vasubu_vv_32m8_m,VASUBU_VV_m,v32i32>;


defm VASUBU_VX : VALU_OPMVX<0b001010,"vasubu.vx">;

def : PatVgrGpr<int_riscv_vasubu_vx_8m1,VASUBU_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vasubu_vx_8m2,VASUBU_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vasubu_vx_8m4,VASUBU_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vasubu_vx_8m8,VASUBU_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vasubu_vx_16m1,VASUBU_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vasubu_vx_16m2,VASUBU_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vasubu_vx_16m4,VASUBU_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vasubu_vx_16m8,VASUBU_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vasubu_vx_32m1,VASUBU_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vasubu_vx_32m2,VASUBU_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vasubu_vx_32m4,VASUBU_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vasubu_vx_32m8,VASUBU_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vasubu_vx_8m1_m,VASUBU_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vasubu_vx_8m2_m,VASUBU_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vasubu_vx_8m4_m,VASUBU_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vasubu_vx_8m8_m,VASUBU_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vasubu_vx_16m1_m,VASUBU_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vasubu_vx_16m2_m,VASUBU_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vasubu_vx_16m4_m,VASUBU_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vasubu_vx_16m8_m,VASUBU_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vasubu_vx_32m1_m,VASUBU_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vasubu_vx_32m2_m,VASUBU_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vasubu_vx_32m4_m,VASUBU_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vasubu_vx_32m8_m,VASUBU_VX_m,v32i32>;

defm VASUB_VV : VALU_OPMVV<0b001011,"vasub.vv">;

def : PatVgrVgr<int_riscv_vasub_vv_8m1,VASUB_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vasub_vv_8m2,VASUB_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vasub_vv_8m4,VASUB_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vasub_vv_8m8,VASUB_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vasub_vv_16m1,VASUB_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vasub_vv_16m2,VASUB_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vasub_vv_16m4,VASUB_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vasub_vv_16m8,VASUB_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vasub_vv_32m1,VASUB_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vasub_vv_32m2,VASUB_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vasub_vv_32m4,VASUB_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vasub_vv_32m8,VASUB_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vasub_vv_8m1_m,VASUB_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vasub_vv_8m2_m,VASUB_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vasub_vv_8m4_m,VASUB_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vasub_vv_8m8_m,VASUB_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vasub_vv_16m1_m,VASUB_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vasub_vv_16m2_m,VASUB_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vasub_vv_16m4_m,VASUB_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vasub_vv_16m8_m,VASUB_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vasub_vv_32m1_m,VASUB_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vasub_vv_32m2_m,VASUB_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vasub_vv_32m4_m,VASUB_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vasub_vv_32m8_m,VASUB_VV_m,v32i32>;


defm VASUB_VX : VALU_OPMVX<0b001011,"vasub.vx">;

def : PatVgrGpr<int_riscv_vasub_vx_8m1,VASUB_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vasub_vx_8m2,VASUB_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vasub_vx_8m4,VASUB_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vasub_vx_8m8,VASUB_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vasub_vx_16m1,VASUB_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vasub_vx_16m2,VASUB_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vasub_vx_16m4,VASUB_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vasub_vx_16m8,VASUB_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vasub_vx_32m1,VASUB_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vasub_vx_32m2,VASUB_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vasub_vx_32m4,VASUB_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vasub_vx_32m8,VASUB_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vasub_vx_8m1_m,VASUB_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vasub_vx_8m2_m,VASUB_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vasub_vx_8m4_m,VASUB_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vasub_vx_8m8_m,VASUB_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vasub_vx_16m1_m,VASUB_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vasub_vx_16m2_m,VASUB_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vasub_vx_16m4_m,VASUB_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vasub_vx_16m8_m,VASUB_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vasub_vx_32m1_m,VASUB_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vasub_vx_32m2_m,VASUB_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vasub_vx_32m4_m,VASUB_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vasub_vx_32m8_m,VASUB_VX_m,v32i32>;

/***********Vector Single-Width Fractional Multiply with Rounding and Saturation Functions***************/

defm VSMUL_VV : VALU_OPIVV<0b100111,"vsmul.vv">;

def : PatVgrVgr<int_riscv_vsmul_vv_8m1,VSMUL_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vsmul_vv_8m2,VSMUL_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vsmul_vv_8m4,VSMUL_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vsmul_vv_8m8,VSMUL_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vsmul_vv_16m1,VSMUL_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vsmul_vv_16m2,VSMUL_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vsmul_vv_16m4,VSMUL_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vsmul_vv_16m8,VSMUL_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vsmul_vv_32m1,VSMUL_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vsmul_vv_32m2,VSMUL_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vsmul_vv_32m4,VSMUL_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vsmul_vv_32m8,VSMUL_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vsmul_vv_8m1_m,VSMUL_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vsmul_vv_8m2_m,VSMUL_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vsmul_vv_8m4_m,VSMUL_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vsmul_vv_8m8_m,VSMUL_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vsmul_vv_16m1_m,VSMUL_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vsmul_vv_16m2_m,VSMUL_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vsmul_vv_16m4_m,VSMUL_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vsmul_vv_16m8_m,VSMUL_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vsmul_vv_32m1_m,VSMUL_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vsmul_vv_32m2_m,VSMUL_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vsmul_vv_32m4_m,VSMUL_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vsmul_vv_32m8_m,VSMUL_VV_m,v32i32>;

defm VSMUL_VX : VALU_OPIVX<0b100111,"vsmul.vx">;

def : PatVgrGpr<int_riscv_vsmul_vx_8m1,VSMUL_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vsmul_vx_8m2,VSMUL_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vsmul_vx_8m4,VSMUL_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vsmul_vx_8m8,VSMUL_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vsmul_vx_16m1,VSMUL_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vsmul_vx_16m2,VSMUL_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vsmul_vx_16m4,VSMUL_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vsmul_vx_16m8,VSMUL_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vsmul_vx_32m1,VSMUL_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vsmul_vx_32m2,VSMUL_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vsmul_vx_32m4,VSMUL_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vsmul_vx_32m8,VSMUL_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vsmul_vx_8m1_m,VSMUL_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vsmul_vx_8m2_m,VSMUL_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vsmul_vx_8m4_m,VSMUL_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vsmul_vx_8m8_m,VSMUL_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vsmul_vx_16m1_m,VSMUL_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vsmul_vx_16m2_m,VSMUL_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vsmul_vx_16m4_m,VSMUL_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vsmul_vx_16m8_m,VSMUL_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vsmul_vx_32m1_m,VSMUL_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vsmul_vx_32m2_m,VSMUL_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vsmul_vx_32m4_m,VSMUL_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vsmul_vx_32m8_m,VSMUL_VX_m,v32i32>;


/**************Vector Single-Width Scaling Shift Functions****************/

defm VSSRL_VV : VALU_OPIVV<0b101010,"vssrl.vv">;

def : PatVgrVgr<int_riscv_vssrl_vv_8m1,VSSRL_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vssrl_vv_8m2,VSSRL_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vssrl_vv_8m4,VSSRL_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vssrl_vv_8m8,VSSRL_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vssrl_vv_16m1,VSSRL_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vssrl_vv_16m2,VSSRL_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vssrl_vv_16m4,VSSRL_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vssrl_vv_16m8,VSSRL_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vssrl_vv_32m1,VSSRL_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vssrl_vv_32m2,VSSRL_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vssrl_vv_32m4,VSSRL_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vssrl_vv_32m8,VSSRL_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vssrl_vv_8m1_m,VSSRL_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vssrl_vv_8m2_m,VSSRL_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vssrl_vv_8m4_m,VSSRL_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vssrl_vv_8m8_m,VSSRL_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vssrl_vv_16m1_m,VSSRL_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vssrl_vv_16m2_m,VSSRL_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vssrl_vv_16m4_m,VSSRL_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vssrl_vv_16m8_m,VSSRL_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vssrl_vv_32m1_m,VSSRL_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vssrl_vv_32m2_m,VSSRL_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vssrl_vv_32m4_m,VSSRL_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vssrl_vv_32m8_m,VSSRL_VV_m,v32i32>;


defm VSSRL_VX : VALU_OPIVX<0b101010,"vssrl.vx">;

def : PatVgrGpr<int_riscv_vssrl_vx_8m1,VSSRL_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vssrl_vx_8m2,VSSRL_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vssrl_vx_8m4,VSSRL_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vssrl_vx_8m8,VSSRL_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vssrl_vx_16m1,VSSRL_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vssrl_vx_16m2,VSSRL_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vssrl_vx_16m4,VSSRL_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vssrl_vx_16m8,VSSRL_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vssrl_vx_32m1,VSSRL_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vssrl_vx_32m2,VSSRL_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vssrl_vx_32m4,VSSRL_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vssrl_vx_32m8,VSSRL_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vssrl_vx_8m1_m,VSSRL_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vssrl_vx_8m2_m,VSSRL_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vssrl_vx_8m4_m,VSSRL_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vssrl_vx_8m8_m,VSSRL_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vssrl_vx_16m1_m,VSSRL_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vssrl_vx_16m2_m,VSSRL_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vssrl_vx_16m4_m,VSSRL_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vssrl_vx_16m8_m,VSSRL_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vssrl_vx_32m1_m,VSSRL_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vssrl_vx_32m2_m,VSSRL_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vssrl_vx_32m4_m,VSSRL_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vssrl_vx_32m8_m,VSSRL_VX_m,v32i32>;

defm VSSRL_VI : VALU_OPIVI_unsigned<0b101010,"vssrl.vi">;

def : PatVgrSimm5<int_riscv_vssrl_vi_8m1,VSSRL_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vssrl_vi_8m2,VSSRL_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vssrl_vi_8m4,VSSRL_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vssrl_vi_8m8,VSSRL_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vssrl_vi_16m1,VSSRL_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vssrl_vi_16m2,VSSRL_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vssrl_vi_16m4,VSSRL_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vssrl_vi_16m8,VSSRL_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vssrl_vi_32m1,VSSRL_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vssrl_vi_32m2,VSSRL_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vssrl_vi_32m4,VSSRL_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vssrl_vi_32m8,VSSRL_VI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vssrl_vi_8m1_m,VSSRL_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vssrl_vi_8m2_m,VSSRL_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vssrl_vi_8m4_m,VSSRL_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vssrl_vi_8m8_m,VSSRL_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vssrl_vi_16m1_m,VSSRL_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vssrl_vi_16m2_m,VSSRL_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vssrl_vi_16m4_m,VSSRL_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vssrl_vi_16m8_m,VSSRL_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vssrl_vi_32m1_m,VSSRL_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vssrl_vi_32m2_m,VSSRL_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vssrl_vi_32m4_m,VSSRL_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vssrl_vi_32m8_m,VSSRL_VI_m,v32i32>;

defm VSSRA_VV : VALU_OPIVV<0b101011,"vssra.vv">;

def : PatVgrVgr<int_riscv_vssra_vv_8m1,VSSRA_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vssra_vv_8m2,VSSRA_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vssra_vv_8m4,VSSRA_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vssra_vv_8m8,VSSRA_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vssra_vv_16m1,VSSRA_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vssra_vv_16m2,VSSRA_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vssra_vv_16m4,VSSRA_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vssra_vv_16m8,VSSRA_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vssra_vv_32m1,VSSRA_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vssra_vv_32m2,VSSRA_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vssra_vv_32m4,VSSRA_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vssra_vv_32m8,VSSRA_VV_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vssra_vv_8m1_m,VSSRA_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vssra_vv_8m2_m,VSSRA_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vssra_vv_8m4_m,VSSRA_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vssra_vv_8m8_m,VSSRA_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vssra_vv_16m1_m,VSSRA_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vssra_vv_16m2_m,VSSRA_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vssra_vv_16m4_m,VSSRA_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vssra_vv_16m8_m,VSSRA_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vssra_vv_32m1_m,VSSRA_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vssra_vv_32m2_m,VSSRA_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vssra_vv_32m4_m,VSSRA_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vssra_vv_32m8_m,VSSRA_VV_m,v32i32>;


defm VSSRA_VX : VALU_OPIVX<0b101011,"vssra.vx">;

def : PatVgrGpr<int_riscv_vssra_vx_8m1,VSSRA_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vssra_vx_8m2,VSSRA_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vssra_vx_8m4,VSSRA_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vssra_vx_8m8,VSSRA_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vssra_vx_16m1,VSSRA_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vssra_vx_16m2,VSSRA_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vssra_vx_16m4,VSSRA_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vssra_vx_16m8,VSSRA_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vssra_vx_32m1,VSSRA_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vssra_vx_32m2,VSSRA_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vssra_vx_32m4,VSSRA_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vssra_vx_32m8,VSSRA_VX_um,v32i32>;

def : PatVmVgrGpr<int_riscv_vssra_vx_8m1_m,VSSRA_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vssra_vx_8m2_m,VSSRA_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vssra_vx_8m4_m,VSSRA_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vssra_vx_8m8_m,VSSRA_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vssra_vx_16m1_m,VSSRA_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vssra_vx_16m2_m,VSSRA_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vssra_vx_16m4_m,VSSRA_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vssra_vx_16m8_m,VSSRA_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vssra_vx_32m1_m,VSSRA_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vssra_vx_32m2_m,VSSRA_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vssra_vx_32m4_m,VSSRA_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vssra_vx_32m8_m,VSSRA_VX_m,v32i32>;

defm VSSRA_VI : VALU_OPIVI_unsigned<0b101011,"vssra.vi">;

def : PatVgrSimm5<int_riscv_vssra_vi_8m1,VSSRA_VI_um,v16i8>;
def : PatVgrSimm5<int_riscv_vssra_vi_8m2,VSSRA_VI_um,v32i8>;
def : PatVgrSimm5<int_riscv_vssra_vi_8m4,VSSRA_VI_um,v64i8>;
def : PatVgrSimm5<int_riscv_vssra_vi_8m8,VSSRA_VI_um,v128i8>;

def : PatVgrSimm5<int_riscv_vssra_vi_16m1,VSSRA_VI_um,v8i16>;
def : PatVgrSimm5<int_riscv_vssra_vi_16m2,VSSRA_VI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vssra_vi_16m4,VSSRA_VI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vssra_vi_16m8,VSSRA_VI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vssra_vi_32m1,VSSRA_VI_um,v4i32>;
def : PatVgrSimm5<int_riscv_vssra_vi_32m2,VSSRA_VI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vssra_vi_32m4,VSSRA_VI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vssra_vi_32m8,VSSRA_VI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vssra_vi_8m1_m,VSSRA_VI_m,v16i8>;
def : PatVmVgrSimm5<int_riscv_vssra_vi_8m2_m,VSSRA_VI_m,v32i8>;
def : PatVmVgrSimm5<int_riscv_vssra_vi_8m4_m,VSSRA_VI_m,v64i8>;
def : PatVmVgrSimm5<int_riscv_vssra_vi_8m8_m,VSSRA_VI_m,v128i8>;

def : PatVmVgrSimm5<int_riscv_vssra_vi_16m1_m,VSSRA_VI_m,v8i16>;
def : PatVmVgrSimm5<int_riscv_vssra_vi_16m2_m,VSSRA_VI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vssra_vi_16m4_m,VSSRA_VI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vssra_vi_16m8_m,VSSRA_VI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vssra_vi_32m1_m,VSSRA_VI_m,v4i32>;
def : PatVmVgrSimm5<int_riscv_vssra_vi_32m2_m,VSSRA_VI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vssra_vi_32m4_m,VSSRA_VI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vssra_vi_32m8_m,VSSRA_VI_m,v32i32>;

/*************Vector Narrowing Fixed-Point Clip Functions****************/

defm VNCLIPU_WV : VALU_OPIVV<0b101110,"vnclipu.wv">;

def : PatWidVgrVgr<int_riscv_vnclipu_wv_8m1,VNCLIPU_WV_um,v16i16,v16i8>;
def : PatWidVgrVgr<int_riscv_vnclipu_wv_8m2,VNCLIPU_WV_um,v32i16,v32i8>;
def : PatWidVgrVgr<int_riscv_vnclipu_wv_8m4,VNCLIPU_WV_um,v64i16,v64i8>;

def : PatWidVgrVgr<int_riscv_vnclipu_wv_16m1,VNCLIPU_WV_um,v8i32,v8i16>;
def : PatWidVgrVgr<int_riscv_vnclipu_wv_16m2,VNCLIPU_WV_um,v16i32,v16i16>;
def : PatWidVgrVgr<int_riscv_vnclipu_wv_16m4,VNCLIPU_WV_um,v32i32,v32i16>;

def : PatVmWidVgrVgr<int_riscv_vnclipu_wv_8m1_m,VNCLIPU_WV_m,v16i16,v16i8>;
def : PatVmWidVgrVgr<int_riscv_vnclipu_wv_8m2_m,VNCLIPU_WV_m,v32i16,v32i8>;
def : PatVmWidVgrVgr<int_riscv_vnclipu_wv_8m4_m,VNCLIPU_WV_m,v64i16,v64i8>;

def : PatVmWidVgrVgr<int_riscv_vnclipu_wv_16m1_m,VNCLIPU_WV_m,v8i32,v8i16>;
def : PatVmWidVgrVgr<int_riscv_vnclipu_wv_16m2_m,VNCLIPU_WV_m,v16i32,v16i16>;
def : PatVmWidVgrVgr<int_riscv_vnclipu_wv_16m4_m,VNCLIPU_WV_m,v32i32,v32i16>;

defm VNCLIPU_WX : VALU_OPIVX<0b101110,"vnclipu.wx">;

def : PatWidVgrGpr<int_riscv_vnclipu_wx_8m1,VNCLIPU_WX_um,v16i16>;
def : PatWidVgrGpr<int_riscv_vnclipu_wx_8m2,VNCLIPU_WX_um,v32i16>;
def : PatWidVgrGpr<int_riscv_vnclipu_wx_8m4,VNCLIPU_WX_um,v64i16>;

def : PatWidVgrGpr<int_riscv_vnclipu_wx_16m1,VNCLIPU_WX_um,v8i32>;
def : PatWidVgrGpr<int_riscv_vnclipu_wx_16m2,VNCLIPU_WX_um,v16i32>;
def : PatWidVgrGpr<int_riscv_vnclipu_wx_16m4,VNCLIPU_WX_um,v32i32>;

def : PatVmWidVgrGpr<int_riscv_vnclipu_wx_8m1_m,VNCLIPU_WX_m,v16i16>;
def : PatVmWidVgrGpr<int_riscv_vnclipu_wx_8m2_m,VNCLIPU_WX_m,v32i16>;
def : PatVmWidVgrGpr<int_riscv_vnclipu_wx_8m4_m,VNCLIPU_WX_m,v64i16>;

def : PatVmWidVgrGpr<int_riscv_vnclipu_wx_16m1_m,VNCLIPU_WX_m,v8i32>;
def : PatVmWidVgrGpr<int_riscv_vnclipu_wx_16m2_m,VNCLIPU_WX_m,v16i32>;
def : PatVmWidVgrGpr<int_riscv_vnclipu_wx_16m4_m,VNCLIPU_WX_m,v32i32>;

defm VNCLIPU_WI : VALU_OPIVI_unsigned<0b101110,"vnclipu.wi">;

def : PatVgrSimm5<int_riscv_vnclipu_wi_8m1,VNCLIPU_WI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vnclipu_wi_8m2,VNCLIPU_WI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vnclipu_wi_8m4,VNCLIPU_WI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vnclipu_wi_16m1,VNCLIPU_WI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vnclipu_wi_16m2,VNCLIPU_WI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vnclipu_wi_16m4,VNCLIPU_WI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vnclipu_wi_8m1_m,VNCLIPU_WI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vnclipu_wi_8m2_m,VNCLIPU_WI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vnclipu_wi_8m4_m,VNCLIPU_WI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vnclipu_wi_16m1_m,VNCLIPU_WI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vnclipu_wi_16m2_m,VNCLIPU_WI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vnclipu_wi_16m4_m,VNCLIPU_WI_m,v32i32>;

defm VNCLIP_WV : VALU_OPIVV<0b101111,"vnclip.wv">;

def : PatWidVgrVgr<int_riscv_vnclip_wv_8m1,VNCLIP_WV_um,v16i16,v16i8>;
def : PatWidVgrVgr<int_riscv_vnclip_wv_8m2,VNCLIP_WV_um,v32i16,v32i8>;
def : PatWidVgrVgr<int_riscv_vnclip_wv_8m4,VNCLIP_WV_um,v64i16,v64i8>;

def : PatWidVgrVgr<int_riscv_vnclip_wv_16m1,VNCLIP_WV_um,v8i32,v8i16>;
def : PatWidVgrVgr<int_riscv_vnclip_wv_16m2,VNCLIP_WV_um,v16i32,v16i16>;
def : PatWidVgrVgr<int_riscv_vnclip_wv_16m4,VNCLIP_WV_um,v32i32,v32i16>;

def : PatVmWidVgrVgr<int_riscv_vnclip_wv_8m1_m,VNCLIP_WV_m,v16i16,v16i8>;
def : PatVmWidVgrVgr<int_riscv_vnclip_wv_8m2_m,VNCLIP_WV_m,v32i16,v32i8>;
def : PatVmWidVgrVgr<int_riscv_vnclip_wv_8m4_m,VNCLIP_WV_m,v64i16,v64i8>;

def : PatVmWidVgrVgr<int_riscv_vnclip_wv_16m1_m,VNCLIP_WV_m,v8i32,v8i16>;
def : PatVmWidVgrVgr<int_riscv_vnclip_wv_16m2_m,VNCLIP_WV_m,v16i32,v16i16>;
def : PatVmWidVgrVgr<int_riscv_vnclip_wv_16m4_m,VNCLIP_WV_m,v32i32,v32i16>;

defm VNCLIP_WX : VALU_OPIVX<0b101111,"vnclip.wx">;

def : PatWidVgrGpr<int_riscv_vnclip_wx_8m1,VNCLIP_WX_um,v16i16>;
def : PatWidVgrGpr<int_riscv_vnclip_wx_8m2,VNCLIP_WX_um,v32i16>;
def : PatWidVgrGpr<int_riscv_vnclip_wx_8m4,VNCLIP_WX_um,v64i16>;

def : PatWidVgrGpr<int_riscv_vnclip_wx_16m1,VNCLIP_WX_um,v8i32>;
def : PatWidVgrGpr<int_riscv_vnclip_wx_16m2,VNCLIP_WX_um,v16i32>;
def : PatWidVgrGpr<int_riscv_vnclip_wx_16m4,VNCLIP_WX_um,v32i32>;

def : PatVmWidVgrGpr<int_riscv_vnclip_wx_8m1_m,VNCLIP_WX_m,v16i16>;
def : PatVmWidVgrGpr<int_riscv_vnclip_wx_8m2_m,VNCLIP_WX_m,v32i16>;
def : PatVmWidVgrGpr<int_riscv_vnclip_wx_8m4_m,VNCLIP_WX_m,v64i16>;

def : PatVmWidVgrGpr<int_riscv_vnclip_wx_16m1_m,VNCLIP_WX_m,v8i32>;
def : PatVmWidVgrGpr<int_riscv_vnclip_wx_16m2_m,VNCLIP_WX_m,v16i32>;
def : PatVmWidVgrGpr<int_riscv_vnclip_wx_16m4_m,VNCLIP_WX_m,v32i32>;

defm VNCLIP_WI : VALU_OPIVI_unsigned<0b101111,"vnclip.wi">;

def : PatVgrSimm5<int_riscv_vnclip_wi_8m1,VNCLIP_WI_um,v16i16>;
def : PatVgrSimm5<int_riscv_vnclip_wi_8m2,VNCLIP_WI_um,v32i16>;
def : PatVgrSimm5<int_riscv_vnclip_wi_8m4,VNCLIP_WI_um,v64i16>;

def : PatVgrSimm5<int_riscv_vnclip_wi_16m1,VNCLIP_WI_um,v8i32>;
def : PatVgrSimm5<int_riscv_vnclip_wi_16m2,VNCLIP_WI_um,v16i32>;
def : PatVgrSimm5<int_riscv_vnclip_wi_16m4,VNCLIP_WI_um,v32i32>;

def : PatVmVgrSimm5<int_riscv_vnclip_wi_8m1_m,VNCLIP_WI_m,v16i16>;
def : PatVmVgrSimm5<int_riscv_vnclip_wi_8m2_m,VNCLIP_WI_m,v32i16>;
def : PatVmVgrSimm5<int_riscv_vnclip_wi_8m4_m,VNCLIP_WI_m,v64i16>;

def : PatVmVgrSimm5<int_riscv_vnclip_wi_16m1_m,VNCLIP_WI_m,v8i32>;
def : PatVmVgrSimm5<int_riscv_vnclip_wi_16m2_m,VNCLIP_WI_m,v16i32>;
def : PatVmVgrSimm5<int_riscv_vnclip_wi_16m4_m,VNCLIP_WI_m,v32i32>;

/*************Vector Single-Width Floating-Point Add/Subtract Functions****************/
defm VFADD_VV : VALU_OPFVV<0b000000,"vfadd.vv">;

def : PatVgrVgr<int_riscv_vfadd_vv_f32m1,VFADD_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vfadd_vv_f32m2,VFADD_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vfadd_vv_f32m4,VFADD_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vfadd_vv_f32m8,VFADD_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfadd_vv_f32m1_m,VFADD_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfadd_vv_f32m2_m,VFADD_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfadd_vv_f32m4_m,VFADD_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfadd_vv_f32m8_m,VFADD_VV_m,v32f32>;

defm VFADD_VF : VALU_OPFVF<0b000000,"vfadd.vf">;

def : PatVgrFloat<int_riscv_vfadd_vf_f32m1,VFADD_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfadd_vf_f32m2,VFADD_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfadd_vf_f32m4,VFADD_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfadd_vf_f32m8,VFADD_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vfadd_vf_f32m1_m,VFADD_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfadd_vf_f32m2_m,VFADD_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfadd_vf_f32m4_m,VFADD_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfadd_vf_f32m8_m,VFADD_VF_m,v32f32>;

defm VFSUB_VV : VALU_OPFVV<0b000010,"vfsub.vv">;

def : PatVgrVgr<int_riscv_vfsub_vv_f32m1,VFSUB_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vfsub_vv_f32m2,VFSUB_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vfsub_vv_f32m4,VFSUB_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vfsub_vv_f32m8,VFSUB_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfsub_vv_f32m1_m,VFSUB_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfsub_vv_f32m2_m,VFSUB_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfsub_vv_f32m4_m,VFSUB_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfsub_vv_f32m8_m,VFSUB_VV_m,v32f32>;

defm VFSUB_VF : VALU_OPFVF<0b000010,"vfsub.vf">;

def : PatVgrFloat<int_riscv_vfsub_vf_f32m1,VFSUB_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfsub_vf_f32m2,VFSUB_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfsub_vf_f32m4,VFSUB_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfsub_vf_f32m8,VFSUB_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vfsub_vf_f32m1_m,VFSUB_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfsub_vf_f32m2_m,VFSUB_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfsub_vf_f32m4_m,VFSUB_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfsub_vf_f32m8_m,VFSUB_VF_m,v32f32>;

defm VFRSUB_VF : VALU_OPFVF<0b100111,"vfrsub.vf">;

def : PatVgrFloat<int_riscv_vfrsub_vf_f32m1,VFRSUB_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfrsub_vf_f32m2,VFRSUB_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfrsub_vf_f32m4,VFRSUB_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfrsub_vf_f32m8,VFRSUB_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vfrsub_vf_f32m1_m,VFRSUB_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfrsub_vf_f32m2_m,VFRSUB_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfrsub_vf_f32m4_m,VFRSUB_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfrsub_vf_f32m8_m,VFRSUB_VF_m,v32f32>;
	
/*************Vector Single-Width Floating-Point Multiply/Divide Functions****************/
defm VFMUL_VV : VALU_OPFVV<0b100100,"vfmul.vv">;

def : PatVgrVgr<int_riscv_vfmul_vv_f32m1,VFMUL_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vfmul_vv_f32m2,VFMUL_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vfmul_vv_f32m4,VFMUL_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vfmul_vv_f32m8,VFMUL_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfmul_vv_f32m1_m,VFMUL_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfmul_vv_f32m2_m,VFMUL_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfmul_vv_f32m4_m,VFMUL_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfmul_vv_f32m8_m,VFMUL_VV_m,v32f32>;

defm VFMUL_VF : VALU_OPFVF<0b100100,"vfmul.vf">;

def : PatVgrFloat<int_riscv_vfmul_vf_f32m1,VFMUL_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfmul_vf_f32m2,VFMUL_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfmul_vf_f32m4,VFMUL_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfmul_vf_f32m8,VFMUL_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vfmul_vf_f32m1_m,VFMUL_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfmul_vf_f32m2_m,VFMUL_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfmul_vf_f32m4_m,VFMUL_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfmul_vf_f32m8_m,VFMUL_VF_m,v32f32>;

defm VFDIV_VV : VALU_OPFVV<0b100000,"vfdiv.vv">;

def : PatVgrVgr<int_riscv_vfdiv_vv_f32m1,VFDIV_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vfdiv_vv_f32m2,VFDIV_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vfdiv_vv_f32m4,VFDIV_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vfdiv_vv_f32m8,VFDIV_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfdiv_vv_f32m1_m,VFDIV_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfdiv_vv_f32m2_m,VFDIV_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfdiv_vv_f32m4_m,VFDIV_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfdiv_vv_f32m8_m,VFDIV_VV_m,v32f32>;

defm VFDIV_VF : VALU_OPFVF<0b100000,"vfdiv.vf">;

def : PatVgrFloat<int_riscv_vfdiv_vf_f32m1,VFDIV_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfdiv_vf_f32m2,VFDIV_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfdiv_vf_f32m4,VFDIV_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfdiv_vf_f32m8,VFDIV_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vfdiv_vf_f32m1_m,VFDIV_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfdiv_vf_f32m2_m,VFDIV_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfdiv_vf_f32m4_m,VFDIV_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfdiv_vf_f32m8_m,VFDIV_VF_m,v32f32>;

defm VFRDIV_VF : VALU_OPFVF<0b100001,"vfrdiv.vf">;	

def : PatVgrFloat<int_riscv_vfrdiv_vf_f32m1,VFRDIV_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfrdiv_vf_f32m2,VFRDIV_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfrdiv_vf_f32m4,VFRDIV_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfrdiv_vf_f32m8,VFRDIV_VF_um,v32f32>;
	
def : PatVmVgrFloat<int_riscv_vfrdiv_vf_f32m1_m,VFRDIV_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfrdiv_vf_f32m2_m,VFRDIV_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfrdiv_vf_f32m4_m,VFRDIV_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfrdiv_vf_f32m8_m,VFRDIV_VF_m,v32f32>;	

/*************Vector Single-Width Floating-Point Fused Multiply-Add Functions****************/
defm VFMACC_VV : VALU_OPFVV_MulAdd<0b101100,"vfmacc.vv">;

def : PatVgrVgrVgr<int_riscv_vfmacc_vv_f32m1,VFMACC_VV_um,v4f32>;
def : PatVgrVgrVgr<int_riscv_vfmacc_vv_f32m2,VFMACC_VV_um,v8f32>;
def : PatVgrVgrVgr<int_riscv_vfmacc_vv_f32m4,VFMACC_VV_um,v16f32>;
def : PatVgrVgrVgr<int_riscv_vfmacc_vv_f32m8,VFMACC_VV_um,v32f32>;

def : PatVmVgrVgrVgr<int_riscv_vfmacc_vv_f32m1_m,VFMACC_VV_m,v4f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmacc_vv_f32m2_m,VFMACC_VV_m,v8f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmacc_vv_f32m4_m,VFMACC_VV_m,v16f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmacc_vv_f32m8_m,VFMACC_VV_m,v32f32>;

defm VFMACC_VF : VALU_OPFVF_MulAdd<0b101100,"vfmacc.vf">;

def : PatVgrFloatVgr<int_riscv_vfmacc_vf_f32m1,VFMACC_VF_um,v4f32>;
def : PatVgrFloatVgr<int_riscv_vfmacc_vf_f32m2,VFMACC_VF_um,v8f32>;
def : PatVgrFloatVgr<int_riscv_vfmacc_vf_f32m4,VFMACC_VF_um,v16f32>;
def : PatVgrFloatVgr<int_riscv_vfmacc_vf_f32m8,VFMACC_VF_um,v32f32>;

def : PatVmVgrFloatVgr<int_riscv_vfmacc_vf_f32m1_m,VFMACC_VF_m,v4f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmacc_vf_f32m2_m,VFMACC_VF_m,v8f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmacc_vf_f32m4_m,VFMACC_VF_m,v16f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmacc_vf_f32m8_m,VFMACC_VF_m,v32f32>;

defm VFNMACC_VV : VALU_OPFVV_MulAdd<0b101101,"vfnmacc.vv">;

def : PatVgrVgrVgr<int_riscv_vfnmacc_vv_f32m1,VFNMACC_VV_um,v4f32>;
def : PatVgrVgrVgr<int_riscv_vfnmacc_vv_f32m2,VFNMACC_VV_um,v8f32>;
def : PatVgrVgrVgr<int_riscv_vfnmacc_vv_f32m4,VFNMACC_VV_um,v16f32>;
def : PatVgrVgrVgr<int_riscv_vfnmacc_vv_f32m8,VFNMACC_VV_um,v32f32>;

def : PatVmVgrVgrVgr<int_riscv_vfnmacc_vv_f32m1_m,VFNMACC_VV_m,v4f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmacc_vv_f32m2_m,VFNMACC_VV_m,v8f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmacc_vv_f32m4_m,VFNMACC_VV_m,v16f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmacc_vv_f32m8_m,VFNMACC_VV_m,v32f32>;

defm VFNMACC_VF : VALU_OPFVF_MulAdd<0b101101,"vfnmacc.vf">;

def : PatVgrFloatVgr<int_riscv_vfnmacc_vf_f32m1,VFNMACC_VF_um,v4f32>;
def : PatVgrFloatVgr<int_riscv_vfnmacc_vf_f32m2,VFNMACC_VF_um,v8f32>;
def : PatVgrFloatVgr<int_riscv_vfnmacc_vf_f32m4,VFNMACC_VF_um,v16f32>;
def : PatVgrFloatVgr<int_riscv_vfnmacc_vf_f32m8,VFNMACC_VF_um,v32f32>;

def : PatVmVgrFloatVgr<int_riscv_vfnmacc_vf_f32m1_m,VFNMACC_VF_m,v4f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmacc_vf_f32m2_m,VFNMACC_VF_m,v8f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmacc_vf_f32m4_m,VFNMACC_VF_m,v16f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmacc_vf_f32m8_m,VFNMACC_VF_m,v32f32>;

defm VFMSAC_VV : VALU_OPFVV_MulAdd<0b101110,"vfmsac.vv">;

def : PatVgrVgrVgr<int_riscv_vfmsac_vv_f32m1,VFMSAC_VV_um,v4f32>;
def : PatVgrVgrVgr<int_riscv_vfmsac_vv_f32m2,VFMSAC_VV_um,v8f32>;
def : PatVgrVgrVgr<int_riscv_vfmsac_vv_f32m4,VFMSAC_VV_um,v16f32>;
def : PatVgrVgrVgr<int_riscv_vfmsac_vv_f32m8,VFMSAC_VV_um,v32f32>;

def : PatVmVgrVgrVgr<int_riscv_vfmsac_vv_f32m1_m,VFMSAC_VV_m,v4f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmsac_vv_f32m2_m,VFMSAC_VV_m,v8f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmsac_vv_f32m4_m,VFMSAC_VV_m,v16f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmsac_vv_f32m8_m,VFMSAC_VV_m,v32f32>;

defm VFMSAC_VF : VALU_OPFVF_MulAdd<0b101110,"vfmsac.vf">;

def : PatVgrFloatVgr<int_riscv_vfmsac_vf_f32m1,VFMSAC_VF_um,v4f32>;
def : PatVgrFloatVgr<int_riscv_vfmsac_vf_f32m2,VFMSAC_VF_um,v8f32>;
def : PatVgrFloatVgr<int_riscv_vfmsac_vf_f32m4,VFMSAC_VF_um,v16f32>;
def : PatVgrFloatVgr<int_riscv_vfmsac_vf_f32m8,VFMSAC_VF_um,v32f32>;

def : PatVmVgrFloatVgr<int_riscv_vfmsac_vf_f32m1_m,VFMSAC_VF_m,v4f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmsac_vf_f32m2_m,VFMSAC_VF_m,v8f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmsac_vf_f32m4_m,VFMSAC_VF_m,v16f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmsac_vf_f32m8_m,VFMSAC_VF_m,v32f32>;

defm VFNMSAC_VV : VALU_OPFVV_MulAdd<0b101111,"vfnmsac.vv">;

def : PatVgrVgrVgr<int_riscv_vfnmsac_vv_f32m1,VFNMSAC_VV_um,v4f32>;
def : PatVgrVgrVgr<int_riscv_vfnmsac_vv_f32m2,VFNMSAC_VV_um,v8f32>;
def : PatVgrVgrVgr<int_riscv_vfnmsac_vv_f32m4,VFNMSAC_VV_um,v16f32>;
def : PatVgrVgrVgr<int_riscv_vfnmsac_vv_f32m8,VFNMSAC_VV_um,v32f32>;

def : PatVmVgrVgrVgr<int_riscv_vfnmsac_vv_f32m1_m,VFNMSAC_VV_m,v4f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmsac_vv_f32m2_m,VFNMSAC_VV_m,v8f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmsac_vv_f32m4_m,VFNMSAC_VV_m,v16f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmsac_vv_f32m8_m,VFNMSAC_VV_m,v32f32>;

defm VFNMSAC_VF : VALU_OPFVF_MulAdd<0b101111,"vfnmsac.vf">;

def : PatVgrFloatVgr<int_riscv_vfnmsac_vf_f32m1,VFNMSAC_VF_um,v4f32>;
def : PatVgrFloatVgr<int_riscv_vfnmsac_vf_f32m2,VFNMSAC_VF_um,v8f32>;
def : PatVgrFloatVgr<int_riscv_vfnmsac_vf_f32m4,VFNMSAC_VF_um,v16f32>;
def : PatVgrFloatVgr<int_riscv_vfnmsac_vf_f32m8,VFNMSAC_VF_um,v32f32>;

def : PatVmVgrFloatVgr<int_riscv_vfnmsac_vf_f32m1_m,VFNMSAC_VF_m,v4f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmsac_vf_f32m2_m,VFNMSAC_VF_m,v8f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmsac_vf_f32m4_m,VFNMSAC_VF_m,v16f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmsac_vf_f32m8_m,VFNMSAC_VF_m,v32f32>;

defm VFMADD_VV : VALU_OPFVV_MulAdd<0b101000,"vfmadd.vv">;

def : PatVgrVgrVgr<int_riscv_vfmadd_vv_f32m1,VFMADD_VV_um,v4f32>;
def : PatVgrVgrVgr<int_riscv_vfmadd_vv_f32m2,VFMADD_VV_um,v8f32>;
def : PatVgrVgrVgr<int_riscv_vfmadd_vv_f32m4,VFMADD_VV_um,v16f32>;
def : PatVgrVgrVgr<int_riscv_vfmadd_vv_f32m8,VFMADD_VV_um,v32f32>;

def : PatVmVgrVgrVgr<int_riscv_vfmadd_vv_f32m1_m,VFMADD_VV_m,v4f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmadd_vv_f32m2_m,VFMADD_VV_m,v8f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmadd_vv_f32m4_m,VFMADD_VV_m,v16f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmadd_vv_f32m8_m,VFMADD_VV_m,v32f32>;

defm VFMADD_VF : VALU_OPFVF_MulAdd<0b101000,"vfmadd.vf">;

def : PatVgrFloatVgr<int_riscv_vfmadd_vf_f32m1,VFMADD_VF_um,v4f32>;
def : PatVgrFloatVgr<int_riscv_vfmadd_vf_f32m2,VFMADD_VF_um,v8f32>;
def : PatVgrFloatVgr<int_riscv_vfmadd_vf_f32m4,VFMADD_VF_um,v16f32>;
def : PatVgrFloatVgr<int_riscv_vfmadd_vf_f32m8,VFMADD_VF_um,v32f32>;

def : PatVmVgrFloatVgr<int_riscv_vfmadd_vf_f32m1_m,VFMADD_VF_m,v4f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmadd_vf_f32m2_m,VFMADD_VF_m,v8f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmadd_vf_f32m4_m,VFMADD_VF_m,v16f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmadd_vf_f32m8_m,VFMADD_VF_m,v32f32>;

defm VFNMADD_VV : VALU_OPFVV_MulAdd<0b101001,"vfnmadd.vv">;

def : PatVgrVgrVgr<int_riscv_vfnmadd_vv_f32m1,VFNMADD_VV_um,v4f32>;
def : PatVgrVgrVgr<int_riscv_vfnmadd_vv_f32m2,VFNMADD_VV_um,v8f32>;
def : PatVgrVgrVgr<int_riscv_vfnmadd_vv_f32m4,VFNMADD_VV_um,v16f32>;
def : PatVgrVgrVgr<int_riscv_vfnmadd_vv_f32m8,VFNMADD_VV_um,v32f32>;

def : PatVmVgrVgrVgr<int_riscv_vfnmadd_vv_f32m1_m,VFNMADD_VV_m,v4f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmadd_vv_f32m2_m,VFNMADD_VV_m,v8f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmadd_vv_f32m4_m,VFNMADD_VV_m,v16f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmadd_vv_f32m8_m,VFNMADD_VV_m,v32f32>;


defm VFNMADD_VF : VALU_OPFVF_MulAdd<0b101001,"vfnmadd.vf">;

def : PatVgrFloatVgr<int_riscv_vfnmadd_vf_f32m1,VFNMADD_VF_um,v4f32>;
def : PatVgrFloatVgr<int_riscv_vfnmadd_vf_f32m2,VFNMADD_VF_um,v8f32>;
def : PatVgrFloatVgr<int_riscv_vfnmadd_vf_f32m4,VFNMADD_VF_um,v16f32>;
def : PatVgrFloatVgr<int_riscv_vfnmadd_vf_f32m8,VFNMADD_VF_um,v32f32>;

def : PatVmVgrFloatVgr<int_riscv_vfnmadd_vf_f32m1_m,VFNMADD_VF_m,v4f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmadd_vf_f32m2_m,VFNMADD_VF_m,v8f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmadd_vf_f32m4_m,VFNMADD_VF_m,v16f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmadd_vf_f32m8_m,VFNMADD_VF_m,v32f32>;

defm VFMSUB_VV : VALU_OPFVV_MulAdd<0b101010,"vfmsub.vv">;

def : PatVgrVgrVgr<int_riscv_vfmsub_vv_f32m1,VFMSUB_VV_um,v4f32>;
def : PatVgrVgrVgr<int_riscv_vfmsub_vv_f32m2,VFMSUB_VV_um,v8f32>;
def : PatVgrVgrVgr<int_riscv_vfmsub_vv_f32m4,VFMSUB_VV_um,v16f32>;
def : PatVgrVgrVgr<int_riscv_vfmsub_vv_f32m8,VFMSUB_VV_um,v32f32>;

def : PatVmVgrVgrVgr<int_riscv_vfmsub_vv_f32m1_m,VFMSUB_VV_m,v4f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmsub_vv_f32m2_m,VFMSUB_VV_m,v8f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmsub_vv_f32m4_m,VFMSUB_VV_m,v16f32>;
def : PatVmVgrVgrVgr<int_riscv_vfmsub_vv_f32m8_m,VFMSUB_VV_m,v32f32>;


defm VFMSUB_VF : VALU_OPFVF_MulAdd<0b101010,"vfmsub.vf">;

def : PatVgrFloatVgr<int_riscv_vfmsub_vf_f32m1,VFMSUB_VF_um,v4f32>;
def : PatVgrFloatVgr<int_riscv_vfmsub_vf_f32m2,VFMSUB_VF_um,v8f32>;
def : PatVgrFloatVgr<int_riscv_vfmsub_vf_f32m4,VFMSUB_VF_um,v16f32>;
def : PatVgrFloatVgr<int_riscv_vfmsub_vf_f32m8,VFMSUB_VF_um,v32f32>;

def : PatVmVgrFloatVgr<int_riscv_vfmsub_vf_f32m1_m,VFMSUB_VF_m,v4f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmsub_vf_f32m2_m,VFMSUB_VF_m,v8f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmsub_vf_f32m4_m,VFMSUB_VF_m,v16f32>;
def : PatVmVgrFloatVgr<int_riscv_vfmsub_vf_f32m8_m,VFMSUB_VF_m,v32f32>;

defm VFNMSUB_VV : VALU_OPFVV_MulAdd<0b101011,"vfnmsub.vv">;

def : PatVgrVgrVgr<int_riscv_vfnmsub_vv_f32m1,VFNMSUB_VV_um,v4f32>;
def : PatVgrVgrVgr<int_riscv_vfnmsub_vv_f32m2,VFNMSUB_VV_um,v8f32>;
def : PatVgrVgrVgr<int_riscv_vfnmsub_vv_f32m4,VFNMSUB_VV_um,v16f32>;
def : PatVgrVgrVgr<int_riscv_vfnmsub_vv_f32m8,VFNMSUB_VV_um,v32f32>;

def : PatVmVgrVgrVgr<int_riscv_vfnmsub_vv_f32m1_m,VFNMSUB_VV_m,v4f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmsub_vv_f32m2_m,VFNMSUB_VV_m,v8f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmsub_vv_f32m4_m,VFNMSUB_VV_m,v16f32>;
def : PatVmVgrVgrVgr<int_riscv_vfnmsub_vv_f32m8_m,VFNMSUB_VV_m,v32f32>;

defm VFNMSUB_VF : VALU_OPFVF_MulAdd<0b101011,"vfnmsub.vf">;	

def : PatVgrFloatVgr<int_riscv_vfnmsub_vf_f32m1,VFNMSUB_VF_um,v4f32>;
def : PatVgrFloatVgr<int_riscv_vfnmsub_vf_f32m2,VFNMSUB_VF_um,v8f32>;
def : PatVgrFloatVgr<int_riscv_vfnmsub_vf_f32m4,VFNMSUB_VF_um,v16f32>;
def : PatVgrFloatVgr<int_riscv_vfnmsub_vf_f32m8,VFNMSUB_VF_um,v32f32>;

def : PatVmVgrFloatVgr<int_riscv_vfnmsub_vf_f32m1_m,VFNMSUB_VF_m,v4f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmsub_vf_f32m2_m,VFNMSUB_VF_m,v8f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmsub_vf_f32m4_m,VFNMSUB_VF_m,v16f32>;
def : PatVmVgrFloatVgr<int_riscv_vfnmsub_vf_f32m8_m,VFNMSUB_VF_m,v32f32>;	
	

/*************Vector Floating-Point Square-Root Functions****************/
defm VFSQRT_V : VALU_OPFVV_VFUNARY<0b100011,0b00000,"vfsqrt.v">;	

def : PatVgr<int_riscv_vfsqrt_v_f32m1,VFSQRT_V_um,v4f32>;
def : PatVgr<int_riscv_vfsqrt_v_f32m2,VFSQRT_V_um,v8f32>;
def : PatVgr<int_riscv_vfsqrt_v_f32m4,VFSQRT_V_um,v16f32>;
def : PatVgr<int_riscv_vfsqrt_v_f32m8,VFSQRT_V_um,v32f32>;

def : PatVmVgr<int_riscv_vfsqrt_v_f32m1_m,VFSQRT_V_m,v4f32>;
def : PatVmVgr<int_riscv_vfsqrt_v_f32m2_m,VFSQRT_V_m,v8f32>;
def : PatVmVgr<int_riscv_vfsqrt_v_f32m4_m,VFSQRT_V_m,v16f32>;
def : PatVmVgr<int_riscv_vfsqrt_v_f32m8_m,VFSQRT_V_m,v32f32>;

/*************Vector  Floating-Point MIM/MAX Functions****************/
defm VFMIN_VV : VALU_OPFVV<0b000100,"vfmin.vv">;

def : PatVgrVgr<int_riscv_vfmin_vv_f32m1,VFMIN_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vfmin_vv_f32m2,VFMIN_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vfmin_vv_f32m4,VFMIN_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vfmin_vv_f32m8,VFMIN_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfmin_vv_f32m1_m,VFMIN_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfmin_vv_f32m2_m,VFMIN_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfmin_vv_f32m4_m,VFMIN_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfmin_vv_f32m8_m,VFMIN_VV_m,v32f32>;

defm VFMIN_VF : VALU_OPFVF<0b000100,"vfmin.vf">;

def : PatVgrFloat<int_riscv_vfmin_vf_f32m1,VFMIN_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfmin_vf_f32m2,VFMIN_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfmin_vf_f32m4,VFMIN_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfmin_vf_f32m8,VFMIN_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vfmin_vf_f32m1_m,VFMIN_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfmin_vf_f32m2_m,VFMIN_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfmin_vf_f32m4_m,VFMIN_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfmin_vf_f32m8_m,VFMIN_VF_m,v32f32>;

defm VFMAX_VV : VALU_OPFVV<0b000110,"vfmax.vv">;

def : PatVgrVgr<int_riscv_vfmax_vv_f32m1,VFMAX_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vfmax_vv_f32m2,VFMAX_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vfmax_vv_f32m4,VFMAX_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vfmax_vv_f32m8,VFMAX_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfmax_vv_f32m1_m,VFMAX_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfmax_vv_f32m2_m,VFMAX_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfmax_vv_f32m4_m,VFMAX_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfmax_vv_f32m8_m,VFMAX_VV_m,v32f32>;


defm VFMAX_VF : VALU_OPFVF<0b000110,"vfmax.vf">;

def : PatVgrFloat<int_riscv_vfmax_vf_f32m1,VFMAX_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfmax_vf_f32m2,VFMAX_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfmax_vf_f32m4,VFMAX_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfmax_vf_f32m8,VFMAX_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vfmax_vf_f32m1_m,VFMAX_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfmax_vf_f32m2_m,VFMAX_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfmax_vf_f32m4_m,VFMAX_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfmax_vf_f32m8_m,VFMAX_VF_m,v32f32>;

/********vector floating-point sign-injection********/
defm VFSGNJ_VV : VALU_OPFVV<0b001000,"vfsgnj.vv">;

def : PatVgrVgr<int_riscv_vfsgnj_vv_f32m1,VFSGNJ_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vfsgnj_vv_f32m2,VFSGNJ_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vfsgnj_vv_f32m4,VFSGNJ_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vfsgnj_vv_f32m8,VFSGNJ_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfsgnj_vv_f32m1_m,VFSGNJ_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfsgnj_vv_f32m2_m,VFSGNJ_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfsgnj_vv_f32m4_m,VFSGNJ_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfsgnj_vv_f32m8_m,VFSGNJ_VV_m,v32f32>;

defm VFSGNJ_VF : VALU_OPFVF<0b001000,"vfsgnj.vf">;

def : PatVgrFloat<int_riscv_vfsgnj_vf_f32m1,VFSGNJ_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfsgnj_vf_f32m2,VFSGNJ_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfsgnj_vf_f32m4,VFSGNJ_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfsgnj_vf_f32m8,VFSGNJ_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vfsgnj_vf_f32m1_m,VFSGNJ_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfsgnj_vf_f32m2_m,VFSGNJ_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfsgnj_vf_f32m4_m,VFSGNJ_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfsgnj_vf_f32m8_m,VFSGNJ_VF_m,v32f32>;

defm VFSGNJN_VV : VALU_OPFVV<0b001001,"vfsgnjn.vv">;

def : PatVgrVgr<int_riscv_vfsgnjn_vv_f32m1,VFSGNJN_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vfsgnjn_vv_f32m2,VFSGNJN_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vfsgnjn_vv_f32m4,VFSGNJN_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vfsgnjn_vv_f32m8,VFSGNJN_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfsgnjn_vv_f32m1_m,VFSGNJN_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfsgnjn_vv_f32m2_m,VFSGNJN_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfsgnjn_vv_f32m4_m,VFSGNJN_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfsgnjn_vv_f32m8_m,VFSGNJN_VV_m,v32f32>;


defm VFSGNJN_VF : VALU_OPFVF<0b001001,"vfsgnjn.vf">;

def : PatVgrFloat<int_riscv_vfsgnjn_vf_f32m1,VFSGNJN_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfsgnjn_vf_f32m2,VFSGNJN_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfsgnjn_vf_f32m4,VFSGNJN_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfsgnjn_vf_f32m8,VFSGNJN_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vfsgnjn_vf_f32m1_m,VFSGNJN_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfsgnjn_vf_f32m2_m,VFSGNJN_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfsgnjn_vf_f32m4_m,VFSGNJN_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfsgnjn_vf_f32m8_m,VFSGNJN_VF_m,v32f32>;

defm VFSGNJX_VV : VALU_OPFVV<0b001010,"vfsgnjx.vv">;

def : PatVgrVgr<int_riscv_vfsgnjx_vv_f32m1,VFSGNJX_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vfsgnjx_vv_f32m2,VFSGNJX_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vfsgnjx_vv_f32m4,VFSGNJX_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vfsgnjx_vv_f32m8,VFSGNJX_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfsgnjx_vv_f32m1_m,VFSGNJX_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfsgnjx_vv_f32m2_m,VFSGNJX_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfsgnjx_vv_f32m4_m,VFSGNJX_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfsgnjx_vv_f32m8_m,VFSGNJX_VV_m,v32f32>;


defm VFSGNJX_VF : VALU_OPFVF<0b001010,"vfsgnjx.vf">;

def : PatVgrFloat<int_riscv_vfsgnjx_vf_f32m1,VFSGNJX_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vfsgnjx_vf_f32m2,VFSGNJX_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vfsgnjx_vf_f32m4,VFSGNJX_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vfsgnjx_vf_f32m8,VFSGNJX_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vfsgnjx_vf_f32m1_m,VFSGNJX_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vfsgnjx_vf_f32m2_m,VFSGNJX_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vfsgnjx_vf_f32m4_m,VFSGNJX_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vfsgnjx_vf_f32m8_m,VFSGNJX_VF_m,v32f32>;

/*************Vector Floating-Point Compare Functions****************/
defm VMFEQ_VV : VALU_OPFVV<0b011000,"vmfeq.vv">;

def : PatVgrVgr<int_riscv_vmfeq_vv_f32m1,VMFEQ_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vmfeq_vv_f32m2,VMFEQ_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vmfeq_vv_f32m4,VMFEQ_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vmfeq_vv_f32m8,VMFEQ_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vmfeq_vv_f32m1_m,VMFEQ_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vmfeq_vv_f32m2_m,VMFEQ_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vmfeq_vv_f32m4_m,VMFEQ_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vmfeq_vv_f32m8_m,VMFEQ_VV_m,v32f32>;

defm VMFEQ_VF : VALU_OPFVF<0b011000,"vmfeq.vf">;

def : PatVgrFloat<int_riscv_vmfeq_vf_f32m1,VMFEQ_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vmfeq_vf_f32m2,VMFEQ_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vmfeq_vf_f32m4,VMFEQ_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vmfeq_vf_f32m8,VMFEQ_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vmfeq_vf_f32m1_m,VMFEQ_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vmfeq_vf_f32m2_m,VMFEQ_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vmfeq_vf_f32m4_m,VMFEQ_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vmfeq_vf_f32m8_m,VMFEQ_VF_m,v32f32>;

defm VMFNE_VV : VALU_OPFVV<0b011100,"vmfne.vv">;

def : PatVgrVgr<int_riscv_vmfne_vv_f32m1,VMFNE_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vmfne_vv_f32m2,VMFNE_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vmfne_vv_f32m4,VMFNE_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vmfne_vv_f32m8,VMFNE_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vmfne_vv_f32m1_m,VMFNE_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vmfne_vv_f32m2_m,VMFNE_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vmfne_vv_f32m4_m,VMFNE_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vmfne_vv_f32m8_m,VMFNE_VV_m,v32f32>;

defm VMFNE_VF : VALU_OPFVF<0b011100,"vmfne.vf">;

def : PatVgrFloat<int_riscv_vmfne_vf_f32m1,VMFNE_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vmfne_vf_f32m2,VMFNE_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vmfne_vf_f32m4,VMFNE_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vmfne_vf_f32m8,VMFNE_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vmfne_vf_f32m1_m,VMFNE_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vmfne_vf_f32m2_m,VMFNE_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vmfne_vf_f32m4_m,VMFNE_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vmfne_vf_f32m8_m,VMFNE_VF_m,v32f32>;

defm VMFLT_VV : VALU_OPFVV<0b011011,"vmflt.vv">;

def : PatVgrVgr<int_riscv_vmflt_vv_f32m1,VMFLT_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vmflt_vv_f32m2,VMFLT_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vmflt_vv_f32m4,VMFLT_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vmflt_vv_f32m8,VMFLT_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vmflt_vv_f32m1_m,VMFLT_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vmflt_vv_f32m2_m,VMFLT_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vmflt_vv_f32m4_m,VMFLT_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vmflt_vv_f32m8_m,VMFLT_VV_m,v32f32>;

defm VMFLT_VF : VALU_OPFVF<0b011011,"vmflt.vf">;

def : PatVgrFloat<int_riscv_vmflt_vf_f32m1,VMFLT_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vmflt_vf_f32m2,VMFLT_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vmflt_vf_f32m4,VMFLT_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vmflt_vf_f32m8,VMFLT_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vmflt_vf_f32m1_m,VMFLT_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vmflt_vf_f32m2_m,VMFLT_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vmflt_vf_f32m4_m,VMFLT_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vmflt_vf_f32m8_m,VMFLT_VF_m,v32f32>;

defm VMFLE_VV : VALU_OPFVV<0b011001,"vmfle.vv">;

def : PatVgrVgr<int_riscv_vmfle_vv_f32m1,VMFLE_VV_um,v4f32>;
def : PatVgrVgr<int_riscv_vmfle_vv_f32m2,VMFLE_VV_um,v8f32>;
def : PatVgrVgr<int_riscv_vmfle_vv_f32m4,VMFLE_VV_um,v16f32>;
def : PatVgrVgr<int_riscv_vmfle_vv_f32m8,VMFLE_VV_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vmfle_vv_f32m1_m,VMFLE_VV_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vmfle_vv_f32m2_m,VMFLE_VV_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vmfle_vv_f32m4_m,VMFLE_VV_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vmfle_vv_f32m8_m,VMFLE_VV_m,v32f32>;

defm VMFLE_VF : VALU_OPFVF<0b011001,"vmfle.vf">;

def : PatVgrFloat<int_riscv_vmfle_vf_f32m1,VMFLE_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vmfle_vf_f32m2,VMFLE_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vmfle_vf_f32m4,VMFLE_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vmfle_vf_f32m8,VMFLE_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vmfle_vf_f32m1_m,VMFLE_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vmfle_vf_f32m2_m,VMFLE_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vmfle_vf_f32m4_m,VMFLE_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vmfle_vf_f32m8_m,VMFLE_VF_m,v32f32>;

defm VMFGT_VF : VALU_OPFVF<0b011101,"vmfgt.vf">;

def : PatVgrFloat<int_riscv_vmfgt_vf_f32m1,VMFGT_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vmfgt_vf_f32m2,VMFGT_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vmfgt_vf_f32m4,VMFGT_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vmfgt_vf_f32m8,VMFGT_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vmfgt_vf_f32m1_m,VMFGT_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vmfgt_vf_f32m2_m,VMFGT_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vmfgt_vf_f32m4_m,VMFGT_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vmfgt_vf_f32m8_m,VMFGT_VF_m,v32f32>;

defm VMFGE_VF : VALU_OPFVF<0b011111,"vmfge.vf">;

def : PatVgrFloat<int_riscv_vmfge_vf_f32m1,VMFGE_VF_um,v4f32>;
def : PatVgrFloat<int_riscv_vmfge_vf_f32m2,VMFGE_VF_um,v8f32>;
def : PatVgrFloat<int_riscv_vmfge_vf_f32m4,VMFGE_VF_um,v16f32>;
def : PatVgrFloat<int_riscv_vmfge_vf_f32m8,VMFGE_VF_um,v32f32>;

def : PatVmVgrFloat<int_riscv_vmfge_vf_f32m1_m,VMFGE_VF_m,v4f32>;
def : PatVmVgrFloat<int_riscv_vmfge_vf_f32m2_m,VMFGE_VF_m,v8f32>;
def : PatVmVgrFloat<int_riscv_vmfge_vf_f32m4_m,VMFGE_VF_m,v16f32>;
def : PatVmVgrFloat<int_riscv_vmfge_vf_f32m8_m,VMFGE_VF_m,v32f32>;

/*************Vector Floating-Point Classify Functions****************/
defm VFCLASS_V : VALU_OPFVV_VFUNARY<0b100011,0b10000,"vfclass.v">;

def : PatVgr<int_riscv_vfclass_v_f32m1,VFCLASS_V_um,v4f32>;
def : PatVgr<int_riscv_vfclass_v_f32m2,VFCLASS_V_um,v8f32>;
def : PatVgr<int_riscv_vfclass_v_f32m4,VFCLASS_V_um,v16f32>;
def : PatVgr<int_riscv_vfclass_v_f32m8,VFCLASS_V_um,v32f32>;

def : PatVmVgr<int_riscv_vfclass_v_f32m1_m,VFCLASS_V_m,v4f32>;
def : PatVmVgr<int_riscv_vfclass_v_f32m2_m,VFCLASS_V_m,v8f32>;
def : PatVmVgr<int_riscv_vfclass_v_f32m4_m,VFCLASS_V_m,v16f32>;
def : PatVmVgr<int_riscv_vfclass_v_f32m8_m,VFCLASS_V_m,v32f32>;

/*************Vector Floating-Point Merge Functions****************/
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in
def VFMERGE_VFM : RVInstVA<0b010111, 0b101, OPC_VOP,
               (outs VReg:$vd), (ins VMASK:$vm, VReg:$vs2, FPR32:$rs1),
               "vfmerge.vfm", "$vd, $vs2, $rs1, $vm">,Sched<[]>{
  bits<5> rs1;
  bits<1> vm;
  let Inst{25} = vm;
  let Inst{19-15} = rs1;
}

def : PatVmVgrFloat<int_riscv_vfmerge_vfm_f32m1,VFMERGE_VFM,v4f32>;
def : PatVmVgrFloat<int_riscv_vfmerge_vfm_f32m2,VFMERGE_VFM,v8f32>;
def : PatVmVgrFloat<int_riscv_vfmerge_vfm_f32m4,VFMERGE_VFM,v16f32>;
def : PatVmVgrFloat<int_riscv_vfmerge_vfm_f32m8,VFMERGE_VFM,v32f32>;


/*************Vector Floating-Point Move Functions****************/
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in
def VFMV_V_F : RVInstVA<0b010111, 0b101, OPC_VOP,
               (outs VReg:$vd), (ins FPR32:$rs1),
               "vfmv.v.f", "$vd, $rs1">,Sched<[]>{
  bits<5> rs1;
  let Inst{25} = 0b1;
  let vs2 = 0b00000;
  let Inst{19-15} = rs1;
}

def : Pat<(v4f32(int_riscv_vfmv_v_f32m1 FPR32:$rs1)),(v4f32(VFMV_V_F FPR32:$rs1))>;
def : Pat<(v8f32(int_riscv_vfmv_v_f32m2 FPR32:$rs1)),(v8f32(VFMV_V_F FPR32:$rs1))>;
def : Pat<(v16f32(int_riscv_vfmv_v_f32m4 FPR32:$rs1)),(v16f32(VFMV_V_F FPR32:$rs1))>;
def : Pat<(v32f32(int_riscv_vfmv_v_f32m8 FPR32:$rs1)),(v32f32(VFMV_V_F FPR32:$rs1))>;

/*************Vector Single-Width Floating-Point/Integer Type-Convert Functions****************/
defm VFCVT_XU_F_V : VALU_OPFVV_VFUNARY<0b100010,0b00000,"vfcvt.xu.f.v">;

def : PatVgr<int_riscv_vfcvt_xu_f_v_f32m1,VFCVT_XU_F_V_um,v4f32>;
def : PatVgr<int_riscv_vfcvt_xu_f_v_f32m2,VFCVT_XU_F_V_um,v8f32>;
def : PatVgr<int_riscv_vfcvt_xu_f_v_f32m4,VFCVT_XU_F_V_um,v16f32>;
def : PatVgr<int_riscv_vfcvt_xu_f_v_f32m8,VFCVT_XU_F_V_um,v32f32>;

def : PatVmVgr<int_riscv_vfcvt_xu_f_v_f32m1_m,VFCVT_XU_F_V_m,v4f32>;
def : PatVmVgr<int_riscv_vfcvt_xu_f_v_f32m2_m,VFCVT_XU_F_V_m,v8f32>;
def : PatVmVgr<int_riscv_vfcvt_xu_f_v_f32m4_m,VFCVT_XU_F_V_m,v16f32>;
def : PatVmVgr<int_riscv_vfcvt_xu_f_v_f32m8_m,VFCVT_XU_F_V_m,v32f32>;

defm VFCVT_X_F_V : VALU_OPFVV_VFUNARY<0b100010,0b00001,"vfcvt.x.f.v">;

def : PatVgr<int_riscv_vfcvt_x_f_v_f32m1,VFCVT_X_F_V_um,v4f32>;
def : PatVgr<int_riscv_vfcvt_x_f_v_f32m2,VFCVT_X_F_V_um,v8f32>;
def : PatVgr<int_riscv_vfcvt_x_f_v_f32m4,VFCVT_X_F_V_um,v16f32>;
def : PatVgr<int_riscv_vfcvt_x_f_v_f32m8,VFCVT_X_F_V_um,v32f32>;

def : PatVmVgr<int_riscv_vfcvt_x_f_v_f32m1_m,VFCVT_X_F_V_m,v4f32>;
def : PatVmVgr<int_riscv_vfcvt_x_f_v_f32m2_m,VFCVT_X_F_V_m,v8f32>;
def : PatVmVgr<int_riscv_vfcvt_x_f_v_f32m4_m,VFCVT_X_F_V_m,v16f32>;
def : PatVmVgr<int_riscv_vfcvt_x_f_v_f32m8_m,VFCVT_X_F_V_m,v32f32>;

defm VFCVT_F_XU_V : VALU_OPFVV_VFUNARY<0b100010,0b00010,"vfcvt.f.xu.v">;

def : PatVgr<int_riscv_vfcvt_f_xu_v_u32m1,VFCVT_F_XU_V_um,v4i32>;
def : PatVgr<int_riscv_vfcvt_f_xu_v_u32m2,VFCVT_F_XU_V_um,v8i32>;
def : PatVgr<int_riscv_vfcvt_f_xu_v_u32m4,VFCVT_F_XU_V_um,v16i32>;
def : PatVgr<int_riscv_vfcvt_f_xu_v_u32m8,VFCVT_F_XU_V_um,v32i32>;

def : PatVmVgr<int_riscv_vfcvt_f_xu_v_u32m1_m,VFCVT_F_XU_V_m,v4i32>;
def : PatVmVgr<int_riscv_vfcvt_f_xu_v_u32m2_m,VFCVT_F_XU_V_m,v8i32>;
def : PatVmVgr<int_riscv_vfcvt_f_xu_v_u32m4_m,VFCVT_F_XU_V_m,v16i32>;
def : PatVmVgr<int_riscv_vfcvt_f_xu_v_u32m8_m,VFCVT_F_XU_V_m,v32i32>;

defm VFCVT_F_X_V : VALU_OPFVV_VFUNARY<0b100010,0b00011,"vfcvt.f.x.v">;

def : PatVgr<int_riscv_vfcvt_f_x_v_i32m1,VFCVT_F_X_V_um,v4i32>;
def : PatVgr<int_riscv_vfcvt_f_x_v_i32m2,VFCVT_F_X_V_um,v8i32>;
def : PatVgr<int_riscv_vfcvt_f_x_v_i32m4,VFCVT_F_X_V_um,v16i32>;
def : PatVgr<int_riscv_vfcvt_f_x_v_i32m8,VFCVT_F_X_V_um,v32i32>;

def : PatVmVgr<int_riscv_vfcvt_f_x_v_i32m1_m,VFCVT_F_X_V_m,v4i32>;
def : PatVmVgr<int_riscv_vfcvt_f_x_v_i32m2_m,VFCVT_F_X_V_m,v8i32>;
def : PatVmVgr<int_riscv_vfcvt_f_x_v_i32m4_m,VFCVT_F_X_V_m,v16i32>;
def : PatVmVgr<int_riscv_vfcvt_f_x_v_i32m8_m,VFCVT_F_X_V_m,v32i32>;

/*************Vector Widening Floating-Point/Integer Type-Convert Functions****************/
defm VFWCVT_F_XU_V : VALU_OPFVV_VFUNARY<0b100010,0b01010,"vfwcvt.f.xu.v">;

def : PatVgr<int_riscv_vfwcvt_f_xu_v_u16m1,VFWCVT_F_XU_V_um,v8i16>;
def : PatVgr<int_riscv_vfwcvt_f_xu_v_u16m2,VFWCVT_F_XU_V_um,v16i16>;
def : PatVgr<int_riscv_vfwcvt_f_xu_v_u16m4,VFWCVT_F_XU_V_um,v32i16>;

def : PatVmVgr<int_riscv_vfwcvt_f_xu_v_u16m1_m,VFWCVT_F_XU_V_m,v8i16>;
def : PatVmVgr<int_riscv_vfwcvt_f_xu_v_u16m2_m,VFWCVT_F_XU_V_m,v16i16>;
def : PatVmVgr<int_riscv_vfwcvt_f_xu_v_u16m4_m,VFWCVT_F_XU_V_m,v32i16>;

defm VFWCVT_F_X_V : VALU_OPFVV_VFUNARY<0b100010,0b01011,"vfwcvt.f.x.v">;

def : PatVgr<int_riscv_vfwcvt_f_x_v_i16m1,VFWCVT_F_X_V_um,v8i16>;
def : PatVgr<int_riscv_vfwcvt_f_x_v_i16m2,VFWCVT_F_X_V_um,v16i16>;
def : PatVgr<int_riscv_vfwcvt_f_x_v_i16m4,VFWCVT_F_X_V_um,v32i16>;

def : PatVmVgr<int_riscv_vfwcvt_f_x_v_i16m1_m,VFWCVT_F_X_V_m,v8i16>;
def : PatVmVgr<int_riscv_vfwcvt_f_x_v_i16m2_m,VFWCVT_F_X_V_m,v16i16>;
def : PatVmVgr<int_riscv_vfwcvt_f_x_v_i16m4_m,VFWCVT_F_X_V_m,v32i16>;

/*************Vector Narrowing Floating-Point/Integer Type-Convert Functions****************/
defm VFNCVT_XU_F_W : VALU_OPFVV_VFUNARY<0b100010,0b10000,"vfncvt.xu.f.w">;

def : PatVgr<int_riscv_vfncvt_xu_f_w_f32m2,VFNCVT_XU_F_W_um,v8f32>;
def : PatVgr<int_riscv_vfncvt_xu_f_w_f32m4,VFNCVT_XU_F_W_um,v16f32>;
def : PatVgr<int_riscv_vfncvt_xu_f_w_f32m8,VFNCVT_XU_F_W_um,v32f32>;

def : PatVmVgr<int_riscv_vfncvt_xu_f_w_f32m2_m,VFNCVT_XU_F_W_m,v8f32>;
def : PatVmVgr<int_riscv_vfncvt_xu_f_w_f32m4_m,VFNCVT_XU_F_W_m,v16f32>;
def : PatVmVgr<int_riscv_vfncvt_xu_f_w_f32m8_m,VFNCVT_XU_F_W_m,v32f32>;

defm VFNCVT_X_F_W : VALU_OPFVV_VFUNARY<0b100010,0b10001,"vfncvt.x.f.w">;

def : PatVgr<int_riscv_vfncvt_x_f_w_f32m2,VFNCVT_X_F_W_um,v8f32>;
def : PatVgr<int_riscv_vfncvt_x_f_w_f32m4,VFNCVT_X_F_W_um,v16f32>;
def : PatVgr<int_riscv_vfncvt_x_f_w_f32m8,VFNCVT_X_F_W_um,v32f32>;

def : PatVmVgr<int_riscv_vfncvt_x_f_w_f32m2_m,VFNCVT_X_F_W_m,v8f32>;
def : PatVmVgr<int_riscv_vfncvt_x_f_w_f32m4_m,VFNCVT_X_F_W_m,v16f32>;
def : PatVmVgr<int_riscv_vfncvt_x_f_w_f32m8_m,VFNCVT_X_F_W_m,v32f32>;

/*************Vector Single-Width Integer Reduction Functions****************/
defm VREDSUM_VS : VALU_OPMVV<0b000000,"vredsum.vs">;

def : PatVgrVgr<int_riscv_vredsum_vs_8m1,VREDSUM_VS_um,v16i8>;
def : PatVgrVgr<int_riscv_vredsum_vs_8m2,VREDSUM_VS_um,v32i8>;
def : PatVgrVgr<int_riscv_vredsum_vs_8m4,VREDSUM_VS_um,v64i8>;
def : PatVgrVgr<int_riscv_vredsum_vs_8m8,VREDSUM_VS_um,v128i8>;

def : PatVgrVgr<int_riscv_vredsum_vs_16m1,VREDSUM_VS_um,v8i16>;
def : PatVgrVgr<int_riscv_vredsum_vs_16m2,VREDSUM_VS_um,v16i16>;
def : PatVgrVgr<int_riscv_vredsum_vs_16m4,VREDSUM_VS_um,v32i16>;
def : PatVgrVgr<int_riscv_vredsum_vs_16m8,VREDSUM_VS_um,v64i16>;

def : PatVgrVgr<int_riscv_vredsum_vs_32m1,VREDSUM_VS_um,v4i32>;
def : PatVgrVgr<int_riscv_vredsum_vs_32m2,VREDSUM_VS_um,v8i32>;
def : PatVgrVgr<int_riscv_vredsum_vs_32m4,VREDSUM_VS_um,v16i32>;
def : PatVgrVgr<int_riscv_vredsum_vs_32m8,VREDSUM_VS_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vredsum_vs_8m1_m,VREDSUM_VS_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vredsum_vs_8m2_m,VREDSUM_VS_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vredsum_vs_8m4_m,VREDSUM_VS_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vredsum_vs_8m8_m,VREDSUM_VS_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vredsum_vs_16m1_m,VREDSUM_VS_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vredsum_vs_16m2_m,VREDSUM_VS_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vredsum_vs_16m4_m,VREDSUM_VS_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vredsum_vs_16m8_m,VREDSUM_VS_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vredsum_vs_32m1_m,VREDSUM_VS_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vredsum_vs_32m2_m,VREDSUM_VS_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vredsum_vs_32m4_m,VREDSUM_VS_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vredsum_vs_32m8_m,VREDSUM_VS_m,v32i32>;

defm VREDMAXU_VS : VALU_OPMVV<0b000110,"vredmaxu.vs">;

def : PatVgrVgr<int_riscv_vredmaxu_vs_u8m1,VREDMAXU_VS_um,v16i8>;
def : PatVgrVgr<int_riscv_vredmaxu_vs_u8m2,VREDMAXU_VS_um,v32i8>;
def : PatVgrVgr<int_riscv_vredmaxu_vs_u8m4,VREDMAXU_VS_um,v64i8>;
def : PatVgrVgr<int_riscv_vredmaxu_vs_u8m8,VREDMAXU_VS_um,v128i8>;

def : PatVgrVgr<int_riscv_vredmaxu_vs_u16m1,VREDMAXU_VS_um,v8i16>;
def : PatVgrVgr<int_riscv_vredmaxu_vs_u16m2,VREDMAXU_VS_um,v16i16>;
def : PatVgrVgr<int_riscv_vredmaxu_vs_u16m4,VREDMAXU_VS_um,v32i16>;
def : PatVgrVgr<int_riscv_vredmaxu_vs_u16m8,VREDMAXU_VS_um,v64i16>;

def : PatVgrVgr<int_riscv_vredmaxu_vs_u32m1,VREDMAXU_VS_um,v4i32>;
def : PatVgrVgr<int_riscv_vredmaxu_vs_u32m2,VREDMAXU_VS_um,v8i32>;
def : PatVgrVgr<int_riscv_vredmaxu_vs_u32m4,VREDMAXU_VS_um,v16i32>;
def : PatVgrVgr<int_riscv_vredmaxu_vs_u32m8,VREDMAXU_VS_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u8m1_m,VREDMAXU_VS_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u8m2_m,VREDMAXU_VS_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u8m4_m,VREDMAXU_VS_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u8m8_m,VREDMAXU_VS_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u16m1_m,VREDMAXU_VS_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u16m2_m,VREDMAXU_VS_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u16m4_m,VREDMAXU_VS_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u16m8_m,VREDMAXU_VS_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u32m1_m,VREDMAXU_VS_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u32m2_m,VREDMAXU_VS_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u32m4_m,VREDMAXU_VS_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vredmaxu_vs_u32m8_m,VREDMAXU_VS_m,v32i32>;

defm VREDMAX_VS : VALU_OPMVV<0b000111,"vredmax.vs">;

def : PatVgrVgr<int_riscv_vredmax_vs_i8m1,VREDMAX_VS_um,v16i8>;
def : PatVgrVgr<int_riscv_vredmax_vs_i8m2,VREDMAX_VS_um,v32i8>;
def : PatVgrVgr<int_riscv_vredmax_vs_i8m4,VREDMAX_VS_um,v64i8>;
def : PatVgrVgr<int_riscv_vredmax_vs_i8m8,VREDMAX_VS_um,v128i8>;

def : PatVgrVgr<int_riscv_vredmax_vs_i16m1,VREDMAX_VS_um,v8i16>;
def : PatVgrVgr<int_riscv_vredmax_vs_i16m2,VREDMAX_VS_um,v16i16>;
def : PatVgrVgr<int_riscv_vredmax_vs_i16m4,VREDMAX_VS_um,v32i16>;
def : PatVgrVgr<int_riscv_vredmax_vs_i16m8,VREDMAX_VS_um,v64i16>;

def : PatVgrVgr<int_riscv_vredmax_vs_i32m1,VREDMAX_VS_um,v4i32>;
def : PatVgrVgr<int_riscv_vredmax_vs_i32m2,VREDMAX_VS_um,v8i32>;
def : PatVgrVgr<int_riscv_vredmax_vs_i32m4,VREDMAX_VS_um,v16i32>;
def : PatVgrVgr<int_riscv_vredmax_vs_i32m8,VREDMAX_VS_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vredmax_vs_i8m1_m,VREDMAX_VS_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vredmax_vs_i8m2_m,VREDMAX_VS_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vredmax_vs_i8m4_m,VREDMAX_VS_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vredmax_vs_i8m8_m,VREDMAX_VS_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vredmax_vs_i16m1_m,VREDMAX_VS_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vredmax_vs_i16m2_m,VREDMAX_VS_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vredmax_vs_i16m4_m,VREDMAX_VS_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vredmax_vs_i16m8_m,VREDMAX_VS_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vredmax_vs_i32m1_m,VREDMAX_VS_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vredmax_vs_i32m2_m,VREDMAX_VS_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vredmax_vs_i32m4_m,VREDMAX_VS_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vredmax_vs_i32m8_m,VREDMAX_VS_m,v32i32>;

defm VREDMINU_VS : VALU_OPMVV<0b000100,"vredminu.vs">;

def : PatVgrVgr<int_riscv_vredminu_vs_u8m1,VREDMINU_VS_um,v16i8>;
def : PatVgrVgr<int_riscv_vredminu_vs_u8m2,VREDMINU_VS_um,v32i8>;
def : PatVgrVgr<int_riscv_vredminu_vs_u8m4,VREDMINU_VS_um,v64i8>;
def : PatVgrVgr<int_riscv_vredminu_vs_u8m8,VREDMINU_VS_um,v128i8>;

def : PatVgrVgr<int_riscv_vredminu_vs_u16m1,VREDMINU_VS_um,v8i16>;
def : PatVgrVgr<int_riscv_vredminu_vs_u16m2,VREDMINU_VS_um,v16i16>;
def : PatVgrVgr<int_riscv_vredminu_vs_u16m4,VREDMINU_VS_um,v32i16>;
def : PatVgrVgr<int_riscv_vredminu_vs_u16m8,VREDMINU_VS_um,v64i16>;

def : PatVgrVgr<int_riscv_vredminu_vs_u32m1,VREDMINU_VS_um,v4i32>;
def : PatVgrVgr<int_riscv_vredminu_vs_u32m2,VREDMINU_VS_um,v8i32>;
def : PatVgrVgr<int_riscv_vredminu_vs_u32m4,VREDMINU_VS_um,v16i32>;
def : PatVgrVgr<int_riscv_vredminu_vs_u32m8,VREDMINU_VS_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vredminu_vs_u8m1_m,VREDMINU_VS_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vredminu_vs_u8m2_m,VREDMINU_VS_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vredminu_vs_u8m4_m,VREDMINU_VS_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vredminu_vs_u8m8_m,VREDMINU_VS_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vredminu_vs_u16m1_m,VREDMINU_VS_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vredminu_vs_u16m2_m,VREDMINU_VS_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vredminu_vs_u16m4_m,VREDMINU_VS_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vredminu_vs_u16m8_m,VREDMINU_VS_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vredminu_vs_u32m1_m,VREDMINU_VS_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vredminu_vs_u32m2_m,VREDMINU_VS_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vredminu_vs_u32m4_m,VREDMINU_VS_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vredminu_vs_u32m8_m,VREDMINU_VS_m,v32i32>;

defm VREDMIN_VS : VALU_OPMVV<0b000101,"vredmin.vs">;

def : PatVgrVgr<int_riscv_vredmin_vs_i8m1,VREDMIN_VS_um,v16i8>;
def : PatVgrVgr<int_riscv_vredmin_vs_i8m2,VREDMIN_VS_um,v32i8>;
def : PatVgrVgr<int_riscv_vredmin_vs_i8m4,VREDMIN_VS_um,v64i8>;
def : PatVgrVgr<int_riscv_vredmin_vs_i8m8,VREDMIN_VS_um,v128i8>;

def : PatVgrVgr<int_riscv_vredmin_vs_i16m1,VREDMIN_VS_um,v8i16>;
def : PatVgrVgr<int_riscv_vredmin_vs_i16m2,VREDMIN_VS_um,v16i16>;
def : PatVgrVgr<int_riscv_vredmin_vs_i16m4,VREDMIN_VS_um,v32i16>;
def : PatVgrVgr<int_riscv_vredmin_vs_i16m8,VREDMIN_VS_um,v64i16>;

def : PatVgrVgr<int_riscv_vredmin_vs_i32m1,VREDMIN_VS_um,v4i32>;
def : PatVgrVgr<int_riscv_vredmin_vs_i32m2,VREDMIN_VS_um,v8i32>;
def : PatVgrVgr<int_riscv_vredmin_vs_i32m4,VREDMIN_VS_um,v16i32>;
def : PatVgrVgr<int_riscv_vredmin_vs_i32m8,VREDMIN_VS_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vredmin_vs_i8m1_m,VREDMIN_VS_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vredmin_vs_i8m2_m,VREDMIN_VS_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vredmin_vs_i8m4_m,VREDMIN_VS_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vredmin_vs_i8m8_m,VREDMIN_VS_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vredmin_vs_i16m1_m,VREDMIN_VS_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vredmin_vs_i16m2_m,VREDMIN_VS_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vredmin_vs_i16m4_m,VREDMIN_VS_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vredmin_vs_i16m8_m,VREDMIN_VS_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vredmin_vs_i32m1_m,VREDMIN_VS_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vredmin_vs_i32m2_m,VREDMIN_VS_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vredmin_vs_i32m4_m,VREDMIN_VS_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vredmin_vs_i32m8_m,VREDMIN_VS_m,v32i32>;

defm VREDAND_VS : VALU_OPMVV<0b000001,"vredand.vs">;

def : PatVgrVgr<int_riscv_vredand_vs_8m1,VREDAND_VS_um,v16i8>;
def : PatVgrVgr<int_riscv_vredand_vs_8m2,VREDAND_VS_um,v32i8>;
def : PatVgrVgr<int_riscv_vredand_vs_8m4,VREDAND_VS_um,v64i8>;
def : PatVgrVgr<int_riscv_vredand_vs_8m8,VREDAND_VS_um,v128i8>;

def : PatVgrVgr<int_riscv_vredand_vs_16m1,VREDAND_VS_um,v8i16>;
def : PatVgrVgr<int_riscv_vredand_vs_16m2,VREDAND_VS_um,v16i16>;
def : PatVgrVgr<int_riscv_vredand_vs_16m4,VREDAND_VS_um,v32i16>;
def : PatVgrVgr<int_riscv_vredand_vs_16m8,VREDAND_VS_um,v64i16>;

def : PatVgrVgr<int_riscv_vredand_vs_32m1,VREDAND_VS_um,v4i32>;
def : PatVgrVgr<int_riscv_vredand_vs_32m2,VREDAND_VS_um,v8i32>;
def : PatVgrVgr<int_riscv_vredand_vs_32m4,VREDAND_VS_um,v16i32>;
def : PatVgrVgr<int_riscv_vredand_vs_32m8,VREDAND_VS_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vredand_vs_8m1_m,VREDAND_VS_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vredand_vs_8m2_m,VREDAND_VS_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vredand_vs_8m4_m,VREDAND_VS_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vredand_vs_8m8_m,VREDAND_VS_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vredand_vs_16m1_m,VREDAND_VS_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vredand_vs_16m2_m,VREDAND_VS_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vredand_vs_16m4_m,VREDAND_VS_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vredand_vs_16m8_m,VREDAND_VS_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vredand_vs_32m1_m,VREDAND_VS_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vredand_vs_32m2_m,VREDAND_VS_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vredand_vs_32m4_m,VREDAND_VS_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vredand_vs_32m8_m,VREDAND_VS_m,v32i32>;

defm VREDOR_VS : VALU_OPMVV<0b000010,"vredor.vs">;

def : PatVgrVgr<int_riscv_vredor_vs_8m1,VREDOR_VS_um,v16i8>;
def : PatVgrVgr<int_riscv_vredor_vs_8m2,VREDOR_VS_um,v32i8>;
def : PatVgrVgr<int_riscv_vredor_vs_8m4,VREDOR_VS_um,v64i8>;
def : PatVgrVgr<int_riscv_vredor_vs_8m8,VREDOR_VS_um,v128i8>;

def : PatVgrVgr<int_riscv_vredor_vs_16m1,VREDOR_VS_um,v8i16>;
def : PatVgrVgr<int_riscv_vredor_vs_16m2,VREDOR_VS_um,v16i16>;
def : PatVgrVgr<int_riscv_vredor_vs_16m4,VREDOR_VS_um,v32i16>;
def : PatVgrVgr<int_riscv_vredor_vs_16m8,VREDOR_VS_um,v64i16>;

def : PatVgrVgr<int_riscv_vredor_vs_32m1,VREDOR_VS_um,v4i32>;
def : PatVgrVgr<int_riscv_vredor_vs_32m2,VREDOR_VS_um,v8i32>;
def : PatVgrVgr<int_riscv_vredor_vs_32m4,VREDOR_VS_um,v16i32>;
def : PatVgrVgr<int_riscv_vredor_vs_32m8,VREDOR_VS_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vredor_vs_8m1_m,VREDOR_VS_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vredor_vs_8m2_m,VREDOR_VS_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vredor_vs_8m4_m,VREDOR_VS_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vredor_vs_8m8_m,VREDOR_VS_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vredor_vs_16m1_m,VREDOR_VS_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vredor_vs_16m2_m,VREDOR_VS_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vredor_vs_16m4_m,VREDOR_VS_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vredor_vs_16m8_m,VREDOR_VS_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vredor_vs_32m1_m,VREDOR_VS_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vredor_vs_32m2_m,VREDOR_VS_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vredor_vs_32m4_m,VREDOR_VS_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vredor_vs_32m8_m,VREDOR_VS_m,v32i32>;

defm VREDXOR_VS : VALU_OPMVV<0b000011,"vredxor.vs">;

def : PatVgrVgr<int_riscv_vredxor_vs_8m1,VREDXOR_VS_um,v16i8>;
def : PatVgrVgr<int_riscv_vredxor_vs_8m2,VREDXOR_VS_um,v32i8>;
def : PatVgrVgr<int_riscv_vredxor_vs_8m4,VREDXOR_VS_um,v64i8>;
def : PatVgrVgr<int_riscv_vredxor_vs_8m8,VREDXOR_VS_um,v128i8>;

def : PatVgrVgr<int_riscv_vredxor_vs_16m1,VREDXOR_VS_um,v8i16>;
def : PatVgrVgr<int_riscv_vredxor_vs_16m2,VREDXOR_VS_um,v16i16>;
def : PatVgrVgr<int_riscv_vredxor_vs_16m4,VREDXOR_VS_um,v32i16>;
def : PatVgrVgr<int_riscv_vredxor_vs_16m8,VREDXOR_VS_um,v64i16>;

def : PatVgrVgr<int_riscv_vredxor_vs_32m1,VREDXOR_VS_um,v4i32>;
def : PatVgrVgr<int_riscv_vredxor_vs_32m2,VREDXOR_VS_um,v8i32>;
def : PatVgrVgr<int_riscv_vredxor_vs_32m4,VREDXOR_VS_um,v16i32>;
def : PatVgrVgr<int_riscv_vredxor_vs_32m8,VREDXOR_VS_um,v32i32>;

def : PatVmVgrVgr<int_riscv_vredxor_vs_8m1_m,VREDXOR_VS_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vredxor_vs_8m2_m,VREDXOR_VS_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vredxor_vs_8m4_m,VREDXOR_VS_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vredxor_vs_8m8_m,VREDXOR_VS_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vredxor_vs_16m1_m,VREDXOR_VS_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vredxor_vs_16m2_m,VREDXOR_VS_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vredxor_vs_16m4_m,VREDXOR_VS_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vredxor_vs_16m8_m,VREDXOR_VS_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vredxor_vs_32m1_m,VREDXOR_VS_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vredxor_vs_32m2_m,VREDXOR_VS_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vredxor_vs_32m4_m,VREDXOR_VS_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vredxor_vs_32m8_m,VREDXOR_VS_m,v32i32>;


/*************Vector Widening Integer Reduction Functions****************/
defm VWREDSUMU_VS : VALU_OPIVV<0b110000,"vwredsumu.vs">;

def : PatWidVgrVgr<int_riscv_vwredsumu_vs_u8m1,VWREDSUMU_VS_um,v16i8,v16i16>;
def : PatWidVgrVgr<int_riscv_vwredsumu_vs_u8m2,VWREDSUMU_VS_um,v32i8,v32i16>;
def : PatWidVgrVgr<int_riscv_vwredsumu_vs_u8m4,VWREDSUMU_VS_um,v64i8,v64i16>;

def : PatWidVgrVgr<int_riscv_vwredsumu_vs_u16m1,VWREDSUMU_VS_um,v8i16,v8i32>;
def : PatWidVgrVgr<int_riscv_vwredsumu_vs_u16m2,VWREDSUMU_VS_um,v16i16,v16i32>;
def : PatWidVgrVgr<int_riscv_vwredsumu_vs_u16m4,VWREDSUMU_VS_um,v32i16,v32i32>;

def : PatVmWidVgrVgr<int_riscv_vwredsumu_vs_u8m1_m,VWREDSUMU_VS_m,v16i8,v16i16>;
def : PatVmWidVgrVgr<int_riscv_vwredsumu_vs_u8m2_m,VWREDSUMU_VS_m,v32i8,v32i16>;
def : PatVmWidVgrVgr<int_riscv_vwredsumu_vs_u8m4_m,VWREDSUMU_VS_m,v64i8,v64i16>;

def : PatVmWidVgrVgr<int_riscv_vwredsumu_vs_u16m1_m,VWREDSUMU_VS_m,v8i16,v8i32>;
def : PatVmWidVgrVgr<int_riscv_vwredsumu_vs_u16m2_m,VWREDSUMU_VS_m,v16i16,v16i32>;
def : PatVmWidVgrVgr<int_riscv_vwredsumu_vs_u16m4_m,VWREDSUMU_VS_m,v32i16,v32i32>;

defm VWREDSUM_VS : VALU_OPIVV<0b110001,"vwredsum.vs">;

def : PatWidVgrVgr<int_riscv_vwredsum_vs_i8m1,VWREDSUM_VS_um,v16i8,v16i16>;
def : PatWidVgrVgr<int_riscv_vwredsum_vs_i8m2,VWREDSUM_VS_um,v32i8,v32i16>;
def : PatWidVgrVgr<int_riscv_vwredsum_vs_i8m4,VWREDSUM_VS_um,v64i8,v64i16>;

def : PatWidVgrVgr<int_riscv_vwredsum_vs_i16m1,VWREDSUM_VS_um,v8i16,v8i32>;
def : PatWidVgrVgr<int_riscv_vwredsum_vs_i16m2,VWREDSUM_VS_um,v16i16,v16i32>;
def : PatWidVgrVgr<int_riscv_vwredsum_vs_i16m4,VWREDSUM_VS_um,v32i16,v32i32>;

def : PatVmWidVgrVgr<int_riscv_vwredsum_vs_i8m1_m,VWREDSUM_VS_m,v16i8,v16i16>;
def : PatVmWidVgrVgr<int_riscv_vwredsum_vs_i8m2_m,VWREDSUM_VS_m,v32i8,v32i16>;
def : PatVmWidVgrVgr<int_riscv_vwredsum_vs_i8m4_m,VWREDSUM_VS_m,v64i8,v64i16>;

def : PatVmWidVgrVgr<int_riscv_vwredsum_vs_i16m1_m,VWREDSUM_VS_m,v8i16,v8i32>;
def : PatVmWidVgrVgr<int_riscv_vwredsum_vs_i16m2_m,VWREDSUM_VS_m,v16i16,v16i32>;
def : PatVmWidVgrVgr<int_riscv_vwredsum_vs_i16m4_m,VWREDSUM_VS_m,v32i16,v32i32>;

/*************Vector Single-Width Floting-Point Reduction Functions****************/
defm VFREDOSUM_VS : VALU_OPFVV<0b000011,"vfredosum.vs">;

def : PatVgrVgr<int_riscv_vfredosum_vs_f32m1,VFREDOSUM_VS_um,v4f32>;
def : PatVgrVgr<int_riscv_vfredosum_vs_f32m2,VFREDOSUM_VS_um,v8f32>;
def : PatVgrVgr<int_riscv_vfredosum_vs_f32m4,VFREDOSUM_VS_um,v16f32>;
def : PatVgrVgr<int_riscv_vfredosum_vs_f32m8,VFREDOSUM_VS_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfredosum_vs_f32m1_m,VFREDOSUM_VS_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfredosum_vs_f32m2_m,VFREDOSUM_VS_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfredosum_vs_f32m4_m,VFREDOSUM_VS_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfredosum_vs_f32m8_m,VFREDOSUM_VS_m,v32f32>;

defm VFREDSUM_VS : VALU_OPFVV<0b000001,"vfredsum.vs">;

def : PatVgrVgr<int_riscv_vfredsum_vs_f32m1,VFREDSUM_VS_um,v4f32>;
def : PatVgrVgr<int_riscv_vfredsum_vs_f32m2,VFREDSUM_VS_um,v8f32>;
def : PatVgrVgr<int_riscv_vfredsum_vs_f32m4,VFREDSUM_VS_um,v16f32>;
def : PatVgrVgr<int_riscv_vfredsum_vs_f32m8,VFREDSUM_VS_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfredsum_vs_f32m1_m,VFREDSUM_VS_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfredsum_vs_f32m2_m,VFREDSUM_VS_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfredsum_vs_f32m4_m,VFREDSUM_VS_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfredsum_vs_f32m8_m,VFREDSUM_VS_m,v32f32>;

defm VFREDMAX_VS : VALU_OPFVV<0b000111,"vfredmax.vs">;

def : PatVgrVgr<int_riscv_vfredmax_vs_f32m1,VFREDMAX_VS_um,v4f32>;
def : PatVgrVgr<int_riscv_vfredmax_vs_f32m2,VFREDMAX_VS_um,v8f32>;
def : PatVgrVgr<int_riscv_vfredmax_vs_f32m4,VFREDMAX_VS_um,v16f32>;
def : PatVgrVgr<int_riscv_vfredmax_vs_f32m8,VFREDMAX_VS_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfredmax_vs_f32m1_m,VFREDMAX_VS_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfredmax_vs_f32m2_m,VFREDMAX_VS_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfredmax_vs_f32m4_m,VFREDMAX_VS_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfredmax_vs_f32m8_m,VFREDMAX_VS_m,v32f32>;

defm VFREDMIN_VS : VALU_OPFVV<0b000101,"vfredmin.vs">;

def : PatVgrVgr<int_riscv_vfredmin_vs_f32m1,VFREDMIN_VS_um,v4f32>;
def : PatVgrVgr<int_riscv_vfredmin_vs_f32m2,VFREDMIN_VS_um,v8f32>;
def : PatVgrVgr<int_riscv_vfredmin_vs_f32m4,VFREDMIN_VS_um,v16f32>;
def : PatVgrVgr<int_riscv_vfredmin_vs_f32m8,VFREDMIN_VS_um,v32f32>;

def : PatVmVgrVgr<int_riscv_vfredmin_vs_f32m1_m,VFREDMIN_VS_m,v4f32>;
def : PatVmVgrVgr<int_riscv_vfredmin_vs_f32m2_m,VFREDMIN_VS_m,v8f32>;
def : PatVmVgrVgr<int_riscv_vfredmin_vs_f32m4_m,VFREDMIN_VS_m,v16f32>;
def : PatVmVgrVgr<int_riscv_vfredmin_vs_f32m8_m,VFREDMIN_VS_m,v32f32>;

/*************Vector Mask-Register Logical Functions****************/
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in{
class VALU_OPMVV_NOVM<bits<6> funct6,string opcodestr>
		: RVInstVA<funct6,0b010,OPC_VOP,(outs VReg:$vd),
		  (ins VReg:$vs2, VReg:$vs1),opcodestr,"$vd, $vs2, $vs1">,Sched<[]>{
		  bits<5> vs1;
		  let Inst{25} = 0b1;
		  let Inst{19-15} = vs1;
		  }
}

def VMAND_MM : VALU_OPMVV_NOVM<0b011001,"vmand.mm">;
def : PatVgrVgr<int_riscv_vmand_mm,VMAND_MM,v16i8>;

def VMNAND_MM : VALU_OPMVV_NOVM<0b011101,"vmnand.mm">;
def : PatVgrVgr<int_riscv_vmnand_mm,VMNAND_MM,v16i8>;

def VMANDNOT_MM : VALU_OPMVV_NOVM<0b011000,"vmandnot.mm">;
def : PatVgrVgr<int_riscv_vmandnot_mm,VMANDNOT_MM,v16i8>;

def VMXOR_MM : VALU_OPMVV_NOVM<0b011011,"vmxor.mm">;
def : PatVgrVgr<int_riscv_vmxor_mm,VMXOR_MM,v16i8>;

def VMOR_MM : VALU_OPMVV_NOVM<0b011010,"vmor.mm">;
def : PatVgrVgr<int_riscv_vmor_mm,VMOR_MM,v16i8>;

def VMNOR_MM : VALU_OPMVV_NOVM<0b011110,"vmnor.mm">;
def : PatVgrVgr<int_riscv_vmnor_mm,VMNOR_MM,v16i8>;

def VMORNOT_MM : VALU_OPMVV_NOVM<0b011100,"vmornot.mm">;
def : PatVgrVgr<int_riscv_vmornot_mm,VMORNOT_MM,v16i8>;

def VMXNOR_MM : VALU_OPMVV_NOVM<0b011111,"vmxnor.mm">;
def : PatVgrVgr<int_riscv_vmxnor_mm,VMXNOR_MM,v16i8>;


/*************Vector Mask Population Functions****************/
defm VPOPC_M : VALU_OPMVV_VWXUNARY<0b010000,0b10000,"vpopc.m">;

def : PatVgr<int_riscv_vpopc_m,VPOPC_M_um,v16i8>;
def : PatVmVgr<int_riscv_vpopc_m_m,VPOPC_M_m,v16i8>;

/*************Vector find-first-set mask bit Functions****************/
defm VFIRST_M : VALU_OPMVV_VWXUNARY<0b010000,0b10001,"vfirst.m">;
def : PatVgr<int_riscv_vfirst_m,VFIRST_M_um,v16i8>;
def : PatVmVgr<int_riscv_vfirst_m_m,VFIRST_M_m,v16i8>;

/*************Vector set-before-first mask bit Functions****************/
defm VMSBF_M : VALU_OPMVV_VMUNARY<0b010000,0b00001,"vmsbf.m">;
def : PatVgr<int_riscv_vmsbf_m,VMSBF_M_um,v16i8>;
def : PatVmVgr<int_riscv_vmsbf_m_m,VMSBF_M_m,v16i8>;

/*************Vector set-including-first mask bit Functions****************/
defm VMSIF_M : VALU_OPMVV_VMUNARY<0b010000,0b00011,"vmsif.m">;
def : PatVgr<int_riscv_vmsif_m,VMSIF_M_um,v16i8>;
def : PatVmVgr<int_riscv_vmsif_m_m,VMSIF_M_m,v16i8>;

/*************Vector set-only-first mask bit Functions****************/
defm VMSOF_M : VALU_OPMVV_VMUNARY<0b010000,0b00010,"vmsof.m">;
def : PatVgr<int_riscv_vmsof_m,VMSOF_M_um,v16i8>;
def : PatVmVgr<int_riscv_vmsof_m_m,VMSOF_M_m,v16i8>;

/*************Vector iota Functions****************/
defm VIOTA_M : VALU_OPMVV_VMUNARY<0b010100,0b10000,"viota.m">;
def : PatVgr<int_riscv_viota_m,VIOTA_M_um,v16i8>;
def : PatVmVgr<int_riscv_viota_m_m,VIOTA_M_m,v16i8>;

/*************Vector vid Functions****************/
defm VID_V : VALU_OPIVV_VID<0b10001,"vid.v">;

def : Pat<(int_riscv_vid_v_u8m1),(VID_V_um)>;
def : Pat<(int_riscv_vid_v_u8m2),(VID_V_um)>;
def : Pat<(int_riscv_vid_v_u8m4),(VID_V_um)>;
def : Pat<(int_riscv_vid_v_u8m8),(VID_V_um)>;

def : Pat<(int_riscv_vid_v_u16m1),(VID_V_um)>;
def : Pat<(int_riscv_vid_v_u16m2),(VID_V_um)>;
def : Pat<(int_riscv_vid_v_u16m4),(VID_V_um)>;
def : Pat<(int_riscv_vid_v_u16m8),(VID_V_um)>;

def : Pat<(int_riscv_vid_v_u32m1),(VID_V_um)>;
def : Pat<(int_riscv_vid_v_u32m2),(VID_V_um)>;
def : Pat<(int_riscv_vid_v_u32m4),(VID_V_um)>;
def : Pat<(int_riscv_vid_v_u32m8),(VID_V_um)>;

def : Pat<(int_riscv_vid_v_u8m1_m VMASK:$vm),(VID_V_m VMASK:$vm)>;
def : Pat<(int_riscv_vid_v_u8m2_m VMASK:$vm),(VID_V_m VMASK:$vm)>;
def : Pat<(int_riscv_vid_v_u8m4_m VMASK:$vm),(VID_V_m VMASK:$vm)>;
def : Pat<(int_riscv_vid_v_u8m8_m VMASK:$vm),(VID_V_m VMASK:$vm)>;

def : Pat<(int_riscv_vid_v_u16m1_m VMASK:$vm),(VID_V_m VMASK:$vm)>;
def : Pat<(int_riscv_vid_v_u16m2_m VMASK:$vm),(VID_V_m VMASK:$vm)>;
def : Pat<(int_riscv_vid_v_u16m4_m VMASK:$vm),(VID_V_m VMASK:$vm)>;
def : Pat<(int_riscv_vid_v_u16m8_m VMASK:$vm),(VID_V_m VMASK:$vm)>;

def : Pat<(int_riscv_vid_v_u32m1_m VMASK:$vm),(VID_V_m VMASK:$vm)>;
def : Pat<(int_riscv_vid_v_u32m2_m VMASK:$vm),(VID_V_m VMASK:$vm)>;
def : Pat<(int_riscv_vid_v_u32m4_m VMASK:$vm),(VID_V_m VMASK:$vm)>;
def : Pat<(int_riscv_vid_v_u32m8_m VMASK:$vm),(VID_V_m VMASK:$vm)>;

/*************Vector Integer Scalar Move Instructions********************/
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in
def VMV_X_S : RVInstVA<0b010000, 0b010, OPC_VOP,
			  (outs GPR:$rd), (ins VReg:$vs2),
			  "vmv.x.s", "$rd, $vs2">,Sched<[]>{
  let Inst{25} = 0b1;
  let Inst{19-15} = 0b00000;
}

let hasSideEffects = 0, mayLoad = 0, mayStore =0, Uses = [VL] in
def VMV_S_X : RVInstVA<0b010000, 0b110, OPC_VOP,
			  (outs VReg:$vd), (ins GPR:$rs1),
			  "vmv.s.x", "$vd, $rs1">,Sched<[]>{
  bits<5> rs1;
  let Inst{25} = 0b1;
  let vs2 = 0b00000;
  let Inst{19-15} = rs1;
}

def : PatVgr<int_riscv_vmv_x_s_8m1,VMV_X_S,v16i8>;
def : PatVgr<int_riscv_vmv_x_s_8m2,VMV_X_S,v32i8>;
def : PatVgr<int_riscv_vmv_x_s_8m4,VMV_X_S,v64i8>;
def : PatVgr<int_riscv_vmv_x_s_8m8,VMV_X_S,v128i8>;

def : PatVgr<int_riscv_vmv_x_s_16m1,VMV_X_S,v8i16>;
def : PatVgr<int_riscv_vmv_x_s_16m2,VMV_X_S,v16i16>;
def : PatVgr<int_riscv_vmv_x_s_16m4,VMV_X_S,v32i16>;
def : PatVgr<int_riscv_vmv_x_s_16m8,VMV_X_S,v64i16>;

def : PatVgr<int_riscv_vmv_x_s_32m1,VMV_X_S,v4i32>;
def : PatVgr<int_riscv_vmv_x_s_32m2,VMV_X_S,v8i32>;
def : PatVgr<int_riscv_vmv_x_s_32m4,VMV_X_S,v16i32>;
def : PatVgr<int_riscv_vmv_x_s_32m8,VMV_X_S,v32i32>;

def : PatGpr<int_riscv_vmv_s_x_8m1,VMV_S_X>;
def : PatGpr<int_riscv_vmv_s_x_8m2,VMV_S_X>;
def : PatGpr<int_riscv_vmv_s_x_8m4,VMV_S_X>;
def : PatGpr<int_riscv_vmv_s_x_8m8,VMV_S_X>;

def : PatGpr<int_riscv_vmv_s_x_16m1,VMV_S_X>;
def : PatGpr<int_riscv_vmv_s_x_16m2,VMV_S_X>;
def : PatGpr<int_riscv_vmv_s_x_16m4,VMV_S_X>;
def : PatGpr<int_riscv_vmv_s_x_16m8,VMV_S_X>;

def : PatGpr<int_riscv_vmv_s_x_32m1,VMV_S_X>;
def : PatGpr<int_riscv_vmv_s_x_32m2,VMV_S_X>;
def : PatGpr<int_riscv_vmv_s_x_32m4,VMV_S_X>;
def : PatGpr<int_riscv_vmv_s_x_32m8,VMV_S_X>;

/*************Vector Floating-Point Scalar Move Functions****************/
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in
def VFMV_F_S : RVInstVAR<0b010000, 0b001, OPC_VOP,
               (outs FPR32:$rd), (ins VReg:$vs2),
               "vfmv.f.s", "$rd, $vs2">,Sched<[]>{
 
  let Inst{25} = 0b1;
  let Inst{19-15} = 0b00000;
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in
def VFMV_S_F : RVInstVA<0b010000, 0b101, OPC_VOP,
               (outs VReg:$vd), (ins FPR32:$rs1),
               "vfmv.s.f", "$vd, $rs1">,Sched<[]>{
  bits<5> rs1;
  let Inst{25} = 0b1;
  let vs2 = 0b00000;
  let Inst{19-15} = rs1;
}

def : PatVgr<int_riscv_vfmv_f_s_f32m1,VFMV_F_S,v4f32>;
def : PatVgr<int_riscv_vfmv_f_s_f32m2,VFMV_F_S,v8f32>;
def : PatVgr<int_riscv_vfmv_f_s_f32m4,VFMV_F_S,v16f32>;
def : PatVgr<int_riscv_vfmv_f_s_f32m8,VFMV_F_S,v32f32>;

def : PatFloat<int_riscv_vfmv_s_f_f32m1,VFMV_S_F,f32>;
def : PatFloat<int_riscv_vfmv_s_f_f32m2,VFMV_S_F,f32>;
def : PatFloat<int_riscv_vfmv_s_f_f32m4,VFMV_S_F,f32>;
def : PatFloat<int_riscv_vfmv_s_f_f32m8,VFMV_S_F,f32>;

/*************Vector Slideup Functions****************/
defm VSLIDEUP_VX : VALU_OPIVX<0b001110,"vslideup.vx">;

def : PatVgrGpr<int_riscv_vslideup_vx_8m1,VSLIDEUP_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vslideup_vx_8m2,VSLIDEUP_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vslideup_vx_8m4,VSLIDEUP_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vslideup_vx_8m8,VSLIDEUP_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vslideup_vx_16m1,VSLIDEUP_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vslideup_vx_16m2,VSLIDEUP_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vslideup_vx_16m4,VSLIDEUP_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vslideup_vx_16m8,VSLIDEUP_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vslideup_vx_32m1,VSLIDEUP_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vslideup_vx_32m2,VSLIDEUP_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vslideup_vx_32m4,VSLIDEUP_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vslideup_vx_32m8,VSLIDEUP_VX_um,v32i32>;

def : PatVgrGpr<int_riscv_vslideup_vx_f32m1,VSLIDEUP_VX_um,v4f32>;
def : PatVgrGpr<int_riscv_vslideup_vx_f32m2,VSLIDEUP_VX_um,v8f32>;
def : PatVgrGpr<int_riscv_vslideup_vx_f32m4,VSLIDEUP_VX_um,v16f32>;
def : PatVgrGpr<int_riscv_vslideup_vx_f32m8,VSLIDEUP_VX_um,v32f32>;

def : PatVmVgrGpr<int_riscv_vslideup_vx_8m1_m,VSLIDEUP_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_8m2_m,VSLIDEUP_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_8m4_m,VSLIDEUP_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_8m8_m,VSLIDEUP_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vslideup_vx_16m1_m,VSLIDEUP_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_16m2_m,VSLIDEUP_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_16m4_m,VSLIDEUP_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_16m8_m,VSLIDEUP_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vslideup_vx_32m1_m,VSLIDEUP_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_32m2_m,VSLIDEUP_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_32m4_m,VSLIDEUP_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_32m8_m,VSLIDEUP_VX_m,v32i32>;

def : PatVmVgrGpr<int_riscv_vslideup_vx_f32m1_m,VSLIDEUP_VX_m,v4f32>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_f32m2_m,VSLIDEUP_VX_m,v8f32>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_f32m4_m,VSLIDEUP_VX_m,v16f32>;
def : PatVmVgrGpr<int_riscv_vslideup_vx_f32m8_m,VSLIDEUP_VX_m,v32f32>;

defm VSLIDEUP_VI : VALU_OPIVI_unsigned<0b001110,"vslideup.vi">;

def : PatVgrUimm5<int_riscv_vslideup_vi_8m1,VSLIDEUP_VI_um,v16i8>;
def : PatVgrUimm5<int_riscv_vslideup_vi_8m2,VSLIDEUP_VI_um,v32i8>;
def : PatVgrUimm5<int_riscv_vslideup_vi_8m4,VSLIDEUP_VI_um,v64i8>;
def : PatVgrUimm5<int_riscv_vslideup_vi_8m8,VSLIDEUP_VI_um,v128i8>;

def : PatVgrUimm5<int_riscv_vslideup_vi_16m1,VSLIDEUP_VI_um,v8i16>;
def : PatVgrUimm5<int_riscv_vslideup_vi_16m2,VSLIDEUP_VI_um,v16i16>;
def : PatVgrUimm5<int_riscv_vslideup_vi_16m4,VSLIDEUP_VI_um,v32i16>;
def : PatVgrUimm5<int_riscv_vslideup_vi_16m8,VSLIDEUP_VI_um,v64i16>;

def : PatVgrUimm5<int_riscv_vslideup_vi_32m1,VSLIDEUP_VI_um,v4i32>;
def : PatVgrUimm5<int_riscv_vslideup_vi_32m2,VSLIDEUP_VI_um,v8i32>;
def : PatVgrUimm5<int_riscv_vslideup_vi_32m4,VSLIDEUP_VI_um,v16i32>;
def : PatVgrUimm5<int_riscv_vslideup_vi_32m8,VSLIDEUP_VI_um,v32i32>;

def : PatVgrUimm5<int_riscv_vslideup_vi_f32m1,VSLIDEUP_VI_um,v4f32>;
def : PatVgrUimm5<int_riscv_vslideup_vi_f32m2,VSLIDEUP_VI_um,v8f32>;
def : PatVgrUimm5<int_riscv_vslideup_vi_f32m4,VSLIDEUP_VI_um,v16f32>;
def : PatVgrUimm5<int_riscv_vslideup_vi_f32m8,VSLIDEUP_VI_um,v32f32>;

def : PatVmVgrUimm5<int_riscv_vslideup_vi_8m1_m,VSLIDEUP_VI_m,v16i8>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_8m2_m,VSLIDEUP_VI_m,v32i8>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_8m4_m,VSLIDEUP_VI_m,v64i8>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_8m8_m,VSLIDEUP_VI_m,v128i8>;

def : PatVmVgrUimm5<int_riscv_vslideup_vi_16m1_m,VSLIDEUP_VI_m,v8i16>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_16m2_m,VSLIDEUP_VI_m,v16i16>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_16m4_m,VSLIDEUP_VI_m,v32i16>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_16m8_m,VSLIDEUP_VI_m,v64i16>;

def : PatVmVgrUimm5<int_riscv_vslideup_vi_32m1_m,VSLIDEUP_VI_m,v4i32>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_32m2_m,VSLIDEUP_VI_m,v8i32>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_32m4_m,VSLIDEUP_VI_m,v16i32>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_32m8_m,VSLIDEUP_VI_m,v32i32>;

def : PatVmVgrUimm5<int_riscv_vslideup_vi_f32m1_m,VSLIDEUP_VI_m,v4f32>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_f32m2_m,VSLIDEUP_VI_m,v8f32>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_f32m4_m,VSLIDEUP_VI_m,v16f32>;
def : PatVmVgrUimm5<int_riscv_vslideup_vi_f32m8_m,VSLIDEUP_VI_m,v32f32>;

defm VSLIDEDOWN_VX : VALU_OPIVX<0b001111,"vslidedown.vx">;

def : PatVgrGpr<int_riscv_vslidedown_vx_8m1,VSLIDEDOWN_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vslidedown_vx_8m2,VSLIDEDOWN_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vslidedown_vx_8m4,VSLIDEDOWN_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vslidedown_vx_8m8,VSLIDEDOWN_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vslidedown_vx_16m1,VSLIDEDOWN_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vslidedown_vx_16m2,VSLIDEDOWN_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vslidedown_vx_16m4,VSLIDEDOWN_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vslidedown_vx_16m8,VSLIDEDOWN_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vslidedown_vx_32m1,VSLIDEDOWN_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vslidedown_vx_32m2,VSLIDEDOWN_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vslidedown_vx_32m4,VSLIDEDOWN_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vslidedown_vx_32m8,VSLIDEDOWN_VX_um,v32i32>;

def : PatVgrGpr<int_riscv_vslidedown_vx_f32m1,VSLIDEDOWN_VX_um,v4f32>;
def : PatVgrGpr<int_riscv_vslidedown_vx_f32m2,VSLIDEDOWN_VX_um,v8f32>;
def : PatVgrGpr<int_riscv_vslidedown_vx_f32m4,VSLIDEDOWN_VX_um,v16f32>;
def : PatVgrGpr<int_riscv_vslidedown_vx_f32m8,VSLIDEDOWN_VX_um,v32f32>;

def : PatVgrGpr<int_riscv_vslidedown_vx_f32m1,VSLIDEDOWN_VX_um,v4f32>;
def : PatVgrGpr<int_riscv_vslidedown_vx_f32m2,VSLIDEDOWN_VX_um,v8f32>;
def : PatVgrGpr<int_riscv_vslidedown_vx_f32m4,VSLIDEDOWN_VX_um,v16f32>;
def : PatVgrGpr<int_riscv_vslidedown_vx_f32m8,VSLIDEDOWN_VX_um,v32f32>;

def : PatVmVgrGpr<int_riscv_vslidedown_vx_8m1_m,VSLIDEDOWN_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_8m2_m,VSLIDEDOWN_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_8m4_m,VSLIDEDOWN_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_8m8_m,VSLIDEDOWN_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vslidedown_vx_16m1_m,VSLIDEDOWN_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_16m2_m,VSLIDEDOWN_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_16m4_m,VSLIDEDOWN_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_16m8_m,VSLIDEDOWN_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vslidedown_vx_32m1_m,VSLIDEDOWN_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_32m2_m,VSLIDEDOWN_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_32m4_m,VSLIDEDOWN_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_32m8_m,VSLIDEDOWN_VX_m,v32i32>;

def : PatVmVgrGpr<int_riscv_vslidedown_vx_f32m1_m,VSLIDEDOWN_VX_m,v4f32>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_f32m2_m,VSLIDEDOWN_VX_m,v8f32>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_f32m4_m,VSLIDEDOWN_VX_m,v16f32>;
def : PatVmVgrGpr<int_riscv_vslidedown_vx_f32m8_m,VSLIDEDOWN_VX_m,v32f32>;

defm VSLIDEDOWN_VI : VALU_OPIVI_unsigned<0b001111,"vslidedown.vi">;

def : PatVgrUimm5<int_riscv_vslidedown_vi_8m1,VSLIDEDOWN_VI_um,v16i8>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_8m2,VSLIDEDOWN_VI_um,v32i8>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_8m4,VSLIDEDOWN_VI_um,v64i8>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_8m8,VSLIDEDOWN_VI_um,v128i8>;

def : PatVgrUimm5<int_riscv_vslidedown_vi_16m1,VSLIDEDOWN_VI_um,v8i16>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_16m2,VSLIDEDOWN_VI_um,v16i16>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_16m4,VSLIDEDOWN_VI_um,v32i16>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_16m8,VSLIDEDOWN_VI_um,v64i16>;

def : PatVgrUimm5<int_riscv_vslidedown_vi_32m1,VSLIDEDOWN_VI_um,v4i32>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_32m2,VSLIDEDOWN_VI_um,v8i32>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_32m4,VSLIDEDOWN_VI_um,v16i32>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_32m8,VSLIDEDOWN_VI_um,v32i32>;

def : PatVgrUimm5<int_riscv_vslidedown_vi_f32m1,VSLIDEDOWN_VI_um,v4f32>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_f32m2,VSLIDEDOWN_VI_um,v8f32>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_f32m4,VSLIDEDOWN_VI_um,v16f32>;
def : PatVgrUimm5<int_riscv_vslidedown_vi_f32m8,VSLIDEDOWN_VI_um,v32f32>;

def : PatVmVgrUimm5<int_riscv_vslidedown_vi_8m1_m,VSLIDEDOWN_VI_m,v16i8>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_8m2_m,VSLIDEDOWN_VI_m,v32i8>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_8m4_m,VSLIDEDOWN_VI_m,v64i8>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_8m8_m,VSLIDEDOWN_VI_m,v128i8>;

def : PatVmVgrUimm5<int_riscv_vslidedown_vi_16m1_m,VSLIDEDOWN_VI_m,v8i16>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_16m2_m,VSLIDEDOWN_VI_m,v16i16>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_16m4_m,VSLIDEDOWN_VI_m,v32i16>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_16m8_m,VSLIDEDOWN_VI_m,v64i16>;

def : PatVmVgrUimm5<int_riscv_vslidedown_vi_32m1_m,VSLIDEDOWN_VI_m,v4i32>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_32m2_m,VSLIDEDOWN_VI_m,v8i32>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_32m4_m,VSLIDEDOWN_VI_m,v16i32>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_32m8_m,VSLIDEDOWN_VI_m,v32i32>;

def : PatVmVgrUimm5<int_riscv_vslidedown_vi_f32m1_m,VSLIDEDOWN_VI_m,v4f32>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_f32m2_m,VSLIDEDOWN_VI_m,v8f32>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_f32m4_m,VSLIDEDOWN_VI_m,v16f32>;
def : PatVmVgrUimm5<int_riscv_vslidedown_vi_f32m8_m,VSLIDEDOWN_VI_m,v32f32>;

defm VSLIDE1UP_VX : VALU_OPMVX<0b001110,"vslide1up.vx">;

def : PatVgrGpr<int_riscv_vslide1up_vx_8m1,VSLIDE1UP_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vslide1up_vx_8m2,VSLIDE1UP_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vslide1up_vx_8m4,VSLIDE1UP_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vslide1up_vx_8m8,VSLIDE1UP_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vslide1up_vx_16m1,VSLIDE1UP_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vslide1up_vx_16m2,VSLIDE1UP_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vslide1up_vx_16m4,VSLIDE1UP_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vslide1up_vx_16m8,VSLIDE1UP_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vslide1up_vx_32m1,VSLIDE1UP_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vslide1up_vx_32m2,VSLIDE1UP_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vslide1up_vx_32m4,VSLIDE1UP_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vslide1up_vx_32m8,VSLIDE1UP_VX_um,v32i32>;

def : PatVgrGpr<int_riscv_vslide1up_vx_f32m1,VSLIDE1UP_VX_um,v4f32>;
def : PatVgrGpr<int_riscv_vslide1up_vx_f32m2,VSLIDE1UP_VX_um,v8f32>;
def : PatVgrGpr<int_riscv_vslide1up_vx_f32m4,VSLIDE1UP_VX_um,v16f32>;
def : PatVgrGpr<int_riscv_vslide1up_vx_f32m8,VSLIDE1UP_VX_um,v32f32>;

def : PatVmVgrGpr<int_riscv_vslide1up_vx_8m1_m,VSLIDE1UP_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_8m2_m,VSLIDE1UP_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_8m4_m,VSLIDE1UP_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_8m8_m,VSLIDE1UP_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vslide1up_vx_16m1_m,VSLIDE1UP_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_16m2_m,VSLIDE1UP_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_16m4_m,VSLIDE1UP_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_16m8_m,VSLIDE1UP_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vslide1up_vx_32m1_m,VSLIDE1UP_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_32m2_m,VSLIDE1UP_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_32m4_m,VSLIDE1UP_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_32m8_m,VSLIDE1UP_VX_m,v32i32>;

def : PatVmVgrGpr<int_riscv_vslide1up_vx_f32m1_m,VSLIDE1UP_VX_m,v4f32>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_f32m2_m,VSLIDE1UP_VX_m,v8f32>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_f32m4_m,VSLIDE1UP_VX_m,v16f32>;
def : PatVmVgrGpr<int_riscv_vslide1up_vx_f32m8_m,VSLIDE1UP_VX_m,v32f32>;

defm VSLIDE1DOWN_VX : VALU_OPMVX<0b001111,"vslide1down.vx">;

def : PatVgrGpr<int_riscv_vslide1down_vx_8m1,VSLIDE1DOWN_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vslide1down_vx_8m2,VSLIDE1DOWN_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vslide1down_vx_8m4,VSLIDE1DOWN_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vslide1down_vx_8m8,VSLIDE1DOWN_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vslide1down_vx_16m1,VSLIDE1DOWN_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vslide1down_vx_16m2,VSLIDE1DOWN_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vslide1down_vx_16m4,VSLIDE1DOWN_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vslide1down_vx_16m8,VSLIDE1DOWN_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vslide1down_vx_32m1,VSLIDE1DOWN_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vslide1down_vx_32m2,VSLIDE1DOWN_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vslide1down_vx_32m4,VSLIDE1DOWN_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vslide1down_vx_32m8,VSLIDE1DOWN_VX_um,v32i32>;

def : PatVgrGpr<int_riscv_vslide1down_vx_f32m1,VSLIDE1DOWN_VX_um,v4f32>;
def : PatVgrGpr<int_riscv_vslide1down_vx_f32m2,VSLIDE1DOWN_VX_um,v8f32>;
def : PatVgrGpr<int_riscv_vslide1down_vx_f32m4,VSLIDE1DOWN_VX_um,v16f32>;
def : PatVgrGpr<int_riscv_vslide1down_vx_f32m8,VSLIDE1DOWN_VX_um,v32f32>;

def : PatVmVgrGpr<int_riscv_vslide1down_vx_8m1_m,VSLIDE1DOWN_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_8m2_m,VSLIDE1DOWN_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_8m4_m,VSLIDE1DOWN_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_8m8_m,VSLIDE1DOWN_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vslide1down_vx_16m1_m,VSLIDE1DOWN_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_16m2_m,VSLIDE1DOWN_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_16m4_m,VSLIDE1DOWN_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_16m8_m,VSLIDE1DOWN_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vslide1down_vx_32m1_m,VSLIDE1DOWN_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_32m2_m,VSLIDE1DOWN_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_32m4_m,VSLIDE1DOWN_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_32m8_m,VSLIDE1DOWN_VX_m,v32i32>;

def : PatVmVgrGpr<int_riscv_vslide1down_vx_f32m1_m,VSLIDE1DOWN_VX_m,v4f32>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_f32m2_m,VSLIDE1DOWN_VX_m,v8f32>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_f32m4_m,VSLIDE1DOWN_VX_m,v16f32>;
def : PatVmVgrGpr<int_riscv_vslide1down_vx_f32m8_m,VSLIDE1DOWN_VX_m,v32f32>;


/*************Vector Register Gather Instructions****************/
defm VRGATHER_VV : VALU_OPIVV<0b001100,"vrgather.vv">;

def : PatVgrVgr<int_riscv_vrgather_vv_8m1,VRGATHER_VV_um,v16i8>;
def : PatVgrVgr<int_riscv_vrgather_vv_8m2,VRGATHER_VV_um,v32i8>;
def : PatVgrVgr<int_riscv_vrgather_vv_8m4,VRGATHER_VV_um,v64i8>;
def : PatVgrVgr<int_riscv_vrgather_vv_8m8,VRGATHER_VV_um,v128i8>;

def : PatVgrVgr<int_riscv_vrgather_vv_16m1,VRGATHER_VV_um,v8i16>;
def : PatVgrVgr<int_riscv_vrgather_vv_16m2,VRGATHER_VV_um,v16i16>;
def : PatVgrVgr<int_riscv_vrgather_vv_16m4,VRGATHER_VV_um,v32i16>;
def : PatVgrVgr<int_riscv_vrgather_vv_16m8,VRGATHER_VV_um,v64i16>;

def : PatVgrVgr<int_riscv_vrgather_vv_32m1,VRGATHER_VV_um,v4i32>;
def : PatVgrVgr<int_riscv_vrgather_vv_32m2,VRGATHER_VV_um,v8i32>;
def : PatVgrVgr<int_riscv_vrgather_vv_32m4,VRGATHER_VV_um,v16i32>;
def : PatVgrVgr<int_riscv_vrgather_vv_32m8,VRGATHER_VV_um,v32i32>;

def : PatVgr1Vgr2<int_riscv_vrgather_vv_f32m1,VRGATHER_VV_um,v4f32,v4i32>;
def : PatVgr1Vgr2<int_riscv_vrgather_vv_f32m2,VRGATHER_VV_um,v8f32,v8i32>;
def : PatVgr1Vgr2<int_riscv_vrgather_vv_f32m4,VRGATHER_VV_um,v16f32,v16i32>;
def : PatVgr1Vgr2<int_riscv_vrgather_vv_f32m8,VRGATHER_VV_um,v32f32,v32i32>;

def : PatVmVgrVgr<int_riscv_vrgather_vv_8m1_m,VRGATHER_VV_m,v16i8>;
def : PatVmVgrVgr<int_riscv_vrgather_vv_8m2_m,VRGATHER_VV_m,v32i8>;
def : PatVmVgrVgr<int_riscv_vrgather_vv_8m4_m,VRGATHER_VV_m,v64i8>;
def : PatVmVgrVgr<int_riscv_vrgather_vv_8m8_m,VRGATHER_VV_m,v128i8>;

def : PatVmVgrVgr<int_riscv_vrgather_vv_16m1_m,VRGATHER_VV_m,v8i16>;
def : PatVmVgrVgr<int_riscv_vrgather_vv_16m2_m,VRGATHER_VV_m,v16i16>;
def : PatVmVgrVgr<int_riscv_vrgather_vv_16m4_m,VRGATHER_VV_m,v32i16>;
def : PatVmVgrVgr<int_riscv_vrgather_vv_16m8_m,VRGATHER_VV_m,v64i16>;

def : PatVmVgrVgr<int_riscv_vrgather_vv_32m1_m,VRGATHER_VV_m,v4i32>;
def : PatVmVgrVgr<int_riscv_vrgather_vv_32m2_m,VRGATHER_VV_m,v8i32>;
def : PatVmVgrVgr<int_riscv_vrgather_vv_32m4_m,VRGATHER_VV_m,v16i32>;
def : PatVmVgrVgr<int_riscv_vrgather_vv_32m8_m,VRGATHER_VV_m,v32i32>;

def : PatVmVgr1Vgr2<int_riscv_vrgather_vv_f32m1_m,VRGATHER_VV_m,v4f32,v4i32>;
def : PatVmVgr1Vgr2<int_riscv_vrgather_vv_f32m2_m,VRGATHER_VV_m,v8f32,v8i32>;
def : PatVmVgr1Vgr2<int_riscv_vrgather_vv_f32m4_m,VRGATHER_VV_m,v16f32,v16i32>;
def : PatVmVgr1Vgr2<int_riscv_vrgather_vv_f32m8_m,VRGATHER_VV_m,v32f32,v32i32>;

defm VRGATHER_VX : VALU_OPIVX<0b001100,"vrgather.vx">;

def : PatVgrGpr<int_riscv_vrgather_vx_8m1,VRGATHER_VX_um,v16i8>;
def : PatVgrGpr<int_riscv_vrgather_vx_8m2,VRGATHER_VX_um,v32i8>;
def : PatVgrGpr<int_riscv_vrgather_vx_8m4,VRGATHER_VX_um,v64i8>;
def : PatVgrGpr<int_riscv_vrgather_vx_8m8,VRGATHER_VX_um,v128i8>;

def : PatVgrGpr<int_riscv_vrgather_vx_16m1,VRGATHER_VX_um,v8i16>;
def : PatVgrGpr<int_riscv_vrgather_vx_16m2,VRGATHER_VX_um,v16i16>;
def : PatVgrGpr<int_riscv_vrgather_vx_16m4,VRGATHER_VX_um,v32i16>;
def : PatVgrGpr<int_riscv_vrgather_vx_16m8,VRGATHER_VX_um,v64i16>;

def : PatVgrGpr<int_riscv_vrgather_vx_32m1,VRGATHER_VX_um,v4i32>;
def : PatVgrGpr<int_riscv_vrgather_vx_32m2,VRGATHER_VX_um,v8i32>;
def : PatVgrGpr<int_riscv_vrgather_vx_32m4,VRGATHER_VX_um,v16i32>;
def : PatVgrGpr<int_riscv_vrgather_vx_32m8,VRGATHER_VX_um,v32i32>;

def : PatVgrGpr<int_riscv_vrgather_vx_f32m1,VRGATHER_VX_um,v4f32>;
def : PatVgrGpr<int_riscv_vrgather_vx_f32m2,VRGATHER_VX_um,v8f32>;
def : PatVgrGpr<int_riscv_vrgather_vx_f32m4,VRGATHER_VX_um,v16f32>;
def : PatVgrGpr<int_riscv_vrgather_vx_f32m8,VRGATHER_VX_um,v32f32>;

def : PatVmVgrGpr<int_riscv_vrgather_vx_8m1_m,VRGATHER_VX_m,v16i8>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_8m2_m,VRGATHER_VX_m,v32i8>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_8m4_m,VRGATHER_VX_m,v64i8>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_8m8_m,VRGATHER_VX_m,v128i8>;

def : PatVmVgrGpr<int_riscv_vrgather_vx_16m1_m,VRGATHER_VX_m,v8i16>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_16m2_m,VRGATHER_VX_m,v16i16>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_16m4_m,VRGATHER_VX_m,v32i16>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_16m8_m,VRGATHER_VX_m,v64i16>;

def : PatVmVgrGpr<int_riscv_vrgather_vx_32m1_m,VRGATHER_VX_m,v4i32>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_32m2_m,VRGATHER_VX_m,v8i32>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_32m4_m,VRGATHER_VX_m,v16i32>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_32m8_m,VRGATHER_VX_m,v32i32>;

def : PatVmVgrGpr<int_riscv_vrgather_vx_f32m1_m,VRGATHER_VX_m,v4f32>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_f32m2_m,VRGATHER_VX_m,v8f32>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_f32m4_m,VRGATHER_VX_m,v16f32>;
def : PatVmVgrGpr<int_riscv_vrgather_vx_f32m8_m,VRGATHER_VX_m,v32f32>;

defm VRGATHER_VI : VALU_OPIVI_unsigned<0b001100,"vrgather.vi">;

def : PatVgrUimm5<int_riscv_vrgather_vi_8m1,VRGATHER_VI_um,v16i8>;
def : PatVgrUimm5<int_riscv_vrgather_vi_8m2,VRGATHER_VI_um,v32i8>;
def : PatVgrUimm5<int_riscv_vrgather_vi_8m4,VRGATHER_VI_um,v64i8>;
def : PatVgrUimm5<int_riscv_vrgather_vi_8m8,VRGATHER_VI_um,v128i8>;

def : PatVgrUimm5<int_riscv_vrgather_vi_16m1,VRGATHER_VI_um,v8i16>;
def : PatVgrUimm5<int_riscv_vrgather_vi_16m2,VRGATHER_VI_um,v16i16>;
def : PatVgrUimm5<int_riscv_vrgather_vi_16m4,VRGATHER_VI_um,v32i16>;
def : PatVgrUimm5<int_riscv_vrgather_vi_16m8,VRGATHER_VI_um,v64i16>;

def : PatVgrUimm5<int_riscv_vrgather_vi_32m1,VRGATHER_VI_um,v4i32>;
def : PatVgrUimm5<int_riscv_vrgather_vi_32m2,VRGATHER_VI_um,v8i32>;
def : PatVgrUimm5<int_riscv_vrgather_vi_32m4,VRGATHER_VI_um,v16i32>;
def : PatVgrUimm5<int_riscv_vrgather_vi_32m8,VRGATHER_VI_um,v32i32>;

def : PatVgrUimm5<int_riscv_vrgather_vi_f32m1,VRGATHER_VI_um,v4f32>;
def : PatVgrUimm5<int_riscv_vrgather_vi_f32m2,VRGATHER_VI_um,v8f32>;
def : PatVgrUimm5<int_riscv_vrgather_vi_f32m4,VRGATHER_VI_um,v16f32>;
def : PatVgrUimm5<int_riscv_vrgather_vi_f32m8,VRGATHER_VI_um,v32f32>;

def : PatVmVgrUimm5<int_riscv_vrgather_vi_8m1_m,VRGATHER_VI_m,v16i8>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_8m2_m,VRGATHER_VI_m,v32i8>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_8m4_m,VRGATHER_VI_m,v64i8>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_8m8_m,VRGATHER_VI_m,v128i8>;

def : PatVmVgrUimm5<int_riscv_vrgather_vi_16m1_m,VRGATHER_VI_m,v8i16>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_16m2_m,VRGATHER_VI_m,v16i16>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_16m4_m,VRGATHER_VI_m,v32i16>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_16m8_m,VRGATHER_VI_m,v64i16>;

def : PatVmVgrUimm5<int_riscv_vrgather_vi_32m1_m,VRGATHER_VI_m,v4i32>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_32m2_m,VRGATHER_VI_m,v8i32>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_32m4_m,VRGATHER_VI_m,v16i32>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_32m8_m,VRGATHER_VI_m,v32i32>;

def : PatVmVgrUimm5<int_riscv_vrgather_vi_f32m1_m,VRGATHER_VI_m,v4f32>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_f32m2_m,VRGATHER_VI_m,v8f32>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_f32m4_m,VRGATHER_VI_m,v16f32>;
def : PatVmVgrUimm5<int_riscv_vrgather_vi_f32m8_m,VRGATHER_VI_m,v32f32>;


/*************Vector Compress Instruction****************/
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, Uses = [VL] in
def VCOMPRESS_VM : RVInstVA<0b010111, 0b010, OPC_VOP,
               (outs VReg:$vd), (ins VReg:$vs1, VReg:$vs2),
               "vcompress.vm", "$vd, $vs2, $vs1">,Sched<[]>{
  bits<5> vs1;
  let Inst{25} = 0b1;
  let Inst{19-15} = vs1;
	}

def : PatVgr1Vgr2<int_riscv_vcompress_vm_8m1,VCOMPRESS_VM,v16i8,v16i8>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_8m2,VCOMPRESS_VM,v16i8,v32i8>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_8m4,VCOMPRESS_VM,v16i8,v64i8>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_8m8,VCOMPRESS_VM,v16i8,v128i8>;

def : PatVgr1Vgr2<int_riscv_vcompress_vm_16m1,VCOMPRESS_VM,v16i8,v8i16>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_16m2,VCOMPRESS_VM,v16i8,v16i16>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_16m4,VCOMPRESS_VM,v16i8,v32i16>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_16m8,VCOMPRESS_VM,v16i8,v64i16>;

def : PatVgr1Vgr2<int_riscv_vcompress_vm_32m1,VCOMPRESS_VM,v16i8,v4i32>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_32m2,VCOMPRESS_VM,v16i8,v8i32>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_32m4,VCOMPRESS_VM,v16i8,v16i32>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_32m8,VCOMPRESS_VM,v16i8,v32i32>;

def : PatVgr1Vgr2<int_riscv_vcompress_vm_f32m1,VCOMPRESS_VM,v16i8,v4f32>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_f32m2,VCOMPRESS_VM,v16i8,v8f32>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_f32m4,VCOMPRESS_VM,v16i8,v16f32>;
def : PatVgr1Vgr2<int_riscv_vcompress_vm_f32m8,VCOMPRESS_VM,v16i8,v32f32>;

}//end HasStdExtV
