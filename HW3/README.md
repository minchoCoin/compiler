# HW3 - Read and store data

## how to compile?
```
gcc data.c -o data
```
```
gcc data_upgrade.c -o data_upgrade
```
## functions
### data.c
Find and print integers and symbols from the input string
- SYM: symbol
- INT: integer
#### example
input
```
hello world 3abc qwerty123
compiler is fun 567 5678
cat1 5dog
```
output
```
(SYM, hello)
(SYM, world)
(INT, 3)
(SYM, abc)
(SYM, qwerty123)
(SYM, compiler)
(SYM, is)
(SYM, fun)
(INT, 567)
(INT, 5678)
(SYM, cat1)
(INT, 5)
(SYM, dog)
```
### data_upgrade.c
Find and print integers,floating values,booleans and symbols from the input string
- SYM: symbol
- INT: integer
- FLO: floating values
- BOO: boolean values(true, True, false, False)
#### example
input
```
hello world true false
true123 false8 3.14 pi
cat1 5dog 1.3x 56 78
```
output
```
(SYM, hello)
(SYM, world)
(BOO, True)
(BOO, False)
(SYM, true123)
(SYM, false8)
(FLO, 3.140000)
(SYM, pi)
(SYM, cat1)
(INT, 5)
(SYM, dog)
(FLO, 1.300000)
(SYM, x)
(INT, 56)
(INT, 78)
```