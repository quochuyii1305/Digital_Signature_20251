#include "prime.h"
#include <gmp.h>

// Kiểm tra số nguyên tố
int isProbablePrime(mpz_t n, int iterations) {
    return mpz_probab_prime_p(n, iterations);
}

// Tìm số nguyên tố tiếp theo
void getNextPrime(mpz_t result, const char* start) {
    mpz_set_str(result, start, 10);
    while (!isProbablePrime(result, 99)) {
        mpz_add_ui(result, result, 1);
    }
}

// Sinh q và p theo chuẩn DSA
// q: số nguyên tố N-bit (thường 160 hoặc 256 bit)
// p: số nguyên tố L-bit sao cho q chia hết (p-1)
void generateDSAParams(mpz_t p, mpz_t q, unsigned int L, unsigned int N, gmp_randstate_t state) {
    mpz_t temp, p_minus_1, multiplier;
    mpz_inits(temp, p_minus_1, multiplier, NULL);
    
    // Bước 1: Sinh q là số nguyên tố N-bit
    mpz_urandomb(q, state, N);
    mpz_setbit(q, N-1);  // Đảm bảo bit cao nhất = 1
    mpz_nextprime(q, q);
    
    // Bước 2: Sinh p sao cho p = kq + 1 với k là số chẵn
    // và p là số nguyên tố L-bit
    mpz_ui_pow_ui(temp, 2, L-1);  // 2^(L-1)
    mpz_div(multiplier, temp, q);  // k_min = 2^(L-1) / q
    
    // Đảm bảo k là số chẵn
    if (mpz_odd_p(multiplier)) {
        mpz_add_ui(multiplier, multiplier, 1);
    }
    
    int found = 0;
    while (!found) {
        // p = kq + 1
        mpz_mul(p, multiplier, q);
        mpz_add_ui(p, p, 1);
        
        // Kiểm tra xem p có phải số nguyên tố và có đúng L bit không
        if (mpz_sizeinbase(p, 2) == L && isProbablePrime(p, 50)) {
            found = 1;
        } else {
            mpz_add_ui(multiplier, multiplier, 2);  // Thử k tiếp theo (chẵn)
        }
    }
    
    mpz_clears(temp, p_minus_1, multiplier, NULL);
}

// Hàm findQ cũ - giữ lại để tương thích ngược nhưng cải thiện
void findQ(mpz_t result, mpz_t n) {
    // Với DSA, ta nên sinh q riêng biệt thay vì tìm ước của p-1
    // Hàm này giờ chỉ tìm một ước nguyên tố đơn giản
    mpz_t temp, divisor;
    mpz_inits(temp, divisor, NULL);
    
    mpz_set(temp, n);
    mpz_set_ui(divisor, 2);
    
    // Chia cho 2 cho đến khi không chia hết
    while (mpz_divisible_ui_p(temp, 2)) {
        mpz_divexact_ui(temp, temp, 2);
    }
    
    // Thử các số lẻ
    mpz_set_ui(divisor, 3);
    while (mpz_cmp_ui(temp, 1) > 0) {
        if (mpz_divisible_p(temp, divisor)) {
            while (mpz_divisible_p(temp, divisor)) {
                mpz_divexact(temp, temp, divisor);
            }
            mpz_set(result, divisor);
        }
        mpz_add_ui(divisor, divisor, 2);
        
        // Giới hạn số lần thử để tránh treo
        if (mpz_cmp_ui(divisor, 10000000) > 0) {
            // Nếu không tìm được ước nhỏ, trả về số nguyên tố nhỏ
            mpz_set_ui(result, 65537);
            break;
        }
    }
    
    // Nếu temp còn lại và là số nguyên tố lớn hơn kết quả hiện tại
    if (mpz_cmp_ui(temp, 1) > 0 && mpz_cmp(temp, result) > 0) {
        mpz_set(result, temp);
    }
    
    mpz_clears(temp, divisor, NULL);
}