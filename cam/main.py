import cv2
import pyfirmata
import time
# Enable camera
cap = cv2.VideoCapture(2)
cap.set(3, 720)
cap.set(4, 1280)

board

# import cascade file for facial recognition
stop_data = cv2.CascadeClassifier('stop_data.xml')


while True:
    success, img = cap.read()
    imgGray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Getting corners around the face
    found = stop_data.detectMultiScale(imgGray, minSize=(20, 20))  # 1.3 = scale factor, 5 = minimum neighbor
    # drawing bounding box around face
    for (x, y, w, h) in found:
        img = cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 3)
        print((x+x+w)/2,(y+y+h)/2)



    cv2.imshow('face_detect', img)
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyWindow('face_detect')