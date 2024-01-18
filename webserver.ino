#include <ESP8266WiFi.h>

// Substitua essas informações com as suas credenciais Wi-Fi
const char* ssid = "nome da rede";
const char* password = "senha da rede";

// Criar uma instância do servidor na porta 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado ao Wi-Fi");

  // Iniciar o servidor
  server.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  // Verificar se há clientes
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Novo cliente conectado");

    // Ler a requisição do cliente
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Enviar a resposta HTML
    String html = "<html><meta charset=UTF-8 /><body><h1>ESP8266 Web Server</h1><p>Olá, este é o seu servidor web!</p></body></html>";
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(html);

    // Aguardar um momento antes de fechar a conexão
    delay(10);
    client.stop();
    Serial.println("Cliente desconectado");
  }
}
