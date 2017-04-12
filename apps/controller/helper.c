#include <string.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "controller/helper.h"

char *get_controller_ip()
{
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr, *r_addr = NULL;
    const char *LOCAL_IP = "127.0.0.1";

    getifaddrs(&ifap);
    ifa = ifap;
    while (ifa != NULL) {
        if (ifa->ifa_addr->sa_family == AF_INET) { // if ipv4
            if (ifa->ifa_addr) {
                sa = (struct sockaddr_in *) ifa->ifa_addr;
                addr = inet_ntoa(sa->sin_addr);
                // ignore local ip
                if ((strcmp(addr, LOCAL_IP) != 0) & (r_addr == NULL)) {
                    r_addr = malloc(1 + strlen(addr));
                    strcpy(r_addr, addr);
                }
            }
        }
        ifa = ifa->ifa_next;
    }
    freeifaddrs(ifap);
    return r_addr;
}
