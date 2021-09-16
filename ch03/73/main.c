#include <stdio.h>

typedef enum {
    NEG,
    ZERO,
    POS,
    OTHER,
} range_t;

range_t find_range_asm(float x) {
    __asm__(
            "  vxorps %xmm1, %xmm1, %xmm1\n"
            "  vucomiss %xmm1, %xmm0\n"
            "  ja .L_POS\n"
            "  jb .L_NEG\n"
            "  je .L_ZERO\n"
            "  jmp .L_OTHER\n"
            ".L_NEG:\n"
            "  movl $0, %eax\n"
            "  jmp .L_Done\n"
            ".L_ZERO:\n"
            "  movl $1, %eax\n"
            "  jmp .L_Done\n"
            ".L_POS:\n"
            "  movl $2, %eax\n"
            "  jmp .L_Done\n"
            ".L_OTHER:\n"
            "  movl $3, %eax\n"
            ".L_Done:\n"
           );
}

range_t find_range(float x) {
    int result;
    if (x < 0)
        result = NEG;
    else if (x == 0)
        result = ZERO;
    else if (x > 0)
        result = POS;
    else
        result = OTHER;
    return result;
}

int main() {
    unsigned x = 0;

    do {
        float *fp = (float *)&x;
        float f = *fp;

        range_t fr = find_range(f);
        range_t fra = find_range_asm(f);

        if (fr != fra) {
            printf("%d != %d, found: %f, x: %d\n", fr, fra, f, x);
            return 0;
        }
    } while (++x);

}
