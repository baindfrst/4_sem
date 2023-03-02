#include <stdio.h>
#include <iostream>
using namespace std;
class drob
{
    public:
    int chisl;
    int znam;
    drob operator* (drob frst)
    {
        drob ret(frst.chisl * chisl, frst.znam * znam);
        return ret;
    }
    bool operator< (drob frst)
    {
        return chisl < frst.chisl;
    }
    bool operator> (drob frst)
    {
        return chisl > frst.chisl;
    }
    bool operator== (drob frst)
    {
        return chisl == frst.chisl;
    }
    operator double()
    {
        double ret = znam % 10;
        int rez = (znam / 10);
        while(rez != 0)
        {
            ret /= 10;
            ret += rez % 10;
            rez /= 10;
        }
        ret /= 10;
        ret += chisl;
        return ret;
    }
    ostream& operator<< (ostream& t)
    {
        cout << chisl << '/' << znam; 
        return t;
    }
    drob(int ch = 1, int zn = 1)
    {
        if(zn == 0)
        {
            zn = 1;
        }
        chisl = ch;
        znam = zn;
    }
};

int main()
{
    drob f(3332, 4322);
    drob s(2, 5);
    drob mult = f * s;
    double r;
    r = f;
    cout << r << endl;
    mult << cout << endl;
    f << cout << endl;
а}