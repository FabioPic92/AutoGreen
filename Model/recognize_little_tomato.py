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