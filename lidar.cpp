#include <iostream>
#include "points.h"
#include "icp.h"

int main() {
    Tree t;
    Point pt, l, r, ll, lr, rl, rr;
    
    pt.x = -1;
    pt.y = 1;
    l.x = -6.5;
    l.y = -2;
    r.x = 3;
    r.y = 1.2;
    ll.x = -5;
    ll.y = 2;
    lr.x = -3.5;
    lr.y = -2.1;
    rl.x = 5;
    rl.y = -2;
    rr.x = 6.5;
    rr.y = 3;

    BinNode lln = { ll, nullptr, nullptr };
    BinNode lrn = { lr, nullptr, nullptr };
    BinNode ln = { l, &lln, &lrn };
    BinNode rln = { rl, nullptr, nullptr };
    BinNode rrn = { rr, nullptr, nullptr };
    BinNode rn = { r, &rln, &rrn };
    t = { pt, &ln, &rn };

    Point c = closest(t, { 0, -5 });
    printf("%fx %fy\n", c.x, c.y);
    return 0;
}