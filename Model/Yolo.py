from ultralytics import YOLO

model = YOLO("yolov8n.pt")

model.train(
    data="Dataset_with_validation/dataset.yaml",
    epochs=50,
    imgsz=1280,
    batch=8,
    project="runs/train",
    name="exp_yolov8"
)