#include <iostream>
using namespace std;
class Connector {
public:
        // Конструктор. Получает параметром адрес, куда требуется подключиться.
        // Выполняет необходимую инициализацию соединения. 
        // После завершения работы конструктора соединение установлено и готово к работе.
        // Если возникают какие-либо проблемы - выбрасывает exception с описанием проблемы.
        Connector(const string& address) {
        }
    
        // Отправить по установленному соединению сообщение, текст сообщения передаётся в параметре data.
        // Если возникают какие-либо проблемы - выбрасывает exception с описанием проблемы.
        void sendRequest(const string& data) {
        }
};
int main()
{
    int n;
    cin>>n;
    try
    {
        for (int i=0; i<n; i++)
        {
            string adress;
            cin>>adress;
            cout<<adress<<":";
            Connector a(adress);
            a.sendRequest("HELLO");
        }
    }
    catch(string b)
    {
        cout<<b<<endl
    }
    return 0;
}