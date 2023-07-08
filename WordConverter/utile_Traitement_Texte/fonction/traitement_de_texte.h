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

typedef struct {
    char* number;
    int end_position;
} NumberInfo;

typedef struct {
    char* word;
    int end_position;
} EmailInfo;

/*Module Filtre*/
typedef struct {
    int (*filter)(const char* text, int position, const char* separators);
    void (*action)(const char* text, int position, const char* separators);
} FilterAction;

int is_url_filter(const char* text, int position, const char* separators);
void url_action(const char* text, int position, const char* separators);
int is_word_filter(const char* text, int position, const char* separators);
void word_action(const char* text, int position, const char* separators);


regex_t compile_regex(const char* pattern);
char* extract_partial_text(const char* text, int position);
int is_url_start(const char* text, int position, regex_t* url_regex);
URLInfo get_url_info(const char* text, int position, regex_t* url_regex);
URLInfo is_url_at_position(const char* text, int position);
int countUrl(const char* text);
int countLengthText(const char* text);
void printAllUrlInText(const char* text);

/* WORD Traitement*/
int findWordStart(const char* text, int position, const char* separators);
int findWordEnd(const char* text, int position, const char* separators);
char* extractWord(const char* text, int start, int end);
WordInfo getWordAtPosition(const char* text, int position, const char* separators);
void printWordAndLink(const char* text);
void runExamples();
int isSeparator(char character, const char* separators);

#endif  // TRAITEMENT_DE_TEXTE_H
