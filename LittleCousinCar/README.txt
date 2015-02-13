//----------------------READ.ME-------------------//
Como utilizar a biblioteca LittleCousinCar.h:
  * Funções:
    - prepararPinos()
      Define os terminais do CI de acordo com suas devidas tarefas (Entrada ou Saida) e freia os motores
      Parâmetros de entrada:
        Nenhum
      Tipo de retorno:
        VOID
      Exemplo de uso:
        prepararPinos(); //Prepara os pinos
    
    - leRoda(lado)
      Realiza a leitura do sensor ótico localizado nas rodas para saber sua posição
      Parâmetros de entrada:
        ladoDireito - Efetua a leitura do sensor da roda direita
        ladoEsquerdo - Efetua a leitura do sensor da roda esquerda
      Tipo de retorno:
        Inteiro - Valor da leitura do sensor
      Exemplo de uso:
        int i = leRoda(ladoDireito); //Variavel i recebe o valor da leitura do sensor ótico da roda direita
  
    - motorDireita(direcao)
      Realiza operações com o motor do lado direito ( Motor 1 ).
        Parâmetros de entrada:
          FRENTE - Movimenta a roda para frente
          TRAS - Movimenta a roda para trás
          PARAR - Freia a roda
        Tipo de retorno:
          VOID
        Exemplo de uso:
          motorDireita(FRENTE); //Move o motor da direita para frente indefinidamente


    - motorEsquerda(direcao)
      Realiza operações com o motor do lado esquerdo ( Motor 2 ).
        Parâmetros de entrada:
          FRENTE - Movimenta a roda para frente
          TRAS - Movimenta a roda para trás
          PARAR - Freia a roda
        Tipo de retorno:
          VOID
        Exemplo de uso:
          motorEsquerda(FRENTE); //Move o motor da esquerda para frente indefinidamente
