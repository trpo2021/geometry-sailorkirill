#include <libgeometry/functions.h>

int main()
{
    int number_of_figures = 0;
    char object[MAXSIZE];
    printf("Welcome to geometry app! To exit the application write 'exit' or just make a mistake when entering the figure.\n");
    while (1) {
        printf("Enter the type of the figure: ");
        //scanf("%[^\n]s", object);
        fgets(object, MAXSIZE + 1, stdin);
        if (strcmp(object, "exit\n") == 0) {
            return 0;
        }
        int object_len = strlen(object);

        int figure_define[MAXSIZE];

        int x_coord[MAXSIZE];
        int y_coord[MAXSIZE];
        double radius[MAXSIZE];

        figure_define[number_of_figures] = wkt_check(object, object_len);
        if (figure_define[number_of_figures] == 1) {
            Circle tokens;
            tokens = circle_wkt_check(object, object_len);

            Calculations result_calc;
            result_calc = circle_compute(tokens.r);

            printf("%d. %s\n", number_of_figures + 1, object);
            printf("    perimeter = %lf\n", result_calc.perimeter);
            printf("    area = %lf\n", result_calc.area);

            x_coord[number_of_figures] = tokens.x;
            y_coord[number_of_figures] = tokens.y;
            radius[number_of_figures] = tokens.r;
        }
        if (figure_define[number_of_figures] == 2) {
            Triangle tokens;
            tokens = triangle_wkt_check(object, object_len);

            Calculations result_calc;
            result_calc = triangle_compute(tokens);

            printf("%d. %s\n", number_of_figures + 1, object);
            printf("    perimeter = %lf\n", result_calc.perimeter);
            printf("    area = %lf\n", result_calc.area);
        }

        if (number_of_figures > 0) {
            for (int i = 1; number_of_figures - i >= 0; ++i) {
                if ((figure_define[number_of_figures] == 1) && (figure_define[number_of_figures - i] == 1)) {
                    double distance = sqrt(pow(x_coord[number_of_figures] - x_coord[number_of_figures - i], 2) + pow(y_coord[number_of_figures] - y_coord[number_of_figures - i], 2));
                    if ((radius[number_of_figures] + radius[number_of_figures - i] >= distance) && (distance + radius[number_of_figures - i] > radius[number_of_figures]) && (distance + radius[number_of_figures] > radius[number_of_figures - i])) {
                        printf("    intersects with a circle #%d\n", number_of_figures - i + 1);
                    }
                }
            }
        }
        number_of_figures++;
    }
    return 0;
}