#include <stdio.h>
#include "./float4.h"

int main()
{
    float t[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    printf("%f\n", t[0]);
    float4 a = float4(1);
    float4 b = {5};
    float4 c = a * b + a;
    c += a;
    printf("%f %f %f %f\n", c.x(), c.y(), c.z(), c.w());
    return 0;
}