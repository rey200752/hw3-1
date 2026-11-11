
const int RledPin = 3;
const int GledPin = 10;
const int BledPin = 11;

const int potPin = A0;
const int buttonPin = 2;

int mode = 0;
int lastButtonState = HIGH;
int brightness = 255;

unsigned long lastPress = 0;
unsigned long lastUpdate = 0;

int hue = 0;

void setup() {
  Serial.begin(9600);

  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    if (millis() - lastPress > 200) {
      mode++;
      if (mode > 4) mode = 0;
      lastPress = millis();
    }
  }

  lastButtonState = buttonState;

  int sensorValue = analogRead(potPin);
  brightness = map(sensorValue, 0, 1023, 0, 255);

  int r = 0;
  int g = 0;
  int b = 0;

  if (mode == 0) {
    r = 255;
  }
  else if (mode == 1) {
    g = 255;
  }
  else if (mode == 2) {
    b = 255;
  }
  else if (mode == 3) {
    r = 255;
    g = 255;
    b = 255;
  }
  else {
    if (millis() - lastUpdate >= 20) {
      lastUpdate = millis();
      hue = (hue + 1) % 360;
    }

    if (hue < 60) {
      r = 255;
      g = hue * 255 / 60;
    }
    else if (hue < 120) {
      r = (120 - hue) * 255 / 60;
      g = 255;
    }
    else if (hue < 180) {
      g = 255;
      b = (hue - 120) * 255 / 60;
    }
    else if (hue < 240) {
      g = (240 - hue) * 255 / 60;
      b = 255;
    }
    else if (hue < 300) {
      r = (hue - 240) * 255 / 60;
      b = 255;
    }
    else {
      r = 255;
      b = (360 - hue) * 255 / 60;
    }
  }

  analogWrite(RledPin, 255 - r * brightness / 255);
  analogWrite(GledPin, 255 - g * brightness / 255);
  analogWrite(BledPin, 255 - b * brightness / 255);

  delay(1);
}

