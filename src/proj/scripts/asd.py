# USAGE
# python encode_faces.py --dataset dataset --encodings encodings.pickle

# import the necessary packages
from imutils import paths
import face_recognition
import argparse
import pickle
import cv2
import os
import sys


name = sys.argv[1]
print(name)
# load the input image and convert it from RGB (OpenCV ordering)
# to dlib ordering (RGB)
image = cv2.imread(name)

# (Resize pra rodar na Placa)
width = int(image.shape[1]*(1/3))
height = int(image.shape[0]*(1/3))
dim = (width, height)
image = cv2.resize(image, dim, interpolation = cv2.INTER_AREA)
cv2.imwrite("../Jr2/"+str(name) + "_ref.png", image)
