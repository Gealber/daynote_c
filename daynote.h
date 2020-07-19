typedef struct Note {
	char *date;
	char *text;
} Note;

char *getcurrent_date(void);
int check_date(char *date);
int create_note(Note *note);
int append_note(char *text);
