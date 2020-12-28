#include "main.h"

/*
 grammar 

expr : term ((plus | minus) term)* 
term : factor ((mul | div) factor)*  
factor : int | LPAREN expr RPAREN
*/

AST_t do_parse(struct Parser *this, char *text){
    /*
    첫 번째 토큰을 파싱한다. 그 후 파싱된 토큰을 분석하여 grammar대로 처리한다. 
    */
    this->lexer->lexer_init(this->lexer, text);
    //this->current_token = this->lexer->get_next_token(this->lexer); 
    while(true){
        Token *current_token = this->lexer->get_next_token(this->lexer);
        if(current_token == NULL){
            return NULL;
        }
        switch(current_token->type){
            case NODE_OP:
                printf("Token : NODE_OP - %c\n", current_token->op);
                break; 
            case NODE_INT:
                printf("Token : NODE_INT - %d\n", current_token->integer);
                break; 
            case NODE_EOF:
                printf("Token : NODE_EOF\n");
                return NULL;
                break;
            default:
                printf("test lexer error\n");
                return NULL;
                break;
    }
    }
    return NULL;
    //return program(this);
}

Node *factor(struct Parser *this){

}

Node *term(struct Parser *this){
    Node *node = this->factor(this); 
}

Node *expr(struct Parser *this){
    /*
        get_next_token 메소드를 이용하여 다음 토큰을 받아오고 
        grammar에 따라 재귀 하향 파싱을 진행한다.  
    */
   Token *current_token = NULL; 
    Node *node = this->term(this);
}

AST_t program(struct Parser *this){
    return expr(this);
}

void test_print(struct Parser *this){
    printf("test_print()\n");

}

void parser_error(struct Parser *this){
    fprintf(stderr, "Syntax Error!\n");
}
