#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#define byte uint8_t
#define bit(b, t, of) (((b & t) > 0) << (of - 1))

#define P_BLOCK(_8, _7, _6, _5, _4, _3, _2, _1) \
return \
	bit(b, 0x01, _1) | \
	bit(b, 0x02, _2) | \
	bit(b, 0x04, _3) | \
	bit(b, 0x08, _4) | \
	bit(b, 0x10, _5) | \
	bit(b, 0x20, _6) | \
	bit(b, 0x40, _7) | \
	bit(b, 0x80, _8);

#define LOG(byte) printf("%s = %x ; %u\n", #byte, byte, byte)

byte
PB1(byte b)
{
	P_BLOCK(6, 8, 1, 7, 2, 4, 5, 3);
}

int
main(void)
{
	byte test = 0xAA;
	LOG(test);
	byte test_2 = PB1(test);
	LOG(test_2);
	
	return 0;
}
