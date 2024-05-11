#pragma

#include<iostream>
#include<functional>

template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
class RBTree {
	Compare cmp = Compare();

	// ���� ������-������� ������, ������ ����, ��� ���������, ���� (0 - �������, 1 - ������) 
	// � ������� nil ��� ����������� ��������� �������
	class RBTreeNode {
	public:
		RBTreeNode* parent;
		RBTreeNode* left;
		RBTreeNode* right;

		T data;
		bool color;
		bool isNull;
		RBTreeNode(T value = T(), RBTreeNode* p = nullptr, RBTreeNode* l = nullptr, RBTreeNode* r = nullptr,
			bool n = false, bool c = false) :
			parent(p), data(value), left(l), right(r), isNull(n), color(c) {}
	};

	//  ���������� ��� ���������� ��� Node (Allocator ��� T ��� �� ��������)
	using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc < RBTreeNode >;

	//  ��������� ��� ��������� ������ ��� ������� Node
	AllocType Alc;
};