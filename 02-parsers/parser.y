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
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

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
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <int> expr
%nterm <int> binary_operator
%nterm <std::string> lvalue

%printer { yyo << $$; } <*>;

%%
%start program;
program:
    main_class class_declarations;

main_class:
    "class" "identifier" "{" "public static void main" "(" ")" "{" statements "}" "}" {};

class_declarations:
	%empty {} | class_declarations class_declaration {};

class_declaration:
    "class" "identifier" "{" declarations "}" {} |
    "class" "identifier" "extends" "identifier" "{" declarations "}" {};

declarations:
    %empty {} |
    declarations declaration;

declaration:
    variable_declaration {} | method_declaration {};

method_declaration:
    "public" type "identifier" "(" ")" "{" statements "}" {} |
    "public" type "identifier" "(" formals ")" "{" statements "}" {};

variable_declaration:
    type "identifier" ";" {};

formals:
	type "identifier" more_formals {};

more_formals:
	%empty {} |
	"," type "identifier" more_formals {};

type:
	simple_type {} | array_type {};

simple_type:
    "int" {} | "boolean" {} | "void" {} | type_identifier {};

array_type:
    simple_type "[" "]" {};

type_identifier:
    "identifier" {};

statements:
	%empty {} |
	statements statement {};

statement:
    	"assert" "(" expr ")" ";" { if ($3 == 1) { std::cout << true; } else { std::cout << false; } } |
        local_variable_declaration {} |
        "{" statements "}" {} |
        "if"  "(" expr ")" statement {} |
        "if"  "(" expr ")" statement "else" statement {} |
        "while"  "(" expr ")" statement {} |
        "System.out.println" "(" expr ")" ";" { std::cout << $3 << std::endl; } |
        lvalue "=" expr ";" { driver.variables[$1] = $3; } |
        "return" expr ";" { driver.result = $2; } |
        method_invocation ";" {};


local_variable_declaration:
	variable_declaration {};

method_invocation:
	expr "." "identifier" "(" ")" {} |
	expr "." "identifier" "(" expr more_exprs  ")" {};

more_exprs:
  %empty {} |
  "," expr more_exprs {};

lvalue:
	"identifier" { $$ = $1; }
	 | "identifier" "[" expr "]" { } ;

expr:
	expr binary_operator expr {
	switch ($2) {
		case 1: $$ = $1 && $3; break;
		case 2: $$ = $1 || $3; break;
		case 3: $$ = $1 < $3; break;
		case 4: $$ = $1 > $3; break;
		case 5: $$ = $1 == $3; break;
		case 6: $$ = $1 + $3; break;
		case 7: $$ = $1 - $3; break;
		case 8: $$ = $1 * $3; break;
		case 9: $$ = $1 / $3; break;
		case 10: $$ = $1 % $3; break;
	};
	}  |
        expr "[" expr "]" { }  |
        expr "." "length"  { } |
        "new" simple_type "[" expr "]" {} |
        "new" type_identifier "(" ")" {} |
        "!" expr { $$ = !($2); } |
        "(" expr ")" { $$ = $2; } |
        "identifier" { $$ = driver.variables[$1]; } | "number" { $$ = $1; } |
        "this" {} | "true" { $$ = 1; } | "false" { $$ = 0; } |
        method_invocation {};

%left "+" "-";
%left "*" "/" "%";

binary_operator:
	"&&" { $$ = 1; }  |
	"||" { $$ = 2; }  |
	"<"  { $$ = 3; }  |
	">"  { $$ = 4; }  |
	"==" { $$ = 5; }  |
	"+"  { $$ = 6; }  |
	"-"  { $$ = 7; }  |
	"*"  { $$ = 8; }  |
	"/"  { $$ = 9; }  |
	"%"  { $$ = 10; };
%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}