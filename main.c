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

  
  // We print the result of each packets
  keyObject = md5String(data_raw);
  
  resultpow=md5Pow(keyObject,1); //Index


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
    keyObject = md5Number(keyObject);
    print_packet(queue[i]);
    }
  
    //To free-up the memory
    //free(result);

  //TO change in stm32F4 (MAC TEST)
  printf("test mac:  ");
  mac_result=mac(resultpow,msg1);
  print_hash(mac_result);

  //Hardcoded Last Key (K0)
  key0=Table_of_Keys[number-1];
  printf("test Key 0 :  ");
  print_hash(key0);

  
}
