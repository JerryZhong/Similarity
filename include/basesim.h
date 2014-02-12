#ifndef _BASESIM_H
#define _BASESIM_H
#include<map>
#include<vector>
#include<sim_type.h>

/*a abstract class about similarity */
 namespace crystal
{
    using namespace std;
    class basesim
    {
        public:
            /*return 0 on success.other failed...*/
            virtual int load(const char *file)=0;
            
            /*
             *preprocess data after loaded from file (load function executed over.)
             *return 0 on success.other failed...*/
            virtual int preprocess()=0;

            /*
             * compute similarity of all items use different cf similarity alogrithm.
             * @threadnum:set the number of thread to archive high performance.
             * return 0 on success,other failed...*/
            virtual int compute(int threadnum)=0;

            /* post process data after compute similarity
            *  return 0 on success,other failed...*/
            virtual int postprocess();

            /*
            * dump the similarity between all items to @outputfile
            * return 0 on success ,other failed...*/
            virtual int dump(const char *outputfile);
        
        public:
            basesim();
            virtual ~basesim();
            
            void set_min_occur_user(int limit);
            
            void set_max_occur_user(int limit);
            
            void set_topn_sims(int limit);
            
        protected:
            map<int,vector<sim_t> >  _item_sims;
            map<int,int>             _mid2idx  ;
            map<int,int>             _idx2mid  ;

            int _min_occur_user;
            int _max_occur_user;
            int _topn_sims;
    };
}
#endif
