#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// tokenize.c
//

typedef enum {
  TK_RESERVED,  // Keywords or punctuators
  TK_IDENT,     // Identifier
  TK_NUM,       // Integer literals
  TK_EOF,       // End-of-file markers
} TokenKind;

typedef struct Token Token;
struct Token {
  TokenKind kind;  // Token kind
  Token *next;     // Next Token
  int val;         // If kind is TK_NUM, its value
  char *str;       // Token string
  int len;         // Token length
};

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);

Token *consume_ident();
Token *tokenize();

extern Token *token;
extern char *user_input;

//
// parse.c
//

typedef enum {
  ND_ADD,     // +
  ND_SUB,     // -
  ND_MUL,     // *
  ND_DIV,     // /
  ND_EQ,      // ==
  ND_NE,      // !=
  ND_LT,      // <
  ND_LE,      // <=
  ND_ASSIGN,  // =
  ND_RETURN,  // "return"
  ND_LVAR,    // local variable
  ND_NUM,     // Integer
} NodeKind;

// AST node type
typedef struct Node Node;
struct Node {
  NodeKind kind;  // Node kind
  Node *next;     // Next node
  Node *lhs;      // Left-hand side
  Node *rhs;      // Right-hand side
  int val;        // Used if kind == ND_NUM
  char name;      // Used if kind == ND_LVAR
};

Node *program();

//
// codegen.c
//

void codegen(Node *node);
