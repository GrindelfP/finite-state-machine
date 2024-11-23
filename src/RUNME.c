/*

   _____ _______    _______ ______   __  __          _____ _    _ _____ _   _ ______ 
  / ____|__   __|/\|__   __|  ____| |  \/  |   /\   / ____| |  | |_   _| \ | |  ____|
 | (___    | |  /  \  | |  | |__    | \  / |  /  \ | |    | |__| | | | |  \| | |__   
  \___ \   | | / /\ \ | |  |  __|   | |\/| | / /\ \| |    |  __  | | | | . ` |  __|  
  ____) |  | |/ ____ \| |  | |____  | |  | |/ ____ \ |____| |  | |_| |_| |\  | |____ 
 |_____/   |_/_/    \_\_|  |______| |_|  |_/_/    \_\_____|_|  |_|_____|_| \_|______|
                                                                                     
                                                                                     
2024-11-22 by GrindelfP.                                                                                     

This is a main file for the State Machine program.
*/
#include <stdio.h>
#include "state-machine.h"
#define INPUT_LENGTH 60
int handleInputLine(char *line);

int main(int argc, char** argv) {
    
    char* line = malloc(INPUT_LENGTH), * lexemesSet = malloc(strlen(line) + 1);
    int status = handleInputLine(line);

    if (status == 0) status = stateMachine(line, lexemesSet);

    if (status == 0) {
        printf("Formated line is: %s\n", line);
        printf("Lexemes set for this line is: [\n");
        printf("%s", lexemesSet);
        printf("]\n");
    }

    free(lexemesSet);
    free(line);

    return status;
}

int handleInputLine(char *line) {

    int status = 0;

    printf("Enter here the line to be formated\n(up to 60 characters, others will be truncated): ");

    if (fgets(line, INPUT_LENGTH, stdin)) {
        line[strcspn(line, "\n")] = 0;
        printf("Here is your line: %s\n", line);
    }

    return status;
}
