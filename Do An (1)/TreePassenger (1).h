#pragma once





//include r vẫn k đc
//bool CheckIdIsExisted(TREE_PASSENGER t, int x)
//{
//	if (t != NULL)
//	{
//		if (t->data.GetId() == x)
//		{
//			return true;
//		}
//		if (t->data.GetId() > x)
//		{
//			CheckIdIsExisted(t->pLeft, x);
//		}
//		else
//		{
//			CheckIdIsExisted(t->pRight, x);
//		}
//	}
//	return false;
//}

//Derecursion
// ông để dạng include đi
// là chuyển cây nhị phân sang file riêng hả okm
//NODE_PASSENGER* SearchNode1(TREE_PASSENGER t, Passenger x)
//{
//	if (t != NULL)
//	{
//		NODE_PASSENGER* p = t;
//		while (p != NULL)
//		{
//			if (p->data.GetId() == x.GetId())
//			{
//				return p;
//			}
//			else if (p->data.GetId() > x.GetId())
//			{
//				p = p->pLeft;
//			}
//			else
//			{
//				p = p->pRight;
//			}
//		}
//	}
//	return NULL;
//}
//
//
//

//
//void DeleteNode(TREE_PASSENGER &t, Passenger x)
//{
//	if (t == NULL)
//	{
//		return;
//	}
//	else
//	{
//		if (x.GetId() > t->data.GetId())
//		{
//			DeleteNode(t->pRight, x);
//		}
//		else if (x.GetId() < t->data.GetId())
//		{
//			DeleteNode(t->pLeft, x);
//		}
//		else // x.id = t->data.id
//		{
//			NODE_PASSENGER *temp = t;
//			if (t->pLeft == NULL)     //1.
//			{
//				t = temp->pRight;
//			}
//			else if (t->pRight == NULL)
//			{
//				t = temp->pLeft;
//			}
//			//5. 1-> delete node have 0 or 1 child
//			else // node have 2 child
//			{
//				//way 1: leftest of right, 
//				//findReplace(temp, t->pRight);
//
//				//way 2: rightest of left
//				FindReplace(temp, t->pLeft);
//			}
//			delete temp;
//
//		}
//	}
//}









//
//
//void NLR(TREE_PASSENGER t)
//{
//	if (t != NULL)
//	{
//		OutputPassenger(t->data);
//		NLR(t->pLeft);
//		NLR(t->pRight);
//	}
//}
//

//void LNR(TREE_PASSENGER t)
//{
//	if (t != NULL)
//	{
//		LNR(t->pLeft);
//		cout << t->data << " ";
//
//		LNR(t->pRight);
//	}
//}
//void LRN(TREE_PASSENGER t)
//{
//	if (t != NULL)
//	{
//		LRN(t->pLeft);
//		LRN(t->pRight);
//		cout << t->data << " ";
//
//
//	}
//}
//void NRL(TREE_PASSENGER t)
//{
//	if (t != NULL)
//	{
//		cout << t->data << " ";
//		NRL(t->pRight);
//
//
//		NRL(t->pLeft);
//
//	}
//}
//void RNL(TREE_PASSENGER t)
//{
//	if (t != NULL)
//	{
//		RNL(t->pRight);
//
//		cout << t->data << " ";
//		RNL(t->pLeft);
//
//	}
//}
//void RLN(TREE_PASSENGER t)
//{
//	if (t != NULL)
//	{
//		RLN(t->pRight);
//		RLN(t->pLeft);
//		cout << t->data << " ";
//
//
//	}
//}

//rồi. k đc t chuyển qa strcut. mệt quá


