/***************************************************************************
 *   Copyright (C) 2003 by Valentin Mihov                                  *
 *   valo@valo                                                             *
 *                                                                         *
 *   $Id: CList.h,v 1.3 2003/12/24 16:21:51 valo Exp $                       *
 ***************************************************************************/

#ifndef _CLIST_H_
#define _CLIST_H_


/**
 * 
 * Valentin Mihov
 **/
template <class T>
class CList
{
  class CListItem
  {
    public:
	  T key;
	  CListItem *prev,*next;
	  
	  CListItem() { prev = next = NULL;}
	  CListItem(T ele) { prev = next = NULL;key = ele; }
	  ~CListItem() {}
  };

public:
  CList() { list = NULL;list_length = 0; }
  ~CList();

  /* Push functions */
  void PushFront(T ele);
  void PushBack(T ele);
  void PushAfter(T ele,CListItem *item);
  void PushBefore(T ele,CListItem *item);
  
  /* Pop functions */
  void PopFront();
  void PopBack();
  void Pop(CListItem *item);
  
  CListItem* begin() { return (list_length)?list:NULL; }
  int length() { return list_length; }
  
private:
  CListItem *list;
  int list_length;
};

template <class T>
CList<T>::~CList()
{
	CListItem *item = list,*prev = NULL;
	while (item && item->next)
	{
		prev = item;
		item = item->next;
		delete prev;
	}
	delete prev;
}


template <class T>
void CList<T>::PushFront(T ele)
{
	CListItem *item = new CListItem(ele);
	item->next = list;
	if (list) list->prev = item;
	list = item;
	list_length++;
}


template <class T>
void CList<T>::PushBack(T ele)
{
	if (!list) PushFront(ele);
	CListItem *item = new CListItem(ele);
	CListItem inter = list.Begin();
	while (inter->next) (*inter)++;
	inter->next = item;
	item->prev = inter;
	list_length++;
}

template <class T>
void CList<T>::PushAfter(T ele,CListItem *item)
{
	if (!item) return;
	CListItem *new_item = new CListItem(ele);
	if (item->next) { new_item->next = item->next;item->next->prev = new_item; }
	new_item->prev = item;
	item->next = new_item;
	list_length++;
}

template <class T>
void CList<T>::PushBefore(T ele,CListItem *item)
{
	if (!item) return;
	CListItem *new_item = new CListItem(ele);
	if (item->prev) { new_item->prev = item->prev;item->prev->next = new_item; }
	new_item->next = item;
	item->prev = new_item;
	list_length++;
}

template <class T>
void CList<T>::PopFront()
{
	if (!list) return;
	CListItem *item = list;
	if (item->next) { list = list->next; list->prev = NULL;}
	else list = NULL;
	delete item;
	list_length--;
	if (list_length == 0) list = NULL;
}

template <class T>
void CList<T>::PopBack()
{
	CListItem *inter = list;
	if (!list) return;
	if (list_length == 1) PopFront();
	while (inter->next) inter++;
	inter->prev->next = NULL;
	delete inter;
	list_length--;
	if (list_length == 0) list = NULL;
}

template <class T>
void CList<T>::Pop(CListItem *item)
{
	CListItem *after;
	if (!item) return;
	if (item->prev) { item->prev->next = item->next;after = item->prev; }
	if (item->next) { item->next->prev = item->prev;after = item->next; }
	delete item;
	list_length--;
	if (list_length == 0) list = NULL;
}

#endif
