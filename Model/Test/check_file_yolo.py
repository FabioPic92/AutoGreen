import os

images_root = "Dataset_with_validation/images"
labels_root = "Dataset_with_validation/labels"

class_names = ["l_fully_ripened", "l_half_ripened", "l_green"]
valid_class_ids = set(range(len(class_names)))

def check_labels(split):
    errors = 0
    image_dir = os.path.join(images_root, split)
    label_dir = os.path.join(labels_root, split)

    if not os.path.exists(label_dir):
        print(f"Label directory not found: {label_dir}")
        return

    for img_file in os.listdir(image_dir):
        if not img_file.lower().endswith((".jpg", ".png", ".jpeg")):
            continue
        base_name = os.path.splitext(img_file)[0]
        label_file = os.path.join(label_dir, base_name + ".txt")

        if not os.path.exists(label_file):
            print(f"Label miss: {img_file}")
            errors += 1
            continue

        with open(label_file, "r") as f:
            lines = f.readlines()

        for i, line in enumerate(lines):
            parts = line.strip().split()
            if len(parts) != 5:
                print(f"Format error {label_file}, row {i+1}: {line.strip()}")
                errors += 1
                continue
            try:
                class_id = int(parts[0])
                if class_id not in valid_class_ids:
                    print(f"Class id out of range {label_file}, row {i+1}: {class_id}")
                    errors += 1
            except ValueError:
                print(f"Class id don't int {label_file}, row {i+1}: {parts[0]}")
                errors += 1

    if errors == 0:
        print(f"It's ok '{split}'")
    else:
        print(f"{errors} Problem in split '{split}'")

for split in ["train", "val", "test"]:
    check_labels(split)