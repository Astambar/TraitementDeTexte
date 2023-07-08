#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traitement_de_texte.h"

int findWordStart(const char* text, int position, const char* separators)
{
    int i = position;
    while (i >= 0 && !isSeparator(text[i], separators)) {
        i--;
    }
    return i + 1;
}

int findWordEnd(const char* text, int position, const char* separators)
{
    int i = position;
    while (text[i] != '\0' && !isSeparator(text[i], separators)) {
        i++;
    }
    return i - 1;
}

char* extractWord(const char* text, int start, int end)
{
    int length = end - start + 1;
    char* word = (char*)malloc((length + 1) * sizeof(char));
    strncpy(word, text + start, length);
    word[length] = '\0';
    return word;
}

WordInfo getWordAtPosition(const char* text, int position, const char* separators)
{
    int start = findWordStart(text, position, separators);
    int end = findWordEnd(text, position, separators);

    if (start != -1 && end != -1 && position >= start && position <= end) {
        char* word = extractWord(text, start, end);
        WordInfo info = { word, end };
        return info;
    }

    WordInfo info = { NULL, -1 };
    return info;
}

void printWordAndLink(const char* text)
{
    int i = 0;
    int countUrl = 0;
    int countWord = 0;
    int lengthText = countLengthText(text);
    const char* separators = " ;,?;.:/!\n\t\r";
    URLInfo info;
    WordInfo wordInfo;

    for (; i <= lengthText; i++) 
    {
        info = is_url_at_position(text, i);
        if (info.url != NULL)
        {
            printf("URL numéro[%d] Trouver la voici : %s\n", countUrl, info.url);
            printf("URL Trouver à la position: %d\n", i);
            printf("Fin de l'URL à la position: %d\n", info.end_position);
            countUrl++;
            i = info.end_position;
            free(info.url);
            continue;
        }
        wordInfo = getWordAtPosition(text, i, separators);
        if (wordInfo.word != NULL) 
        {
            printf("Mot numéro[%d] Trouver la voici : %s\n", countWord, wordInfo.word);
            printf("Mot Trouver à la position: %d\n", i);
            printf("Fin du mot à la position: %d\n", wordInfo.end_position);
            countWord++;
            i = wordInfo.end_position;
            free(wordInfo.word);
            continue;
        }
        printf("Ce n'est ni un mot ni une URL : %c\n", text[i]);
    }
}
