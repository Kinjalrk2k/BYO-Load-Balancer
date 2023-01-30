const express = require("express");

const app = express();

app.get("/", (req, res) => {
  console.log("Got it");
  res.json({ msg: "Hello, World!" });
});

const PORT = 5000;
app.listen(PORT, () => {
  console.log(`Server started in PORT ${PORT}`);
});
