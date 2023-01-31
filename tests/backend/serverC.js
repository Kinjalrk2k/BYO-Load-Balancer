const express = require("express");

const app = express();

app.get("/", (req, res) => {
  console.log(req.method, req.url);
  res.json({ msg: "Hello, from Server C" });
});

const PORT = 5002;
app.listen(PORT, () => {
  console.log(`Server C started in PORT ${PORT}`);
});
