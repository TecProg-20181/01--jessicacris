#include <stdio.h>

//Type of image que usa essas cores para reproduzir um espectro cromático
typedef struct _pixel {
    unsigned short int red;
    unsigned short int green;
    unsigned short int blue;
} Pixel;

typedef struct _image {
    // width and height = 512, with is the size of the matrix of image.
    // rgb = 3, whit is color of image.
    unsigned short int pixel[512][512][3];
    unsigned int width;
    unsigned int height;
} Image;

// This function stes the image color.
int max(int colorC1, int colorC2) {
    if (colorC1 > colorC2)
        return colorC1;
    return colorC1;
}

int pixel_equal(Pixel pixelp1, Pixel pixelp2) {
    if (pixelp1.red == pixelp2.red &&
        pixelp1.green == pixelp2.green &&
        pixelp1.blue == pixelp2.blue)
        return 1;
    return 0;
}


Image grey_scale(Image img) {
    for (unsigned int scale1 = 0; scale1 < img.height; ++scale1) {
        for (unsigned int scale2 = 0; scale2 < img.width; ++scale2) {
            int media = img.pixel[scale1][scale2][0] +
                        img.pixel[scale1][scale2][1] +
                        img.pixel[scale1][scale2][2];
            media /= 3;
            img.pixel[scale1][scale2][0] = media;
            img.pixel[scale1][scale2][1] = media;
            img.pixel[scale1][scale2][2] = media;
        }
    }

    return img;
}

void blur(unsigned int height, unsigned short int pixel[512][512][3], int filesize, unsigned int width) {
    for (unsigned int firstScale = 0; firstScale < height; ++firstScale) {
        for (unsigned int secondScale = 0; secondScale < width; ++secondScale) {
            Pixel media = {0, 0, 0};

            int lesser_height = (height - 1 > firstScale + filesize/2) ? firstScale + filesize/2 : height - 1;
            int min_width = (width - 1 > secondScale + filesize/2) ? secondScale + filesize/2 : width - 1;
            for(int token = (0 > firstScale - T/2 ? 0 : firstScale - T/2); token <= lesser_height; ++token) {
                for(int title = (0 > secondScale - T/2 ? 0 : secondScale - T/2); title <= min_width; ++title) {
                    media.red += pixel[token][title][0];
                    media.green += pixel[token][title][1];
                    media.blue += pixel[token][title][2];
                }
            }

            // printf("%u", media.red)
            //Código duplicado

            media.red /= filesize * filesize;
            media.green /= filesize * filesize;
            media.blue /= filesize * filesize;

            pixel[firstScale][secondScale][0] = media.red;
            pixel[firstScale][secondScale][1] = media.green;
            pixel[firstScale][secondScale][2] = media.blue;
        }
    }
}

Image rotate_90_right(Image img) {
    Image rotated;

    rotated.width = img.height;
    rotated.height = img.width;

    for (unsigned int firstColumn = 0, firstLine = 0; firstColumn < rotated.height; ++firstColumn, ++firstLine) {
        for (int SecondColumn = rotated.width - 1, secondLine = 0; SecondColumn >= 0; --SecondColumn, ++secondLine) {
            rotated.pixel[firstColumn][SecondColumn][0] = img.pixel[firstLine][secondLine][0];
            rotated.pixel[firstColumn][SecondColumn][1] = img.pixel[firstLine][secondLine][1];
            rotated.pixel[firstColumn][SecondColumn][2] = img.pixel[firstLine][secondLine][2];
        }
    }

    return rotated;
}

void invert_cores(unsigned short int pixel[512][512][3],
                    unsigned int width, unsigned int height) {
    for (unsigned int columnC1 = 0; columnC1 < height; ++columnC1) {
        for (unsigned int columnC2 = 0; columnC2 < width; ++columnC2) {
            pixel[columnC1][columnC2][0] = 255 - pixel[columnC1][columnC2][0];
            pixel[columnC1][columnC2][1] = 255 - pixel[columnC1][columnC2][1];
            pixel[columnC1][columnC2][2] = 255 - pixel[columnC1][columnC2][2];
        }
    }
}

Image cut_image(Image img, int lineN1, int lineN2, int width, int height) {
    Image cutting;

    cutting.width = width;
    cutting.height = height;

    for(int firstCutting = 0; firstCutting < height; ++firstCutting) {
        for(int secondCutting = 0; secondCutting < width; ++secondCutting) {
            cutting.pixel[firstCutting][secondCutting][0] = img.pixel[firstCutting + lineN1][secondCutting + lineN2][0];
            cutting.pixel[firstCutting][secondCutting][1] = img.pixel[firstCutting + lineN1][secondCutting + lineN2][1];
            cutting.pixel[firstCutting][secondCutting][2] = img.pixel[firstCutting + lineN1][secondCutting + lineN2][2];
        }
    }

    return cutting;
}

int main() {
    Image img;

    // read type of image
    char read_image[4];
    scanf("%s", read_image);

    // read width height and color of image
    int max_color;
    scanf("%u %u %d", &img.width, &img.height, &max_color);

    // read all pixels of image
    for (unsigned int columnC1 = 0; columnC1 < img.height; ++columnC1) {
        for (unsigned int columnC2 = 0; columnC2 < img.width; ++columnC2) {
            scanf("%hu %hu %hu", &img.pixel[columnC1][columnC2][0],
                                 &img.pixel[columnC1][columnC2][1],
                                 &img.pixel[columnC1][columnC2][2]);

        }
    }

    int number_options;
    scanf("%d", &number_options);

    for(int option1 = 0; option1 < number_options; ++option1) {
        int options;
        scanf("%d", &options);

        switch(option) {
            case 1: { // Escala de Cinza
                img = grey_scale(img);
                break;
            }
            case 2: { // Filtro Sepia
                for (unsigned int x = 0; x < img.height; ++x) {
                    for (unsigned int j = 0; j < img.width; ++j) {
                        unsigned short int pixel[3];
                        pixel[0] = img.pixel[x][j][0];
                        pixel[1] = img.pixel[x][j][1];
                        pixel[2] = img.pixel[x][j][2];

                        int p =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;
                        int menor_r = (255 >  p) ? p : 255;
                        img.pixel[x][j][0] = menor_r;

                        p =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;
                        menor_r = (255 >  p) ? p : 255;
                        img.pixel[x][j][1] = menor_r;

                        p =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;
                        menor_r = (255 >  p) ? p : 255;
                        img.pixel[x][j][2] = menor_r;
                    }
                }

                break;
            }
            case 3: { // Blur
                int tamanho = 0;
                scanf("%d", &tamanho);
                blur(img.height, img.pixel, tamanho, img.width);
                break;
            }
            case 4: { // Rotacao
                int quantas_vezes = 0;
                scanf("%d", &quantas_vezes);
                quantas_vezes %= 4;
                for (int j = 0; j < quantas_vezes; ++j) {
                    img = rotate90right(img);
                }
                break;
            }
            case 5: { // Espelhamento
                int horizontal = 0;
                scanf("%d", &horizontal);

                int width = img.width, height = img.height;

                if (horizontal == 1) width /= 2;
                else height /= 2;

                for (int i2 = 0; i2 < height; ++i2) {
                    for (int j = 0; j < width; ++j) {
                        int x = i2, y = j;

                        if (horizontal == 1) y = img.width - 1 - j;
                        else x = img.height - 1 - i2;

                        Pixel aux1;
                        aux1.red = img.pixel[i2][j][0];
                        aux1.green = img.pixel[i2][j][1];
                        aux1.blue = img.pixel[i2][j][2];

                        img.pixel[i2][j][0] = img.pixel[x][y][0];
                        img.pixel[i2][j][1] = img.pixel[x][y][1];
                        img.pixel[i2][j][2] = img.pixel[x][y][2];

                        img.pixel[x][y][0] = aux1.red;
                        img.pixel[x][y][1] = aux1.green;
                        img.pixel[x][y][2] = aux1.blue;
                    }
                }
                break;
            }
            case 6: { // Inversao de Cores
                inverter_cores(img.pixel, img.width, img.height);
                break;
            }
            case 7: { // Cortar Imagem
                int x, y;
                scanf("%d %d", &x, &y);
                int width, height;
                scanf("%d %d", &width, &height);

                img = cortar_imagem(img, x, y, width, height);
                break;
            }
        }

    }

    // print type of image
    printf("P3\n");
    // print width height and color of image
    printf("%u %u\n255\n", img.width, img.height); //Nomes com significados, método grande, duplucação

    // print pixels of image
    for (unsigned int i = 0; i < img.height; ++i) {
        for (unsigned int j = 0; j < img.width; ++j) {
            printf("%hu %hu %hu ", img.pixel[i][j][0],
                                   img.pixel[i][j][1],
                                   img.pixel[i][j][2]);

        }
        printf("\n");
    }
    return 0;
}
