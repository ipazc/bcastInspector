#include <stdio.h>
#include "src/filters/stormbcastfilter.h"


int main()
{
    macLinkedList = createList();
    printFilterHeuristic(HEURISTIC_NAME);
    performCapture(ALL_PACKETS, processPacket);
    freeList(macLinkedList);
    return 0;
}