# KMeansSemgentation

The goal of this project is to segment an image using K-means. In order to run the code, please follow the following steps in your terminal:

<h1>Preface</h1>


<h1>Instructions for Running</h1>

1. CD into the project path, and build the project:
```console
cd KMeansSegmentation
gpp main.c
```

2. Run k-means on the image
```console
./a.out
```
This runs k-means on the image "image.jpeg", and saves the segmented image as "data.txt". To view the segmented image we use the jupyernotebook, and compare to the built-in k-means function of sklearn to test accuracy.

3. Compare C-code to Python
Start the jupyter-noteboot: 
```console
jupyternotebook
```
Open image-segmentation.ipynb to view the image segmented by C-code
