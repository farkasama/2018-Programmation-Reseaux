#ifndef __CLIENTUDP_SERVICE_H__
#define __CLIENTUDP_SERVICE_H__

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

#define MYUDP_PORTSTR "8001"
#define MYUDP_PORT 8001
#define MYMULT_PORT 8002

void * launch_UDP_reception(void *descr);

int init_multicast_reception();

int getMultSock();

#endif