from ultralytics import YOLO

model = YOLO('runs/train/exp_yolov8/weights/best.pt')

# Fai delle previsioni su un'immagine di test
results = model("Dataset_with_validation/images/test/IMG_1110.jpg")

# Visualizza i risultati delle predizioni
results[0].show()