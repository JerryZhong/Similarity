#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include"scorecosine.h"


namespace  crystal
{
    using namespace std;
    scorecosine::scorecosine(void)
    {
    }

    scorecosine::~scorecosine(void)
    {
    }
	
/*
   int  scorecosine::compute(int threadnum)
   {
        int midpos=0;
        map<int,vector<uscore_t> >::iterator iter = _item_users.begin(),iter_end=_item_users.end();
        for(;iter!=iter_end; iter++)
        {   
            midpos = iter->first;
            fprintf(stderr,"mispos:%d\n",midpos);
            vector<sim_t> sims;
            if(compute(midpos,sims))
                continue;
            else
                save(midpos,sims);
        }
        return 0;
    }
    */
    

     int scorecosine::compute(int midpos,vector<sim_t> &sims)
    {
       
        map<int ,vector<uscore_t> >::iterator iter_a = _item_users.find(midpos);
        if(iter_a==_item_users.end())
            return 1;
        sims.clear();
        int midnum = _item_users.size();//总媒体数
        vector<int> cocurrence(midnum,0);
        vector<uscore_t> *users_viewmida=&iter_a->second;
        int numa_users = users_viewmida->size();
        int norm2_a    = norm2(*users_viewmida);
         for(int i=0;i<numa_users;i++)
        {
            int user_i=(*users_viewmida)[i]._user;
            vector<iscore_t> *mids_viewed_by_useri = &_user_items[user_i];
            int numi_mids = mids_viewed_by_useri->size();
             for(int j=0;j<numi_mids;j++)
            {
                int midpos2 =(*mids_viewed_by_useri)[j]._item;
                if(midpos!=midpos2)
                    cocurrence[midpos2]+=(*mids_viewed_by_useri)[j]._score * (*users_viewmida)[i]._score;
            }
        }

        for(int i=0;i<midnum;i++)
        {
            if(cocurrence[i]==0)
                continue;
            int norm2_b = norm2(_item_users[i]);
            int numerator = cocurrence[i];
            double sim_ab = (1.0*numerator)/sqrt((double)(1.0*norm2_a*norm2_b));
            sims.push_back(sim_t(i, sim_ab));
        }
/*        for(int i=0;i<sims.size();i++)
        {
           fprintf(stderr,"%d::%f ",sims[i]._item,sims[i]._sim);
        }
        fprintf(stderr,"\n");
*/
        return 0;
    }


    /* int scorecosine::save(int midpos , vector<sim_t> &sims)
    {
        int sz = sims.size();
        if(sz==0)
            return 0;
        sz = sz > _topn_sims?_topn_sims:sz;
        partial_sort(sims.begin(), sims.begin()+sz, sims.end(),larger_sim);
        int mid = _idx2mid[midpos];
        for(int i=0;i<sz;i++)
           sims[i]._item = _idx2mid[sims[i]._item];//change pos to mid.
        _item_sims[mid].insert(_item_sims[mid].end(),sims.begin(),sims.begin()+sz);
    }*/
    
}
