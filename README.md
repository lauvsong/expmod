# expmod
Simple modular exponentation based on `openssl`

## Prerequisite
- openssl/bn.h

## Syntax
```
// r = a**e mod m
./expmod <a> <b> <m>
```

## Example
```
./expmod 5 117 19
a =  5
e =  117
m =  19
a**e mod m =  1
```