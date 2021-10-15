#include "bsp.h"

point get_point(double x, double y) {
	point p = {
		.x = x,
		.y = y
	};
	return p;
}

line get_line(double x1, double y1, double x2, double y2) {
	point p1 = {
		.x = x1,
		.y = y1
	};
	point p2 = {
		.x = x2,
		.y = y2
	};

	line l = {
		.a = p1,
		.b = p2
	};
	return l;
}

bsp_tree get_bsp_tree(node* root) {
	bsp_tree tree = {
		.root = root
	};
	return tree;
}

int intersection(line l1, line l2) {
	return fabs(((l1.a.x - l1.b.x) * (l2.a.y - l2.b.y) - (l1.a.y - l1.b.y) * (l2.a.x - l2.b.x))) >= 1e-7;
}

point intersection_point(line l1, line l2) {
	double d = (l1.a.x - l1.b.x) * (l2.a.y - l2.b.y) - (l1.a.y - l1.b.y) * (l2.a.x - l2.b.x);
	double x_n = (l1.a.x * l1.b.y - l1.a.y * l1.b.x) * (l2.a.x - l2.b.x) - (l1.a.x - l1.b.x) * (l2.a.x * l2.b.y - l2.a.y * l2.b.x);
	double y_n = (l1.a.x * l1.b.y - l1.a.y * l1.b.x) * (l2.a.y - l2.b.y) - (l1.a.y - l1.b.y) * (l2.a.x * l2.b.y - l2.a.y * l2.b.x);

	point p = {
		.x = x_n / d,
		.y = y_n / d
	};

	return p;
}

void make_tree(node* n, int n_lines) {

	if (n_lines == 0) return;

	int back_index = 0, front_index = 0;
	node* back;
	node* front;

	// Allocating memory for the nodes and nodes lines
	back = (node*)malloc(sizeof(node));
	front = (node*)malloc(sizeof(node));
	back->lines = (line*)malloc(sizeof(line) * MAX_LINES);
	front->lines = (line*)malloc(sizeof(line) * MAX_LINES);

	line center = n->lines[0];
	for (int i = 1; i < n_lines; i++) {
		line test_line = n->lines[i];
		// Check if the two lines intersect
		if (intersection(center, test_line)) {
			// Find the intersection point
			point cross_point = intersection_point(center, test_line);
			
			// Create two more lines subdividing the test line
			line sub_one = {
				.a = test_line.a,
				.b = cross_point
			};

			line sub_two = {
				.a = cross_point,
				.b = test_line.b
			};

			// Check if each point of the two new lines lies on top or above the center line
			double d;
			if (test_line.a.x != cross_point.x && test_line.a.y != cross_point.y) {
				double d = (sub_one.a.x - center.a.x) * (center.b.y - center.a.y) - (sub_one.a.y - center.a.y) * (center.b.x - center.a.x);
				if (d < 0) {
					back->lines[back_index] = sub_one;
					back_index++;
					printf("above\n");
				}
				else {
					front->lines[front_index] = sub_one;
					front_index++;
					printf("below\n");
				}
			}
			if (test_line.b.x != cross_point.x && test_line.b.y != cross_point.y) {
				d = (sub_two.a.x - center.a.x) * (center.b.y - center.a.y) - (sub_two.a.y - center.a.y) * (center.b.x - center.a.x);
				if (d < 0) {
					back->lines[back_index] = sub_two;
					back_index++;
					printf("above\n");
				}
				else {
					front->lines[front_index] = sub_two;
					front_index++;
					printf("below\n");
				}
			}
		}
		// Check if each point of the line lies on top or above the center line
		else {
			double d1 = (test_line.a.x - center.a.x) * (center.b.y - center.a.y) - (test_line.a.y - center.a.y) * (center.b.x - center.a.x);
			double d2 = (test_line.b.x - center.a.x) * (center.b.y - center.a.y) - (test_line.b.y - center.a.y) * (center.b.x - center.a.x);
			if (d1 < 0 && d2 < 0) {
				back->lines[back_index] = test_line;
				back_index++;
				printf("above\n");
			}
			else if (d1 > 0 && d2 > 0) {
				front->lines[front_index] = test_line;
				front_index++;
				printf("below\n");
			}
		}
	}

	n->back = (back_index == 0) ? 0 : back;
	n->front = (front_index == 0) ? 0 : front;

	printf("back_size=%d, front_size=%d\n", back_index, front_index);
	make_tree(back, back_index);
	make_tree(front, front_index);
}

int get_tree_height(node* root) {
	if (!root) return 0;

	int left_height = get_tree_height(root->back);
	int right_height = get_tree_height(root->front);

	return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

void visualize_tree(bsp_tree tree) {
	int tree_height = get_tree_height(tree.root);

	printf("height=%d\n", tree_height);
}
