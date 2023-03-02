#ifndef WRITE_TO_CAN_DRIVE
  #define WRITE_TO_CAN_DRIVE
#endif

static void handle_rx_message(twai_message_t& message)
{
  #undef WRITE_TO_CAN_DRIVE

  #ifdef WRITE_TO_CAN_DRIVE
    format_to_can_drive(message);
  #else
    write_to_serial(message);
  #endif
}

void handle_tx_message(twai_message_t message)
{
  String string = "Data with ID [###] will be transmitted: ";
  string.replace("###", String(message.identifier, HEX));

  Serial.print(string);

  for (int i = 0; i < message.data_length_code; i ++)
  {
    printf("data[%d] = %#02x", i, message.data[i]);

    if (i < message.data_length_code)
      printf(", ");
  }
    

  // Queue message for transmission
  esp_err_t result = twai_transmit(&message, portMAX_DELAY);

  if (result == ESP_OK)
    printf("\n%s: Message queued for transmission.\n", esp_err_to_name(result));
  else
    printf("\n%s: Failed to queue the message for transmission.\n", esp_err_to_name(result));

  Serial.println("..................................................\n");
}

/*
Helper Functions for Transmit Message
*/

void transmit_normal_message(uint32_t identifier, uint8_t data[], uint8_t data_length_code = TWAI_FRAME_MAX_DLC)
{
  // configure message to transmit
  twai_message_t message = {
    .identifier = identifier,
    .data_length_code = data_length_code,
  };

  memcpy(message.data, data, data_length_code);

  //Transmit messages using self reception request
  handle_tx_message(message);
}

void transmit_loop_back_message(uint32_t identifier, uint8_t data[], uint8_t data_length_code = TWAI_FRAME_MAX_DLC)
{
  // configure message to transmit
  twai_message_t message = {
    {
      {
        .self = 1,
      }
    },
    .identifier = identifier,
    .data_length_code = data_length_code,
  };

  memcpy(message.data, data, data_length_code);

  //Transmit messages using self reception request
  handle_tx_message(message);
}

void transmit_remote_transmission_request_message(uint32_t identifier, uint8_t data[], uint8_t data_length_code = TWAI_FRAME_MAX_DLC)
{
  // configure message to transmit
  twai_message_t message = {
    {
      {
        .rtr = 1,
      }
    },
    .identifier = identifier,
    .data_length_code = data_length_code,
  };

  memcpy(message.data, data, data_length_code);

  //Transmit messages using self reception request
  handle_tx_message(message);
}


