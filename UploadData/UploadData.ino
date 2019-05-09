#include <SoftwareSerial.h>
#include <dht.h>
#define DHT_PIN  3

dht DHT;
float temperature, humidity;
char tempString[5], humidityString[5];
char thingspeakUrl[70];
char serialMonitorUrl[70];


/* Create object named SIM800 of the class SoftwareSerial */
SoftwareSerial SIM800(10, 11); //RX and TX

void setup() {
  SIM800.begin(9600);  /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
}

void loop() {
  DHT.read11(DHT_PIN);
  temperature = DHT.temperature;
  humidity = DHT.humidity;
  dtostrf(temperature, 4, 2, tempString);
  dtostrf(humidity, 4, 2, humidityString);

  sprintf(thingspeakUrl, "GET https://api.thingspeak.com/update?api_key=A1QPWYJUCHKHGMQD&field1=%s&field2=%s\r\n\x1A", tempString, humidityString);
  sprintf(serialMonitorUrl, "GET https://api.thingspeak.com/update?api_key=A1QPWYJUCHKHGMQD&field1=%s&field2=%s\\r\\n" ,tempString, humidityString)
  
  Serial.println("TCP Send :");
  Serial.print("AT\\r\\n");
  SIM800.println("AT"); /* Check Communication */
  delay(5000);
  ShowSerialData();  /* Print response on the serial monitor */
  delay(5000);
  Serial.print("AT+CIPMODE=0\\r\\n");
  SIM800.println("AT+CIPMODE=0"); /* Non-Transparent (normal) mode for TCP/IP application */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIPMUX=0\\r\\n");
  SIM800.println("AT+CIPMUX=0");  /* Single TCP/IP connection mode */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CGATT=1\\r\\n");
  SIM800.println("AT+CGATT=1"); /* Attach to GPRS Service */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CREG?\\r\\n");
  SIM800.println("AT+CREG?"); /* Network registration status */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CGATT?\\r\\n");
  SIM800.println("AT+CGATT?");  /* Attached to or detached from GPRS service */ 
  delay(5000); 
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CSTT=\"internet\",\"\",\"\"\\r\\n");
  SIM800.println("AT+CSTT=\"internet\",\"\",\"\""); /* Start task and set APN */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIICR\\r\\n");
  SIM800.println("AT+CIICR"); /* Bring up wireless connection with GPRS */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIFSR\\r\\n");
  SIM800.println("AT+CIFSR"); /* Get local IP address */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"\\r\\n");
  SIM800.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");  /* Start up TCP connection */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIPSEND\\r\\n");
  SIM800.println("AT+CIPSEND"); /* Send data through TCP connection */
  delay(2000);
  ShowSerialData();
  delay(2000);
//  Serial.print("GET /update?api_key=C7JFHZY54GLCJY38&field1=1\\r\\n");
//  SIM800.print("GET /update?api_key=C7JFHZY54GLCJY38&field1=1\r\n\x1A");  /* URL for data to be sent to */

  Serial.print(serialMonitorUrl);
  SIM800.print(thingspeakUrl):
  
  delay(10000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIPSHUT\\r\\n");
  SIM800.println("AT+CIPSHUT"); /* Deactivate GPRS PDP content */
  delay(5000);
  ShowSerialData();
  delay(5000);
}

void ShowSerialData()
{
  while(SIM800.available()!=0)  /* If data is available on serial port */
  Serial.write(char (SIM800.read())); /* Print character received on to the serial monitor */
}
}

void ShowSerialData()
{
  while(SIM800.available()!=0)  /* If data is available on serial port */
  Serial.write(char (SIM800.read())); /* Print character received on to the serial monitor */
}
