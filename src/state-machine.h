/*

   _____ _______    _______ ______   __  __          _____ _    _ _____ _   _ ______ 
  / ____|__   __|/\|__   __|  ____| |  \/  |   /\   / ____| |  | |_   _| \ | |  ____|
 | (___    | |  /  \  | |  | |__    | \  / |  /  \ | |    | |__| | | | |  \| | |__   
  \___ \   | | / /\ \ | |  |  __|   | |\/| | / /\ \| |    |  __  | | | | . ` |  __|  
  ____) |  | |/ ____ \| |  | |____  | |  | |/ ____ \ |____| |  | |_| |_| |\  | |____ 
 |_____/   |_/_/    \_\_|  |______| |_|  |_/_/    \_\_____|_|  |_|_____|_| \_|______|
                                                                                     
                                                                                     
2024-11-22 by GrindelfP.                                                                                     

This is a header file for the State Machine module.

The State Machine module contains an example of a determined state machine,
which is able to perform following operations on a provided text line: 
 - delete a block commentary,
 - delete redundant spaces,
 - build a lexeme set for a provided line.
*/

#ifndef FINITE_STATE_MACHINE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_STATE_MACHINE_H

#include <string.h>
#include "text-pair.h"

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
int stateMachine(char* line, char** lexemesSet);

/**
 * This function removes redundant spaces in a provided line.
 * 
 * @param line       provided text line
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int removeRedundantSpaces(char* line);

/**
 * This function removes block commentary from a provided line.
 * 
 * @param line       provided text line
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int removeBlockCommentary(char* line);

/**
 * This function builds a set of lexemes for provided line.
 * 
 * @param line       provided text line
 * @param lexemesSet storage memory for lexemes set 
 * 
 * @returns 0 if success, -1 if something went wrong
 */
int buildLexemesSet(char* line, char** lexemesSet);

/**
 * This function removes character from a line ant a specified index.
 * 
 * @param line       provided text line
 * @param index      index at which is the element to be removed 
 *
 * @returns 0 if success, -1 if something went wrong
 */
int removeAtIndex(char *line, int index);

#endif
