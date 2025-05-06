# AutoGreen
Progetto per la creazione di una serra autosufficiente (completamente automatizzato).

## Modello 1

La funzionalità di questo modello consiste in un braccio robotico che si muove verticalmente su un'asta ed esegue le foto che verranno analizzate da un modello di rete neurale per riconoscere il tipo di pianta e capire se è matura o no.

Questo modello sarà composto da un raspberry che dovrà gestire un microcontrollore che gestirà a sua volta sia il motore che la fotocamera.
Le analisi dello foto verrannò fatti sul raspberry.

### Struttura Meccanica e Hardware

####  Componenti Principali Hardware:

- **Microcontrollore**:
  - **Arduino UNO R4 Wifi**, per il controllo del Motore stepper e della fotocamera.
  - **Raspberry Pi3 Model B**, Per la gestine dei vari microcontrollori ed esecuzione di task.
- **Attuatori**:
  - **Motore Stepper Nema 17 17hs15-1504sx1**, Motore che serve per alzare e abbassare la piastra che contiene la fotocamera.
- **Sensori**:
  - **Fotocamera OV7670**, Esegue le foto che verranno inviate al raspberry.

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

## Licenza

Questo progetto è distribuito con la licenza MIT.