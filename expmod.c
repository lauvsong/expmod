#include <stdio.h>
#include <openssl/bn.h>

// r = a**e mod m
int ExpMod(BIGNUM *r, const BIGNUM *a, const BIGNUM *e, BIGNUM *m)
{
    BIGNUM *res = BN_new();
    BIGNUM* rem = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *mul = BN_new();
    BIGNUM *two = BN_new();
    BN_CTX *ctx = BN_CTX_new();
    
    BN_one(res);
    BN_mod(mul, a, m, ctx);
    BN_copy(q, e);
    BN_dec2bn(&two, "2");

    while (!BN_is_zero(q)){
        BN_div(q, rem, q, two, ctx);

        if (BN_is_one(rem)){
            BN_mod_mul(res, res, mul, m, ctx);
        }

        BN_mod_mul(mul, mul, mul, m, ctx);
    }

    BN_copy(r, res);
    return 0;
}

void printBN(char *msg, BIGNUM * a)
{
    char * number_str = BN_bn2dec(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main (int argc, char *argv[])
{
	BIGNUM *a = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *m = BN_new();
	BIGNUM *res = BN_new();
    
    if(argc != 4){
        printf("usage: exp base exponent modulus\\n");
        return -1;
    }

    BN_dec2bn(&a, argv[1]);
    BN_dec2bn(&e, argv[2]);
    BN_dec2bn(&m, argv[3]);
    printBN("a = ", a);
    printBN("e = ", e);
    printBN("m = ", m);

    ExpMod(res,a,e,m);

    printBN("a**e mod m = ", res);

    if(a != NULL) BN_free(a);
    if(e != NULL) BN_free(e);
    if(m != NULL) BN_free(m);
    if(res != NULL) BN_free(res);

    return 0;
}