#pragma once
#ifndef TREE1_H
#define TREE1_H
#include<iostream>
#include<vector>

template<class T>
class Tree
{
private:
	class Node
	{
	private:
		
	public:
		T _data;
		std::vector<Node*> _children;
		Node()
		{
			_children.resize(0);
		}
		Node(T data)
		{
			_data = data;
			_children.resize(0);
		}
		~Node()
		{

		}
	};
	Node* _root;
	bool recPath(Node element, std::vector<int>& path, T data);
	void recPrint(Node* element);
public:
	Tree() : _root(nullptr)
	{
	}
	Tree(T data)
	{
		_root = new Node(data);
	}
	Tree(Node* node) :_root(node)
	{

	}
	std::vector<int> getPath(T data);
	void addElement(T data, std::vector<int>& path);
	T getElement(std::vector<int>& arr);
	void print();
	Tree remove(T data);

};

template<class T>
inline bool Tree<T>::recPath(Node element, std::vector<int>& path, T data)
{
	for (int i = 0; i < element._children.size(); i++)
	{
		if (element._children[i]->_data == data)
		{
			path.push_back(i);
			return true;
		}
		if (element._children[i]->_children.size() != 0)
		{
			path.push_back(i);
			bool chek = recPath(*(element._children[i]), path, data);
			if (chek) return true;
			else path.pop_back();
		}
	}
	return false;
}

template<class T>
inline void Tree<T>::recPrint(Node* element)
{
	std::cout << "(";
	for (int i = 0; i < element->_children.size(); i++)
	{
		std::cout << element->_children[i]->_data;
		if (element->_children[i]->_children.size() != 0)
		{
			recPrint(element->_children[i]);
		}
		if (i != element->_children.size() - 1)
			std::cout << ", ";
	}
	std::cout << ")";
}

template<class T>
inline std::vector<int> Tree<T>::getPath(T data)
{
	std::vector<int> err = std::vector<int>(0);
	err.push_back(-1);
	if (_root == nullptr)
	{
		std::cout << "getPath() error: tree is empty" << std::endl;
		return err;
	}
	std::vector<int> path = std::vector<int>(0);
	if (_root->_data == data)
	{
		return std::vector<int>(0);
	}
	if (_root->_children.size() != 0)
	{
		bool check = recPath(*(_root), path, data);
		if (check) return path;
	}
	std::cout << "getPath() error: tree is empty" << std::endl;
	return err;
}

template<class T>
inline void Tree<T>::addElement(T data, std::vector<int>& path)
{
	if (_root == nullptr)
	{
		_root = new Node(data);
		return;
	}
	if (path.size() == 0)
	{
		_root->_children.push_back(new Node(data));
		return;
	}
	Node* current = _root;
	for (int i = 0; i < path.size(); i++)
	{
		current = current->_children[path[i]];
	}
	current->_children.push_back(new Node(data));
}

template<class T>
inline T Tree<T>::getElement(std::vector<int>& arr)
{
	if (arr.size() == 0)
	{
		std::cout << "getElement error." << std::endl;
		return -1;
	}
	Node* current = _root;
	for (int i = 0; i < arr.size(); i++)
	{
		current = current->_children[arr[i]];
	}
	return current->_data;
}

template<class T>
inline void Tree<T>::print()
{
	if (_root == nullptr)
	{
		std::cout << "Tree is empty." << std::endl;
		return;
	}
	std::cout << _root->_data << " ";
	if (_root->_children.size() != 0)
	{
		recPrint(_root);
		std::cout << std::endl;
	}
	else return;
}

template<class T>
inline Tree<T> Tree<T>::remove(T data)
{
	std::vector<int> path = this->getPath(data);
	Tree remTree;
	Node* curNode = _root;
	int i;
	for (i = 0; i < path.size() - 1; i++)
	{
		curNode = curNode->_children[path[i]];
	}
	remTree = Tree(curNode->_children[path[i]]);
	auto iter = curNode->_children.cbegin();
	curNode->_children.erase(iter + path[i]);
	return remTree;
}


//#include "Tree1.inl"


#endif // !TREE1_H
