#include <stdio.h>
#include <stdlib.h>

#include "src/commands.h"
#include "src/saveload.h"
#include "src/list.h"

/*struct data savedata;*/

int main(void)
{
	
	/*load_data(&savedata);
	run();*/
	while (1) {
		if (!get_command())
			break;
	}
	return 0;
}
