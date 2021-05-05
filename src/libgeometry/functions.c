#include <libgeometry/errorout.h>
#include <libgeometry/functions.h>

int wkt_check(char* figure, int figure_length)
{
    int i, n;
    char example_circle[] = "circle(x y, r)";
    char example_triangle[] = "triangle((x1 y1, x2 y2, x3 y3, x4 y4))";
    for (i = 0; (figure[i] != '(') && (i < figure_length); ++i) {
        n = i;
    }
    if (n == 5) {
        for (i = 0; i < n; ++i) {
            if (tolower(figure[i]) != example_circle[i]) {
                CIRCLE_EXP;
                return -1;
            } else {
                figure[i] = tolower(figure[i]);
                continue;
            }
        }
        return 1;
    } else if (n == 7) {
        for (i = 0; i < n; ++i) {
            if (tolower(figure[i]) != example_triangle[i]) {
                TRIANGLE_EXP;
                return -1;
            } else {
                figure[i] = tolower(figure[i]);
                continue;
            }
        }
        return 2;
    }
    else {
        CIRC_OR_TRI_EXP;
        return -1;
    }
    return 0;
}

Circle circle_wkt_check(char* circle_figure, int circle_length)
{
    Circle circle_tokens;
    int i;
    int tmp[4] = {0};

    for (i = 0; i < circle_length; ++i) {
        if (circle_figure[i] == '(') {
            circle_tokens.open_bracket = i;
            tmp[0]++;
        }
        if ((circle_figure[i] == ' ') && (isdigit(circle_figure[i - 1]) != 0)) {
            circle_tokens.space = i;
            tmp[1]++;
        }
        if (circle_figure[i] == ',') {
            circle_tokens.comma = i;
            tmp[2]++;
        }
        if (circle_figure[i] == ')') {
            circle_tokens.close_bracket = i;
            tmp[3]++;
        }
    }
    int cntrlcount = 0;
    for (i = 0; i < 4; ++i) {
        cntrlcount += control_count(NORMVALUE, tmp[i]);
    }
    if (cntrlcount != 4) {
        UNEXPECTED_TOKEN;
        exit(EXIT_FAILURE);
    } else {
        if (circle_figure[circle_tokens.close_bracket + 2] != '\0') {
            UNEXPECTED_TOKEN;
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

Triangle triangle_wkt_check(char* triangle_figure, int triangle_length)
{
    Triangle triangle_tokens;
    int i;
    int tmp[4] = {0};

    for (i = 0; i < triangle_length; ++i) {
        if (triangle_figure[i] == '(') {
            tmp[0]++;
            triangle_tokens.open_bracket[tmp[0] - 1] = i;
        }
        if (triangle_figure[i] == ')') {
            tmp[1]++;
            triangle_tokens.close_bracket[tmp[1] - 1] = i;
        }
        if (triangle_figure[i] == ',') {
            tmp[2]++;
            triangle_tokens.comma[tmp[2] - 1] = i;
        }
        if ((triangle_figure[i] == ' ') && (isdigit(triangle_figure[i - 1]) != 0)) {
            tmp[3]++;
            triangle_tokens.space[tmp[3] - 1] = i;
        }
    }
    int cntrlcount = 0;
    for (i = 0; i < 4; ++i) {
        if (i == 0) {
            cntrlcount += control_count(NORMVALUE + 1, tmp[i]);
        } else {
            cntrlcount += control_count(NORMVALUE + i, tmp[i]);
        }
    }
    if (cntrlcount != 4) {
        UNEXPECTED_TOKEN;
        exit(EXIT_FAILURE);
    } else {
        if (triangle_figure[triangle_tokens.close_bracket[1] + 2] != '\0') {
            UNEXPECTED_TOKEN;
            exit(EXIT_FAILURE);
        }
        int checker = point_check(
                triangle_figure, triangle_tokens.open_bracket[1], triangle_tokens.space[0]);
        if (checker != 0) {
            triangle_tokens.x[0] = triangle_point_reader(triangle_figure, triangle_tokens.open_bracket[1], triangle_tokens.space[0]);
            checker = point_check(
                triangle_figure, triangle_tokens.comma[0], triangle_tokens.space[1]);
            for (i = 1; (i < 4) && (checker != 0); ++i) {
                triangle_tokens.x[i] = triangle_point_reader(triangle_figure, triangle_tokens.comma[i - 1], triangle_tokens.space[i]);
                if (i < 3) {
                    checker = point_check(
                        triangle_figure, triangle_tokens.comma[i], triangle_tokens.space[i + 1]);
                }
            }
            checker = point_check(
                    triangle_figure, triangle_tokens.space[0], triangle_tokens.comma[0]);
            if (checker != 0) {
                for (i = 0; (i < 3) && (checker != 0); ++i) {
                    triangle_tokens.y[i] = triangle_point_reader(triangle_figure, triangle_tokens.space[i], triangle_tokens.comma[i]);
                    if (i < 2) {
                        checker = point_check(
                            triangle_figure, triangle_tokens.space[i + 1], triangle_tokens.comma[i + 1]);
                    }
                }
                checker = point_check(
                    triangle_figure, triangle_tokens.space[3], triangle_tokens.close_bracket[0]);
                if (checker != 0) {
                    triangle_tokens.y[3] = triangle_point_reader(triangle_figure, triangle_tokens.space[3], triangle_tokens.close_bracket[1]);
                }
            }
        }
    }
    if ((triangle_tokens.x[0] == triangle_tokens.x[3]) && (triangle_tokens.y[0] == triangle_tokens.y[3])) {
        return triangle_tokens;
    } else {
        UNEXPECTED_TOKEN;
        exit(EXIT_FAILURE);
    }
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
            EXP_INTEGER;
            exit(EXIT_FAILURE);
        }
    }
    return checker;
}

int triangle_point_reader(char *triangle_wkt, int boarder1, int boarder2)
{
    int j = 0;
    char coord_of_point[boarder2 - boarder1];
    for (int i = boarder1 + 1; i < boarder2;
         ++i) {
        coord_of_point[j] = triangle_wkt[i];
        j++;
    }
    int point = atoi(coord_of_point);
    return point;
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
            EXP_DOUBLE;
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

Calculations triangle_compute(Triangle points)
{
    Calculations result;
    double ab = sqrt(pow(points.x[1] - points.x[0], 2) +
                     pow(points.y[1] - points.y[0], 2));
    double bc = sqrt(pow(points.x[2] - points.x[1], 2) +
                     pow(points.y[2] - points.y[1], 2));
    double ac = sqrt(pow(points.x[2] - points.x[0], 2) +
                     pow(points.y[2] - points.y[0], 2));
    result.perimeter = ab + bc + ac;

    double det =
        ((points.x[1] - points.x[0]) * (points.y[2] - points.y[0]) -
        ((points.x[2] - points.x[0]) * (points.y[1] - points.y[0])));
    result.area = fabs(det) / 2;

    return result;
}