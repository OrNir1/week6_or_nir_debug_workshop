#include "part2.h"
#include <iostream>
#include <stdexcept>

char* safe_string_copy(char* dest, unsigned int destsize, char* src)
{
	unsigned int srcsize = (unsigned int)strlen(src);
	if (srcsize >= destsize)
		throw std::overflow_error("possible buffer overflow");

	char* ret = dest;
	unsigned int i = 0;
	for (i = 0; i < srcsize * sizeof(*src); i++)
		*dest++ = *src++;
	//filling in the remaining parts of dest with 0
	for (i; i < destsize;i++) {
		*dest++ = 0;
	}

	return ret;
}


#define BUF_SIZE 20
void part2()
{
	char password[] = "secret";
	char dest[BUF_SIZE];
	char src[] = "hello world!";

	safe_string_copy(dest, BUF_SIZE, src);

	//the problem is it copies the str into dest but doesnt delete the current contents of dest

	std::cout << src << std::endl;
	std::cout << dest << std::endl;
}
