#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int characters, words, lines, totalChars, totalLines, totalWords;

void counter(FILE * file, bool isMultFiles) {
    char ch;
    characters = words = lines = 0;
    bool inWord = false;
    while ((ch = fgetc(file)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
        }
        if (isspace(ch)) {
            if (inWord) {
                words++;
                inWord = false;
            }
        }
        else {
            inWord = true;
        }
    }
    if (inWord) { // checks to see if we are in a word at EOF
        words++;
    }
    printf("Characters = %d, Words = %d, Lines = %d\n", characters, words, lines);

    if (isMultFiles) {
            totalChars += characters;
            totalWords += words;
            totalLines += lines;
    }
}

int main(int argc, const char * argv[]) {

    FILE *file;
    bool isMultFiles;

    if (argc == 1) {
        file = stdin;
        isMultFiles = false;
        counter(file, isMultFiles);
        fclose(file);
    }
    else if (argc > 1) {
        totalChars = totalWords = totalLines = 0;
        for (int i = 1; i < argc; i++) {
            file =  fopen(argv[i], "r");
            isMultFiles = true;
            printf("File %d: ", i);
            counter(file, isMultFiles); 
            fclose(file);
        }
        printf("Total Characters = %d, Total Words = %d, Total Lines = %d", totalChars, totalWords, totalLines);
    }
}