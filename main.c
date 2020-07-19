#include <time.h>
#include <string.h>
#include <stdio.h>

int main(int agrc, char *argv[])
{
	char date[100];
	time_t t;
       	time(&t);
	struct tm tm = *localtime(&t);
	sprintf(date, "%d/%d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	FILE *fp = fopen("try", "w");
	fwrite(date, sizeof(char), strlen(date), fp);
	return 0;
}
