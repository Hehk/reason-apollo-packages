const path = require('path');

module.exports = {
  entry: "./lib/js/src/app.bs.js",
  output: {
    path: path.join(__dirname, "build"),
    filename: "output.js"
  }
};
