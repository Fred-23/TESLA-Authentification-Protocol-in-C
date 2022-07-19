#include "sender.h"
#include "md5.h"
//https://code-examples.net/fr/q/101092

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



uint8_t* mac(uint8_t *pkey, char *message ){
  uint8_t *pmess=malloc(16);
  uint8_t *pfinal=malloc(16);
  uint8_t operation;
  uint8_t *poper=malloc(16);
	//concatenate the key and message then do the hash
  memcpy(pmess, message, 16);
  operation= *pmess+*pkey;
  *poper= operation;
  pfinal=md5Number(poper);
	return pfinal;
}

uint8_t* md5Pow(uint8_t *keytohashpow, int iteration){
  uint8_t *powkey;
  powkey=keytohashpow;
  for(signed int i = 0; i < iteration; ++i){
    powkey=md5Number(powkey);
	}
  //print_hash(powkey);
  return powkey;
}


