#!/usr/bin/env python
import rospy
import time
import serial
from std_msgs.msg import Float32


ser = serial.Serial(port = '/dev/ttyUSB0',baudrate=115200)

def talker():
    pub1 = rospy.Publisher('force1', Float32, queue_size=1)
    pub2 = rospy.Publisher('force2', Float32, queue_size=1)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(400) # 10hz
    while not rospy.is_shutdown():
        response = ser.readline()
        where = response.find(',')
        va1 = float(response[:where])
        va2 = float(response[where+1:])
        
        #rospy.loginfo(va1)
        #rospy.loginfo(va2)
        pub1.publish(va1)
        pub2.publish(va2)
        rate.sleep()
if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
