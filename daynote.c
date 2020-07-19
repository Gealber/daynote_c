#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "daynote.h"

char *getcurrent_date(void)
{
	char *date = malloc(sizeof(char)*15);
	if (!date)
		return NULL;
	time_t now;
	time(&now);
	struct tm tm = *localtime(&now);
	sprintf(date, "%d/%d/%d\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
	return date;
}

int check_date(char *curr_date)
{
	char *line_buf = "";
	size_t line_buf_size = 0;

	FILE *datesf = fopen("dates.db", "r");
	if (!datesf) {
		printf("Sorry file dates.db does not exists\n");
		return -1;
	}
	
	getline(&line_buf, &line_buf_size, datesf);
	if (line_buf == NULL || strcmp(curr_date, line_buf) == 0) {
		free(line_buf);
		fclose(datesf);
		return 1;
	} else {
		free(line_buf);
		fclose(datesf);
		return 0;
	}
	
}

int create_note(Note *note)
{
	FILE *fnotes = fopen("notes.db", "a");
	if (!fnotes) {
		printf("Sorry coudn't open file notes.db\n");
		return 1;
	}
	
	FILE *datesf = fopen("dates.db", "w");
	if (!datesf) {
		printf("Sorry coudn't open file dates.db\n");
		return 1;
	}
	
	size_t date_size = strlen(note->date);
	size_t text_size = strlen(note->text);

	fwrite(note->date, sizeof(char), date_size, datesf);
	fwrite(note->date, sizeof(char), date_size, fnotes);
	fwrite(note->text, sizeof(char), text_size, fnotes);
	fclose(fnotes);
	fclose(datesf);
	return 0;
}

int append_note(char *text)
{
	FILE *fnotes = fopen("notes.db", "a");
	if (!fnotes) {
		printf("Sorry coudn't open file notes.db\n");
		return 1;
	}

	size_t text_size = strlen(text);

	fwrite(text, sizeof(char), text_size, fnotes);
	fclose(fnotes);
	return 0;
}

void usage(void)
{
	printf("\a");
	printf("\033[0;31mUsage: daynote <note>\033[0m\n");
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		usage();
		return 1;
	}
	
	Note *note = calloc(1, sizeof(Note));
	if (!note) {
		printf("Not enough memory for notes allocation\n");
		return 1;
	}

	int text_size = strlen(argv[1]);
	note->date = getcurrent_date();
	
	note->text = malloc(sizeof(char)*(text_size+2));
	sprintf(note->text, "%s\n", argv[1]);

	int isdate = check_date(note->date);
	if (isdate == 1)
		append_note(note->text);
	else if (isdate == 0)
		create_note(note);
	else
		goto error;

	free(note->date);
	free(note->text);
	free(note);
	return 0;

error:
	free(note->date);
	free(note->text);
	free(note);
	return 1;
}
