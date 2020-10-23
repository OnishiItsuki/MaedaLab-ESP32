// running test now

int led_R = 0;
int led_G = 2;
int led_B = 4; 

void setup() {
  pinMode(led_R,OUTPUT);
  pinMode(led_G,OUTPUT);
  pinMode(led_B,OUTPUT);
}

void loop() {
  digitalWrite(led_R,HIGH);
  digitalWrite(led_G,LOW);
  digitalWrite(led_B,LOW);
  delay(200);
  
  digitalWrite(led_R,LOW);
  digitalWrite(led_G,HIGH);
  digitalWrite(led_B,LOW);
  delay(200);
  
  digitalWrite(led_R,LOW);
  digitalWrite(led_G,LOW);
  digitalWrite(led_B,HIGH);
  delay(200);
  
  digitalWrite(led_R,LOW);
  digitalWrite(led_G,LOW);
  digitalWrite(led_B,LOW);
  delay(200);

}
