
#####################################################################
# run __ONE__ of the following commands:
# pip install --user tensorflow (if you have no CUDA-enabled GPU)
# pip install --user tensorflow-gpu
#
# afterwards install tflearn
# pip install --user tflearn
#
# Numpy should come bundled with tensorflow. Run this file et voila!
#####################################################################

import array as ar
import numpy as np
import imageio
import glob
from PIL import Image

filelist = glob.glob('C:/Users/marsh/Documents/GitHub/ParallelProgramming/DigitClassifier/ImageData/*.png')
weightlist = glob.glob('C:/Users/marsh/Documents/GitHub/ParallelProgramming/DigitClassifier/WeightsData/*.png')

X = np.array([np.array(Image.open(fname).convert('L')) for fname in filelist])

Y = np.array([1,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,
              1,0,0,0,0,0,0,0,0,0,
              0,1,0,0,0,0,0,0,0,0,
              0,1,0,0,0,0,0,0,0,0,
              0,1,0,0,0,0,0,0,0,0,
              0,1,0,0,0,0,0,0,0,0,
              0,1,0,0,0,0,0,0,0,0,
              0,1,0,0,0,0,0,0,0,0,
              0,1,0,0,0,0,0,0,0,0,
              0,1,0,0,0,0,0,0,0,0,
              0,1,0,0,0,0,0,0,0,0,
              0,0,1,0,0,0,0,0,0,0,
              0,0,1,0,0,0,0,0,0,0,
              0,0,1,0,0,0,0,0,0,0,
              0,0,1,0,0,0,0,0,0,0,
              0,0,1,0,0,0,0,0,0,0,
              0,0,1,0,0,0,0,0,0,0,
              0,0,1,0,0,0,0,0,0,0,
              0,0,1,0,0,0,0,0,0,0,
              0,0,1,0,0,0,0,0,0,0,
              0,0,0,1,0,0,0,0,0,0,
              0,0,0,1,0,0,0,0,0,0,
              0,0,0,1,0,0,0,0,0,0,
              0,0,0,1,0,0,0,0,0,0,
              0,0,0,1,0,0,0,0,0,0,
              0,0,0,1,0,0,0,0,0,0,
              0,0,0,1,0,0,0,0,0,0,
              0,0,0,1,0,0,0,0,0,0,
              0,0,0,1,0,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,0,1,0,0,0,0,
              0,0,0,0,0,1,0,0,0,0,
              0,0,0,0,0,1,0,0,0,0,
              0,0,0,0,0,1,0,0,0,0,
              0,0,0,0,0,1,0,0,0,0,
              0,0,0,0,0,1,0,0,0,0,
              0,0,0,0,0,1,0,0,0,0,
              0,0,0,0,0,1,0,0,0,0,
              0,0,0,0,0,0,1,0,0,0,
              0,0,0,0,0,0,1,0,0,0,
              0,0,0,0,0,0,1,0,0,0,
              0,0,0,0,0,0,1,0,0,0,
              0,0,0,0,0,0,1,0,0,0,
              0,0,0,0,0,0,1,0,0,0,
              0,0,0,0,0,0,1,0,0,0,
              0,0,0,0,0,0,1,0,0,0,
              0,0,0,0,0,0,1,0,0,0,
              0,0,0,0,0,0,0,1,0,0,
              0,0,0,0,0,0,0,1,0,0,
              0,0,0,0,0,0,0,1,0,0,
              0,0,0,0,0,0,0,1,0,0,
              0,0,0,0,0,0,0,1,0,0,
              0,0,0,0,0,0,0,1,0,0,
              0,0,0,0,0,0,0,1,0,0,
              0,0,0,0,0,0,0,1,0,0,
              0,0,0,0,0,0,0,1,0,0,
              0,0,0,0,0,0,0,0,1,0,
              0,0,0,0,0,0,0,0,1,0,
              0,0,0,0,0,0,0,0,1,0,
              0,0,0,0,0,0,0,0,1,0,
              0,0,0,0,0,0,0,0,1,0,
              0,0,0,0,0,0,0,0,1,0,
              0,0,0,0,0,0,0,0,1,0,
              0,0,0,0,0,0,0,0,1,0,
              0,0,0,0,0,0,0,0,1,0,
              0,0,0,0,0,0,0,0,0,1,
              0,0,0,0,0,0,0,0,0,1,
              0,0,0,0,0,0,0,0,0,1,
              0,0,0,0,0,0,0,0,0,1,
              0,0,0,0,0,0,0,0,0,1,
              0,0,0,0,0,0,0,0,0,1,
              0,0,0,0,0,0,0,0,0,1,
              0,0,0,0,0,0,0,0,0,1,
              0,0,0,0,0,0,0,0,0,1,
              1,0,0,0,0,0,0,0,0,0,
              0,1,0,0,0,0,0,0,0,0,
              0,0,1,0,0,0,0,0,0,0,
              0,0,0,1,0,0,0,0,0,0,
              0,0,0,0,1,0,0,0,0,0,
              0,0,0,0,0,1,0,0,0,0,
              0,0,0,0,0,0,1,0,0,0,
              0,0,0,0,0,0,0,1,0,0,
              0,0,0,0,0,0,0,0,1,0,
              0,0,0,0,0,0,0,0,0,1])

W = np.array([np.array(Image.open(fname).convert('L')) for fname in weightlist])


with open("C:/Users/marsh/Documents/GitHub/ParallelProgramming/DigitClassifier/ImageData/exports/X.bin", "wb") as f:
    images = X
    print(images.shape)
    f.write(ar.array("f", images.flatten()))

with open("C:/Users/marsh/Documents/GitHub/ParallelProgramming/DigitClassifier/ImageData/exports/Y.bin", "wb") as f:
    labels = Y
    print(labels.shape)
    f.write(ar.array("f", labels.flatten()))

with open("C:/Users/marsh/Documents/GitHub/ParallelProgramming/DigitClassifier/ImageData/exports/W.bin", "wb") as f:
    weights = W
    print(weights.shape)
    f.write(ar.array("f", weights.flatten()))
