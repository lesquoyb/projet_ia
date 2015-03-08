#include "Connection.h"
bool Connection::is_connected = false;
SOCKET Connection::sock;
vector<string> Connection::query;
string Connection::transmission_end = "_#_";

Connection::Connection() {}
Connection::~Connection() {}

/**Connexion au serveur*/
void Connection::linkServer(char adresseServeur[200]) {
    if (!Connection::is_connected) {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 0), &wsaData)) throw Erreur("L'initialisation a échoué");
        Connection::sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (Connection::sock == INVALID_SOCKET) {
            ostringstream oss;
            oss << "la création du socket a échoué : code d'erreur = " << WSAGetLastError() << endl;	// pour les valeurs renvoyées par WSAGetLastError() : cf. doc réf winsock
            throw Erreur(oss.str().c_str());
        }

        SOCKADDR_IN sockaddr;
        short portServeur = 4567;
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_addr.s_addr = inet_addr(adresseServeur);
        sockaddr.sin_port = htons(portServeur);

        if (connect(Connection::sock, (SOCKADDR *)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR) { throw Erreur("La connexion a échoué"); }
        Connection::is_connected = true;

        cout << "connexion réussie "<< endl;
        Connection::get();
    }
    else { cout << "Une connexion est déjà en cours" << endl; }
}

/**Deconnexion du serveur*/
void Connection::unlinkServer() {
    if (Connection::is_connected) {
        if (shutdown(Connection::sock, SD_BOTH) == SOCKET_ERROR) throw Erreur("la coupure de connexion a échoué");
        if (closesocket(Connection::sock)) throw Erreur("La fermeture du socket a échoué");
        WSACleanup();
        Connection::is_connected = false;

        cout << "arrêt normal du client" << endl;
    } else {
        cout << "La  connexion n'est pas établie." << endl;
    }
}

/**Reception d'un message*/
string Connection::get() {
    if (Connection::is_connected) {
        char reponse[200];
        if (recv(Connection::sock, reponse, 200, 0) == SOCKET_ERROR) { throw Erreur("La réception de la réponse a échoué"); }
        else {
            char* p = strstr(reponse, "\\END\\");
            *p = '\0';
            string rep(reponse);
            return rep;
        }
    } else {
        cout << "La connexion n'est pas établie." << endl;
        return "error";
    }
}

/**Envoi de toutes les requetes*/
void Connection::push() {
    if (Connection::is_connected) {
        string temp;
        for (string a_query : query) { temp += a_query + Connection::separator; }
        temp += Connection::transmission_end + Connection::separator + "\r\n";
        query.clear();
        cout << temp;
        char* queries = _strdup(temp.c_str());
        if (send(Connection::sock, queries, strlen(queries), 0) == SOCKET_ERROR) { throw Erreur("échec de l'envoi de la requête"); }
    } else {
        cout << "La connexion n'est pas établie" << endl;
    }
}

/**Enregistrement d'une requete*/
void Connection::commit(string message, bool push) {
    query.push_back(message);
    if (push) Connection::push();
}

void Connection::clear() {
    query.clear();
}

bool Connection::isConnected() { return is_connected; }
