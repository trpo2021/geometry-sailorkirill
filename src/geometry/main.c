#include <libgeometry/functions.h>

int main()
{
    char object[MAXSIZE];
    printf("Enter the type of the figure: ");
    scanf("%[^\n]s", object);
    int object_len = strlen(object);

    int figure_define = wkt_check(object, object_len);
    if (figure_define == 1) {
        Circle tokens;
        tokens = circle_wkt_check(object, object_len);

        Calculations result_calc;
        result_calc = circle_compute(tokens.r);

        printf("%s\n", object);
        printf("    perimeter = %lf\n", result_calc.perimeter);
        printf("    area = %lf\n", result_calc.area);
    }
    return 0;
}