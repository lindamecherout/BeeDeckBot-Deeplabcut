
/*
 * author : Lina Le Guellec
 * date : 08/09/2023
 * This code sets the 2 axes of the robotic flower in motion. 
 * The robotic flower imitates the movement of a flower.
 * The frequencies, amplitudes and phase of the horizontal and vertical axes are chosen randomly each time the switch is triggered.
 */



#include <Arduino.h>
#include <MatrixMath.h>
#include <DynamixelShield.h>
#include <Keyboard.h>


#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
  #define DEBUG_SERIAL SerialUSB    
#else
  #define DEBUG_SERIAL Serial1
#endif


#define CW_ANGLE_LIMIT_ADDR         6
#define CCW_ANGLE_LIMIT_ADDR        8
#define ANGLE_LIMIT_ADDR_LEN        2
#define OPERATING_MODE_ADDR_LEN     2
#define TORQUE_ENABLE_ADDR          24
#define TORQUE_ENABLE_ADDR_LEN      1
#define LED_ADDR                    25
#define LED_ADDR_LEN                1
#define GOAL_POSITION_ADDR          30
#define GOAL_POSITION_ADDR_LEN      2
#define PRESENT_POSITION_ADDR       36
#define PRESENT_POSITION_ADDR_LEN   2
#define TIMEOUT 10    //default communication timeout 10ms

uint8_t Turn_on = 1;
uint8_t Turn_off = 0;

const uint8_t DXL_ID_z = 1;
const uint8_t DXL_ID_x = 2;

const float DXL_PROTOCOL_VERSION = 1.0;

uint16_t GoalPosition1 = 0;
uint16_t GoalPosition2 = 1023; //1023

DynamixelShield dxl;




     
#define pi    3.1415926535897932384626433832795

long t_0, t_1, t;

int angle[2] = {1023/2, 1023/2};
int init_angle[2];

float r[2] = {5, 12.14};

float Ax_tab[] = {3.0, 5.0, 7.0};
float Az_tab[] = {1.0, 2.0, 3.0};
//float fx_tab[] = {0.2, 0.3, 0.5};   
float fx_tab[] = {0.5, 0.5, 0.5};  // f = 0.5 Hz 
float tau_tab[] = {0.0, 0.25, 0.5, 0.75, 1.0};

float f_z, f_x, A_z, A_x, phi_x, phi_z;
float tau;


int16_t spe=1023;


int etat = 0;
int trig = 0;
int trig_pin = 5;

int rfid_pin = 12 ;
int rfid_pin_val = 0; 
int rfid_pin_val_was = 0;

/*
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/
void setup()
{ 
  
  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);   //Set debugging port baudrate to 115200bps
  while(!DEBUG_SERIAL);         //Wait until the serial port for terminal is opened
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(2000000/35);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  // Turn off torque when configuring items in EEPROM area
  if(dxl.write(DXL_ID_z, TORQUE_ENABLE_ADDR, (uint8_t*)&Turn_off , TORQUE_ENABLE_ADDR_LEN, TIMEOUT))
    DEBUG_SERIAL.println("DYNAMIXELz Torque off");
  else
    DEBUG_SERIAL.println("Error: DYNAMIXELz Torque off failed");

  if(dxl.write(DXL_ID_x, TORQUE_ENABLE_ADDR, (uint8_t*)&Turn_off , TORQUE_ENABLE_ADDR_LEN, TIMEOUT))
    DEBUG_SERIAL.println("DYNAMIXELx Torque off");
  else
    DEBUG_SERIAL.println("Error: DYNAMIXELx Torque off failed");

  // Set to Joint Mode
  if(dxl.write(DXL_ID_z, CW_ANGLE_LIMIT_ADDR, (uint8_t*)&GoalPosition1, ANGLE_LIMIT_ADDR_LEN, TIMEOUT)
        && dxl.write(DXL_ID_z, CCW_ANGLE_LIMIT_ADDR, (uint8_t*)&GoalPosition2, ANGLE_LIMIT_ADDR_LEN, TIMEOUT))
    DEBUG_SERIAL.println("DYNAMIXELz joint mode");
  else
    DEBUG_SERIAL.println("Error: DYNAMIXELz joint mode failed");

  if(dxl.write(DXL_ID_x, CW_ANGLE_LIMIT_ADDR, (uint8_t*)&GoalPosition1, ANGLE_LIMIT_ADDR_LEN, TIMEOUT)
        && dxl.write(DXL_ID_x, CCW_ANGLE_LIMIT_ADDR, (uint8_t*)&GoalPosition2, ANGLE_LIMIT_ADDR_LEN, TIMEOUT))
    DEBUG_SERIAL.println("DYNAMIXELx joint mode");
  else
    DEBUG_SERIAL.println("Error: DYNAMIXELx joint mode failed");

  // Turn on torque
  if(dxl.write(DXL_ID_z, TORQUE_ENABLE_ADDR, (uint8_t*)&Turn_on, TORQUE_ENABLE_ADDR_LEN, TIMEOUT))
    DEBUG_SERIAL.println("DYNAMIXELz Torque on");
  else
    DEBUG_SERIAL.println("Error: DYNAMIXELz Torque on failed");

  if(dxl.write(DXL_ID_x, TORQUE_ENABLE_ADDR, (uint8_t*)&Turn_on, TORQUE_ENABLE_ADDR_LEN, TIMEOUT))
    DEBUG_SERIAL.println("DYNAMIXELx Torque on");
  else
    DEBUG_SERIAL.println("Error: DYNAMIXELx torque on failed");

/*
  pinMode(trig_pin, INPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
 

  */
  pinMode(rfid_pin, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  Keyboard.begin();
  

  delay(200);
  init_phase();
  delay(1000);
  
  /*++++++++++++++++++++++++++++++++++++++++++++++++++*/
  t_0 = millis();
  /*++++++++++++++++++++++++++++++++++++++++++++++++++*/
 
}

/*
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/

 void init_phase(){

    int taille_Ax_tab = sizeof(Ax_tab)/sizeof(Ax_tab[0]);
    int taille_Az_tab = sizeof(Az_tab)/sizeof(Az_tab[0]);
    int taille_tau_tab = sizeof(tau_tab)/sizeof(tau_tab[0]);
    int taille_fx_tab = sizeof(fx_tab)/sizeof(fx_tab[0]);
  
    int index_Ax_tab = random(taille_Ax_tab);
    int index_Az_tab = random(taille_Az_tab);
    int index_tau_tab = random(taille_tau_tab);
    int index_fx_tab = random(taille_fx_tab);
    
    A_x = Ax_tab[index_Ax_tab];
    A_z = Az_tab[index_Az_tab];
    tau = tau_tab[index_tau_tab];
    f_x = fx_tab[index_fx_tab];



    f_z = 2*f_x;

    if ( tau < 0.25) {
      phi_x = (pi/2)*(1 - 4*tau);
      phi_z = (pi/2)*(8*tau - 1);
    }
  
    else if ( tau < 0.5) {
      phi_x = (pi/2)*(1 - 4*tau);
      phi_z = - (pi/2)*(8*(tau - 0.25) - 1);
    }
    
    else if ( tau < 0.75) {
      phi_x = - (pi/2)*(1 - 4*(tau - 0.5));
      phi_z = (pi/2)*(8*(tau - 0.5) - 1);
    }
    
    else {
      phi_x = - (pi/2)*(1 - 4*(tau - 0.5));
      phi_z = - (pi/2)*(8*(tau - 0.75) - 1);
    }
 
}
  


void Gestion(){
  
  rfid_pin_val_was = rfid_pin_val;
  rfid_pin_val = digitalRead(rfid_pin);
  Serial.println(rfid_pin_val);

  
  switch(etat){

    case 0:
      if ( rfid_pin_val == 1 and  rfid_pin_val_was == 0 ){
        etat = 1;
        delay(500);
        t_0 = millis();
        clic();
        Serial.print("case 0");
      }
    break;
    
    case 1:

    /*
      if (rfid_pin_val == 1 and  rfid_pin_val_was == 0){
        etat = 0;
        init_phase();
        clic();
        Serial.print("case 1");
        delay(500);
      }  */

      if (t > 10000){
        etat = 0;
        init_phase();
        clic();
        Serial.print("temps depasse");
        delay(500);
      }


    break;
    
  }
}

void Action(int etat){
   switch(etat){
    case 0:
      init_mov();
      dxl.write(DXL_ID_z, GOAL_POSITION_ADDR, (uint8_t*)&init_angle[0], GOAL_POSITION_ADDR_LEN, TIMEOUT);
      dxl.write(DXL_ID_x, GOAL_POSITION_ADDR, (uint8_t*)&init_angle[1], GOAL_POSITION_ADDR_LEN, TIMEOUT);
    break;

    case 1:
     gen_mov();
     dxl.write(DXL_ID_z, GOAL_POSITION_ADDR, (uint8_t*)&angle[0], GOAL_POSITION_ADDR_LEN, TIMEOUT);
     dxl.write(DXL_ID_x, GOAL_POSITION_ADDR, (uint8_t*)&angle[1], GOAL_POSITION_ADDR_LEN, TIMEOUT);
    break;
  }

  
}



void gen_mov(){
  


  float z_d =  sin((2.00*pi*f_z*(float)t/1000) + phi_z);
  z_d = 0.5*(z_d-1.00)*A_z;

  float x_d =  sin(2.00*pi*f_x*(float)t/1000 + phi_x);
  x_d = 0.5*(x_d)*A_x;

  float a_z = atan((z_d/r[0]))*(180/pi);
  float a_x = atan((x_d/r[1]))*(180/pi);
  
  angle[0] = (int)((1023/2) + (a_z*1023/300));
  angle[1] = (int)((1023/2) + (a_x*1023/300));
  
}

void init_mov(){
  
  float z_d =  sin(phi_z);
  z_d = 0.5*(z_d-1.00)*A_z;

  float x_d =  sin(phi_x);
  x_d = 0.5*(x_d)*A_x;

  float a_z = atan((z_d/r[0]))*(180/pi);
  float a_x = atan((x_d/r[1]))*(180/pi);
  
  init_angle[0] = (int)((1023/2) + (a_z*1023/300));
  init_angle[1] = (int)((1023/2) + (a_x*1023/300));
  
}

void clic() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('r');
  Keyboard.releaseAll();
}

/*
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/

void loop() 
{
  t_1 = millis();
  t = (t_1-t_0); 

  Gestion();
  Action(etat);

}