from ultralytics import YOLO

model = YOLO('runs/train/exp_yolov8/weights/best.pt')

results = model("Dataset_with_validation/images/test/IMG_1110.jpg")

results[0].show()