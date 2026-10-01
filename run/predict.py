import torch
import torch.nn.functional as F
import sys
import numpy as np
from pathlib import Path

# 加载你的pt模型
model_path = Path(__file__).resolve().with_name("mnist.pt")
# Open the Unicode path with Python before handing the model bytes to TorchScript.
with model_path.open("rb") as model_file:
    model = torch.jit.load(model_file, map_location="cpu")
model.eval()

# 接收Qt发过来的像素数据
raw_string = sys.argv[1]
data = np.array([float(x) for x in raw_string.split(',') if x.strip()]).reshape(1, 1, 28, 28)
inp = torch.from_numpy(data).float()

with torch.no_grad():
    out = model(inp)
    probs = torch.nn.functional.softmax(out, dim=1)[0]

top3_prob, top3_idx = torch.topk(probs, 3)
ans = top3_idx[0].item()


html_output = (
    f"<p align='center'>"
    f"<span style='font-size: 60px; font-weight: bold;'>{ans}</span>"
    f"<br><br>"
    f"<span style='font-size: 16px;'>"
    f"1st: [{top3_idx[0].item()}] {int(top3_prob[0].item()*100)}% &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; "
    f"2nd: [{top3_idx[1].item()}] {int(top3_prob[1].item()*100)}% &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; "
    f"3rd: [{top3_idx[2].item()}] {int(top3_prob[2].item()*100)}%"
    f"</span>"
    f"</p>"
)

# 打印这一个完整的富文本字符串给 Qt
print(html_output)