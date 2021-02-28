/* begin wrap.c */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXLINE 10000
#define MAXWORD 1000

int main(int argc, char* argv[]) {
	FILE *inf, *outf;
	char c = '\0', cc, d, line[MAXLINE+2], word[MAXWORD+2];
	int width, newline = 0, line_pos = 0, word_pos = 0;
	if (argc != 4) {
		printf("USAGE: wrap <read_from> <write_to> <chars_per_line>\n");
		return 0;
	}
	if (!strcmp(argv[1], argv[2])) {
		printf("ERROR: input and output files must differ\n");
		return 0;
	}
	if (!(inf = fopen(argv[1], "r"))) {
		printf("ERROR: can't read from \"%s\"\n", argv[1]);
		return 0;
	}
	if (!(outf = fopen(argv[2], "w"))) {
		printf("ERROR: can't write to \"%s\"\n", argv[2]);
		return 0;
	}
	if ((width = atoi(argv[3])) > MAXLINE || width < 1) {
		printf("ERROR: line width must be from 1 to %d, inclusive\n", MAXLINE);
		return 0;
	}
	while (1) {
		d = cc;
		c = cc = getc(inf);
		if (c == EOF) {
			if (line_pos > 0) {
				line[line_pos] = '\0';
				fprintf(outf, "%s\n", line);
			}
			goto quit;
		}
		if (c == '\r')
			continue;
		if (c == '\n') {
			if (d == '\n')
				newline = 1;
			else
				c = ' ';
		}
		line[line_pos++] = word[word_pos++] = c;
		if (isspace(c))
			word_pos = 0;
		if (word_pos > MAXWORD) {
			word[word_pos] = '\0';
			printf("ERROR: \"%s\" exceeds maximum word length (%d)\n", word, MAXWORD);
			goto quit;
		}
		if (newline || line_pos > width) {
			newline = 0;
			line_pos -= word_pos;
			while (isspace(line[--line_pos]) && line[line_pos] != '\n');
			line[line_pos+1] = '\0';
			fprintf(outf, "%s\n", line);
			strncpy(line, word, word_pos);
			line_pos = word_pos;
		}
	}
quit:;
     fclose(outf);
     fclose(inf);
     return 0;
}
/* end wrap.c */
