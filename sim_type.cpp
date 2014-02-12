#include"sim_type.h"
namespace crystal
{
    bool larger_sim(const sim_t &a,const sim_t &b)
    {
            return a._sim > b._sim;
    }
    
    bool less_user(const uscore_t &a,const uscore_t &b)
    {
            return a._user< b._user;
    }
}
