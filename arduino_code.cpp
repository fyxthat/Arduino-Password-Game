#include <TimerOne.h>                     // Biblioteca para controlar o Timer1
#include <MultiFuncShield.h>              // Biblioteca específica para o Shield Multifuncional

byte btn; // Define a variavel do botao
byte buttonNumber; // Define a variavel do numero do botao
int contador; // Define a variavel do contador
int senha[8]; // Define o vetor da senha
int correct = 0; // Inicializa a variavel de acertos

unsigned long tempoAnterior = 0; // Define o tempo anterior para 0
const long intervalo = 1000; // Define o intervalo para 1 segundo

int timer (){ // Funcao para definir o tempo
  do{
  btn = MFS.getButton(); // Lê o botão pressionado (se houver)
  buttonNumber = btn & B00111111;  // Isola os bits que representam o número do botão (0 a 3)
  contador = map(analogRead(POT_PIN), 0, 1023, 45, 90); // Lê o valor do potenciômetro e mapeia para um intervalo de tempo entre 45 e 90 ms
  Serial.println(contador); // Mostra o tempo de intervalo no monitor serial
  }while(buttonNumber != 1); // Prende a definicao do tempo em um loop ate que o botao 1 seja pressionado 
  return contador; // Retorna o valor definido para o tempo
}

int gerarSenha(){ // Funcao para gerar uma senha
  randomSeed(analogRead(A4)); // Seta uma semente aletoria para uma entrada nao utilizada
  for (int i = 0; i < 8; i++){ // Crie um loop para adicionar cada inteiro da senha
    senha[i] = random(1, 4); // Gera cada inteiro da senha
  }
  return senha; // Retorna o ponteiro para a senha
}

void ledAcertos(int a){ // Variavel dos leds com o contador em binario (Esse nem precisa explicar se o numero for tal apaga e acende os que precisa)
  if (a == 0){
    MFS.writeLeds(LED_1 | LED_2 | LED_3 | LED_4, OFF);
  } else if (a == 1){
    MFS.writeLeds(LED_1, ON);
    MFS.writeLeds(LED_2 | LED_3 | LED_4, OFF);
  } else if (a == 2){
    MFS.writeLeds(LED_2, ON);
    MFS.writeLeds(LED_1 | LED_3 | LED_4, OFF);
  } else if (a == 3){
    MFS.writeLeds(LED_1 | LED_2, ON);
    MFS.writeLeds(LED_3 | LED_4, OFF);
  } else if (a == 4){
    MFS.writeLeds(LED_3, ON);
    MFS.writeLeds(LED_1 | LED_2 | LED_4, OFF);
  } else if (a == 5){
    MFS.writeLeds(LED_1 | LED_3, ON);
    MFS.writeLeds(LED_2 | LED_4, OFF);
  } else if (a == 6){
    MFS.writeLeds(LED_2 | LED_3, ON);
    MFS.writeLeds(LED_1 | LED_4, OFF);
  } else if (a == 7){
    MFS.writeLeds(LED_1 | LED_2 | LED_3, ON);
    MFS.writeLeds(LED_4, OFF);
  } else if (a == 8){
    MFS.writeLeds(LED_4, ON);
    MFS.writeLeds(LED_1 | LED_2 | LED_3, OFF);
  } else {
    MFS.writeLeds(LED_1 | LED_2 | LED_3 | LED_4, ON);
  }
}

void setup(){
  Serial.begin(9600); // Inicia comunicação com o monitor serial (9600 bps)
  Timer1.initialize(); // Inicializa o Timer1
  MFS.initialize(&Timer1); // Inicializa o Shield Multifuncional com o Timer1
  Serial.println(timer()); // Printa no inicio o tempo selecionado
  gerarSenha(); // Gera uma senha
  MFS.write("COOL"); // Escreve COOL na tela
  delay(3000); // Da um delay antes de limpar a tela e começar o contador
  MFS.write(""); // Limpa a tela
}

void loop(){
  btn = MFS.getButton(); // Lê o botão pressionado (se houver)
  byte buttonNumber = btn & B00111111; // Isola os bits que representam o número do botão (0 a 3)
  byte buttonAction = btn & B11000000; // Isola os bits que representam a forma que o botão foi apertado (Clique longo ou rápido)

  if (contador > 0){ // Comeca o sistema
    MFS.write(contador);  // Escreve na tela o tempo restante
    unsigned long tempoAtual = millis();  // Define o tempo atual
    if (tempoAtual - tempoAnterior >= intervalo){ // Conta se passou um segundo
        tempoAnterior = tempoAtual; // Passa o valor do tempo atual para o anterior para que o tempo anterior nao seja sempre 0
        contador--; // Diminui um no contador simulando um contador de segundos
    }
    if (contador < 10){ // Se o tempo restante for menor que 10
      MFS.beep(20); // Faz um som por 200ms
      MFS.blinkDisplay(DIGIT_ALL, ON);  // Ativa uma funcao que pisca o display ate que seja desativada
    }
    if (buttonAction == BUTTON_PRESSED_INT){  // Checa se foi um clique curto evitando que conte dois cliques em um unico clique
      if (buttonNumber == senha[correct]){  // Checa se o botao pressionado é o valor da senha em que se espera
          correct++;  // Adiciona um na variavel que checa os acertos
          MFS.beep(8, 0, 1);  // Faz um som por 80ms sem pausa com um ciclo
          ledAcertos(correct);  // Chama a funcao que ascende o led com base nos acertos
      }
      else{ // Se o valor clicado for diferente da senha
        correct = 0;  // Reseta a variavel de acertos
        contador -= 2;  // Diminui dois segundo no tempo restante
      }
    }
    if (correct == 8){  // Se a senha estiver correta
      MFS.write("SAFE");  // Escreve SAFE na tela
      MFS.beep(50, 50, 3) // Faz um som por 500ms com 500ms de pausa 3 vezes
    }
  }
  else{ // Se o tempo restante for menor que 0
    MFS.blinkDisplay(DIGIT_ALL, OFF); // Para de piscar o display (O display comeca a piscar quando menor que 10)
    MFS.write("ICE"); // Escreve ICE na tela
    MFS.beep(30000);  // Faz um bipe continuo por 5 minutos (Basicamente o mesmo que indefinidamente pq ninguem merece 5 minutos desse)
  }
}

/* Integrantes do Grupo:

-Diogo de Sa Cavalcanti Araujo

-Gabriel Guerreiro de Sousa Coelho

-João Vitor Padilha Ferreira

-Luís Felipe Guimarães da Cunha Romanach

-Yago Pereira Costa */