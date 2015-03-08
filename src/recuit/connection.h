#ifndef CONNECTION
#define CONNECTION
#include <winsock2.h>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include "Erreur.h"

#pragma comment(lib, "ws2_32.lib") // spécifique à VISUAL C++
using namespace std;

class Connection {
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
    Connection();
    ~Connection();

    static SOCKET sock;
    static bool is_connected;
    static vector<string> query;
    static string transmission_end;
};

#endif
