#include <stdio.h>
#include <stdlib.h>

#include "src/commands.h"
#include "src/saveload.h"
#include "src/list.h"
#include "src/readin.h"

int main(void)
{
	while (1) {
		if (!get_command())
			break;
	}
	return 0;
}
