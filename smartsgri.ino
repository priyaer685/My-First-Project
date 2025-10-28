import processing.serial.*;
Serial myPort;

float distance;
float temperature;
float humidity;
float soilMoisture;

void setup() {
  size(800, 600);
  myPort = new Serial(this, "COM3", 9600); // change COM port if needed
  myPort.bufferUntil('\n');
  smooth();
}

void draw() {
  background(0);
  fill(0, 255, 0);
  textSize(20);
  text("SMART AGRICULTURE SYSTEM", 220, 40);
  
  stroke(0, 255, 0);
  noFill();
  arc(width/2, height, 600, 600, PI, TWO_PI);
  arc(width/2, height, 400, 400, PI, TWO_PI);
  arc(width/2, height, 200, 200, PI, TWO_PI);

  // Radar line
  stroke(0, 255, 0);
  line(width/2, height, width/2 + cos(radians(distance)) * 300, height - sin(radians(distance)) * 300);

  // Data display
  fill(0, 255, 0);
  text("Distance: " + distance + " cm", 30, 100);
  text("Temperature: " + temperature + " °C", 30, 140);
  text("Humidity: " + humidity + " %", 30, 180);
  text("Soil Moisture: " + soilMoisture, 30, 220);
}

void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('\n');
  if (data != null) {
    data = trim(data);
    String[] values = split(data, ',');
    if (values.length == 4) {
      distance = float(values[0]);
      temperature = float(values[1]);
      humidity = float(values[2]);
      soilMoisture = float(values[3]);
    }
  }
}
