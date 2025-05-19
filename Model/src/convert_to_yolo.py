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
    coco_to_yolo("../Dataset_with_validation/annotations/train_resized.json", "../Dataset_with_validation/labels/train", "../Dataset_with_validation/images/train")
    coco_to_yolo("../Dataset_with_validation/annotations/val_resized.json", "../Dataset_with_validation/labels/val", "../Dataset_with_validation/images/val")
    coco_to_yolo("../Dataset_with_validation/annotations/test_resized.json", "../Dataset_with_validation/labels/test", "../Dataset_with_validation/images/test")
