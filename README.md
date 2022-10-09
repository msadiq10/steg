# Image Steganography
Image steganography of PPM images to encode and decode messages in the red pixel field of the images using C.

## Functions and roles
- The getPPM function reads the PPM file and returns the structure (contents) of the ppm.
- The showPPM function display the PPM image using printf calls, in exactly the syntax of a PPM file.
- The encode function returns a copy of PPM image i with message text hidden in the red pixel field in successive pixels.
- The decode function returns the message hidden in the red pixel values of an encoded PPM image by comparison with the red pixel values of the original PPM image.

## Choice of data structures and algorithms
- Used a 2D array to allocate memory for the pixels from the ppm.
- Made use of a linked list using recursive struct "typedef struct Comment" to store the comments from the ppm.
## Limitations
- This program will not work if the ppm file contains comments that have more than 100 characters in one line.
