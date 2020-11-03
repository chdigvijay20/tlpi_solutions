**Suppose that we create two UNIX domain datagram sockets bound to the paths /somepath/a and /somepath/b, and that we connect the socket /somepath/a to /somepath/b. What happens if we create a third datagram socket and try to send (sendto()) a datagram via that socket to /somepath/a? Write a program to determine the answer. If you have access to other UNIX systems, test the program on those systems to see if the answer differs.**

`sendto()` call to a `/somepath/a` fails with `[EPERM Operation not permitted]`
~~~
$ ./build/57/socket_b_57_4 &
[1] 122138
$ ./build/57/socket_a_57_4 &
[2] 122142
$ ./build/57/socket_c_57_4
ERROR [EPERM Operation not permitted] sendto
~~~
