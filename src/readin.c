/* Functions to get text from stdin */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readin.h"

char *gets_unl(void)
{
	char *str = readstdin();
#ifdef DEBUG
	puts("String was: ");
	printf("%s\n", str);
#endif
	return str;
}

char *readstdin(void)
{
	const size_t morelength = 20;
	char *buffer = malloc(morelength);
	char *currentpos = buffer;
	int currentchar;
	size_t maxlength = morelength;
	size_t length = 0;
	if (is_null(currentpos))
		return NULL;
	while (((currentchar = getchar()) != '\n') && currentchar != EOF) {
		if (++length >= maxlength) {
			char *newBuffer = realloc(buffer, maxlength += morelength);
			if (is_null(newBuffer)) {
				free(buffer);
				return NULL;
			}
			currentpos = newBuffer + (currentpos - buffer);
			buffer = newBuffer;
		}
		*currentpos++ = currentchar;
	}
	*currentpos = '\0';
	return buffer;
}

int want_date(void)
{
	char *str = gets_unl();
	size_t sz = strlen(str);
	if (sz == 1) {
		if (*str == 'y' || *str == 'Y') {
			free(str);
			return 1;
		}
	}
	free(str);
	return 0;
}

inline
size_t is_null(char *ptr)
{
	//return !ptr;
	if (ptr == NULL)
		return 1;
	else
		return 0;
}

char *gets_unl_f(FILE *db)
{
	const size_t morelength = 20;
	char *buffer = malloc(morelength);
	char *currentpos = buffer;
	int currentchar;
	size_t maxlength = morelength;
	size_t length = 0;
	if (is_null(currentpos))
		return NULL;
	while (((currentchar = fgetc(db)) != '\n') && currentchar != EOF) {
		if (++length >= maxlength) {
			char *newBuffer = realloc(buffer, maxlength += morelength);
			if (is_null(newBuffer)) {
				free(buffer);
				return NULL;
			}
			currentpos = newBuffer + (currentpos - buffer);
			buffer = newBuffer;
		}
		*currentpos++ = currentchar;
	}
	*currentpos = '\0';
	return buffer;
}
