
#include "macList.h"
#include "../networking.h"

MacLinkedList * createList()
{
    MacLinkedList * list = (MacLinkedList *)malloc(sizeof(MacLinkedList)*1);

    list->count = 0;
    list->nextNode = NULL;
    list->mac[0] = 0;
    list->mac[1] = 0;
    list->mac[2] = 0;
    list->mac[3] = 0;
    list->mac[4] = 0;
    list->mac[5] = 0;

    return list;
}


int registerBroadcastFrameForSource(MacLinkedList *list, const u_char *mac)
{
    int counter = 0;

    while (list->nextNode && !counter)
    {
        if (macEquals(list->mac, mac))
        {
            list->count += 1;
            counter = list->count;
        }

        list = list->nextNode;
    }

    if (!counter)
    {
        assignMac(list->mac, mac);
        list->count = 1;
        list->nextNode = createList();
        counter = 1;
    }

    return counter;
}

void assignMac(u_char* macDst, u_char* macSrc)
{
    int i;
    for (i = 0; i < MAC_BYTES_SIZE; i++)
        macDst[i] = macSrc[i];
}

int macEmpty(u_char* mac)
{
    int macEmpty = 1;
    int i;

    for (i = 0; i < MAC_BYTES_SIZE; i++)
        if (mac[i])
            macEmpty = 0;

    return macEmpty;
}

void resetCounters(MacLinkedList * list)
{
    while (list->nextNode)
    {
        list->count = 0;
        list = list->nextNode;
    }
}

int macEquals(u_char* mac1, u_char* mac2)
{
    int i;
    int macEquals = 1;

    for (i = 0; i < MAC_BYTES_SIZE; i++) {
        if (mac1[i] != mac2[i])
            macEquals = 0;
    }

    return macEquals;
}

void freeList(MacLinkedList * list)
{
    MacLinkedList * auxList;
    while (list)
    {
        auxList = list->nextNode;
        free(list);
        list = auxList;
    }
}