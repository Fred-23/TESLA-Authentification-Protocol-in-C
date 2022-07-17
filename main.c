#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "md5.h"
#include "sender.h"



char data_raw[12]= "Hello World";
char *Pointer = &data_raw[12];

int main(){
	uint8_t *result;
  uint8_t *mac_result;
  //char *char_result;
  // We print the result of each key hash between 0 and 9
  result = md5String(data_raw);
  for(int i=0; i<10;i++){
	 
    printf("index %i   :", i);
	  print_hash(result);
    result = md5Number(result);
    //free(result);
    }

  mac_result=mac(result,data_raw);
  print_hash(mac_result);
  //Need improvement
  /*char_result = md5Char(data_raw);
  for(int i=0; i<10;i++){
    printf("index %i   :", i);
	  print_char_hash(char_result);
    char_result = md5Char(char_result);
    //free(result);
    }*/
}
