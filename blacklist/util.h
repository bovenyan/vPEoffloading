#ifndef UTIL_H
#define UTIL_H
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

unsigned int ip_str2int(const char * ip_str); 

char * ip_int2str(const unsigned int ip_int);

#endif
