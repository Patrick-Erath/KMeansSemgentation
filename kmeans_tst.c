#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include "stb_image.h"
#include "kmeans.h"
#include "kmeans.c"
#include <math.h>
#include <time.h>

int WIDTH_GL;
int HEIGHT_GL;
double x[615440];
double *centers;
int   *cluster_final;

int* kmeans(
            int  dim,		                  // Data dimensions
            double *x,                        // Data img_pointer
            int   n,                          // Number of elements
            int   k,                          // Number of clusters
            double *cluster_centroid 		  // Initial cluster centroids
           );

uint8_t* read_image(char image_path[]) {
	int width, height, bpp;

	// Read in image as grayscale (1 channel)
	uint8_t* grayscale_image = stbi_load(image_path, &width, &height, &bpp, 1);
	stbi_image_free(grayscale_image);

	// Set global size variables
	WIDTH_GL = width;
	HEIGHT_GL = height;

	// Return image
	return grayscale_image;
}


int main(int nargs, char **args)
{
	// Image Path goes heres
	char IMAGE_PATH[] = "./Images/image.jpeg";
	char *PATH_POINTER;
	PATH_POINTER = IMAGE_PATH;

	// Get pointer to 1D-Image array
	uint8_t* img_pointer = read_image(PATH_POINTER);
	int size = WIDTH_GL * HEIGHT_GL;

	// Print Image params
	printf("IMAGE PARAMS: \n");
	printf("SIZE : ");
	printf("%d", size);
	printf("    WIDTH : ");
	printf("%d", WIDTH_GL);
	printf("    HEIGHT : ");
	printf("%d", HEIGHT_GL);
	printf("\n");

	// Randomly init k-cluster centers
	int k_clusters = 2;
	int i;
	srand(time(NULL)); 
	centers = calloc(k_clusters, sizeof(img_pointer));
	for(i=0; i<k_clusters; i++){
		centers[i] = rand() % 255;
	}
	printf("\n 1. Randomly Initalized k-clusters");

	// Convert data to double array
	double x[size];
	for(i=0; i< size; i++){
		x[i] = (double) img_pointer[i];
	}

	// Run K-means on image
	cluster_final = kmeans(1, x, size, k_clusters, centers);

	// Write the segmented image file as a binary representation of an int
	FILE *f = fopen("./Data/data.txt", "w+");
	if (f) {
        for(i=0; i<size; i++){
			 fprintf(f, "%d\n", cluster_final[i]);
		}
        fclose(f);
    }
	free(centers);

	printf("IMAGE SUCESSFULLY SEGMENTED \n");

	return 0;
}


