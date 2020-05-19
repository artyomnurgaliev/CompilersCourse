cmake_minimum_required(VERSION 3.0)
project(08-IrTreeCanonization)
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    execute_process(
            COMMAND brew --prefix bison
            RESULT_VARIABLE BREW_BISON
            OUTPUT_VARIABLE BREW_BISON_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_BISON EQUAL 0 AND EXISTS "${BREW_BISON_PREFIX}")
        message(STATUS "Found Bison keg installed by Homebrew at ${BREW_BISON_PREFIX}")
        set(BISON_EXECUTABLE "${BREW_BISON_PREFIX}/bin/bison")
    endif ()

    execute_process(
            COMMAND brew --prefix flex
            RESULT_VARIABLE BREW_FLEX
            OUTPUT_VARIABLE BREW_FLEX_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_FLEX EQUAL 0 AND EXISTS "${BREW_FLEX_PREFIX}")
        message(STATUS "Found Flex keg installed by Homebrew at ${BREW_FLEX_PREFIX}")
        set(FLEX_EXECUTABLE "${BREW_FLEX_PREFIX}/bin/flex")
        include_directories(${BREW_FLEX_PREFIX}/include)
    endif ()
endif ()

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


set(CURRENT_EXECUTABLE "${PROJECT_NAME}Executable")
set(GRAMMAR_LIB "${PROJECT_NAME}GrammarLib")
set(GRAMMAR_PROJECT "${PROJECT_NAME}GrammarProject")
set(IR_LIB "${PROJECT_NAME}IrLib")

set(
        SOURCES
        driver.cpp
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
        visitors/IrtreeBuildVisitor.h
        visitors/IrtreeBuildVisitor.cpp
        objects/objs/VariableObject.cpp objects/objs/VariableObject.h objects/objs/ArrayObject.cpp objects/objs/ArrayObject.h objects/PrimitiveSimpleType.cpp objects/PrimitiveSimpleType.h objects/PrimitiveArrayType.cpp objects/PrimitiveArrayType.h objects/PrimitiveType.cpp objects/PrimitiveType.h

        method-mechanisms/FrameTranslator.cpp method-mechanisms/FrameTranslator.h method-mechanisms/address/Address.h method-mechanisms/address/AddressInFrame.cpp method-mechanisms/address/AddressInFrame.h method-mechanisms/address/AddressInRegister.cpp method-mechanisms/address/AddressInRegister.h)

add_subdirectory(grammar)
add_subdirectory(irtree)

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

target_link_libraries(${CURRENT_EXECUTABLE} ${IR_LIB})



