#include <stdio.h>
int main(void)
{
    double x_coord = 0;
    double y_coord = 0;

    if(scanf("%lf %lf", &x_coord, &y_coord) == 0) {
        return 1;
    }
                    
    printf("%d\n", x_coord >= 1 && x_coord <= 7 && y_coord <= 5 && y_coord >= 2 && y_coord <= 10 - x_coord);

    return 0;
}
