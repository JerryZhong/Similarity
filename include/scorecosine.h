#ifndef _SCORE_COSINE_H
#define _SCORE_COSINE_H
#include"simscore_thread.h"
namespace crystal
{
     class scorecosine :public simscore_thread
    {
        public:
            scorecosine(void);	
            virtual ~scorecosine(void);
        
            virtual int compute(int item,vector<sim_t> &sims);
    };
}
#endif
