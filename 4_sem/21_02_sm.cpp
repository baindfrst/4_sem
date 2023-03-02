#include <iostream>
namespace A{int f = 1;}
namespace B{int f = 2;}
using namespace std;
int main()
{
    using namespace B;
    cout<<f;
    using namespace A;
    using B::f;
    cout<<f;
    return 0;
}