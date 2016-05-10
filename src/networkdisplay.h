
#ifndef _networkdisplay_h_
#define _networkdisplay_h_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pcap.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "networking.h"

/**
 * Prints the current selected heuristic for the broadcast storm capture.
 */
void printFilterHeuristic(char* heuristic);

/*
 * CRC: Last 4 bytes of frame
 */
void printCRC(u_char *frame);

/*
 * frame bytes ( 12 and 13 )
 * DESTINATION MAC ADDRESS
 */
void printEthertype(u_char *frame);

/**
 * Prints the especified mac address as a string.
 *
 * @param macAddress pointer to a mac address 48 bit integer.
 */
void printMac(u_char *macAddress);

/**
 * Prints the payload of the given packet in hexadecimal format.
 *
 * @param payload   pointer to the payload.
 * @param payloadSize   size in bytes of the payload.
 *
 */
void printPayload(u_char *payload, size_t payloadSize);

/*
 * Print the MAC addresses
 */
void printMacsFromFrame(u_char *frame);

/**
 * Prints the payload from the specified frame
 */
void printPayloadFromFrame(u_char *frame, size_t frameSize);

/**
 * Prints the packet IPv4 information (ip addresses)
 *
 * @param packet     IPv4 packet (payload of the frame).
 * @param packetLength size in bytes of the packet.
 */
void printIPv4Info(u_char *packet, size_t packetLength);

/*
 * pcap_pkthdr Generic per-packet information, as supplied by libpcap:
 *      packet lengths and the packet timestamp
 *
 * u_char* frame: Bytes of data from the frame itself with all
 *                the wire bits stripped
 */
void printFrame(const struct pcap_pkthdr *frameHeader, u_char* frame);

/*
 * printIPandMask(char *defaultDev)
 *
 * Prints the IP address and the Network mask configured into the network
 * device whose p_cap name is into defatultDevice
 *
 */
void printIPandMask(char *defaultDev);

#endif /* _networkdisplay_h_ */