#include <sys/types.h>

#ifndef __UDP_DATA_STRUCT_H
#define __UDP_DATA_STRUCT_H

#define UDP_DATA_LENGTH sizeof(udp_data)

#define u8  unsigned char

typedef struct udp_data {
	int check_udp_front;	
	
	float position_UpToDown_udp;
  float speed_UpToDown_udp;
  float current_UpToDown_udp;	
	
  u8 pc_ip_udp[4];
  u8 stm32_ip_udp[4];
  u8 hardware_id_udp[4];
  float position_DownToUp_udp;
  float speed_DownToUp_udp;
  float current_DownToUp_udp;
  float temperature_DownToUp_udp;

  float acceleration_1_DownToUp_udp;  //?????6byte
  float acceleration_2_DownToUp_udp;
  float acceleration_3_DownToUp_udp;

  float angular_speed_1_DownToUp_udp;  //?????6byte
  float angular_speed_2_DownToUp_udp;
  float angular_speed_3_DownToUp_udp;

  float rpy_angle_r_DownToUp_udp;  //???RPY??6byte
  float rpy_angle_p_DownToUp_udp;
  float rpy_angle_y_DownToUp_udp;

	
	int check_udp_back;
	
} udp_data, *udp_data_ptr;

#endif
