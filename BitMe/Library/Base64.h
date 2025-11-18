#ifndef __BASE_64_H__
#define __BASE_64_H__

#include <string>
#include <vector>
#include <cstdint>

std::string BinaryToBase64(const uint8_t *data, size_t bytes);
std::string BinaryToBase64(const std::vector<uint8_t> &data);
std::vector<uint8_t> Base64ToBinary(const char *s);
std::vector<uint8_t> Base64ToBinary(const std::string &s);

#endif