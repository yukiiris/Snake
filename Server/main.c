#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main(int argc, char **argv) {

	init();
    draw(0);
	draw(1);
	server();
	return 0;
}
