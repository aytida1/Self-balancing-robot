int p1 = 11;
int p2 = 10;
int p3 = 9;
int p4 = 6;

void setup() {
  // put your setup code here, to run once:

    pinMode(p1, OUTPUT);
    pinMode(p2, OUTPUT);
    pinMode(p3, OUTPUT);
    pinMode(p4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    analogWrite(p1, 100);
    analogWrite(p2, 0);
    analogWrite(p3, 0);
    analogWrite(p4, 100);
    
}
