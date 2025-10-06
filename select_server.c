#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT "9034"

const char* inet_ntop2(void *addr,char *buf,size_t size)
{
    struct sockaddr_storage *sas=addr;
    struct sockaddr_in *sa4;
    struct sockaddr_in6 *sa6;
    void *src;

    switch (sas->ss_family){
        case AF_INET:
        sa4=addr;
        src=&(sa4->sin_addr);
        break;
        case AF_INET6:
        sa6 =addr;
        src=&(sa6->sin6_addr);
        break;
        default:
        return NULL;
    }
    return inet_ntop(sas->ss_family,src,buf,size);
}

int get_listener_socket(void){
    struct addrinfo hints,*ai,*p;
    int yes=1;
    int rv;
    int listener;

    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;
    if((rv=getaddrinfo(NULL,PORT,&hints,&ai))!=0){
        fprintf(stderr,"selectserver:%s\n",gai_strerror(rv));
        exit(1);
    }

    for(p=ai;p!=NULL;p=p->ai_next){
        listener = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
        if(listener<0){
            continue;
        }

        setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));

        if(bind(listener,p->ai_addr,p->ai_addrlen)<0){
            close(listener);
            continue;
        }

        break;
    }

    if(p==NULL){
        fprintf(stderr,"selectserver:failed to bind\n");
        exit(2);
    }

    freeaddrinfo(ai);
    if(listen(listener,10)== -1){
        perror("listen");
        exit(3);
    }

    return listener;

}

void handle_new_connection(int listener,fd_set *master,int *fdmax){
    socklen_t addrlen;
    int newfd;
    struct sockaddr_storage remoteaddr;
    char remoteIP[INET6_ADDRSTRLEN];

    addrlen=sizeof remoteaddr;
    newfd=accept(listener,(struct sockaddr*)&remoteaddr,&addrlen);

    if(newfd== -1){
        perror("accept");
    }else{
        FD_SET(newfd,master);
        if(newfd>*fdmax){
            *fdmax=newfd;
        }
        printf("selectserver:new connection from %s on socket %d\n",inet_ntop2(&remoteaddr,remoteIP,sizeof(remoteIP)),newfd);
    }
}

void broadcast(char *buf,int nbytes,int listener,int s, fd_set* master,int fdmax){
    for(int j=0;j<=fdmax;j++){
        if(FD_ISSET(j,master)){
            if(j!=listener && j!=s){
                if(send(j,buf,nbytes,0)== -1){
                    perror("send");
                }
            }
        }
    }
}

void handle_clinet_data(int s,int listener,fd_set *master,int fdmax){
    char buf[256];
    int nbytes;

    if((nbytes = recv(s,buf,sizeof(buf),0))<=0){
        if(nbytes== 0){
            printf("selectserver:socket %d hung up\n",s);
        }else{
            perror("recv");
        }
        close(s);
        FD_CLR(s,master);
    }else{
        broadcast(buf,nbytes,listener,s,master,fdmax);
    }
}


int main(void ){

    fd_set master;
    fd_set read_fds;

    int fdmax;

    int listener;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    listener=get_listener_socket();

    FD_SET(listener,&master);

    // tv
}