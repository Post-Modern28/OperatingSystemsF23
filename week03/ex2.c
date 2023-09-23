#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct Point{
    double x;
    double y;
};

double distance(struct Point a, struct Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

double area(struct Point a, struct Point b, struct Point c) {
    double ab = distance(a, b);
    double bc = distance(b, c);
    double ca = distance(c, a);
    double p = (ab + bc + ca) / 2;
    return sqrt(p * (p - ab) * (p - bc) * (p - ca));
}

int main() {
    struct Point a = {2.5, 6};
    struct Point b = {1, 2.2};
    struct Point c = {10, 6};

    double ab = distance(a, b);
    printf("Distance between A and B: %.2f\n", ab);

    double abc_area = area(a, b, c);
    printf("Area of ABC: %.2f\n", abc_area);

    return 0;
}
