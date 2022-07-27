#import Libraries
from keras.models import load_model
from time import sleep
from tensorflow.keras.preprocessing.image import img_to_array
from keras.preprocessing import image
import cv2
import numpy as np
import time

#Import Models
faceDetection=cv2.CascadeClassifier('Models/haarcascade_frontalface_default.xml')
emotionDetectionModel = load_model('Models/emotionDetectionModel.h5')
ageDetectionModel = load_model('Models/ageDetectionModel.h5')
genderDetectionModel = load_model('Models/genderDetectionModel.h5')


classLabels=['Angry','Disgust', 'Fear', 'Happy','Neutral','Sad','Surprise']
genderLabels = ['Male', 'Female']

frameRate = 15 #Decide the frame rate the program will run off
previousTime = 0
capture = cv2.VideoCapture(0)

while True:
    timeElapsed = time.time() - previousTime
    ret,frame=capture.read()
    labels=[]
    
    if timeElapsed > 1./frameRate:
        previousTime = time.time()
        grayScale = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
        faces = faceDetection.detectMultiScale(grayScale,1.3,5)

        for (x,y,w,h) in faces:
            cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)
            boxGrayScale= grayScale[y:y+h,x:x+w]
            boxGrayScale=cv2.resize(boxGrayScale,(48,48),interpolation=cv2.INTER_AREA)

            #Get image ready for prediction
            box = boxGrayScale.astype('float')/255.0  #Scale
            box = img_to_array(box)
            box = np.expand_dims(box,axis=0)

            emotionPrediction = emotionDetectionModel.predict(box)[0]  
            label = classLabels[emotionPrediction.argmax()]  #Find the label
            label_position=(x,y)
            cv2.putText(frame,label,label_position,cv2.FONT_HERSHEY_SIMPLEX,1,(230,230,250),2)#render text
            
            #Gender
            boxColour = frame[y:y+h,x:x+w]
            boxColour = cv2.resize(boxColour,(200,200),interpolation=cv2.INTER_AREA)
            genderPrediction = genderDetectionModel.predict(np.array(boxColour).reshape(-1,200,200,3))
            genderPrediction = (genderPrediction>= 0.5).astype(int)[:,0]
            genderLabel = genderLabels[genderPrediction[0]] 
            genderLabelPosition=(x,y+h+50)
            cv2.putText(frame,genderLabel,genderLabelPosition,cv2.FONT_HERSHEY_SIMPLEX,1,(230,230,250),2)
            
            #Age
            agePrediction = ageDetectionModel.predict(np.array(boxColour).reshape(-1,100,100,3))
            age = round(agePrediction[0,0])
            age_label_position=(x+125,y+h+50) #50 pixels below to move the label outside the face
            cv2.putText(frame,"Age="+str(age),age_label_position,cv2.FONT_HERSHEY_SIMPLEX,1,(230,230,250),2)
            
        
            
    
        cv2.imshow('AI Application', frame)
        input = cv2.waitKey(30) & 0xff
        if input == 27:      #Press Esc to stop the video
            break
capture.release()
cv2.destroyAllWindows()