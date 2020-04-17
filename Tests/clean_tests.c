#include <math.h>
#include <stdio.h>
#include <stdint.h>

#include <time.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "kmeans.h"


int k_means() {

    // Read in RGB image as a 1D array 
	int width, height, bpp;
	uint8_t* rgb_image = stbi_load("image.png", &width, &height, &bpp, 3);
	stbi_image_free(rgb_image);
	srand(time(NULL)); 

	// Init random RGB cluster centers
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
	cluster_centers[0][0] = 115;
	cluster_centers[0][1] = 30;
    cluster_centers[0][2] = 40;

    // CENTER 2
	cluster_centers[1][0] = 145;
	cluster_centers[1][1] = 20;
    cluster_centers[1][2] = 60;

    // Grab RGB pixels
	int red_pixels[height*width];
	int blue_pixels[height*width];
	int green_pixels[height*width];
    j = 0;
    for(i=0; i<height*width; i++){
        red_pixels[i] = rgb_image[j];
        blue_pixels[i] = rgb_image[j+1];
        green_pixels[i] = rgb_image[j+2];
        j += 3;
    }

    int *pixel_groups = malloc (sizeof (int) * width*height);
    // Calculate eucilidean distance bewtween each pixel and each cluster center, assign to group of closest cluster
    for(i=0; i<height*width; i++){ 
        int min = 9999;
        int min_index = 0;
        for(j=0; j<k_clusters; j++){
            int r = red_pixels[i];
            int b = blue_pixels[i];
            int g = green_pixels[i];

            int r_c =  cluster_centers[j][0];
            int g_c =  cluster_centers[j][1];
            int b_c =  cluster_centers[j][2];

            int r_diff = pow((red_pixels[i] - cluster_centers[j][0]), 2);
            int b_diff = pow((blue_pixels[i] - cluster_centers[j][1]), 2);
            int g_diff = pow((green_pixels[i] - cluster_centers[j][2]), 2);
            int euclidean_distance = sqrt(r_diff + b_diff + g_diff);

           // printf("%d\n", euclidean_distance);  
            if(euclidean_distance < min){
                min = euclidean_distance;
                min_index = j;
            }
        }
        // Assign pixel to the closest cluster group
        pixel_groups[i] = min_index;
    }

    
    // Count groups
    int counter[2];
    counter[0] = 0;
    counter[1] = 0;
    for(i=0; i<height*width; i++){
        if(pixel_groups[i] == 0){
            counter[0] += 1;
        }
        else if (pixel_groups[i] == 1)
        {
            counter[1] += 1;
        }
    }

     printf("0 Counts %d\n", counter[0]);  
     printf("1 Counts %d\n", counter[1]);  

    return 0;
}

int main(int argc, char*argv[]) {
	printf("Try to read in image");
	printf("\n");
    k_means();
}