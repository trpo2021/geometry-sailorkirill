#pragma once

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int triangle_point_reader(char *triangle_wkt, int boarder1, int boarder2);

int point_check(char* figure, int indx1, int indx2);

int control_count(int norm, int get_count);

Triangle triangle_wkt_check(char* triangle_figure, int triangle_length);

Circle circle_wkt_check(char* circle_figure, int circle_length);

int wkt_check(char* figure, int figure_length);