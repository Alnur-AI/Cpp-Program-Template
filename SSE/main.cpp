
#include <emmintrin.h>
#include <iostream>
#include "stdio.h"
int main(){

	__m128i m2 = _mm_setr_epi16(2, 4, 6, 8, 12, 1, 14, 16);
	std::cout << m2[0] << std::endl;
}
