#include "functions.h"
#include "sender.h"

void print_packet(struct Packet_Tesla ppacket){
	printf("[Packet : Index   %i  | Message = %s | MAC =  ",ppacket.index, ppacket.message);
  print_hash(ppacket.mac);
	printf(" |  Key = ");
  print_hash(ppacket.key);
  printf(" ]");
  printf(" \n");
}
