# CompilersCourse

![Docker build](https://img.shields.io/docker/cloud/build/akhtyamovpavel/compilers_course_image) ![Docker Pulls](https://img.shields.io/docker/pulls/akhtyamovpavel/compilers_course_image)

Курс "Языки программирования и теории компиляции" ФПМИ МФТИ, 2 курс.

## Содержание

* [Грамматика](/reqs-draft.md)
* Список семинаров
    - [01. Лексический анализатор](/01-scanners)
    - [02. Синтаксический анализатор](/02-parsers)
    - [03. Построение AST-дерева](/04-visitors)
    - [04. Интерпретатор через Visitor](/04-visitors)
    - [05. Таблицы символов](/05-variable-scopes)
    - [06. Механизмы вызова функций](/06-function-calls)
    - [07. Построение дерева IR](/07-irtree-build)
    - [08. Оптимизация дерева IR](/08-irtree-optimizations)
* Список чекпоинтов
    - [01. Наивный интерпретатор](/milestones/01-naive-interpreter.md)
    - [02. AST-дерево](/milestones/02-ast-tree.md)
    - [03. Визиторы](/milestones/03-visitors.md)
    - [04. Scope-ы и системы типов](/milestones/04-scopes.md)
    - [05. Функции](/milestones/05-functions.md)
    - [06. Построение IR-дерева](/milestones/06-ir-builder.md)
    - [07. Канонизация IR-дерева](/milestones/07-ir-canonization.md)
    - [08. Построение блоков IR-дерева](/milestones/08-block-trace-formation.md)
    

### Сдача заданий

В таблице [akht.pl/compilers2020-checkpoints](https://akht.pl/compilers2020-checkpoints) необходимо записать фамилию, имя и пометить ячейку (вставить комментарий) с соответствующим чекпоинтом.

## Сборка Docker контейнера
Ссылка на image - https://hub.docker.com/r/akhtyamovpavel/compilers_course_image

Скачивание образа:
```
docker pull akhtyamovpavel/compilers_course_image
```
Сборка образа:
```
docker build -t akhtyamovpavel/compilers_course_image .
```
