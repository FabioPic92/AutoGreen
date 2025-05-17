import argparse
from ultralytics import YOLO

parser = argparse.ArgumentParser()
parser.add_argument("--image", type=str, required=True)
args = parser.parse_args()


model = YOLO("../Models/LittleTomatoModel.pt")

results = model(args.image)

results[0].show()