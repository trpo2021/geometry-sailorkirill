#pragma once

#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    double perimeter;
    double area;
} Calculations;

Calculations circle_compute(double radius);

int radius_check(char *figure, int indx1, int indx2);

int point_check(char *figure, int indx1, int indx2);

int control_count(int norm, int get_count);

Circle circle_wkt_check(char *circle_figure, int circle_length);

int wkt_check(char *figure, int figure_length);