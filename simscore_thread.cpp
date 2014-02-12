#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include"simscore_thread.h"

namespace crystal
{
    using namespace std;
     simscore_thread::simscore_thread(void)
    {
        pthread_mutex_init(&_cs,0);
    }

     simscore_thread::~simscore_thread(void)
    {
        pthread_mutex_destroy(&_cs);
    }
    
    int  simscore_thread::compute(int threadnum)
    {
        vector<pthread_t> threads;
        for(int i=0;i<threadnum;i++)
        {
            pthread_t hd;
            if(pthread_create(&hd,0,compute_thread,this)!=0)//this as the parameter 
                return -1;
            else
                fprintf(stderr,"pThreadID=%1u\n",hd);
            threads.push_back(hd);
        }

        for(int i=0;i<threadnum;i++)
            pthread_join(threads[i],0);
        return 0;
    }

    bool simscore_thread::fetch(int &item)
    {
        bool flag=false;
        pthread_mutex_lock(&_cs);
        static map<int,vector<uscore_t> >::iterator iter_a = _item_users.begin(),iter_a_end=_item_users.end();
        if(iter_a!=iter_a_end)
        {
            item = iter_a->first;
            flag = true;
            iter_a++;
        }
        pthread_mutex_unlock(&_cs);
        return flag;
    }

     int simscore_thread::save(int midpos,vector<sim_t> &sims)
    {
        int  sz = sims.size();
        if(sz==0)
            return 0;
        sz = sz >_topn_sims?_topn_sims:sz;
        partial_sort(sims.begin(),sims.begin()+sz,sims.end(),larger_sim);
        int mid = _idx2mid[midpos];
         for(int i=0;i<sz;i++)
            sims[i]._item = _idx2mid[sims[i]._item];//change midpos to mid.
            
        pthread_mutex_lock(&_cs);
        _item_sims[mid].insert(_item_sims[mid].end(),sims.begin(),sims.begin()+sz);
        pthread_mutex_unlock(&_cs);
        return 0;
    }
    
     void* simscore_thread::compute_thread(void *arg )
    {
        simscore_thread * psim = (simscore_thread*)arg;
        int item=0;
        vector<sim_t> sims(psim->_item_users.size());//temp vector info...
        bool flag = psim->fetch(item);
         while(flag)
        {
            sims.clear();//clear the memory 
            psim->compute(item,sims);
            psim->save(item,sims);
            flag = psim->fetch(item);
        }
        pthread_exit(0);
        return 0;
    }
}
