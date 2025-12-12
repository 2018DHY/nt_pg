// std lib
#include <stdio.h>
#include <string.h>
// std lib

// POSIX
#include <sys/socket.h> //socket函数
#include <netinet/in.h> //ipv4/6结构体
#include <netdb.h>      //getaddrinfo
#include <arpa/inet.h>  //inet_ntop
#include <unistd.h>     //用于gethostname

#include <ifaddrs.h> //用于获取网口interface

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
    struct addrinfo hints, *res = NULL, *p = NULL;
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
        struct ifaddrs *ifaddr, *ifa;
        int family, s;
        char host[NI_MAXHOST];

        // 获取网络接口列表
        if (getifaddrs(&ifaddr) == -1)
        {
            perror("getifaddrs");
            return -1;
        }

        // 遍历所有网络接口
        printf("local interface IP addr list:\n");
        printf("================\n");

        for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
        {
            if (ifa->ifa_addr == NULL)
                continue;

            family = ifa->ifa_addr->sa_family;

            // 只处理IPv4和IPv6地址
            if (family == AF_INET || family == AF_INET6)
            {
                s = getnameinfo(ifa->ifa_addr,
                                (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
                                host, NI_MAXHOST,
                                NULL, 0, NI_NUMERICHOST);

                if (s != 0)
                {
                    printf("getnameinfo() failed: %s\n", gai_strerror(s));
                    continue;
                }

                printf("interface: %-10s type: %-6s address: %s\n",
                       ifa->ifa_name,
                       (family == AF_INET) ? "IPv4" : "IPv6",
                       host);
            }
        }

        // 释放ifaddrs结构
        freeifaddrs(ifaddr);
    }
    else
    {
        if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0)
        {
            fprintf(stderr, "getaddrinfo:%s \n", gai_strerror(status));
            return 2;
        }
        printf("IP addresses for %s:\n\n", argv[1]);
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
    }

    return 0;
}