// robo resolvedor de labirinto

#define TRIG_F 6 //portas a serem definidas ainda 
#define ECHO_F 5 //F - frente, E - esquerda, D - direita
#define TRIG_E
#define ECHO_E
#define TRIG_D
#define ECHO_D
#define MOTOR_E
#define MOTOR_D

#define VELOCIDADE_SOM_MS 343

void setup()
{
  pinMode(TRIG_F, OUTPUT);
  pinMode(ECHO_F, INPUT);
  pinMode(TRIG_E, OUTPUT);
  pinMode(ECHO_E, INPUT);
  pinMode(TRIG_D, OUTPUT);
  pinMode(ECHO_D, INPUT);

  digitalWrite(TRIG_F, LOW);
  digitalWrite(TRIG_E, LOW);
  digitalWrite(TRIG_D, LOW);

  pinMode(MOTOR_E, OUTPUT);
  pinMode(MOTOR_D, OUTPUT);
  Serial.begin(9600);

}

float distance_detection(int trig, int echo) //funcao pra identificar as distancias a partir de cada ultrassonico
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long tempoEcho = pulseIn(echo, HIGH);

  return (tempoEcho*VELOCIDADE_SOM_MS/2000.0);


}

void loop()
  
{
  float frente_distancia = distance_detection(TRIG_F, ECHO_F);
  Serial.println(frente_distancia);
  float esquerda_distancia = distance_detection(TRIG_E, ECHO_E);
  Serial.println(esquerda_distancia);
  float direita_distancia = distance_detection(TRIG_D, ECHO_D);
  Serial.println(direita_distancia);
  
 
}

//ajustar os movimentos conforme a PONTE H L298N
void mover_frente() 
{
  digitalWrite(MOTOR_E, HIGH);
  digitalWrite(MOTOR_D, HIGH);
}

void parar()
{
  digitalWrite(MOTOR_E, LOW);
  digitalWrite(MOTOR_D, LOW);
}

void girar_esquerda()
{
  digitalWrite(MOTOR_E, HIGH);
  digitalWrite(MOTOR_D, LOW);
}

void girar_direita()
{
  digitalWrite(MOTOR_E, LOW);
  digitalWrite(MOTOR_D, HIGH);
}