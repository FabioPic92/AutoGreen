from ultralytics import YOLO
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--image', type=str, required=True)
args = parser.parse_args()


model = YOLO('runs/train/exp_yolov8/weights/best.pt')

results = model(args.image)

results[0].show()