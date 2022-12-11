#include <winsock2.h>
#include <Windows.h>


#define DEFAULT_BUFLEN 512
#define NUM_OF_SUBS 20
#define TOPIC_LEN 15
#define MESSAGE_LEN 250



typedef struct TopicSubscribers {
	char tema[TOPIC_LEN];
	SOCKET nizSub[NUM_OF_SUBS];
	int velicina;
}TopicSub;

struct Queue
{
	int prvi, poslednji, velicina;
	unsigned kapacitet;
	TopicSubscribers* niz;
};

struct TopicMessage {
	char tema[TOPIC_LEN];
	char poruka[MESSAGE_LEN];
};

struct MessageQueue
{
	int prvi, poslednji, velicina;
	unsigned kapacitet;
	TopicMessage* niz;
};

struct Subscriber {
	SOCKET socket;
	HANDLE hSemaphore;
	bool running;
};

struct MessageStruct
{
	int header;
	char poruka[DEFAULT_BUFLEN - 4];

};

struct ThreadArgument {
	SOCKET socket;
	int brKlijenta;
	int redniBroj;

};