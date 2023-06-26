void SD_CARD_error_handler(SD_CARD_error_t err) {
  char SD_CARD_error_instruction[SD_CARD_ERROR_INSTRUCTION_BUFFER_SIZE]; //Instrução da forma: "Y\0", "S\0", ou "N\0";
  
  switch (err) {
    case (SD_CARD_error_t) SD_CARD_ERROR_CODES::SD_CARD_NOT_MOUNTED: {
      Serial.println("Falha na montagem do cartão SD!\n");
      break;
    }
    case (SD_CARD_error_t) SD_CARD_ERROR_CODES::SD_CARD_TYPE_NONE: {
      Serial.println("Nenhum cartão SD foi inserido!\n");
      break;
    }
    case (SD_CARD_error_t) SD_CARD_ERROR_CODES::SD_CARD_BEGIN_FAIL: {
      Serial.println("Falha na inicialização do cartão SD!\n");
      break;
    }
  }

  if (err == (SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_WRITE || err == (SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_APPEND) {
    switch (err) {
      case (SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_WRITE: {
        Serial.println("Falha na abertura do arquivo para operação de escrita!\n");
        break;
      }
      case (SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_APPEND: {
        Serial.println("Falha na abertura do arquivo para operação de concatenamento!\n");
        break;
      }
    }
  } else {
    Serial.println("Deseja prosseguir com a inicialização do sistema? (Y/N)(S/N)\n");
    Serial.println("Aviso: o sistema somente enviará dados via UART caso seja inicializado!\n");
    Serial.println("(Y/S/N) - ");
    delay(SD_CARD_ERROR_INSTRUCTION_INPUT_DURATION);
    if (Serial.available() > 0) {
      Serial.readBytes(SD_CARD_error_instruction, SD_CARD_ERROR_INSTRUCTION_BUFFER_SIZE);
    }
    if (SD_CARD_error_instruction[0] == 'Y' || SD_CARD_error_instruction[0] == 'S') {
      Serial.println("Prosseguindo com a inicialização do sistema!\n");
      ignore_SD_CARD = true;
    } else if (SD_CARD_error_instruction[0] == 'N') {
      Serial.println("Encerrando...!\n");
      exit(0);
    } else {
      Serial.println("Instrução não compreendida, prosseguindo com a inicialização!\n");
      ignore_SD_CARD = true;
    }
  }
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
  #ifdef ISDEBUG
  Serial.printf("Writing file: %s\n", path);
  #endif

  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    #ifdef ISDEBUG
    Serial.println("Failed to open file for writing!\n");
    #endif
    SD_CARD_error_handler((SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_WRITE);
  }
  if (file.print(message)) {
    #ifdef ISDEBUG
    Serial.println("File written!\n");
    #endif
  } else {
    #ifdef ISDEBUG
    Serial.println("Write failed!\n");
    #endif
  }
  file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message) {
  #ifdef ISDEBUG
  Serial.printf("Appending to file: %s\n", path);
  #endif

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    #ifdef ISDEBUG
    Serial.println("Failed to open file for appending!\n");
    #endif
    SD_CARD_error_handler((SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_APPEND);
  }
  if (file.print(message)) {
    #ifdef ISDEBUG
    Serial.println("Message appended!\n");
    #endif
  } else {
    #ifdef ISDEBUG
    Serial.println("Append failed!\n");
    #endif
  }
  file.close();
}