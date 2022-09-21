#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>

#define byte uint8_t
#define number uint32_t
#define BYTE_NUM 4
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

#define HEX_STR "0123456789ABCDEF"
#define LOG_BYTE(byte) (HEX_STR[((byte&0xF0) >> 4)]), (HEX_STR[(byte&0xF)])
#define LOG(byte) printf("%s = %c%c ; %u\n", #byte, LOG_BYTE(byte), byte)
#define LOG_NUM(num) printf("%s = %u;\n", #num, num);
#define LOG2(bytes) \
	LOG(bytes[0]); \
	LOG(bytes[1]);

static inline
void
die(char *str)
{
	puts(str);
	exit(1);
}

#define DEFEND(n, string) \
	if (n > BYTE_NUM || n == 0) { \
		LOG(n); \
		die(string); \
	}

void
LOG_LINE_FUNC(const char *bar_name, byte *bar, byte n)
{
	printf("%s = ", bar_name);
	for (byte i = n-1; i < n; i--) {
		printf("%c%c", LOG_BYTE(bar[i]));
	}
	puts(" ;"); 
}

#define LOG_LINE(bar, n) LOG_LINE_FUNC(#bar, bar, n)

void
PB_M(byte *bar, byte n, byte (*PB_fun)(byte))
{
	DEFEND(n, "PB_M insufficient n");
	for (byte i = 0; i < n; i++) {
		bar[i] = PB_fun(bar[i]);
	}
}

#define _2PB(bar, PB_fun) PB_M(bar, 2, PB_fun);


#define GET_BYTE(num, n) ((num >> (8*n)) & 0xFF)
#define POST_BYTE(byte, n) byte << (8*n)

void
CUT_LAST_OFT(byte *bar, number num, byte n, byte bof)
{
	DEFEND(n, "CUT_LAST insufficient n");
	byte tmp;
	for (byte i = 0; i < n; i++) {
		bar[i + bof] = GET_BYTE(num, i);
	}
}

#define CUT_LAST(bar, num, n) CUT_LAST_OFT(bar, num, n, 0)

#define SV 0x5EBA

#define CODE_LEN 8
byte tb[2] = {0};
byte fb[4] = {0};
byte code[CODE_LEN] = {0};

#define LOG_CODE() LOG_LINE(code, CODE_LEN);

byte
PB1_1(byte b)
{
	P_BLOCK(6, 8, 1, 7, 2, 4, 5, 3);
}

byte
PB1_2(byte b)
{
	P_BLOCK(7, 1, 5, 8, 3, 6, 4, 2);
}

void
get_bits(number num, byte *bar)
{
	for (byte i = 0; i < 8; i++) {
		bar[i] = ((num >> (i*0x3)) & 0x3);
	}
}

byte
PB_CONSTRUCT_FROM_NUM(byte b, number num)
{
	byte bar[8] = {0};
	get_bits(num, bar);
	P_BLOCK(bar[7], bar[6], bar[5], bar[4], bar[3], bar[2], bar[1], bar[0]);
}

byte
PB_CONSTRUCT(byte b, byte *bar)
{
	P_BLOCK(bar[7], bar[6], bar[5], bar[4], bar[3], bar[2], bar[1], bar[0]);
}

#define b_line_len 32
#define bll b_line_len

void
test_PB(byte (*PB)(byte))
{
	byte line[bll] = {0};
	byte start_val = 0;
	do {
		for (byte i = 0; i < bll; i++) { line[i] = start_val++; };
		//
		for (byte i = 0; i < 65; i++) {
			for (byte j = 0; j < bll; j++) {
				if (j > 1 && j % 16 == 0) { printf(" | "); }
				printf("%c%c ", LOG_BYTE(line[j]));
				line[j] = PB(line[j]);
			}
			printf("\n");
		}
		printf("\n");
		//
	} while (start_val != 0);
}

#define used_byte 255

void
gen_random_PB()
{
	byte bits[8];
	{
		byte keys[8];
		for (byte i = 0; i < 8; i++) {
			keys[i] = i;
		}
		LOG_LINE(keys, 8);
		byte used_keys = 0;
		byte last_indx = 0;
		byte randb = 0;
		byte rand_indx = 0;
		srand(time(NULL));
		while (used_keys != 8) {
			if (used_keys == 7) {
				bits[used_keys] = keys[last_indx];
				break;
			}	
			rand_indx = rand() % 8;
			randb = keys[rand_indx];
			if (randb == used_byte) { continue; }
			bits[used_keys++] = randb;
			last_indx ^= rand_indx;
			keys[rand_indx] = used_byte;
		}
	}
	LOG_LINE(bits, 8);
	test_PB(PB1_1);
}

//

#define HIGH 1
#define LOW 0

static inline void
place_tb(byte *fb, byte *tb, byte pos)
{
	if (pos) {
		fb[3] = tb[1];
		fb[2] = tb[0];
	} else {
		fb[1] = tb[1];
		fb[0] = tb[0];
	}
}

static inline void
place_fb(byte *code, byte *fb, byte pos)
{
	if (pos) {
		for (byte i = 0; i < 4; i++) {
			code[i+4] = fb[i];
		}
	} else {
		for (byte i = 0; i < 4; i++) {
			code[i] = fb[i];
		}
	}
}

void
create_promocode(number num)
{
	
}

int
main(void)
{
	// test_PB(PB1_2);
	gen_random_PB();
	return 0;
}
