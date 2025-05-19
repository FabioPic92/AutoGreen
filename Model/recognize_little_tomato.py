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