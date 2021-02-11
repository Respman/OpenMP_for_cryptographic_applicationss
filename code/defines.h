#pragma once

#define NUMBER_OF_FILES 2

#define ERR_PARSE_DATA 1
#define ERR_KEY_DERIVE 2
#define ERR_DECRYPT 3

#define BUF_SIZE 1024
#define BLOCK_START 14
#define SALT_LEN 20
#define HEADER_LEN (SALT_LEN + 4)
#define IV_LEN 16
#define PASS_LEN 8
#define ENC_LEN 80 
#define DIGEST_LEN 20
#define KEY_LEN 32

extern uint8_t buf[BUF_SIZE];
extern uint8_t salt[SALT_LEN];
extern uint32_t rounds_num; 
extern uint8_t iv[IV_LEN]; 
extern uint8_t header[HEADER_LEN];
extern uint8_t enc_data[ENC_LEN+1]; 
extern char checksum[DIGEST_LEN];
extern FILE* f_log;
