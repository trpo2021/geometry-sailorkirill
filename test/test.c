#include <libgeometry/functions.h>
#include <ctest.h>

CTEST(wkt_format_check, circle)
{
    char figure[] = "circle(5 1, 1.5)";
    const int figure_length = strlen(figure);
    const int result = wkt_check(figure, figure_length);
    
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(wkt_format_check, triangle)
{
    char figure[] = "triangle((-3 -2, -1 0, -3 2, -3 -2))";
    const int figure_length = strlen(figure);
    const int result = wkt_check(figure, figure_length);
    
    const int expected = 2;
    ASSERT_EQUAL(expected, result);
}

CTEST(wkt_format_check, incorrect_figure_1)
{
    char figure[] = "ciccle(5 -54, 35(";
    const int figure_length = strlen(figure);
    const int result = wkt_check(figure, figure_length);
    
    const int expected = -1;
    ASSERT_EQUAL(expected, result);
}

CTEST(wkt_format_check, incorrect_figure_2)
{
    char figure[] = "circle)5 -4, 353)";
    const int figure_length = strlen(figure);
    const int result = wkt_check(figure, figure_length);
    
    const int expected = -1;
    ASSERT_EQUAL(expected, result);
}

CTEST(wkt_format_check, incorrect_figure_3)
{
    char figure[] = "trihngle((5 1, 2 3, 5 3, 5 1))";
    const int figure_length = strlen(figure);
    const int result = wkt_check(figure, figure_length);
    
    const int expected = -1;
    ASSERT_EQUAL(expected, result);
}

CTEST(control_count_check, triangle_normal_value)
{
    const int get_count[] = {2, 2, 3, 4};
    int result = 0;
    for (int i = 0; i < 4; ++i) {
        if (i == 0) {
            result += control_count(NORMVALUE + 1, get_count[i]);
        } else {
            result += control_count(NORMVALUE + i, get_count[i]);
        }
    }
    
    const int expected = 4;
    ASSERT_EQUAL(expected, result);
}

CTEST(control_count_check, circle_normal_value)
{
    const int get_count[] = {1, 1, 1, 1};
    int result = 0;
    for (int i = 0; i < 4; ++i) {
        result += control_count(NORMVALUE, get_count[i]);
    }
    
    const int expected = 4;
    ASSERT_EQUAL(expected, result);
}

CTEST(control_count_check, incorrect_normal_value_1)
{
    const int get_count[] = {1, 1, 3, 2};
    int result = 0;
    for (int i = 0; i < 4; ++i) {
        result += control_count(NORMVALUE, get_count[i]);
    }
    
    const int expected = 2;
    ASSERT_EQUAL(expected, result);
}

CTEST(control_count_check, incorrect_normal_value_2)
{
    const int get_count[] = {1, 3, 3, 4};
    int result = 0;
    for (int i = 0; i < 4; ++i) {
        if (i == 0) {
            result += control_count(NORMVALUE + 1, get_count[i]);
        } else {
            result += control_count(NORMVALUE + i, get_count[i]);
        }
    }
    
    const int expected = 2;
    ASSERT_EQUAL(expected, result);
}

CTEST(point_checking, circle_point_check_1)
{
    char figure[] = "circle(5 1, 1.5)";
    const int indx1 = 6;
    const int indx2 = 8;
    int result = point_check(figure, indx1, indx2);

    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(point_checking, circle_point_check_2)
{
    char figure[] = "circle(     5 1, 1.5)";
    const int indx1 = 6;
    const int indx2 = 13;
    int result = point_check(figure, indx1, indx2);

    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(point_checking, circle_point_check_3)
{
    char figure[] = "circle(12 -453, 2332)";
    const int indx1 = 9;
    const int indx2 = 14;
    int result = point_check(figure, indx1, indx2);

    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(point_checking, triangle_point_check_1)
{
    char figure[] = "triangle((5 1, 2 5, 5 -2, 5 1))";
    const int indx1 = 11;
    const int indx2 = 13;
    int result = point_check(figure, indx1, indx2);

    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(point_checking, triangle_point_check_2)
{
    char figure[] = "triangle((5 1, 1 3, 54 1, 5 1))";
    const int indx1 = 27;
    const int indx2 = 29;
    int result = point_check(figure, indx1, indx2);

    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(point_checking, triangle_point_check_3)
{
    char figure[] = "triangle((5 1, 1 3, 54 1, 5      1))";
    const int indx1 = 27;
    const int indx2 = 34;
    int result = point_check(figure, indx1, indx2);

    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(calculations, circle_calculate)
{
    Calculations result;
    double radius = 1.5;
    result = circle_compute(radius);

    const int expected_area = 7.068583;
    const int expected_perimeter = 9.424778;
    ASSERT_DBL_NEAR(expected_area, result.area);
    ASSERT_DBL_NEAR(expected_perimeter, result.perimeter);
}

CTEST(calculations, triangle_calculate)
{
    Calculations result;
    Triangle points;
    
    points.x[0] = points.x[3] = 5;
    points.y[0] = points.y[3] = -1;
    points.x[1] = 2;
    points.y[1] = -3;
    points.x[2] = 5;
    points.y[2] = 1;

    result = triangle_compute(points);

    const int expected_area = 3;
    const int expected_perimeter = 10.605551;
    ASSERT_DBL_NEAR(expected_area, result.area);
    ASSERT_DBL_NEAR(expected_perimeter, result.perimeter);
}