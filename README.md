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

## Setup

### Install 

1. git clone git@github.com:FabioPic92/AutoGreen.git

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

Nel caso non trovasse i file .so e .a in ogni terminale in cui lanciate un nodo con paho eseguite lo script:

1. ./configure.sh

#### Install Opencv

sudo apt install libopencv-dev python3-opencv

### Model Install

1. cd Model
2. source Modelenv/bin/activate
3. pip install -r requirements.txt

# Core

TO-DO

# Model

Il primo modello scelto avrà lo scopo di riconoscere se una pianta di pomodorini sarà matura o no.
Il dataset scelto è quello di loboro Ai, nel nostro caso si è scelto il subdataset little tomato(http://assets.laboro.ai.s3.amazonaws.com/laborotomato/laboro_tomato_little.zip).
Questo Dataset è composto da immagini di piante di pomodorini e da un file json che indica la quantità e lo stato di maturazione(l_fully_ripened l_half_ripened, l_green) in un file json.
Purtroppo il dataset è piccolo(289 immagini per il training e 70 per il test) ma visto che le etichette di cui abbiamo bisogno sono poche(nello specifico 3) per ora va bene.

Fasi per l'addestramento:
1. Studio Modello 
2. Pre-processing Dataset
3. Training Model
4. Test Model


### Studio modello 
Per ora si è scelto il modello YOLOv5 in quanto soddisfa le nostre necessità.
In futuro si pensa di sviluppare un proprio modello

### Pre-Processed Dataset
Come detto precedentemente il dataset è composto da foto di dimensioni quali: 3024x4032, 3120x4160.
Mentre la fotocamera OV2640 ha risoluzione 1600x1200.
In quanto il modello ho necessiatà di foto quadrata andiamo a modificare le immagini ad una size di 1280x1280.
In secondo luogo abbiamobisogno di un set per la validazione perciò si andrà a creare 2 set Train e Val a partire dal set di Train.
Per convenzione si andrà a fare una divisone 80/20 dove 80 è il train e il 20 e il set di validazione.

Codice:
```python
import os
import json
import random
import shutil
import cv2
import numpy as np

VAL_RATIO = 0.2
TARGET_SIZE = (1280, 1280)

SRC_ANNOTATIONS_DIR = "../Dataset/annotations"
SRC_IMAGE_TRAIN_DIR = "../Dataset/train"
SRC_IMAGE_TEST_DIR = "../Dataset/test"

DST_ANNOTATIONS_DIR = "annotations"
DST_IMAGE_DIR = "images"
DST_TRAIN_DIR = os.path.join(DST_IMAGE_DIR, "train")
DST_VAL_DIR = os.path.join(DST_IMAGE_DIR, "val")
DST_TEST_DIR = os.path.join(DST_IMAGE_DIR, "test")

os.makedirs(DST_ANNOTATIONS_DIR, exist_ok=True)
os.makedirs(DST_TRAIN_DIR, exist_ok=True)
os.makedirs(DST_VAL_DIR, exist_ok=True)
os.makedirs(DST_TEST_DIR, exist_ok=True)

def load_file_dataset_json(path_annotations_json):
    with open(os.path.join(path_annotations_json, "train.json"), "r") as f:
        data = json.load(f)

    images = data["images"]
    annotations = data["annotations"]
    categories = data["categories"]
    info = data.get("info", {})
    licenses = data.get("licenses", [])

    return images, annotations, categories, info, licenses

def letterbox_resize(image, target_size=(1280, 1280), color=(114, 114, 114)):
    h, w = image.shape[:2]
    target_w, target_h = target_size
    scale = min(target_w / w, target_h / h)
    new_w, new_h = int(w * scale), int(h * scale)
    resized = cv2.resize(image, (new_w, new_h), interpolation=cv2.INTER_LINEAR)
    pad_w = (target_w - new_w) // 2
    pad_h = (target_h - new_h) // 2
    img_padded = cv2.copyMakeBorder(resized, pad_h, target_h - new_h - pad_h,
                                    pad_w, target_w - new_w - pad_w,
                                    cv2.BORDER_CONSTANT, value=color)
    return img_padded, scale, (pad_w, pad_h)

def process_coco_split(json_path, image_src_dir, image_dst_dir, output_json_path, target_size):
    images, annotations, categories, info, licenses = load_file_dataset_json(json_path)

    new_images = []
    new_annotations = []

    for img in images:
        filename = img['file_name']
        img_id = img['id']
        src_path = os.path.join(image_src_dir, filename)
        dst_path = os.path.join(image_dst_dir, filename)

        if not os.path.exists(src_path):
            print(f"Image don't found: {src_path}")
            continue

        image = cv2.imread(src_path)
        if image is None:
            print(f"Error read: {src_path}")
            continue

        resized_image, scale, (pad_w, pad_h) = letterbox_resize(image, target_size)
        cv2.imwrite(dst_path, resized_image)

        img['width'], img['height'] = target_size
        new_images.append(img)

        for ann in annotations:
            if ann['image_id'] == img_id:
                x, y, w, h = ann['bbox']
                x = x * scale + pad_w
                y = y * scale + pad_h
                w = w * scale
                h = h * scale
                ann['bbox'] = [x, y, w, h]
                new_annotations.append(ann)

    output_data = {
        "info": info,
        "licenses": licenses,
        "images": new_images,
        "annotations": new_annotations,
        "categories": categories
    }

    with open(output_json_path, "w") as f:
        json.dump(output_data, f, indent=4)

    print(f"Save {output_json_path} with {len(new_images)} images")


if __name__ == "__main__":
    images, annotations, categories, info, licenses = load_file_dataset_json(SRC_ANNOTATIONS_DIR)

    random.shuffle(images)
    val_size = int(len(images) * VAL_RATIO)
    val_images = images[:val_size]
    train_images = images[val_size:]

    val_ids = set(img["id"] for img in val_images)
    train_ids = set(img["id"] for img in train_images)

    train_annotations = [ann for ann in annotations if ann["image_id"] in train_ids]
    val_annotations = [ann for ann in annotations if ann["image_id"] in val_ids]

    train_json_temp = "train_temp.json"
    val_json_temp = "val_temp.json"

    def write_temp_json(path, imgs, anns):
        with open(path, "w") as f:
            json.dump({
                "info": info,
                "licenses": licenses,
                "images": imgs,
                "annotations": anns,
                "categories": categories
            }, f, indent=4)

    write_temp_json(train_json_temp, train_images, train_annotations)
    write_temp_json(val_json_temp, val_images, val_annotations)

    process_coco_split(train_json_temp, SRC_IMAGE_TRAIN_DIR, DST_TRAIN_DIR,
                       os.path.join(DST_ANNOTATIONS_DIR, "train_resized.json"), TARGET_SIZE)

    process_coco_split(val_json_temp, SRC_IMAGE_TRAIN_DIR, DST_VAL_DIR,
                       os.path.join(DST_ANNOTATIONS_DIR, "val_resized.json"), TARGET_SIZE)

    process_coco_split(os.path.join(SRC_ANNOTATIONS_DIR, "test.json"),
                       SRC_IMAGE_TEST_DIR, DST_TEST_DIR,
                       os.path.join(DST_ANNOTATIONS_DIR, "test_resized.json"), TARGET_SIZE)

    os.remove(train_json_temp)
    os.remove(val_json_temp)

    print("Dataset Done!")
```

### Training Model
Per eseguire l'addestramento bisogna trasformare il dataset da coco a Yolo:
Di seguito i passaggi:

1. Creazione labels nel file convert_to_yolo.py
```python
import os
import json

def coco_to_yolo(json_path, output_dir, image_dir, img_size=(1280, 1280)):
    with open(json_path) as f:
        data = json.load(f)

    os.makedirs(output_dir, exist_ok=True)

    image_map = {img["id"]: img for img in data["images"]}

    ann_map = {}
    for ann in data["annotations"]:
        img_id = ann["image_id"]
        ann_map.setdefault(img_id, []).append(ann)

    for img_id, anns in ann_map.items():
        img_info = image_map[img_id]
        img_w, img_h = img_info["width"], img_info["height"]
        filename = os.path.splitext(img_info["file_name"])[0] + ".txt"
        label_path = os.path.join(output_dir, filename)

        lines = []
        for ann in anns:
            x, y, w, h = ann["bbox"]
            xc = (x + w / 2) / img_w
            yc = (y + h / 2) / img_h
            ww = w / img_w
            hh = h / img_h
            category_id = ann["category_id"] - 1 
            lines.append(f"{category_id} {xc:.6f} {yc:.6f} {ww:.6f} {hh:.6f}")

        with open(label_path, "w") as f:
            f.write("\n".join(lines))

if __name__ == "__main__":
    coco_to_yolo("Dataset_with_validation/annotations/train_resized.json", "labels/train", "Dataset_with_validation/images/train")
    coco_to_yolo("Dataset_with_validation/annotations/val_resized.json", "labels/val", "Dataset_with_validation/images/val")
    coco_to_yolo("Dataset_with_validation/annotations/test_resized.json", "labels/test", "Dataset_with_validation/images/test")
```

2. Creazione file yaml in generate_yaml.py
```python
names = ["l_fully_ripened", "l_half_ripened", "l_green"]

yaml_content = f"""\
path: .
train: Dataset_with_validation/images/train
val: Dataset_with_validation/images/val
test: Dataset_with_validation/images/test

nc: {len(names)}
names:
"""

if __name__ == "__main__":
    for name in names:
        yaml_content += f"  - {name}\n"

    with open("dataset.yaml", "w") as f:
        f.write(yaml_content)
```

Di seguito si procede con il training:
Il modello base è 
```python
from ultralytics import YOLO

model = YOLO("Models/yolov5s.pt")

model.train(
    data="Dataset_with_validation/dataset.yaml",
    epochs=50,
    imgsz=1280,
    batch=8,
    project="runs/train",
    name="little_tomato"
)
```
### Test Model
Il test sui risultati è stato fatto con il set test:\
```python
import argparse
from ultralytics import YOLO

parser = argparse.ArgumentParser()
parser.add_argument("--image", type=str, required=True)
args = parser.parse_args()


model = YOLO("../Models/LittleTomatoModel.pt")

results = model(args.image)

results[0].show()
```
### Risultati

Di seguito riporto i risultati del primo training.

![Training Results](Model/result/results.png)
[Scarica il file CSV](Model/result/results.csv)

I risultati finali ottenuti sono:
| **Metrica**    | **Valore** |
|----------------|------------|
| Precisione     | 0.80521    |
| Recall         | 0.82732    |
| mAP@50         | 0.89262    |
| mAP@50-95      | 0.769      |

Per ora sono buoni, bisogna fare altri test per capire se c'è bisogno di migliorare.

## Licenza

Questo progetto è distribuito con la licenza MIT.
