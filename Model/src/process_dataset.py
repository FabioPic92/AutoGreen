import os
import json
import random
import shutil
import cv2
import numpy as np

VAL_RATIO = 0.2
TARGET_SIZE = (1280, 1280)

SRC_ANNOTATIONS_DIR = "../Dataset/annotations"
SRC_IMAGE_TRAIN_DIR = "../Dataset/train"
SRC_IMAGE_TEST_DIR = "../Dataset/test"

DST_ANNOTATIONS_DIR = "annotations"
DST_IMAGE_DIR = "images"
DST_TRAIN_DIR = os.path.join(DST_IMAGE_DIR, "train")
DST_VAL_DIR = os.path.join(DST_IMAGE_DIR, "val")
DST_TEST_DIR = os.path.join(DST_IMAGE_DIR, "test")

os.makedirs(DST_ANNOTATIONS_DIR, exist_ok=True)
os.makedirs(DST_TRAIN_DIR, exist_ok=True)
os.makedirs(DST_VAL_DIR, exist_ok=True)
os.makedirs(DST_TEST_DIR, exist_ok=True)

def load_file_dataset_json(path_annotations_json):
    with open(os.path.join(path_annotations_json, "train.json"), "r") as f:
        data = json.load(f)

    images = data["images"]
    annotations = data["annotations"]
    categories = data["categories"]
    info = data.get("info", {})
    licenses = data.get("licenses", [])

    return images, annotations, categories, info, licenses

def letterbox_resize(image, target_size=(1280, 1280), color=(114, 114, 114)):
    h, w = image.shape[:2]
    target_w, target_h = target_size
    scale = min(target_w / w, target_h / h)
    new_w, new_h = int(w * scale), int(h * scale)
    resized = cv2.resize(image, (new_w, new_h), interpolation=cv2.INTER_LINEAR)
    pad_w = (target_w - new_w) // 2
    pad_h = (target_h - new_h) // 2
    img_padded = cv2.copyMakeBorder(resized, pad_h, target_h - new_h - pad_h,
                                    pad_w, target_w - new_w - pad_w,
                                    cv2.BORDER_CONSTANT, value=color)
    return img_padded, scale, (pad_w, pad_h)

def process_coco_split(json_path, image_src_dir, image_dst_dir, output_json_path, target_size):
    images, annotations, categories, info, licenses = load_file_dataset_json(json_path)

    new_images = []
    new_annotations = []

    for img in images:
        filename = img["file_name"]
        img_id = img['id']
        src_path = os.path.join(image_src_dir, filename)
        dst_path = os.path.join(image_dst_dir, filename)

        if not os.path.exists(src_path):
            print(f"Image don't found: {src_path}")
            continue

        image = cv2.imread(src_path)
        if image is None:
            print(f"Error read: {src_path}")
            continue

        resized_image, scale, (pad_w, pad_h) = letterbox_resize(image, target_size)
        cv2.imwrite(dst_path, resized_image)

        img["width"], img["height"] = target_size
        new_images.append(img)

        for ann in annotations:
            if ann["image_id"] == img_id:
                x, y, w, h = ann["bbox"]
                x = x * scale + pad_w
                y = y * scale + pad_h
                w = w * scale
                h = h * scale
                ann["bbox"] = [x, y, w, h]
                new_annotations.append(ann)

    output_data = {
        "info": info,
        "licenses": licenses,
        "images": new_images,
        "annotations": new_annotations,
        "categories": categories
    }

    with open(output_json_path, "w") as f:
        json.dump(output_data, f, indent=4)

    print(f"Save {output_json_path} with {len(new_images)} images")


if __name__ == "__main__":
    images, annotations, categories, info, licenses = load_file_dataset_json(SRC_ANNOTATIONS_DIR)

    random.shuffle(images)
    val_size = int(len(images) * VAL_RATIO)
    val_images = images[:val_size]
    train_images = images[val_size:]

    val_ids = set(img["id"] for img in val_images)
    train_ids = set(img["id"] for img in train_images)

    train_annotations = [ann for ann in annotations if ann["image_id"] in train_ids]
    val_annotations = [ann for ann in annotations if ann["image_id"] in val_ids]

    train_json_temp = "train_temp.json"
    val_json_temp = "val_temp.json"

    def write_temp_json(path, imgs, anns):
        with open(path, "w") as f:
            json.dump({
                "info": info,
                "licenses": licenses,
                "images": imgs,
                "annotations": anns,
                "categories": categories
            }, f, indent=4)

    write_temp_json(train_json_temp, train_images, train_annotations)
    write_temp_json(val_json_temp, val_images, val_annotations)

    process_coco_split(train_json_temp, SRC_IMAGE_TRAIN_DIR, DST_TRAIN_DIR,
                       os.path.join(DST_ANNOTATIONS_DIR, "train_resized.json"), TARGET_SIZE)

    process_coco_split(val_json_temp, SRC_IMAGE_TRAIN_DIR, DST_VAL_DIR,
                       os.path.join(DST_ANNOTATIONS_DIR, "val_resized.json"), TARGET_SIZE)

    process_coco_split(os.path.join(SRC_ANNOTATIONS_DIR, "test.json"),
                       SRC_IMAGE_TEST_DIR, DST_TEST_DIR,
                       os.path.join(DST_ANNOTATIONS_DIR, "test_resized.json"), TARGET_SIZE)

    os.remove(train_json_temp)
    os.remove(val_json_temp)

    print("Dataset Done!")