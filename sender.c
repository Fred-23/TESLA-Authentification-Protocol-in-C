
#include "sender.h"
#include "md5.h"




//File for generating the key hash
void print_bytes(void *p, size_t length){
	uint8_t *pp = (uint8_t *)p;
	for(unsigned int i = 0; i < length; ++i){
		if(i && !(i % 16)){
			printf("\n");
		}
		printf("%02X ", pp[i]);
	}
	printf("\n");
}

void print_hash(uint8_t *p){
	for(unsigned int i = 0; i < 16; ++i){
		printf("%02x", p[i]);
	}
	printf("\n");
}

void print_char_hash(char *p){
	for(unsigned int i = 0; i < 16; ++i){
		printf("%02X", p[i]);
	}
	printf("\n");
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

uint8_t* mac(uint8_t *pkey, char *message ){
  uint8_t *pmac;
  
	//concatenate the key and message then do the hash
  pmac=pkey+(*message);
  pmac=md5Number(pmac);
	return pmac;
}