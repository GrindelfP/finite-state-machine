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
 * @param lineLenght lenght of the provided line
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int stateMachine(char* line, char** lexemesSet) {
    
    int status, lineLength = strlen(line);
    
    status = removeRedundantSpaces(line, lineLength);

    // TODO: make lineLength be calculated inside each time

    if (status == 0) status = removeBlockCommentary(line, lineLength);
    
    if (status == 0) status = buildLexemesSet(line, lexemesSet, lineLength);
    
    return status;
} 

/**
 * This function removes redundant spaces in a provided line.
 * 
 * @param line       provided text line
 * @param lineLenght lenght of the provided line
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int removeRedundantSpaces(char* line, int lineLength) {
    int shortener = 1, status = 0;
    for (int i = 0; i < lineLength - shortener; ++i) {
        if (line[i] == ' ' && line[i + 1] == ' ') {
            status = removeAtIndex(line, i, lineLength);
            i--;
            shortener++;
        } else if (i == 0 && line[i] == ' ') {
            status = removeAtIndex(line, i, lineLength);
            i--;
            shortener++;
        } else if (line[i] == ' ' && line[i + 1] == ';') {
            status = removeAtIndex(line, i, lineLength);
            i--;
            shortener++;
        }
    }

    return status;
}

/**
 * This function removes block commentary from a provided line.
 * 
 * @param line       provided text line
 * @param lineLenght lenght of the provided line
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int removeBlockCommentary(char* line, int lineLength) {

    return 0;
}

/**
 * This function builds a set of lexemes for provided line.
 * 
 * @param line       provided text line
 * @param lexemesSet storage memory for lexemes set 
 * @param lineLenght lenght of the provided line
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int buildLexemesSet(char* line, char** lexemesSet, int lineLength) {

    return 0;
}

/**
 * This function removes character from a line ant a specified index.
 * 
 * @param line       provided text line
 * @param index      index at which is the element to be removed 
 * @param lineLenght lenght of the provided line
 *
 * @returns 0 if success, -1 if something went wrong
 */
int removeAtIndex(char *line, int index, int lineLength) {
    int status = -1;

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
