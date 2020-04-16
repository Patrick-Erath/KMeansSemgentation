#include <math.h>
#include <stdio.h>
#include <stdint.h>

#include <time.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "kmeans.h"

// READ IN IMAGE
int read_in_image() {

    // Read image
	int width, height, bpp;
	uint8_t* rgb_image = stbi_load("image.png", &width, &height, &bpp, 3);
	stbi_image_free(rgb_image);
	srand(time(NULL)); 

	// Init random cluster centers
    int i;
    int j;
	int k_clusters = 2;
    int cluster_centers[k_clusters][3];
    // Initalize a cluster center (RGB) for each K_cluster
    /*
    for(i=0; i<k_clusters; i++){
        for(j=0; j<3; j++){
            cluster_centers[i][j] = rand() % 255; 
        }
    } 
    */
    // CENTER 1
	cluster_centers_init[0][0] = 145;
	cluster_centers_init[0][1] = 30;
    cluster_centers_init[0][2] = 30;

    // CENTER 2
	cluster_centers_init[0][0] = 145;
	cluster_centers_init[0][1] = 30;
    cluster_centers_init[0][2] = 30;

    // Grab RGB pixels
	int red_pixels[height*width];
	int blue_pixels[height*width];
	int green_pixels[height*width];
    int j=0;
    for(i=0; i<height*width; i++){
        red_pixels[i] = rgb_image[j];
        blue_pixels[i] = rgb_image[j+1];
        green_pixels[i] = rgb_image[j+2];
        j += 3;
    }

    // Calculate eucilidean distance bewtween each pixel and each cluster center, assign to group of closest cluster
    for(i=0; i<height*width; i++){ 
        for(j=0; j<k_clusters; j++){
            int rgb_diff = abs(pow((red_pixels[i] - , 2)))
        }
    }



    return 0;

}

int main(int argc, char*argv[]) {
	printf("Try to read in image");
	printf("\n");
    read_in_image();
}