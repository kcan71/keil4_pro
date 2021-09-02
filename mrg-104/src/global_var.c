#include "global_var.h"
           
unsigned char Printf_port,Fpga_yy_ver,Fpga_mm_ver,Fpga_dd_ver,Fpga_ver_ver;
unsigned char Com1_state,Com1_num,Data_com1,Com1_input_tim_chk;
unsigned char Com2_state,Com2_num,Data_com2,Com2_input_tim_chk;
unsigned char Com3_state,Com3_num,Data_com3,Com3_input_tim_chk;
unsigned char Com4_state,Com4_num,Data_com4,Com4_input_tim_chk;
unsigned char Com5_state,Com5_num,Data_com5,Com5_input_tim_chk;
char Com1_data[COM_DATA_SIZE],Com2_data[COM_DATA_SIZE],Com3_data[COM_DATA_SIZE],Com4_data[COM_DATA_SIZE],Com5_data[COM_DATA_SIZE];
unsigned char Com_input_time_state,Send_num,Send_data[10],Pro_ver[7],Ack_06_check;

unsigned int Com1_jig_state1,Com2_jig_state1,Com3_jig_state1,Com4_jig_state1,Ack_tim_chk;
unsigned int Com1_jig_state2,Com2_jig_state2,Com3_jig_state2,Com4_jig_state2;

unsigned char Re_start_mode;

unsigned char Debug_mode,Test_data;

unsigned char Com_ack_chk;
unsigned int Time_sec,Time_hour;



//const unsigned int timming[10][14] = 
