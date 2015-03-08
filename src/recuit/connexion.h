#ifndef CONNECTION
#define CONNECTION
#ifdef __unix__
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <errno.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define WSAGetLastError() errno
    #define SD_BOTH 2
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
    #define _strdup strdup
#else
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib") // sp�cifique � VISUAL C++
    #if (_MSC_VER == 1800)
        #define strdup _strdup
    #endif
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include "exception.h"


using namespace std;

class Connexion {
public:
    static void linkServer(char[200]);
    static void unlinkServer();
    static string get();
    static void commit(string, bool = false);
    static void push();
    static void clear();
    static bool isConnected();

    static const char separator = ';';

private:
    Connexion();
    ~Connexion();

    static SOCKET sock;
    static bool is_connected;
    static vector<string> query;
    static string transmission_end;
};

#endif
