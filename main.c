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

Test all the new functions and try to authentificate some message. Modify the sender to send message after some index (2) ok

Only thing to do it's the receiver part that will take a table of structure and try to authentificate the message

Also do a lot of print for the packet to now what it's been send everytime
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
	uint8_t *key0;
  uint8_t *keyObject;
  uint8_t *MACmsg;
  uint8_t *resultpow = malloc(16);
  uint8_t *mac_result;
  //char *char_result;
  // We print the result of each key hash between 0 and 9
  keyObject = md5String(data_raw);
  //ko last key
  resultpow=md5Pow(keyObject,1); //Index
  //print_hash(resultpow);

  
  //-------------------Sender Part----------------------//
  for(int i=0; i<number;i++){
    
    
    Table_of_Keys[i]=keyObject;
    queue[i].index=i;
    if(i>=delay){ 
      MACmsg = mac(Table_of_Keys[i],msg1);
      queue[i].mac=MACmsg;
      printf("MAC msg :  ");
      print_hash(queue[i].mac); 
      }
    queue[i].key=keyObject;
    keyObject = md5Number(keyObject);
    
    printf("index %i   :", i);
	  print_hash(Table_of_Keys[i]);
    
    }
    //To free-up the memory
    //free(result);

  //Will change in stm32F4
  printf("test mac:  ");
  mac_result=mac(resultpow,msg1);
  print_hash(mac_result);
  
  key0=queue[number-1].key;
  printf("test Key 0 :  ");
  print_hash(key0);
}
