#ifndef _SIM_H
#define _SIM_H

/**
 *base struct and consant variable  used in this program
 * */
namespace crystal
{
    const int buffer_size = 64;
    extern char *line;
    extern int max_line_len;
    /*item similarity */
    struct sim_t
    {
        sim_t():_item(0),_sim(0.0){}
        sim_t(int item,double sim):_item(item),_sim(sim){}
        ~sim_t(){}
        int    _item;
        double  _sim;
    };

    /*item score struct */
    struct uscore_t
    {
        uscore_t():_user(0),_score(0){}
        uscore_t(int user,int score):_user(user),_score(score){}
        ~uscore_t(){}
        int _user ;
        int _score;
    };

    /*user score struct */
    struct iscore_t
    {
        iscore_t():_item(0),_score(0){}
        iscore_t(int item,int score):_item(item),_score(score){}
        ~iscore_t(){}
        int _item ;
        int _score;
    };

    bool larger_sim(const sim_t &a, const sim_t &b);/*sort the struct of sim_t a certain way[sim_score]:largest-lowest      */
    bool less_user(const uscore_t &a, const uscore_t &b);/*sort the struct of uscore_t a certain way[userid]:lowest-largest */
}
#endif
