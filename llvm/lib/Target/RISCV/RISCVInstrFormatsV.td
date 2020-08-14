//===-- RISCVInstrFormatsV.td - RISCV Vector Extension Instruction Formats --*- tablegen -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file describes the RISC-V V extension instruction formats.
// Contributed by Hunan Compiler Information Technology Co., Ltd, 
// http://www.compiler-dev.com, Email: <info@compiler-dev.com>.
//===----------------------------------------------------------------------===//

class RVInstVLoad<bits<6> funct6, bits<3> funct3,RISCVOpcode opcode,
				dag outs, dag ins, string opcodestr, string argstr>
				: RVInst<outs, ins, opcodestr, argstr, [], InstFormatV>{
		bits<5> rs1;
		bits<5> vd;

		let Inst{31-26} = funct6;
		let Inst{19-15} = rs1;
		let Inst{14-12} = funct3;
		let Inst{11-7} = vd;
		let Opcode = opcode.Value;
}

class RVInstVStore<bits<6> funct6,bits<3> funct3,RISCVOpcode opcode,
				dag outs,dag ins, string opcodestr,string argstr>
				: RVInst<outs, ins, opcodestr, argstr, [], InstFormatV>{
		bits<5> rs1;
		bits<5> vs3;

		let Inst{31-26} = funct6;
		let Inst{19-15} = rs1;
		let Inst{14-12} = funct3;
		let Inst{11-7} = vs3;
		let Opcode = opcode.Value;
}

class RVInstVA<bits<6> funct6,bits<3> funct3,RISCVOpcode opcode,
				dag outs, dag ins, string opcodestr, string argstr>
				: RVInst<outs, ins, opcodestr, argstr, [], InstFormatV>{
		bits<5> vs2;
		bits<5> vd;

		let Inst{31-26} = funct6;
		let Inst{24-20} = vs2;
		let Inst{14-12} = funct3;
		let Inst{11-7} = vd;
		let Opcode = opcode.Value;
}

class RVInstVAR<bits<6> funct6,bits<3> funct3,RISCVOpcode opcode,
				dag outs, dag ins, string opcodestr, string argstr>
				: RVInst<outs, ins, opcodestr, argstr, [], InstFormatV>{
		bits<5> vs2;
		bits<5> rd;

		let Inst{31-26} = funct6;
		let Inst{24-20} = vs2;
		let Inst{14-12} = funct3;
		let Inst{11-7} = rd;
		let Opcode = opcode.Value;
}

class RVInstVSet<bits<5> funct5, RISCVOpcode opcode,dag outs, 
				dag ins, string opcodestr, string argstr, list<dag> pattern>
				: RVInst<outs, ins, opcodestr, argstr, pattern, InstFormatV>{
		bits<5> rs1;
		bits<5> rd;

		let Inst{31-27} = funct5;
		let Inst{19-15} = rs1;
		let Inst{14-12} = 0b111;
		let Inst{11-7} = rd;
		let Opcode = opcode.Value;
}
