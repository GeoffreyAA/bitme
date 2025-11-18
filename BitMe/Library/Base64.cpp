#include "stdafx.h"
#include "Base64.h"
#include <assert.h>

const uint8_t Base64Alphabet[] = {

	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'

};

uint32_t Make24BitBlock(uint8_t byte1, uint8_t byte2, uint8_t byte3)
{
	uint32_t x = byte1;
	uint32_t y = byte2;
	uint32_t z = byte3;

	return (x << 16) | (y << 8) | z;
}

uint8_t GetSextet(uint32_t _24_bit_block, size_t index)
{
	assert(0 <= index && index < 4);

	if (index < 4)
	{
		return (uint8_t)((_24_bit_block >> 6 * (3 - index)) & 0x3F);
	}

	return 0;
}

uint8_t GetBase64Char(uint8_t sextet)
{
	assert(0 <= sextet && sextet < 64);

	return (sextet < 64) ? Base64Alphabet[sextet] : 0;
}

std::string BinaryToBase64(const uint8_t *data, size_t bytes)
{
	std::string s;

	if (data)
	{
		while (bytes--)
		{
			uint8_t byte1 = *data++;
			uint8_t byte2 = 0;
			uint8_t byte3 = 0;

			if (bytes)
			{
				byte2 = *data++;
				bytes--;
			}

			if (bytes)
			{
				byte3 = *data++;
				bytes--;
			}

			uint32_t block = Make24BitBlock(byte1, byte2, byte3);

			for (size_t i = 0; i < 4; i++)
			{
				s.append(1, GetBase64Char(GetSextet(block, i)));
			}
		}
	}

	return s;
}

std::string BinaryToBase64(const std::vector<uint8_t> &data)
{
	return BinaryToBase64(data.data(), data.size() * sizeof(uint8_t));
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t GetBase64Sextet(uint8_t base64char)
{
	for (size_t i = 0; i < sizeof(Base64Alphabet) / sizeof(Base64Alphabet[0]); i++)
	{
		if (Base64Alphabet[i] == base64char)
			return (uint8_t)i;
	}

	return 0;
}

uint32_t Make24BitBlock(uint8_t sextet1, uint8_t sextet2, uint8_t sextet3, uint8_t sextet4)
{
	uint32_t a = sextet1;
	uint32_t b = sextet2;
	uint32_t c = sextet3;
	uint32_t d = sextet4;

	return (a << 18) | (b << 12) | (c << 6) | d;
}

std::vector<uint8_t> Base64ToBinary(const char *s)
{
	std::vector<uint8_t> b;

	if (s)
	{
		while (*s)
		{
			uint8_t sextet1 = 0;
			uint8_t sextet2 = 0;
			uint8_t sextet3 = 0;
			uint8_t sextet4 = 0;

			sextet1 = GetBase64Sextet(*s++);
			if (*s)	sextet2 = GetBase64Sextet(*s++);
			if (*s)	sextet3 = GetBase64Sextet(*s++);
			if (*s)	sextet4 = GetBase64Sextet(*s++);

			uint32_t block = Make24BitBlock(sextet1, sextet2, sextet3, sextet4);

			b.push_back((block >> 16) & 0xFF);
			b.push_back((block >> 8)  & 0xFF);
			b.push_back(block & 0xFF);
		}
	}

	return b;
}

std::vector<uint8_t> Base64ToBinary(const std::string &s)
{
	return Base64ToBinary(s.c_str());
}