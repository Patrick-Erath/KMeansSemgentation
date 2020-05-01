extern int* kmeans(
            int  dim,		                      // dimension of data 
            double *X,                        // pointer to array containing image data 
            int   n,                         // number of elements    
            int   k,                         // number of clusters
            double *cluster_centroid         // initial cluster centroids
           );