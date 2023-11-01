#include "ary.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
const double eps = 1e-10;
bool equal(double x, double y) {
    return fabs(x - y) < eps;
}

void dbg(wartosc a) {
    printf("(%.15lf %.15lf  %d)\n", a.x, a.y, a.czy_anty);
}

int main() {


    wartosc a = wartosc_dokladna(0.0);
    wartosc b = wartosc_od_do(-100.0, 200.0);
    wartosc c = razy(a, b); //[0; 0]
    
    assert(in_wartosc(c, 0.0));
    assert(equal(min_wartosc(c), 0.0));
    assert(equal(max_wartosc(c), 0.0));
    assert(equal(sr_wartosc(c), 0.0));
    assert(!in_wartosc(c, -0.0001));
    assert(!in_wartosc(c, -0.0001));

    wartosc d = razy(b, wartosc_dokladna(-1.0));    //[-200; 100]
    assert(in_wartosc(d, -200.0));
    assert(in_wartosc(d, 100.0));
    assert(!in_wartosc(d, 200.0));


    wartosc e = podzielic(wartosc_dokladna(1), d);  //R - [-0.005; 0.01]


    assert(in_wartosc(e, -0.005000));
    assert(in_wartosc(e, -0.005001));
    assert(!in_wartosc(e, -0.00499999));
    assert(in_wartosc(e, 0.01000));
    assert(in_wartosc(e, 0.0100001));
    assert(!in_wartosc(e, 0.00999999));
    //assert(isnan(sr_wartosc(e)));

    wartosc f = podzielic(wartosc_od_do(-1.0, 7.0), e); //[-1400.0; 700.0]



    assert(equal(min_wartosc(f), -1400.0));
    assert(equal(max_wartosc(f), 700.0));
    assert(equal(sr_wartosc(f), -350.0));
    assert(in_wartosc(f, -1400.0));
    assert(!in_wartosc(f, -1400.00001));
    assert(in_wartosc(f, -1399.99991));
    assert(in_wartosc(f, 700.0));
    assert(!in_wartosc(f, 700.00001));
    assert(in_wartosc(f, 699.99999));
    

    wartosc g = podzielic(wartosc_dokladna(1.0), e); //[-200; 100]
    wartosc h = plus(wartosc_od_do(-1000, -500), g); //[-1200; -400]
    wartosc i = podzielic(wartosc_od_do(1.0, 2.0), h); //[-0.005; -0.000833333]  
    wartosc j = plus(wartosc_od_do(0.005, 0.006), i); //[0.0; 0.0051666]
    wartosc k = podzielic(wartosc_od_do(1.0, 2.0), j); //[193.548387096774206; inf]
    dbg(k);
    assert(equal(min_wartosc(k), 193.548387096774206));
    assert(isinf(sr_wartosc(k)));
    assert(sr_wartosc(k) > 0);
    assert(isinf(max_wartosc(k)));
    assert(!in_wartosc(k, 0.0));
    assert(!in_wartosc(k, -100000.0));
    assert(in_wartosc(k, 100000.0));
    assert(!in_wartosc(k, 193.4999999));
    assert(in_wartosc(k, 193.60101));
    dbg(k);
    wartosc l = podzielic(wartosc_od_do(-9.0, 9.0), k); //[-0.0465; 0.0465]
    dbg(k);
    dbg(l);
    assert(equal(sr_wartosc(l), 0.0));
    assert(in_wartosc(l, 0.0));
    assert(in_wartosc(l, 0.0465));
    assert(!in_wartosc(l, 0.04650001));

    wartosc m = wartosc_dokladnosc(1.0, 100); //[0.0; 2.0]
    wartosc n = wartosc_dokladnosc(-1.0, 100); //[-2.0; 0.0], bardzo fajny edge case

    assert(in_wartosc(n, -2.0));
    assert(in_wartosc(n, 0.0));
    assert(!in_wartosc(n, 0.000001));
    assert(!in_wartosc(n, 2.0));
    
    wartosc o = minus(m, n);    //[0.0; 4.0]

    assert(in_wartosc(o, 0.0));
    assert(!in_wartosc(o, -0.000001));
    assert(!in_wartosc(o, 4.000001));
    assert(in_wartosc(o, 4.000000));
    assert(equal(sr_wartosc(o), 2.0000));

    wartosc p = razy(k, wartosc_od_do(-3.0, -2.0)); //[-inf; -387.096774193548413]

    assert(isinf(sr_wartosc(p)));
    assert(sr_wartosc(p) < 0.0);
    assert(isinf(min_wartosc(p)));
    assert(min_wartosc(p) < 0.0);
    assert(equal(max_wartosc(p), -387.096774193548413));
    
}
