#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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


char data_raw[12]= "Hello World";
char *Pointer = &data_raw[12];

int main(){
	uint8_t *result;
  //Also we can't get use SHA-1
  /*print_hash(md5Number(md5String(data_raw)));
  print_hash(md5Number(md5String(data_raw)));*/

  result = md5String(data_raw);
  for(int i=0; i<11;i++){
	 
    printf("index %i   :", i);
	  print_hash(result);
    result = md5Number(result);
    //free(result);
    }


  
}
