#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>



void show_alloc_meme (void)
{
	int trying;
	char *str;

	str = malloc(sizeof(char * ) + 1 *3);
	trying = getpagesize();
	if (trying)
		printf("%d\n", trying);
	else
		printf("Error occured.\n");
	printf("The page size for this system is %ld bytes.\n",
	       sysconf(_SC_PAGESIZE)); /* _SC_PAGE_SIZE is OK too. */
}

int main(void)
{
	show_alloc_meme();
	return (0);
}