; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-unknown-linux-gnu | FileCheck %s

define <3 x i32> @f_29(<12 x i16> %a, <12 x i16> %b) {
; CHECK-LABEL: f_29:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movd {{.*#+}} xmm0 = mem[0],zero,zero,zero
; CHECK-NEXT:    movd {{.*#+}} xmm1 = mem[0],zero,zero,zero
; CHECK-NEXT:    punpcklwd {{.*#+}} xmm1 = xmm1[0],xmm0[0],xmm1[1],xmm0[1],xmm1[2],xmm0[2],xmm1[3],xmm0[3]
; CHECK-NEXT:    movd {{.*#+}} xmm0 = mem[0],zero,zero,zero
; CHECK-NEXT:    movd {{.*#+}} xmm2 = mem[0],zero,zero,zero
; CHECK-NEXT:    punpcklwd {{.*#+}} xmm2 = xmm2[0],xmm0[0],xmm2[1],xmm0[1],xmm2[2],xmm0[2],xmm2[3],xmm0[3]
; CHECK-NEXT:    punpckldq {{.*#+}} xmm2 = xmm2[0],xmm1[0],xmm2[1],xmm1[1]
; CHECK-NEXT:    movd {{.*#+}} xmm0 = mem[0],zero,zero,zero
; CHECK-NEXT:    movd {{.*#+}} xmm3 = mem[0],zero,zero,zero
; CHECK-NEXT:    punpcklwd {{.*#+}} xmm3 = xmm3[0],xmm0[0],xmm3[1],xmm0[1],xmm3[2],xmm0[2],xmm3[3],xmm0[3]
; CHECK-NEXT:    movd {{.*#+}} xmm0 = mem[0],zero,zero,zero
; CHECK-NEXT:    movd {{.*#+}} xmm1 = mem[0],zero,zero,zero
; CHECK-NEXT:    punpcklwd {{.*#+}} xmm1 = xmm1[0],xmm0[0],xmm1[1],xmm0[1],xmm1[2],xmm0[2],xmm1[3],xmm0[3]
; CHECK-NEXT:    punpckldq {{.*#+}} xmm1 = xmm1[0],xmm3[0],xmm1[1],xmm3[1]
; CHECK-NEXT:    punpcklqdq {{.*#+}} xmm1 = xmm1[0],xmm2[0]
; CHECK-NEXT:    movd {{.*#+}} xmm0 = mem[0],zero,zero,zero
; CHECK-NEXT:    movd {{.*#+}} xmm2 = mem[0],zero,zero,zero
; CHECK-NEXT:    punpcklwd {{.*#+}} xmm2 = xmm2[0],xmm0[0],xmm2[1],xmm0[1],xmm2[2],xmm0[2],xmm2[3],xmm0[3]
; CHECK-NEXT:    movd %r9d, %xmm0
; CHECK-NEXT:    movd %r8d, %xmm3
; CHECK-NEXT:    punpcklwd {{.*#+}} xmm3 = xmm3[0],xmm0[0],xmm3[1],xmm0[1],xmm3[2],xmm0[2],xmm3[3],xmm0[3]
; CHECK-NEXT:    punpckldq {{.*#+}} xmm3 = xmm3[0],xmm2[0],xmm3[1],xmm2[1]
; CHECK-NEXT:    movd %ecx, %xmm0
; CHECK-NEXT:    movd %edx, %xmm2
; CHECK-NEXT:    punpcklwd {{.*#+}} xmm2 = xmm2[0],xmm0[0],xmm2[1],xmm0[1],xmm2[2],xmm0[2],xmm2[3],xmm0[3]
; CHECK-NEXT:    movd %esi, %xmm4
; CHECK-NEXT:    movd %edi, %xmm0
; CHECK-NEXT:    punpcklwd {{.*#+}} xmm0 = xmm0[0],xmm4[0],xmm0[1],xmm4[1],xmm0[2],xmm4[2],xmm0[3],xmm4[3]
; CHECK-NEXT:    punpckldq {{.*#+}} xmm0 = xmm0[0],xmm2[0],xmm0[1],xmm2[1]
; CHECK-NEXT:    punpcklqdq {{.*#+}} xmm0 = xmm0[0],xmm3[0]
; CHECK-NEXT:    movd {{.*#+}} xmm3 = mem[0],zero,zero,zero
; CHECK-NEXT:    pinsrw $1, {{[0-9]+}}(%rsp), %xmm3
; CHECK-NEXT:    pinsrw $2, {{[0-9]+}}(%rsp), %xmm3
; CHECK-NEXT:    pinsrw $3, {{[0-9]+}}(%rsp), %xmm3
; CHECK-NEXT:    movd {{.*#+}} xmm2 = mem[0],zero,zero,zero
; CHECK-NEXT:    pinsrw $1, {{[0-9]+}}(%rsp), %xmm2
; CHECK-NEXT:    pinsrw $2, {{[0-9]+}}(%rsp), %xmm2
; CHECK-NEXT:    pinsrw $3, {{[0-9]+}}(%rsp), %xmm2
; CHECK-NEXT:    movdqa %xmm0, %xmm4
; CHECK-NEXT:    pmulhuw %xmm1, %xmm4
; CHECK-NEXT:    pmullw %xmm1, %xmm0
; CHECK-NEXT:    movdqa %xmm0, %xmm1
; CHECK-NEXT:    punpckhwd {{.*#+}} xmm1 = xmm1[4],xmm4[4],xmm1[5],xmm4[5],xmm1[6],xmm4[6],xmm1[7],xmm4[7]
; CHECK-NEXT:    movdqa %xmm2, %xmm5
; CHECK-NEXT:    pmulhuw %xmm3, %xmm5
; CHECK-NEXT:    pmullw %xmm3, %xmm2
; CHECK-NEXT:    punpcklwd {{.*#+}} xmm2 = xmm2[0],xmm5[0],xmm2[1],xmm5[1],xmm2[2],xmm5[2],xmm2[3],xmm5[3]
; CHECK-NEXT:    punpcklwd {{.*#+}} xmm0 = xmm0[0],xmm4[0],xmm0[1],xmm4[1],xmm0[2],xmm4[2],xmm0[3],xmm4[3]
; CHECK-NEXT:    movdqa %xmm0, %xmm3
; CHECK-NEXT:    shufps {{.*#+}} xmm3 = xmm3[1,3],xmm1[1,3]
; CHECK-NEXT:    shufps {{.*#+}} xmm0 = xmm0[0,2],xmm1[0,2]
; CHECK-NEXT:    shufps {{.*#+}} xmm1 = xmm1[2,3],xmm2[0,1]
; CHECK-NEXT:    shufps {{.*#+}} xmm1 = xmm1[3,1,2,3]
; CHECK-NEXT:    pshufd {{.*#+}} xmm4 = xmm2[3,3,0,1]
; CHECK-NEXT:    unpcklps {{.*#+}} xmm1 = xmm1[0],xmm4[0],xmm1[1],xmm4[1]
; CHECK-NEXT:    paddd %xmm3, %xmm0
; CHECK-NEXT:    pshufd {{.*#+}} xmm2 = xmm2[0,2,1,3]
; CHECK-NEXT:    paddd %xmm1, %xmm2
; CHECK-NEXT:    movdqa %xmm0, %xmm1
; CHECK-NEXT:    shufps {{.*#+}} xmm1 = xmm1[1,3],xmm2[1,3]
; CHECK-NEXT:    shufps {{.*#+}} xmm0 = xmm0[0,2],xmm2[0,3]
; CHECK-NEXT:    paddd %xmm1, %xmm0
; CHECK-NEXT:    retq
entry:
  %a32 = zext <12 x i16> %a to <12 x i32>
  %b32 = zext <12 x i16> %b to <12 x i32>
  %prod12 = mul nuw <12 x i32> %a32, %b32
  %odd12 = shufflevector <12 x i32> %prod12, <12 x i32> undef, <6 x i32> <i32
1, i32 3, i32 5, i32 7, i32 9, i32 11>
  %even12 = shufflevector <12 x i32> %prod12, <12 x i32> undef, <6 x i32> <i32
0, i32 2, i32 4, i32 6, i32 8, i32 10>
  %prod6 = add <6 x i32> %odd12, %even12
  %odd6 = shufflevector <6 x i32> %prod6, <6 x i32> undef, <3 x i32> <i32 1,
i32 3, i32 5>
  %even6 = shufflevector <6 x i32> %prod6, <6 x i32> undef, <3 x i32> <i32 0,
i32 2, i32 4>
  %result = add <3 x i32> %odd6, %even6
  ret <3 x i32> %result
}