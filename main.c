/*
* Project Photopobre
*   Jéssica Cristina
*   13/0142930
*
*/

    #include <stdio.h>

    //Type of image that uses these colors to reproduce a chromatic spectrum
    typedef struct _pixel {
        unsigned short int red;
        unsigned short int green;
        unsigned short int blue;
    } Pixel;

    typedef struct _image {
         // width and height = 512, with is the size[] of the matrix of image.
        // rgb = 3, whit is color of image.
       // 0 -> red
      // 1 -> green
      // 2 -> blue
        unsigned short int pixel[512][512][3];
        unsigned int width;
        unsigned int height;
    } Image;

  // This function stes the image color.
  int max(int a, int b) {
      if (a > b){
          return a;
      }else {
          return b;
      }
}

  int min(int a, int b) {
      if (a < b){
          return b;
      }else{
        return a;
      }
  }

      int pixel_equal(Pixel pixelp1, Pixel pixelp2) {
        if (pixelp1.red == pixelp2.red && pixelp1.green == pixelp2.green && pixelp1.blue == pixelp2.blue){
            return 1;

          }else {
            return 0;
          }
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

                int shorter_height;
                int token;
                int title;
                int r_blur;
                int min_w = 0;
                min_w = min(token-1,r_blur + filesize/2);
                 for(int token = max(0, firstScale - secondScale); token <= min_w; ++token){
                    }

                    int firstScale;
                    int secondScale;
                    int min_h = 0;
                    min_h = min(title - 1,r_blur + filesize/2);
                    for(int title = max(0, firstScale - secondScale); title <= min_h; ++title){

                        media.red += pixel[token][title][0];
                        media.green += pixel[token][title][1];
                        media.blue += pixel[token][title][2];
                      }

                    // printf("%u", media.red)

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
        int rotate_90_right;

        rotated.width = img.height;
        rotated.height = img.width;

        for (unsigned int firstRotated = 0, firstLine = 0; firstRotated < rotated.height; ++firstRotated, ++firstRotated) {
            for (int secondRotated = rotated.width - 1, secondLine = 0; secondRotated >= 0; --secondRotated, ++secondRotated) {
                rotated.pixel[firstRotated][secondRotated][0] = img.pixel[firstLine][secondLine][0];
                rotated.pixel[firstRotated][secondRotated][1] = img.pixel[firstLine][secondLine][1];
                rotated.pixel[firstRotated][secondRotated][2] = img.pixel[firstLine][secondLine][2];
            }
        }

        return rotated;
    }

    void invert_colors(unsigned short int pixel[512][512][3],
                        unsigned int width, unsigned int height) {
        for (unsigned int colorsC1 = 0; colorsC1 < height; ++colorsC1) {
            for (unsigned int colorsC2 = 0; colorsC2 < width; ++colorsC2) {
                pixel[colorsC1][colorsC2][0] = 255 - pixel[colorsC1][colorsC2][0];
                pixel[colorsC1][colorsC2][1] = 255 - pixel[colorsC1][colorsC2][1];
                pixel[colorsC1][colorsC2][2] = 255 - pixel[colorsC1][colorsC2][2];
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

    Image mirror ( Image img) {
      int horizontal = 0;
      scanf("%d", &horizontal);

      int width = img.width;
      int height = img.height;

      if (horizontal == 1){
        width /= 2;

      }else {
        height /= 2;
      }

      for (int auxA1 = 0; auxA1 < height; ++auxA1) {
          for (int auxA2 = 0; auxA2 < width; ++auxA2) {

              int x = auxA1;
              int y = auxA2;

              if (horizontal == 1){
                y = img.width - 1 - auxA2;

              }else {
                x = img.height - 1 - auxA1;
              }

              Pixel aux1;
              aux1.red = img.pixel[auxA1][auxA2][0];
              aux1.green = img.pixel[auxA1][auxA2][1];
              aux1.blue = img.pixel[auxA1][auxA2][2];

              img.pixel[auxA1][auxA2][0] = img.pixel[x][y][0];
              img.pixel[auxA1][auxA2][1] = img.pixel[x][y][1];
              img.pixel[auxA1][auxA2][2] = img.pixel[x][y][2];

              img.pixel[x][y][0] = aux1.red;
              img.pixel[x][y][1] = aux1.green;
              img.pixel[x][y][2] = aux1.blue;
          }
      }
      return img;
    }

Image Sepia_filter ( Image img){
  for (unsigned int columnC1 = 0; columnC1 < img.height; ++columnC1) {
      for (unsigned int columnC2 = 0; columnC2 < img.width; ++columnC2) {
          unsigned short int pixel[3];
          pixel[0] = img.pixel[columnC1][columnC2][0];
          pixel[1] = img.pixel[columnC1][columnC2][1];
          pixel[2] = img.pixel[columnC1][columnC2][2];

          int image_pixel =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;

          int lesser_range = (255,image_pixel);

           if (255 >  image_pixel) {
             lesser_range = image_pixel;
           }else {
             lesser_range = 255;
          }
          img.pixel[columnC1][columnC1][0] = lesser_range;

          image_pixel =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;

          if (255 >  image_pixel){
            lesser_range = image_pixel;
          }else{
             lesser_range = 255;
          }
          img.pixel[columnC1][columnC2][1] = lesser_range;

          image_pixel =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;

          if (255 >  image_pixel) {
            lesser_range = image_pixel;
          }else{
             lesser_range = 255;
          }
          img.pixel[columnC1][columnC2][2] = lesser_range;
      }

  }
  return img;
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
        int option;
        scanf("%d", &number_options);

        for(int option1 = 0; option1 < number_options; ++option1) {
            int options;
            scanf("%d", &options);

            switch(option) {
                case 1: { // Green Scale
                    img = grey_scale(img);
                    break;
                }
                case 2: { // Sepia filter

                    img = Sepia_filter (img);
                    break;
                }
                case 3: { // Blur
                    int size_blur = 0;
                    scanf("%d", &size_blur);
                    blur(img.height, img.pixel, size_blur, img.width);
                    break;
                }
                case 4: { // Rotated
                    int  how_many = 0;
                    scanf("%d", &how_many);
                    how_many %= 4;
                    for (int j = 0; j < how_many; ++j) {
                        img = rotate_90_right(img);
                    }
                    break;
                }
                case 5: { // Mirroring

                img = mirror (img);

                    break;
                }
                case 6: { // Invert colors
                    invert_colors(img.pixel, img.width, img.height);
                    break;
                }
                case 7: { // Curt Image
                    int line1;
                    int line2;

                    scanf("%d %d", &line1, &line2);

                    int width;
                    int height;
                    scanf("%d %d", &width, &height);

                    img = cut_image(img, line1, line2, width, height);
                    break;
                }
            }

        }

        // print type of image
        printf("read_image\n");
        // print width height and color of image
        printf("%u %u\n255\n", img.width, img.height);

        // print pixels of image
        for (unsigned int columnC1 = 0; columnC1 < img.height; ++columnC1) {
            for (unsigned int columnC2 = 0; columnC2 < img.width; ++columnC2) {
                printf("%hu %hu %hu ", img.pixel[columnC1][columnC2][0],
                                       img.pixel[columnC1][columnC2][1],
                                       img.pixel[columnC2][columnC1][2]);

            }
            printf("\n");
        }
        return 0;
    }
