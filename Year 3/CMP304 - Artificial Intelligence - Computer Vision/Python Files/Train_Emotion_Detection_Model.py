#Library Imports
from keras.preprocessing.image import ImageDataGenerator
from keras.models import Sequential
from keras.layers import Dense,Dropout,Flatten
from keras.layers import Conv2D,MaxPooling2D
import os
from matplotlib import pyplot as plt
import numpy as np

#Set image sizes
IMG_HEIGHT=48 
IMG_WIDTH = 48
batch_size=32

trainDataPath = 'Emotion_Dataset/train'
testDataPath = 'Emotion_Dataset/test'

#Defines a data generator
trainDataGenerator = ImageDataGenerator(
					rescale=1./255,#rescales the image
					rotation_range=30,
					shear_range=0.3,
					zoom_range=0.3,
					horizontal_flip=True,
					fill_mode='nearest')

validationDataGenerator = ImageDataGenerator(rescale=1./255)

trainGenerator = trainDataGenerator.flow_from_directory(
					trainDataPath,
					color_mode='grayscale',#images are already greyscale
					target_size=(IMG_HEIGHT, IMG_WIDTH),
					batch_size=batch_size,
					class_mode='categorical',
					shuffle=True)

validationGenerator = validationDataGenerator.flow_from_directory(
							testDataPath,
							color_mode='grayscale',
							target_size=(IMG_HEIGHT, IMG_WIDTH),
							batch_size=batch_size,
							class_mode='categorical',
							shuffle=True)


image, label = trainGenerator.__next__()

# Create the model
model = Sequential()

model.add(Conv2D(32, kernel_size=(3, 3), activation='relu', input_shape=(48,48,1)))

model.add(Conv2D(64, kernel_size=(3, 3), activation='relu'))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Dropout(0.1))

model.add(Conv2D(128, kernel_size=(3, 3), activation='relu'))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Dropout(0.1))

model.add(Conv2D(256, kernel_size=(3, 3), activation='relu'))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Dropout(0.1))

model.add(Flatten())
model.add(Dense(512, activation='relu'))
model.add(Dropout(0.1))

model.add(Dense(7, activation='softmax'))

model.compile(optimizer = 'adam', loss='categorical_crossentropy', metrics=['accuracy'])
print(model.summary())


#Plot model
trainImageAmount = 0
for root, dirs, files in os.walk(trainDataPath):
    trainImageAmount += len(files)
    
testImageAmount = 0
for root, dirs, files in os.walk(testDataPath):
    testImageAmount += len(files)


epochs=50

history=model.fit(trainGenerator,
                steps_per_epoch=trainImageAmount//batch_size,
                epochs=epochs,
                validation_data=validationGenerator,
                validation_steps=testImageAmount//batch_size)

model.save('emotionDetectionModel.h5')

trainingLoss = history.history['loss']
validationLoss = history.history['val_loss']
epochs = range(1, len(trainingLoss) + 1)
plt.plot(epochs, trainingLoss, 'y', label='Training loss')
plt.plot(epochs, validationLoss, 'r', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()

trainingAccuracy = history.history['accuracy']
validationAccuracy = history.history['val_accuracy']

plt.plot(epochs, trainingAccuracy, 'y', label='Training accuracy')
plt.plot(epochs, validationAccuracy, 'r', label='Validation accuracy')
plt.title('Training and Validation Accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()
plt.show()