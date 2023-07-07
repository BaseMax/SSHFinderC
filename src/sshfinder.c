#include "sshfinder.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>


int 
main(int argc, char *argv[])
{
    int port = 22;
    int thread = 10;
    int help_flag = 0;


    int capacity = INITIAL_CAPACITY;
    RAII_VARIABLE(char **,ips,malloc(capacity * sizeof(char *)),MF);
    int ipCount = 0;

    static struct option long_options[] = {
        {"help"   ,   no_argument,       0, 'h'},
        {"range"  ,   required_argument, 0, 'r'},
        {"port"   ,   required_argument, 0, 'p'},
        {"threads",   required_argument, 0, 't'},
        {0        ,   0                , 0,   0}
    };
    
    int option;
    while ((option = getopt_long(argc, argv,
                    "hr:p:t:", long_options, NULL)) != -1) {
        if (option == 'h') {
            help_flag = 1;
            break;
        }

        switch (option) {
            case 'r':
                char *ipToken = strtok(optarg, ",");
                while (ipToken != NULL) {
                    char *slashPos = strchr(ipToken, '/');
                    if (slashPos != NULL) {
                        if(!isValidIP(ipToken)) {
                            fprintf(stderr,
                                    "Invalid IP range %s\n",
                                    ipToken);
                            exit(EXIT_FAILURE);
                        } else {
                            
                        }
                    } else {
                        if (!isValidIP(ipToken)) {
                            fprintf(stderr,
                                    "Invalid IP address %s\n",
                                    ipToken);
                            exit(EXIT_FAILURE);
                        } else {
                            ips[ipCount] = strdup(ipToken);
                            ipCount++;
                        }
                    }

                    if (ipCount >= capacity) {
                        capacity *= 2;
                        ips = realloc(ips, capacity * sizeof(char *));
                    }

                    ipToken = strtok(NULL, ",");
                }
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case 't':
                thread = atoi(optarg);
                printf("Thread = %d\n", thread);
                break;
            default:
                fprintf(stderr,
                        "Option %s not provided.\n",
                        argv[1]
                       );
                exit(EXIT_FAILURE);
        }
    }

    if (help_flag) {
        usage();
        return EXIT_SUCCESS;
    }

    proccessIPS(ips, ipCount, port);
    

    return EXIT_SUCCESS;
}


static 
void usage(void)
{
    printf(
"Usage information:\n"
"\t-h     --help          Display the help message and usage information\n"
"\t-r     --range         The ip range to scan (ex. 192.168.0.1/24,192.168.2.0/24)\n"
"\t-p     --port          The port number to scan for SSH services (default is 22)\n"
"\t-t     --threads       The number of concurrent therads to use for scanning (default is 10\n"
"Authors: Maximilian Edison <maximilianedison@gmail.com>\n"
"         BaseMax           <basemaxcode@gmail.com>\n"
    );
}


void 
freemem(void **pp)
{
    if (pp != NULL && *pp != NULL) {
        free(*pp);
        *pp = NULL;
    }
}


static
bool isValidIP(const char *ip) {
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ip, &(sa.sin_addr));

    if (result == 1)
        return true;
    else if (result == 0) {
        char *slashPos = strchr(ip, '/');
        if (slashPos != NULL) {
            *slashPos = '\0';
            int isValidCIDR = inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1;
            *slashPos = '/';

            if (isValidCIDR) {
                int cidr = atoi(slashPos + 1);
                if (cidr >= 0 && cidr <= 32) {
                    return true;
                }
            }
        }
    }

    return false;
}


bool 
isIpAvailable(const char* ip, int port) 
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return false;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &(serverAddr.sin_addr)) <= 0) {
        close(sockfd);
        return false;
    }

    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        close(sockfd);
        return false;
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl");
        close(sockfd);
        return false;
    }

    int result = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result < 0) {
        if (errno == EINPROGRESS) {
            struct pollfd fds[1];
            fds[0].fd = sockfd;
            fds[0].events = POLLOUT;

            int pollResult = poll(fds, 1, 5000); 
            if (pollResult < 0) {
                perror("poll");
                close(sockfd);
                return false;
            } else if (pollResult == 0) {
                close(sockfd);
                return false;
            }

            if (fds[0].revents & POLLOUT) {
                int error = 0;
                socklen_t len = sizeof(error);
                if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) == 0 && error == 0) {
                    close(sockfd);
                    return true;
                }
            }
        }
        close(sockfd);
        return false;
    }

    close(sockfd);
    return true;
}


static
void proccessIPS(char **ips, int count, int port)
{
    for (int i = 0; i < count; i++) {
        if (isIpAvailable(ips[i], port))
            printf("IP %s on %d is available\n", ips[i], port);
        else 
            printf("IP %s on %d is not available\n", ips[i], port);
    }
}
