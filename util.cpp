#include "util.h"
#include "sim_type.h"

namespace crystal{

    char* util::readline(FILE *fp)
    {   
        int len;
        if(fgets(line,max_line_len,fp)==NULL) {
             return NULL;
        }
         while(strrchr(line,'\n')==NULL)
        {   
            max_line_len *=2;
            line = (char *)realloc(line,max_line_len);
            len  = (int)strlen(line);
            if (fgets(line+len,max_line_len,fp)==NULL)
               break;
        }   
           return line;
    }

}
