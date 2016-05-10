# bcastInspector
This broadcast messages inspector is intended to be a network watchdog and to make alarms when broadcast storms are alive.

# Compilation

Follow the following steps in order to compile:
```bash
$ mkdir build && cd build
$ cmake ..
$ make
$./bcastInspector
```

# How it works

Measures the amount of broadcast packets for each MAC address each second. If a default threshold of 130 packets is reached by any MAC for a given second, it is considered a broadcast storm.
