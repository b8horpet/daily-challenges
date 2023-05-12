#include <cstdlib>//sry, this    isn't a flower
#include <cstdio>// do not      tell a botanist
using u=unsigned;using f=       double;struct P
{f x,y;};struct T{f a,b        ,c,d,e;P t(P p){
return{p.x*a+p.y*b,p.x          *c+p.y*d+e};}};
char m[W*H*3]={0};T            t[]={{0,0,0,.16,
0},{.85,.04,-.04,.85            ,1.6},{.2,-.26,
.23,.22,1.6},{-.15,            .28,.26,.24,.44}
};const char R[]=             "\x1V]d";int main
(){u r[100]={0};                u c=0;for(u i=0
;i<4;++i){for(;                  c<R[i];++c){r[
c]=i;}}P p{0,0}                  ;auto M=[](P x
)->P{return{x.x                   *f(W)/10.0+(W
/2),f(H)-(x.y*f                   (H)/10.0)};};
for(u i=0;i<L;++                 i){auto o=t[r[
rand()%100]];p=o.t(p);P         c=M(p);m[3*(u(c
.y)*W+u(c.x))+1]= -1;}         printf("P6\n%d "
"%d\n255\n",W,H);fwrite    (m,W*H*3,1,stdout);}
