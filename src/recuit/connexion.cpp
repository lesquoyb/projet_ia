#include "connexion.h"
bool Connexion::is_connected = false;
SOCKET Connexion::sock;
vector<string> Connexion::query;
string Connexion::transmission_end = "_#_";

Connexion::Connexion() {}
Connexion::~Connexion() {}

/**Connexion au serveur*/
void Connexion::linkServer(char adresseServeur[200]) {
    if (!Connexion::is_connected) {
        #ifdef WIN32
                WSADATA wsaData;
                if (WSAStartup(MAKEWORD(2, 0), &wsaData)) throw Exception("L'initialisation a échoué");
        #endif
        Connexion::sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (Connexion::sock == INVALID_SOCKET) {
            ostringstream oss;
            oss << "la création du socket a échoué : code d'erreur = " << WSAGetLastError() << endl;	// pour les valeurs renvoyées par WSAGetLastError() : cf. doc réf winsock
            throw Exception(oss.str().c_str());
        }

        SOCKADDR_IN sockaddr;
        short portServeur = 4567;
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_addr.s_addr = inet_addr(adresseServeur);
        sockaddr.sin_port = htons(portServeur);

        if (connect(Connexion::sock, (SOCKADDR *)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR) { throw Exception("La connexion a échoué"); }
        Connexion::is_connected = true;

        cout << "connexion réussie "<< endl;
        Connexion::get();
    }
    else { cout << "Une connexion est déjà en cours" << endl; }
}

/**Deconnexion du serveur*/
void Connexion::unlinkServer() {
    if (Connexion::is_connected) {
        if (shutdown(Connexion::sock, SD_BOTH) == SOCKET_ERROR) throw Exception("la coupure de connexion a échoué");
        if (closesocket(Connexion::sock)) throw Exception("La fermeture du socket a échoué");
        #ifdef WIN32
            WSACleanup();
        #endif
        Connexion::is_connected = false;

        cout << "arrêt normal du client" << endl;
    } else {
        cout << "La  connexion n'est pas établie." << endl;
    }
}

/**Reception d'un message*/
string Connexion::get() {
    if (Connexion::is_connected) {
        char reponse[200];
        if (recv(Connexion::sock, reponse, 200, 0) == SOCKET_ERROR) { throw Exception("La réception de la réponse a échoué"); }
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
void Connexion::push() {
    if (Connexion::is_connected) {
        string temp;
        for (string a_query : query) { temp += a_query + Connexion::separator; }
        temp += Connexion::transmission_end + Connexion::separator + "\r\n";
        query.clear();
        cout << temp;
        char* queries = _strdup(temp.c_str());
        if (send(Connexion::sock, queries, strlen(queries), 0) == SOCKET_ERROR) { throw Exception("échec de l'envoi de la requête"); }
    } else {
        cout << "La connexion n'est pas établie" << endl;
    }
}

/**Enregistrement d'une requete*/
void Connexion::commit(string message, bool push) {
    query.push_back(message);
    if (push) Connexion::push();
}

void Connexion::clear() {
    query.clear();
}

bool Connexion::isConnected() { return is_connected; }
