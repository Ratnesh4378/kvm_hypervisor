#include <stddef.h>
#include <stdint.h>

int flag=0;
static void outb(uint16_t port, uint8_t value) {
	asm("outb %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");
}

void HC_print8bit(uint8_t val)
{
	outb(0xE9, val);
}

void HC_print32bit(uint32_t val)
{
	// Fill in here
	asm volatile("outl %0,%1" : /* empty */ : "a"(val), "Nd"(0xE8) : "memory");
	//asm volatile("outl %0, $0xE8" : : "a"(val));  //Changes
	//val++;		// Remove this
}

uint32_t HC_numExits()
{
	// Fill in here
	uint32_t num_exits;
	asm volatile("inl %1, %0" : "=a"(num_exits) : "Nd"(0xEA) : "memory");
    //asm volatile("inl %%dx, %0" : "=a"(num_exits) : "d"(0xEA)); // Perform an input operation to read num_exits from port 0xE8
    return num_exits;
	//return 0;	// Remove this
}

void HC_printStr(char *str)
{
	// Fill in here
	//uintptr_t addr = (uintptr_t)str;
	 uintptr_t ptr = (uintptr_t)str; 
	//HC_print32bit((uint32_t)ptr);
	asm volatile("outl %0,%1" : /* empty */ : "a"((uint32_t)ptr), "Nd"(0xE7) : "memory");
	//asm volatile("outl %0, $0xE7" : : "a"((uint32_t)ptr)); 
	//str++;		// Remove this
}

char *HC_numExitsByType()
{
	// Fill in here
	char *str1;
	char *str;
	uint32_t res1;
	uint32_t res;
	//HC_print32bit(flag);
	if(flag==0){
		asm volatile("inl %1, %0" : "=a"(res1) : "Nd"(0xE6) : "memory");
		//asm volatile("inl %1, %0" : "=a"(res) : "d"(0xE6), "a"(ptr));
		//str=res;
		flag=1;
		//char* dummy="hjhkjhkjhkjhkhkhui0";
		//char* check1=res1;
		// while(check1[i]!='\0'){
		// 	*(str1+i)=check1[i];
		// 	i++;
		// }
		//HC_print32bit(i);
		//*(str1+i)='\0';
		//str1=res1;
		//str1="7777\n";
		//*(str1+7)='9';
		str1=(char*)(uintptr_t)res1;
		return str1;	// Remove this
	}
	else{
		asm volatile("inl %1, %0" : "=a"(res) : "Nd"(0xE6) : "memory");
		// char* check=res;
		// while(check[i]!='\0'){
		// 		*(str+i)=check[i];
		// 		i++;
		// 	}
		// *(str+i)='\0';
		str=(char*)(uintptr_t)res;
		//asm volatile("inl %1, %0" : "=a"(res) : "d"(0xE6), "a"(ptr));
		return str;	// Remove this
	}
}

uint32_t HC_gvaToHva(uint32_t gva)
{
	// Fill in here
	uint32_t hva;
	//HC_print32bit(gva);
	//uintptr_t ptr=(uintptr_t)&gva;
	asm volatile("outl %0,%1" : /* empty */ : "a"(gva), "Nd"(0xE5) : "memory");
	asm volatile("inl %1, %0" : "=a"(hva) : "Nd"(0xE4) : "memory");
	//asm volatile("outl %0,%1" : /* empty */ : "a"(gva), "Nd"(0xE7) : "memory");
	//asm volatile("outl %0, $0xE5" : : "a"(gva));
	//asm volatile("inl %1, %0" : "=a"((uint32_t)hva) : "d"(0xE5), "a"((uint32_t)gva));
	//gva++;		// Remove this
	return hva;	// Remove this
	//return 0;
}

void
__attribute__((noreturn))
__attribute__((section(".start")))
_start(void) {
	const char *p;

	for (p = "Hello 695!\n"; *p; ++p)
		HC_print8bit(*p);


	/*----------Don't modify this section. We will use grading script---------*/
	/*---Your submission will fail the testcases if you modify this section---*/
	HC_print32bit(2048);
	HC_print32bit(4294967295);

	uint32_t num_exits_a, num_exits_b;
	num_exits_a = HC_numExits();

	char *str = "CS695 Assignment 2\n";
	HC_printStr(str);

	num_exits_b = HC_numExits();

	HC_print32bit(num_exits_a);
	HC_print32bit(num_exits_b);

	char *firststr = HC_numExitsByType();
	uint32_t hva;
	hva = HC_gvaToHva(1024);
	HC_print32bit(hva);
	hva = HC_gvaToHva(4294967295);
	HC_print32bit(hva);
	char *secondstr = HC_numExitsByType();

	HC_printStr(firststr);
	HC_printStr(secondstr);
	/*------------------------------------------------------------------------*/

	*(long *) 0x400 = 42;

	for (;;)
		asm("hlt" : /* empty */ : "a" (42) : "memory");
}
