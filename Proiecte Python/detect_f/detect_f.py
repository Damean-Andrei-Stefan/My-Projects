import cv2

# incarcam cascada
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
# incarcam imaginea
img = cv2.imread('test.jpg')
# convertim imaginea in alb-negru
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# folosim cascada sa detectam fete
faces = face_cascade.detectMultiScale(gray, 1.11, 4)
# patrate pentru fiecare fata
for (x, y, w, h) in faces:
    cv2.rectangle(img, (x, y), (x+w, y+h), (0,0,228), 3)
# imaginea cu partate
cv2.imshow('img', img)
cv2.waitKey()