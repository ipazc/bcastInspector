/*
 * Course on NGN @ University of León
 * Dept. IESA (Systems and Electrical Eng)
 * (C) 2015, José María Foces Morán
 *
 * LABS on the pcap capture library
 * ngn-libcap-test2.c
 * v 1.0 9/March/2015
 *
 * Captures n Ethernet frames (n is provided as first command-line argument) and
 * for each, it prints the header fields
 *
 *
 * Modified by Iván de Paz Centeno
 * @email ipazce00@estudiantes.unileon.es
 * date: 04/04/2016
 *
 * Extension to detect broadcast storms, by Iván de Paz Centeno
 * @email ipazc@unileon.es
 * date: 09/05/2016
 */

#include "networking.h"



unsigned int frameCount = 0;


int isIPv4(u_char *frame)
{
    uint16_t *originalEtherType = (uint16_t*)&frame[12];
    uint16_t etherType = ntohs(*originalEtherType);
    return etherType == IPv4;
}

int isBroadcast(u_char *macAddress)
{
    int i;
    int result = 1;

    for (i=0; i<MAC_BYTES_SIZE; i++)
        result = result && (macAddress[i] & BCAST_MASK == BCAST_MASK);

    return result;
}


void getNewFrame(u_char *dummy, const struct pcap_pkthdr *frameHeader, u_char *frame)
{
    printf("Packet captured no. %u  ", frameCount++);

    /*
     * Print the frame just captured
     */
    printFrame(frameHeader, frame);

    fflush(stdout);

}


MacsOfFrame getMacsOfFrame(u_char *frame)
{
    MacsOfFrame macsOfFrame;
    macsOfFrame.origin = &frame[6];
    macsOfFrame.destination = &frame[0];

    return macsOfFrame;
}

unsigned int performCapture(unsigned int nFramesToCapture, pcap_handler callback)
{

    char *defaultNetDevice;
    char errbuf[PCAP_ERRBUF_SIZE]; //The pcap error string buffer

    /*
     * Lookup the default network device on which to capture by invoking
     * pcap_lookupdev()
     */
    //defaultNetDevice = pcap_lookupdev(errbuf);
    defaultNetDevice = "wlan0";
    if (defaultNetDevice == (char *) NULL) {
        printf("%s\n", errbuf);
        exit(2);
    }

    /*
     * Printout of IP address + Net mask
     */
    printIPandMask(defaultNetDevice);

    /*
     * Open network device for capturing frames not-in-promiscuous mode:
     *
     * pcap_t *pcap_open_live(
     * const char *device,
     * int snaplen,
     * int promisc,
     * int timeout_ms,
     * char *errbuf);
     *
     */
    pcap_t* status;
    status = pcap_open_live(defaultNetDevice, BUFSIZ, 0, -1, errbuf);


    if (status == (pcap_t *) NULL) {
        printf("Call to pcap_open_live() returned error: %s\n", errbuf);
        exit(4);
    }

    if (nFramesToCapture <= 0)
        printf("\n\nCapturing frames...\n");
    else
        printf("\n\nCapturing %u frames:\n", nFramesToCapture);
    fflush(stdout);

    /*
     * int pcap_loop(
     * pcap_t *status,
     * int number_of_frames_to_capture,
     * pcap_handler callback_function,
     * u_char *user
     * )
     *
     */
    pcap_loop(status, nFramesToCapture, callback, (char *) NULL);

    return nFramesToCapture;
}