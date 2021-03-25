#include <libgeometry/functions.h>

int wkt_check(char* figure, int figure_length)
{
    int i, n;
    char example_circle[] = "circle(x y, r)";
 
    for (i = 0; (figure[i] != '(') && (i < figure_length); ++i) {
        n = i;
    }
    if (n == 5) {
        for (i = 0; i < n; ++i) {
            if (tolower(figure[i]) != example_circle[i]) {
                printf("Error at column %d: expected 'circle'\n", i);
                exit(EXIT_FAILURE);
            } else {
                figure[i] = tolower(figure[i]);
                continue;
            }
        }
        return 1;
    }
    // else if (n == 6)
    // polygon check
    //else if (n == 7)
    // triangle check
    else {
        printf("Error at column %d: expected 'circle'\n", n + 1);
        exit(EXIT_FAILURE);
    }
    return 0;
}

Circle circle_wkt_check(char* circle_figure, int circle_length)
{
    Circle circle_tokens;
    int i, tmp1, tmp2, tmp3, tmp4;
    tmp1 = tmp2 = tmp3 = tmp4 = 0;

    for (i = 0; i < circle_length; ++i) {
        if (circle_figure[i] == '(') {
            circle_tokens.open_bracket = i;
            tmp1++;
        }
        if ((circle_figure[i] == ' ') && (isdigit(circle_figure[i - 1]) != 0)) {
            circle_tokens.space = i;
            tmp2++;
        }
        if (circle_figure[i] == ',') {
            circle_tokens.comma = i;
            tmp3++;
        }
        if (circle_figure[i] == ')') {
            circle_tokens.close_bracket = i;
            tmp4++;
        }
    }
    int cntrlcount = control_count(NORMVALUE, tmp1)
            + control_count(NORMVALUE, tmp2) + control_count(NORMVALUE, tmp3)
            + control_count(NORMVALUE, tmp4);
    if (cntrlcount != 4) {
        printf("Error: unexpected token\n");
        exit(EXIT_FAILURE);
    } else {
        if (circle_figure[circle_tokens.close_bracket + 1] != '\0') {
            printf("Error at column %d: unexpected token\n",
                     circle_tokens.close_bracket + 1);
            exit(EXIT_FAILURE);
        }
        int checker = point_check(
                circle_figure, circle_tokens.open_bracket, circle_tokens.space);
        if (checker != 0) {
            int j = 0;
            char coordX[circle_tokens.space - circle_tokens.open_bracket];
            for (i = circle_tokens.open_bracket + 1; i < circle_tokens.space;
                 ++i) {
                coordX[j] = circle_figure[i];
                j++;
            }
            circle_tokens.x = atoi(coordX);

            checker = point_check(
                    circle_figure, circle_tokens.space, circle_tokens.comma);
            if (checker != 0) {
                j = 0;
                char coordY[circle_tokens.comma - circle_tokens.space];
                for (i = circle_tokens.space; i < circle_tokens.comma; ++i) {
                    coordY[j] = circle_figure[i];
                    j++;
                }
                circle_tokens.y = atoi(coordY);

                checker = radius_check(
                        circle_figure,
                        circle_tokens.comma,
                        circle_tokens.close_bracket);
                if (checker != 0) {
                    j = 0;
                    char rad[circle_tokens.close_bracket - circle_tokens.comma];
                    for (i = circle_tokens.comma + 1;
                         i < circle_tokens.close_bracket;
                         ++i) {
                        rad[j] = circle_figure[i];
                        j++;
                    }
                    circle_tokens.r = atof(rad);
                }
            }
        }
    }
    return circle_tokens;
}

int control_count(int norm, int get_count)
{
    if (norm == get_count) {
        return 1;
    } else {
        return 0;
    }
}

int point_check(char* figure, int indx1, int indx2)
{
    int i;
    int checker = 0;
    for (i = indx1 + 1; i < indx2; ++i) {
        if (isdigit(figure[i]) != 0) {
            checker = 1;
        } else if (
                (figure[i] == ' ')
                || (((figure[i] == '+') || (figure[i] == '-'))
                    && (isdigit(figure[i + 1]) != 0))) {
            continue;
        } else {
            printf("Error at column %d: expected '<int>'\n", i);
            exit(EXIT_FAILURE);
        }
    }
    return checker;
}

int radius_check(char* figure, int indx1, int indx2)
{
    int i;
    int checker = 0;
    for (i = indx1 + 1; i < indx2; ++i) {
        if (isdigit(figure[i]) != 0) {
            checker = 1;
        } else if (
                (figure[i] == ' ')
                || (((figure[i] == '+') || (figure[i] == '.'))
                    && (isdigit(figure[i + 1]) != 0)
                    && (isdigit(figure[i - 1]) != 0))) {
            continue;
        } else {
            printf("Error at column %d: expected positive '<double>'\n", i);
            exit(EXIT_FAILURE);
        }
    }
    return checker;
}

Calculations circle_compute(double radius)
{
    Calculations result;
    result.perimeter = 2 * M_PI * radius;
    result.area = M_PI * pow(radius, 2);

    return result;
}