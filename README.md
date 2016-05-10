# bcastInspector
This broadcast messages inspector is intended to be a network watchdog and to make alarms when broadcast storms are alive.

# Compilation

Follow the following steps in order to compile:
```bash
$ mkdir build && cd build
$ cmake ..
$ make
$ sudo ./bcastInspector
```

# How it works

Measures the amount of broadcast packets for each MAC address each second. If a default threshold of 130 packets is reached by any MAC for a given second, it is considered a broadcast storm.

If there is any kind of problem regarding the interface selected for the detection, you can modify the default interface by editing the `src/networking.c` file:

```c
...
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
    ...
```

Set the defaultNetDevice to the correct interface (for example 'eth0' or 'tun0').
