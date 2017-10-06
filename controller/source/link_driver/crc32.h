#ifndef CRC_32_H
#define CRC_32_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned long calculate_crc(const unsigned char* buf, unsigned buflen);
unsigned long CRC32(unsigned  char ch, unsigned long crc);
unsigned long crc_file (const char* filename);
void crc_to_buf (unsigned long crc, unsigned char* ret);
unsigned long buf_to_crc (const unsigned char*);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
