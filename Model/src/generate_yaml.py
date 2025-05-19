names = ["l_fully_ripened", "l_half_ripened", "l_green"]

yaml_content = f"""\
path: .
train: Dataset_with_validation/images/train
val: Dataset_with_validation/images/val
test: Dataset_with_validation/images/test

nc: {len(names)}
names:
"""

if __name__ == "__main__":
    for name in names:
        yaml_content += f"  - {name}\n"

    with open("Dataset_with_validation/dataset.yaml", "w") as f:
        f.write(yaml_content)