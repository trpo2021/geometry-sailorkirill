#pragma once

#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAXSIZE 50
#define NORMVALUE 1

typedef struct {
    double r;
    int x;
    int y;
    int space;
    int comma;
    int open_bracket;
    int close_bracket;
} Circle;

typedef struct {
    int x[4];
    int y[4];
    int space[4];
    int comma[3];
    int open_bracket[2];
    int close_bracket[2];
} Triangle;

typedef struct {
    double perimeter;
    double area;
} Calculations;

Calculations triangle_compute(Triangle points);

Calculations circle_compute(double radius);

int radius_check(char* figure, int indx1, int indx2);

int triangle_point_reader(char* triangle_wkt, int boarder1, int boarder2);

int point_check(char* figure, int indx1, int indx2);

int control_count(int norm, int get_count);

Triangle triangle_wkt_check(char* triangle_figure, int triangle_length);

Circle circle_wkt_check(char* circle_figure, int circle_length);

int wkt_check(char* figure, int figure_length);

bool circ_intersects_circ(int x1, int x2, int y1, int y2, double r1, double r2);

bool circ_intersects_triangle(int x1, int* x2, int y1, int* y2, int r);

bool triangle_intersects_circ(int* x1, int x2, int* y1, int y2, int r);