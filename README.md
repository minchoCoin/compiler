# compiler
Assignments of compiler lecture(2024 fall)

# index
## HW2
- analyzing simple assembly code(focus on stack frame of functions)
## HW3
- parsing string into integer, floating values, symbol, boolean values

## HW4
- parsing string into integer, symbol, and string type.
    - The string values are character and number enclosed in double quotation marks.

## HW5
- parsing string into integer, symbol, string values, and Pair type.
    - It is possible that pair have pair type.

## HW6
- parsing string into integer, symbol, and List
    - parsing list to pair((8 3) => (8 . (3 . NIL)))
## HW7
- count words and special signs('(',')','.',',','-','_','!'@' etc) from one-line string.
    - with Lex
    - without Lex(just writing c code)
## HW8
- parsing string into integer, symbol, string, and list using lex
    - parsing list to pair((8 3) => (8 . (3 . NIL)))
## HW9
- making simple calculator through parsing list.
    - ex) (+ 3 5) => 8, (/ +10 -5) => -2, (* 10 10) => 100

## HW10
- get right parse of arithmetic formula

```
23 - 5 / 2
F -> n
T -> F
E -> T
F -> n
T -> F
F -> n
T -> T / F
E -> E - T
```

## HW11
- Basic Arithmetic Operations Program
    - using flex and bison
```
23 / 5 - 7 * -12
88
```

## HW12
- make abstract syntax tree(AST)
```
11 + 12 * 13
Op(+)
    Int(11)
    Op(*)
        Int(12)
        Int(13)
```