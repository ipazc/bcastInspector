
#ifndef _stormbcastfilter_h_
#define _stormbcastfilter_h_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "../networking.h"
#include "../list/macList.h"
#include <sys/time.h>

#define HEURISTIC_NAME "Broadcast packets per second, per source address.\n"
#define HEURISTIC_MAX_PACKETS_THRESHOLD 130

extern MacLinkedList *macLinkedList;
extern int highestStrike;
extern struct timeval lastTimeSnapshot;

void* processPacket(u_char *dummy, void *frameHeader, u_char *frame);

#endif /* _stormbcastfilter_h_ */