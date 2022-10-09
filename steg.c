#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/*
  Stores the RGB values of a pixel
*/
typedef struct Pixel{
  int red;
  int green;
  int blue;
} Pixel;
/* 
  Linked list to store the commments.
*/
typedef struct Comment{
  char line[100];           // stores the line of comment.
  struct Comment *next;  // next node
}Comment;

/*
  Stores the contents of a PPM file
*/
typedef struct PPM{
  /* TODO: Question 1 */
  char twolettercode[4];           // holds the magic number P3.
  Comment *head, *comments, *tail; // nodes of the comment linked list. 
  int width, height, maxval;       // storing width, height and maximum rgb value of a ppm.
  Pixel **pixels;
} PPM;

/*
  Returns the PPM struct from the file fd
*/
PPM* getPPM(FILE* fd){	
  PPM* ppm = (PPM*) malloc(sizeof(PPM));	
  /* TODO: Question 2a */
  int ch;                                                        // variable to store a character from the file fd.
  ppm->head=NULL;                                                // setting the head and tail node of comment linked list to NULL.
  ppm->tail=NULL;

  fgets(ppm->twolettercode, sizeof(ppm->twolettercode), fd);     // reading the magic value from the file.
  if(ppm->twolettercode[0]!='P'|| ppm->twolettercode[1]!='3'){   // checking if the magic number is valid.
    fprintf(stderr,"not ppm file\n");
    exit(1);
  }

  ch=fgetc(fd);                                                  // checking if the next character is #.
  while(ch=='#'){                                                // if its true then that means its a comment.
    ungetc(ch,fd);
    ppm->comments= (Comment* )malloc(sizeof(Comment));           // allocating memory for comments.
    fgets(ppm->comments->line, sizeof(ppm->comments->line), fd); // stores the line of comment into the comments->c.
    ppm->comments->next=NULL;                                    // setting comments->next to NULL.
    if(ppm->head==NULL)                                          
    {
      ppm->head=ppm->comments;                                   // if the comment linked list is empty,
    }                                                            // we add the comment to the head node.
    else
    {                                                            // else we traverse through the entire list of comments, 
      ppm->tail=ppm->head;                                       // and store the new comment in the tail node.
      while (ppm->tail->next!=NULL)
      {
        ppm->tail=ppm->tail->next;
      }
      ppm->tail->next=ppm->comments;
    }
    

    ch=fgetc(fd);   
  }
  ungetc(ch, fd);                                                
  fscanf(fd, "%d %d", &ppm->width,&ppm->height);                 // storing the width and height of the ppm.
  fscanf(fd, "%d", &ppm->maxval);                                // storing the maximum pixel value of the ppm.
  
  // Allocating memory for pixels.
  ppm->pixels = (Pixel**)malloc(ppm->height * sizeof(Pixel*));
  
  for (int i=0; i<ppm->height; i++)
  {
    ppm->pixels[i]= (Pixel*)malloc(ppm->width * sizeof(Pixel));
  }
  
  // Reading and storing r g b pixels in a 2D matrix format.
  for(int j=0; j<ppm->height; j++)
  {
    for(int k=0; k<ppm->width; k++)
    {
      fscanf(fd, "%d %d %d", &ppm->pixels[j][k].red, &ppm->pixels[j][k].green, &ppm->pixels[j][k].blue);
    }
  }
  return ppm;
}

/*
  Prints a PPM struct in the format of a PPM file
*/
void showPPM(PPM* ppm){

  /* TODO: Question 2b */
  
  printf("%s", ppm->twolettercode);

  ppm->comments=ppm->head;
  while (ppm->comments!=NULL)
  {
    printf("%s", ppm->comments->line);
    ppm->comments=ppm->comments->next;
  }
  
  printf("%d %d\n", ppm->width,ppm->height);
  printf("%d\n", ppm->maxval);
  for(int j=0; j<ppm->height; j++)
  {
    for(int k=0; k<ppm->width; k++)
    {
      printf("%d %d %d\n", ppm->pixels[j][k].red, ppm->pixels[j][k].green, ppm->pixels[j][k].blue);
    }
  }

}


/*
  Loads a file and returns it
  Prints error message and returns NULL if file can't be found or isn't a valid PPM
*/
PPM* loadPPMFromFile(char* filename){
  FILE* file;
  
  /* TODO: step 1, open the file */
  file= fopen(filename, "r");
  /* step 2: Check that file has been loaded correctly; show error otherwise*/
  if(file != NULL){
    PPM* ppm;
    /* TODO: step 3, get the PPM data from the file with the getPPM function */
    ppm= getPPM(file);
    if(ppm == NULL){
      /* TODO: step 4, display error if file cannot been parsed into a PPM struct*/
      fprintf(stderr,"steg: file cannot been parsed into a PPM struct \n");
    }

    /* TODO: step 5, close the file */
    fclose(file);
    /* step 6: return the PPM */
    return ppm;
  } else {
    fprintf(stderr,"steg: couldn't open %s\n",filename);
    exit(0);
    fclose(file);
    return NULL;
  }
}

/*
  Write a PPM to a file
*/
void writePPMtoFile(PPM* ppm){
  /* write the contents of the ppm to standard out (stdout) */

  /* TODO: write the headers first */

  /* TODO: then write the R G B pixel values */
}


/*
  Encodes text into red field of PPM
  Returns the encoded PPM
*/
PPM* encode(char* text, PPM* i){	

  /* TODO: Question 2c */ 
  int a = 0;
  int length= strlen(text);
  int j=rand()%(i->height);

  while(j<i->height){
    int k=0;
    while (k<i->width)
    {
      if(a<length-1 && i->pixels[j][k].red!=text[a])
      {
        i->pixels[j][k].red=text[a];
        a+=1;        
      }
      k+=1;
    }
    j+=1;
  }

  return i;
}


/*
  Compares 2 PPM structs and decodes the message hidden within
  Returns the decoded message if the images have the same dimensions
  Returns NULL otherwise
*/
char* decode(PPM* i1, PPM* i2){
  char* decodedMsg = malloc(sizeof(char));

  /* TODO: Question 2d */
  int i = 0;
  int j=0;
  
  while (j<i1->height)
  {
    int k=0;
    while (k<i1->width)
    {
      if(i1->pixels[j][k].red!=i2->pixels[j][k].red)
      {
        if(i1->pixels[j][k].green==i2->pixels[j][k].green)
        {
          if(i1->pixels[j][k].blue==i2->pixels[j][k].blue)
          {
            decodedMsg[i]=i2->pixels[j][k].red;
            i=i+1;
          }
        }
      }
      k+=1;
    }
    j+=1;
  }
  
  decodedMsg[i]='\0';
  return decodedMsg;
}

/* TODO: Question 3 */
int main(int argc, char* argv[]){
	
  /* check arguments */
  switch(argc) {
  case 2:
    /* TODO: not enough arguments, print an error message */
    fprintf(stderr,"not enough arguments \n");
    break;
  case 3:
    if(strcmp(argv[1], "e") == 0){ //Argument "e" - encode PPM
      PPM* ppm = loadPPMFromFile(argv[2]);
				
      /*Check that PPM is valid; continue if it is, exit otherwise */
      if(ppm != NULL){
        PPM* encodedPPM;
        /* TODO: encode the ppm with the text and assign to encodedPPM */
        char* encodeMsg;
        encodeMsg=malloc(sizeof(char));
        fprintf(stderr,"Enter message to be encoded: ");
        fgets(encodeMsg,ppm->height * ppm->width, stdin);
        encodedPPM= encode(encodeMsg, ppm);
        /*Check that no error occured*/
        if(encodedPPM == NULL){
          return EXIT_FAILURE;
        } else {
          /* TODO: print a confirmation that encoding was successful */
          fprintf(stderr,"Encode succesfull!! \n");
          /* TODO: print the PPM to standard output with showPPM */
          showPPM(encodedPPM);
          return EXIT_SUCCESS;				
        }
      } else {					
        return EXIT_FAILURE;
      }
    } else {
      fprintf(stderr, "Unrecognised or incomplete command line.\n");
      return EXIT_FAILURE;			
    }
    break;
  case 4:
    if(strcmp(argv[1], "d") == 0){ //Argument "d" - decode PPM
      PPM* comparisonPPM;
      PPM* encodedPPM;

      /* TODO: get comparison file filename from argv, load it with
         loadPPMFromFile then assign to comparisonPPM */
      comparisonPPM= loadPPMFromFile(argv[2]);
      /* TODO: get encoded file filename from argv, load it with
         loadPPMFromFile then assign to encodedPPM */
			encodedPPM= loadPPMFromFile(argv[3]);
      /*Check both PPMs are valid; continue if so, exit otherwise */
      if(comparisonPPM != NULL && encodedPPM != NULL){
        char* decodedMsg;
        
        /* TODO: decode the encodedPPM with the comparisonPPM and assign to decodedMsg */ 
        decodedMsg= decode(comparisonPPM, encodedPPM);
        /*Check that the message has been decoded*/
        if(decodedMsg != NULL){
          /* TODO: print a confirmation message that the message was decoded */ 
          fprintf(stderr, "Decode successfull!! \n");

          /* TODO: print the decoded message */
          fprintf(stderr,"Decoded message: %s \n", decodedMsg);
          return EXIT_SUCCESS;
        } else {
          return EXIT_FAILURE;
        }				
      } else {
        return EXIT_FAILURE;
      }			
    } else {
      fprintf(stderr, "Unrecognised or incomplete command line.\n\n");
      return EXIT_FAILURE;			
    }
    break;
  default:
    fprintf(stderr, "Unrecognised or incomplete command line.\n\n");
    return EXIT_FAILURE;
  }
}
