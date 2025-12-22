#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include "prime.h"
#include "generator.h"
#include "dsa.h"

int main() {
    // Khởi tạo random state
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    
    // Khai báo biến
    mpz_t p, q, g, x, y, r, s, hashVal;
    
    mpz_inits(p, q, g, x, y, r, s, hashVal, NULL);
    
    // Sinh các tham số công khai
    unsigned int L_bits, N_bits;

    printf("Nhap do dai cua so nguyen to p (L-bit, vi du: 512, 640, 1024, 2048): ");
    scanf("%u", &L_bits);
    
    // Chọn kích thước N cho q dựa trên L
    if (L_bits <= 1024) {
        N_bits = 160;  // DSA chuẩn cho L <= 1024
    } else if (L_bits <= 2048) {
        N_bits = 224;  // DSA chuẩn cho L = 2048
    } else {
        N_bits = 256;  // DSA chuẩn cho L = 3072
    }
    
    printf("Dang sinh tham so DSA (L=%u, N=%u)...\n", L_bits, N_bits);
    printf("Qua trinh nay co the mat vai giay...\n");
    
    // Sinh p và q theo chuẩn DSA
    generateDSAParams(p, q, L_bits, N_bits, state);
    
    // Sinh generator g
    getGen(g, p, q, state);
    
    printf("\nSimulation of Digital Signature Algorithm\n");
    printf("\nGlobal public key components are:\n");
    gmp_printf("\nP (%u bits): 0x%Zx\n", L_bits, p);
    gmp_printf("\nQ (%u bits): 0x%Zx\n", N_bits, q);
    gmp_printf("\nG is: 0x%Zx\n", g);
    
    // Sinh khóa riêng x
    mpz_urandomm(x, state, q);
    while (mpz_cmp_ui(x, 0) == 0) {
        mpz_urandomm(x, state, q);
    }
    
    // Tính khóa công khai y = g^x mod p
    mpz_powm(y, g, x, p);
    
    // Sinh hash giả lập (kích thước bằng q để đảm bảo tính bảo mật)
    mpz_urandomb(hashVal, state, N_bits);
    mpz_mod(hashVal, hashVal, q);
    
    printf("\nSecret information:\n");
    gmp_printf("X (private) is: 0x%Zx\n", x);
    gmp_printf("Y (public) is: 0x%Zx\n", y);
    gmp_printf("H (mdhash) is: 0x%Zx\n", hashVal);
    
    // Ký số
    printf("\nGenerating digital signature:\n");
    DSA_sign(hashVal, p, q, g, x, r, s);
    gmp_printf("R is: 0x%Zx\n", r);
    gmp_printf("S is: 0x%Zx\n", s);
    
    // Xác thực chữ ký
    printf("\nVerifying digital signature:\n");
    bool verified = DSA_verify(hashVal, r, s, p, q, g, y);
    
    if (verified) {
        gmp_printf("\nSuccess: Digital signature is verified!\nR = 0x%Zx\n", r);
    } else {
        printf("\nError: Incorrect digital signature\n");
    }
    
    // Giải phóng bộ nhớ
    mpz_clears(p, q, g, x, y, r, s, hashVal, NULL);
    gmp_randclear(state);
    
    return 0;
}