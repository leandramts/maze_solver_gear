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
#define tempo_90 400
#define DIST_PL 7 //distancia pra detectar parede lateral
#define DIST_PF 12 //distancia parede frontal

enum Movimento { PARADO, FRENTE, ESQUERDA, DIREITA, TRAS };
Movimento lastMove = PARADO;

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

float distance_detection(int trig, int echo) 
{
  float soma = 0;
  int validas = 0;

  for (int i = 0; i < 5; i++) { // 5 leituras rápidas
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    unsigned long tempoEcho = pulseIn(echo, HIGH, 20000);
    float distancia = tempoEcho * 0.0343 / 2.0;

    if (tempoEcho > 0 && distancia > 0.5 && distancia < 400) 
    {
      soma += distancia;
      validas++;
    }
    delay(5); // pequeno intervalo
  }

  if (validas == 0) return -1.0; // nada válido
  return soma / validas;
}

void loop() 
{
    // Faz leituras e ajusta
    float frente_distancia   = distance_detection(TRIG_F, ECHO_F);
    float direita_distancia  = distance_detection(TRIG_D, ECHO_D);
    float esquerda_distancia = distance_detection(TRIG_E, ECHO_E);
    Serial.print("Frente: ");
    Serial.print(frente_distancia);
    Serial.print(" cm, Direita: ");
    Serial.print(direita_distancia);
    Serial.print(" cm, Esquerda: ");
    Serial.println(esquerda_distancia);
    delay(500); 

 labirinto_mao_esquerda(frente_distancia, direita_distancia, esquerda_distancia);
 delay(200);

    

}

void labirinto_mao_esquerda(float f_d, float d_d, float e_d)
{
  float erro = d_d - e_d;

  if (f_d > DIST_PF) 
  {
    if (erro > 3) 
    {
      mover_direita_leve();
      Serial.println("Corrigindo pro meio: direita");
    }
    else if (erro < -3) 
    {
      mover_esquerda_leve();
      Serial.println("Corrigindo pro meio: esquerda");
    }
    else
    {
      mover_frente();
      Serial.println("Seguindo reto, centralizado");
    }
  } 
  else if (e_d > DIST_PL) 
  {
    parar();
    delay(100);
    girar_esquerda();
    delay(tempo_90);
    Serial.println("Virando esquerda");
  }
  else if (d_d > DIST_PL) // parede à frente, abre direita
  {
    parar();
    delay(100);
    girar_direita();
    delay(tempo_90);
    Serial.println("Virando direita");
  }
  else // beco sem saída
  {
    parar();
    delay(100);
    mover_tras();
    delay(400);
  }
}

void labirinto_mao_esquerda_com_memoria(float f_d, float d_d, float e_d)
{
    float erro = d_d - e_d;

    if (f_d > DIST_PF) 
    {
        if (erro > 3) 
        {
            mover_direita_leve();
            Serial.println("Corrigindo pro meio: direita");
        }
        else if (erro < -3) 
        {
            mover_esquerda_leve();
            Serial.println("Corrigindo pro meio: esquerda");
        }
        else
        {
            mover_frente();
            Serial.println("Seguindo reto, centralizado");
        }
    } 
    else if (e_d > DIST_PL) 
    {
        if (lastMove != ESQUERDA) 
        {
            parar(); 
            delay(100);
            girar_esquerda();
            delay(tempo_90);
            Serial.println("Virando esquerda");
        } 
        else
        {
            mover_frente(); 
            Serial.println("Forçando frente para quebrar loop de esquerda");
        }
    }
    else if (d_d > DIST_PL) 
    {
        if (lastMove != DIREITA) 
        {
            parar(); 
            delay(100);
            girar_direita(); 
            delay(tempo_90);
            Serial.println("Virando direita");
        } 
        else
        {
            mover_frente(); // evita girar direita infinito
            Serial.println("Forçando frente para quebrar loop de direita");
        }
    }
    else // Beco sem saída
    {
        if (lastMove != TRAS)
        {
            parar();
            delay(100);
            mover_tras(); 
            delay(400);
            Serial.println("Recuando");
        }
        else
        {
            girar_direita();
            delay(tempo_90); // evita frente-trás infinito
            Serial.println("Forçando giro para quebrar vai-e-volta");
        }
    }
}

//movimentos ajustados com Ponte H L298
void mover_frente() 
{
  analogWrite(enA, 100);
  analogWrite(enB, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  lastMove = FRENTE;
}


void mover_tras()
{
  analogWrite(enA, 100);
  analogWrite(enB, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  lastMove = TRAS;
}

void parar()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void mover_esquerda_leve()
{
  analogWrite(enA, 80);
  analogWrite(enB, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void mover_direita_leve()
{
  analogWrite(enA, 100);
  analogWrite(enB, 80);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void girar_direita()
{
  analogWrite(enA, 100);
  analogWrite(enB, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  lastMove = DIREITA;
}

void girar_esquerda()
{
  analogWrite(enA, 100);
  analogWrite(enB, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  lastMove = ESQUERDA;
}