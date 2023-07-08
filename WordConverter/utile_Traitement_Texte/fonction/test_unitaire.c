#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int totalTests = 0;
int testsReussis = 0;
int testsEchoues = 0;

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef void (*TestResultCallback)(const char *, int);

TestResultCallback defaultCallback = NULL;

#define TEST_REPORT_FOLDER "TestReport"
#define SUCCESS_FILE "TestReport/success.txt"
#define FAILED_FILE "TestReport/failed.txt"

void createTestReportFolder() {
    struct stat st;
    if (stat(TEST_REPORT_FOLDER, &st) == -1) {
        mkdir(TEST_REPORT_FOLDER, 0700);
    }
}

void clearTestReportFiles() {
    remove(SUCCESS_FILE);
    remove(FAILED_FILE);
}

void recordTestResult(const char *conditionString, int condition) {
    const char *filename = condition ? SUCCESS_FILE : FAILED_FILE;
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier '%s'.\n", filename);
        return;
    }
    fprintf(file, "%s\n", conditionString);
    fclose(file);
}

void initTestJournal(int clearPreviousJournal) {
    createTestReportFolder();

    if (clearPreviousJournal) {
        clearTestReportFiles();
    }
}
void printSectionHeader(const char *functionName) {
    int borderLength = strlen(functionName) + 8;  // Longueur de la chaîne functionName + caractères supplémentaires
    printf("\n");  // Ligne vide avant l'encart
    printf("%s\n", "=======================================");
    printf("|%*s%*s|\n", borderLength / 2, "", (borderLength + 1) / 2, "");  // Espaces vides sur la première ligne
    printf("|=== %s ===|\n", functionName);
    printf("|%*s%*s|\n", borderLength / 2, "", (borderLength + 1) / 2, "");  // Espaces vides sur la dernière ligne
    printf("%s\n", "=======================================");
    printf("\n");  // Ligne vide après l'encart
}
const char *TEST_CONTEXT = "";  // Déclaré comme const char *

void checkAssertion(int condition, const char *conditionString, const char *functionName, TestResultCallback callback) {
    if (strcmp(functionName, TEST_CONTEXT) != 0) {
        printSectionHeader(functionName);  // Appel de la fonction pour afficher l'encart
        TEST_CONTEXT = functionName;  // Réassigner le pointeur
    }

    totalTests++;
    if (condition) {
        printf(ANSI_COLOR_GREEN "Test réussi : %s\n" ANSI_COLOR_RESET, conditionString);
        testsReussis++;
    } else {
        printf(ANSI_COLOR_RED "Test échoué : %s\n" ANSI_COLOR_RESET, conditionString);
        testsEchoues++;
    }

    char resultString[512];
    snprintf(resultString, sizeof(resultString), "%s", conditionString);
    recordTestResult(resultString, condition);

    if (callback != NULL) {
        callback(resultString, condition);
    }
}

#define TEST_ASSERT(condition, callback) \
    do { \
        TestResultCallback cb = (callback && callback != NULL) ? callback : defaultCallback; \
        checkAssertion((condition), #condition, __func__, cb); \
    } while (0)

#define TEST_ASSERT_NC(condition) \
    TEST_ASSERT(condition, NULL)

int additionner(int a, int b) {
    return a + b;
}

void handleTestResult(const char *conditionString, int condition) {
    // Traitement spécifique sur le résultat du test
    if (condition) {
        printf("Le test '%s' a réussi.\n", conditionString);
    } else {
        printf("Le test '%s' a échoué.\n", conditionString);
    }
    // Effectuer d'autres traitements...
}

void testFunction() {
    TEST_ASSERT_NC(additionner(2, 3) == 5);
	TEST_ASSERT_NC(additionner(2, 3) == 5);
}
void nouvelleTestFunction() {
    TEST_ASSERT_NC(additionner(2, 3) != 5);
	TEST_ASSERT_NC(additionner(2, 3) == 5);
}
int main() {
    int clearPreviousJournal = 1; // Modifier cette valeur pour définir si l'ancien journal doit être écrasé ou non

    initTestJournal(clearPreviousJournal);

    testFunction();
	nouvelleTestFunction();
    printf("\nTotal des tests exécutés : %d\n", totalTests);
    printf("Tests réussis : %d\n", testsReussis);
    printf("Tests échoués : %d\n", testsEchoues);

    return 0;
}
