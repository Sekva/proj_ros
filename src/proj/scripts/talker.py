#!/usr/bin/python2
import rospy
import cv2
from geometry_msgs.msg import Point32
from std_msgs.msg import Float32

norma = 0

def callback(aux):
	norma = aux.data
	print "NORMA >>>>", norma 


def talker():
	pub = rospy.Publisher('arduino', Point32, queue_size=10)
	rospy.init_node('tracker', anonymous=True)
	rospy.Subscriber('arduino_norma', Float32, callback)
	rate = rospy.Rate(10) # 10hz
	while not rospy.is_shutdown():
		arqCasc = 'haarcascade_frontalface_default.xml'
		faceCascade = cv2.CascadeClassifier(arqCasc)

		webcam = cv2.VideoCapture(0)  #instancia o uso da webcam
		font = cv2.FONT_HERSHEY_SIMPLEX

		while True:
			s, imagem = webcam.read() #pega efeticamente a imagem da webcam
			faces = faceCascade.detectMultiScale(imagem, minNeighbors=5, minSize=(30, 30), maxSize=(200,200))
			#coordenada
			# Desenha um retangulo nas faces detectadas
			for (x, y, w, h) in faces:
				cv2.rectangle(imagem, (x, y), (x+w, y+h), (0, 255, 0), 2)
				cv2.circle(imagem, (int(x + w/2), int(y + h/2)), (5), (0, 255, 0), 2)
				cv2.line(imagem, (0,0), (x + w/2, y + w/2), (255, 255, 255), 2)
				ponto = Point32()
				ponto.x = x+w/2
				ponto.y = y+h/2 
				ponto.z = 0
				rospy.loginfo(ponto)
				pub.publish(ponto)

			cv2.imshow('Video', imagem) #mostra a imagem captura na janela

			#o trecho seguinte e apenas para parar o codigo e fechar a janela
			if cv2.waitKey(1) & 0xFF == ord('q'):
				break

		webcam.release() #dispensa o uso da webcam
		cv2.destroyAllWindows() #fecha todas a janelas abertas
		rate.sleep()

if __name__ == '__main__':
	try:
		talker()
	except rospy.ROSInterruptException:
		pass
