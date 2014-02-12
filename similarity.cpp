#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "simfactory.h"
using namespace std;

char *line;
const char *sim_help="Usage:\n" \
                     "similarity score cosine <threadnum> <min_occur_user> <max_occur_user> <topN> <inputfile> <outputfile>\n" \
                     "Specification :\n"    \
                     "when use score based similarity algorithm,the inputfile format is :\n" \
                     "itemid1 userid1:score1 userid2:score2 userid3:score3 \n" \
                     "itemid1 userid1:score1 userid2:score2 userid3:score3 \n" \
                     "...\n";

 int main(int argc,char **argv)
{
    if(argc!=9)
    {
        fprintf(stderr,sim_help);
        exit(1);
    }
    else
    {
//        char *a="score";
//        char *b="cosine";
//        char *c="outputweight";
//        char *d="topnmedia";
    
        char type[1024],tid[1024],inputfile[1024],outputfile[1024];
        strcpy(type,argv[1]);   //[score,view]
        strcpy(tid ,argv[2]);   //[cosine,tonimato,...]
        int threadnum = atoi(argv[3]);
        int min_occur_user=atoi(argv[4]);
        int max_occur_user=atoi(argv[5]);
        int topn = atoi(argv[6]);
        strcpy(inputfile,argv[7]);
        strcpy(outputfile,argv[8]);

/*      char type[1024],tid[1024],inputfile[1024],outputfile[1024];
        strcpy(type,a);   //[score,view]
        strcpy(tid ,b);
        int threadnum =3;
        int min_occur_user=1;
        int max_occur_user=1000;
        int topn = 3;
        strcpy(inputfile,c);
        strcpy(outputfile,d);
*/
        crystal::basesim *cf_sim = crystal::simfactory::create(type,tid);
        if(cf_sim==0)
        {
            fprintf(stderr,"create cf_sim error!\n");
            return -1;
        }
        cf_sim->set_min_occur_user(min_occur_user);
        cf_sim->set_max_occur_user(max_occur_user);
        cf_sim->set_topn_sims(topn);
        
        fprintf(stderr,"loading user items...\n");
        time_t start_tm = time(NULL);
        int err = cf_sim->load(inputfile);
        if(err!=0)
        {
            fprintf(stderr,"load function error!\n");
            delete cf_sim;
            return -1;
        }
        time_t end_tm = time(NULL);
        fprintf(stderr,"finished, time used:%dS\n",end_tm-start_tm);

        fprintf(stderr,"preprocessing data ...\n");
        start_tm = time(NULL);
        err = cf_sim->preprocess();
        if(err != 0)
        {
            fprintf(stderr,"preprocess function error\n");
            delete cf_sim;
            return -1;
        }
        end_tm = time(NULL);
        fprintf(stderr,"finished, time used:%dS\n",end_tm-start_tm);

        fprintf(stderr,"computing similarity ...\n");
        start_tm = time(NULL);
        err = cf_sim->compute(threadnum);
         if(err != 0)
        {   
            fprintf(stderr,"computing similarity error\n");
            delete cf_sim;
            return -1; 
        }
        end_tm = time(NULL);
        fprintf(stderr,"finished, time used:%dS\n",end_tm-start_tm);
    
        fprintf(stderr,"post processing data ... \n");
        start_tm = time(NULL);
        err = cf_sim->postprocess();
        if(err != 0)
        {
            fprintf(stderr,"post processing data error\n");
            delete cf_sim;
            return -1;
        }
        end_tm = time(NULL);
        fprintf(stderr,"finished, time used:%dS\n",end_tm-start_tm);
        
        fprintf(stderr,"dumping similarity to file ... \n");
        start_tm = time(NULL);
        err = cf_sim->dump(outputfile);
        if(err != 0)
        {
            fprintf(stderr,"dumping similarity to file error\n");
            delete cf_sim;
            return -1;
        }
        end_tm = time(NULL);
        fprintf(stderr,"finished, time used:%dS\n",end_tm-start_tm);
        delete cf_sim;
        return 0;
     }
}
