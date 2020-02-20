#ifndef __CLIENTTCP_SERVICE_H__
#define __CLIENTTCP_SERVICE_H__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "vue.h"

#define SERV_TCP_PORT 8000


// struct TCP_service;

int launch_TCP_connection();

void * TCP_receptor(void * ptr);

int get_message(char* buff, int buff_size);

int send_message(char* buff);

void * TCP_sender(void* ptr);



#endif