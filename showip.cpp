#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <unistd.h> //用于gethostname

/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(const char *node, // 例如： "www.example.com" 或 IP
                const char *service, // 例如： "http" 或 port number
                const struct addrinfo *hints,
                struct addrinfo **res);
*/

// update

static char ip4_str[] = "IPv4";
static char ip6_str[] = "IPv6";

int main(int argc, char *argv[])
{
    bool self = false;
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if (argc != 2)
    {
        fprintf(stderr, "usage: showip hostname\n");
        self = true;
    }
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (self)
    {
        hints.ai_flags = AI_CANONNAME;
        char hostname[256];
        gethostname(hostname, sizeof(hostname)); // 先获取主机名
        printf("host name is %s\n", hostname);
        if ((status = getaddrinfo(hostname, "4399", &hints, &res)) != 0)
        {
            fprintf(stderr, "getaddrinfo:%s \n", gai_strerror(status));
            return 2;
        }
        printf("local IP addresses:\n\n");
    }
    else
    {
        if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0)
        {
            fprintf(stderr, "getaddrinfo:%s \n", gai_strerror(status));
            return 2;
        }
        printf("IP addresses for %s:\n\n", argv[1]);
    }

    for (p = res; p != NULL; p = p->ai_next)
    {
        void *addr;
        char *ipver;

        if (p->ai_family == AF_INET)
        {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = ip4_str;
        }
        else
        {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = ip6_str;
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf(" %s:%s\n", ipver, ipstr);
    }

    freeaddrinfo(res);

    return 0;
}