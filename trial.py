import os

def move(l, r):
  os.system('echo "17={0}" > /dev/pi-blaster && echo "18={1}" > /dev/pi-blaster'.format(l, r) )
def fwd(distance):
  move(0.3,0.7)
  stp()
  print (distance)
def rev (distance):
  move(0.7,0.3)
  stp()
  print (distance)
def stp():
    os.system('echo "release 17" > /dev/pi-blaster  &&  echo "release 18" > /dev/pi-blaster')
def rt (vector, angle):
  #set navpoint
  #get vector
  #save orientation
  #move along vector to navpoint
  #check orientation to navpoint
  #get new vector
  #move along vector
  for x in xrange(angle):
    move(0.7, 0.7)
  stp()
  print(angle)

def lt (vector, angle):
  for x in xrange(angle):
    move(0.3, 0.3)
  stp()
  print(angle)
