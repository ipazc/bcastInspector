
#include "stormbcastfilter.h"

MacLinkedList *macLinkedList = NULL;
struct timeval lastTimeSnapshot;
int highestStrike = 0;

void* processPacket(u_char *dummy, void *frameHeader, u_char *frame)
{
    const struct pcap_pkthdr * frameHeaderContent = (const struct pcap_pkthdr*) frameHeader;
    struct timeval currentTimeSnapshot;

    gettimeofday(&currentTimeSnapshot, NULL);

    int elapsedTime = abs(currentTimeSnapshot.tv_sec - lastTimeSnapshot.tv_sec);

    if (elapsedTime > 1)
    {
        resetCounters(macLinkedList);
        highestStrike = 0;
        lastTimeSnapshot = currentTimeSnapshot;
    }

    MacsOfFrame macsOfFrame = getMacsOfFrame(frame);
    printf("\rPacket received. [s: \"");
    printMac(macsOfFrame.origin);
    printf("\"; d: \"");
    printMac(macsOfFrame.destination);
    printf("\"]");

    if (macLinkedList)
    {
        if (isBroadcast(macsOfFrame.destination))
        {
            int bcastCount = registerBroadcastFrameForSource(macLinkedList, macsOfFrame.origin);

            if (bcastCount > highestStrike)
                highestStrike = bcastCount;
            printf("**broadcast** (%d frames)", bcastCount);
        }
    }

    double probabilityOfStorm = (double)highestStrike/HEURISTIC_MAX_PACKETS_THRESHOLD * 100;
    printf("\n Probability of broadcast storm: %0.2f%%", probabilityOfStorm);

    if (probabilityOfStorm > 100)
    {
        printf("\n********BROADCAST STORM DETECTED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    }
    fflush(stdout);
    return (void*) 0;
}
