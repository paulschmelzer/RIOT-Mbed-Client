#include "net/ipv6/addr.h"
#include "net/ipv4/addr.h"



#define PAL_IPV4_ADDRESS_SIZE 4
#define PAL_IPV6_ADDRESS_SIZE 16
#define PAL_NET_MAX_ADDR_SIZE 32

typedef uint8_t ipV4Addr_t[PAL_IPV4_ADDRESS_SIZE];
typedef uint8_t ipV6Addr_t[PAL_IPV6_ADDRESS_SIZE];

typedef uint32_t socketLength_t;

typedef struct socketAddress {
    unsigned short    addressType;    /*! Address family for the socket. */
    char              addressData[PAL_NET_MAX_ADDR_SIZE];  /*! Address (based on protocol). */
} socketAddress_t; /*! Address data structure with enough room to support IPV4 and IPV6. */

typedef struct ipV4Addr{
	ipv4_addr_t addr;
	uint16_t port;
} ipV4Addr;

typedef enum {
    PAL_AF_UNSPEC = 0,
    PAL_AF_INET = 2,    /*! Internet IP Protocol.   */
    PAL_AF_INET6 = 10, /*! IP version 6.    */
} palSocketDomain_t;/*! Network domains supported by PAL. */
