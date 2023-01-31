const express = require("express");

const app = express();

app.get("/", (req, res) => {
  console.log(req.method, req.url);
  res.json({ msg: `Hello, from Server: ${process.env.SERVER_NAME}` });
});

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
  console.log(`Server: ${process.env.SERVER_NAME} started in PORT ${PORT}`);
});
