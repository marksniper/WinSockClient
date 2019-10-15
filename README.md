# Server WINSOCK Example of server in C. 
The client open socket, using _WINSOCK_, in order to communicate with
server. 
*ATTENTION* before launch _client_, it is *MANDATORY* that 
*SERVER* application, see last part of documentations, has runned. The
server receive a _GREETING_ by client. The client sends a _GREETING_ to
server. The client creates new file, called _random.txt_, and writes 10
randoms number. After, client open the file, in _read mode_ and prints
on standard output the file content. If file doesn't exists, server
creates its.
## LINKShttps://sourceforge.net/projects/mingw-w64/
[Common error in WINSOCK](https://www.binarytides.com/code-tcp-socket-server-winsock/)

[Download MinGW-w64](https://sourceforge.net/projects/mingw-w64/)
## TEST
1. USE SERVER PROGRAM Download, compile, build and run the
_WINSOCK SERVER_ program, written in C, which is available in
*WINCLIENTSOCKET* repository, [link]()
## Authors
* **Benedetto Marco Serinelli** - *Initial work* 
## Acknowledgments
The code was developed with _CLion_ and another test was done with _Code
Blocks_.
