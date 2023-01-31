const express = require("express");

const app = express();

app.get("/", (req, res) => {
  console.log(req.method, req.url);
  res.json({ msg: "Hello, from Server A" });
});

const PORT = 5000;
app.listen(PORT, () => {
  console.log(`Server A started in PORT ${PORT}`);
});
