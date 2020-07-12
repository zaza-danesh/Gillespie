#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>
#include <signal.h>
#include <limits.h>
//#include <iostream.h>
//#include <fstream.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sysexits.h>
#include <err.h>
#include <errno.h>
#include "aleatoire.h"
#define RINIT  long idum; time_t seconds; time(&seconds); srand(seconds); idum=-rand();
#define SP " "
#define CR "\n"
#define Pi 3.1415926535897932385
