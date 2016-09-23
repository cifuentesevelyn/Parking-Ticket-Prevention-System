#Developed by: Evelyn Cifuentes
#Program to trigger RFID reader with Motion Sensor and compare/match incoming ID tags.
#Updated: April 25, 2016

#Created for lot 10
#Note: All commented out 'print' lines strictly for value testing and verification


import Adafruit_BBIO.UART as UART
import Adafruit_BBIO.GPIO as GPIO
import serial
import time
import sys
import schedule #For timing

#Motion Detector Setup
trigger_pin = 'P9_12'
echo_pin = 'P9_14'

GPIO.setup("P9_12", GPIO.OUT)
GPIO.setup("P9_14", GPIO.IN)

#Valid ID's for lot 10
id_a = ['0xff', '0xff', '0xff', '0xff', '0xff', '0xff', '0xff', '0xff', '0xff', '0xd9', '0xf', '0xfb', '0xbb', '0xfd', '0x5f', '0x0']
id_b = ['0xff', '0xff', '0xff', '0xff', '0xff', '0xff', '0xff', '0xff', '0xfd', '0x7f', '0x5d', '0x9d', '0xbb', '0xfd', '0xcb', '0x0']
id_c = ['0xff', '0xff', '0xff', '0xff', '0xff', '0xff', '0xff', '0xff', '0xdf', '0x11', '0xff', '0xd3', '0x51', '0xfd', '0xe9', '0x0']

#Empty list for incoming ID
data = []

def files():		#Opening text files to write to
	text_file = open("update.txt", "a")
	sfile = open("select.txt", "a")
	lcd_file = open("lcd.txt", "a")
	no_file = open("nopass.txt", "a")
	print('files OPENED')	#Denotes when text files are opened by program
	#Other programs SHOULD NOT open text files, data corruption might happen.
	
# initialization of variables for lot incrementation
lot_capacity = 0
lot_new = 0

def lot ():
   global lot_capacity
   global lot_new
   lot_capacity +=1
   lot_new==lot_capacity -1 
   return lot_capacity
   return lot_new

#Begin Motion Sensor Functions
def send_trigger_pulse():
	GPIO.output("P9_12", True)
	time.sleep(.00001)
	GPIO.output("P9_12", False)
	
def wait_for_echo(value, timeout):
	count = timeout
	while GPIO.input("P9_14") != value and count>0:
		count = count - 1

def get_distance():
	send_trigger_pulse()
	wait_for_echo(True,10000)
	start=time.time()
	wait_for_echo(False,10000)
	finish=time.time()
	pulse_len = finish - start
	distance_cm = pulse_len/.000058
	distance_in = distance_cm/2.5
	dist=distance_in*40
	print (dist)
	return (dist)
	
#RFID Activation and reading function
def RFIDmod():
	UART.setup("UART1")
	
	files()
	
	global lot_capacity
	global lot_new
	
	lot_numb= 10

	#Opens Serial port for UART1
	ser = serial.Serial(port = "/dev/ttyO1", baudrate=9600)
	ser.close()
	ser.open()

	#SEND command to RFID reader
	ser.write("0XA0")
	ser.write("0X06")
	ser.write("0X80")
	ser.write("0X00")
	ser.write("0X01")
	ser.write("0X01")
	ser.write("0X02")
	ser.write("0XD6")

	print "Reading begun"


	#initialize counter
	count = 0
	  
		  
	while count in range(0,16):

		count += 1						#Increment count for Data
		string = ser.read()			
		#print count                	#Print Count value
	 
		#print '%x' % ord(string)   	#Print Byte read
		   
		val = hex(ord(string))      
		#print val                    	#Print stringed value as hex
		
		data.append(val)
		
		#print data                  	#Print array
		
		


		if count == 16:
			# print ("Test print of 'Data'")
			# print data
			# print data[8]
			# print data[9]
			# print data[10]
			# print data[11]
			# print data[12]
			# print data[13]
			# print data[14]
			# print data[15]
			
			if not data: #if list is empty
				lot()
				print("Tag missing: Please Park in Pay-to-Park")
				lot_capacity = str(lot_capacity)
				#Send lot values to files
				with open("lcd.txt", "w") as lcd_file:
					lcd_file.write("%s\n" % (lot_capacity))
				if lot_new < (lot_capacity):
					with open("update.txt", "w") as text_file:
						text_file.write("%s\n" % (lot_capacity))
					with open("select.txt", "w") as sfile:
						sfile.write("%s\n" % (lot_numb))
					with open("nopass.txt", "w") as no_file:
						no_file.write("%s\n" % ("2"))
				print ( "Lot Capacity: " + lot_capacity + "/38" + '\n')
				lot_capacity=int(lot_capacity)
				text_file.close()
				sfile.close()
				no_file.close()
				lcd_file.close()
				#Denotes when text files have closed, ready for other prog. to open
				print('files closed')	
				break
			
			elif id_a == data:
				print "Pass Valid!"
				lot()
				lot_capacity = str(lot_capacity)
				#send lot values to files
				with open("lcd.txt", "w") as lcd_file:
					lcd_file.write("%s\n" % (lot_capacity))
				if lot_new < (lot_capacity):
					with open("update.txt", "w") as text_file:
						text_file.write("%s\n" % (lot_capacity))
					with open("select.txt", "w") as sfile:
						sfile.write("%s\n" % (lot_numb))
					with open("nopass.txt", "w") as no_file:
						no_file.write("%s\n" % ("0"))
				print ( "Lot Capacity: " + lot_capacity + "/38" + '\n')
				lot_capacity=int(lot_capacity)
				text_file.close()
				sfile.close()
				no_file.close()
				lcd_file.close()
				print('files closed')
				time.sleep(5)
				sys.stdout.flush()
				data[:]=[]
				break

			elif id_b == data:
				print "Pass Valid!"
				lot()
				lot_capacity = str(lot_capacity)
				#send lot values to files
				with open("lcd.txt", "w") as lcd_file:
					lcd_file.write("%s\n" % (lot_capacity))
				if lot_new < (lot_capacity):
					with open("update.txt", "w") as text_file:
						text_file.write("%s\n" % (lot_capacity))
					with open("select.txt", "w") as sfile:
						sfile.write("%s\n" % (lot_numb))
					with open("nopass.txt", "w") as no_file:
						no_file.write("%s\n" % ("0"))
				print ( "Lot Capacity: " + lot_capacity + "/38" + '\n')
				lot_capacity=int(lot_capacity)
				text_file.close()
				sfile.close()
				no_file.close()
				lcd_file.close()
				print('files closed')				
				time.sleep(5)
				sys.stdout.flush()
				data[:]=[]
				break

			elif id_c == data:
				print "Pass Valid!"
				lot() 
				lot_capacity = str(lot_capacity)
				#send lot capacity to file
				with open("lcd.txt", "w") as lcd_file:
					lcd_file.write("%s\n" % (lot_capacity))
				if lot_new < (lot_capacity):
					with open("update.txt", "w") as text_file:
						text_file.write("%s\n" % (lot_capacity))
					with open("select.txt", "w") as sfile:
						sfile.write("%s\n" % (lot_numb))
					with open("nopass.txt", "w") as no_file:
						no_file.write("%s\n" % ("0"))
				print ( "Lot Capacity: " + lot_capacity + "/38" + '\n')
				lot_capacity=int(lot_capacity)
				text_file.close()
				sfile.close()
				no_file.close()
				lcd_file.close()
				print('files closed')
				time.sleep(5)
				sys.stdout.flush()
				data[:]=[]
				break
				
			else:
				print "Pass Invalid\n"
				#Send signal to Zach that their pass is invalid
				with open("nopass.txt", "w") as no_file:
					no_file.write("%s\n" % ("1"))
					
				no_file.close()
				print('files closed')
				time.sleep(5)
				sys.stdout.flush()
				data[:]=[]
				break
				
			break
			continue
			
			

	sys.stdout.flush()		

	ser.write(string)

	ser.close()
	
#Main function: Calls Motion Sensor and only triggers RFID
#within desired distance range
def main():
	
	while True:
	
		if (get_distance() >= 10 and get_distance() <= 50):#Range between 10&50inches
			print("Distance is between 10 and 50!")
			print("RFID Active")
			startTime=time.time()							#Timers to test length of time
			RFIDmod()
			time.sleep(5)
			endTime=time.time()
			print('Timer took %s seconds' %(endTime-startTime))
			print '\n'
			time.sleep(1)
		
		else:
			print("Distance is out of range!")
			print("Invalid read- Continue Motion Detection")
			print '\n'
			time.sleep(1)
		break

	


	time.sleep(5)
	

schedule.every(.083).minutes.do(main) #sets up up 'Main' func. to run every 5 seconds

while 1:
	#print('begin program')
	startTime=time.time()
	schedule.run_pending()				#Runs Main func. every 4.98 seconds
	endTime=time.time()
	#print('sleeping begun')
	time.sleep(2)
	#print('sleeping over')
	print('%s' %(endTime-startTime))
