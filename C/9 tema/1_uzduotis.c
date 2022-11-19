#include <stdio.h>
#include <math.h>

typedef struct Point {
    double x, y;
} Point;

void printPoint(Point p)
{
    printf("x = %f y = %f\n", p.x, p.y);
}

Point createPoint(double x, double y)
{
    return (Point){x, y};
}

double getDistance(Point a, Point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main()
{
    getDistance(createPoint(2.0, -3.0), createPoint(-4.0, 5.0));

    return 0;
}
