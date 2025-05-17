# AutoGreen
Progetto per la creazione di una serra autosufficiente (completamente automatizzato).

## Modello 1

Il sistema sarà composto da un Raspberry Pi 3 Model B che fungerà da unità centrale di controllo e analisi. Il Raspberry gestirà un microcontrollore collegato, responsabile del controllo diretto del motore e della fotocamera. Le immagini acquisite verranno inviate dal microcontrollore al Raspberry, dove verranno effettuate le operazioni di elaborazione e analisi. 

### Struttura Meccanica e Hardware

####  Componenti Principali Hardware:

- **Microcontrollore**:
  - **Esp-S3**, per il controllo del Motore stepper e della fotocamera.
  - **Raspberry Pi3 Model B**, Per la gestine dei vari microcontrollori ed esecuzione di task.
- **Attuatori**:
  - **Motore Stepper Nema 17 17hs15-1504sx1**, Motore che serve per alzare e abbassare la piastra che contiene la fotocamera.
- **Sensori**:
  - **Fotocamera OV2460**, Esegue le foto che verranno inviate al raspberry.

#### Struttura Meccanica

La parte meccanica consisterà in una piastra che conterrà il microcontrollore, gli attuatori e la fotocamera.
verrà attaccata ad un asta attraverso una ruota dentata.

### Software e Programmazione

#### Principale software da implementare:

- **Gestione del Motore Stepper**, software per la gestione del movimento del motore.
- **Gestione della fotocamera**, software per l'esecuzione della foto.
- **Gestione invio dati**, software per l'invio dei dati.
- **Modello per riconoscere le piante**, Modello di AI per il riconoscimento di un oggetto(nel nostro caso una pianta).

## Installazione e Setup

### Core

#### Build

1. cd AutoGreen/Core
2. mkdir build
3. cd build
4. cmake ..
5. make

questo genererà i file eseguibili per i vari nodi

#### Install Paho Library

La libreria va installata in locale sia per C che C++

Versione C

1. git clone https://github.com/eclipse-paho/paho.mqtt.c.git
2. cd paho.mqtt.c
3. cmake -B build -DPAHO_BUILD_STATIC=ON -DPAHO_BUILD_SHARED=OFF -DPAHO_BUILD_SAMPLES=OFF -DPAHO_ENABLE_TESTING=OFF
4. cmake --build build

Nella cartella build/src dovresti trovare i file .a (es. libpaho-mqtt3as.a)

Versione C++

1. git clone https://github.com/eclipse/paho.mqtt.cpp
2. cd paho.mqtt.cpp
3. git submodule init
4. git submodule update
5. cmake -Bbuild -H. -DPAHO_WITH_MQTT_C=ON -DPAHO_BUILD_EXAMPLES=ON
6. sudo cmake --build build/ --target install

#### Tips

Nel caso non trovasse i file .so e .a in ogni terminale in cui lanciate un nodo con paho eseguite i comandi:

1. chmod +x configure.sh
2. ./configure.sh

## Model

Il primo modello che si è scelto riconoscera il tipo di verdura pomodorini.
Il dataset scelto è quello di loboro Ai, nel nostro caso si è scelto il subdataset little tomato(http://assets.laboro.ai.s3.amazonaws.com/laborotomato/laboro_tomato_little.zip).
Questo Dataset è composto da immagini di pomodorini e da un file json che indica la quantità e lo stato di maturazione in un file json.
Purtroppo il dataset è piccolo(289  immagini) ma visto che le itichette di cui abbiamo bisogno sono poche ma per ora va bene.

### Pre-Processed Dataset
Il dataset è composto da foto di dimensioni quali: 3024*4032, 3120*4160 e simili.
Mentre la fotocamera OV2640 ha risoluzione 1632x1232, perciò andiamo a scalare a 1280


## Licenza

Questo progetto è distribuito con la licenza MIT.
