#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "qrcodegen.h"

int main() {

    char text[500];

    printf("=== QR Code Generator ===\n");
    printf("Enter text or URL:\n");

    fgets(text, sizeof(text), stdin);

    uint8_t qr0[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];

    bool ok = qrcodegen_encodeText(
        text,
        tempBuffer,
        qr0,
        qrcodegen_Ecc_LOW,
        qrcodegen_VERSION_MIN,
        qrcodegen_VERSION_MAX,
        qrcodegen_Mask_AUTO,
        true
    );

    if (!ok) {
        printf("Failed to generate QR Code!\n");
        return 1;
    }

    int size = qrcodegen_getSize(qr0);

    FILE *fp = fopen("qrcode.pbm", "w");

    fprintf(fp, "P1\n");
    fprintf(fp, "%d %d\n", size, size);

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            fprintf(fp, "%d ",
                    qrcodegen_getModule(qr0, x, y));
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    printf("QR Code saved as qrcode.pbm\n");

    return 0;
}