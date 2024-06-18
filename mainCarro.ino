#include "BluetoothSerial.h"

BluetoothSerial ESP_BT;  // Objeto BluetoothSerial

// Pines de conexión
int enA = 27;   // Pin PWM para controlar la velocidad
int in1 = 26;   // Pin de control de dirección
int in2 = 25;   // Pin de control de dirección
int in3 = 33;
int in4 = 32;
int enB = 14;
int TRIG_PIN= 18;
int ECHO_PIN=19;
int LED_PIN= 15;
const int distancia_lim=10;

void sensor_init(){
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Apaga el LED inicialmente
}

void medir(){
  long duration, distance;
  
  // Clear the TRIG_PIN by setting it LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Set the TRIG_PIN HIGH for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the ECHO_PIN, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (round trip)

  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Check if the distance is below the threshold
  if (distance <= distancia_lim) {
    digitalWrite(LED_PIN, HIGH); // Enciende el LED
  } else {
    digitalWrite(LED_PIN, LOW); // Apaga el LED
  }
  
  // Wait for a bit before the next measurement
  delay(1000);
}

void mover(String command){
    Serial.println("Received: " + command);  // Imprimir el texto recibido en el puerto serie
    // ESP_BT.println("Echo: " + command);  // Enviar el texto de vuelta al dispositivo conectado
    if (command == "F") {
      // Mover ambos motores hacia adelante
      digitalWrite(in1, HIGH);  // IN1 en HIGH
      digitalWrite(in2, LOW);   // IN2 en LOW
      analogWrite(enA, 50);    // Velocidad máxima (255)

      digitalWrite(in3, HIGH);  // IN3 en HIGH
      digitalWrite(in4, LOW);   // IN4 en LOW
      analogWrite(enB, 50);    // Velocidad máxima (255)

    } else if (command == "B") {
      // Mover ambos motores hacia atrás
      digitalWrite(in1, LOW);   // IN1 en LOW
      digitalWrite(in2, HIGH);  // IN2 en HIGH
      analogWrite(enA, 50);    // Velocidad máxima (255)

      digitalWrite(in3, LOW);   // IN3 en LOW
      digitalWrite(in4, HIGH);  // IN4 en HIGH
      analogWrite(enB, 50);    // Velocidad máxima (255)

    } else if (command == "S") {
      // Detener ambos motores
      digitalWrite(in3, LOW);  // IN3 en LOW
      digitalWrite(in4, LOW);  // IN4 en LOW
      analogWrite(enA, 0);     // Velocidad 0 (detener)
    }else if (command == "L") {
      // Mover el motor izquierdo hacia adelante y el derecho hacia atrás
      digitalWrite(in1, HIGH);  // IN1 en HIGH
      digitalWrite(in2, LOW);   // IN2 en LOW
      analogWrite(enA, 150);    // Velocidad máxima (255)

      digitalWrite(in3, LOW);   // IN3 en LOW
      digitalWrite(in4, HIGH);  // IN4 en HIGH
      analogWrite(enB, 150);    // Velocidad máxima (255)

    } else if (command == "R") {
      // Mover el motor izquierdo hacia atrás y el derecho hacia adelante
      digitalWrite(in1, LOW);   // IN1 en LOW
      digitalWrite(in2, HIGH);  // IN2 en HIGH
      analogWrite(enA, 150);    // Velocidad máxima (255)

      digitalWrite(in3, HIGH);  // IN3 en HIGH
      digitalWrite(in4, LOW);   // IN4 en LOW
      analogWrite(enB, 150);    // Velocidad máxima (255)
    }
  }
}

void setup() {
  Serial.begin(115200);                              // Inicializar el puerto serie para debug
  delay(3000);
  ESP_BT.begin("ESP32BT");                          // Nombre del dispositivo Bluetooth
  Serial.println("Bluetooth Device is Ready to Pair");
  sensor_init();                                   //inicializa el sensor
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
     if (ESP_BT.available()) {
    String command = ESP_BT.readString();  // Leer el texto recibido
    mover(command);  // Ejecutar el comando de movimiento
  } else {
    Serial.println("Esperando comando Bluetooth...");
  }
  medir();  
}

