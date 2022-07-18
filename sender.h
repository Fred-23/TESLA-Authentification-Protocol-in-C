#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void print_bytes(void *p, size_t length);
void print_hash(uint8_t *p);
void print_char_hash(char *p);
char* concat(const char *s1, const char *s2);
uint8_t* mac(uint8_t *pkey, char *message );
uint8_t* md5Pow(uint8_t *keytohashpow, int iteration);
