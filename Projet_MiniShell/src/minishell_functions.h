#ifndef MINISHELL_FUNCTIONS_H
#define MINISHELL_FUNCTIONS_H

#include <stdbool.h>

#define MAX_TOKENS 64  // Définir MAX_TOKENS
#define SPECIAL_OPERATORS "&&|||><&"  // Définir SPECIAL_OPERATORS

bool is_background_command(char **tokens, int token_count);
void execute_command_in_background(char **argv);
void parse_and_execute(char *commande);
int executerLsPersonnalise(char *commande);

#endif // MINISHELL_FUNCTIONS_H
