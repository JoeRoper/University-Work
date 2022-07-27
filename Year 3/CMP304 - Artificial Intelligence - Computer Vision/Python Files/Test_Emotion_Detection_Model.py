#Library Imports
from keras.models import load_model
from keras.preprocessing.image import ImageDataGenerator
from keras.models import Sequential
from keras.layers import Dense,Dropout,Flatten
from keras.layers import Conv2D,MaxPooling2D
import os
from matplotlib import pyplot as plt
import numpy as np
import random
from sklearn import metrics
from sklearn.metrics import confusion_matrix
import seaborn as sns

#Set image sizes
IMG_HEIGHT=48 
IMG_WIDTH = 48
batch_size=128

path = 'Emotion_Dataset/test'
emotionModel = load_model('Models/emotionDetectionModel.h5', compile=False)

validationDataGenerator = ImageDataGenerator(rescale=1./255)


validationGenerator = validationDataGenerator.flow_from_directory(
							path,
							color_mode='grayscale',
							target_size=(IMG_HEIGHT, IMG_WIDTH),
							batch_size=batch_size,
							class_mode='categorical',
							shuffle=True)


##########################################################
#Test the model
emotionLabels=['Angry','Disgust', 'Fear', 'Happy','Neutral','Sad','Surprise']

for x in range(0, 3):
    #Generate a batch of images
    testImage, testLabel = validationGenerator.__next__()
    predictions = emotionModel.predict(testImage)

    predictions = np.argmax(predictions, axis=1)
    testLabels = np.argmax(testLabel, axis=1)


    print ("Accuracy = ", metrics.accuracy_score(testLabels, predictions))

    #Confusion Matrix
    confusionMatrix = confusion_matrix(testLabels, predictions)
    print(confusionMatrix)

    #prints heatmap
    #sns.heatmap(confusionMatrix, annot=True)

   
    
    #render results
    x = random.randint(0, testImage.shape[0] - 1)
    image = testImage[x]
    actualLabel = emotionLabels[testLabels[x]]
    predictionLabel = emotionLabels[predictions[x]]
    plt.imshow(image[:,:,0], cmap='gray')
    plt.title("Actual label: "+actualLabel+  "    Predicted label: "+ predictionLabel)
    plt.show()