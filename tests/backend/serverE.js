const express = require("express");

const app = express();

app.get("/", (req, res) => {
  console.log(req.method, req.url);
  res.json({ msg: "Hello, from Server E" });
});

const PORT = 5004;
app.listen(PORT, () => {
  console.log(`Server E started in PORT ${PORT}`);
});
