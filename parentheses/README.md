# parentheses

```
gcc parentheses_bnf.c -o parentheses_bnf
```

```
gcc parentheses_ebnf.c -o parentheses_ebnf
```

# example
```
()
()()
(((((((
Syntax err
```

```
()()
()()()()()()
(())
)))))
Syntax err
```