#define RED_PIN 6
#define GREEN_PIN 5
#define BLUE_PIN 3
#define WHITE_PIN 9

#define Loop_Delay 300

int Brightness_R;
int Brightness_G;
int Brightness_B;
int Brightness_W;

int FadeStep_R;  
int FadeStep_G;
int FadeStep_B;
int FadeStep_W;

void setup() {
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(WHITE_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Brightness_R = 0;
  Brightness_G = 0;
  Brightness_B = 0;
  Brightness_W = 0;

  FadeStep_R = 0;
  FadeStep_G = 325;
  FadeStep_B = 650;
  FadeStep_W = 250;
}

void loop() {
  FadeStep_R--;
  FadeStep_G--;
  FadeStep_B--;
  FadeStep_W--;

  FadeStep_R = (FadeStep_R == -764) ? 765 : FadeStep_R;
  FadeStep_G = (FadeStep_G == -764) ? 765 : FadeStep_G;
  FadeStep_B = (FadeStep_B == -764) ? 765 : FadeStep_B;
  FadeStep_W = (FadeStep_W == -764) ? 765 : FadeStep_W;

  Brightness_R = (FadeStep_R < 0) ? -FadeStep_R : FadeStep_R - 510;
  Brightness_G = (FadeStep_G < 0) ? -FadeStep_G : FadeStep_G - 510;
  Brightness_B = (FadeStep_B < 0) ? -FadeStep_B : FadeStep_B - 510;
  Brightness_W = (FadeStep_W < 0) ? -FadeStep_W : FadeStep_W - 510;

  Brightness_B = constrain(Brightness_B, 0, 255);
  Brightness_G = constrain(Brightness_G, 0, 255);
  Brightness_R = constrain(Brightness_R, 0, 255); 
  Brightness_W = constrain(Brightness_W, 0, 255); 

//setLEDS(Brightness_R, Brightness_G, Brightness_B, Brightness_W);
  // Serial.print("INICIO");
  // Serial.println(Brightness_R);
  //  Serial.println(Brightness_G);
  //   Serial.println(Brightness_B);
  //    Serial.println(Brightness_W);
  setLEDS(0,0,0,80);
  delay(Loop_Delay);
}

void setLEDS(int ipR, int ipG, int ipB, int ipW) {
  analogWrite(RED_PIN, ipR);
  analogWrite(GREEN_PIN, ipG);
  analogWrite(BLUE_PIN, ipB);
  analogWrite(WHITE_PIN, ipW);
}
