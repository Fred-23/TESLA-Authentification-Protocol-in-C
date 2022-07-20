#include "md5.h"
#include "receiver.h"
#include "sender.h"
//00663e2855ddb1d7ba9ae17ffaef4f64
//00663e2855ddb1d7ba9ae17ffaef4f64  
//Receiver part to analyze the data and valid it

bool IsValidkey(uint8_t *pkey,uint8_t *key_zero, int number_of_keys){
	uint8_t *someKey;
  someKey = md5Number(pkey);
  //someKey = key_zero;
  bool result= false;
  for(int i=0;i<number_of_keys;i++){
    //print_hash(someKey);
    //print_hash(key_zero);
    //First Verification
    if (*someKey == *key_zero){
      result =true;
      //printf("VALIDDD");
    }
    else{
      someKey = md5Number(someKey);
    }
    
  }
  return result;
}