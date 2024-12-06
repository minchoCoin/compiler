# code for procedures
```
code(
    proc main(){
    int a;
    a=read();
    call write(a);
}
)
```
```
ssp 3
code(
    a=read();
    call write(a);
)
retp
```
```
ssp 3

code(a=read();)
code(call write(a);)

retp
```
```
ssp 3

code_L(a)
code_R(read();)
mst
code_R(a)
cup 1 l_write
retp
```
```
ssp 3

lda 3
mst
cup 0 l_read
sto
mst
code_L(a)
ind
cup 1 l_write
retp
```
```
ssp 3

lda 3
mst
cup 0 1_read
sto
mst
lda 3
ind
cup 1 1_write
retp
```

# references
[https://github.com/woogyun/tvm](https://github.com/woogyun/tvm)