#include "md5.h"
#include "receiver.h"
#include "sender.h"

//Receiver part to analyze the data and valid it

bool IsValidkey(uint8_t *pkey){
	uint8_t *someKey;
  someKey = md5Number(pkey);
  for(int i=0;i<size_n;i++){
    print_hash(someKey);

    //First Verification
    if (key_zero == someKey){
      return true;
    }
  }
  return false;
}