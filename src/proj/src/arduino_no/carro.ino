int CA = 7;
int DA = 8;

int CB = 2;
int DB = 3;

bool sCA = true;
bool sDA = !sCA;

bool sCB = false;
bool sDB = !sCB;

int E_A = 4;
int E_B = 5;

uint8_t entrada = 0;
uint8_t setor = 3;
uint8_t distancia = 0;

void girar(uint32_t tempo_milissegundos) {
  andar_direita(tempo_milissegundos);
}

void andar_tras(uint32_t tempo_milissegundos) {

  boolean val = true;

  digitalWrite(CA, val);
  digitalWrite(DA, !val);

  digitalWrite(CB, !val);
  digitalWrite(DB, val);


  digitalWrite(E_A, HIGH);
  digitalWrite(E_B, HIGH);

  delay(tempo_milissegundos);

  digitalWrite(E_A, LOW);
  digitalWrite(E_B, LOW);
}

void andar_frente(uint32_t tempo_milissegundos) {

  boolean val = true;

  digitalWrite(CA, !val);
  digitalWrite(DA, val);

  digitalWrite(CB, val);
  digitalWrite(DB, !val);


  digitalWrite(E_A, HIGH);
  digitalWrite(E_B, HIGH);

  delay(tempo_milissegundos);

  digitalWrite(E_A, LOW);
  digitalWrite(E_B, LOW);

}

void andar_direita(uint32_t tempo_milissegundos) {

  boolean val = true;

  digitalWrite(CA, val);
  digitalWrite(DA, !val);


  digitalWrite(CB, val);
  digitalWrite(DB, !val);


  digitalWrite(E_A, HIGH);
  digitalWrite(E_B, HIGH);

  delay(tempo_milissegundos);

  digitalWrite(E_A, LOW);
  digitalWrite(E_B, LOW);

}

void andar_esquerda(uint32_t tempo_milissegundos) {

  boolean val = true;

  digitalWrite(CA, !val);
  digitalWrite(DA, val);


  digitalWrite(CB, !val);
  digitalWrite(DB, val);


  digitalWrite(E_A, HIGH);
  digitalWrite(E_B, HIGH);

  delay(tempo_milissegundos);

  digitalWrite(E_A, LOW);
  digitalWrite(E_B, LOW);

}


void setup() {
  Serial.begin(9600);
  digitalWrite(E_A, LOW);
  digitalWrite(E_B, LOW);
  digitalWrite(13, LOW);
}

uint32_t tempo_normal = 50;

void loop() {

  if (Serial.available()) {
    entrada = Serial.read();
  } else {
    return;
  }

  setor =     (entrada & B11100000) >> 5;
  distancia = (entrada & B00011111);

  if (setor == B010) {
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }

  if (setor == 3 && distancia == 0) {
    girar(tempo_normal);
    return;
  }

  if (setor < 3) andar_esquerda(tempo_normal);
  if (setor > 3) andar_direita(tempo_normal);

  if (setor == 3 && distancia < 15) andar_frente(tempo_normal);

}
