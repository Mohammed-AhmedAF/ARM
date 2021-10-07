
int __svc(0x00) svc_service_add(int x, int y);
int __svc(0x01) svc_service_sub(int x, int y);
int __svc(0x02) svc_service_mul(int x, int y);
int __svc(0x03) svc_service_div(int x, int y);


int x, y, z;
int main(void)
{
	x = 6;
	y = 4;
	z = svc_service_add(x,y);
	
	x = 4;
	y = 3;
	z = svc_service_mul(x,y);
	
}

__asm void SVC_Handler(void)
{
	/*Testing link register*/
	TST LR, #4
	ITE EQ
	MRSEQ R0, MSP
	MSRNE R0, PSP
	B __cpp(svc_handler_c)
}

void svc_handler_c(int * svc_args)
{
	unsinged int svc_number;
	svc_number = ((char*)svc_args[6][-2];
}