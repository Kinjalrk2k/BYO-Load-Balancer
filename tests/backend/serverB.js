const express = require("express");

const app = express();

app.get("/", (req, res) => {
  console.log(req.method, req.url);
  res.json({ msg: "Hello, from Server B" });
});

const PORT = 5001;
app.listen(PORT, () => {
  console.log(`Server B started in PORT ${PORT}`);
});
