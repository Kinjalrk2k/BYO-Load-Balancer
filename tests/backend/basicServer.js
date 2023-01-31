const express = require("express");

const app = express();

app.get("/", (req, res) => {
  console.log(req.method, req.url);
  res.json({ msg: `Hello, from Server: ${process.env.SERVER_NAME}` });
});

app.all("/echo", (req, res) => {
  req.res.json({
    serverName: process.env.SERVER_NAME,
    method: req.method,
    url: req.url,
    query: req.query,
    params: req.params,
    headers: req.headers,
    body: req.body,
  });
});

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
  console.log(`Server: ${process.env.SERVER_NAME} started in PORT ${PORT}`);
});
