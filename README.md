# PPM image processing project
## WOOPER - Project C P1 S2

Program for making various modifications to PPM P3 images.


# What is image processing? 

Image processing studies digital images and their transformations, with the aim of improving their quality or extracting information from them. 
To understand image processing, you first need to understand what an image is. 
Images have many parameters: 
- acquisition resolution and the coding mode used during digitization
- the optical settings used (including focus), which determine, for example, image sharpness
- lighting conditions
- image transmission chain noise

Each image has a certain number of pixels, which is a combination of colors (red, blue and green). By manipulating these parameters, we can process the image, i.e. modify it. 
For example, binarize, rotate, mirror, change pixel color, etc.


# Use

Download the folder, move inside, compile with make clean and make, then run the program with ./img.

You can use various commands after ./img. For program help, write ./img -h
    
# Example of prompts :

./img -i bender.ppm -o bendergris.ppm -g

./img -i bender.ppm -o rota.ppm -p -p

./img -i bender.ppm -c




