// robo resolvedor de labirinto

#define TRIG_F 6 //portas a serem definidas ainda 
#define ECHO_F 5 //F - frente, E - esquerda, D - direita
#define TRIG_E
#define ECHO_E
#define TRIG_D
#define ECHO_D

//motor esquerdo
#define in1  
#define in2 

//motor direito
#define in3 
#define in4 

#define VELOCIDADE_SOM_MS 343

#define DIST_P 5 //distancia pra detectar parede

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

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(9600);

}

float distance_detection(int trig, int echo) //funcao pra identificar as distancias a partir de cada ultrassonico
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
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

  //condicões de movimento (logica da mão direita)

  if (direita_distancia > DIST_P) //se a direita estiver livre, gire pra direita
  {
    parar();
    delay(200);
    girar_direita();
    delay(500);
  }
  else if (frente_distancia > DIST_P) //se a direita estiver bloqueada, e a frente livre, mova pra frente
  {
    mover_frente();
  }

  else if (esquerda_distancia > DIST_P) //se a frente e a direita estiverem bloqueadas, mova pra esquerda
  {
    parar();
    delay(200);
    girar_esquerda();
    delay(500);
  }
  else 
  {
    parar();
    delay(200);
    mover_tras();
    delay(500);
  }

}

//movimentos ajustados com Ponte H L298
void mover_frente() 
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void mover_tras()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}

void parar()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void girar_esquerda()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void girar_direita()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}