#include "defines.h"

#include <cstring>
#include <string>

using namespace std;

#define BLOCK_SIZE 16

const char printables[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+, -./:;<=>?@[\\]^_`{|}~ \r\n\t\0" ;

unsigned int is_printable(string data)
{
	unsigned int cnt = 0 ;
	for (auto i = 0 ; i < ENC_LEN / BLOCK_SIZE ; i++)
	{
		for (auto j = 0 ; j < BLOCK_SIZE ; j++)
			if (!strchr(printables, data[i*BLOCK_SIZE + j]))
				goto skip ;
		cnt++ ;
		skip:
				continue ;	
	}
	return cnt ;
}
