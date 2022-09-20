#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

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
#define LOG2(bytes) \
	LOG(bytes[0]); \
	LOG(bytes[1]);
#define LOG2_LINE(bytes) printf("%s = %c%c%c%c ; %u\n", #bytes, LOG_BYTE(bytes[1]), LOG_BYTE(bytes[0]), (bytes[1] << 8) + bytes[0]);
// #define LOG3_LINE(bytes) printf("%s = %c%c%c%c%c%c ; %u\n", #bytes LOG_BYTE(bytes[2]), LOG_BYTE(bytes[1]), LOG_BYTE(bytes[0])

byte
PB1(byte b)
{
	P_BLOCK(6, 8, 1, 7, 2, 4, 5, 3);
}

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
	// DEFEND(n, "LOG_LINE_FUNC insufficient n");
	printf("%s = ", bar_name);
	for (byte i = n-1; i < n; i--) {
		printf("%c%c", LOG_BYTE(bar[i]));
	}
	puts(" ;"); 
}

#define LOG_LINE(bar, n) LOG_LINE_FUNC(#bar, bar, n)

byte *
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
	
	LOG_CODE();
	return 0;
}
