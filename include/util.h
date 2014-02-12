#ifndef _UTIL_H
#define _UTIL_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sim_type.h"

#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
namespace crystal{
    using namespace std;
    
    class util
    {
        public:
             static char *readline(FILE *input);
    };

}



#endif
