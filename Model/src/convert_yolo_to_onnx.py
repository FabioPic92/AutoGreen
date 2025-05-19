import torch
from ultralytics.nn.tasks import DetectionModel

torch.serialization.add_safe_globals({'ultralytics.nn.tasks.DetectionModel': DetectionModel})

# Ora carica il modello completo
model = torch.load('../Models/LittleTomatoModel.pt', weights_only=False)

# Imposta in eval mode
model.eval()

# model = torch.load('../Models/LittleTomatoModel.pt') 
# model.eval()
# dummy_input = torch.zeros((1, 3, 1280, 120)) 


# torch.onnx.export(model, dummy_input, '../../Core/Models/LittleTomatoModel.onnx',
#                   opset_version=12,
#                   input_names=['images'],
#                   output_names=['output'],
#                   dynamic_axes={'images': {0: 'batch'}, 'output': {0: 'batch'}})