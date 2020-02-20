#include "clientTCP_service.h"
#include "controler.h"

int main()
{
    printf("Try connection...\n");
    int descr = launch_TCP_connection();
    pthread_t th1, th2;
    if (descr!=-1)
    {   
        pthread_create(&th1,NULL, launch_UDP_reception, NULL);
        if (init_controler()!=-1) {
            pthread_create(&th2,NULL, launch_game , NULL);
        }
    }
    pthread_join(th2,NULL);
    pthread_cancel(th1);
    end_vue();
    free_game();
    close(descr);
}