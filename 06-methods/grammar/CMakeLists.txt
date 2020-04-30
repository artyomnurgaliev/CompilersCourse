project(GrammarFunctionCalls)

set(PARSER_TARGET "Parser${PROJECT_NAME}")
set(SCANNER_TARGET "Scanner${PROJECT_NAME}")
set(TREE_TARGET "Tree${PROJECT_NAME}")

set(PARSER_OUTPUT "BISON_${PARSER_TARGET}_OUTPUTS")
set(SCANNER_OUTPUT "FLEX_${SCANNER_TARGET}_OUTPUTS")


set(
        HEADERS
        driver.hh
        parser.hh
)

BISON_TARGET(
        ${PARSER_TARGET}
        parser.y
        ${PROJECT_SOURCE_DIR}/parser.cpp
        COMPILE_FLAGS --graph
        DEFINES_FILE ${PROJECT_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
        ${SCANNER_TARGET}
        scanner.l
        ${PROJECT_SOURCE_DIR}/scanner.cpp
)



ADD_FLEX_BISON_DEPENDENCY(${SCANNER_TARGET} ${PARSER_TARGET})

set(
        SOURCES
        ${${PARSER_OUTPUT}}
        ${${SCANNER_OUTPUT}}
        nterms_classes/Program.cpp
        nterms_classes/BinaryOperator.cpp
        nterms_classes/BinaryOperator.h
        nterms_classes/expressions/AccessToArrayElementExpression.cpp
        nterms_classes/expressions/AccessToArrayElementExpression.h
        nterms_classes/expressions/ArrayLengthExpression.cpp
        nterms_classes/expressions/ArrayLengthExpression.h
        nterms_classes/expressions/ArrayDefenitionExpression.cpp
        nterms_classes/expressions/ArrayDefenitionExpression.h
        nterms_classes/expressions/DefenitionExpression.cpp
        nterms_classes/expressions/DefenitionExpression.h
        nterms_classes/expressions/NotExpression.cpp
        nterms_classes/expressions/NotExpression.h
        nterms_classes/expressions/ParenthesisExpression.cpp
        nterms_classes/expressions/ParenthesisExpression.h
        nterms_classes/expressions/ThisExpression.cpp
        nterms_classes/expressions/ThisExpression.h
        nterms_classes/expressions/MethodInvocationExpression.cpp
        nterms_classes/expressions/MethodInvocationExpression.h
        nterms_classes/Lvalue/Lvalue.h
        nterms_classes/Lvalue/SimpleLvalue.cpp
        nterms_classes/Lvalue/SimpleLvalue.h
        nterms_classes/Lvalue/ArrayElementLvalue.cpp
        nterms_classes/Lvalue/ArrayElementLvalue.h
        nterms_classes/expressions/ExpressionList.cpp
        nterms_classes/expressions/ExpressionList.h
        nterms_classes/MethodInvocation.cpp
        nterms_classes/MethodInvocation.h
        nterms_classes/LocalVariableDeclaration.cpp
        nterms_classes/LocalVariableDeclaration.h
        nterms_classes/statements/Statement.h
        nterms_classes/statements/AssertStatement.cpp
        nterms_classes/statements/AssertStatement.h
        nterms_classes/statements/LocalVariableDeclarationStatement.cpp
        nterms_classes/statements/LocalVariableDeclarationStatement.h
        nterms_classes/statements/ScopeStatement.cpp
        nterms_classes/statements/ScopeStatement.h
        nterms_classes/statements/IfStatement.cpp
        nterms_classes/statements/IfStatement.h
        nterms_classes/statements/IfElseStatement.cpp
        nterms_classes/statements/IfElseStatement.h
        nterms_classes/statements/WhileStatement.cpp
        nterms_classes/statements/WhileStatement.h
        nterms_classes/statements/SoutStatement.cpp
        nterms_classes/statements/SoutStatement.h
        nterms_classes/statements/AssignmentStatement.cpp
        nterms_classes/statements/AssignmentStatement.h
        nterms_classes/statements/ReturnStatement.cpp
        nterms_classes/statements/ReturnStatement.h
        nterms_classes/statements/MethodInvocationStatement.cpp
        nterms_classes/statements/MethodInvocationStatement.h
        nterms_classes/statements/StatementList.cpp
        nterms_classes/statements/StatementList.h
        nterms_classes/TypeIdentifier.cpp
        nterms_classes/TypeIdentifier.h
        nterms_classes/type/ArrayType.cpp
        nterms_classes/type/ArrayType.h
        nterms_classes/type/SimpleType.cpp
        nterms_classes/type/SimpleType.h
        nterms_classes/type/Type.cpp
        nterms_classes/type/Type.h
        nterms_classes/FormalList.cpp
        nterms_classes/FormalList.h
        nterms_classes/declarations/VariableDeclaration.cpp
        nterms_classes/declarations/VariableDeclaration.h
        nterms_classes/declarations/MethodDeclaration.cpp
        nterms_classes/declarations/MethodDeclaration.h
        nterms_classes/declarations/Declaration.cpp
        nterms_classes/declarations/Declaration.h
        nterms_classes/declarations/DeclarationList.cpp
        nterms_classes/declarations/DeclarationList.h
        nterms_classes/class_declarations/ClassDeclaration.cpp
        nterms_classes/class_declarations/ClassDeclaration.h
        nterms_classes/class_declarations/ClassDeclarationList.cpp
        nterms_classes/class_declarations/ClassDeclarationList.h
        nterms_classes/class_declarations/MainClass.cpp
        nterms_classes/class_declarations/MainClass.h
        nterms_classes/Formal.cpp
        nterms_classes/Formal.h
        nterms_classes/expressions/BoolExpression.cpp
        nterms_classes/expressions/BoolExpression.h)

add_library(
        ${GRAMMAR_LIB}
        SHARED
        ${SOURCES}
)

target_include_directories(
        ${GRAMMAR_LIB} PRIVATE ${PROJECT_SOURCE_DIR}
)

target_include_directories(
        ${GRAMMAR_LIB} PRIVATE ${PROJECT_SOURCE_DIR}/..
)

target_include_directories(
        ${GRAMMAR_LIB} PRIVATE ${PROJECT_SOURCE_DIR}/../include
)