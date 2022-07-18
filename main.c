#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "md5.h"
#include "sender.h"

//TO DO
/*
Check the table of keys (init plus incrementation)
and md5Pow function OK
mac with the same message OK
Do the receiver part as python but make something different for the index, maybe an interruption or an condition in parallel
In a first time don't lose to much time on that because it will be use differently in the drone
Put a lot of comments for my tutor
Test all the new functions and try to authentificate some message. Modify the sender to send message after some index (2)
*/

uint8_t* Table_of_Keys[10]={0};
char data_raw[12]= "Hello World";
char *Pointer = &data_raw[12];

int main(){
	uint8_t *result;
  uint8_t *resultpow = malloc(16);
  uint8_t *mac_result;
  //char *char_result;
  // We print the result of each key hash between 0 and 9
  result = md5String(data_raw);
  resultpow=md5Pow(result,2);
  //print_hash(resultpow);
  //-------------------Sender Part----------------------//
  for(int i=0; i<10;i++){
	  Table_of_Keys[i]=result;
    printf("index %i   :", i);
	  print_hash(result);
    print_hash(Table_of_Keys[i]);
    result = md5Number(result);

      /*struct Packet_Tesla
        {
           int index;
           char message[12];
           uint8_t *mac;
           uint8_t *key;
        };*/  
    //--------Use packets structure----//

    //free(result);
    }

  mac_result=mac(result,data_raw);//Will change in stm32 so not a issue only not for the reicever
  print_hash(mac_result);

  
  //mac_result=mac(result,);//Will change in stm32 so not a issue only not for the reicever
  //print_hash(mac_result);
  //Need improvement
  /*char_result = md5Char(data_raw);
  for(int i=0; i<10;i++){
    printf("index %i   :", i);
	  print_char_hash(char_result);
    char_result = md5Char(char_result);
    //free(result);
    }*/
}
