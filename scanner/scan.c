#include "defs.h"
#include "data.h"
#include "decl.h"

//Read next character, put back the character if read "too far" into the stream
static int next(void) {
    int c;

    if (Putback) {
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);
    if (c == '\n') Line++; // To be able to return line number in debug messages
    return c;
}

// Put back unwanted character
static void putback(int c) {
    Putback = c;
}

// Function to skip whitespace and return the first relevant character
static int skip(void) {
    int c;

    c = next();
    while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
        c = next();
    }
    return (c);
}
// Returns position of c in s, -1 if c is not in s
static int chrpos(char *s, int c) {
    char *p;

    p = strchr(s, c);

    return (p ? p - s : -1);
}

// Scan integer literals, return the value
static int scanint(int c) {
    int k, val = 0;

    while ((k = chrpos("0123456789", c)) >= 0) {
        val = val * 10 + k;
        c = next();
    }

    putback(c); // Above loop stops if c is not in the set "0123456789" -> put c back into the stream to be consumed later
    return val;
}

int scan(struct token *t) {
    int c;

    c = skip();

    switch(c) {
        case EOF:
            t->token = T_EOF;
            return (0);
        case '+':
            t->token = T_PLUS;
            break;
        case '-':
            t->token = T_MINUS;
            break;
        case '*':
            t->token = T_STAR;
            break;
        case '/':
            t->token = T_SLASH;
            break;
        default:
            if (isdigit(c)) { // T_INTLIT
                t->intvalue = scanint(c);
                t->token = T_INTLIT;
                break;
            }
            printf("Unrecognised character %c on line %d\n", c, Line);
            exit(1);
    }

    return(1);
}