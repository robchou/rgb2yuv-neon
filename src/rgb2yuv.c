#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void BGR888ToYUV444(unsigned char *yuv, unsigned char *bgr, int pixel_num)
{
    int i;
    for (i = 0; i < pixel_num; ++i) {
        uint8_t r = bgr[i * 3];
        uint8_t g = bgr[i * 3 + 1];
        uint8_t b = bgr[i * 3 + 2];

        uint8_t y = 0.299 * r + 0.587 * g + 0.114 * b;
        uint8_t u = -0.169 * r - 0.331 * g + 0.5 * b + 128;
        uint8_t v = 0.5 * r - 0.419 * g - 0.081 * b + 128;

        yuv[i * 3] = y;
        yuv[i * 3 + 1] = u;
        yuv[i * 3 + 2] = v;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("usage: test <infile> <outfile> <width> <height>\n");
        return -1;
    }

    FILE *infile = fopen(argv[1], "rb");
    FILE *outfile = fopen(argv[2], "wb");

    if (!infile) {
        fprintf(stderr, "error: failed to open infile %s\n", argv[1]);
        exit(2);
    }

    if (!outfile) {
        fprintf(stderr, "error: failed to open outfile %s\n", argv[2]);
        exit(2);
    }

    int width = atoi(argv[3]);
    int height = atoi(argv[4]);

    printf("with x height is %d x %d\n", width, height);

    int nmemb = (width * height) * sizeof(uint8_t) * 3;

    printf("nmemb is %d\n", nmemb);

    uint8_t *rgb_buffer = (uint8_t*)malloc(nmemb);
    uint8_t *yuv_buffer = (uint8_t*)malloc(nmemb);

    fread(rgb_buffer, sizeof(uint8_t), nmemb, infile);
    BGR888ToYUV444(yuv_buffer, rgb_buffer, width * height);

    fwrite(yuv_buffer, 1, nmemb, outfile);

    if (!infile) {
        fclose(infile);
    }

    if (!outfile) {
        fclose(outfile);
    }

    if (!yuv_buffer) {
        free(yuv_buffer);
    }

    if (!rgb_buffer) {
        free(rgb_buffer);
    }

    return 0;
}
