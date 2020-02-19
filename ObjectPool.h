#pragma once
#include "singletonBase.h"

template <typename T>
struct Node
{
	Node<T>* prevNode;
	Node<T>* nextNode;
	T data;
};

template <typename T>
class ObjectPool : public singletonBase<ObjectPool<T>> {
private:
	Node<T>* poolHead;
	Node<T>* poolTail;
	Node<T>* lockHead;
	Node<T>* lockTail;
	int poolSize;
	int lockSize;
	int maxPoolSize;
public:
	//ObjectPool() �ʱⰪ �ο�
	ObjectPool() {
		poolHead = nullptr;
		poolTail = nullptr;
		lockHead = nullptr;
		lockTail = nullptr;
		poolSize = 0;
		lockSize = 0;
		maxPoolSize = 0;
	}
	~ObjectPool() {

	}
	//void Init(int inputSize) inputSize��ŭ �̸� �Ҵ�
	void Init(int inputSize) {
		maxPoolSize = inputSize;
		for (int i = 0; i < inputSize; i++) {
			createNode();
		}
	}
	//void createNode ���ο� ��� ����
	void createNode() {
		Node<T>* tempNode = new Node<T>;

		if (poolHead == nullptr) {
			tempNode->nextNode = nullptr;
			tempNode->prevNode = nullptr;
			poolHead = tempNode;
			poolTail = tempNode;
		}
		else {
			tempNode->prevNode = poolTail;
			tempNode->nextNode = nullptr;
			poolTail->nextNode = tempNode;
			poolTail = tempNode;
		}
		poolSize++;
	}
	//T* getObject() ������Ʈ Ǯ�� ��� �������� �ּҸ� ���� ��󿡰� ��ȯ
	T* getObject() {
		Node<T>* getTemp;
		if (poolHead == nullptr) {
			createNode();
		}

		getTemp = poolHead;

		if (poolHead == poolTail) {
			poolHead = nullptr;
			poolTail = nullptr;
		}
		else {
			poolHead = poolHead->nextNode;
		}

		if (lockHead == nullptr) {
			getTemp->prevNode = nullptr;
			getTemp->nextNode = nullptr;
			lockHead = getTemp;
			lockTail = getTemp;
		}
		else {
			getTemp->prevNode = lockTail;
			getTemp->nextNode = nullptr;
			lockTail->nextNode = getTemp;
			lockTail = getTemp;
		}
		poolSize--;
		lockSize++;
		return &(getTemp->data);
	}
	//void returnObject(T* inputData) ��ȯ�� ��� �������� �ּҸ� Ǯ�� ����
	void returnObject(T* inputData) {
		Node<T>* returnTemp = FindNode(inputData, lockHead);

		if (lockHead == nullptr) {

		}

		if (returnTemp == lockHead) {
			lockHead = lockHead->nextNode;
			if (lockHead != nullptr)lockHead->prevNode = nullptr;
		}
		else if (returnTemp == lockTail) {
			lockTail = lockTail->prevNode;
			lockTail->nextNode = nullptr;
		}
		else {
			returnTemp->nextNode->prevNode = returnTemp->prevNode;
			returnTemp->prevNode->nextNode = returnTemp->nextNode;
		}

		if (poolHead == nullptr) {
			returnTemp->prevNode = nullptr;
			returnTemp->nextNode = nullptr;
			poolHead = returnTemp;
			poolTail = returnTemp;
		}
		else {
			returnTemp->prevNode = poolTail;
			returnTemp->nextNode = nullptr;
			poolTail->nextNode = returnTemp;
			poolTail = returnTemp;
		}
		poolSize++;
		lockSize--;
	}
	//Node<T>* FindNode(T* inputData, Node<T>* listHead) listHead�� �ش��ϴ� ����Ʈ�� ��� ���Ҹ� ��ȸ�Ͽ� inputData�� ��ġ�ϴ� Data�� ���� ��带 �˻�
	Node<T>* FindNode(T* inputData, Node<T>* listHead) {
		Node<T>* iter = listHead;
		while (true) {
			if (iter == nullptr) {
				return nullptr;
			}
			else if (&(iter->data) == inputData) {
				return iter;
			}
			iter = iter->nextNode;
		}
	}
	//����׿� poolList Size gether
	int GetPoolSize() {
		return poolSize;
	}
	//����׿� lockList Size gether
	int GetLockSize() {
		return lockSize;
	}
	int ActualPoolSize() {
		return GetListSize(poolHead);
	}
	int ActualLockSize() {
		return GetListSize(lockHead);
	}
	int GetListSize(Node<T>* listhead) {
		Node<T>* iter = listhead;
		int cnt = 0;
		while (true) {
			if (iter == nullptr) {
				break;
			}
			else {
				cnt++;
			}
			iter = iter->nextNode;
		}
		return cnt;
	}
};