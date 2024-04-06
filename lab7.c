#include <stdio.h>
#include <math.h>

enum Months {
    January, February, March, April, May, June,
    July, August, September, October, November, December
};

struct Square {
    double xy[4][2];
};

union {
    struct {
        int a;
    } num;
    struct {
        unsigned ready: 1;
        unsigned low_toner: 1;
        unsigned damaged_drum: 1;
        unsigned no_paper: 1;
    } laser_printer;
} printers;

int main() {
    enum Months month;
    month = July;
    struct Square square = {0, 0, 2, 0, 0, 2, 2, 2};
    printf("%d\n", month);
    printf("%f\n", pow(square.xy[0][0] - square.xy[1][0], 2) + pow(square.xy[0][1] - square.xy[1][1], 2));
    scanf("%x", &printers.num.a);
    printf("Ready - ");
    printers.laser_printer.ready ? printf("Yes\n") : printf("No\n");
    printf("Low toner - ");
    printers.laser_printer.low_toner ? printf("Yes\n") : printf("No\n");
    printf ("Damaged drum - ");
    printers.laser_printer.damaged_drum ? printf("Yes\n") : printf("No\n");
    printf ("No paper - ");
    printers.laser_printer.no_paper ? printf("Yes\n") : printf("No\n");
}