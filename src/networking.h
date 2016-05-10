#ifndef _networking_h_
#define _networking_h_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pcap.h>
#include "networkdisplay.h"

#define MAC_BYTES_SIZE 6
#define BCAST_MASK 0xFF
#define MAX_CHARACTERS_PER_LINE_PRESENTATION 70
#define ALL_PACKETS 0

enum ETHERTYPES
{
    IPv4 = 0x800,
};

typedef struct MacsOfPacket
{
    char* origin;
    char* destination;
} MacsOfFrame;

extern unsigned int frameCount;


MacsOfFrame getMacsOfFrame(u_char *frame);

/**
 * Returns whether a received frame is an IPv4 packet or not.
 */
int isIPv4(u_char *frame);

/**
 * Determines if a given mac address is a broadcast one or not.
 *
 * @param macAddress pointer to a mac address 48 bit integer.
 *
 * @returns logical true if is a broadcast address. Logical false otherwise.
 */
int isBroadcast(u_char *macAddress);

unsigned int performCapture(unsigned int nFramesToCapture, pcap_handler callback);


#endif /* _networking_h_ */