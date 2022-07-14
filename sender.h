#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void print_bytes(void *p, size_t length);
void print_hash(uint8_t *p);
void print_char_hash(char *p);
char* concat(const char *s1, const char *s2);
char* mac(char *pkey, char *message );