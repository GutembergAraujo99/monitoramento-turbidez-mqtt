# Sistema de Monitoramento e Bloqueio de Fluxo Hídrico com MQTT

Este projeto apresenta um protótipo de monitoramento da turbidez da água utilizando Arduino UNO R4 WiFi, sensor de turbidez, servomotor e comunicação via protocolo MQTT.

O objetivo do sistema é identificar alterações na qualidade da água e acionar automaticamente um atuador para simular o bloqueio do fluxo hídrico quando a turbidez ultrapassar o limite definido.

## Componentes Utilizados

- Arduino UNO R4 WiFi
- Sensor de turbidez
- Micro Servo Motor SG90
- Protoboard
- Jumpers
- Rede Wi-Fi

## Funcionamento

O Arduino realiza a leitura do sensor de turbidez. Quando a água apresenta turbidez acima do limite configurado, o servomotor é acionado para simular o fechamento de uma válvula.

Os dados de turbidez e o estado da válvula são enviados via MQTT para acompanhamento remoto em dashboard.

## Comunicação MQTT

A comunicação é realizada através da rede Wi-Fi integrada ao Arduino UNO R4 WiFi, utilizando o protocolo MQTT para envio das informações ao broker.

## Estrutura do Repositório

- `codigo/` - Código-fonte do Arduino
- `documentacao/` - Artigo final do projeto
- `diagramas/` - Fluxograma e diagrama de conexões
- `imagens/` - Imagens do protótipo e dashboard
- `video/` - Link do vídeo demonstrativo

## Vídeo Demonstrativo

https://youtube.com/shorts/nPdbARxCByc?feature=share

## Autor

José Gutemberg de Araújo  
Universidade Presbiteriana Mackenzie
