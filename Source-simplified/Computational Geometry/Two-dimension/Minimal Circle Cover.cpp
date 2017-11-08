#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
const int N=2005;
const double INF=1e9;
const double eps=1e-8;
const double pi=acos(-1);
inline int read(){
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0'; c=getchar();}
    return x*f;
}

inline int sgn(double x){
    if(abs(x)<eps) return 0;
    else return x<0?-1:1;
}

struct Vector{
    double x,y;
    Vector(double a=0,double b=0):x(a),y(b){}
    bool operator <(const Vector &a)const{
        return sgn(x-a.x)<0||(sgn(x-a.x)==0&&sgn(y-a.y)<0);
    }
    void print(){printf("%lf %lf\n",x,y);}
};
typedef Vector Point;
Vector operator +(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
Vector operator -(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
Vector operator *(Vector a,double b){return Vector(a.x*b,a.y*b);}
Vector operator /(Vector a,double b){return Vector(a.x/b,a.y/b);}
bool operator ==(Vector a,Vector b){return sgn(a.x-b.x)==0&&sgn(a.y-b.y)==0;}
double Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
double Cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
double Len(Vector a){return sqrt(Dot(a,a));}
Vector Normal(Vector a){
    return Vector(-a.y,a.x);//counterClockwise
};
struct Line{
    Point s,t;
    Line(){}
    Line(Point a,Point b):s(a),t(b){}
};
bool isLSI(Line l1,Line l2){
    Vector v=l1.t-l1.s,u=l2.s-l1.s,w=l2.t-l1.s;
    return sgn(Cross(v,u))!=sgn(Cross(v,w));
}
Point LI(Line a,Line b){
    Vector v=a.s-b.s,v1=a.t-a.s,v2=b.t-b.s;
    double t=Cross(v2,v)/Cross(v1,v2);
    return a.s+v1*t;
}
Point Circumcenter(Point a,Point b,Point c){
    Point p=(a+b)/2,q=(a+c)/2;
    Vector v=Normal(b-a),u=Normal(c-a);
    if(sgn(Cross(v,u))==0){
        if(sgn(Len(a-b)+Len(b-c)-Len(a-c))==0) return (a+c)/2;
        if(sgn(Len(a-b)+Len(a-c)-Len(b-c))==0) return (b+c)/2;
        if(sgn(Len(a-c)+Len(b-c)-Len(a-b))==0) return (a+b)/2;
    }
    return LI(Line(p,p+v),Line(q,q+u));
}

double minCircleCover(Point p[],int n,Point &c){
    random_shuffle(p+1,p+1+n);
    c=p[1];
    double r=0;
    for(int i=2;i<=n;i++)
        if(sgn(Len(c-p[i])-r)>0){
            c=p[i],r=0;
            for(int j=1;j<i;j++)
                if(sgn(Len(c-p[j])-r)>0){
                    c=(p[i]+p[j])/2,r=Len(c-p[i]);
                    for(int k=1;k<j;k++)
                        if(sgn(Len(c-p[k])-r)>0){
                            c=Circumcenter(p[i],p[j],p[k]);
                            r=Len(c-p[i]);
                        }
                }
        }
    return r;
}

int n;
Point p[N],c;
int main(int argc, const char * argv[]){
    while(true){
        n=read();if(n==0) break;
        for(int i=1;i<=n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        double r=minCircleCover(p,n,c);
        printf("%.2f %.2f %.2f\n",c.x,c.y,r);
    }
}
