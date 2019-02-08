# biscuit-wifi

## biscuit-euler-wifi:

An Arduino project with the libraries needed to configure the Wifi of the Biscuit. Retrieves sets of data from the orientation sensor and sends them through UDP packets to a user-specified port (4210 by default) of a user-specified IP address every 100ms (or faster / slower if desired).

Enables the Biscuit to send orientation values via WiFi, specifically:
- Euler angles (degrees)
- Magnetometer xyz values (micro Teslas)
- Gyroscope xyz values (radians per second)
- Accelerometer xyz values (m/s^2)
- Linear Acceleration xyz values (m/s^2)
- Gravity xyz values (m/s^2)
- Quaternion wxyz values (qW,qX,qY,qZ)

If a set of values are unecessary, simply comment out their respective sprintf statement.

## udp-recv.c:

A C program that sniffs a user-specified port (4210 by default) for UDP packets, parses and displays them as a string. Enables the user to access and observe the orientation data sets provided by the Biscuit in real time - over a Wifi connection.

Command Line Instructions:    
```
make
./udp-recv
```

To change the port the udp socket is bound to, edit port.h.


(A modified version of Paul Krzyzanowski's [demo-udp-03](https://www.cs.rutgers.edu/~pxk/417/notes/sockets/demo-udp-03.html))
