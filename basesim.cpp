#include<stdio.h>
#include<algorithm>
#include"basesim.h"

namespace crystal{
    using namespace std;
    
    basesim::basesim():_min_occur_user(0),_max_occur_user(0),_topn_sims(0X7FFFFFF)
    {
    }

    basesim::~basesim()
    {   
    }
    
    int basesim::postprocess()
    {
        map<int,vector<sim_t> > ::iterator iter = _item_sims.begin(),iter_end = _item_sims.end();
        for(;iter!=iter_end;iter++)
            sort(iter->second.begin(),iter->second.end(),larger_sim);//<alogrithm>
        return 0;
    }
    
    int basesim::dump(const char * outputfile)
    {
         FILE *fp = fopen(outputfile,"w");
        if(fp==NULL)
        {
            fprintf(stderr,"open %f error!",outputfile);
            exit(1);
        }

        map<int, vector<sim_t> >::iterator iter = _item_sims.begin(), iter_end = _item_sims.end();
         for(;iter!=iter_end;iter++)
        {
            int mid = iter->first;
            if(iter->second.size()==0)
                continue;
            fprintf(fp,"%d ",mid);
            int num = (int)iter->second.size() > _topn_sims ? _topn_sims : (int)iter->second.size();
             for(int i=0;i<num;i++)
                fprintf(fp,"%d,%f ",iter->second[i]._item, iter->second[i]._sim)     ;
            fprintf(fp,"\n")    ;
        }
        return 0;
    }
    
     void basesim::set_min_occur_user(int limit)
    {
        _min_occur_user=limit;   
    }
    void basesim::set_max_occur_user(int limit)
    {
        _max_occur_user=limit;
    }
    void basesim::set_topn_sims(int limit)
    {
        _topn_sims=limit;
    }

}
