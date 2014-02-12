#ifndef _SIM_FACTORY_H
#define _SIM_FACTORY_H
#include "basesim.h"
namespace crystal{

    class simfactory
    {
         public:
            simfactory(void);
            virtual ~simfactory(void);
            static basesim* create(const char* based, const char * algorithm);
    };
}
#endif
