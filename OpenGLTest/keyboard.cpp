#include <cstdio>
#include <cstdlib>
#include "main.h"

void OnKeyboard(unsigned char key, int x, int y) {
	switch (key) {
    	case '\x1B':
			exit(EXIT_SUCCESS);
		break;
	}
}