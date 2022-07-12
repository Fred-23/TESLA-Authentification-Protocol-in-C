#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "md5.h"

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

/*int main(int argc, char *argv[]){
	uint8_t *result;
	if(argc > 1){
		for(int i = 1; i < argc; ++i){
			result = md5String(argv[i]);
			print_hash(result);
		}
	}
	else{
		result = md5File(stdin);
		print_hash(result);
	}

	free(result);
}*/
char data_raw[12]= "Hello World";
char *Pointer = &data_raw[12];

int main(){
	//uint8_t *result;
  //Maybe use SHA-1  instead because it's to random we don't get the same thing everytime
  print_hash(md5Number(md5String("t")));
  print_hash(md5Number(md5String("t")));

  /*result = md5String(data_raw);
  for(int i=0; i<11;i++){
	 
    printf("index %i   :", i);
	  print_hash(result);
    result = md5Number(result);
    //free(result);
    }
*/

  
}
