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

TO-DO

Per Paho fare export alle librerie in build/src per ogni terminale

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/ubuntu/Documents/Projects/AutoGreen/Raspberry/external/paho/paho.mqtt.cpp/build/src

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
