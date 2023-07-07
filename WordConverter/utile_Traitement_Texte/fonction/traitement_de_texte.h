#ifndef TRAITEMENT_DE_TEXTE_H
#define TRAITEMENT_DE_TEXTE_H

#include <stdbool.h>
#include <stdlib.h>
#include <regex.h>


typedef struct {
    char* url;
    int end_position;
} URLInfo;

typedef struct {
    char* word;
    int end_position;
} WordInfo;

regex_t compile_regex(const char* pattern);
char* extract_partial_text(const char* text, int position);
URLInfo is_url_at_position(const char* text, int position);
int countUrl(const char* text);
int countLengthText(const char* text);
void printAllUrlInText(const char* text);
WordInfo getWordAtPosition(const char* text, int position, const char* separators);
void printWordAndLink(const char* text);
void runExamples();

#endif  // TRAITEMENT_DE_TEXTE_H
