#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define sqr(x) ((x)*(x))
// The maximum number of clusters, this is for optimization 
#define MAX_CLUSTERS 16
// Maximum iterations, also for optimization, this limits long converegence time from over-fitting
#define MAX_ITERATIONS 200
#define BIG_double (INFINITY)
  
// Calculate the Euclidean Distance between two points p1 and p2
double calculate_euclidean_distance(int dim, double *p1, double *p2)
  {
    double distance_sq_sum = 0;
    
    for (int ii = 0; ii < dim; ii++)
      distance_sq_sum += sqr(p1[ii] - p2[ii]);

    return distance_sq_sum;
    
  }

// Calculate ALL of the Eucilidean distances for a each point and each cluster
void calculate_all_euclidean_distancess(int dim, int n, int k, double *X, double *cluster_center, double *distance_output)
  {
    // Iterate over each point
    for (int ii = 0; ii < n; ii++)
    // Iterate over each cluster
      for (int jj = 0; jj < k; jj++) 
        {
         // Calculate Eucilidean distance between point and cluster_center
          distance_output[ii*k + jj] = calculate_euclidean_distance(dim, &X[ii*dim], &cluster_center[jj*dim]);
        }
  }
  
// Calculate the total distance between a point and it's respective cluster center
double calculate_total_distance(int dim, int n, int k, double *X, double *centroids, int *cluster_assignment_index)
  {
    double tot_D = 0;
    
   // Iterate over each point
    for (int ii = 0; ii < n; ii++)
      {
       // Get active cluster
        int active_cluster = cluster_assignment_index[ii];
       // Sum distance 
        if (active_cluster != -1)
          tot_D += calculate_euclidean_distance(dim, &X[ii*dim], &centroids[active_cluster*dim]);
      }
      
    return tot_D;
  }

// Assign each point to a cluster group, based on the nearest o
void choose_all_clusters_from_distances(int dim, int n, int k, double *distance_array, int *cluster_assignment_index)
  {
   // Iterate over each point
    for (int ii = 0; ii < n; ii++)
      {
        int best_index = -1;
        double closest_distance = BIG_double;
        
       // Iterate over each cluster
        for (int jj = 0; jj < k; jj++)
          {
           // Calculate distance between point and cluster cluster_center
           
            double cur_distance = distance_array[ii*k + jj];
            if (cur_distance < closest_distance)
              {
                best_index = jj;
                closest_distance = cur_distance;
              }
          }
       // Save the assigned cluster group 
        cluster_assignment_index[ii] = best_index;
      }
  }

void calc_cluster_centroids(int dim, int n, int k, double *X, int *cluster_assignment_index, double *new_cluster_centroid)
  {
    int cluster_member_count[MAX_CLUSTERS];
  
   // Initialize cluster cluster_center coordinate sums to zero
    for (int ii = 0; ii < k; ii++) 
      {
        cluster_member_count[ii] = 0;
        
        for (int jj = 0; jj < dim; jj++)
          new_cluster_centroid[ii*dim + jj] = 0;
     }

   // sum all points
   // for every point
    for (int ii = 0; ii < n; ii++)
      {
       // which cluster is it in?
        int active_cluster = cluster_assignment_index[ii];

       // update count of members in that cluster
        cluster_member_count[active_cluster]++;
        
       // sum point coordinates for finding cluster_center
        for (int jj = 0; jj < dim; jj++)
          new_cluster_centroid[active_cluster*dim + jj] += X[ii*dim + jj];
      }
      
      
   // now divide each coordinate sum by number of members to find mean/cluster_center
   // for each cluster
    for (int ii = 0; ii < k; ii++) 
      {
        if (cluster_member_count[ii] == 0)
          printf("WARNING: Empty cluster %d! \n", ii);
          
       // for each dimension
        for (int jj = 0; jj < dim; jj++)
          new_cluster_centroid[ii*dim + jj] /= cluster_member_count[ii];  /// XXXX will divide by zero here for any empty clusters!

      }
  }

void get_cluster_member_count(int n, int k, int *cluster_assignment_index, int *cluster_member_count)
  {
   // initialize cluster member counts
    for (int ii = 0; ii < k; ii++) 
      cluster_member_count[ii] = 0;
  
   // count members of each cluster    
    for (int ii = 0; ii < n; ii++)
      cluster_member_count[cluster_assignment_index[ii]]++;
  }

void update_delta_score_table(int dim, int n, int k, double *X, int *cluster_assignment_cur, double *cluster_centroid, int *cluster_member_count, double *point_move_score_table, int cc)
  {
   // for every point (both in and not in the cluster)
    for (int ii = 0; ii < n; ii++)
      {
        double dist_sum = 0;
        for (int kk = 0; kk < dim; kk++)
          {
            double axis_dist = X[ii*dim + kk] - cluster_centroid[cc*dim + kk]; 
            dist_sum += sqr(axis_dist);
          }
          
        double mult = ((double)cluster_member_count[cc] / (cluster_member_count[cc] + ((cluster_assignment_cur[ii]==cc) ? -1 : +1)));

        point_move_score_table[ii*dim + cc] = dist_sum * mult;
      }
  }
  
  
void  perform_move(int dim, int n, int k, double *X, int *cluster_assignment, double *cluster_centroid, int *cluster_member_count, int move_point, int move_target_cluster)
  {
    int cluster_old = cluster_assignment[move_point];
    int cluster_new = move_target_cluster;
  
   // Update cluster assignment array
    cluster_assignment[move_point] = cluster_new;
    
   // Update cluster count array
    cluster_member_count[cluster_old]--;
    cluster_member_count[cluster_new]++;
    
    if (cluster_member_count[cluster_old] <= 1)
      printf("WARNING: Can't handle single-member clusters! \n");
    
   // Update cluster_center array
    for (int ii = 0; ii < dim; ii++)
      {
        cluster_centroid[cluster_old*dim + ii] -= (X[move_point*dim + ii] - cluster_centroid[cluster_old*dim + ii]) / cluster_member_count[cluster_old];
        cluster_centroid[cluster_new*dim + ii] += (X[move_point*dim + ii] - cluster_centroid[cluster_new*dim + ii]) / cluster_member_count[cluster_new];
      }
  }  
  
void cluster_diag(int dim, int n, int k, double *X, int *cluster_assignment_index, double *cluster_centroid)
  {
    int cluster_member_count[MAX_CLUSTERS];
    
    get_cluster_member_count(n, k, cluster_assignment_index, cluster_member_count);
     
    printf("\t Final Clusters Centers: \n");
    for (int ii = 0; ii < k; ii++) 
      printf("    Cluster %d:     Count: %8d, \t Gray-Scale Value: (%.1f) \n", ii, cluster_member_count[ii], cluster_centroid[ii*dim + 0]);
  }

// Copy array for data.txt output
void copy_assignment_array(int n, int *src, int *tgt)
  {
	int ii=0;
    for (ii = 0; ii < n; ii++)
      tgt[ii] = src[ii];
  }
  
int assignment_change_count(int n, int a[], int b[])
  {
    int change_count = 0;

    for (int ii = 0; ii < n; ii++)
      if (a[ii] != b[ii])
        change_count++;
        
    return change_count;
  }

void fail(char *str)
  {
    printf(str);
    exit(-1);
  }

int*  kmeans(
            int  dim,		                     // dimension of data 

            double *X,                        // pointer to data
            int   n,                         // number of elements
            
            int   k,                         // number of clusters
            double *cluster_centroid        // initial cluster centroids
              // output
           )
  {
    double *dist                    = (double *)malloc(sizeof(double) * n * k);
    int   *cluster_assignment_cur  = (int *)malloc(sizeof(int) * n);
    int   *cluster_assignment_prev = (int *)malloc(sizeof(int) * n);
    double *point_move_score        = (double *)malloc(sizeof(double) * n * k);
	
    
    
    if (!dist || !cluster_assignment_cur || !cluster_assignment_prev || !point_move_score)
      fail("Error Occured");
    
   // Initialization
  calculate_all_euclidean_distancess(dim, n, k, X, cluster_centroid, dist);
	printf("\n 2. Calculated Eucilidan Done \n");
  choose_all_clusters_from_distances(dim, n, k, dist, cluster_assignment_cur);
	printf("\n 3. Assigned Cluster Centers Done \n");
  copy_assignment_array(n, cluster_assignment_cur, cluster_assignment_prev);
	printf("\n K-means Reached  \n");

   // Iterative k-means
    double prev_totD = BIG_double;
    int batch_iteration = 0;
    while (batch_iteration < MAX_ITERATIONS)
      {
        // Recalculate cluster centers
         calc_cluster_centroids(dim, n, k, X, cluster_assignment_cur, cluster_centroid);


        // Check improvemens criteria
         double totD = calculate_total_distance(dim, n, k, X, cluster_centroid, cluster_assignment_cur);
         if (totD > prev_totD)
          // Current solution worse than previous, 
           {
            // Restore old assignments
             copy_assignment_array(n, cluster_assignment_prev, cluster_assignment_cur);
            // Recalculate centroids
             calc_cluster_centroids(dim, n, k, X, cluster_assignment_cur, cluster_centroid);
             printf("  negative progress made on this step - iteration completed (%.2f) \n", totD - prev_totD);
             break;
           }
           
        // Save step
         copy_assignment_array(n, cluster_assignment_cur, cluster_assignment_prev);
        // Reassign all points to their respective closest cluster-center
         calculate_all_euclidean_distancess(dim, n, k, X, cluster_centroid, dist);
         choose_all_clusters_from_distances(dim, n, k, dist, cluster_assignment_cur);
         
         int change_count = assignment_change_count(n, cluster_assignment_cur, cluster_assignment_prev);
         
         printf("%3d   %u   %9d  %16.2f %17.2f\n", batch_iteration, 1, change_count, totD, totD - prev_totD);
         fflush(stdout);
        
        // If no change has occured, then convergence has been reached
         if (change_count == 0)
           {
             printf("\t Convergence Reached \n");
             break;
           }

         prev_totD = totD;               
         batch_iteration++;
      }

cluster_diag(dim, n, k, X, cluster_assignment_cur, cluster_centroid);    
    free(dist);
    free(cluster_assignment_prev);
    free(point_move_score);

	return cluster_assignment_cur;
  }           