#ifndef SIMSCORE_THREAD_H
#define SIMSCORE_THREAD_H
#include<pthread.h>
#include"simscore.h"
namespace crystal{
    using namespace std;
    class simscore_thread:public simscore
    {
        public:
            simscore_thread(void);
            virtual ~simscore_thread(void);
        
            int compute(int threadnum);

            bool fetch(int &item);

            int save(int item,vector<sim_t> &sims);
        
        public:
            virtual int compute(int item,vector<sim_t> &sim)=0;

        private:
            static  void* compute_thread(void *arg);

        private:
            pthread_mutex_t _cs;
    };
}

#endif
