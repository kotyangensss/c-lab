#include <stdio.h>
#include <math.h>

int main() {
    float a, z1 ,z2;
    scanf("%f", &a);
    z1 = cos(a)+sin(a)+cos(3*a)+sin(3*a);
    z2 = 2*sqrt(2)*cos(a)*sin(M_PI/4+2*a);
    printf("%f\t%f\n", z1, z2);
}