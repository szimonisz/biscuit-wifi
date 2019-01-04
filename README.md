# biscuit-wifi

## biscuit-euler-wifi:

An Arduino project with the libraries needed to configure the Wifi of the Biscuit. Retrieves Euler angles from the orientation sensor and sends them through UDP packets to port 4210 of the local network every 100ms.

## udp-recv.c:

A C program that sniffs a designated port (4210) for UDP packets, parses and displays them as a string. Enables the user to access and observe the Euler angles provided by the Biscuit in real time - over a Wifi connection.

Command Line Instructions:    make
                              ./udp-recv


(A modified version of Paul Krzyzanowski's [demo-udp-03](https://www.cs.rutgers.edu/~pxk/417/notes/sockets/demo-udp-03.html))
