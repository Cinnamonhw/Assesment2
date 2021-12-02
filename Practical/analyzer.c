/* front.c - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);
void expr(void);
void term(void);
void factor(void);
void error(void);
void program(void);
void block(void);
void statement(void);
void switchstmt(void);
void foreach(void);
void for_loop(void);
void while_loop(void);
void do_while(void);
void ifstmt(void);
void assignment(void);
void returnstmt(void);
void for_each(void);


/* Character classes */
#define LETTER 0 //[a-zA-Z]
#define DIGIT 1 //[0-9]
#define SINGLEQUOTE 2 //[\']
#define DOUBLEQUOTE 3 //[\"]
#define DECIMAL 4 //[\.]
#define UNKNOWN 99 //[^a-zA-Z0-9]

/* Token codes */
#define FLOAT_LIT 9
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define DECIMAL_POINT 27
#define SEMICOLON 28
#define MODULO 29
#define FOR_CODE 30
#define IF_CODE 31
#define ELSE_CODE 32
#define WHILE_CODE 33
#define DO_CODE 34
#define INT_CODE 35
#define FLOAT_CODE 36
#define SWITCH_CODE 37
#define VOID_CODE 38
#define MAIN_CODE 39
#define LEFT_BRACE 40
#define RIGHT_BRACE 41
#define GREATER_THAN 42
#define LESS_THAN 43
#define FOR_EACH 44
#define COLON 45
#define CASE 46
#define DEFAULT 47
#define SINGLE_QUOTE 48
#define BREAK 49




/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen("front.in", "r")) == NULL)
	 	printf("ERROR - cannot open front.in \n");
	 else {
	 	getChar();
	 do {
	 	lex();
    program();
   } while (nextToken != EOF);
     //expr();
	 }
	 return 0;
}



/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 nextToken = LEFT_PAREN;
			 break;
		 case ')':
			 addChar();
			 nextToken = RIGHT_PAREN;
			 break;
		 case '+':
			 addChar();
			 nextToken = ADD_OP;
			 break;
		 case '-':
			 addChar();
			 nextToken = SUB_OP;
			 break;
		 case '*':
			 addChar();
			 nextToken = MULT_OP;
			 break;
		 case '/':
			 addChar();
			 nextToken = DIV_OP;
			 break;
		 case '=':
			 addChar();
			 nextToken = ASSIGN_OP;
			 break;
		 case '.':
			 addChar();
			 nextToken = DECIMAL_POINT;
			 break;
     case ';':
       addChar();
       nextToken = SEMICOLON;
       break;
     case '%':
       addChar();
       nextToken = MODULO;
       break;
     case '{':
       addChar();
       nextToken = LEFT_BRACE;
       break;
     case '}':
       addChar();
       nextToken = RIGHT_BRACE;
       break;
     case '>':
       addChar();
       nextToken = GREATER_THAN;
       break;
     case '<':
       addChar();
       nextToken = LESS_THAN;
       break;
     case ':':
       addChar();
       nextToken = COLON;
       break;
     case '\'':
       addChar();
       nextToken = SINGLE_QUOTE;
       break;
     default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar))
		 	charClass = DIGIT;
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void) {
	 lexLen = 0;
	 getNonBlank();
	 switch (charClass) {
		/* Identifiers */
		 case LETTER:
			 addChar();
			 getChar();
        while (charClass == LETTER || charClass == DIGIT) {
         addChar();
         getChar();
        }
        if (strcmp(lexeme, "void") == 0) {
          nextToken = VOID_CODE;
        }
        else if (strcmp(lexeme, "main") == 0) {
          nextToken = MAIN_CODE;
        }
        else if (strcmp(lexeme, "for") == 0) {
          nextToken = FOR_CODE;
        }
        else if(strcmp(lexeme ,"if") == 0) {
          nextToken = IF_CODE;
        }
        else if(strcmp(lexeme ,"else") == 0) {
          nextToken = ELSE_CODE;
        }
        else if(strcmp(lexeme ,"while") == 0) {
          nextToken = WHILE_CODE;
        }
        else if(strcmp(lexeme ,"do") == 0) {
          nextToken = DO_CODE;
        }
        else if(strcmp(lexeme ,"int") == 0) {
          nextToken = INT_CODE;
        }
        else if(strcmp(lexeme, "float") == 0) {
          nextToken = FLOAT_CODE;
        }
        else if(strcmp(lexeme ,"switch") == 0) {
          nextToken = SWITCH_CODE;
        }
        else if(strcmp(lexeme, "foreach") == 0) {
          nextToken = FOR_EACH;
        }
        else if(strcmp(lexeme, "case") == 0) {
          nextToken = CASE;
        }
        else if(strcmp(lexeme, "default") == 0) {
          nextToken = DEFAULT;
        }
        else if(strcmp(lexeme, "break") == 0) {
          nextToken = BREAK;
        }
        else {
          nextToken = IDENT;
        }

			 break;
		/* Integer & Float literals */
		 case DIGIT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
       nextToken = INT_LIT;
       if (nextChar == 'u' || nextChar == 'U' || nextChar == 'l' || nextChar == 'L') {
         addChar();
         getChar();

         if(nextChar == 'l' || nextChar == 'L') {
           addChar();
           getChar();

         }
         nextToken = INT_LIT;
       }
       if (nextChar == 'e' || nextChar == 'E') {
         addChar();
         getChar();

         if (nextChar == '-') {
           addChar();
           getChar();
           while (charClass == DIGIT) {
             addChar();
             getChar();
           }
         }
         nextToken = FLOAT_LIT;
       }

       if (charClass == UNKNOWN && nextChar == '.'){
         addChar();
				 getChar();
         while (charClass == DIGIT) {
				  addChar();
				  getChar();
			   }
         if (nextChar == 'e' || nextChar == 'E' || nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L') {
          addChar();
          getChar();
          while (charClass == DIGIT) {
            addChar();
            getChar();

          }
         }
          if (nextChar == '-') {
            addChar();
            getChar();
            while (charClass == DIGIT) {
              addChar();
              getChar();
            }
          }
         nextToken = FLOAT_LIT;
       }

		 	break;
    case DECIMAL:
          addChar();
				  getChar();
          if (charClass == DIGIT){
            addChar();
				    getChar();
            while (charClass == DIGIT) {
				      addChar();
				      getChar();
			      }
            nextToken = FLOAT_LIT;
          }
          else {
              nextToken = DECIMAL_POINT;
          }
     break;
		/* Parentheses and operators */
		 case UNKNOWN:
      if (nextChar == '-') {
        addChar();
        getChar();
        if (charClass == DIGIT) {
          addChar();
          getChar();
          while (charClass == DIGIT) {
            addChar();
            getChar();
          }
          if (charClass == UNKNOWN && nextChar == '.'){
            addChar();
				    getChar();
            while (charClass == DIGIT) {
				    addChar();
				    getChar();
			      }
            if (nextChar == 'e' || nextChar == 'E' || nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L') {
              addChar();
              getChar();
              while (charClass == DIGIT) {
                addChar();
                getChar();
              }
              if (nextChar == '-') {
                addChar();
                getChar();
                while (charClass == DIGIT) {
                  addChar();
                  getChar();
                }
              }
            }
          }
        } else {
          nextToken = SUB_OP;
        }
      }
      else if (nextChar == '.') {
        addChar();
        getChar();
        if (charClass == DIGIT) {
        addChar();
        getChar();
        while (charClass == DIGIT) {
          addChar();
          getChar();
        }
        if (nextChar == 'e' || nextChar == 'E' || nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L') {
          addChar();
          getChar();
          while (charClass == DIGIT) {
            addChar();
            getChar();
          }
          if (nextChar == '-') {
            addChar();
            getChar();
          }
        }
        nextToken = FLOAT_LIT;
        }
        else {
          nextToken = DECIMAL_POINT;
        }
      }
      else {
			    lookup(nextChar);
			    getChar();
      }

			 break;
			/* EOF */
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 } /* End of switch */
	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
	 return nextToken;
} /* End of function lex */

/* program
Parses strings in the language generated by the rule:
<program> -> VOID MAIN ( ) <block>
*/
void program() {
  printf("Enter <program>\n");
  if (nextToken != VOID_CODE)
    error();
  else {
    lex();
    if (nextToken != MAIN_CODE)
      error();
    else {
      lex();
      if (nextToken != LEFT_PAREN)
        error();
      else {
        lex();
        if (nextToken != RIGHT_PAREN)
          error();
        lex();
        block();
      }
    }
  }
  printf("Exit <program>\n");
}

/*block
Parses string in the language generated by the rule:
<block> -> { { <statement> ; } }
*/
void block(void) {
  printf("Enter <block>\n");
  if (nextToken != LEFT_BRACE)
 	error();
  else {
	lex();
 	  while (nextToken != RIGHT_BRACE) {
      statement();
      if (nextToken != SEMICOLON)
        error();
      lex();
    }
    if (nextToken != RIGHT_BRACE) 
      error();
    lex();
  }
  printf("Exit <block>\n");
}

/* statement
Parses strings in the language generated by the rule:
<statement> -> <switchstmt> | <foreach> | <forloop> | <whileloop> | <do-while> | <ifstmt> | <assignment> ; | <return> ;
*/
void statement(void) {
  printf("Enter <statement>\n");
  //lex();
  if (nextToken == SWITCH_CODE) {
    switchstmt();
  }
  if (nextToken == FOR_EACH) {
    for_each();
  }
  else if (nextToken == FOR_CODE) {
    for_loop();
  }
  else if (nextToken == IF_CODE) {
    ifstmt();
  }
  else if (nextToken == WHILE_CODE) {
    while_loop();
  }
  else if (nextToken == DO_CODE) {
    do_while();
  }
  else {
    lex();
    if (nextToken == IDENT) {
    assignment();
    }
    printf("Exit <statement>\n");
  }
  

}
// /* switchstmt
// Parses strings in the language generated by the rule:
// <switchstmt> --> switch (<expr>) { case: <statement> ; default: <statement> ; }
// */
void switchstmt(void) {
  printf("Enter <switchstmt>\n");
  if (nextToken != SWITCH_CODE) 
    error();
  else {
    lex();
    if (nextToken != LEFT_PAREN)
      error();
    else {
      lex();
      expr();
      if (nextToken != RIGHT_PAREN) 
        error();
      else {
        lex();
        if (nextToken != LEFT_BRACE)
          error();
        else {
          lex();
          if (nextToken != CASE) {
            error();
          }
          else {
            lex();
            expr();
            if (nextToken != COLON) {
              error();
            }
            else {
              lex();
              statement();
              if (nextToken != SEMICOLON) {
                error();
              }
              else {
                lex();
                if (nextToken != BREAK) {
                  error();
                }
                else {
                  lex();
                  if (nextToken != SEMICOLON) {
                    error();
                  }
                  else {
                    lex();
                    if (nextToken != DEFAULT) {
                      error();
                    }
                    else {
                      lex();
                      if (nextToken != COLON) {
                        error();
                      }
                      else {
                        lex();
                        statement();
                        if (nextToken != SEMICOLON) {
                          error();
                        }
                        else {
                          lex();
                          if (nextToken != BREAK) {
                            error();
                          }
                          else {
                            lex();
                            if (nextToken != SEMICOLON) {
                              error();
                            }
                            else {
                              lex();
                              if (nextToken != RIGHT_BRACE) {
                                error();
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  printf("Exit <switchstmt>\n");
}

/* for_each 
Parses strings in the language generated by the rule:
<for_each> -> foreach ( <expr> ) { <statement> }
*/
void for_each(void) {
  printf("Enter <for_each>\n");
  if (nextToken != FOR_EACH) {
    error();
  }
  else {
    lex();
    if (nextToken != LEFT_PAREN) {
      error();
    }
    else {
      lex();
      expr();
      if (nextToken != RIGHT_PAREN) {
        error();
      }
      else {
        lex();
        statement();
      }
    }
  }
  printf("Exit <for_each>\n");
}

/* for_loop
Parses strings in the language generated by the rule:
<for_loop> -> for '(' [ <expression> ] ';' [ <expression> ] ';' [ <expression> ] ')' <statement>
*/
void for_loop() {
  printf("Enter <for_loop>\n");
  if (nextToken != FOR_CODE) {
    error();
  }
  else {
    lex();
    if (nextToken != LEFT_PAREN) {
      error();
    }
    else {
      lex();
      expr();
      if (nextToken != SEMICOLON) {
        error();
      }
      else {
        lex();
        expr();
        if (nextToken != SEMICOLON) {
          error();
        }
        else {
          lex();
          expr();
          if (nextToken != RIGHT_PAREN) {
            error();
          }
          else {
            lex();
            //block();
            statement();
          }
        }
      }
    }
  }
  printf("Exit <for_loop>\n");
}

/* while_loop
Parses strings in the language generated by the rule: 
<while_loop> --> while '(' <expr> ')' <statement>
*/
void while_loop() {
  printf("Enter <while_loop>\n");
  if(nextToken != WHILE_CODE) {
    error();
  }
  else {
    lex();
    if(nextToken != LEFT_PAREN) {
      error();
    }
    else {
      lex();
      expr();
      if (nextToken != RIGHT_PAREN) {
        error();
      }
      else {
        lex();
        statement();
      }
    }
  }
  printf("Exit <while_loop>\n");
}

/*do_while
Parses strings in the language generated by the rule:
<do_while> -> do { <statement> } while ( <expr> )
*/
void do_while(void) {
  printf("Enter <do_while>\n");
  if (nextToken != DO_CODE){
    error();
  }
  else {
    lex();
    statement();
    lex();
    if ( nextToken != WHILE_CODE) {
      error();
    }
    else {
      while_loop();
    }

  }
  printf("Exit <do_while>\n");
}

/* ifstmt
Parses strings in the language generated by the rule:
<ifstmt> -> if '(' <expresssion> ')' <statement> [ else <statement> ]
*/
void ifstmt(void) {
  printf("Enter <ifstmt>\n");
  if (nextToken != IF_CODE) 
    error();
  else {
    lex();
    if (nextToken != LEFT_PAREN) {
      error();
    }
    else {
      lex();
      expr();
      if (nextToken != RIGHT_PAREN) {
        error();
      }
      else if (nextToken == LEFT_BRACE) {
          block();
      }
      else {
        lex();
        //block();
        statement();
        if (nextToken == ELSE_CODE) {
          lex();
          //statement();
        }
      }
    }
  }
  printf("Exit <ifstmt>\n");
}

/* assignment
Parses strings in the language generate by the rule:
<assignment> -> id = <expr> ;
*/
void assignment(void) {
  printf("Enter <assignment>\n");
  //lex();
  if (nextToken != IDENT)
    error();
    else {
      lex();
      if (nextToken != ASSIGN_OP)
        error();
        else {
          lex();
          expr();
          if (nextToken != SEMICOLON)
            error();
        }
    }
  printf("Exit <assignment>\n");
}

/* expr
 Parses strings in the language generated by the rule:
 <expr> -> <term> {(+ | -) <term>}
 */
void expr(void) {
   //printf("Enter <expr>\n");
   /*Parse the first term */
	 term();
   /* As long as the next token is + or -, get
	 the next token and parse the next term */
	 while (nextToken == ADD_OP || nextToken == SUB_OP || nextToken == GREATER_THAN || nextToken == ASSIGN_OP || nextToken == LESS_THAN) {
		 lex();
		 term();
	 }
   //printf("Exit <expr>\n");
}

/* term
 Parses strings in the language generated by the rule:
 <term> -> <factor> {(* | /) <factor>}
 */
void term(void) {
   //printf("Enter <term>\n");
   /* Parse the first factor */
	 factor();
   /* As long as the next token is *, /, or % get the
	 next token and parse the next factor */
	 while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MODULO || nextToken == IDENT) {
		 lex();
		 factor();
	 }
   //printf("Exit <term>\n");
}

/* factor
 Parses strings in the language generated by the rule:
 <factor> -> id | int_constant | ( <expr> )
 */
void factor(void) {
     //printf("Enter <factor>\n");
     /* Determine which RHS */
	 if (nextToken == IDENT || nextToken == INT_LIT || nextToken == FLOAT_LIT || nextToken == ADD_OP || nextToken == SINGLE_QUOTE)
     /* Get the next token */
		 lex();
     /* If the RHS is ( <expr> ), call lex to pass over the
		 left parenthesis, call expr, and check for the right
		 parenthesis */
	 else { if (nextToken == LEFT_PAREN) {
		 lex();
		 expr();
		 if (nextToken == RIGHT_PAREN)
		 	lex();
		 else
		 	error();
		 }
     /* It was not an id, an integer literal, or a left
		 parenthesis */
		 else
		 error();
	 }
	 //printf("Exit <factor>\n");
}
void error(void){
 printf("You have an error in your language, please try again\n");
 exit(1);
}
