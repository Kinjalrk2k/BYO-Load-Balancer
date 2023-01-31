const express = require("express");

const app = express();

app.get("/", (req, res) => {
  console.log(req.method, req.url);
  res.json({ msg: "Hello, from Server D" });
});

const PORT = 5003;
app.listen(PORT, () => {
  console.log(`Server D started in PORT ${PORT}`);
});
