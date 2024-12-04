#ifndef MAIN_H
#define MAIN_H

typedef struct code
{
    int size;
    int ip;
    char* line;
} code_t;

/*

*/
void    syntax_error    (code_t* code, int line);

/*

*/
int     get_g           (code_t* code);

/*

*/
int     get_e           (code_t* code);

/*

*/
int     get_t           (code_t* code);

/*

*/
int     get_n           (code_t* code);

/*

*/
int     get_p           (code_t* code);

/*

*/
void    skip_spaces     (code_t* code);

#endif //MAIN_H
