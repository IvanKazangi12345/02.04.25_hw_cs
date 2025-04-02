//Main.cpp
#include <iostream>
#include "Socket.h"

using namespace std;

int main()
{
	int nChoice;
	char rec[225] = "\n 1 - 50 $ \n 2 - 80 $ \n 3 - 90 $ \n 4 - 120 $ \n 5 - 250 $";
	int port = 24242; //выбираем порт
	int balance = 0;
	string ipAddress = "127.0.0.1"; //Адрес сервера
	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];
	cout << "1) Start server" << endl;
	cout << "2) Connect to server" << endl;
	cout << "3) Exit" << endl;
	cin >> nChoice;
	if (nChoice == 1)
	{
		ServerSocket server;
		cout << "Starting server..." << endl;
		//Запускаем сервер
		server.StartHosting(port);
		while (true)
		{
			cout << "\tWaiting..." << endl;
			//Получаем данные от клиента
			//и сохраняем в переменной receiveMessage
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			if (strcmp(receiveMessage, "rec") == 0) {
				strcpy_s(sendMessage, rec);
				server.SendData(sendMessage);
			}
			else if (strcmp(receiveMessage, "1") == 0) {
				server.SendData("50$");
				balance += 50;
			}
			else if (strcmp(receiveMessage, "2") == 0) {
				server.SendData("80$");
				balance += 80;
			}
			else if (strcmp(receiveMessage, "3") == 0) {
				server.SendData("90$");
				balance += 90;
			}
			else if (strcmp(receiveMessage, "4") == 0) {
				server.SendData("120$");
				balance += 120;
			}
			else if (strcmp(receiveMessage, "5") == 0) {
				server.SendData("250$");
				balance += 250;
			}
			else if (strcmp(receiveMessage, "balance") == 0) {
				char ch[50];
				sprintf_s(ch, "%d", balance);
				server.SendData(ch);
			}
			else {
				server.SendDataMessage();
			}
			while (strcmp(receiveMessage, "cont") == 0) {
			
			}
			//Отправляем данные клиенту
			//Если есть сообщение "end", завершаем работу
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
	}
	else if (nChoice == 2)
	{
		//cout << "Enter an IP address: " << endl;
		////Запрашиваем IP сервера
		//cin >> ipAddress;
		ClientSocket client;
		//подключаемся к серверу
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			//отправляем сообщение
			client.SendDataMessage();
			cout << "\tWaiting" << endl;
			//получаем ответ
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
		//Закрываем соединение
		client.CloseConnection();
	}
	else if (nChoice == 3)
		return 0;
}










