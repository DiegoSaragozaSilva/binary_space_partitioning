#ifndef BSP_H
#define BSP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINES 1024

typedef struct point {
	double x;
	double y;
} point;

typedef struct line {
	point a;
	point b;
} line;

typedef struct node node;
struct node {
	line* lines;
	node* back;
	node* front;
};

typedef struct bsp_tree {
	node* root;
} bsp_tree;

point get_point(double x, double y);
line get_line(double x1, double y1, double x2, double y2);
bsp_tree get_bsp_tree(node* root);

void make_tree(node* n, int n_lines);
int get_tree_height(node* root);
void visualize_tree(bsp_tree tree);

int intersection(line l1, line l2);
point intersection_point(line l1, line l2);

#endif
