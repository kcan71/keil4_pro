#include "string.h"
#include "global_var.h"
#include "define.c"

void com1_work(void)   
{
  unsigned int i,int_buf0;

  if(!strncmp(Com1_data,"CH1 NO INPUT",12))
  {
    Com1_jig_state1 = 0x40000000;
  }
  else if(!strncmp(Com1_data,"CH2 NO INPUT",12))
  {
    Com1_jig_state2 = 0x40000000;
  }
  else if((!strncmp(Com1_data,"1A",2))||(!strncmp(Com1_data,"1X",2)))
  {
    Com1_jig_state1 |= 0x40000000;
    if(Com1_data[1] == 'A')//audio check mode
        Com1_jig_state1 |= 0x00000002;
    
    if(Com1_data[2] == 'U')//r video check
        Com1_jig_state1 |= 0x00000004;
    else if(Com1_data[2] == 'R')//r video check
        Com1_jig_state1 |= 0x00000008;
    
    if(Com1_data[3] == 'U')//g video check
        Com1_jig_state1 |= 0x00000010;
    else if(Com1_data[3] == 'G')//g video check
        Com1_jig_state1 |= 0x00000020;
    
    if(Com1_data[4] == 'U')//b video check
        Com1_jig_state1 |= 0x00000040;
    else if(Com1_data[4] == 'B')//b video check
        Com1_jig_state1 |= 0x00000080;
    
    if(Com1_data[6] != 'X')//timmming check
      Com1_jig_state1 |= (Com1_data[6] - 0x30) << 8;
    
    if(Com1_data[7] == 'H')
      Com1_jig_state1 |= 0x00002000;      
    else if(Com1_data[7] != 'X')
      Com1_jig_state1 |= 0x00001000;  
  }
  else if((!strncmp(Com1_data,"2A",2))||(!strncmp(Com1_data,"2X",2)))
  {
    Com1_jig_state2 |= 0x40000000;
    if(Com1_data[1] == 'A')//audio check mode
        Com1_jig_state2 |= 0x00000002;
    
    if(Com1_data[2] == 'U')//r video check
        Com1_jig_state2 |= 0x00000004;
    else if(Com1_data[2] == 'R')//r video check
        Com1_jig_state2 |= 0x00000008;
    
    if(Com1_data[3] == 'U')//g video check
        Com1_jig_state2 |= 0x00000010;
    else if(Com1_data[3] == 'G')//g video check
        Com1_jig_state2 |= 0x00000020;
    
    if(Com1_data[4] == 'U')//b video check
        Com1_jig_state2 |= 0x00000040;
    else if(Com1_data[4] == 'B')//b video check
        Com1_jig_state2 |= 0x00000080;
    
    if(Com1_data[6] != 'X')//timmming check
      Com1_jig_state2 |= (Com1_data[6] - 0x30) << 8;
    
    if(Com1_data[7] == 'H')
      Com1_jig_state2 |= 0x000002000;      
    else if(Com1_data[7] != 'X')
      Com1_jig_state2 |= 0x000001000;  
    
  }
  else if(Com1_num > 2)
  {   
    
    Printf_port = COM_RS485;
    putchar(':');
    putchar('D');
    putchar(0x31);
    if((Com1_data[0] == 'T')||(Com1_data[0] == 'U'))
    {
      putchar('V');
      int_buf0 = ':' + 'D' + 0x31 + 'V' + Send_data[1];
      Com1_num--;
      for(i = 3;i < Com1_num;i++)
        Com1_data[i] = Com1_data[i + 1];
      putchar(Send_data[1]);
    }    
    else if((Com1_data[0] == 0x38)&&(Com1_data[1] == 0x33))//edid data satet return
    {
      putchar('R');
      putchar(Com5_data[2]);
      putchar('E');
      putchar('D');
      putchar('S');
      int_buf0 = ':' + 'D' + 0x31 + 'R' + Com5_data[2] + 'E' + 'D' + 'S' + Com1_data[2];
      putchar(Com1_data[2]);
      Com1_num = 0;
    }    
	 else if((Com1_data[0] == 0x3a)&&(Com1_data[1] == 0x30))// check side state return
    {
      putchar('R');
      putchar(Com5_data[2]);
      putchar('S');
      putchar('D');
      putchar('S');
      int_buf0 = ':' + 'D' + 0x31 + 'R' + Com5_data[2] + 'S' + 'D' + 'S' + Com1_data[2];
      putchar(Com1_data[2]);
      Com1_num = 0;
    }    
    else
    {
      putchar('R');
      int_buf0 = ':' + 'D' + 0x31 + 'R' + 0x31;
      putchar(0x31);
    }
    

    for(i = 0;i < Com1_num;i++)
    {
      putchar(Com1_data[i]);
      int_buf0 += Com1_data[i];
    }
    int_buf0 &= 0x00ff;
    putchar(int_buf0);
    putchar(0x0d);
    putchar(0x0a);
  }
  if(Debug_mode)
  {
    int_buf0 = ':' + 'D' + 0x31 + 'R' + 0x31;
    Printf_port = COM_RS485;
    putchar(':');
    putchar('D');
    putchar(0x31);
    putchar('R');
    putchar(0x31);
    for(i = 0;i < Com1_num;i++)
    {
      putchar(Com1_data[i]);
      int_buf0 += Com1_data[i];
    }
    int_buf0 &= 0x00ff;
    putchar(int_buf0);
    putchar(0x0d);
    putchar(0x0a);
  }
}
void com2_work(void)   
{
  unsigned int i,int_buf0;

  if(!strncmp(Com2_data,"CH1 NO INPUT",12))
  {
    Com2_jig_state1 = 0x40000000;
  }
  else if(!strncmp(Com2_data,"CH2 NO INPUT",12))
  {
    Com2_jig_state2 = 0x40000000;
  }
  else if((!strncmp(Com2_data,"1A",2))||(!strncmp(Com2_data,"1X",2)))
  {
    Com2_jig_state1 |= 0x40000000;
    if(Com2_data[1] == 'A')//audio check mode
        Com2_jig_state1 |= 0x00000002;
    
    if(Com2_data[2] == 'U')//r video check
        Com2_jig_state1 |= 0x00000004;
    else if(Com2_data[2] == 'R')//r video check
        Com2_jig_state1 |= 0x00000008;
    
    if(Com2_data[3] == 'U')//g video check
        Com2_jig_state1 |= 0x00000010;
    else if(Com2_data[3] == 'G')//g video check
        Com2_jig_state1 |= 0x00000020;
    
    if(Com2_data[4] == 'U')//b video check
        Com2_jig_state1 |= 0x00000040;
    else if(Com2_data[4] == 'B')//b video check
        Com2_jig_state1 |= 0x00000080;
    
    if(Com2_data[6] != 'X')//timmming check
      Com2_jig_state1 |= (Com2_data[6] - 0x30) << 8;
    
    if(Com2_data[7] == 'H')
      Com2_jig_state1 |= 0x000002000;      
    else if(Com2_data[7] != 'X')
      Com2_jig_state1 |= 0x000001000;  
  }
  else if((!strncmp(Com2_data,"2A",2))||(!strncmp(Com2_data,"2X",2)))
  {
    Com2_jig_state2 |= 0x40000000;
    if(Com2_data[1] == 'A')//audio check mode
        Com2_jig_state2 |= 0x00000002;
    
    if(Com2_data[2] == 'U')//r video check
        Com2_jig_state2 |= 0x00000004;
    else if(Com2_data[2] == 'R')//r video check
        Com2_jig_state2 |= 0x00000008;
    
    if(Com2_data[3] == 'U')//g video check
        Com2_jig_state2 |= 0x00000010;
    else if(Com2_data[3] == 'G')//g video check
        Com2_jig_state2 |= 0x00000020;
    
    if(Com2_data[4] == 'U')//b video check
        Com2_jig_state2 |= 0x00000040;
    else if(Com2_data[4] == 'B')//b video check
        Com2_jig_state2 |= 0x00000080;
    
    if(Com2_data[6] != 'X')//timmming check
      Com2_jig_state2 |= (Com2_data[6] - 0x30) << 8;
    
    if(Com2_data[7] == 'H')
      Com2_jig_state2 |= 0x000002000;      
    else if(Com2_data[7] != 'X')
      Com2_jig_state2 |= 0x000001000;  
    
  }
  else if(Com2_num > 2)
  {   
    Printf_port = COM_RS485;
    putchar(':');
    putchar('D');
    putchar(0x32);
    if((Com2_data[0] == 'T')||(Com2_data[0] == 'U'))
    {
      putchar('V');
      int_buf0 = ':' + 'D' + 0x32 + 'V' + Send_data[1];
      Com2_num--;
      
      for(i = 3;i < Com2_num;i++)
        Com2_data[i] = Com2_data[i + 1];
      putchar(Send_data[1]);
    }
    else if((Com2_data[0] == 0x38)&&(Com2_data[1] == 0x33))
    {
      putchar('R');
      putchar(Com5_data[2]);
      putchar('E');
      putchar('D');
      putchar('S');
      int_buf0 = ':' + 'D' + 0x32 + 'R' + Com5_data[2] + 'E' + 'D' + 'S' + Com2_data[2];
      putchar(Com2_data[2]);
      Com2_num = 0;
    } 
	  else if((Com2_data[0] == 0x3a)&&(Com2_data[1] == 0x30))// check side state return
    {
      putchar('R');
      putchar(Com5_data[2]);
      putchar('S');
      putchar('D');
      putchar('S');
      int_buf0 = ':' + 'D' + 0x32 + 'R' + Com5_data[2] + 'S' + 'D' + 'S' + Com2_data[2];
      putchar(Com2_data[2]);
      Com2_num = 0;
    }    
    else
    {
      putchar('R');
      int_buf0 = ':' + 'D' + 0x32 + 'R' + 0x31;
      putchar(0x31);  
    }   
      
    for(i = 0;i < Com2_num;i++)
    {
       putchar(Com2_data[i]);
       int_buf0 += Com2_data[i];
    }
    int_buf0 &= 0x00ff;
    putchar(int_buf0);
    putchar(0x0d);
    putchar(0x0a);
  }
  if(Debug_mode)
  {
    int_buf0 = ':' + 'D' + 0x32 + 'R' + 0x31;
    Printf_port = COM_RS485;
    putchar(':');
    putchar('D');
    putchar(0x32);
    putchar('R');
    putchar(0x31);
    for(i = 0;i < Com2_num;i++)
    {
      putchar(Com2_data[i]);
      int_buf0 += Com2_data[i];
    }
    int_buf0 &= 0x00ff;
    putchar(int_buf0);
    putchar(0x0d);
    putchar(0x0a);
  }
}
void com3_work(void)   
{
  unsigned int i,int_buf0;

  if(!strncmp(Com3_data,"CH1 NO INPUT",12))
  {
    Com3_jig_state1 = 0x40000000;
  }
  else if(!strncmp(Com3_data,"CH2 NO INPUT",12))
  {
    Com3_jig_state2 = 0x40000000;
  }
  else if((!strncmp(Com3_data,"1A",2))||(!strncmp(Com3_data,"1X",2)))
  {
    Com3_jig_state1 |= 0x40000000;
    if(Com3_data[1] == 'A')//audio check mode
        Com3_jig_state1 |= 0x00000002;
    
    if(Com3_data[2] == 'U')//r video check
        Com3_jig_state1 |= 0x00000004;
    else if(Com3_data[2] == 'R')//r video check
        Com3_jig_state1 |= 0x00000008;
    
    if(Com3_data[3] == 'U')//g video check
        Com3_jig_state1 |= 0x00000010;
    else if(Com3_data[3] == 'G')//g video check
        Com3_jig_state1 |= 0x00000020;
    
    if(Com3_data[4] == 'U')//b video check
        Com3_jig_state1 |= 0x00000040;
    else if(Com3_data[4] == 'B')//b video check
        Com3_jig_state1 |= 0x00000080;
    
    if(Com3_data[6] != 'X')//timmming check
      Com3_jig_state1 |= (Com3_data[6] - 0x30) << 8;
    
    if(Com3_data[7] == 'H')
      Com3_jig_state1 |= 0x000002000;      
    else if(Com3_data[7] != 'X')
      Com3_jig_state1 |= 0x000001000;  
  }
  else if((!strncmp(Com3_data,"2A",2))||(!strncmp(Com3_data,"2X",2)))
  {
    Com3_jig_state2 |= 0x40000000;
    if(Com3_data[1] == 'A')//audio check mode
        Com3_jig_state2 |= 0x00000002;
    
    if(Com3_data[2] == 'U')//r video check
        Com3_jig_state2 |= 0x00000004;
    else if(Com3_data[2] == 'R')//r video check
        Com3_jig_state2 |= 0x00000008;
    
    if(Com3_data[3] == 'U')//g video check
        Com3_jig_state2 |= 0x00000010;
    else if(Com3_data[3] == 'G')//g video check
        Com3_jig_state2 |= 0x00000020;
    
    if(Com3_data[4] == 'U')//b video check
        Com3_jig_state2 |= 0x00000040;
    else if(Com3_data[4] == 'B')//b video check
        Com3_jig_state2 |= 0x00000080;
    
    if(Com3_data[6] != 'X')//timmming check
      Com3_jig_state2 |= (Com3_data[6] - 0x30) << 8;
    
    if(Com3_data[7] == 'H')
      Com3_jig_state2 |= 0x000002000;      
    else if(Com3_data[7] != 'X')
      Com3_jig_state2 |= 0x000001000;  
    
  }
  else if(Com3_num > 2)
  {   
    Printf_port = COM_RS485;
    putchar(':');
    putchar('D');
    putchar(0x33);
    if((Com3_data[0] == 'T')||(Com3_data[0] == 'U'))
    {
      putchar('V');
      int_buf0 = ':' + 'D' + 0x33 + 'V' + Send_data[1];
      Com3_num--;
      for(i = 3;i < Com3_num;i++)
        Com3_data[i] = Com3_data[i + 1];
      putchar(Send_data[1]);
    }
    else if((Com3_data[0] == 0x38)&&(Com3_data[1] == 0x33))
    {
      putchar('R');
      putchar(Com5_data[2]);
      putchar('E');
      putchar('D');
      putchar('S');
      int_buf0 = ':' + 'D' + 0x33 + 'R' + Com5_data[2] + 'E' + 'D' + 'S' + Com3_data[2];
      putchar(Com3_data[2]);
      Com3_num = 0;
    } 
	  else if((Com3_data[0] == 0x3a)&&(Com3_data[1] == 0x30))// check side state return
    {
      putchar('R');
      putchar(Com5_data[2]);
      putchar('S');
      putchar('D');
      putchar('S');
      int_buf0 = ':' + 'D' + 0x33 + 'R' + Com5_data[2] + 'S' + 'D' + 'S' + Com3_data[2];
      putchar(Com3_data[2]);
      Com3_num = 0;
    }    
    else
    {
      putchar('R');
      int_buf0 = ':' + 'D' + 0x33 + 'R' + 0x31;
      putchar(0x31);
    }
    
    for(i = 0;i < Com3_num;i++)
    {
      putchar(Com3_data[i]);
      int_buf0 += Com3_data[i];
    }
    int_buf0 &= 0x00ff;
    putchar(int_buf0);
    putchar(0x0d);
    putchar(0x0a);
  }
  if(Debug_mode)
  {
    int_buf0 = ':' + 'D' + 0x33 + 'R' + 0x31;
    Printf_port = COM_RS485;
    putchar(':');
    putchar('D');
    putchar(0x33);
    putchar('R');
    putchar(0x31);
    for(i = 0;i < Com3_num;i++)
    {
      putchar(Com3_data[i]);
      int_buf0 += Com3_data[i];
    }
    int_buf0 &= 0x00ff;
    putchar(int_buf0);
    putchar(0x0d);
    putchar(0x0a);
  }
}
void com4_work(void)   
{
  unsigned int i,int_buf0;

  if(!strncmp(Com4_data,"CH1 NO INPUT",12))
  {
    Com4_jig_state1 = 0x40000000;
  }
  else if(!strncmp(Com4_data,"CH2 NO INPUT",12))
  {
    Com4_jig_state2 = 0x40000000;
  }
  else if((!strncmp(Com4_data,"1A",2))||(!strncmp(Com4_data,"1X",2)))
  {
    Com4_jig_state1 |= 0x40000000;
    if(Com4_data[1] == 'A')//audio check mode
        Com4_jig_state1 |= 0x00000002;
    
    if(Com4_data[2] == 'U')//r video check
        Com4_jig_state1 |= 0x00000004;
    else if(Com4_data[2] == 'R')//r video check
        Com4_jig_state1 |= 0x00000008;
    
    if(Com4_data[3] == 'U')//g video check
        Com4_jig_state1 |= 0x00000010;
    else if(Com4_data[3] == 'G')//g video check
        Com4_jig_state1 |= 0x00000020;
    
    if(Com4_data[4] == 'U')//b video check
        Com4_jig_state1 |= 0x00000040;
    else if(Com4_data[4] == 'B')//b video check
        Com4_jig_state1 |= 0x00000080;
    
    if(Com4_data[6] != 'X')//timmming check
      Com4_jig_state1 |= (Com4_data[6] - 0x30) << 8;
    
    if(Com4_data[7] == 'H')
      Com4_jig_state1 |= 0x000002000;      
    else if(Com4_data[7] != 'X')
      Com4_jig_state1 |= 0x000001000;  
  }
  else if((!strncmp(Com4_data,"2A",2))||(!strncmp(Com4_data,"2X",2)))
  {
    Com4_jig_state2 |= 0x40000000;
    if(Com4_data[1] == 'A')//audio check mode
        Com4_jig_state2 |= 0x00000002;
    
    if(Com4_data[2] == 'U')//r video check
        Com4_jig_state2 |= 0x00000004;
    else if(Com4_data[2] == 'R')//r video check
        Com4_jig_state2 |= 0x00000008;
    
    if(Com4_data[3] == 'U')//g video check
        Com4_jig_state2 |= 0x00000010;
    else if(Com4_data[3] == 'G')//g video check
        Com4_jig_state2 |= 0x00000020;
    
    if(Com4_data[4] == 'U')//b video check
        Com4_jig_state2 |= 0x00000040;
    else if(Com4_data[4] == 'B')//b video check
        Com4_jig_state2 |= 0x00000080;
    
    if(Com4_data[6] != 'X')//timmming check
      Com4_jig_state2 |= (Com4_data[6] - 0x30) << 8;
    
    if(Com4_data[7] == 'H')
      Com4_jig_state2 |= 0x000002000;      
    else if(Com4_data[7] != 'X')
      Com4_jig_state2 |= 0x000001000;  
    
  }
  else if(Com4_num > 2)
  {   
    Printf_port = COM_RS485;
    putchar(':');
    putchar('D');
    putchar(0x34);
    if((Com4_data[0] == 'T')||(Com4_data[0] == 'U'))
    {
      putchar('V');
      int_buf0 = ':' + 'D' + 0x34 + 'V' + Send_data[1];
      Com4_num--;
      for(i = 3;i < Com4_num;i++)
        Com4_data[i] = Com4_data[i + 1];
      putchar(Send_data[1]);
    }
    else if((Com4_data[0] == 0x38)&&(Com4_data[1] == 0x33))
    {
      putchar('R');
      putchar(Com5_data[2]);
      putchar('E');
      putchar('D');
      putchar('S');
      int_buf0 = ':' + 'D' + 0x34 + 'R' + Com5_data[2] + 'E' + 'D' + 'S' + Com4_data[2];
      putchar(Com4_data[2]);
      Com4_num = 0;
    } 
	  else if((Com4_data[0] == 0x3a)&&(Com4_data[1] == 0x30))// check side state return
    {
      putchar('R');
      putchar(Com5_data[2]);
      putchar('S');
      putchar('D');
      putchar('S');
      int_buf0 = ':' + 'D' + 0x34 + 'R' + Com5_data[2] + 'S' + 'D' + 'S' + Com4_data[2];
      putchar(Com4_data[2]);
      Com4_num = 0;
    }    
    else
    {
      putchar('R');
      int_buf0 = ':' + 'D' + 0x34 + 'R' + 0x31;
      putchar(0x31);
    }
    
    for(i = 0;i < Com4_num;i++)
    {
      putchar(Com4_data[i]);
      int_buf0 += Com4_data[i];
    }
    int_buf0 &= 0x00ff;
    putchar(int_buf0);
    putchar(0x0d);
    putchar(0x0a);
  }
  if(Debug_mode)
  {
    int_buf0 = ':' + 'D' + 0x34 + 'R' + 0x31;
    Printf_port = COM_RS485;
    putchar(':');
    putchar('D');
    putchar(0x34);
    putchar('R');
    putchar(0x31);
    for(i = 0;i < Com4_num;i++)
    {
      putchar(Com4_data[i]);
      int_buf0 += Com4_data[i];
    }
    int_buf0 &= 0x00ff;
    putchar(int_buf0);
    putchar(0x0d);
    putchar(0x0a);
  }
}

void rs232c_data_send(void)
{
  unsigned int i;

  if(Com5_data[0] == 0x31)
    Printf_port = COM_PORT1;
  else if(Com5_data[0] == 0x32)
    Printf_port = COM_PORT2;
  else if(Com5_data[0] == 0x33)
    Printf_port = COM_PORT3;
  else if(Com5_data[0] == 0x34)
    Printf_port = COM_PORT4;
  if((Com5_data[0] > 0x30)&&(Com5_data[0] < 0x35))
  {
    putchar(STX);
    for(i = 0;i < Send_num;i++)
    {      
      putchar(Send_data[i]);
    }
    putchar(ETX);
  }
}

void version_send(void)
{
	unsigned int i,int_buf0,send_num;
	
	Com5_data[1] = 'R';
	
	int_buf0 = ':';
	int_buf0 += 'D';	
  Com5_data[1] = 'V';
   
	send_num = 2;
	Com5_data[send_num++] = Pro_ver[1];
	Com5_data[send_num++] = Pro_ver[2];
	Com5_data[send_num++] = Pro_ver[3];
	Com5_data[send_num++] = Pro_ver[4];
	Com5_data[send_num++] = Pro_ver[5];
  //printf("\n\rMCU  : MRG-104-1%s\n\r",Pro_ver);
	for(i = 0;i < send_num;i++)
		int_buf0 += Com5_data[i];
	int_buf0 &= 0x00ff;
	Com5_data[7] = int_buf0;
	
	Printf_port = COM_RS485;
	
	putchar(':');
	putchar('D');
	for(i = 0;i < 8;i++)
		putchar(Com5_data[i]);
	putchar(0x0d);
	putchar(0x0a);
	
}

void rs485_ack_command(void)
{
	unsigned int i,int_buf0;
	
	Com5_data[1] = 'R';
	
	int_buf0 = ':';
	int_buf0 += 'D';
	for(i = 0;i < (Com5_num - 1);i++)
		int_buf0 += Com5_data[i];
	int_buf0 &= 0x00ff;
	Com5_data[7] = int_buf0;
	
	Printf_port = COM_RS485;
	
	putchar(':');
	putchar('D');
	for(i = 0;i < Com5_num;i++)
		putchar(Com5_data[i]);
	putchar(0x0d);
	putchar(0x0a);
}

void port_state_chk(void)
{
  unsigned int i,check_data,int_buf0;   
  
  if((Com5_data[0] == 0x31)&&(Com5_data[2] == 0x31))
  {
    check_data = Com1_jig_state1;
  }
  else if((Com5_data[0] == 0x31)&&(Com5_data[2] == 0x32))
  {
    check_data = Com1_jig_state2;
  }
  else if((Com5_data[0] == 0x32)&&(Com5_data[2] == 0x31))
  {
    check_data = Com2_jig_state1;
  }
  else if((Com5_data[0] == 0x32)&&(Com5_data[2] == 0x32))
  {
    check_data = Com2_jig_state2;
  }
  else if((Com5_data[0] == 0x33)&&(Com5_data[2] == 0x31))
  {
    check_data = Com3_jig_state1;
  }
  else if((Com5_data[0] == 0x33)&&(Com5_data[2] == 0x32))
  {
    check_data = Com3_jig_state2;
  }
  else if((Com5_data[0] == 0x34)&&(Com5_data[2] == 0x31))
  {
    check_data = Com4_jig_state1;
  }
  else if((Com5_data[0] == 0x34)&&(Com5_data[2] == 0x32))
  {
    check_data = Com4_jig_state2;
  }  
  
  Com5_num = 5;
  if(check_data & 0x80000000)
  {
    if(check_data & 0x40000000)
    {
      Com5_data[Com5_num++] = 'F';
      Com5_data[Com5_num++] = 'I';
      Com5_data[Com5_num++] = 'N';
      Com5_data[Com5_num++] = 'I';
    }
    else
    {
      Com5_data[Com5_num++] = 'T';
      Com5_data[Com5_num++] = 'E';
      Com5_data[Com5_num++] = 'S';
      Com5_data[Com5_num++] = 'T';
    }
  }
  else if(check_data & 0x40000000)
  {
    Com5_data[Com5_num++] = 'F';
    Com5_data[Com5_num++] = 'I';
    Com5_data[Com5_num++] = 'N';
    Com5_data[Com5_num++] = 'I';
  }
  else if(check_data == 0x00000000)
  {
    Com5_data[Com5_num++] = 'S';
    Com5_data[Com5_num++] = 'T';
    Com5_data[Com5_num++] = 'O';
    Com5_data[Com5_num++] = 'P';
  }
	
  Com5_data[4] = Com5_data[2];
  Com5_data[2] = Com5_data[0];
  Com5_data[0] = ':';
  Com5_data[1] = 'D';
  Com5_data[3] = 'R';
  //Com5_data[4] = Com5_data[0];

  int_buf0 = 0;
  for(i = 0;i < Com5_num;i++)
    int_buf0 += Com5_data[i];
   
  int_buf0 &= 0x00ff;
  Com5_data[Com5_num++] = int_buf0;

  Printf_port = COM_RS485;

  for(i = 0;i < Com5_num;i++)
    putchar(Com5_data[i]);
  putchar(0x0d);
  putchar(0x0a);
}

void port_result_chk(void)
{
  unsigned int i,check_data,int_buf0;   

  if((Com5_data[0] == 0x31)&&(Com5_data[2] == 0x31))
  {
    check_data = Com1_jig_state1;
  }
  else if((Com5_data[0] == 0x31)&&(Com5_data[2] == 0x32))
  {
    check_data = Com1_jig_state2;
  }
  else if((Com5_data[0] == 0x32)&&(Com5_data[2] == 0x31))
  {
    check_data = Com2_jig_state1;
  }
  else if((Com5_data[0] == 0x32)&&(Com5_data[2] == 0x32))
  {
    check_data = Com2_jig_state2;
  }
  else if((Com5_data[0] == 0x33)&&(Com5_data[2] == 0x31))
  {
    check_data = Com3_jig_state1;
  }
  else if((Com5_data[0] == 0x33)&&(Com5_data[2] == 0x32))
  {
    check_data = Com3_jig_state2;
  }
  else if((Com5_data[0] == 0x34)&&(Com5_data[2] == 0x31))
  {
    check_data = Com4_jig_state1;
  }
  else if((Com5_data[0] == 0x34)&&(Com5_data[2] == 0x32))
  {
    check_data = Com4_jig_state2;
  }  
    
    
  Com5_num = 5;
  if(check_data & 0x80000000)
  {
    if(check_data & 0x40000000)
    {
      int_buf0 = check_data & 0x00000003;
      if(int_buf0 == 0x00000002)
        Com5_data[Com5_num++] = 'A';
      else if(int_buf0 == 0x00000000)
        Com5_data[Com5_num++] = 'X';
      
      int_buf0 = check_data & 0x0000000c;
      if(int_buf0 ==  0x00000000)
        Com5_data[Com5_num++] = 'X';
      else if(int_buf0 ==  0x00000004)
        Com5_data[Com5_num++] = 'U';
      else if(int_buf0 ==  0x00000008)
        Com5_data[Com5_num++] = 'R';
      
      int_buf0 = check_data & 0x00000030;
      if(int_buf0 ==  0x00000000)
        Com5_data[Com5_num++] = 'X';
      else if(int_buf0 ==  0x00000010)
        Com5_data[Com5_num++] = 'U';
      else if(int_buf0 ==  0x00000020)
        Com5_data[Com5_num++] = 'G';
      
      int_buf0 = check_data & 0x000000c0;
      if(int_buf0 ==  0x00000000)
        Com5_data[Com5_num++] = 'X';
      else if(int_buf0 ==  0x00000040)
        Com5_data[Com5_num++] = 'U';
      else if(int_buf0 ==  0x00000080)
        Com5_data[Com5_num++] = 'B';
 
      Com5_data[Com5_num++] = 'T';
      int_buf0 = (check_data & 0x00000f00) >> 8;
      if((int_buf0 > 3)&&(int_buf0 < 10))
        Com5_data[Com5_num++] = 0x30 + int_buf0;
      else
        Com5_data[Com5_num++] = 'X';
      
      int_buf0 = check_data & 0x00003000;
      if(int_buf0 != 0x00001000)//hdcp check
      {  
        if(int_buf0 == 0x00002000)
          Com5_data[Com5_num++] = 'H';
        else if(int_buf0 == 0x00000000)
          Com5_data[Com5_num++] = 'X';
      }
    }
    else
    {
      Com5_data[Com5_num++] = 'T';
      Com5_data[Com5_num++] = 'E';
      Com5_data[Com5_num++] = 'S';
      Com5_data[Com5_num++] = 'T';
    }
  }
  else if(check_data & 0x40000000)
  {
    Com5_data[Com5_num++] = 'N';
    Com5_data[Com5_num++] = 'O';
    Com5_data[Com5_num++] = ' ';
    Com5_data[Com5_num++] = 'I';
    Com5_data[Com5_num++] = 'N';
    Com5_data[Com5_num++] = 'P';
    Com5_data[Com5_num++] = 'U';
    Com5_data[Com5_num++] = 'T';
  }
  else if(check_data == 0x00000000)
  {
    Com5_data[Com5_num++] = 'S';
    Com5_data[Com5_num++] = 'T';
    Com5_data[Com5_num++] = 'O';
    Com5_data[Com5_num++] = 'P';
    Com5_data[Com5_num++] = 'T';
    Com5_data[Com5_num++] = 'X';
    Com5_data[Com5_num++] = 'X';
  }
	
  Com5_data[4] = Com5_data[2];
  Com5_data[2] = Com5_data[0];
  Com5_data[0] = ':';
  Com5_data[1] = 'D';
  Com5_data[3] = 'T';
  //Com5_data[4] = 0x31;

  int_buf0 = 0;
  for(i = 0;i < Com5_num;i++)
    int_buf0 += Com5_data[i];
   
  int_buf0 &= 0x00ff;
  Com5_data[Com5_num++] = int_buf0;

  Printf_port = COM_RS485;

  for(i = 0;i < Com5_num;i++)
    putchar(Com5_data[i]);
  putchar(0x0d);
  putchar(0x0a);
}

unsigned char auto_command_ack(unsigned char channel)
{
  if(Com5_data[0] == 0x31)
    Printf_port = COM_PORT1;
  else if(Com5_data[0] == 0x32)
    Printf_port = COM_PORT2;
  else if(Com5_data[0] == 0x33)
    Printf_port = COM_PORT3;
  else if(Com5_data[0] == 0x34)
    Printf_port = COM_PORT4;
  if((Com5_data[0] > 0x30)&&(Com5_data[0] < 0x35))
  {
    putchar(STX);
    putchar(0x3a);
    putchar(0x32);
    putchar(0x30);
    putchar(channel);
    putchar(ETX);
    Ack_tim_chk = 0;
    Ack_06_check |= 0x01;
    while(Ack_tim_chk < 30000)
    {
      if(Com5_data[0] == 0x31)
      {
        if((Com1_state == 1)&&(Com1_input_tim_chk > OVER_TIME))
        {
          Ack_06_check &= 0xfe;
          Com1_state = 0;
          Com_input_time_state &= 0xfe;
          Com1_input_tim_chk = 0;
          break;
        }
      }
      else if(Com5_data[0] == 0x32)
      {
        if((Com2_state == 1)&&(Com2_input_tim_chk > OVER_TIME))
        {
          Ack_06_check &= 0xfe;
          Com2_state = 0;
          Com_input_time_state &= 0xfd;
          Com2_input_tim_chk = 0;
          break;
        }
      }
      else if(Com5_data[0] == 0x33)
      {
        if((Com3_state == 1)&&(Com3_input_tim_chk > OVER_TIME))
        {
          Ack_06_check &= 0xfe;
          Com3_state = 0;
          Com_input_time_state &= 0xfb;
          Com3_input_tim_chk = 0;
          break;
        }
      }
      else if(Com5_data[0] == 0x34)
      {
        if((Com4_state == 1)&&(Com4_input_tim_chk > OVER_TIME))
        {
          Ack_06_check &= 0xfe;
          Com4_state = 0;
          Com_input_time_state &= 0xf7;
          Com1_input_tim_chk = 0;
          break;
        }
      }
      HAL_Delay(50);   
    }
  }
   //Printf_port = COM_RS485;
   //printf("Final Ack_tim_chk %d\r\n",Ack_tim_chk);
   return(Ack_06_check);
}

void time_over_error_return(void)
{
  unsigned int int_buf0;

  int_buf0 = ':' + 'D' + Com5_data[1] + 'R' + Com5_data[3] + 'T' + 'I' + 'M' + 'O';
  int_buf0 &= 0x00ff;

  Printf_port = COM_RS485;

  putchar(':');
  putchar('D');
  putchar(Com5_data[1]);
  putchar('R');
  putchar(Com5_data[3]);
  putchar('T');
  putchar('I');
  putchar('M');
  putchar('O');	
  putchar(int_buf0);
  putchar(0x0d);
  putchar(0x0a);
}

void com5_work(void)   
{
  unsigned char buf0;
  unsigned int i,int_buf0;

  int_buf0 = ':';
  int_buf0 += 'D';	
  for(i = 0;i < (Com5_num - 1);i++)
  int_buf0 += Com5_data[i];

  int_buf0 &= 0x00ff;
	
  if(int_buf0 == Com5_data[Com5_num - 1])//check sum ok
  {
    Send_num = 0;    
    if((Com5_data[3] == 'V')&&(Com5_data[4] =='E' )&&(Com5_data[5] =='R' )&&(Com5_data[6] =='?' ))//program version 확인
    {
      if((Com5_data[2] == 0x31)||(Com5_data[2] == 0x32)||(Com5_data[2] == 0x33))//msdt-4060 program version(0x31 ch1,0x32 ch2,0x33 ch1 ch2)
      {
        Send_data[Send_num++] = 0x35;
        Send_data[Send_num++] = Com5_data[2];
        rs232c_data_send();
      }
      else if(Com5_data[2] == 0x30)//mrg-104 program version
      {
        version_send();
      }
    }      
    else if((Com5_data[3] == 'T')&&(Com5_data[4] =='O')&&(Com5_data[5] =='N'))//check mode on(1,2,3,4)
    {
		Ack_tim_chk = 0;
      buf0 = auto_command_ack(Com5_data[2]);
      //HAL_Delay(500);

      if((buf0 & 0x01) == 0x00)
      {
        Send_data[Send_num++] = Com5_data[2];
        Send_data[Send_num++] = 0x30;
        Send_data[Send_num++] = Com5_data[6];
        
        if(Com5_data[2] == 0x31)
        {
          if(Com5_data[0] == 0x31)
            Com1_jig_state1 = 0x80000000;
          else if(Com5_data[0] == 0x32)
            Com2_jig_state1 = 0x80000000;
          else if(Com5_data[0] == 0x33)
            Com3_jig_state1 = 0x80000000;
          else if(Com5_data[0] == 0x34)
            Com4_jig_state1 = 0x80000000;
        }
        else if(Com5_data[2] == 0x32)
        {
          if(Com5_data[0] == 0x31)
            Com1_jig_state2 = 0x80000000;
          else if(Com5_data[0] == 0x32)
            Com2_jig_state2 = 0x80000000;
          else if(Com5_data[0] == 0x33)
            Com3_jig_state2 = 0x80000000;
          else if(Com5_data[0] == 0x34)
            Com4_jig_state2 = 0x80000000;
        }
        rs232c_data_send();
        //HAL_Delay(300);
        rs485_ack_command();
      }
      else
      {
        time_over_error_return();
      }
    }
    else if((Com5_data[3] == 'T')&&(Com5_data[4] =='S')&&(Com5_data[5] =='O')&&(Com5_data[6] =='F'))//cc off
    {
      Send_data[Send_num++] = 0x3a;
      Send_data[Send_num++] = 0x33;
      //Send_data[Send_num++] = 0x30;
      if(Com5_data[2] == 0x31)
      {
        Send_data[Send_num++] = 0x33;
        if(Com5_data[0] == 0x31)
          Com1_jig_state1 = 0;
        else if(Com5_data[0] == 0x32)
          Com2_jig_state1 = 0;
        else if(Com5_data[0] == 0x33)
          Com3_jig_state1 = 0;
        else if(Com5_data[0] == 0x34)
          Com4_jig_state1 = 0;
      }
      else if(Com5_data[2] == 0x32)
      {
        Send_data[Send_num++] = 0x35;
        if(Com5_data[0] == 0x31)
          Com1_jig_state2 = 0;
        else if(Com5_data[0] == 0x32)
          Com2_jig_state2 = 0;
        else if(Com5_data[0] == 0x33)
          Com3_jig_state2 = 0;
        else if(Com5_data[0] == 0x34)
          Com4_jig_state2 = 0;
      }
      else
      {
        Send_data[Send_num++] = 0x30;
      }
      rs232c_data_send();
      rs485_ack_command();
    }
    else if((Com5_data[3] == 'S')&&(Com5_data[4] =='T')&&(Com5_data[5] =='S')&&(Com5_data[6] =='?'))//test state 확인
    {
      port_state_chk();
    }
    else if((Com5_data[3] == 'R')&&(Com5_data[4] =='E')&&(Com5_data[5] =='S')&&(Com5_data[6] =='?'))//test result 확인
    {
      port_result_chk();
    }
    else if((Com5_data[0] != 0x30)&&(Com5_data[2] == 'R')&&(Com5_data[3] == 'E')&&(Com5_data[4] =='S')&&(Com5_data[5] =='E')&&(Com5_data[6] =='T'))//reset
    {
      Send_data[Send_num++] = 0x50;
      Send_data[Send_num++] = 0x31;
      Send_data[Send_num++] = 0x32;
      Send_data[Send_num++] = 0x33;
      Send_data[Send_num++] = 0x34;
      rs232c_data_send();
      rs485_ack_command();
    }
    else if((Com5_data[3] == 'A')&&(Com5_data[4] =='U')&&(Com5_data[5] =='T')&&(Com5_data[6] =='O'))//auto mode
    {
      Send_data[Send_num++] = 0x3a;
      Send_data[Send_num++] = 0x32;
      Send_data[Send_num++] = 0x30;
      rs232c_data_send();
      rs485_ack_command();
    }
    else if((Com5_data[0] == 0x30)&&(Com5_data[2] == 'R')&&(Com5_data[3] == 'E')&&(Com5_data[4] =='S')&&(Com5_data[5] =='E')&&(Com5_data[6] == 'T'))//reset mode
    {
      Re_start_mode = 1;
      rs485_ack_command();
    }
    else if((Com5_data[3] == 'D')&&(Com5_data[4] =='E')&&(Com5_data[5] =='B')&&(Com5_data[6] == 0x30))//debug mode off
    {
      Debug_mode = 0;
      rs485_ack_command();
    }
    else if((Com5_data[3] == 'D')&&(Com5_data[4] =='E')&&(Com5_data[5] =='B')&&(Com5_data[6] == 0x31))//debug mode on
    {
      Debug_mode = 1;
      rs485_ack_command();
    }
    else if((Com5_data[3] == 'E')&&(Com5_data[4] =='D')&&(Com5_data[5] =='W'))//2019.02.11 //edid data write
    {
      Send_data[Send_num++] = 0x38;
      Send_data[Send_num++] = 0x31;
      Send_data[Send_num++] = Com5_data[6];
      rs232c_data_send();
      //rs485_ack_command();
    }
    else if((Com5_data[3] == 'E')&&(Com5_data[4] =='D')&&(Com5_data[5] =='S'))//2019.02.11 //edid data state
    {
      Send_data[Send_num++] = 0x38;
      Send_data[Send_num++] = 0x33;
      Send_data[Send_num++] = 0x30;
      rs232c_data_send();
      //rs485_ack_command();
    }
	 else if((Com5_data[3] == 'S')&&(Com5_data[4] =='D')&&(Com5_data[5] =='W'))//2019.02.11 //how many check side?
    {
      Send_data[Send_num++] = 0x3a;
      Send_data[Send_num++] = 0x31;
      Send_data[Send_num++] = Com5_data[6];//0x30 A only side check, 0x31 A and B side check
      rs232c_data_send();
      //rs485_ack_command();
    }
    else if((Com5_data[3] == 'S')&&(Com5_data[4] =='D')&&(Com5_data[5] =='S'))//2019.02.11 //check side state
    {
      Send_data[Send_num++] = 0x3a;
      Send_data[Send_num++] = 0x31;
      Send_data[Send_num++] = 0x32;
      rs232c_data_send();
      //rs485_ack_command();
    }
    else if((Com5_data[3] == 's')&&(Com5_data[4] =='t')&&(Com5_data[5] =='a')&&(Com5_data[6] == 't'))//debug mode on
    {
      printf("Com1_jig_state1 = 0x%04x\r\n",Com1_jig_state1);
      printf("Com1_jig_state2 = 0x%04x\r\n",Com1_jig_state2);
      printf("Com2_jig_state1 = 0x%04x\r\n",Com2_jig_state1);
      printf("Com2_jig_state2 = 0x%04x\r\n",Com2_jig_state2);
      printf("Com3_jig_state1 = 0x%04x\r\n",Com3_jig_state1);
      printf("Com3_jig_state2 = 0x%04x\r\n",Com3_jig_state2);
      printf("Com4_jig_state1 = 0x%04x\r\n",Com4_jig_state1);
      printf("Com4_jig_state2 = 0x%04x\r\n",Com4_jig_state2);
    }
  }
  else
  {
    //Printf_port = COM_RS485;
    //printf(":D%d check sum error %02x,%02x\r\n",Com5_data[0],int_buf0,Com5_data[Com5_num - 1]);
  }
}
