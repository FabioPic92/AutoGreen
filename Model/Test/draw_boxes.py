import cv2
import json
import numpy as np

json_path = "../Dataset_with_validation/annotations/train_resized.json"
image_path = "../Dataset_with_validation/images/train/IMG_1147.jpg"

image = cv2.imread(image_path)

with open(json_path, "r") as f:
    data = json.load(f)

images = data["images"]
annotations = data["annotations"]

image_name = "IMG_1147.jpg"

id = ""
for im in images:
    if im["file_name"] == image_name:
        id = im["id"]
    
print(f"ID: {id}")

for annotation in annotations:
    d = annotation
    if id == d["image_id"]: 
        print(f"ID: {d["image_id"]}, pos {len(d["bbox"])}")

        type = str(d["category_id"])

        x, y, w, h = d["bbox"]
        top_left = (int(x), int(y))
        top_right = (int(x + w), int(y))
        bottom_right = (int(x + w), int(y + h))
        bottom_left = (int(x), int(y + h))
        
        points = [top_left, top_right, bottom_right, bottom_left]

        for i in range(4):
            start_point = points[i]
            end_point = points[(i + 1) % 4] 
            cv2.line(image, start_point, end_point, color=(0, 255, 0), thickness=2)

        cv2.putText(
            image, 
            type,        
            (int(x), int(y + 10)),
            cv2.FONT_HERSHEY_SIMPLEX,
            1,                        
            (0, 0, 0),              
            2,                        
            cv2.LINE_AA              
        )
cv2.imwrite('saved_image.jpg', image)
