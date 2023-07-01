#include "sshfinder.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_RANGE_SIZE 100

int
main(int argc, char *argv[])
{
    char range[MAX_RANGE_SIZE];
    int port = 22;
    int thread = 10;
    int help_flag = 0;

    static struct option long_options[] = {
        {"help"  ,   no_argument,       0, 'h'},
        {"range" ,   required_argument, 0, 'r'},
        {"port"  ,   required_argument, 0, 'p'},
        {"thread",   required_argument, 0, 't'},
        {0       ,   0                , 0,   0}
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
                strncpy(range, optarg, MAX_RANGE_SIZE);
                printf("Range = %s\n", range);
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

    return EXIT_SUCCESS;
}

static void usage(void)
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
