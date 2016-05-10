#ifndef _iplist_h_
#define _iplist_h_

#include <stdlib.h>
#include <string.h>

typedef struct MacLinkedList
{
    struct MacLinkedList * nextNode;
    u_char mac[6];
    int count;
} MacLinkedList;

MacLinkedList * createList();

/**
 * Increases the broadcast counter for the specified IP and returns the count of packets for this IP
 */
int registerBroadcastFrameForSource(MacLinkedList *list, const u_char *mac);

/**
 * Returns 1 if macs are equals. 0 otherwise
 */
int macEquals(u_char* mac1, u_char* mac2);

void assignMac(u_char* macDst, u_char* macSrc);

int macEmpty(u_char* mac);

void resetCounters(MacLinkedList * list);

void freeList(MacLinkedList * list);

#endif /* _iplist_h_ */