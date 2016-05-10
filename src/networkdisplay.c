#include "networkdisplay.h"

void printMac(u_char *macAddress)
{
    int i;

    for (i = 0; i < MAC_BYTES_SIZE; i++) {
        if (i)
            printf(":");

        printf("%02x", macAddress[i]);
    }
}

void printPayload(u_char *payload, size_t payloadSize)
{
    int i;
    int lineFeedNeeded;

    for (i=0; i<payloadSize; i++)
    {
        lineFeedNeeded = (i*2) % MAX_CHARACTERS_PER_LINE_PRESENTATION == 0;

        if (lineFeedNeeded)
            printf("\n\t");

        printf("%02x ", payload[i]);
    }

    printf("\n");
}

void printMacsFromFrame(u_char *frame) {

    /*
     * First six bytes of frame ( 0 - 5 )
     * DESTINATION MAC ADDRESS
     */
    printf("Destination MAC: ");
    printMac(&frame[0]);

    if (isBroadcast(&frame[0]))
        printf(" (** IS BROADCAST)");


    printf("\nSource MAC: ");

    /*
     * Ensuing six bytes of frame ( 6 - 11 )
     * SOURCE MAC ADDRESS
     */
    printMac(&frame[6]);

    if (isBroadcast(&frame[6]))
        printf(" (** IS BROADCAST)");
}

void printPayloadFromFrame(u_char *frame, size_t frameSize)
{
    // We know that the payload starts at position 14 of the frame and finishes
    // at the end of the frame (no CRC is present).
    printf("Payload: ");
    printPayload(&frame[14], frameSize-14);
}

void printIPv4Info(u_char *packet, size_t packetLength)
{
    // We know from the schema (https://en.wikipedia.org/wiki/IPv4#Header)
    // that the source IP address is at byte 12
    // and the dest IP address is at byte 16

    struct in_addr *ipSrcPointer;
    struct in_addr *ipDstPointer;
    const char *srcIP;
    const char *dstIP;

    printf("\nIt's an IPv4 packet.");

    ipSrcPointer = (struct in_addr*)&packet[12];
    srcIP = inet_ntoa(*ipSrcPointer);

    printf("\nSource IP Address: %s", srcIP);

    ipDstPointer = (struct in_addr*)&packet[16];
    dstIP = inet_ntoa(*ipDstPointer);
    printf("\nDestination IP Address: %s\n", dstIP);
}

void printFrame(const struct pcap_pkthdr *frameHeader, u_char* frame) {

    printf("Header length: %u\n", frameHeader->len);
    printMacsFromFrame(frame);
    printEthertype(frame);
    printCRC(frame);
    printPayloadFromFrame(frame, frameHeader->len);



    if (isIPv4(frame))
    {
        printIPv4Info(&frame[14], frameHeader->len-14);
    }
}

void printIPandMask(char *defaultDev) {
    bpf_u_int32 netAddress;
    bpf_u_int32 netMask;
    struct in_addr inAddress;
    char errbuf[PCAP_ERRBUF_SIZE];

    printf("Network device name = %s\n", defaultDev);

    /*
     * pcap_lookupnet() returns the IP and the netmask of the passed device
     * Actual parameters netAddress and netMask are passed by reference since
     * we want them to hold the IP and the netmask, they are therefore output
     * parameters
     */
    if (pcap_lookupnet(defaultDev, &netAddress, &netMask, errbuf) == -1) {
        printf("%s\n", errbuf);
        exit(3);
    }

    /*
     * inet_ntoa() turns a "binary network address into an ascii string"
     */
    inAddress.s_addr = netAddress;
    char *ip;

    if ((ip = inet_ntoa(inAddress)) == NULL) {
        perror("inet_ntoa");
        exit(4);
    }

    printf("IP address = %s\n", ip);

    inAddress.s_addr = netMask;
    char *mask = inet_ntoa(inAddress);

    if (mask == NULL) {
        perror("inet_ntoa");
        exit(5);
    }

    printf("Network mask = %s\n", mask);
    fflush(stdout);
}


void printCRC(u_char *frame) {

    printf("\nCRC: \n");
    fflush(stdout);

}

void printEthertype(u_char *frame) {
    uint16_t *originalEtherType = (uint16_t*)&frame[12];
    uint16_t etherType = ntohs(*originalEtherType);

    printf("\nEthertype: 0x%04x", etherType);
    fflush(stdout);

}

void printFilterHeuristic(char* heuristic)
{
    printf("\nChosen heuristic: %s", heuristic);

}
