#include "bsp.h"

int main() {
	line l1 = get_line(0, 0, 1, 0);
	line l3 = get_line(0.5, 0.2, 1, -1);

	line lines[] = {l1, l3};

	node root = {
		.lines = lines,
		.front = 0,
		.back = 0
	};

	bsp_tree tree = get_bsp_tree(&root);

	make_tree(tree.root, sizeof(lines) / sizeof(lines[0]));

	visualize_tree(tree);

	return 1;	
}
