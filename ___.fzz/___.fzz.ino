// 动手做5-2：从序列埠控制 LED 开关，使用switch..case
// 详细说明，请参阅第五章，5-22页。

const byte LED = 13;
char val;         // 储存接收资料的变量，采字符类型
int a;
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.print("Welcome to Arduino!");
}

void loop() {
  if ( Serial.available() ) {
    val = Serial.read();
    switch (val) {
      case'0':
        digitalWrite(LED, LOW);
        Serial.print("LED OFF");
        break;
      case'1':
        digitalWrite(LED, HIGH);
        Serial.print("LED ON");
        break;
      default:
        for (byte a = 0; a < 4; a++) {
          digitalWrite(LED, HIGH);
          delay(300);
          digitalWrite(LED, LOW);
          delay(300);
        }
    }
  }
}

