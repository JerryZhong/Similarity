#ifndef _SIMSCORE_H
#define _SIMSCORE_H
#include"basesim.h"

namespace crystal
{
    using namespace std;
     class simscore:public basesim
    {
        public:
            virtual int load(const char * file);//implement in this derived class.if upper class need to achieve it, do it self.
            virtual int preprocess();           //the same to the upper.

            int norm2(vector<uscore_t> &scores);
    
        protected:
            map<int,vector<uscore_t> > _item_users;//key:midpos value:<uid1,score1>,<uid2,score2>
            map<int,vector<iscore_t> > _user_items;//key:uid    value:<midpos1,score1>,<midpos2,score2>
    };
}
#endif
