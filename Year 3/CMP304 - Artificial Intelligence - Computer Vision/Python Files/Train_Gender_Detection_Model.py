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
gender = []
for image in os.listdir(path):
  genders = image.split("_")[1]
  image = cv2.imread(str(path)+"/"+str(image))
  image = cv2.cvtColor(image,cv2.COLOR_BGR2RGB)
  #img = cv2.resize(img, (0, 0), fx=0.5, fy=0.5)
  images.append(np.array(image))
  gender.append(np.array(genders))
  
images = np.array(images)   #Forgot to scale image for my training. Please divide by 255 to scale. 
gender = np.array(gender,np.uint64)

xTrainGender, xTestGender, yTrainGender, yTestGender = train_test_split(images, gender, random_state=42)

#create model
model = Sequential()

model.add(Conv2D(36, kernel_size=3, activation='relu', input_shape=(200,200,3)))

model.add(MaxPool2D(pool_size=3, strides=2))
model.add(Conv2D(64, kernel_size=3, activation='relu'))
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
model.add(Dense(1, activation='sigmoid', name='gender'))

model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

history = model.fit(xTrainGender, yTrainGender, validation_data=(xTestGender, yTestGender), epochs=50)

model.save('genderDetectionModel.h5')


#plot the graphs
loss = history.history['loss']
val_loss = history.history['val_loss']
epochs = range(1, len(loss) + 1)
plt.plot(epochs, loss, 'y', label='Training loss')
plt.plot(epochs, val_loss, 'r', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()

trainingAccuracy = history.history['accuracy']
validationAccuracy = history.history['val_accuracy']

plt.plot(epochs, trainingAccuracy, 'y', label='Training Accuracy')
plt.plot(epochs, validationAccuracy, 'r', label='Validation Accuracy')
plt.title('Training and validation accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()
plt.show()
