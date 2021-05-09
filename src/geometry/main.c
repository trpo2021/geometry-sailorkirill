#include <libgeometry/functions.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int number_of_figures = 0;
    char object[MAXSIZE];
    printf("Welcome to geometry app! To exit the application write 'exit' or "
           "just make a mistake when entering the figure.\n");
    while (1) {
        printf("Enter the type of the figure: ");
        fgets(object, MAXSIZE + 1, stdin);
        if (strcmp(object, "exit\n") == 0) {
            return 0;
        }
        int object_len = strlen(object);

        int figure_define[MAXSIZE];

        int x_coord[MAXSIZE];
        int y_coord[MAXSIZE];
        double radius[MAXSIZE];
        int x_coord_triangle[MAXSIZE][4];
        int y_coord_triangle[MAXSIZE][4];

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

            for (int i = 0; i < 4; ++i) {
                x_coord_triangle[number_of_figures][i] = tokens.x[i];
                y_coord_triangle[number_of_figures][i] = tokens.y[i];
            }
        }

        if (number_of_figures > 0) {
            for (int i = 1; number_of_figures - i >= 0; ++i) {
                if ((figure_define[number_of_figures] == 1)
                    && (figure_define[number_of_figures - i] == 1)) {
                    if (circ_intersects_circ(
                                x_coord[number_of_figures],
                                x_coord[number_of_figures - i],
                                y_coord[number_of_figures],
                                y_coord[number_of_figures - i],
                                radius[number_of_figures],
                                radius[number_of_figures - i])
                        == 1) {
                        printf("    intersects with a circle #%d\n",
                               number_of_figures - i + 1);
                    }
                } else if (
                        (figure_define[number_of_figures] == 2)
                        && (figure_define[number_of_figures - i] == 1)) {
                    if (triangle_intersects_circ(
                                x_coord_triangle[number_of_figures],
                                x_coord[number_of_figures - i],
                                y_coord_triangle[number_of_figures],
                                y_coord[number_of_figures - i],
                                radius[number_of_figures - i])
                        == 1) {
                        printf("    intersects with a circle #%d\n",
                               number_of_figures - i + 1);
                    }
                } else if (
                        (figure_define[number_of_figures] == 1)
                        && (figure_define[number_of_figures - i] == 2)) {
                    if (circ_intersects_triangle(
                                x_coord[number_of_figures],
                                x_coord_triangle[number_of_figures - i],
                                y_coord[number_of_figures],
                                y_coord_triangle[number_of_figures - i],
                                radius[number_of_figures])
                        == 1) {
                        printf("    intersects with a triangle #%d\n", 
                               number_of_figures - i + 1);
                    }
                }
            }
        }
        number_of_figures++;
    }
    return 0;
}