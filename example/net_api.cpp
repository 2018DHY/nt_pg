#include <stdio.h>

#include <arpa/inet.h>

#define pft   printf("==========%s==========\n",__func__)

/**
 * 字节序转换函数
 * 头文件 #include <arpa/inet.h>
 * 主机转网络
 * htonl int   用于转IP地址
 * htons short 用于转端口号
 *
 * 网络转主机
 * ntohl int
 * ntohs short
 *
 */

void byt_seq_test()
{
    pft;
    int hostl = 0x01020304;
    int netl = 0;
    short hosts = 0x0506;
    short nets = 0;
    netl = htonl(hostl);
    printf("%x\n", netl);

    nets = htons(hosts);
    printf("%x\n", nets);
}

/**
 *点分十进制转化函数(用于将IP字符串转化为字节序列)
 * 头文件 #include <arpa/inet.h>
 * int inet_pton(int af, const char *restrict src, void *restrict dst); 点分十进制字符串转网络字节序列
 * af 表示地址族类型AF_INET:IPV4 AF_INET6:IPV6
 * src 字符串地址
 * dst 存到目的地地址
 * 返回值 1为成功
 * 
 * const char *inet_ntop(int af, const void *restrict src, char dst[restrict .size], socklen_t size);
 * af 表示地址族类型AF_INET:IPV4 AF_INET6:IPV6
 * src 源
 * dst 字符串指针
 * size 字符串缓冲区大小
 * 
 */

 /**
  * socket 获得一个套接字 
  * 头文件 #include <sys/socket.h>
  * 
  * int socket(int domain, int type, int protocol);
  * 
  */

 void str_to_int_test(){
    pft;
    uint32_t ip_int=0;
    inet_pton(AF_INET,"192.168.1.1",&ip_int);
    u_int8_t* ptr=(u_int8_t*)&ip_int;
    printf("str to int is %d %d %d %d\n",ptr[0],ptr[1],ptr[2],ptr[3]);

    uint32_t ip_int_r=0x01020304;
    char buf[INET_ADDRSTRLEN]="";
    inet_ntop(AF_INET,&ip_int_r,buf,sizeof(buf));
    printf("int to str is %s\n",buf);
 }

int main(int argc, char *argv[])
{
    byt_seq_test();
    str_to_int_test();

    return 0;
}