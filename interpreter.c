#include "main.h"


Interpreter *set_init(){
    Interpreter *interpreter = (Interpreter*)malloc(sizeof(Interpreter));  
    Parser *parser = (Parser*)malloc(sizeof(Parser)); 
    Lexer *lexer = (Lexer*)malloc(sizeof(Lexer)); 

    lexer->get_next_token = get_next_token; 
    lexer->skip_whitespace = skip_whitespace;
    lexer->lexer_error = lexer_error; 
    lexer->lexer_init = lexer_init; 
    lexer->make_token = make_token;
    lexer->make_integer = make_integer;
    lexer->increase_pos = increase_pos;

    parser->lexer = lexer;
    parser->do_parse = do_parse; 
    parser->parser_error = parser_error;
    parser->term = term; 
    parser->factor = factor; 
    parser->expr = expr;
    parser->program = program;
    parser->test_print = test_print;

    interpreter->parser = parser;
    interpreter->do_interpret = do_interpret; 

    return interpreter; 
}

bool_t do_interpret(struct Interpreter *this, char *text){
    AST_t ast = this->parser->do_parse(this->parser, text);
    return true;
}
