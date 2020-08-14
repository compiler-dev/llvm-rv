#include<riscv_vector.h>
#include<stdio.h>

#define VLEN 128
#define SEW 16
#define LMUL 1

static void print_value(int16_t *vv, uint32_t avl)
{
	printf("{");
	for(int i = 0; i< avl -1; i++)
		printf("0x%04x,", *(vv+i));
	printf("0x%04x",  *(vv+avl-1));
	printf("}\n");
}

int compare_result(vint16m1_t a, int16_t b[], uint32_t vl)
{
	for(int i = 0; i<vl; i++)
	   if(a[i] != b[i])
	     return 1;
	return 0;
}


int main()
{
	uint32_t avl = LMUL*VLEN/SEW;
	uint32_t vl;
	 
	vl = vsetvli(avl,RVV_E16,RVV_M1,RVV_D1);
	vint16m1_t a = {0x7ffc,0x7ffd,0x7ffe,0x7fff,0x8000,0x8001,0x8001,0x8003};
	vint16m1_t b = {1,2,3,4,5,6,7,8};
	vint16m1_t c = {0};	
	
	int16_t expect[LMUL*VLEN/SEW] = {0};
	for(int i = 0; i<vl; i++)
		expect[i] = a[i] + b[i];
	
	printf("Expect:\n");
        print_value(expect,vl);


	c = vadd_vv_i16m1(a,b);
	
	int16_t actual[LMUL*VLEN/SEW] = {0};
	for(int i = 0; i<vl; i++)
		actual[i] = c[i];
	printf("Actual:\n");
	print_value(actual,vl);

	int result = compare_result(c,expect,vl);
	if(result == 0)
		printf("pass!\n");
	else
		printf("fail!\n");

	return 0;
}
