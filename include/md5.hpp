#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

namespace pt {

typedef unsigned int uint32;
typedef unsigned char uint8;

struct MD5Context {
    uint32 state[4];
    uint32 count[2];
    uint8 buffer[64];
};

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define FF(a, b, c, d, x, s, ac) { \
    (a) += F((b), (c), (d)) + (x) + (uint32)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G((b), (c), (d)) + (x) + (uint32)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H((b), (c), (d)) + (x) + (uint32)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
    (a) += I((b), (c), (d)) + (x) + (uint32)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

extern const uint8 PADDING[64];

void MD5Init(MD5Context* context);
void MD5Update(MD5Context* context, const uint8* input, uint32 inputLen);
void MD5Final(uint8 digest[16], MD5Context* context);
std::string md5_string(const std::string& input);

}