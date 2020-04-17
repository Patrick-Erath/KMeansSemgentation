#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "kmeans.h"
#include "kmeans.c"
#include <math.h>
int width_;
int height_;
double x[615440];
double *centers;
int   *cluster_final;

int* kmeans(
            int  dim,		                     // dimension of data 

            double *X,                        // pointer to data
            int   n,                         // number of elements
            
            int   k,                         // number of clusters
            double *cluster_centroid 		// initial cluster centroids
           );

uint8_t* read_in_image() {

	int width, height, bpp;

	uint8_t* grayscale_image = stbi_load("image2.jpeg", &width, &height, &bpp, 1);

	stbi_image_free(grayscale_image);

	width_ = width;
	height_ = height;

	return grayscale_image;
}


int main(int nargs, char **args)
{
	uint8_t* pointer = read_in_image();
	int size = width_ * height_;

	printf("SIZE : ");
	printf("%d", size);
	printf("    WIDTH : ");
	printf("%d", width_);
	printf("    HEIGHT : ");
	printf("%d", height_);


	double c[2] = {25.0, 50.0};
	int i;
	int k = 2;

	centers = calloc(k, sizeof(pointer));


	/* populate centroids */
	for (i = 0; i < k; i++)
	{
		centers[i] = (c[i]);
	}

	// convert data to double array
	double x[size];
	for(i=0; i< size; i++){
		//memcpy(r, pointer, sizeof(double));
		x[i] = (double) pointer[i];
	}

	/* run k-means */
	cluster_final = kmeans(1, x, size, k, centers);

	for(i=0; i<100; i++){
		printf("%d", cluster_final[i]);
	
	}
		printf("DONE");

	printf("%d", cluster_final[540000]);
	printf("%d", cluster_final[545000]);
	printf("%d", cluster_final[size-1]);
	// printf("%d", sizeof(cluster_final[size-1]));


	
/**
 * write will write the binary representation of the int, 
 * e.g. 8 bytes forming the 64 bits of an integral value, directly to the file. 
 * There is no conversion into ASCII or UTF8 "characters" as you'd expect when opening the file with a text editor. 
 * The integral value 2 in binary is 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x02,
 * and that's what you "see" in your file. A textual representation would be 0x32, i.e. the ASCII value of digit 2.
 * */
	FILE *f = fopen("data.txt", "w+");
	// On success
	if (f) {
        for(i=0; i<size; i++){
			 fprintf(f, "%d\n", cluster_final[i]);
		}
        fclose(f);
    }

	free(centers);

	return 0;
}


