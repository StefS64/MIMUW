// Franciszek Witt (Edited by Marcin Szopa)
#include "ary.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

void print_przedzial(wartosc w) {
  if(w.czy_anty) {
    printf("[-inf, %f] U [%f, inf]\n", w.x, w.y);
  } else {
    printf("[%f, %f]\n", w.x, w.y);
  }
}

//const double eps = 1e-12;
bool equal(double x, double y)
{
    return fabs(x - y) < 1e-12;
}

void testy_kuby()
{
    wartosc a = wartosc_dokladnosc(0.0, 100); //[0; 0]
    assert(in_wartosc(a, -0.0));

    wartosc b = wartosc_od_do(-2, -0.01); //[-2.0; -0.01]
    wartosc c = podzielic(b, a);          // zb pusty
    assert(isnan(max_wartosc(c)));
    assert(isnan(min_wartosc(c)));
    assert(isnan(sr_wartosc(c)));

    wartosc d = podzielic(b, minus(a, wartosc_od_do(-0.01, 0.01))); //[-inf; -1] U [1, inf]
    assert(isinf(min_wartosc(d)));
    assert(isinf(max_wartosc(d)));
    assert(in_wartosc(d, -1.0));
    assert(in_wartosc(d, 1.0));
    assert(!in_wartosc(d, 0.99));
    assert(isnan(sr_wartosc(d)));

    wartosc e = razy(d, wartosc_dokladna(3));                                 //[-inf; -3.0] U [3.0, inf]
    wartosc f = podzielic(wartosc_od_do(1, 2), plus(e, wartosc_dokladna(1))); //[-1.0; 0.5]
    assert(equal(min_wartosc(f), -1.0));
    assert(equal(max_wartosc(f), 0.5));
    assert(in_wartosc(f, 0.0));
    assert(!in_wartosc(f, -1.1));
    assert(!in_wartosc(f, 0.6));
    assert(equal(sr_wartosc(f), -0.25));

    wartosc g = podzielic(wartosc_od_do(1, 2), plus(e, wartosc_dokladna(3))); //[-inf; 0.3333]
    assert(isinf(min_wartosc(g)));
    assert(equal(max_wartosc(g), 1.0 / 3.0));
    assert(isinf(sr_wartosc(g)));
    assert(in_wartosc(g, -1000.0));
    assert(in_wartosc(g, 0.0));
    assert(!in_wartosc(g, 0.4));
    wartosc ep4 = plus(e, wartosc_dokladna(4));
    wartosc h = podzielic(wartosc_od_do(1, 2), ep4); //[-inf; 2.0/7.0] U [1.0, inf]
    assert(isinf(min_wartosc(h)));
    assert(isinf(max_wartosc(h)));
    assert(isnan(sr_wartosc(h)));
    assert(in_wartosc(h, 2.0 / 7.0));
    assert(in_wartosc(h, 1));
    assert(in_wartosc(h, 0.0));
    assert(in_wartosc(h, 0.1));
    assert(!in_wartosc(h, 0.5));
    assert(!in_wartosc(h, 0.375));

    wartosc i = razy(h, wartosc_od_do(-2, -1)); // [-inf -1] U [-4.0/7.0, inf]
    assert(isinf(min_wartosc(h)));
    assert(isinf(max_wartosc(h)));
    assert(isnan(sr_wartosc(h)));
    assert(in_wartosc(i, -1));
    assert(in_wartosc(i, -20));
    assert(in_wartosc(i, -4.0 / 7.0));
    assert(in_wartosc(i, 0.5));
    assert(in_wartosc(i, 0.0));
    assert(!in_wartosc(i, -0.9));
    assert(!in_wartosc(i, -0.6));

    wartosc j = minus(i, h); //[-inf, inf]
    assert(isinf(min_wartosc(h)));
    assert(isinf(max_wartosc(h)));
    assert(isnan(sr_wartosc(h)));
    assert(in_wartosc(j, -1000));
    assert(in_wartosc(j, 0.0));
    assert(in_wartosc(j, 43223));

    wartosc k = razy(j, wartosc_dokladna(0.0)); //[0.0, 0.0]
    assert(equal(min_wartosc(k), 0));
    assert(equal(max_wartosc(k), 0.0));
    assert(equal(sr_wartosc(k), 0.0));
    assert(in_wartosc(k, -0.0));
    assert(in_wartosc(k, 0.0));
    assert(!in_wartosc(k, 1.0));

    wartosc l = podzielic(j, k); // zbior pusty
    assert(isnan(max_wartosc(l)));
    assert(isnan(min_wartosc(l)));
    assert(isnan(sr_wartosc(l)));
    assert(!in_wartosc(l, 2.0));

    wartosc m = minus(g, wartosc_dokladna(1.0));
    wartosc n = razy(m, m);
    wartosc o = podzielic(m, n); //[-inf; 0]
    assert(equal(max_wartosc(o), 0.0));
    assert(isinf(min_wartosc(o)));
    assert(isinf(sr_wartosc(o)));
    assert(in_wartosc(o, 0.0));
    assert(!in_wartosc(o, 0.2));
    assert(in_wartosc(o, -10.0));

    wartosc p = razy(i, i);
    assert(isinf(min_wartosc(h)));
    assert(isinf(max_wartosc(h)));
    assert(isnan(sr_wartosc(h)));
    assert(in_wartosc(p, 0.5));
    assert(in_wartosc(p, 0.5));

    wartosc q = plus(d, wartosc_dokladnosc(0.1, 10)); //[-inf; -0.89] U [1.09; inf]
    wartosc r = razy(q, q);                           //[-inf; -0.970100] U [0.792100; inf]
    assert(isinf(min_wartosc(h)));
    assert(isinf(max_wartosc(h)));
    assert(isnan(sr_wartosc(h)));
    assert(in_wartosc(r, -0.9701));
    assert(in_wartosc(r, 0.7921));
    assert(in_wartosc(r, -1.0));
    assert(!in_wartosc(r, 0.78));
    assert(!in_wartosc(r, 0.0));
}

int main()
{
    wartosc a = wartosc_dokladna(0.0);
    wartosc b = wartosc_od_do(-100.0, 200.0);
    wartosc c = razy(a, b); //[0; 0]

    assert(in_wartosc(c, 0.0));
    assert(equal(min_wartosc(c), 0.0));
    assert(equal(max_wartosc(c), 0.0));
    assert(equal(sr_wartosc(c), 0.0));
    assert(!in_wartosc(c, -0.0001));
    assert(!in_wartosc(c, -0.0001));

    wartosc d = razy(b, wartosc_dokladna(-1.0)); //[-200; 100]

    assert(in_wartosc(d, -200.0));
    assert(in_wartosc(d, 100.0));
    assert(!in_wartosc(d, 200.0));

    wartosc e = podzielic(wartosc_dokladna(1), d); // R - [-0.005; 0.01]

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

    wartosc g = podzielic(wartosc_dokladna(1.0), e);   //[-200; 100]
    wartosc h = plus(wartosc_od_do(-1000, -500), g);   //[-1200; -400]
    wartosc i = podzielic(wartosc_od_do(1.0, 2.0), h); //[-0.005; -0.000833333]
    wartosc j = plus(wartosc_od_do(0.005, 0.006), i);  //[0.0; 0.0051666]
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

    wartosc m = wartosc_dokladnosc(1.0, 100);  //[0.0; 2.0]
    wartosc n = wartosc_dokladnosc(-1.0, 100); //[-2.0; 0.0], bardzo fajny edge case

    assert(in_wartosc(n, -2.0));
    assert(in_wartosc(n, 0.0));
    assert(!in_wartosc(n, 0.000001));
    assert(!in_wartosc(n, 2.0));

    wartosc o = minus(m, n); //[0.0; 4.0]

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
    // R - [-inf; inf]

    assert(!in_wartosc(q, 0.0));
    assert(!in_wartosc(q, 1.0));
    assert(!in_wartosc(q, -1.0));

    wartosc r = plus(q, k);
    // R - [-inf; inf]

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

    wartosc w = plus(podzielic(wartosc_dokladna(1.0), wartosc_od_do(-0.01, 0.01)), wartosc_dokladna(1.0)); // R - [-99.0; 101.0]

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

    wartosc x = minus(w, wartosc_od_do(1.0, 3.0)); // R - [-100.0; 98.0]

    wartosc y = razy(w, x);

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

    wartosc mz = podzielic(x, y);
    wartosc z = podzielic(wartosc_dokladna(1.0), mz); //[-inf; inf]
    print_przedzial(z);
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

    // MOJE
    wartosc az = razy(wartosc_dokladna(0.5), s);
    wartosc aa = razy(az, y); // (-inf, -4851> U <4949, inf)
    aa = plus(aa, wartosc_dokladna(4851.0));
    aa = razy(aa, wartosc_dokladna(-2.0 / 9800.0));
    // R - [-2.0; 0.0]

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

    wartosc ae = podzielic(ac, ad);
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

    wartosc ag = plus(ab, wartosc_dokladna(1.0)); //[0.5; inf]
    ag = razy(ag, wartosc_od_do(-1.0, 0.0));      //[-inf; 0.0]

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

    // <> / <>
    wartosc ax = podzielic(wartosc_od_do(-3, 5), wartosc_od_do(-1, 1)); // R
    assert(isnan(sr_wartosc(ax)));
    assert(isinf(min_wartosc(ax)));
    assert(min_wartosc(ax) < 0.0);
    assert(max_wartosc(ax) > 0.0);
    assert(isinf(max_wartosc(ax)));
    assert(in_wartosc(ax, 0.0));
    assert(in_wartosc(ax, -0.0));
    assert(in_wartosc(ax, 1.0));
    assert(in_wartosc(ax, -1.0));
    assert(in_wartosc(ax, 10.0));
    assert(in_wartosc(ax, -10.0));
    assert(in_wartosc(ax, 100.0));
    assert(in_wartosc(ax, -100.0));
    assert(in_wartosc(ax, 1000000.0));
    assert(in_wartosc(ax, -1000000.0));

    wartosc ap = plus(podzielic(wartosc_od_do(-5, -3), wartosc_od_do(-1, 1)), wartosc_od_do(0, 2)); // R - (-1,3)
    //print_przedzial(podzielic(wartosc_od_do(-5, -3), wartosc_od_do(-1, 1)));
    //print_przedzial(ap);
    assert(isnan(sr_wartosc(ap)));
    assert(isinf(min_wartosc(ap)));
    assert(min_wartosc(ap) < 0.0);
    assert(max_wartosc(ap) > 0.0);
    assert(isinf(max_wartosc(ap)));
    assert(!in_wartosc(ap, 0.0));
    assert(!in_wartosc(ap, -0.0));
    assert(in_wartosc(ap, -1));
    assert(!in_wartosc(ap, -0.99999999));
    assert(in_wartosc(ap, 3));
    assert(!in_wartosc(ap, 2.999999999));

    // R - ()  /  <>

    wartosc ar = podzielic(ap, wartosc_od_do(-2, 3)); // R - (-1/3, 0.5) zle
    assert(isnan(sr_wartosc(ar)));
    assert(isinf(min_wartosc(ar)));
    assert(min_wartosc(ar) < 0.0);
    assert(max_wartosc(ar) > 0.0);
    assert(isinf(max_wartosc(ar)));
    assert(!in_wartosc(ar, 0.0));
    assert(!in_wartosc(ar, -0.0));
    assert(in_wartosc(ar, 0.5));
    assert(!in_wartosc(ar, 0.49999999));
    assert(!in_wartosc(ar, -0.33333332));
    assert(in_wartosc(ar, -0.33333334));

    // R - () + <> = R (edge-case)
    wartosc as = plus(ap, wartosc_od_do(-1, 3)); // R
    assert(isnan(sr_wartosc(as)));
    assert(isinf(min_wartosc(as)));
    assert(min_wartosc(as) < 0.0);
    assert(max_wartosc(as) > 0.0);
    assert(isinf(max_wartosc(as)));
    assert(in_wartosc(as, 0.0));
    assert(in_wartosc(as, -0.0));
    assert(in_wartosc(as, 1.0));
    assert(in_wartosc(as, -1.0));
    assert(in_wartosc(as, 10.0));
    assert(in_wartosc(as, -10.0));
    assert(in_wartosc(as, 100.0));
    assert(in_wartosc(as, -100.0));
    assert(in_wartosc(as, 1000000.0));
    assert(in_wartosc(as, -1000000.0));

    // R - () + R - () = R
    wartosc at = plus(ap, ar); // R
    assert(isnan(sr_wartosc(at)));
    assert(isinf(min_wartosc(at)));
    assert(min_wartosc(at) < 0.0);
    assert(max_wartosc(at) > 0.0);
    assert(isinf(max_wartosc(at)));
    assert(in_wartosc(at, 0.0));
    assert(in_wartosc(at, -0.0));
    assert(in_wartosc(at, 1.0));
    assert(in_wartosc(at, -1.0));
    assert(in_wartosc(at, 10.0));
    assert(in_wartosc(at, -10.0));
    assert(in_wartosc(at, 100.0));
    assert(in_wartosc(at, -100.0));
    assert(in_wartosc(at, 1000000.0));
    assert(in_wartosc(at, -1000000.0));

    // R - () - R - () = R
    wartosc au = minus(ap, ar); // R
    assert(isnan(sr_wartosc(au)));
    assert(isinf(min_wartosc(au)));
    assert(min_wartosc(au) < 0.0);
    assert(max_wartosc(au) > 0.0);
    assert(isinf(max_wartosc(au)));
    assert(in_wartosc(au, 0.0));
    assert(in_wartosc(au, -0.0));
    assert(in_wartosc(au, 1.0));
    assert(in_wartosc(au, -1.0));
    assert(in_wartosc(au, 10.0));
    assert(in_wartosc(au, -10.0));
    assert(in_wartosc(au, 100.0));
    assert(in_wartosc(au, -100.0));
    assert(in_wartosc(au, 1000000.0));
    assert(in_wartosc(au, -1000000.0));

    wartosc aw = minus(ap, wartosc_od_do(-1, 3)); // R
    assert(isnan(sr_wartosc(aw)));
    assert(isinf(min_wartosc(aw)));
    assert(min_wartosc(aw) < 0.0);
    assert(max_wartosc(aw) > 0.0);
    assert(isinf(max_wartosc(aw)));
    assert(in_wartosc(aw, 0.0));
    assert(in_wartosc(aw, -0.0));
    assert(in_wartosc(aw, 1.0));
    assert(in_wartosc(aw, -1.0));
    assert(in_wartosc(aw, 10.0));
    assert(in_wartosc(aw, -10.0));
    assert(in_wartosc(aw, 100.0));
    assert(in_wartosc(aw, -100.0));
    assert(in_wartosc(aw, 1000000.0));
    assert(in_wartosc(aw, -1000000.0));

    // {0} / <>

    wartosc ay = podzielic(wartosc_dokladna(0), wartosc_od_do(-50, 70)); // 0
    assert(in_wartosc(ay, 0));
    assert(equal(max_wartosc(ay), 0));
    assert(equal(min_wartosc(ay), 0));
    assert(equal(sr_wartosc(ay), 0));
    assert(!in_wartosc(ay, 0.0000001));
    assert(!in_wartosc(ay, 100));
    assert(!in_wartosc(ay, -2136));
    assert(!in_wartosc(ay, -0.004));

    // {0} / R - ()

    wartosc ba = podzielic(wartosc_dokladna(0), ar); // 0
    assert(in_wartosc(ba, 0));
    assert(equal(max_wartosc(ba), 0));
    assert(equal(min_wartosc(ba), 0));
    assert(equal(sr_wartosc(ba), 0));
    assert(!in_wartosc(ba, 0.0000001));
    assert(!in_wartosc(ba, 100));
    assert(!in_wartosc(ba, -2136));
    assert(!in_wartosc(ba, -0.004));

    // {} / R - ()
    wartosc ca = podzielic(wartosc_dokladna(4), ar); // <-12,8>
    assert(equal(max_wartosc(ca), 8));
    assert(in_wartosc(ca, 0.0));
    assert(in_wartosc(ca, -0.0));
    assert(in_wartosc(ca, 1.0));
    assert(in_wartosc(ca, -1.0));
    assert(in_wartosc(ca, 7.0));
    assert(in_wartosc(ca, -10.0));
    assert(in_wartosc(ca, 8));
    assert(in_wartosc(ca, 7.9999999999));
    assert(!in_wartosc(ca, 8.0000000001));
    assert(in_wartosc(ca, -12));
    assert(!in_wartosc(ca, -12.0000001));

    // <> / R - (0, positive)
    wartosc da = podzielic(wartosc_od_do(1.5, 9), razy(wartosc_dokladna(-1), aa)); // (-inf, 9/2>
    //print_przedzial(da);
    assert(isinf(sr_wartosc(da)));
    assert(isinf(min_wartosc(da)));
    assert(min_wartosc(da) < 0.0);
    assert(max_wartosc(da) > 0.0);
    assert(!isinf(max_wartosc(da)));
    assert(in_wartosc(da, 0.0));
    assert(in_wartosc(da, -0.0));
    assert(in_wartosc(da, 1.0));
    assert(in_wartosc(da, -1.0));
    assert(!in_wartosc(da, 10.0));
    //assert(!in_wartosc(da, 4.500000000001));
    assert(in_wartosc(da, 9 / 2));

    wartosc ea = podzielic(wartosc_od_do(-5, 3), wartosc_od_do(-30, 0)); // R
    assert(isnan(sr_wartosc(ea)));
    assert(isinf(min_wartosc(ea)));
    assert(min_wartosc(ea) < 0.0);
    assert(max_wartosc(ea) > 0.0);
    assert(isinf(max_wartosc(ea)));
    assert(in_wartosc(ea, 0.0));
    assert(in_wartosc(ea, -0.0));
    assert(in_wartosc(ea, 1.0));
    assert(in_wartosc(ea, -1.0));
    assert(in_wartosc(ea, 10.0));
    assert(in_wartosc(ea, -10.0));
    assert(in_wartosc(ea, 100.0));
    assert(in_wartosc(ea, -100.0));
    assert(in_wartosc(ea, 1000000.0));
    assert(in_wartosc(ea, -1000000.0));

    wartosc eb = podzielic(wartosc_od_do(-5, 3), wartosc_od_do(0, 5)); // R
    assert(isnan(sr_wartosc(eb)));
    assert(isinf(min_wartosc(eb)));
    assert(min_wartosc(eb) < 0.0);
    assert(max_wartosc(eb) > 0.0);
    assert(isinf(max_wartosc(eb)));
    assert(in_wartosc(eb, 0.0));
    assert(in_wartosc(eb, -0.0));
    assert(in_wartosc(eb, 1.0));
    assert(in_wartosc(eb, -1.0));
    assert(in_wartosc(eb, 10.0));
    assert(in_wartosc(eb, -10.0));
    assert(in_wartosc(eb, 100.0));
    assert(in_wartosc(eb, -100.0));
    assert(in_wartosc(eb, 1000000.0));
    assert(in_wartosc(eb, -1000000.0));

    wartosc fa = razy(wartosc_dokladna(-1), da);
    assert(isinf(sr_wartosc(fa)));
    assert(isinf(max_wartosc(fa)));
    assert(min_wartosc(fa) < 0.0);
    assert(max_wartosc(fa) > 0.0);
    assert(!isinf(min_wartosc(fa)));
    assert(in_wartosc(fa, 0.0));
    assert(in_wartosc(fa, -0.0));
    assert(in_wartosc(fa, 1.0));
    assert(!in_wartosc(fa, -10.0));
    assert(!in_wartosc(fa, -4.500000001));
    assert(in_wartosc(fa, -(9 / 2)));

    wartosc fb = podzielic(wartosc_od_do(-4, -2), wartosc_od_do(-1, 1));
    fb = plus(fb, wartosc_od_do(0, 2));

    wartosc fc = podzielic(wartosc_od_do(-4, -2), wartosc_od_do(-1, 1)); // R - (-2,2)
    wartosc fd = razy(fb, fc);                                           // R
    assert(isnan(sr_wartosc(fd)));
    assert(isinf(min_wartosc(fd)));
    assert(min_wartosc(fd) < 0.0);
    assert(max_wartosc(fd) > 0.0);
    assert(isinf(max_wartosc(fd)));
    assert(in_wartosc(fd, 0.0));
    assert(in_wartosc(fd, -0.0));
    assert(in_wartosc(fd, 1.0));
    assert(in_wartosc(fd, -1.0));
    assert(in_wartosc(fd, 10.0));
    assert(in_wartosc(fd, -10.0));
    assert(in_wartosc(fd, 100.0));
    assert(in_wartosc(fd, -100.0));
    assert(in_wartosc(fd, 1000000.0));
    assert(in_wartosc(fd, -1000000.0));

    // INNE
    testy_kuby();
    printf("CZAS ZAKONCZYC TEN SYF");
    // R - ()   + {}
    // {} +   R - ()
    // R - ()   - {}
}
