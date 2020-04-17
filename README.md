# KMeansSemgentation

To run :

1. Git clone repo
```console
git clone https://github.com/Patrick-Erath/KMeansSemgentation.git
```


2. Cd into folder, and build project
```console
gpp kmeans_tst.c
```

3. Run k-means on the image
```console
./a.out
```
This runs k-means on the image "segment.jpg", and saves the segmented image as "data.txt". To view the segmented image we use the jupyernotebook, and compare to the built-in k-means function of sklearn to test accuracy.

4. Compare C-code to Python
Start the jupyter-noteboot: 
```console
jupyternotebook
```
Open image-segmentation to view the image segmented by C-code
