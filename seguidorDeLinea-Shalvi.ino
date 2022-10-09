#include <QTRSensors.h>

#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             11  // emitter is controlled by digital pin 2

#define mi1        6
#define mi2        7
#define pwmi       5

#define md1        8
#define md2        9
#define pwmd       10

//variables push
int PUSH = 3;
int pushValue = 0;


// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {0, 1, 2, 3, 4, 5, 6, 7}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

//Sensor Ultrasonico
const int Trigger = 12;
const int Echo = 13;

void setup()
{
  delay(500);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
    
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(4, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');

    //int val = qtra.calibratedMaximumOn[2];
    //Serial.println("Valor del censor");
    //Serial.println(val);
    
  }
  Serial.println();
  Serial.println();
  delay(1000);

  //code motor

  pinMode(mi1,OUTPUT);
  pinMode(mi2,OUTPUT);
  pinMode(md1,OUTPUT);
  pinMode(md2,OUTPUT);

  pinMode(PUSH, INPUT);
}

void loop()
{
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(100);          //Hacemos una pausa de 100ms


   unsigned int position = qtra.readLine(sensorValues);
  
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); 
    
  }
   //Serial.println(); // uncomment this line if you are using raw values
    Serial.println(position); // comment this line out if you are using raw values

     //Serial.println("Valor del sensor 2");
  
    int s1 = (sensorValues[0]);
    int s2 = (sensorValues[1]);
    int s3 = (sensorValues[2]);
    int s4 = (sensorValues[3]);
    int s5 = (sensorValues[4]);
    int s6 = (sensorValues[5]);
    int s7 = (sensorValues[6]);
    int s8 = (sensorValues[7]);
    Serial.println(pushValue);

    if(s1 > 800 || s2 > 800 || s3 > 800)
    {
      Serial.println("GIRAR ALA Izquierda");   
      digitalWrite(mi1,HIGH);
      digitalWrite(mi2,LOW);
      analogWrite(pwmi, 100);
      
      digitalWrite(md1,HIGH);
      digitalWrite(md2,LOW);
      analogWrite(pwmd,255);
    }
    if(s1 > 700)
    {
      Serial.println("GIRAR ALA Izquierda con todo");   
      digitalWrite(mi1,HIGH);
      digitalWrite(mi2,LOW);
      analogWrite(pwmi, 50);
      
      digitalWrite(md1,HIGH);
      digitalWrite(md2,LOW);
      analogWrite(pwmd,255);
    }

    

   
    if(s8 > 800 || s7> 800 || s6 > 800)
    {
      Serial.println("GIRAR A LA DeRECHA");
      digitalWrite(4, LOW);

      digitalWrite(mi1,HIGH);
      digitalWrite(mi2,LOW);
      analogWrite(pwmi, 200);

      digitalWrite(md1,HIGH);
      digitalWrite(md2,LOW);
      analogWrite(pwmd,100);
    }
    if(s8 > 800)
    {
      Serial.println("GIRAR A LA Derecha CON TODO");
      digitalWrite(4, LOW);

      digitalWrite(mi1,HIGH);
      digitalWrite(mi2,LOW);
      analogWrite(pwmi, 200);

      digitalWrite(md1,HIGH);
      digitalWrite(md2,LOW);
      analogWrite(pwmd,50);
    }

    if(s4 > 800 && s5 > 800)
    {
      Serial.println("Avanzar");
      digitalWrite(4, LOW);

      digitalWrite(mi1,HIGH);
      digitalWrite(mi2,LOW);
      analogWrite(pwmi, 255);

      digitalWrite(md1,HIGH);
      digitalWrite(md2,LOW);
      analogWrite(pwmd, 255);    
    }

     /*if(position < 2000)
    {
      Serial.println("Stop");
      analogWrite(pwmi, 0);
      analogWrite(pwmd,0);
    }*/
 
}