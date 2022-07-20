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
int global_time = 3;  //Initialize only for the Replit


uint8_t* Table_of_Keys[10]={0};
char data_raw[12]= "Hello World";
char msg1[12]= "TU WIEN";
//char *Pointer = &data_raw[12];

struct Packet_Tesla queue[12];
uint8_t* receiver_buffer[10]={0};
uint8_t* _buff[10]={0};

int main(){
	uint8_t *key0;
  uint8_t *keyObject;
  uint8_t *MACmsg;
  uint8_t *resultpow = malloc(16);
  uint8_t *mac_result;
  uint8_t *zero = malloc (16);

  
  // We print the result of each packets
  keyObject = md5String(data_raw);
  
  resultpow=md5Pow(keyObject,1);//Index
  print_hash(resultpow);


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
    memcpy(queue[i].message, msg1, 12);
    //queue[i].message=msg1;
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

  
  //-------------------Receiver Part----------------------//*

  //This part will really change when implementate in the drone
  for(int p=0; p<number-1;p++){
    uint8_t *varpow =malloc(16);
    uint8_t *mac_rst = malloc(16);
    bool compare_result=false;
    
    free(varpow);
    free(mac_rst);
    //Vérifier que le packet est none
    
      receiver_buffer[p]=queue[p].key;
      if(queue[p].key ==zero){
        printf("receiver : got the packet");
        }
      else{
        if(global_time>delay){
          if(IsValidkey(receiver_buffer[p],key0,number)){
            printf("Valid Key\n");
            //_buff=receiver_buffer;
            //On copie une certaine taille d'un tableau
            //Puis on parcoure le buffer et on execute la vérification
            //plus qu'à trouver une solution pour copier les buffer et le programmes devrait être quasi-fini
           // Ma solution faire un strlen puis à partir du nombre faire un boucle qui . Puis gérer l'exponentielle
            compare_result = false;
            
            for(int it=0; it<number-1;it++){
            int exp=0;
            
              
              printf("%i \n",p);
              if (*mac_rst == *queue[p].mac){
                print_hash(varpow);
                print_hash(mac_rst);
                print_hash(queue[p].mac);
                compare_result=true;
                printf("receiver : authentification successful for %s   \n", queue[p].message);
                
              }
              else{
                exp = delay-queue[it].index-p;
                varpow=md5Pow(receiver_buffer[p],exp);
                mac_rst=mac(varpow, queue[p].message);
              }
              
            }
            if (compare_result==false) {
                printf("receiver : authentification failed for %s   \n", queue[p].message);
                
              }
          }
          else {
            printf("receiver : not a valid key \n");
          }
        }
    
      
        } 
    }
}
