# KMeansSemgentation

The goal of this project is to segment an image using K-means. In order to run the code, please follow the read the following. 

<h1>Preface</h1>
<p>
This project segements an image using k-means. A sample image is provided in the Images/ directory, however any image can be segmented. To test another image, name it 'image.jpeg' and place it in the Images/ folder (ie overwriting the current test mage). The outputted image is saved as a txt file in the Data/ folder as 'data.txt', this is done to allow the algorithm to run as efficiently as possible. 
</p>
<p>
To view the image after it has undergone segmentation, a python script in Jupyer notebook is used. The python script is also used to calculate algorithm efficiency, and compare the C-means algorithm with the python one for accuracy. The instructions to run the python script are explained below, however to simply view the test-case image being compared, a pdf file is also provided (open image-segmentation.pdf instead of opening jupyer notebook).
</p>
<p>
Lastly, the code allows the user to change the number of k-cluster groups. To change the number of groups, simply change the 'k_clusters = 2' variable in main.c
</p>

<h1>Instructions for Running</h1>

1. CD into the project path, and build the project:
```console
cd KMeansSegmentation
gpp main.c
```

2. Run k-means on the image <br/>
For <b>WINDOWS OS</b>:
```console
./a.exe
``` 

<br/>

FOR <b>MAC OS</b>:
```console
./a.out
```
This runs k-means on the image "image.jpeg", and saves the segmented image as "data.txt". To view the segmented image we use the jupyernotebook, and compare to the built-in k-means function to test accuracy.

3. Compare C-code to Python
Start the jupyter-noteboot: 
```console
jupyternotebook
```
Open image-segmentation.ipynb to view the image segmented by C-code
