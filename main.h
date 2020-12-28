#ifndef __HEADER_
#define __HEADER_
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>


typedef int type_t;
typedef int bool_t;

#define true 1 
#define false 0

#define NODE_OP 3
#define NODE_INT 4
#define PAREN 5  //LPAREN or RPAREN
#define NODE_EOF 6


/*
익명 구조체를 사용하여 좀 더 편하게 접근
*/

//type에는 OP인지 INT인지만 구별하고 실질적인 값은 union안에서 결정 
typedef struct Token{
    type_t type;    
    union{
        int integer; 
        char op; //op 문자가 들어간다. 
    }; 
}Token; 



/* Node struct으로 casting 해서 tree에 연결하지만 실제로 사용할떄는 해당 type을 보고 적절한 타입으로 캐스팅해야한다. */
/* return (AST_T)OpNode and (AST_T)IntNode */
typedef struct Node{
    Token *token;
}Node;

typedef struct IntNode{
    Node node;
}IntNode; 

typedef struct OpNode{
    Node node; 
    Token *lhs; 
    Token *rhs;
}OpNode; 



/*
type을 보고 struct Op를 쓸것인지, struct Num을 쓸것인지 결정한다. 
*/
/*
typedef struct Node{
    type_t type;
    union{
        struct Op{
            struct Node *lhs; 
            struct Node *rhs; 
            Token *op; 
        };
        struct Num{
            Token *num;
        };
    };
}Node;
*/

//추상 구문 트리 타입을 Node*형으로 지정한다. 
typedef Node* AST_t;

typedef struct Lexer{
    char *text;
    char current_char;  
    int current_pos;
    void (*lexer_init)(struct Lexer *this, char *text);
    void (*skip_whitespace)(struct Lexer *this);
    Token* (*get_next_token)(struct Lexer *this); 
    void (*increase_pos)(struct Lexer *this);
    int (*make_integer)(struct Lexer *this);
    Token* (*make_token)(struct Lexer *this, type_t type, int value);
    void (*lexer_error)(struct Lexer *this, char error_ch); 
}Lexer;

typedef struct Parser{
    Lexer *lexer;
    Token *current_token;
    void (*parser_init)(struct Parser* this, Lexer *lexer); 
    AST_t (*do_parse)(struct Parser *this, char *text);    

    Node* (*term)(struct Parser *this); 
    Node* (*factor)(struct Parser *this);
    Node* (*expr)(struct Parser *this);
    AST_t (*program)(struct Parser *this);

    void (*test_print)(struct Parser* this);
    void (*parser_error)(struct Parser *this);
}Parser;

typedef struct Interpreter{
    Parser *parser;  
    bool_t (*do_interpret)(struct Interpreter *this , char *text);
}Interpreter; 

/*
================ Interpreter function =======================
*/
void error(); 
Interpreter *set_init(); 
bool_t do_interpret(struct Interpreter *this, char *text);
int int_pow(int base, int exp);
/*
================ Lexer function ==============================
*/
Token *get_next_token(struct Lexer *this); 
void error(struct Lexer *this); 
void skip_whitespace(struct Lexer *this);
void lexer_error(struct Lexer *this, char error_ch); 
void lexer_init(struct Lexer *this, char *text);
Token *make_token(struct Lexer *this, type_t type, int value);
int make_integer(struct Lexer *this);
void increase_pos(struct Lexer *this);
/*
================= Parser function ============================
*/
AST_t do_parse(struct Parser *this, char *text);
void parser_error(struct Parser *this); 
Node *factor(struct Parser *this);
Node *term(struct Parser *this);
Node *expr(struct Parser *this);
AST_t program(struct Parser *this);
void test_print(struct Parser *this);
#endif