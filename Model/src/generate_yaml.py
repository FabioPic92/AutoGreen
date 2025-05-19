names = ["l_fully_ripened", "l_half_ripened", "l_green"]

yaml_content = f"""\
path: Dataset_with_validation
train: images/train
val: images/val
test: images/test

nc: {len(names)}
names:
"""

if __name__ == "__main__":
    for name in names:
        yaml_content += f"  - {name}\n"

    with open("../Dataset_with_validation/dataset.yaml", "w") as f:
        f.write(yaml_content)