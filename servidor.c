#include <stdio.h>
#include <winsock2.h>

#define LEN (1024*4)

int main(int argc, char *argv[])
{
    char buffer[LEN];;

    WSADATA wsaData;

    SOCKET s, c;
    struct sockaddr_in endereco, endereco_cliente;
    int res, tam_endereco_cliente;
    unsigned long long x = 0;

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
    endereco.sin_addr.s_addr = 0;
    endereco.sin_port = htons(3000);

    res = bind(s, (struct sockaddr *) &endereco, sizeof(endereco));
    if(res) {
        printf("erro bind %d\n", res);
        return 3;
    }

    res = listen(s, 1);
    if(res) {
        printf("erro listen %d\n", res);
        return 4;
    }
    printf("ouvindo em 0.0.0.0:3000\n");

    while(1) {
        tam_endereco_cliente = sizeof(struct sockaddr_in);
        c = accept(s, (struct sockaddr *) &endereco_cliente, &tam_endereco_cliente);
        if(c == INVALID_SOCKET) {
            printf("erro aceitando conexao %d\n", WSAGetLastError());
            break;
        }

        while(1) {
            res = recv(c, buffer, LEN, 0);
            if(res) {
                printf("recebendo ");

                x = ntohl(endereco_cliente.sin_addr.s_addr);
                printf("%ld.%ld.%ld.%ld", x >> 24,
                                        (x >> 16) & 0xf,
                                        (x >> 8)  & 0xf,
                                        x        & 0xf);
                printf(":%d\n", ntohs(endereco_cliente.sin_port));
                printf("recebido: %s\n", buffer);

                printf("digtite sua mensagem: ");
                scanf("%s", &buffer);
                res = send(c, buffer, LEN, 0);
                if(res) {
                } else {
                    printf("erro enviando\n");
                }
            } else {
                printf("conexao encerrada\n");
                break;
            }
        }
    }

    closesocket(s);
    WSACleanup();
    return 0;
}