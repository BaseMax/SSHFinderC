#ifndef SSHFINDER_H
#define SSHFINDER_H

#include <stdbool.h>

#define INITIAL_CAPACITY 1

#define MF(p) \
    freemem((void **)&(p))

#define RAII_VARIABLE(vartype,varname,initval,dtor) \
    void _dtor_ ## varname (vartype * v) { dtor(*v); } \
    vartype varname __attribute__((cleanup(_dtor_ ## varname))) = (initval)

static void usage(void);
void freemem(void **pp);
static int isValidIP(const char *ip);
static bool isIpAvailable(const char* ip, int port);
static void proccessIPS(char **ips, int count, int port);

#endif // SSHFINDER_H
