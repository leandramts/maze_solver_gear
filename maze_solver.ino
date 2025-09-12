// robo resolvedor de labirinto

#define TRIG_F 4 //portas a serem definidas ainda 
#define ECHO_F 5 //F - frente, E - esquerda, D - direita
#define TRIG_E 3
#define ECHO_E 2
#define TRIG_D 6
#define ECHO_D 7

//motor esquerdo
#define in1  8
#define in2 9

//motor direito
#define in3 12
#define in4 13

#define enA 10
#define enB 11

#define VELOCIDADE_SOM_MS 343

#define DIST_P 8 //distancia pra detectar parede

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
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  Serial.begin(9600);
}

float distance_detection(int trig, int echo) //funcao pra identificar as distancias a partir de cada ultrassonico
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long tempoEcho = pulseIn(echo, HIGH, 20000);

  return tempoEcho * 0.0343 / 2.0;
}

// Função para normalizar leitura do sensor
float ajustaLeitura(float leitura, float maxConf = 200) {
    if (leitura == 0) {
        return maxConf; // 0 tratado como  muito longe
    }obstáculo
    if (leitura > maxConf) {
        return maxConf; // corta valores acima do confiável
    }
    return leitura;
}

void loop() {
    // Faz leituras e ajusta
    float frente_distancia   = ajustaLeitura(distance_detection(TRIG_F, ECHO_F));
    float direita_distancia  = ajustaLeitura(distance_detection(TRIG_D, ECHO_D));
    float esquerda_distancia = ajustaLeitura(distance_detection(TRIG_E, ECHO_E));
    Serial.print("Frente: ");
    Serial.print(frente_distancia);
    Serial.print(" cm, Direita: ");
    Serial.print(direita_distancia);
    Serial.print(" cm, Esquerda: ");
    Serial.println(esquerda_distancia);
    delay(1000);

    girar_esquerda();
    delay(500);
    girar_direita();
    delay(500);
    

}

//movimentos ajustados com Ponte H L298
void mover_frente() 
{
  analogWrite(enA, 120);
  analogWrite(enB, 120);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void mover_tras()
{
  analogWrite(enA, 120);
  analogWrite(enB, 120);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void parar()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void girar_esquerda_leve()
{
  analogWrite(enA, 90);
  analogWrite(enB, 120);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}

void girar_direita_leve()
{
  analogWrite(enA, 120);
  analogWrite(enB, 90);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void girar_direita()
{
  analogWrite(enA, 120);
  analogWrite(enB, 120);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void girar_esquerda()
{
  analogWrite(enA, 120);
  analogWrite(enB, 120);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}