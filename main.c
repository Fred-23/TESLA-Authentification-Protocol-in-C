#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "md5.h"
#include "sender.h"

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
