#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "md5.h"
#include "functions.h"
#include "sender.h"
#include "receiver.h"


//pointers

#define D = 1s //unit of time

int delay = 2 ;// key disclosure delay
int number = 10 ;// numbers of key

uint8_t* Table_of_Keys[10]={0};
char data_raw[12]= "Hello World";
char msg1[12]= "TU WIEN";
//char *Pointer = &data_raw[12];

struct Packet_Tesla queue[12];

int main(){
	uint8_t *key0;
  uint8_t *keyObject;
  uint8_t *packetvar = malloc (16);
  uint8_t *MACmsg;
  uint8_t *resultpow = malloc(16);
  uint8_t *mac_result;
  uint8_t *zero = malloc (16);
  //char *char_result;
  // We print the result of each key hash between 0 and 9
  keyObject = md5String(data_raw);
  //k0 last key
  resultpow=md5Pow(keyObject,1); //Index
  //print_hash(resultpow);

  //-------------------Sender Part----------------------//
  for(int i=0; i<number;i++){
    
    Table_of_Keys[i]=keyObject;
    queue[i].index=i;
    if (i<delay){
      queue[i].key=zero;
    }
    else {
      queue[i].key=Table_of_Keys[i-1];
    }
    
    MACmsg = mac(Table_of_Keys[i],msg1);
    queue[i].mac=MACmsg;
    //printf("MAC msg :  ");
    //print_hash(queue[i].mac); 
    keyObject = md5Number(keyObject);
    //printf("index %i  Key  :", i);
	  //print_hash(Table_of_Keys[i]);
    print_packet(queue[i]);
    }
    //To free-up the memory
    //free(result);

  //Will change in stm32F4 (MAC TEST)
  /*printf("test mac:  ");
  mac_result=mac(resultpow,msg1);
  print_hash(mac_result);*/

  //Hardcoded First Key
  key0=Table_of_Keys[number-1];

  
  printf("test Key 0 :  ");
  print_hash(key0);
}
