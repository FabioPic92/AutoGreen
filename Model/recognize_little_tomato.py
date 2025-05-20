from ultralytics import YOLO

model = YOLO("yolov8s.pt") 
model.train(
    data="Dataset_with_validation/dataset.yaml",
    epochs=50,
    imgsz=1280,
    batch=4,
    project="runs/train",
    name="little_tomato"
)


# model.train(
#     data="Dataset_with_validation/dataset.yaml",       
#     epochs=100,             
#     batch=16,               
#     imgsz=640,              
#     lr0=0.001,              
#     lrf=0.1,                
#     optimizer="SGD",        
#     momentum=0.937,
#     weight_decay=0.0005,
#     warmup_epochs=3,
#     warmup_momentum=0.8,
#     warmup_bias_lr=0.1,
#     augment=True,          
#     mosaic=1.0,
#     mixup=0.15,
#     fliplr=0.5,
#     translate=0.1,
#     scale=1.2,
#     degrees=15,
# )



# import albumentations as A
# from albumentations.pytorch import ToTensorV2
# from ultralytics import YOLO

# # Definisci il pipeline di augmentazione
# transform = A.Compose([
#     A.HorizontalFlip(p=0.5),          # flip orizzontale 50%
#     A.VerticalFlip(p=0.1),            # flip verticale 10%
#     A.RandomBrightnessContrast(p=0.2), # varia luminosità/contrasto
#     A.ShiftScaleRotate(               # traslazione, scala e rotazione
#         shift_limit=0.0625, scale_limit=0.1, rotate_limit=15, p=0.5
#     ),
#     A.HueSaturationValue(p=0.3),     # variazioni colore
#     A.RandomFog(p=0.1),               # nebbia random (simula condizioni diverse)
#     A.RandomShadow(p=0.1),            # ombre random
# ], bbox_params=A.BboxParams(format='yolo', label_fields=['class_labels']))

# # Se vuoi, convertilo in funzione per YOLOv8
# def augment(image, bboxes, class_labels):
#     augmented = transform(image=image, bboxes=bboxes, class_labels=class_labels)
#     return augmented['image'], augmented['bboxes'], augmented['class_labels']

# # Qui l’idea è di inserire questa funzione in un dataloader personalizzato (se usi uno)
# # oppure di configurare il training YOLOv8 per usarlo (richiede codice più avanzato).
