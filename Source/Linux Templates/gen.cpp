#include<sys/timeb.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
    freopen("gen.in","r",stdin);
    freopen(".in","w",stdout);
    struct timeb t;ftime(&t);
    srand(t.millitm+t.time*1000);
    fclose(stdin); fclose(stdout);
    return 0;
}
