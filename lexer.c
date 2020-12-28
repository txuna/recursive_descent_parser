#include "main.h" 

const type_t SPACE =  ' '; 
const type_t PLUS = '+'; 
const type_t MINUS = '-'; 
const type_t MUL = '*'; 
const type_t DIV = '/'; 
const type_t LPAREN = '('; 
const type_t RPAREN = ')';

void lexer_init(struct Lexer *this, char *text){
    this->text = text; 
    this->current_pos = 0;
    this->current_char = this->text[this->current_pos]; 
}

/*
current_pos를 1 증가 시키면서 currernt_char = text[pos] 가지고 온다. 
pos가 text의 길이를 넘어설 경우 널 문자를 넣는다. 
*/
void increase_pos(struct Lexer *this){ 
    this->current_pos+=1;   
    
    if(this->current_pos > strlen(this->text)-1){   
        //printf("EXCEED\n");
        this->current_char = '\x00'; 
    }else{
        
        this->current_char = this->text[this->current_pos];
    }
    
}

Token *make_token(struct Lexer *this, type_t type, int value){
    Token *token = (Token*)malloc(sizeof(Token));
    switch(type){
        case NODE_OP:
            token->type = NODE_OP; 
            token->op = value; 
            break; 

        case NODE_INT:
            token->type = NODE_INT; 
            token->integer = value;
            break; 

        case NODE_EOF:
            token->type = NODE_EOF; 
            break; 
    }
    
    return token;
}

/*
current_char를 읽고 해당 문자에 대한 토큰을 return 한다. 
허나 읽은 문자가 공백이라면 계속 읽어나간다. 
만일 널 문자로라면 EOF Token을 던진다.
*/
Token *get_next_token(struct Lexer *this){
    Token *token = NULL;
    while(this->current_char != '\x00'){
        if(this->current_char == SPACE){
            this->skip_whitespace(this);
            continue;  
        } 
        else if(this->current_char == PLUS){
            this->increase_pos(this);
            return this->make_token(this, NODE_OP, PLUS);
        } 
        else if(this->current_char == MINUS){
            this->increase_pos(this);
            return this->make_token(this, NODE_OP, MINUS);
        } 
        else if(this->current_char == MUL){
            this->increase_pos(this);
            return this->make_token(this, NODE_OP, MUL);
        }
        else if(this->current_char == DIV){
            this->increase_pos(this);
            return this->make_token(this, NODE_OP, DIV);
        } 
        else if(this->current_char == LPAREN){
            this->increase_pos(this);
            return this->make_token(this, NODE_OP, LPAREN);
        } 
        else if(this->current_char == RPAREN){
            this->increase_pos(this);
            return this->make_token(this, NODE_OP, RPAREN);
        } 
        else if(this->current_char >='0' && this->current_char <= '9'){
            /*
                숫자 문자일 경우 다음 문자도 숫자인지 아닌지 확인후 하나의 숫자로 만들어 낸다.
            */
           int value =  make_integer(this); 
           return this->make_token(this, NODE_INT, value);

        }
        else{
            this->lexer_error(this, this->current_char);
            return NULL;
        }
    }
    return make_token(this, NODE_EOF, 0);
    /*
    token = (Token*)malloc(sizeof(Token)); 
    token->type = NODE_EOF; */
    return token; 
}
/*
숫자가 아닐때까지 계속 result를 더함
*/
int make_integer(struct Lexer *this){
    int result = 0;
    int cos = 1;
    while(this->current_char >='0' && this->current_char <= '9'){
        
        result += this->current_char - '0';
        result = result * int_pow(10, cos);
        //cos++;
        this->increase_pos(this);
    }
    return result/10;
}

/*
current_pos를 증가시켜면서 스페이스가 없을때 까지 증가시킨다. 
increase_pos함수 호출해야할듯
*/
void skip_whitespace(struct Lexer *this){
    while(this->current_char == SPACE){
        this->increase_pos(this);
    }
}

void lexer_error(struct Lexer *this, char error_ch){
    fprintf(stderr, "Incorrect Token about : %c\n", error_ch); 
}

int int_pow(int base, int exp){
    int result = 1;
    while (exp)
    {
        if (exp % 2)
           result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}