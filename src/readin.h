#ifndef READIN_H
#define READIN_H
#include <stdio.h>
char *gets_unl(int tsknte);
char *readstdin(void);
char *delmem(char *str);
int want_date(void);

size_t is_null(char *ptr);
char *gets_unl_f(FILE *db);
#endif // -> READIN_H
