#ifndef SSHFINDER_H
#define SSHFINDER_H

#define MF(p) \
    freemem((void **)&(p))

#define RAII_VARIABLE(vartype,varname,initval,dtor) \
    void _dtor_ ## varname (vartype * v) { dtor(*v); } \
    vartype varname __attribute__((cleanup(_dtor_ ## varname))) = (initval)

static void usage(void);
void freemem(void **pp);

#endif // SSHFINDER_H
