#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Packet_Tesla
{
   int index;
   char message[12];
   uint8_t *mac;
   uint8_t *key;
};

void print_packet(struct Packet_Tesla ppacket);
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

Les deux premiers packets doit être vide
Faire une impression des packets

Send the mac msg and not the key on the first two packet
Les deux premiers ont le message et le mac pas les clés
Puis on envoie k1 pas k2

Update the makeFIle
*/