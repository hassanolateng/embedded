#include <DHT.h>


double volt;
int duty;
DHT dht(2,DHT11);

void setup() {
  // Initialize the serial communication at 9600 baud
  Serial.begin(9600);
  
  // Initialize the DHT sensor
  dht.begin();
  
  // Configure the pins
  pinMode(A5, INPUT);    // Set A5 as an input for analog reading
  pinMode(13, OUTPUT);  // Set digital pin 13 as an output
  pinMode(12, OUTPUT);  // Set digital pin 12 as an output
  pinMode(11, OUTPUT);  // Set digital pin 11 as an output
  pinMode(2, INPUT);    // Set digital pin 2 as an input
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

void loop() {
  // Read the humidity from the DHT sensor
  float h = dht.readHumidity();
  
  // Check if the read failed and print an error message if needed
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Print the humidity if read successfully
    Serial.print("Humidity: ");
    Serial.println(h);
  }
  
  // Read the analog value from pin A5
  int analogValue = analogRead(A5);
  
  // Convert the analog value to voltage (assuming 5V reference)
  volt = (analogValue / 1023.0) * 5.0;
  
  // Adjust the duty cycle based on the voltage
  if (volt < 0.25 && duty > 0) {
    duty=duty-5;
  } else if (volt > 0.25 && duty < 255) {
    duty=duty+5;
  } else if(volt==0.25){
    duty = 0;
  }
  
  // Write the duty cycle to pin 11
  analogWrite(11, duty);
  double speed= (duty/255.0)*100;
  // Print the voltage to the serial monitor
  Serial.print("temperature ");
  Serial.println(volt*100);
  Serial.print("speed ");
  Serial.print(speed);
  Serial.println("%");
  
  // Add a longer delay to allow time for the DHT sensor to stabilize in simulation
  //delay(1000);  // 5-second delay
}
