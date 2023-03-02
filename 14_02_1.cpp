#include <stdio.h>
#include <iostream>
using namespace std;

class atd
{
    double *obj;
    int len;
    int max_len;
    friend atd operator+ (atd frst, atd scnd);
    friend atd operator+ (atd frst, int scnd);
    
    public:
    atd(int max_len_inp)
    {
        obj = new double[max_len];
        len = 0;
        max_len = max_len_inp;
    }

    bool put(double inp)
    {
        if(len != max_len - 1)
        {
            obj[len] = inp;
            len++;
            return 1;
        }
        else
        {
            return 0;
        }
    }

    double get()
    {
        if(len != 0)
        {
            double to_ret = obj[0];
            for (int i = 0; i != (len--); i++)
            {
                obj[i] = obj[i+1];
            }
            return to_ret;
        }
        else
        {
            return 0;
        }
    }

    bool empty()
    {
        if(len == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    bool full()
    {
        if(len == max_len - 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void print()
    {
        for(int i = 0; i != len; i++)
        {
            printf("%.4f ", obj[i]);
        }
        printf("\n");
    }

    ~atd()
    {
        delete[] obj;
    }
};

atd operator+ (atd frst, atd scnd)
{
    if(frst.len + scnd.len <= frst.max_len)
    {
        for(int i = 0; i != scnd.len; i++)
        {
            frst.put(scnd.obj[i]);
        }
        printf("multiplied\n");
    }
    return frst;
}

atd operator+ (atd frst, int scnd)
{
    for(int i = 0; i != frst.len; i++)
    {
        frst.put(frst.obj[i] + (double)scnd);
    }
    return frst;
}

int main()
{
    printf("start\n");
    atd frst(9);
    atd scnd(4);
    printf("gen\n");
    for(int i = 0; i < 3; i++)
    {
        frst.put(rand() % 100);
        scnd.put(rand() % 100);
    }
    frst.print();
    scnd.print();
    printf("mult\n");
    int plus = 7;
    frst = frst + scnd;
    printf("obj + obj:");
    frst.print();
    frst = frst + plus;
    frst.print();
    return 0;
}