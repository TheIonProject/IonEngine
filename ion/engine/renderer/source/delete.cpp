#include <iostream>

#include "Buffer.h"

int trash(void)
{
	ion::Buffer<ION_VERTEX_BUFFER> a;
	(void) a;

	std::cout << "sup\n";
	return 1;
}