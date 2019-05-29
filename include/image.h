#ifndef IMAGE_H__
#define IMAGE_H__

/// \brief structure that contains an image
typedef struct Image{
  unsigned char *pixelData;
  unsigned int width;
  unsigned int height;
  long taille;
}Image;


/// \brief allocate the memory for a new image
/// \param image: pointer on the image.
/// \param width: width of the required the image.
/// \param widthheight: height of the required the image.
/// \return EXIT_FAILURE in case of problem, else EXIT_SUCCESS.
int newImage(Image *image, unsigned int width, unsigned int height);

/// \brief release the image memory
/// \param image: pointer on the image.
void freeImage(Image *image);

/// \brief load an image with PPM (P6) file format.
/// \param image: pointer on the image to load.
/// \param filename: char array containing the filename of the image to load.
/// \return EXIT_FAILURE in case of problem, else EXIT_SUCCESS.
int loadImagePPM(Image *image, char *filename);

#endif
