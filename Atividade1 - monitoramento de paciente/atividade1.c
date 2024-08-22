
#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include <stdio.h>


void vTask(void *pvParameters);
// Definição da função da tarefa vTask
void vTask(void *pvParameters)
{
	char* msg = (char*)pvParameters;
	for (;; )
	{
		vPrintString(msg);

		vTaskDelay(500);
		
	}

	vTaskDelete(NULL);
}
// Função para imprimir uma string seguida de um valor float formatado
void vPrintStringAndFloat(const char* msg, float value)
{
	char buffer[50];
	sprintf(buffer, "%s%.2f\n", msg, value);  // Formata a string com a mensagem e o valor float
	vPrintString(buffer);  // Imprime a string formatada usando vPrintString
}

// Tarefa para monitorar a temperatura corporal
void vTemperatureTask(void* pvParameters) {
	char* msg = (char*)pvParameters;
	for (;; )// Laço infinito para a execução contínua da tarefa
	{
		float temperature = (rand() % 160) / 10.0 + 30.0; //gera vlaor aleatorio entre 30 e 45


		char buffer[100];
		if (temperature > 37.5) { //verifica se a temperatura esta a cima de 37,5 graus, se sim, detecta febre
			sprintf(buffer, "Febre detectada: %.2f\n", temperature);
		}
		else if (temperature < 35) {//verifica se a temperatura esta a baixo de 35 graus, se sim, detecta hipotermia
			sprintf(buffer, "Hipotermia detectada: %.2f\n", temperature);
		}
		else {  // se não estiver em nenhuma condição a cima, apenas mostra a temperatura normal
			sprintf(buffer, "Temperatura corporal: %.2f\n", temperature);
		}

		vPrintString(buffer);
		vTaskDelay(1000);
	}
	vTaskDelete(NULL);
}


// Tarefa para monitorar os batimentos cardíacos
void vHeartRateTask(void* pvParameters) {
	char* msg = (char*)pvParameters;
	for (;; )
	{
		int heartRate = (rand() % 121) + 20; // Gera valor entre 20 e 140

		char buffer[100];
		//monitora os batimentos cardiacos
		if (heartRate > 90) {
			sprintf(buffer, "Batimento cardiaco alto: %d\n", heartRate);  // se os batimentos estiverem a cima de 90, mostra que o valor esta muito alto
		}
		else if (heartRate < 50) {
			sprintf(buffer, "Batimento cardiaco baixo: %d\n", heartRate); // se estiverem a baixo de 50, mostra que estão baixos
		}
		else {  // se não cumpre nenhum dos requisitos a cima, esta tudo normal
			sprintf(buffer, "Batimento cardiaco: %d\n", heartRate);
		}

		vPrintString(buffer); // Use o buffer para imprimir a mensagem
		vTaskDelay(1000); // Atraso de 1 segundo
	}
	vTaskDelete(NULL);
}

// Tarefa para monitorar os batimentos cardíacos
vOxygenSaturationTask(void* pvParameters) { 
	char* msg = (char*)pvParameters;
	for (;; )
	{
		int saturacao = (rand() % 20) + 80; // Gera valor entre 95 e 100
		char buffer[100]; //verifica a saturação de oxigenio no sangue
		if (saturacao < 90) { // se estiver a baixo de 90, esta baixa
			sprintf(buffer, "saturacao de oxigenio baixa: %d\n", saturacao);
		}
		else { // se estiver a cima de 90 esta normal
			sprintf(buffer, "saturacao de oxigenio normal: %d\n", saturacao);
		}
		vPrintString(buffer);// Use o buffer para imprimir a mensagem
		vTaskDelay(1000);// Atraso de 1 segundo
	}

	vTaskDelete(NULL);

}

int main_(void)
{
	static const char* heartRateMsg = "Batimentos cardiacos: "; // Mensagem padrão para batimentos cardíacos
	static const char* oxygenSaturationMsg = "Saturacao de oxigenio: ";// Mensagem padrão para saturação de oxigênio
	static const char* temperatureMsg = "Temperatura corporal: ";// Mensagem padrão para temperatura corporal

	xTaskCreate(vHeartRateTask, "Heart Rate Task", 1000, (void*)heartRateMsg, 1, NULL); //cria a task para monitoraento dos batimentos cardiacos
	xTaskCreate(vOxygenSaturationTask, "Oxygen Saturation Task", 1000, (void*)oxygenSaturationMsg, 1, NULL); // cria task para oxigenação do sangue
	xTaskCreate(vTemperatureTask, "Temperature Task", 1000, (void*)temperatureMsg, 1, NULL); // task para temperatura do paciente

	vTaskStartScheduler();

	for (;; );
	return 0;
}
