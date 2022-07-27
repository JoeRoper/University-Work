import pandas as pd
import numpy as np
import os
import matplotlib.pyplot as plt
import cv2
from keras.models import Sequential,load_model,Model
from keras.layers import Conv2D,MaxPool2D,Dense,Dropout,BatchNormalization,Flatten,Input
from sklearn.model_selection import train_test_split

path = "UTKFace"
images = []
age = []
#split data by age label
for image in os.listdir(path):
  ages = image.split("_")[0]
  image = cv2.imread(str(path)+"/"+str(image))
  image = cv2.cvtColor(image,cv2.COLOR_BGR2RGB)
  image = cv2.resize(image, (0, 0), fx=0.5, fy=0.5)
  images.append(np.array(image))
  age.append(np.array(ages))
  
age = np.array(age,dtype=np.int64)
images = np.array(images)

xTrainAge, xTestAge, yTrainAge, yTestAge = train_test_split(images, age, random_state=42)

#train model
model = Sequential()
model.add(Conv2D(128, kernel_size=3, activation='relu', input_shape=(100,100,3)))
model.add(MaxPool2D(pool_size=3, strides=2))

model.add(Conv2D(128, kernel_size=3, activation='relu'))
model.add(MaxPool2D(pool_size=3, strides=2))
              
model.add(Conv2D(256, kernel_size=3, activation='relu'))
model.add(MaxPool2D(pool_size=3, strides=2))

model.add(Conv2D(512, kernel_size=3, activation='relu'))
model.add(MaxPool2D(pool_size=3, strides=2))

model.add(Flatten())
model.add(Dropout(0.2))
model.add(Dense(512, activation='relu'))

model.add(Dense(1, activation='linear', name='age'))
              
model.compile(optimizer='adam', loss='mse', metrics=['mae'])
print(model.summary())              
                           
history = model.fit(xTrainAge, yTrainAge,
                        validation = (xTestAge, yTestAge), epochs=50)

model.save('ageDetectionModel.h5')