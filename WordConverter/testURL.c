#include <stdio.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* url;
    int end_position;
} URLInfo;

/**
 * compile_regex - Compile l'expression régulière
 * @pattern: Le pattern de l'expression régulière
 *
 * Retourne la structure regex_t compilée.
 */
regex_t compile_regex(const char* pattern)
{
    regex_t regex;
    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Erreur lors de la compilation de l'expression régulière\n");
        exit(1);
    }
    return regex;
}

/**
 * extract_partial_text - Extrait le texte partiel à partir d'une position donnée
 * @text: Le texte source
 * @position: La position de départ
 *
 * Retourne le texte partiel extrait à partir de la position donnée.
 */
char* extract_partial_text(const char* text, int position)
{
    int length = strlen(text) - position;
    char* partial_text = (char*)malloc((length + 1) * sizeof(char));
    strncpy(partial_text, text + position, length);
    partial_text[length] = '\0';
    return partial_text;
}

/**
 * is_url_at_position - Vérifie si une URL débute à la position donnée
 * @text: Le texte source
 * @position: La position de départ
 *
 * Retourne une structure URLInfo contenant l'URL trouvée et la position de fin si une URL débute à la position donnée.
 * Sinon, retourne une structure URLInfo avec NULL et la position d'origine.
 */
URLInfo is_url_at_position(const char* text, int position)
{
    // Pattern de l'URL
    char* url_pattern = "(https?|ftp)://[^[:space:]/$.?#].[^[:space:]]*";

    regex_t url_regex = compile_regex(url_pattern);

    // Vérification si la position donnée correspond au début d'une URL
    char* partial_text = extract_partial_text(text, position);

    regmatch_t match;
    int reti = regexec(&url_regex, partial_text, 1, &match, 0);
    if (!reti && match.rm_so == 0) {
        // Une correspondance a été trouvée au début du texte partiel
        int start = match.rm_so;
        int end = match.rm_eo;
        int length = end - start + 1;
        char* url = strndup(partial_text + start, length);

        // Libération de la mémoire utilisée par l'expression régulière et le texte partiel
        regfree(&url_regex);
        free(partial_text);

        URLInfo info = {url, position + end};
        return info;
    }

    // Libération de la mémoire utilisée par l'expression régulière et le texte partiel
    regfree(&url_regex);
    free(partial_text);

    // Aucune correspondance trouvée ou la correspondance n'est pas au début, retour d'une structure URLInfo avec "URL n'existe pas"
    URLInfo info = {NULL, position};
    return info;
}

int countUrl(const char* text)
{
    int i = 0;
    int countUrl = 0;
    char current_character;
    URLInfo info;

    while ((current_character = text[i]) != '\0') {
        info = is_url_at_position(text, i);
        if (info.url != NULL) {
            printf("URL Trouver à la position: %d\n", i);
            printf("Fin de l'URL à la position: %d\n", info.end_position);
            countUrl++;
            i = info.end_position;
        } else {
            i++;
        }
		if (info.url != NULL) {
			free(info.url);
		}
    }
    return countUrl;
}
int countLengthText(const char* text)
{
	int length = 0;
	for(; text[length] != '\0'; length++)
	;
	return length;
}
void printAllUrlInText(const char* text)
{
    int i = 0;
    int countUrl = 0;
	int lengthText = countLengthText(text);
    char current_character;
    URLInfo info;

    while ((i <= lengthText)) {
        info = is_url_at_position(text, i);
        if (info.url != NULL) {
            printf("URL numéro[%d] Trouver la voici : %s\n", countUrl, info.url);
            printf("URL Trouver à la position: %d\n", i);
            printf("Fin de l'URL à la position: %d\n", info.end_position);
            countUrl++;
            i = info.end_position;
			free(info.url);
        }
        i++;
    }
}

typedef struct {
    char* word;
    int end_position;
} WordInfo;

WordInfo getWordAtPosition(const char* text, int position, const char* separators)
{
    int start = -1;
    int end = -1;
    int separators_length = strlen(separators);

    // Parcours du texte pour trouver les limites du mot
    int i = 0;
    while (text[i] != '\0') {
        bool is_separator = false;
        for (int j = 0; j < separators_length; j++) {
            if (text[i] == separators[j]) {
                is_separator = true;
                break;
            }
        }

        if (!is_separator) {
            // Début du mot
            if (start == -1) {
                start = i;
            }
            end = i;
        } else {
            // Fin du mot
            if (start != -1 && end != -1) {
                if (position >= start && position <= end) {  // Modification de la condition
                    // Le mot contenant la position cible est trouvé
                    int length = end - start + 1;
                    char* word = (char*)malloc((length + 1) * sizeof(char));
                    strncpy(word, text + start, length);
                    word[length] = '\0';

                    WordInfo info = {word, end};
                    return info;
                }
                start = -1;
                end = -1;
            }
        }
        i++;
    }

    // Vérification du dernier mot si la position est dedans
    if (start != -1 && end != -1 && position >= start && position <= end) {  // Modification de la condition
        int length = end - start + 1;
        char* word = (char*)malloc((length + 1) * sizeof(char));
        strncpy(word, text + start, length);
        word[length] = '\0';
        WordInfo info = {word, end};
        return info;
    }

    // Aucun mot ne contient la position cible
    WordInfo info = {NULL, -1};
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

    while ((i <= lengthText)) {
		info = is_url_at_position(text, i);
		if (info.url != NULL)
		{
			printf("URL numéro[%d] Trouver la voici : %s\n", countUrl, info.url);
			printf("URL Trouver à la position: %d\n", i);
			printf("Fin de l'URL à la position: %d\n", info.end_position);
			countUrl++;
			i = info.end_position;
			free(info.url);
		} 
		else
		{	
			wordInfo = getWordAtPosition(text, i, separators);
			if (wordInfo.word != NULL) 
			{
				
				printf("Mot numéro[%d] Trouver la voici : %s\n", countWord, wordInfo.word);
				printf("Mot Trouver à la position: %d\n", i);
				printf("Fin du mot à la position: %d\n", wordInfo.end_position);
				countWord++;
				i = wordInfo.end_position;
			}
			else 
			{
				printf("Ce n'est ni un mot ni une URL : %c\n", text[i]);
			}
			free(wordInfo.word);
		} 
		i++;
    }
}

int main()
{
    const char* text = "Voici un exemple de texte contenant une URL : https://www.example.com. toto https://chat.openai.com/c/6269c834-6230-4273-93ed-86994296e3ca";

    int position = 46;
	const char* separators = " ;,?;.:/!\n\t\r";
    URLInfo info = is_url_at_position(text, position);
	WordInfo wordInfo = getWordAtPosition(text, 0, separators);
    if (info.url != NULL) {
        printf("URL : %s\n", info.url);
        printf("Position de fin : %d\n", info.end_position);
        printf("Caractère au début de l'URL : %c\n", text[position]);
        printf("Caractère à la fin -1 : %c\n", text[info.end_position - 1]);
        printf("Caractère à la fin neutre : %c\n", text[info.end_position]);
        printf("Caractère à la fin +1 : %c\n", text[info.end_position + 1]);

        // Libération de la mémoire allouée pour l'URL
        free(info.url);
    } else {
        printf("Aucune URL ne commence à cette position.\n");
    }
	printf("Url Count: %d\n", countUrl(text));
	printAllUrlInText(text);
	printf("Test Trouve le premier mots : %s\n", wordInfo.word);
	free(wordInfo.word);
	printf("===========================================================================\n");
	printWordAndLink(text);

    return 0;
}
