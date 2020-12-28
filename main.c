#include "main.h" 

const int SIZE = 100;

int main(int argc, char **argv){    
    size_t len = 0;
    char buffer[100] = {0, }; 
    Interpreter *interpreter = NULL;
    interpreter = set_init();
    
    while(true){
        printf("Interpreter> "); 
        fgets(buffer, SIZE-1, stdin); 
        buffer[strlen(buffer)-1] = '\0'; //remove newline 
        if(!strcmp(buffer, "quit")){
            printf("Interpreter> Success Exit!\n");
            break;
        }
        if(!interpreter->do_interpret(interpreter, buffer)){
            fprintf(stderr, "ERROR\n");
        }
        memset(buffer, 0, SIZE);
    }
    free(interpreter->parser->lexer); 
    free(interpreter->parser); 
    free(interpreter);
}



