/*

   _____ _______    _______ ______   __  __          _____ _    _ _____ _   _ ______ 
  / ____|__   __|/\|__   __|  ____| |  \/  |   /\   / ____| |  | |_   _| \ | |  ____|
 | (___    | |  /  \  | |  | |__    | \  / |  /  \ | |    | |__| | | | |  \| | |__   
  \___ \   | | / /\ \ | |  |  __|   | |\/| | / /\ \| |    |  __  | | | | . ` |  __|  
  ____) |  | |/ ____ \| |  | |____  | |  | |/ ____ \ |____| |  | |_| |_| |\  | |____ 
 |_____/   |_/_/    \_\_|  |______| |_|  |_/_/    \_\_____|_|  |_|_____|_| \_|______|
                                                                                     
                                                                                     
2024-11-22 by GrindelfP.                                                                                     

This is a source file for the State Machine module.

The State Machine module contains an example of a determined state machine,
which is able to perform following operations on a provided text line: 
 - delete a block commentary,
 - delete redundant spaces,
 - build a lexeme set for a provided line.
*/

#include "state-machine.h"

/**
 * This function updates the provided line by formatting it 
 * (i.e. removing block commentary and redundant spaces)
 * and 
 * generates a set of lexemes for provided line.
 * 
 * @param line       provided text line
 * @param lexemesSet storage memory for lexemes set 
 *                   (should be uninitialized, because it is initialized
 *                    inside the function)
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int stateMachine(char* line, char* lexemesSet) {
    
    int status;
    
    status = removeBlockCommentary(line);
    
    if (status == 0) status = removeRedundantSpaces(line);
    
    if (status == 0) status = printLexemesSet(line);
    
    return status;
} 

/**
 * This function removes redundant spaces in a provided line.
 * 
 * @param line       provided text line
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int removeRedundantSpaces(char* line) {
    int shortener = 1, status = 0, lineLength = strlen(line);
    for (int i = 0; i < lineLength - shortener; ++i) {
        if (line[i] == ' ' && line[i + 1] == ' ') {
            status = removeAtIndex(line, i);
            i--;
            shortener++;
        } else if (i == 0 && line[i] == ' ') {
            status = removeAtIndex(line, i);
            i--;
            shortener++;
        } else if (line[i] == ' ' && line[i + 1] == ';') {
            status = removeAtIndex(line, i);
            i--;
            shortener++;
        } else if (line[i] == ' ' && line[i + 1] == ')') {
            status = removeAtIndex(line, i);
            i--;
            shortener++;
        } else if (line[i] == '(' && line[i + 1] == ' ') {
            status = removeAtIndex(line, i + 1);
            i--;
            shortener++;
        }
    }

    return status;
}

/**
 * This function removes block commentary from a provided line.
 * It is built using a following state machine, 
 * which table is presented inside the function.
 * 
 * @param line       provided text line
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int removeBlockCommentary(char* line) {

    /*
        STATE MACHINE:
        ╔═══════╦═══════╦════╦════╦═══════╗
        ║ State ║ Input ║ /  ║ *  ║ OTHER ║
        ╠═══════╬═══════╬════╬════╬═══════╣
        ║ q0    ║ ε     ║ q1 ║ q0 ║  q0   ║
        ║ q1    ║ '/'   ║ q1 ║ q2 ║  q0   ║
        ║ q2    ║ '/*'  ║ q2 ║ q3 ║  q2   ║
        ║ q3    ║ '/**' ║ q0 ║ q3 ║  q2   ║
        ╚═══════╩═══════╩════╩════╩═══════╝
    */
    
    int state = 0, status = 0, lineLength = strlen(line), startIndex = 0, endIndex = 0, stateChanged = 1;

    while (stateChanged == 1) {
        stateChanged = 0;
        for (int i = 0; i < lineLength; ++i) {
            
            switch (state) {
                case 0:
                    if (line[i] == '/') { state = 1; startIndex = i; stateChanged = 1; }
                    else if (line[i] == '*') {state = 0; stateChanged = 0;}
                    else { state = 0; stateChanged = 0; }
                    break;
        
                case 1:
                    if (line[i] == '/') {state = 1; stateChanged = 0;}
                    else if (line[i] == '*') {state = 2; stateChanged = 1;}
                    else { state = 0; stateChanged = 0; }
                    break;

                case 2:
                    if (line[i] == '/') {state = 2; stateChanged = 0; }
                    else if (line[i] == '*') { state = 3; stateChanged = 1; }
                    else { state = 2; stateChanged = 0;}
                    break;

                case 3:
                    if (line[i] == '/') {
                        endIndex = i;
                        removeSubstring(line, startIndex, endIndex);
                        state = 0;
                        stateChanged = 0;
                    }
                    else if (line[i] == '*') { state = 3; stateChanged = 0; }
                    else { state = 2; stateChanged = 1; }
                    break;

                default:
                    { status = -1; break; stateChanged = 0; }
            }
        }
    }
    
    return status;
}

/**
 * This function prints a set of lexemes for provided line.
 * 
 * @param line       provided text line
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int printLexemesSet(char* line) {

    char *lexemes = malloc(strlen(line) + 1);
    int i = 0;

    strcpy(lexemes, line);
    int len = strlen(lexemes);
    
    while (i < len) {
        if (isspace(lexemes[i])) {
            // Skip whitespace (redundant also, but these should never get here)
            i++;
        } else if (isdigit(lexemes[i])) {
            // Handle numbers
            while (isdigit(lexemes[i])) {
                putchar(lexemes[i]);
                i++;
            }
            putchar('\n');
        } else if (isalpha(lexemes[i])) {
            // Handle identifiers (variables)
            while (isalnum(lexemes[i]) || lexemes[i] == '_') {
                putchar(lexemes[i]);
                i++;
            }
            putchar('\n');
        } else {
            // Handle operators and symbols
            putchar(lexemes[i]);
            putchar('\n');
            i++;
        }
    }

    free(lexemes);
    
    return 0; // I guess there is nothingh which can go wrong in the logic 
              // (only internal errors)
}

/**
 * This function removes character from a line at a specified index.
 * 
 * @param line  provided text line
 * @param index index at which is the element to be removed 
 *
 * @returns 0 if success, -1 if something went wrong
 */
int removeAtIndex(char *line, int index) {
    int status = -1, lineLength = strlen(line);

    if (index > 0 && index <= lineLength) {
        status = 0;
        int i;
        for (i = index; i < lineLength - 1; ++i) {
            line[i] = line[i + 1];
        }
        line[i] = '\0';
    } 

    return status;
}

/**
 * This function removes subsltring from a line marked by indices.
 * 
 * @param line       provided text line
 * @param startIndex index at which the substring starts
 * @param endIndex   index at which the substring ends
 *
 * @returns 0 if success, -1 if something went wrong
 */
int removeSubstring(char* line, int startIndex, int endIndex) {
    int status = -1, len = strlen(line);
    
    if (startIndex > 0 && endIndex <= len && startIndex < endIndex) {
        
        // Shift characters after the substring to the left
        int i;
        for (i = endIndex + 1; i < len; i++) {
            line[startIndex + i - endIndex - 1] = line[i];
        }
    
        line[startIndex + i - endIndex - 1] = '\0';
    }

    return status;
}
