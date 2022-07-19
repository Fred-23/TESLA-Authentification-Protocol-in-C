#include "md5.h"
#include "receiver.h"
#include "sender.h"

//Receiver part to analyze the data and valid it

bool IsValidkey(uint8_t *pkey,uint8_t *key_zero, int number_of_keys){
	uint8_t *someKey=key_zero;
  for(int i=0;i<number_of_keys;i++){
    //print_hash(someKey);
    //First Verification
    if (someKey == pkey){
      return true;
    }
    someKey = md5Pow(pkey,i);
  }
  return false;
}