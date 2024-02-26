// 设置引脚2为输出模式
// Set pin 2 as output mode
void setup()
{
  pinMode(2, OUTPUT);
}

// 循环执行以下代码
// Loop through the following code
void loop()
{
  // 向引脚2输出低电平（亮灯）
  // Output low level to pin 2 (turn on the light)
  digitalWrite(2, LOW);
  // 延迟1秒
  // Delay for 1 second
  delay(1000);
  // 向引脚2输出高电平（关灯）
  // Output high level to pin 2 (turn off the light)

  digitalWrite(2, HIGH);
  // 延迟3秒
  // Delay for 3 seconds
  delay(3000);
}