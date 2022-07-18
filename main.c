#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "md5.h"
#include "sender.h"

#define D = 1s //unit of time

int delay = 2 ;// key disclosure delay
int number = 10 ;// numbers of key
//TO DO
/*
Check the table of keys (init plus incrementation) OK
and md5Pow function OK
mac with the same message OK

Do the receiver part as python but make something different for the index, maybe an interruption or an condition in parallel
Not necessary since we have a node and a anchor

Put a lot of comments for my tutor

Test all the new functions and try to authentificate some message. Modify the sender to send message after some index (2)

Mieux gérer les pacquets
*/
struct Packet_Tesla
{
   int index;
   char message[12];
   uint8_t *mac;
   uint8_t *key;
};

uint8_t* Table_of_Keys[10]={0};
char data_raw[12]= "Hello World";
char msg1[12]= "TU WIEN";
//char *Pointer = &data_raw[12];

struct Packet_Tesla queue[12];

int main(){
	uint8_t *first_key;
  uint8_t *keyObject;
  uint8_t *MACmsg;
  uint8_t *resultpow = malloc(16);
  uint8_t *mac_result;
  //char *char_result;
  // We print the result of each key hash between 0 and 9
  first_key = md5String(data_raw);
  //I must change that to get the last key
  resultpow=md5Pow(first_key,2);
  //print_hash(resultpow);

  keyObject=first_key;
  //-------------------Sender Part----------------------//
  for(int i=0; i<number;i++){
    
    if(i<delay){
      Table_of_Keys[i]=keyObject;
      queue[i].index=i;
      queue[i].key=keyObject;
      keyObject = md5Number(keyObject);
    }
    else{
      MACmsg = mac(keyObject,msg1);
      Table_of_Keys[i]=keyObject;
      queue[i].index=i;
      queue[i].mac=MACmsg;
    }
    printf("index %i   :", i);
	  print_hash(Table_of_Keys[i]);
      
  //print_hash(Table_of_Keys[i]);*
    
      /*struct Packet_Tesla
        {
           int index;
           char message[12];
           uint8_t *mac;
           uint8_t *key;
        };*/  
    //--------Use packets structure----//

    }
    //To free-up the memory
    //free(result);
  
  mac_result=mac(resultpow,msg1);
  //Will change in stm32F4
  print_hash(mac_result);
 
}
