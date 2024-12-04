#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <main.h>

//-----------------------------------------------------------------------------

int main ()
{
    code_t* code = (code_t*) calloc (1, sizeof (code_t));

    const char* line = "5+3*2-(7-6)+1*(1-1)$";

    int size = sizeof (code) / sizeof (char);

    code->line = (char*) line;
    code->ip = 0;
    code->size = size;

    int val = get_g (code);

    printf ("вычисленное значение = %d\n", val);

    free (code);

    return 0;
}

//-----------------------------------------------------------------------------

int get_g (code_t* code)
{
    int val = get_e (code);

    skip_spaces (code);

    if (code->line[code->ip] != '$')
    {
        syntax_error (code, __LINE__);
        code->ip++;
    }

    return val;
}

//-----------------------------------------------------------------------------

int get_e (code_t* code)
{
    int val = get_t (code);

    skip_spaces (code);

    while (code->line[code->ip] == '+' || code->line[code->ip] == '-')
    {
        char oper = code->line[code->ip];

        code->ip++;

        int val_2 = get_t (code);

        if (oper == '+') val += val_2;
        else val -= val_2;
    }

    return val;
}

//-----------------------------------------------------------------------------

int get_t (code_t* code)
{
    int val = get_p (code);

    skip_spaces (code);

    while (code->line[code->ip] == '*' || code->line[code->ip] == '/')
    {
        char oper = code->line[code->ip];

        code->ip++;

        int val_2 = get_p (code);

        skip_spaces (code);

        if (oper == '*') val *= val_2;
        else val /= val_2;
    }

    return val;
}

//-----------------------------------------------------------------------------

int get_n (code_t* code)
{
    int val = 0;

    skip_spaces (code);

    int old_ip = code->ip;

    while ('0' <= code->line[code->ip] && code->line[code->ip] <= '9')
    {
        val = val * 10 + code->line[code->ip] - '0';

        code->ip++;
    }

    if (old_ip == code->ip)
    {
        syntax_error (code, __LINE__);
    }

    return val;
}

//-----------------------------------------------------------------------------

int get_p (code_t* code)
{
    int val = 0;

    skip_spaces (code);

    if (code->line[code->ip] == '(')
    {
        code->ip++;

        val = get_e (code);

        if (code->line[code->ip] == ')') code->ip++;
        else syntax_error (code, __LINE__);
    }
    else
    {
        val = get_n (code);
    }

    return val;
}

//-----------------------------------------------------------------------------

void syntax_error (code_t* code, int line)
{
    printf ("syntax_error\n"
            "line = %d\n"
            "ip = %d\n"
            "simbol = %c\n", line, code->ip, code->line[code->ip]);

    assert (0);
}

//-----------------------------------------------------------------------------

void skip_spaces (code_t* code)
{
    while (code->line[code->ip] == ' ')
    {
        code->ip++;
    }
}

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
