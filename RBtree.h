#pragma

#include<iostream>
#include<functional>

template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
class RBTree {
	Compare cmp = Compare();

	// Узел красно-черного дерева, хранит ключ, три указателя, цвет (0 - красный, 1 - черный) 
	// и признак nil для обозначения фиктивной вершины
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

	//  Определяем тип аллокатора для Node (Allocator для T нам не подходит)
	using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc < RBTreeNode >;

	//  Аллокатор для выделения памяти под объекты Node
	AllocType Alc;
};