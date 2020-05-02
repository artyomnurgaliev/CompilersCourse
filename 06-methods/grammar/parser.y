%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class Driver;

    #include "visitors/forward_decl.h"
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    #include "visitors/elements.h"
    #include "nterms_classes/Program.h"

    #include <iostream>

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"
    SOUT "System.out.println"
    PSVM "public static void main"
    ASSERT "assert"
    RETURN "return"
    TRUE "true"
    FALSE "false"
    NEW "new"
    THIS "this"
    LBRACE "{"
    RBRACE "}"
    INT "int"
    BOOLEAN "boolean"
    VOID "void"
    SEMICOLON ";"
    ASSIGN "="
    CLASS "class"
    EXTENDS "extends"
    PUBLIC "public"
    LENGTH "length"
    IF "if"
    ELSE "else"
    WHILE "while"
    DOT "."
    NOT "!"
    AND "&&"
    OR "||"
    LESS "<"
    GREATER ">"
    EQUAL "=="
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    PERCENT "%"
    LPAREN "("
    RPAREN ")"
    LSQUAREBRACKET "["
    RSQUAREBRACKET "]"
    COMMA ","
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"

%nterm <Program*> program
%nterm <BinaryOperator*> binary_operator
%nterm <MainClass*> main_class
%nterm <ClassDeclarationList*> class_declarations
%nterm <ClassDeclaration*> class_declaration
%nterm <StatementList*> statements
%nterm <DeclarationList*> declarations
%nterm <Declaration*> declaration
%nterm <VariableDeclaration*> variable_declaration
%nterm <MethodDeclaration*> method_declaration
%nterm <Type*> type
%nterm <FormalList*> formals
%nterm <FormalList*> more_formals
%nterm <SimpleType*> simple_type
%nterm <ArrayType*> array_type
%nterm <TypeIdentifier*> type_identifier
%nterm <Expression*> expr
%nterm <LocalVariableDeclaration*> local_variable_declaration
%nterm <Statement*> statement
%nterm <Lvalue*> lvalue
%nterm <MethodInvocation*> method_invocation
%nterm <ExpressionList*> more_exprs

%printer { yyo << $$; } <*>;

%%
%start program;
program:
    main_class class_declarations { $$ = new Program($1, $2); driver.program = $$; };

main_class:
    "class" "identifier" "{" "public static void main" "(" ")" "{" statements "}" "}" { $$ = new MainClass($2, $8); };

class_declarations:
	%empty { $$ = new ClassDeclarationList(); } | class_declarations class_declaration {  $1->AddClassDeclaration($2); $$ = $1; };

class_declaration:
    "class" "identifier" "{" declarations "}" { $$ = new ClassDeclaration($2, $4); } |
    "class" "identifier" "extends" "identifier" "{" declarations "}" { $$ = new ClassDeclaration($2, $4, $6); };

declarations:
    %empty { $$ = new DeclarationList();  } |
    declarations declaration { $1->AddDeclaration($2); $$ = $1; };

declaration:
    variable_declaration { $$ = new Declaration($1); } | method_declaration { $$ = new Declaration($1); };

method_declaration:
    "public" type "identifier" "(" ")" "{" statements "}" { $$ = new MethodDeclaration($2, $3, $7); } |
    "public" type "identifier" "(" formals ")" "{" statements "}" { $$ = new MethodDeclaration($2, $3, $5, $8); };

variable_declaration:
    type "identifier" ";" { $$ = new VariableDeclaration($1, $2); };

formals:
	type "identifier" more_formals { $3->AddFormal(new Formal($1, $2)); $$ = $3;};

more_formals:
	%empty { $$ = new FormalList(); } |
	"," type "identifier" more_formals { $4->AddFormal(new Formal($2, $3)); $$ = $4;};

type:
	simple_type { $$ = new Type($1); } | array_type { $$ = new Type($1); };

simple_type:
    "int" { $$ = new SimpleType("int"); } |
    "boolean" { $$ = new SimpleType("boolean"); } |
    "void" { $$ = new SimpleType("void"); } |
     type_identifier { $$ = new SimpleType($1);};

array_type:
    simple_type "[" "]" { $$ = new ArrayType($1); };

type_identifier:
    "identifier" { $$ = new TypeIdentifier($1); };

statements:
	%empty { $$ = new StatementList(); } |
	statements statement { $1->AddStatement($2); $$ = $1; };

statement:
    	"assert" "(" expr ")" ";" { $$ = new AssertStatement($3); } |
        local_variable_declaration { $$ = new LocalVariableDeclarationStatement($1); } |
        "{" statements "}" { $$ = new ScopeStatement($2); } |
        "if"  "(" expr ")" statement { $$ = new IfStatement($3, $5); } |
        "if"  "(" expr ")" statement "else" statement { $$ = new IfElseStatement($3, $5, $7); } |
        "while"  "(" expr ")" statement { $$ = new WhileStatement($3, $5); } |
        "System.out.println" "(" expr ")" ";" { $$ = new SoutStatement($3); } |
        lvalue "=" expr ";" { $$ = new AssignmentStatement($1, $3); } |
        "return" expr ";" { $$ = new ReturnStatement($2); } |
        method_invocation ";" { $$ = new MethodInvocationStatement($1); };


local_variable_declaration:
	variable_declaration {  $$ = new LocalVariableDeclaration($1); };

method_invocation:
	expr "." "identifier" "(" ")" { $$ = new MethodInvocation($1, $3); } |
	expr "." "identifier" "(" expr more_exprs  ")" { $$ = new MethodInvocation($1, $3, $5, $6); };

more_exprs:
  %empty { $$ = new ExpressionList(); } |
  "," expr more_exprs { $3->AddExpression($2); $$ = $3; };

lvalue:
	"identifier" { $$ = new SimpleLvalue($1); }|
	 "identifier" "[" expr "]" { $$ = new ArrayElementLvalue($1, $3); } ;

expr:
	expr binary_operator expr {
	    $$ = new BinaryOperatorExpression($1, $2, $3);
	}  |
        expr "[" expr "]" { $$ = new AccessToArrayElementExpression($1, $3); }  |
        expr "." "length"  { $$ = new ArrayLengthExpression($1); } |
        "new" simple_type "[" expr "]" { $$ = new ArrayNewExpression($2, $4); } |
        "new" type_identifier "(" ")" { $$ = new NewExpression($2); } |
        "!" expr { $$ = new NotExpression($2); } |
        "(" expr ")" { $$ = new ParenthesisExpression($2); } |
        "identifier" { $$ = new IdentExpression($1); } | "number" { $$ = new NumberExpression($1); } |
        "this" { $$ = new ThisExpression(); } | "true" { $$ = new BoolExpression(true); } | "false" { $$ = new BoolExpression(false); } |
        method_invocation { $$ = new MethodInvocationExpression($1); };

%left "+" "-";
%left "*" "/" "%";

binary_operator:
	"&&" { $$ = new BinaryOperator("&&"); }  |
	"||" { $$ = new BinaryOperator("||"); }  |
	"<"  { $$ = new BinaryOperator("<"); }  |
	">"  { $$ = new BinaryOperator(">"); }  |
	"==" { $$ = new BinaryOperator("=="); }  |
	"+"  { $$ = new BinaryOperator("+"); }  |
	"-"  { $$ = new BinaryOperator("-"); }  |
	"*"  { $$ = new BinaryOperator("*"); }  |
	"/"  { $$ = new BinaryOperator("/"); }  |
	"%"  { $$ = new BinaryOperator("%"); };
%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}