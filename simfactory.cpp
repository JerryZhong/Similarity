#include<string.h>
#include"simfactory.h"
#include"scorecosine.h"
namespace crystal{

    simfactory::simfactory(void)
    {
    }
    
    simfactory::~simfactory(void)
    {
    }

    basesim *simfactory::create(const char* based, const char * algorithm)
    {
        if(strcmp(based,"score")==0)
        {
            if(strcmp(algorithm,"cosine")==0)
               return new scorecosine();
            else
               return 0;
        }
        else
            return 0;
    }
    

}
