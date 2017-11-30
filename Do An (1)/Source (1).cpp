#include "Process.h"
int main()
{
	//nAirplane begin = 0
	system("color 5A");

	setFullScreen();
	PTR_LIST_AIRPLANE l = new LIST_AIRPLANE;
	LoadAirplane(l);
	TREE_PASSENGER t;
	InitTreePassenger(t);
	LoadPassenger(t);


	/*for (int i = 0; i  <= l->n; i++)
	{
		LIST_FLIGHT fl = l->listAirplane[i]->listFlight;
		NODE_FLIGHT* p = fl.pHead;
		
		while (p != NULL)
		{
			delete[]p->data.listTicket;
				p->data.listTicket = new TICKET[MAX_TICKET];
				p = p->pNext;

		}
		
	}
*/
	
	MageAll(l,t);
	SaveAirplane(l);
	SavePassenger(t);


	system("pause");
	return 0;
}