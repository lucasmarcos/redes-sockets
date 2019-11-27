#include <stdio.h>
#include <winsock2.h>

#define LEN (1024*4)

int main(int argc, char *argv[])
{
    char buffer[LEN];

    WSADATA wsaData;

    SOCKET s;
    struct sockaddr_in endereco;
    int res;

    // inicializa a biblioteca de sockets do windows
    res = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(res) {
        printf("erro inicializando winsock2 %d\n", res);
        return 1;
    }

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(!s) {
        printf("erro criando o socket\n");
        return 2;
    }

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = inet_addr("127.0.0.1");
    endereco.sin_port = htons(3000);

    res = connect(s, (struct sockaddr *) &endereco, sizeof(struct sockaddr_in));
    if(res) {
        printf("erro ao conectar ao servidor: %d\n", WSAGetLastError());
        return 3;
    }
    printf("conectado!\n");

    while(1) {
        printf("digite sua mensagem: ");
        scanf("%s", buffer);

        res = send(s, buffer, LEN, 0);
        if(res) {
            res = recv(s, buffer, LEN, 0);
            if(res) {
                printf("recebido: %s\n", buffer);
            } else {
                printf("erro recebendo\n");
            }
        } else {
            printf("erro enviando\n");
        }
    }

    closesocket(s);
    WSACleanup();
    return 0;
}