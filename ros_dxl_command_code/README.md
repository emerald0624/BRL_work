check :
 > chmod +x filename.py
 
 > dxl ID & dxl Baudrate
 
 > change dxl_init.py 

talker.py : motor angle command (-180~180 --> 0~4095)

listenser.py : talker test

dxl_init.py : dxl initialize 

dxl_pos_des_v4 : dxl command code


CMD : 
 > cm
 
 > roscore
 
 > rosrun ros_dxl_command_code dxl_init.py
 
 > rosrun ros_dxl_command_code dxl_pos_des_v4.py
 
 > rosrun ros_dxl_command_code talker.py
