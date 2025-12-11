#include <stdio.h>

#include <arpa/inet.h>

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
 * int inet_pton(int af, const char *restrict src, void *restrict dst); 点分十进制字符串转网络字节序列
 * af 表示地址族类型AF_INET:IPV4 AF_INET6:IPV6
 * src 字符串地址
 * dst 存到目的地地址
 * 返回值 1为成功
 * 
 * const char *inet_ntop(int af, const void *restrict src, char dst[restrict .size], socklen_t size);
 * 
 */

int main(int argc, char *argv[])
{
    byt_seq_test();
    return 0;
}