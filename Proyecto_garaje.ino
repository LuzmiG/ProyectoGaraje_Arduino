#include <Servo.h> //Libreria de Servo
#include <SoftwareSerial.h> //Libreria de Bluethooth

Servo myServo;
//Conexion de los pines de Transmisión (TX) Y Recepeción (RX) del Bluethooth
int pinTX = 10;
int pinRX = 11;
SoftwareSerial miBT(pinTX,pinRX);  
char dato; //será utilizado para que "1/0"" se puedan leer desde la aplicación


//----------------------------------
void setup() {  
//MODULO BLUETHOOTH
  Serial.begin(9600);  //Velocidad de lectura del Serial (IDE ARDUINO)
  Serial.println("listo"); //Señal de conexion de bluethooth por medio de Serial
  myServo.write(90); //Siempre que empize será en 0 Grados //indicador de posición de grados del servo
  miBT.begin(9600); //Velocidad de conexión (BAUDIOS)  ¡¡¡9600!!!!
  
  // Leds a usar
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  // Servo
  myServo.attach(5); //Pin 5 de arudino es donde debe ir el Servo
  
  //mETODO (LEDS)
  onOffLeds();
}

void loop() {
    // Si mi modulo de bluethooth esta conectado
  //if(Serial.available()){       
  if(miBT.available()){ 
    //Las dos luces se encenderán, inidicando que esta conectado
    onOffLeds();
    //Dato no tiene ningun valor hasta el momento, no almazena nada esta variable
    // Entonces dato = tomará el volor que leerá (METODDO)     
    //dato=Serial.read()  
    dato=miBT.read(); 
    //lee el dato que esta enviando la app
    Serial.println(dato);
        //Si le 'a' llamará a la función 'abrirPuerta'
    if(dato=='c')
    
    abrirPuerta();
    //Si lee 'c' llamará a la función 'cerrarPuerta'
    if(dato=='a')
     cerrarPuerta();
    }   
  }

//---------------------------------------------------------
//ENCEDER LAS LEDS
void onOffLeds(){
   digitalWrite(3 ,HIGH);
  digitalWrite(4,HIGH);
  delay(200); 
  digitalWrite(3 ,LOW);
  digitalWrite(4,LOW);
  delay(100);
  digitalWrite(3 ,HIGH);
  digitalWrite(4,HIGH);
  delay(200);
  digitalWrite(3 ,LOW);
  digitalWrite(4,LOW);

}

//-----------------------------------
//Funcion cERRAR PUERTA
void cerrarPuerta(){
  //----------------------
  //Las luces tienen la funcion de indicadores si esta abierto o cerrado
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
//-------------------
// angudo para Cerrar la puerta debe ser 0 
//¿porque? porque estamos usando una "palanca" con el hilo en la maqueta 

   int angulo = 0;
  do{
     angulo = angulo + 1;
     myServo.write(angulo);
     delay(50);
  }while(angulo < 90 );
//indica que es de 0 a 90 no debe ser mayor a eso   
  digitalWrite(3 ,LOW);
  digitalWrite(4,LOW);
  Serial.println("CERRADO"); 
  
}
//aBRIR PUERTA
void abrirPuerta(){
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  int angulo = 90;
  do{
    //Disminuya - 1 
    angulo = angulo -1;
    myServo.write(angulo);
    //a una velocidad baja (50)
    delay(50);
  }while(angulo > 0 );
   digitalWrite(3 ,LOW);
   digitalWrite(4,LOW);
   Serial.println("ABIERTO");
  
}

