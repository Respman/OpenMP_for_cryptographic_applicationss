#include "defines.h"

int to_bytes(char* data, uint8_t* buf)
{
	char byte ;
	if (strlen(data) % 2)	
		return -1 ;
	auto len = strlen(data) / 2 ;
	if (len > BUF_SIZE)
		return -1 ;
	for (auto i = 0 ; i < len ; i++)
	{
		byte = data[2*i] ;
		if (byte >= '0' && byte <= '9')
			buf[i] = byte - 0x30 ;
		else if (byte >= 'A' && byte <= 'F')
			buf[i] = byte - 0x37 ;
		else if (byte >= 'a' && byte <= 'f')
			buf[i] = byte - 0x57 ;
		else
			return 2*i + 1 ;
		buf[i] <<= 4 ;
		byte = data[2*i + 1] ;
		if (byte >= '0' && byte <= '9')
			buf[i] |= byte - 0x30 ;
		else if (byte >= 'A' && byte <= 'F')
			buf[i] |= byte - 0x37 ;
		else if (byte >= 'a' && byte <= 'f')
			buf[i] |= byte - 0x57 ;
		else
			return 2*i + 2 ;
	}	
	return 0 ;
}

