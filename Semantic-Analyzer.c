#Joel Perkins
#Semantic Analyzer
%{

%}

	%token PROGRAM
	%token END
	%token LT
	%token LE
	%token EQ
	%token NE
	%token GT
	%token GE
	%token IF
	%token THEN
	%token ELSE
	%token ID
	%token NUMBER
	%token RELOP
	%token PRINT
	%token PRINTLN
	%token PROCEDURE
	%token WHILE
	%token DO
	%token BREAK
	%token ENDWHILE
	%token FUNCTION
	%token NOT
	%token INTEGER
	%token ENDIF
	%token FOR
	%token BEGINN
	%token RETURN
	%token AND
	%token MINUS
	%token ADD
	%token OR
	%token MULT
	%token DIV
	%token COMMA
	%token SEMICOLON
	%token LPAREN
	%token RPAREN
	%token ASSIGN
	%token COLON
	%token ADDOP
	%token MULTOP
	%token MOD
	%token STRING

        %nonassoc THEN
        %nonassoc ELSE
%%

program:    		PROGRAM identifier block
			;
	
block:			declarationPart statementPart 
			| statementPart
			;

declarationPart:	vardeclarationpart procandftndeclpart  
			| procandftndeclpart   
			| vardeclarationpart 
			;

vardeclarationpart:	variabledeclaration SEMICOLON 
			| variabledeclaration SEMICOLON varlist
			;
			
varlist:		variabledeclaration SEMICOLON varlist
			| variabledeclaration SEMICOLON
			;

variabledeclaration:	identifierlist COLON type
			;

procandftndeclpart:	proceduredeclaration procandftndeclpart 
			| functiondeclaration procandftndeclpart
			| proceduredeclaration 
			| functiondeclaration
			;

proceduredeclaration:	procedureheading procedurebody 
			;

procedurebody:		block
			;

functiondeclaration:	functionheading functionbody 
			;

functionbody:		block
			;

statementPart:		BEGINN statementsequence END 
			| BEGINN END
			; 

procedureheading:	PROCEDURE identifier formalparameterlist
			;

functionheading:	FUNCTION identifier formalparameterlist  COLON resulttype  
			;

resulttype:		typeidentifier
			;

formalparameterlist:	LPAREN RPAREN
			| LPAREN plist RPAREN 
			;

plist:			plist SEMICOLON formalparametersect | formalparametersect
			;

formalparametersect:	identifierlist COLON parametertype 
			;

parametertype:		typeidentifier 
			;

statementsequence:	slist
			;

slist:			slist statement SEMICOLON
			| statement SEMICOLON
			;

statement:		simplestatement 
			| structuredstatement 
			;
 
simplestatement:	assignmentstatement 
			| procedurestatement 
			| outputstatement 
			| returnstatement 
			;

assignmentstatement:	variable ASSIGN expression
			;

procedurestatement: 	procedureidentifier actualparameterlist
			;

returnstatement: 	RETURN expression 
			;

structuredstatement:	compoundstatement 
			| whilestatement 
			| ifstatement
			;
			
compoundstatement:	BEGINN statementsequence END 
                   	BEGINN END 
			;

whilestatement:		WHILE expression DO statementsequence ENDWHILE
			;

ifstatement:		IF expression THEN statementsequence ELSE statementsequence ENDIF
			| IF expression THEN statementsequence ENDIF
			;

actualparameterlist:	LPAREN aplist RPAREN
			| LPAREN RPAREN
			;
			
aplist:			aplist COMMA actualparameter| actualparameter
			;

actualparameter:	actualvalue 
			;

actualvalue:		expression 
			;


expression:		expression relationaloperator expression2
 			| expression2
			;

expression2:		expression2 additionoperator term 
 			| term
			;


term:			term multoperator factor 
			| factor
			;

factor:			variable 
			| NUMBER 
			| LPAREN expression RPAREN 
			| NOT factor
                        | functioncall
			;

functioncall: 		functionidentifier actualparameterlist
			;

relationaloperator:  	RELOP
			;

additionoperator:	ADDOP
			;

multoperator:		MULTOP
			;

variable:		variableidentifier 
			;

type:			typeidentifier 
			;

outputstatement: 	PRINTLN outputvalue  
			| PRINT outputvalue
			;

outputvalue:		expression | STRING
			;
 
identifier:  		ID
			;

variableidentifier:	identifier 
			;

typeidentifier:		INTEGER 
			;

procedureidentifier:	identifier
			;

functionidentifier:	identifier
			;

identifierlist:		identifierlist COMMA identifier | identifier 
			;

 
%%
	/* end of grammar */

#include <stdio.h>
#include <ctype.h>

char	*progname;
extern int	line;


int main(int argc, char *argv[])
{
	progname = argv[0];
	yyparse();
}


yyerror(char *s)	/* report compiletime error */
{
	warning(s, (char *)0);
}

execerror(char *s, char *t)	/* recover from runtime error */
{
	warning(s, t);
}


warning(char *s, char *t)	/* print warning message */
{
	fprintf(stderr, "%s: %s", progname, s);
	if (t && *t)
		fprintf(stderr, " %s", t);
	fprintf(stderr, " near line %d\n", line);
}
