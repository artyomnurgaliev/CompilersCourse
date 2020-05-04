project(MethodCalls)
set(CURRENT_EXECUTABLE "${PROJECT_NAME}Executable")
set(GRAMMAR_LIB "${PROJECT_NAME}GrammarLib")
set(GRAMMAR_PROJECT "${PROJECT_NAME}GrammarProject")

set(
    SOURCES
    driver.cpp
    visitors/Interpreter.cpp
        visitors/PrintVisitor.cpp
    symbol_table/Symbol.cpp
        symbol_table/ScopeLayer.cpp
    symbol_table/ScopeLayerTree.cpp
    objects/ClassType.h
    objects/ClassType.cpp
        objects/MethodType.h
    objects/MethodType.cpp
        objects/ObjectType.h
    objects/ObjectType.cpp
        visitors/SymbolTreeVisitor.cpp
        visitors/MethodCallVisitor.cpp
        visitors/MethodCallVisitor.h
    method-mechanisms/Frame.cpp
    method-mechanisms/Frame.h
    method-mechanisms/FunctionTable.cpp
    method-mechanisms/FunctionTable.h
        method-mechanisms/ClassStorage.cpp
        method-mechanisms/ClassStorage.h
        visitors/TemplateVisitor.h
        visitors/TemplateVisitor.cpp

        objects/objs/VariableObject.cpp objects/objs/VariableObject.h objects/objs/ArrayObject.cpp objects/objs/ArrayObject.h objects/PrimitiveSimpleType.cpp objects/PrimitiveSimpleType.h objects/PrimitiveArrayType.cpp objects/PrimitiveArrayType.h objects/PrimitiveType.cpp objects/PrimitiveType.h)

add_subdirectory(grammar)

add_executable(
    ${CURRENT_EXECUTABLE}
    main.cpp
    ${SOURCES}
)


target_include_directories(
    ${CURRENT_EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}
)
target_include_directories(
    ${CURRENT_EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/grammar
)


target_link_libraries(${CURRENT_EXECUTABLE} ${GRAMMAR_LIB})



