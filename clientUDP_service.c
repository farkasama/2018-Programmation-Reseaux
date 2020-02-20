#include "clientUDP_service.h"


int sock_muticast;

void * launch_UDP_reception(void *descr)
{
    int sock=socket(PF_INET,SOCK_DGRAM,0);
    sock=socket(PF_INET,SOCK_DGRAM,0);
    struct sockaddr_in address_sock;
    address_sock.sin_family=AF_INET;
    address_sock.sin_port=htons(MYUDP_PORT);
    address_sock.sin_addr.s_addr=htonl(INADDR_ANY);
    int r=bind(sock,(struct sockaddr *)&address_sock,sizeof(struct sockaddr_in));
    if(r!=0){
        return 0;
    }
    struct sockaddr_in emet;
    socklen_t a=sizeof(emet);
    char buff[230];
    while(1){
        int rec = recvfrom(sock,buff,230-1,0,(struct sockaddr *)&emet,&a);
        if (rec == -1) return descr;
        buff[rec]='\0';
        vue_recv(buff);
        // ntohs(emet.sin_port); //Port de l'emetteur
        // inet_ntoa(emet.sin_addr) //Adresse de l'emetteur
    }
}

int init_multicast_reception(int port, char *ip)
{
    int sock=socket(PF_INET,SOCK_DGRAM,0);
    int ok=1;
    int r=setsockopt(sock,SOL_SOCKET,SO_REUSEPORT,&ok,sizeof(ok));
    if (r != 0) return -1;    
    struct sockaddr_in address_sock;
    address_sock.sin_family=AF_INET;
    address_sock.sin_port=htons(port);
    address_sock.sin_addr.s_addr=htonl(INADDR_ANY);
    r=bind(sock,(struct sockaddr *)&address_sock,sizeof(struct sockaddr_in));
    if (r != 0) return -1;
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr=inet_addr(ip);
    mreq.imr_interface.s_addr=htonl(INADDR_ANY);
    r=setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
    if (r != 0) return -1;
    sock_muticast = sock;
    return sock;
}

int getMultSock()
{
    return sock_muticast;
}