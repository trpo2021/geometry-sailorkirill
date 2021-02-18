#include <stdio.h>
#include <string.h>
#include <math.h>
#define SIZE 21

struct point {
    int x;
    int y;
};

struct circle {
    struct point cpt;
    float radius;
};

int main()
{
    short i, n;
    struct circle circ;
    char object0[SIZE];
    char object1[SIZE] = "circle";
    float P, S;

    printf("Enter the number of figures that you want to work with: ");
    scanf("%hd", &n);
    printf("Enter the type of the figure: ");
    //scanf("%[^\n]", object0);
    //printf("%s\n", object0);

    for (i = 0; i < n; i++) {
        fgets(object0, SIZE - 1, stdin);
        if (strcmp(object0, object1) == 0) {
            printf("Enter coordinates of the central point and radius: ");
            scanf("%d %d %f", &circ.cpt.x, &circ.cpt.y, &circ.radius);
            if (circ.radius < 0) {
                printf("Radius must be non-negative!");
                break;
            }
            P = 2 * 3.14 * circ.radius;
            S = 3.14 * pow(circ.radius, 2);
            printf("%d %s(%d %d, %f)\n perimeter = %f\n area = %f\n", n, object1, circ.cpt.x, circ.cpt.y, circ.radius, P, S);
        }
        else
            printf("Error\n");
    }
    return 0;
}