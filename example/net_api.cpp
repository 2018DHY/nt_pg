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

 
 /**
  * socket 创建套接字 
  * 头文件 #include <sys/socket.h>
  * 
  * int socket(int domain, int type, int protocol);
  * domain: AF_UNIX      Local communication
  *         AF_LOCAL     Synonym for AF_UNIX
  *         AF_INET      IPv4 Internet protocols
  * 
  * type:
  * SOCK_STREAM    Provides   sequenced,   reliable,   two-way,  connection-based  byte
  *                streams.  An out-of-band data transmission  mechanism  may  be  sup‐
  *                ported.                                                             
  *                                                                                         
  * SOCK_DGRAM      Supports  datagrams  (connectionless, unreliable messages of a fixed
  *                 maximum length).
  * 
  * protocol:default = 0
  */
 
  /**
   * 认识一些常见的结构体
   * 参考https://beej-zhcn.netdpi.net/ipaddress_struct/zi_liao_jie_gou
   * 
   * struct addrinfo {
   * int ai_flags; // AI_PASSIVE, AI_CANONNAME 等。
   * int ai_family; // AF_INET, AF_INET6, AF_UNSPEC
   * int ai_socktype; // SOCK_STREAM, SOCK_DGRAM
   * int ai_protocol; // 用 0 當作 "any"
   * size_t ai_addrlen; // ai_addr 的大小，單位是 byte
   * struct sockaddr *ai_addr; // struct sockaddr_in 或 _in6
   * char *ai_canonname; // 典型的 hostname
   * struct addrinfo *ai_next; // 鏈結串列、下個節點
   * };
   * 
   * 通用地址(兼容ipv4/6)
   * struct sockaddr {
   * unsigned short sa_family; // address family, AF_xxx
   * char sa_data[14]; // 14 bytes of protocol address
   * };
   * 
   * // （IPv4 专用）
   * struct sockaddr_in {
   * short int sin_family; // Address family, AF_INET
   * unsigned short int sin_port; // Port number 端口号
   * struct in_addr sin_addr; // Internet address 地址
   * unsigned char sin_zero[8]; //填充为了与struct sockaddr 相同的大小
   * };
   * 
   * // (仅限 IPv4)
   * // Internet address (a structure for historical reasons)
   *    struct in_addr {
   *        uint32_t s_addr; // 4字节地址 整数存储非字符串需大端,用htol()
   *    };
   * 
   * 
   * 
   * // (IPv6 專用-- IPv4 請見 struct sockaddr_in 與 struct in_addr)
   * struct sockaddr_in6 {
   *     u_int16_t sin6_family; // address family, AF_INET6
   *     u_int16_t sin6_port; // port number, Network Byte Order
   *     u_int32_t sin6_flowinfo; // IPv6 flow 資訊
   *     struct in6_addr sin6_addr; // IPv6 address
   *     u_int32_t sin6_scope_id; // Scope ID
   * };
   * 
   * struct in6_addr {
   *     unsigned char s6_addr[16]; // IPv6 address
   * };
   * 
   * struct sockaddr_storage {  //编程时可以通过ss_family判断后将该结构体转化为ipv4/6结构体struct sockaddr_in/6
   * sa_family_t ss_family; // address family AF_INET, AF_INET6
   * // 這裡都是填充物（padding），依實作而定，請忽略它：
   * char __ss_pad1[_SS_PAD1SIZE];
   * int64_t __ss_align;
   * char __ss_pad2[_SS_PAD2SIZE];
   * };
   */

int main(int argc, char *argv[])
{
    byt_seq_test();
    str_to_int_test();

    return 0;
}