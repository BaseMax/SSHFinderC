#include "sshfinder.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>



// This is for debug and test only
void
printIPS(char **ips, int count)
{
    for (int i = 0; i < count; i++) {
	if (!isValidIP(ips[i])) {
		printf("Invalid IP address: %s\n", ips[i]);
		exit(EXIT_FAILURE);
	}
        printf("IP = %s\n", ips[i]);
    }
}

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
                    if (ipCount >= capacity) {
                        capacity *= 2;
                        ips = realloc(ips, capacity * sizeof(char *));
                    }
                    ips[ipCount] = strdup(ipToken);
                    ipCount++;
                    ipToken = strtok(NULL, ",");
                }
                break;
            case 'p':
                port = atoi(optarg);
                printf("Port : %d\n", port);
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

    printIPS(ips, ipCount);

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
"\t-t     --threads       The number of concurrent therads to use for scanning (default is 10)\n"
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
int isValidIP(const char *ip) {
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ip, &(sa.sin_addr));

    if (result == 1)
        return 1;
    else if (result == 0) {
        char *slashPos = strchr(ip, '/');
        if (slashPos != NULL) {
            *slashPos = '\0';
            int isValidCIDR = inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1;
            *slashPos = '/';

            if (isValidCIDR) {
                int cidr = atoi(slashPos + 1);
                if (cidr >= 0 && cidr <= 32) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

