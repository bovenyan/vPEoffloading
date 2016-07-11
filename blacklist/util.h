#ifndef UTIL_H
#define UTIL_H
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

unsigned int ip_str2int(const char * ip_str) {
    struct in_addr res_obj;
    inet_aton(ip_str, &res_obj);
    return res_obj.s_addr;
}

char * ip_int2str(const unsigned int ip_int) {
    struct in_addr res_obj;
    res_obj.s_addr = ip_int;
    return inet_ntoa(res_obj);
}
#endif
