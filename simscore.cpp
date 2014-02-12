#include"simscore.h"
#include "util.h"
#include<stdio.h>
#include<algorithm>

namespace crystal{
    using namespace std;

    char *line;
    int max_line_len;
    
     int simscore::load(const char * file)
    {
        char *endptr,*idx,*val;
        int mid,uid,score     ; 
        FILE *fp = fopen(file,"r");
         if(fp==NULL)
        {   
            fprintf(stderr,"can't open input file %s\n",file);
            exit(1);
        }

        int midindex=0;
        int midpos  =0;
        line=NULL;
        max_line_len    =1024;
        line = Malloc(char,max_line_len);
         while(util::readline(fp)!=NULL)
        {
            char *p= strtok(line," \t");
//            fprintf(stderr,"mediaid:%s\n",p);
            mid = (int)strtol(p,&endptr,10);
            map<int,int>::iterator iter  = _mid2idx.find(mid);
             if(iter == _mid2idx.end())
            {
                _mid2idx.insert(pair<int,int>(mid,midindex));
                _idx2mid.insert(pair<int,int>(midindex,mid));
                midpos = midindex;
                midindex++;
            }
            else
                midpos = iter->second;
             while(1)
            {
                idx   = strtok(NULL,":")  ;
                val   = strtok(NULL," \t");
                if(val==NULL)
                    break;
                uid = (int)strtol(idx,&endptr,10);
                score = (int)strtol(val,&endptr,10);
                _item_users[midpos].push_back(uscore_t(uid,score));
                _user_items[uid].push_back(iscore_t(midpos,score));
            }
         }

/*        map<int,vector<uscore_t> >::iterator iter = _item_users.begin(),iter_end=_item_users.end();
        for(;iter!=iter_end;iter++)
        {
            fprintf(stderr,"first:%d\n",iter->first);
            vector<uscore_t> *xxx= &iter->second;
             for(int i=0;i<xxx->size();i++)
            {
                fprintf(stderr,"%d:%d ",(*xxx)[i]._user,(*xxx)[i]._score);
            }
                fprintf(stderr,"\n");
        }
*/
         return 0;
    }
    
     int simscore::preprocess()
    {
        map<int, vector<uscore_t> >::iterator iter=_item_users.begin(),iter_end=_item_users.end();
         for(; iter!=iter_end; iter++)
        {
            int key=iter->first;
            vector<uscore_t> *value=&(iter->second);
            sort(iter->second.begin(),iter->second.end(),less_user);
            _item_sims[_idx2mid[iter->first]] = vector<sim_t>();
            _item_sims[_idx2mid[iter->first] ].resize(2*_topn_sims);
        }
        return 0;
    }
    
    int simscore::norm2(vector<uscore_t> &scores)
    {
        int sum=0;
        int sz = scores.size();
         for(int i=0;i<sz;i++)
        {
            sum+= scores[i]._score*scores[i]._score;
        }
        return sum;
    }
}
