const char SEPARATOR              = ',';
const char TERMINATOR             = '\n';

/*
  Helper Functions for Receive Message
*/
static void write_to_serial(twai_message_t& message)
{
  // Handle received message

  Serial.print("Received New Message: ");

  if (message.extd)
    Serial.print("Message is in Extended Format, ");
  else
    Serial.print("Message is in Standard Format, ");

  Serial.printf("ID: %x\nBytes: ", message.identifier);

  if (!message.rtr)
  {
    for (int i = 0; i < message.data_length_code; i++)
      Serial.printf("data[%d] = %02x, ", i, message.data[i]);

    Serial.println("\n..................................................\n");
  }  
}
static void format_to_can_drive(twai_message_t& message)
{
  // packet format (hex string): [ID],[RTR],[IDE],[DATABYTES 0..8B]\n
  // example: 014A,00,00,1A002B003C004D\n

  write_hex(message.identifier);
  Serial.print(SEPARATOR);
  
  write_hex(message.rtr);
  Serial.print(SEPARATOR);

  write_hex(message.extd);
  Serial.print(SEPARATOR);

  // DLC is determinded by number of data bytes, format: [00]
  for (int i = 0; i < message.data_length_code; i++)
    write_hex(message.data[i]);

  Serial.print(TERMINATOR);
}

static void write_hex(long digits)
{
  if ( digits < 0x10 )
    Serial.print("0");

  Serial.print(digits, HEX);
}
