// HTML response
const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Car Control</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; }
    .slider { width: 300px; margin: 20px auto; }
    label { font-size: 1.2em; }
  </style>
</head>
<body>
  <h1>ESP32 Car Control</h1>
  <div class="slider">
    <label for="leftMotor">Left Motor Speed</label><br>
    <input type="range" id="leftMotor" min="-1023" max="1023" value="0" oninput="sendSpeed('left', this.value)">
  </div>
  <div class="slider">
    <label for="rightMotor">Right Motor Speed</label><br>
    <input type="range" id="rightMotor" min="-1023" max="1023" value="0" oninput="sendSpeed('right', this.value)">
  </div>
  <script>
    function sendSpeed(motor, speed) {
      fetch(`/?motor=${motor}&speed=${speed}`);
    }
  </script>
</body>
</html>
)rawliteral";