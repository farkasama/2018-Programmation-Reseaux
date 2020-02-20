#include "clientTCP_service.h"


#define SDELAY 0
#define UDELAY 50000
#define SIZE_MESS 100
int sock_descr;

int launch_TCP_connection()
{
    struct sockaddr_in adress_sock;
    adress_sock.sin_family = AF_INET;
    adress_sock.sin_port = htons(SERV_TCP_PORT);
    inet_aton("127.0.0.1",&adress_sock.sin_addr);
    int descr=socket(PF_INET,SOCK_STREAM,0);
    int r=connect(descr,(struct sockaddr *)&adress_sock,sizeof(struct sockaddr_in));
    if(r!=-1){
        printf("You are connected!\n");
    } else{
        printf("Probleme de connexion!\n");
        return -1;
    }
    sock_descr = descr;
    return descr;
}

void* TCP_receptor(void * ptr)
{
    printf("RECEPTION BEGIN\n");
    //int descr = *(int *) ptr;
    char* buff = malloc(sizeof(char)*SIZE_MESS);
    while (1)
    {
        int r = get_message(buff, SIZE_MESS*sizeof(char));
        if (r > 0)
        {
            printf("Caracteres recus : %d\n",r);
            printf("Message : %s\n",buff);
        } else if (r < 0)
        {
            free(buff);
            printf("end reception\n");
            return NULL;
        } else {
            printf("Message lenght <6, ignored\n");
        }
    }
}

int get_message(char* buff, int buff_size)
{
    struct timeval tv;
	fd_set initial;
    tv.tv_sec = SDELAY;
	tv.tv_usec = UDELAY;
    FD_ZERO(&initial);
    FD_SET(sock_descr, &initial);
    select(sock_descr+1, &initial, NULL, NULL, &tv);
    if (FD_ISSET(sock_descr, &initial)){
        int size_rec = read(sock_descr,buff, buff_size-1);
        if (size_rec>5) {
            size_rec -= 3;
            buff[size_rec]='\0';
            vue_recv(buff);
            send_message(buff);
            return size_rec;
        } else if ( size_rec <= 0) return -1;
        else return 1;
    } else {
        return 0;
    }
}

void * TCP_sender(void* ptr)
{
    //int descr = *(int*)ptr;
    char buff[SIZE_MESS];

    while (1)
    {
        fgets(buff, sizeof(buff), stdin);
        int r = send_message(buff);
        printf("sended r:%d\n", r);
        if (r <= 0) {
            printf("FAIL TO SEND\n");
            break;
        }
    }
    return 0;
}

int send_message(char* buff)
{
    int r = send(sock_descr,buff,strlen(buff)*sizeof(char), 0);
    return r;
}

