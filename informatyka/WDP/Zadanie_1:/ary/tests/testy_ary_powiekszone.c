//Franciszek Witt
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
    assert(isnan(sr_wartosc(e)));

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

    assert(equal(min_wartosc(k), 193.548387096774206));
    assert(isinf(sr_wartosc(k)));
    assert(sr_wartosc(k) > 0);
    assert(isinf(max_wartosc(k)));
    assert(!in_wartosc(k, 0.0));
    assert(!in_wartosc(k, -100000.0));
    assert(in_wartosc(k, 100000.0));
    assert(!in_wartosc(k, 193.4999999));
    assert(in_wartosc(k, 193.60101));

    wartosc l = podzielic(wartosc_od_do(-9.0, 9.0), k); //[-0.0465; 0.0465]

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

    wartosc q = podzielic(p, wartosc_od_do(0.0, 0.0));
    //R - [-inf; inf]

    assert(!in_wartosc(q, 0.0));
    assert(!in_wartosc(q, 1.0));
    assert(!in_wartosc(q, -1.0));

    wartosc r = plus(q, k);
    //R - [-inf; inf]

    assert(!in_wartosc(r, 0.0));
    assert(!in_wartosc(r, 1.0));
    assert(!in_wartosc(r, -1.0));

    wartosc s = podzielic(wartosc_dokladna(1.0), wartosc_od_do(0.0, 1.0)); //[1.0; inf]

    assert(in_wartosc(s, 1.0));
    assert(!in_wartosc(s, 0.9999));
    assert(in_wartosc(s, 1.00001));
    assert(in_wartosc(s, 100000.6));
    assert(isinf(sr_wartosc(s)));
    assert(sr_wartosc(s) > 0.0);
    
    wartosc t = razy(wartosc_od_do(-123.4, -1.0), s); //[-inf, -1]

    assert(in_wartosc(t, -1.0));
    assert(!in_wartosc(t, -0.9999));
    assert(in_wartosc(t, -1.00001));
    assert(in_wartosc(t, -100000.6));
    assert(isinf(sr_wartosc(t)));
    assert(sr_wartosc(t) < 0.0);
    
    wartosc u = plus(s, t); //[-inf, inf]

    assert(isnan(sr_wartosc(u)));
    assert(isinf(min_wartosc(u)));
    assert(min_wartosc(u) < 0.0);
    assert(max_wartosc(u) > 0.0);
    assert(isinf(max_wartosc(u)));
    assert(in_wartosc(u, 0.0));
    assert(in_wartosc(u, -0.0));
    assert(in_wartosc(u, 1000000.0));
    assert(in_wartosc(u, -1000000.0));

    wartosc v = razy(u, wartosc_dokladna(0.0)); //[0.0, 0.0]

    assert(equal(sr_wartosc(v), 0.0));
    assert(equal(min_wartosc(v), 0.0));
    assert(equal(max_wartosc(v), 0.0));
    assert(in_wartosc(v, 0.0));
    assert(!in_wartosc(v, 0.00001));
    assert(!in_wartosc(v, -0.00001));

    wartosc w = plus(podzielic(wartosc_dokladna(1.0), wartosc_od_do(-0.01, 0.01)), wartosc_dokladna(1.0));   //R - [-99.0; 101.0]

    assert(isnan(sr_wartosc(w)));
    assert(isinf(min_wartosc(w)));
    assert(min_wartosc(w) < 0.0);
    assert(max_wartosc(w) > 0.0);
    assert(isinf(max_wartosc(w)));
    assert(!in_wartosc(w, 0.0));
    assert(!in_wartosc(w, -0.0));
    assert(in_wartosc(w, 1000000.0));
    assert(in_wartosc(w, -1000000.0));
    assert(in_wartosc(w, 101.0));
    assert(in_wartosc(w, -99.0));
    assert(in_wartosc(w, -99.1));
    assert(in_wartosc(w, 101.1));
    assert(!in_wartosc(w, 100.9999));
    assert(!in_wartosc(w, -98.95454));

    wartosc x = minus(w, wartosc_od_do(1.0, 3.0));   //R - [-100.0; 98.0]

    wartosc y = razy(w, x);
    //dbg(y);
    assert(isnan(sr_wartosc(y)));
    assert(isinf(min_wartosc(y)));
    assert(min_wartosc(y) < 0.0);
    assert(max_wartosc(y) > 0.0);
    assert(isinf(max_wartosc(y)));
    assert(!in_wartosc(y, 0.0));
    assert(!in_wartosc(y, -0.0));
    assert(in_wartosc(y, 1000000.0));
    assert(in_wartosc(y, -1000000.0));
    assert(in_wartosc(y, 9898.0));
    assert(in_wartosc(y, -9702.0));
    assert(in_wartosc(y, -9702.1));
    assert(in_wartosc(y, 9898.00001));
    assert(!in_wartosc(y, 9897.999999));
    assert(!in_wartosc(y, -9701.98959));
    //y = -9702.000000000000000 9898.000000000000000;
    wartosc z = podzielic(wartosc_dokladna(1.0), podzielic(x, y));
    //dbg(podzielic(x, y)); //[-inf; inf]
    //dbg(odwrotnosc(y));
    //dbg(odwrotnosc(podzielic(x, y)));
    //dbg(z);
    assert(isnan(sr_wartosc(z)));
    assert(isinf(min_wartosc(z)));
    assert(min_wartosc(z) < 0.0);
    assert(max_wartosc(z) > 0.0);
    assert(isinf(max_wartosc(z)));
    assert(in_wartosc(z, 0.0));
    assert(in_wartosc(z, -0.0));
    assert(in_wartosc(z, 1.0));
    assert(in_wartosc(z, -1.0));
    assert(in_wartosc(z, 10.0));
    assert(in_wartosc(z, -10.0));
    assert(in_wartosc(z, 100.0));
    assert(in_wartosc(z, -100.0));
    assert(in_wartosc(z, 1000000.0));
    assert(in_wartosc(z, -1000000.0));
    //dbg(s);
    //dbg(y);
    //dbg(razy(wartosc_dokladna(0.5), s));
    //dbg(razy(razy(wartosc_dokladna(0.5), s),y));
    wartosc aa = razy(razy(wartosc_dokladna(0.5), s), y);
    aa = plus(aa, wartosc_dokladna(4851.0));
    //dbg(aa);
    //dbg(wartosc_dokladna(-2.0/9800.0));
    aa = razy(aa, wartosc_dokladna(-2.0/9800.0));
    //dbg(aa);
    //R - [-2.0; 0.0]
    //dbg(aa);
    wartosc ab = podzielic(wartosc_dokladna(1.0), aa);
    //[-0.5; inf]

    assert(equal(min_wartosc(ab), -0.5));
    assert(isinf(max_wartosc(ab)));
    assert(max_wartosc(ab) > 0.0);
    assert(in_wartosc(ab, -0.5));
    assert(in_wartosc(ab, -0.4999999));
    assert(!in_wartosc(ab, -0.500000013));
    assert(in_wartosc(ab, 0.0));
    assert(in_wartosc(ab, -0.0));
    assert(in_wartosc(ab, 2318992.022));

    wartosc ac = plus(ab, wartosc_dokladna(0.5));
    //[0.0; inf]

    assert(equal(min_wartosc(ac), 0.0));
    assert(isinf(max_wartosc(ac)));
    assert(max_wartosc(ac) > 0.0);
    assert(isinf(sr_wartosc(ac)));
    assert(sr_wartosc(ac) > 0.0);
    assert(!in_wartosc(ac, -0.0001));
    assert(!in_wartosc(ac, -123321.69));
    assert(in_wartosc(ac, 0.000));
    assert(in_wartosc(ac, 0.000001));
    assert(in_wartosc(ac, 1000000.312));

    wartosc ad = razy(ac, ac);
    //[0.0; inf]
    
    assert(equal(min_wartosc(ad), 0.0));
    assert(isinf(max_wartosc(ad)));
    assert(max_wartosc(ad) > 0.0);
    assert(isinf(sr_wartosc(ad)));
    assert(sr_wartosc(ad) > 0.0);
    assert(!in_wartosc(ad, -0.0001));
    assert(!in_wartosc(ad, -123321.69));
    assert(in_wartosc(ad, 0.000));
    assert(in_wartosc(ad, 0.000001));
    assert(in_wartosc(ad, 1000000.312));

    wartosc ae  = podzielic(ac, ad);
    //[0.0; inf]
    
    assert(equal(min_wartosc(ae), 0.0));
    assert(isinf(max_wartosc(ae)));
    assert(max_wartosc(ae) > 0.0);
    assert(isinf(sr_wartosc(ae)));
    assert(sr_wartosc(ae) > 0.0);
    assert(!in_wartosc(ae, -0.0001));
    assert(!in_wartosc(ae, -123321.69));
    assert(in_wartosc(ae, 0.000));
    assert(in_wartosc(ae, 0.000001));
    assert(in_wartosc(ae, 1000000.312));

    wartosc af = minus(ae, ae);
    //[-inf; inf]

    assert(isnan(sr_wartosc(af)));
    assert(isinf(min_wartosc(af)));
    assert(min_wartosc(af) < 0.0);
    assert(max_wartosc(af) > 0.0);
    assert(isinf(max_wartosc(af)));
    assert(in_wartosc(af, 0.0));
    assert(in_wartosc(af, -0.0));
    assert(in_wartosc(af, 1.0));
    assert(in_wartosc(af, -1.0));
    assert(in_wartosc(af, 10.0));
    assert(in_wartosc(af, -10.0));
    assert(in_wartosc(af, 100.0));
    assert(in_wartosc(af, -100.0));
    assert(in_wartosc(af, 1000000.0));
    assert(in_wartosc(af, -1000000.0));

    wartosc ag = plus(ab, wartosc_dokladna(1.0));   //[0.5; inf]
    ag = razy(ag,  wartosc_od_do(-1.0, 0.0));   //[-inf; 0.0]

    assert(equal(max_wartosc(ag), 0.0));
    assert(isinf(min_wartosc(ag)));
    assert(min_wartosc(ag) < 0.0);
    assert(isinf(sr_wartosc(ag)));
    assert(sr_wartosc(ag) < 0.0);
    assert(in_wartosc(ag, -0.0001));
    assert(in_wartosc(ag, -123321.69));
    assert(in_wartosc(ag, 0.000));
    assert(!in_wartosc(ag, 0.000001));
    assert(!in_wartosc(ag, 1000000.312));

    wartosc ah = razy(wartosc_od_do(-12332.213, 326666.9931), q);

    assert(isnan(min_wartosc(ah)));
    assert(isnan(max_wartosc(ah)));
    assert(!in_wartosc(ah, 0.0));
    
    wartosc ai = podzielic(wartosc_od_do(-12332.213, 326666.9931), q);

    assert(isnan(min_wartosc(ai)));
    assert(isnan(max_wartosc(ai)));
    assert(!in_wartosc(ai, 0.0));

    wartosc aj = minus(wartosc_od_do(-12332.213, 326666.9931), q);

    assert(isnan(min_wartosc(aj)));
    assert(isnan(max_wartosc(aj)));
    assert(!in_wartosc(aj, 0.0));
    
    wartosc ak = plus(wartosc_od_do(-12332.213, 326666.9931), q);

    assert(isnan(min_wartosc(ak)));
    assert(isnan(max_wartosc(ak)));
    assert(!in_wartosc(ak, 0.0));

    wartosc al = razy(aa, q);

    assert(isnan(min_wartosc(al)));
    assert(isnan(max_wartosc(al)));
    assert(!in_wartosc(al, 0.0));
    
    wartosc am = podzielic(aa, q);

    assert(isnan(min_wartosc(am)));
    assert(isnan(max_wartosc(am)));
    assert(!in_wartosc(am, 0.0));

    wartosc an = minus(aa, q);

    assert(isnan(min_wartosc(an)));
    assert(isnan(max_wartosc(an)));
    assert(!in_wartosc(an, 0.0));
    
    wartosc ao = plus(aa, q);

    assert(isnan(min_wartosc(ao)));
    assert(isnan(max_wartosc(ao)));
    assert(!in_wartosc(ao, 0.0));

/*
    wartosc ap = plus(podzielic(wartosc_dokladna(1.0), wartosc_od_do(-1.0, 1.0)), wartosc_dokladna(3.0));
    // R - [2.0; 4.0]

    wartosc aq = plus(razy(ap, wartosc_dokladna(-1.0))
*/
    printf("CZAS ROBIC GAL");
}
