//===-- RISCVRegisterInfo.td - RISC-V Register defs --------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//
// Declarations that describe the RISC-V Vector register files
// Contributed by Hunan Compiler Information Technology Co., Ltd, 
// http://www.compiler-dev.com, Email: <info@compiler-dev.com>.
//===----------------------------------------------------------------------===//


let Namespace = "RISCV" in {
def vsub0 : SubRegIndex<128>;
def vsub1 : SubRegIndex<128>;
def vsub2 : SubRegIndex<128>;
def vsub3 : SubRegIndex<128>;
def vsub4 : SubRegIndex<128>;
def vsub5 : SubRegIndex<128>;
def vsub6 : SubRegIndex<128>;
def vsub7 : SubRegIndex<128>;
}

class VLMULReg<bits<5> Enc,
			  string name,
			  list<Register> subregs = [],
			  list<string> altNames = []>
	: RegisterWithSubRegs<name,subregs>
{
	let HWEncoding{4-0} = Enc;
	let Namespace = "RISCV";
	let SubRegs = subregs;
	let AltNames = altNames;
}

//vector register  
//LMUL = 1
let RegAltNameIndices = [ABIRegAltName] in {
  def V0  : RISCVReg32<0, "v0", ["v0"]>, DwarfRegNum<[64]>;
  def V1  : RISCVReg32<1, "v1", ["v1"]>, DwarfRegNum<[65]>;
  def V2  : RISCVReg32<2, "v2", ["v2"]>, DwarfRegNum<[66]>;
  def V3  : RISCVReg32<3, "v3", ["v3"]>, DwarfRegNum<[67]>;
  def V4  : RISCVReg32<4, "v4", ["v4"]>, DwarfRegNum<[68]>;
  def V5  : RISCVReg32<5, "v5", ["v5"]>, DwarfRegNum<[69]>;
  def V6  : RISCVReg32<6, "v6", ["v6"]>, DwarfRegNum<[70]>;
  def V7  : RISCVReg32<7, "v7", ["v7"]>, DwarfRegNum<[71]>;
  def V8  : RISCVReg32<8, "v8", ["v8"]>, DwarfRegNum<[72]>;
  def V9  : RISCVReg32<9, "v9", ["v9"]>, DwarfRegNum<[73]>;
  def V10 : RISCVReg32<10,"v10", ["v10"]>, DwarfRegNum<[74]>;
  def V11 : RISCVReg32<11,"v11", ["v11"]>, DwarfRegNum<[75]>;
  def V12 : RISCVReg32<12,"v12", ["v12"]>, DwarfRegNum<[76]>;
  def V13 : RISCVReg32<13,"v13", ["v13"]>, DwarfRegNum<[77]>;
  def V14 : RISCVReg32<14,"v14", ["v14"]>, DwarfRegNum<[78]>;
  def V15 : RISCVReg32<15,"v15", ["v15"]>, DwarfRegNum<[79]>;
  def V16 : RISCVReg32<16,"v16", ["v16"]>, DwarfRegNum<[80]>;
  def V17 : RISCVReg32<17,"v17", ["v17"]>, DwarfRegNum<[81]>;
  def V18 : RISCVReg32<18,"v18", ["v18"]>, DwarfRegNum<[82]>;
  def V19 : RISCVReg32<19,"v19", ["v19"]>, DwarfRegNum<[83]>;
  def V20 : RISCVReg32<20,"v20", ["v20"]>, DwarfRegNum<[84]>;
  def V21 : RISCVReg32<21,"v21", ["v21"]>, DwarfRegNum<[85]>;
  def V22 : RISCVReg32<22,"v22", ["v22"]>, DwarfRegNum<[86]>;
  def V23 : RISCVReg32<23,"v23", ["v23"]>, DwarfRegNum<[87]>;
  def V24 : RISCVReg32<24,"v24", ["v24"]>, DwarfRegNum<[88]>;
  def V25 : RISCVReg32<25,"v25", ["v25"]>, DwarfRegNum<[89]>;
  def V26 : RISCVReg32<26,"v26", ["v26"]>, DwarfRegNum<[90]>;
  def V27 : RISCVReg32<27,"v27", ["v27"]>, DwarfRegNum<[91]>;
  def V28 : RISCVReg32<28,"v28", ["v28"]>, DwarfRegNum<[92]>;
  def V29 : RISCVReg32<29,"v29", ["v29"]>, DwarfRegNum<[93]>;
  def V30 : RISCVReg32<30,"v30", ["v30"]>, DwarfRegNum<[94]>;
  def V31 : RISCVReg32<31,"v31", ["v31"]>, DwarfRegNum<[95]>; 
}

def VGR : RegisterClass<"RISCV", [v16i8, v8i16, v4i32, v4f32], 128, (add
    (sequence "V%u", 8, 15),
    (sequence "V%u", 1, 7),
    (sequence "V%u", 24, 31),
    (sequence "V%u", 16, 23),
    V0 
)>;

/*def VGRNoV0 : RegisterClass<"RISCV", [v16i8, v8i16, v4i32, v4f32], 128, (add
    (sequence "V%u", 8, 15),
    (sequence "V%u", 1, 7),
    (sequence "V%u", 24, 31),
    (sequence "V%u", 16, 23)
)>;*/

//LMUL = 2
let SubRegIndices = [vsub1, vsub0], RegAltNameIndices = [ABIRegAltName] in{
	def VP0	 : VLMULReg<0,  "v0",   [V1,V0],		 ["v0"]>,    DwarfRegNum<[0]>;
	def VP1  : VLMULReg<2,  "v2",   [V3,V2],		 ["v2"]>,    DwarfRegNum<[2]>;
	def VP2  : VLMULReg<4,  "v4",   [V5,V4],		 ["v4"]>,    DwarfRegNum<[4]>;
	def VP3  : VLMULReg<6,  "v6",   [V7,V6],		 ["v6"]>,    DwarfRegNum<[6]>;
	def VP4  : VLMULReg<8,  "v8",   [V9,V8],		 ["v8"]>,    DwarfRegNum<[8]>;
	def VP5  : VLMULReg<10, "v10",  [V11,V10],       ["v10"]>,	 DwarfRegNum<[10]>;
	def VP6  : VLMULReg<12, "v12",  [V13,V12],       ["v12"]>,   DwarfRegNum<[12]>;
	def VP7  : VLMULReg<14, "v14",  [V15,V14],	     ["v14"]>,   DwarfRegNum<[14]>;
	def VP8  : VLMULReg<16, "v16",  [V17,V16],       ["v16"]>,   DwarfRegNum<[16]>;
	def VP9  : VLMULReg<18, "v18",  [V19,V18],       ["v18"]>,   DwarfRegNum<[18]>;
	def VP10 : VLMULReg<20, "v20",  [V21,V20],       ["v20"]>,   DwarfRegNum<[20]>;
	def VP11 : VLMULReg<22, "v22",  [V23,V22],       ["v22"]>,   DwarfRegNum<[22]>;
	def VP12 : VLMULReg<24, "v24",  [V25,V24],       ["v24"]>,   DwarfRegNum<[24]>;
	def VP13 : VLMULReg<26, "v26",  [V27,V26],       ["v26"]>,   DwarfRegNum<[26]>;
	def VP14 : VLMULReg<28, "v28",  [V29,V28],       ["v28"]>,   DwarfRegNum<[28]>;
	def VP15 : VLMULReg<30, "v30",  [V31,V30],       ["v30"]>,   DwarfRegNum<[30]>;
}

//LMUL = 4
let SubRegIndices = [vsub3,vsub2,vsub1,vsub0], RegAltNameIndices = [ABIRegAltName] in{
	def VQ0 : VLMULReg<0,  "v0",     [V3, V2, V1, V0],     ["v0"]>,		DwarfRegNum<[0]>;
	def VQ1 : VLMULReg<4,  "v4",     [V7, V6, V5, V4],     ["v4"]>,		DwarfRegNum<[4]>;
	def VQ2 : VLMULReg<8,  "v8",     [V11, V10, V9, V8],   ["v8"]>,		DwarfRegNum<[8]>;
	def VQ3 : VLMULReg<12, "v12",    [V15, V14, V13, V12], ["v12"]>,	DwarfRegNum<[12]>;
	def VQ4 : VLMULReg<16, "v16",    [V19, V18, V17, V16], ["v16"]>,	DwarfRegNum<[16]>;
	def VQ5 : VLMULReg<20, "v20",    [V23, V22, V21, V20], ["v20"]>,	DwarfRegNum<[20]>;
	def VQ6 : VLMULReg<24, "v24",    [V27, V26, V25, V24], ["v24"]>,	DwarfRegNum<[24]>;
	def VQ7 : VLMULReg<28, "v28",    [V31, V30, V29, V28], ["v28"]>,	DwarfRegNum<[28]>;
}

//LMUL = 8
let SubRegIndices = [vsub7,vsub6,vsub5,vsub4,vsub3,vsub2,vsub1,vsub0],
									RegAltNameIndices = [ABIRegAltName] in{
	def VO0 : VLMULReg<0, "v0", 
			[V7, V6, V5, V4, V3, V2, V1, V0], ["v0"]>,	 DwarfRegNum<[0]>;
	def VO1 : VLMULReg<8, "v8", 
			[V15, V14, V13, V12, V11, V10, V9, V8], ["v8"]>,	DwarfRegNum<[8]>;
	def VO2 : VLMULReg<16, "v16", 
			[V23, V22, V21, V20, V19, V18, V17, V16], ["v16"]>,	DwarfRegNum<[16]>;
	def VO3 : VLMULReg<24, "v24",
			[V31, V30, V29, V28, V27, V26, V25, V24], ["v24"]>, DwarfRegNum<[24]>;
}

def VPR : RegisterClass<"RISCV", [v32i8, v16i16, v8i32, v8f32], 256, (add
						(sequence "VP%u", 4, 7),
						(sequence "VP%u", 1, 3),
						(sequence "VP%u", 12, 15),
						(sequence "VP%u", 8, 11),
						VP0)>;
def VQR : RegisterClass<"RISCV", [v64i8, v32i16, v16i32, v16f32], 512, (add
						(sequence "VQ%u", 2, 7),
						VQ1,VQ0)>;
def VOR : RegisterClass<"RISCV", [v128i8, v64i16, v32i32, v32f32], 1024, (add
						(sequence "VO%u", 1, 3),
						VO0)>;


let RegAltNameIndices = [ABIRegAltName] in
def V0T : RISCVReg32<0, "v0.t", ["v0.t"]>, DwarfRegNum<[0]>;
def VMASK : RegisterClass<"RISCV", [v16i8], 128, (add V0T)>;

let RegAltNameIndices = [ABIRegAltName] in
def VL : RISCVReg32<0, "vl", ["vl"]>;
