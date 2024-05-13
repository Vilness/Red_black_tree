#pragma

#include<iostream>
#include<functional>
#include<queue>

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

public:
	//  ��� ���� ������ ��������� ��������� - ��� ����������������
	using key_type = T;
	using key_compare = Compare;
	using value_compare = Compare;
	using value_type = typename T;
	using allocator_type = typename AllocType;
	using size_type = typename size_t;
	using difference_type = typename size_t;
	using pointer = typename T*;
	using const_pointer = typename const pointer;
	using reference = value_type&;
	using const_reference = const value_type&;
	class iterator;   //  ��������������� ���������� ������ iterator, �.�. �� �������� ����	
	using const_iterator = iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
	// ��������� �� ��������� �������
	RBTreeNode* dummy;

	//  ��������� ��������� � ������
	size_type tree_size = 0;

	// �������� ��������� ������� - ������������ ������ ��� �������� ������
	inline RBTreeNode* make_dummy()
	{
		// �������� ������ �� ������� ���� ��� ���������������
		dummy = Alc.allocate(1);

		//  ��� ����, ���������� ����������� �� ���� (left, right, parent) �������������� � ��������
		std::allocator_traits<AllocType>::construct(Alc, &(dummy->parent));
		dummy->parent = dummy;

		std::allocator_traits<AllocType>::construct(Alc, &(dummy->left));
		dummy->left = dummy;

		std::allocator_traits<AllocType>::construct(Alc, &(dummy->right));
		dummy->right = dummy;

		dummy->isNull = true;
		dummy->color = true;

		//  ���������� ��������� �� ��������� �������
		return dummy;
	}

	// �������� ���� ������ 
	inline RBTreeNode* make_node(T&& elem, RBTreeNode* parent, RBTreeNode* left, RBTreeNode* right, bool color)
	{
		// ������ ����� ��� ��, ��� � ��������� �������, ������ ��� ���� ������ ����� ������� �����������
		RBTreeNode* new_node = Alc.allocate(1);

		//  ��� ����, ���������� ����������� �� ���� (left, right, parent) �������������� � ��������
		std::allocator_traits<AllocType>::construct(Alc, &(new_node->parent));
		new_node->parent = parent;

		std::allocator_traits<AllocType>::construct(Alc, &(new_node->left));
		new_node->left = left;

		std::allocator_traits<AllocType>::construct(Alc, &(new_node->right));
		new_node->right = right;

		//  ������������ ���� ������
		std::allocator_traits<AllocType>::construct(Alc, &(new_node->data), std::forward<T>(elem));

		new_node->isNull = false;
		new_node->color = color;

		//  ���������� ��������� �� ��������� �������
		return new_node;
	}

	// �������� ��������� �������
	inline void delete_dummy(RBTreeNode* node) {
		std::allocator_traits<AllocType>::destroy(Alc, &(node->parent));
		std::allocator_traits<AllocType>::destroy(Alc, &(node->left));
		std::allocator_traits<AllocType>::destroy(Alc, &(node->right));
		std::allocator_traits<AllocType>::deallocate(Alc, node, 1);
	}

	// �������� ������� ������
	inline void delete_node(RBTreeNode* node) {
		//  ��� ������� ���� ������ (���������� ����������), � ��������� ������� ��� ��, ��� � ���������
		std::allocator_traits<AllocType>::destroy(Alc, &(node->data));
		delete_dummy(node);
	}

	//  ����������� ����������� ������
	RBTreeNode* recur_copy_tree(RBTreeNode* source, const RBTreeNode* source_dummy) {
		//  ������� ������ �������� ����������
		RBTreeNode* left_sub_tree;
		if (source->left != source_dummy)
			left_sub_tree = recur_copy_tree(source->left, source_dummy);
		else
			left_sub_tree = dummy;

		RBTreeNode* right_sub_tree;
		if (source->right != source_dummy)
			right_sub_tree = recur_copy_tree(source->right, source_dummy);
		else
			right_sub_tree = dummy;

		//  ������ ������ ����������� ����
		RBTreeNode* current = make_node(std::move(source->data), nullptr, left_sub_tree, right_sub_tree, source->color);
		//  ������������� ���������
		if (source->right != source_dummy)
			current->right->parent = current;
		if (source->left != source_dummy)
			current->left->parent = current;
		//  �� � ��, ����� ����������
		return current;
	}
private:
	RBTreeNode* GetMin(RBTreeNode* x) {
		while (!x->left->isNul)
			x = x->left;
	}

	RBTreeNode* GetMax(RBTreeNode* x) {
		while (!x->right->isNul)
			x = x->right;
	}
public:
	RBTree(Compare comparator = Compare(), AllocType alloc = AllocType())
		: dummy(make_dummy()), cmp(comparator), Alc(alloc) {}

	RBTree(std::initializer_list<T> il) : RBTree() {
		for (const T& x : il)
			insert(x);
	}

	RBTree(const RBTree& tree) : RBTree() {
		//  ������ �����
		tree_size = tree.tree_size;
		if (tree.empty()) return;

		dummy->left = recur_copy_tree(tree.dummy->left, tree.dummy);
		dummy->left->parent = dummy;

		//  �������� ���������� min � max
		dummy->parent = GetMax(dummy->left);
		dummy->right = GetMin(dummy->left);
	}

	const RBTree& operator=(const RBTree& tree)
	{
		if (this == &tree) return *this;

		this->clear();

		//  ������ �����
		tree_size = tree.tree_size;
		if (tree.empty()) return;

		dummy->left = recur_copy_tree(tree.dummy->left, tree.dummy);
		dummy->left->parent = dummy;

		//  �������� ���������� min � max
		dummy->parent = GetMax(dummy->left);
		dummy->right = GetMin(dummy->left);

		return *this;
	}

	RBTree(RBTree&& tree) : RBTree() {
		this->swap(tree);
	}

	const RBTree& operator=(RBTree&& tree) {
		this->swap(tree);
		return *this;
	}	

	//  ����� ��������� ��� ������-������� ������ ������ ������
	class iterator
	{		
	private:
		friend class RBTree;
		//  ��������� �� ���� ������
		RBTreeNode* node;

		iterator(RBTreeNode* n) : node(n) {}
	public:
		//  ���������� ����������� ���� � ������������ � ������������ ��������� � ��������������� ����������
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = RBTree::value_type;
		using difference_type = RBTree::difference_type;
		using pointer = RBTree::pointer;
		using reference = RBTree::reference;

		//  �������� � ����, �� ������� ��������� ��������
		inline const T& operator*() const { return node->data; }

		//  ������������ - ��������� ������� ���������
		iterator& operator++() {
			if (!node->right->isNull) {
				node = node->right;
				while (!node->left->isNull)
					node = node->left;
				return *this;
			}

			while (!node->parent->isNull && node->parent->right == node)
				node = node->parent;	
			node = node->parent;
			return *this;
		}

		//  ������������ - ������� �� ���������� ������� ���������
		iterator& operator--() {
			if (!node->left->isNull) {
				node = node->left;
				while(!node->right->isNull)
					node = node->right;
				return *this;
			}

			while (!node->parent->isNull && node->parent->left == node)
				node = node->parent;	
			node = node->parent;
			return *this;
		}

		//  �������������
		iterator operator++(int) {
			iterator res(*this);
			++(*this);
			return res;
		}

		//  �������������
		iterator operator--(int) {
			iterator res(*this);
			--(*this);
			return res;
		}

		friend bool operator==(const iterator& it_1, const iterator& it_2) { return it_1.node == it_2.node; }

		friend bool operator != (const iterator& it_1, const iterator& it_2) { return !(it_1 == it_2); }

		//  ��� �������� �� ����������� ����� ������� � ��������� �����������
		const iterator& operator=(const reverse_iterator& it) = delete;
		bool operator==(const reverse_iterator& it) = delete;
		bool operator!=(const reverse_iterator& it) = delete;
		iterator(const reverse_iterator& it) = delete;
	};

	iterator begin() const noexcept { return iterator(dummy->right); }
	iterator end() const noexcept { return iterator(dummy); }

	reverse_iterator rbegin() const	noexcept { return reverse_iterator(dummy); }
	reverse_iterator rend() const noexcept { return reverse_iterator(dummy->right); }

	AllocType get_allocator() const noexcept { return Alc; }
	key_compare key_comp() const noexcept { return cmp; }
	value_compare value_comp() const noexcept { return cmp; }

	inline bool empty() const noexcept { return tree_size == 0; }

	size_type size() const { return tree_size; }

	void swap(RBTree& tree) {
		std::swap(tree_size, tree.tree_size);
		std::swap(dummy, tree->dummy);
	}

private:
	
	///��������� ����� �������
	void left_rotate(RBTreeNode* x) {
		RBTreeNode* r = x->right;
		x->right = r->left;

		if (r->left != dummy)
			r->left->parent = x;
		r->parent = x->parent;
		if (x->parent == dummy)
			dummy->left = r;
		else if (x->parent->left == x)
			x->parent->left = r;
		else
			x->parent->right = r;
		r->left = x;
		x->parent = r;
	}

	///��������� ������ �������
	void right_rotate(RBTreeNode* x) {
		RBTreeNode* l = x->left;
		x->left = l->right;

		if (l->right != dummy)
			l->right->parent = x;
		l->parent = x->parent;
		if (x->parent == dummy)
			dummy->left = l;
		else if (x->parent->left == x)
			x->parent->left = l;
		else
			x->parent->right = l;
		l->right = x;
		x->parent = l;
	}

	void insert_fixup(RBTreeNode* x) {
		while (!x->color && !x->parent->color) {
			RBTreeNode* xpp = x->parent->parent;
			if (x->parent == xpp->left) {
				if (!xpp->right->color) {
					x->parent->color = true;
					xpp->right->color = true;
					xpp->color = false;
					x = xpp;
				}
				else {
					if (x == x->parent->right) {
						x = x->parent;
						left_rotate(x);
					}
					x->parent->color = true;
					xpp->color = false;
					right_rotate(xpp);
				}
			}
			else {
				if (!xpp->left->color) {
					x->parent->color = true;
					xpp->left->color = true;
					xpp->color = false;
					x = xpp;
				}
				else {
					if (x == x->parent->left) {
						x = x->parent;
						right_rotate(x);
					}
					x->parent->color = true;
					xpp->color = false;
					left_rotate(xpp);
				}
			}
		}
		dummy->left->color = true;
	}

	///������� �������� � ������
	std::pair<iterator, bool> insert(RBTreeNode* node) {
		RBTreeNode* x = dummy->left;
		RBTreeNode* p = dummy;
		while (x != dummy) {
			p = x;
			if (cmp(node->data, x->data))
				x = x->left;
			else if (cmp(x->data, node->data))
				x = x->right;
			else
				return std::make_pair(iterator(dummy), false);
		}

		if (p == dummy)
			dummy->left = dummy->right = dummy->parent = node;
		else if (cmp(node->data, p->data)) {
			p->left = node;
			//���� y - ������� � ������
			if (p == dummy->right)
				dummy->right = node;
		}
		else {
			p->right = node;
			//���� y - �������� � ������
			if (p == dummy->parent)
				dummy->parent = node;
		}
		node->parent = p;
		node->left = node->right = dummy;
		node->color = false;
		tree_size++;
		insert_fixup(node);
		return std::make_pair(iterator(node), true);
	}

public:
	//������� �������� � ������
	std::pair<iterator, bool> insert(const T& value) {
		RBTreeNode* node = make_node(std::move(static_cast<T>(value)), nullptr, nullptr, nullptr, false);
		auto res = insert(node);
		if (!res.second)
			delete_node(node);
		return res;
	}

	//������� �������� � ������
	std::pair<iterator, bool> insert(T&& value) {
		RBTreeNode* node = make_node(std::move(value), nullptr, nullptr, nullptr, false);
		auto res = insert(node);
		if (!res.second)
			delete_node(node);
		return res;
	}

	//������� ���������
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		while (first != last)
			insert(*first++);
	}

	//���������� �������� �� �������, � ������ value, ���� ��� ���, �� end()
	iterator find(const value_type& value) const {
		RBTreeNode* cur = dummy->left;
		while (cur != dummy) {
			if (cmp(value, cur->data))
				cur = cur->left;
			else if (cmp(cur->data, value))
				cur = cur->right;
			else
				return iterator(cur);
		}
		return iterator(cur);
	}	

	//��e����� �� ���������� �������, ������� ��� ������ ���������
	iterator lower_bound(const value_type& key) const {}

	//��e����� �� ���������� �������, ������� ��� ������ ���������
	iterator upper_bound(const value_type& key) const {}

	//�����?
	size_type count(const value_type& key) const {
		return find(key) != end() ? 1 : 0;
	}

	//�� ������?
	std::pair<const_iterator, const_iterator> equal_range(const value_type& key) const {
		const_iterator current{ dummy->left }, left{ dummy->left }, right{ dummy->left };
		while (!current.isNull()) {
			if (!cmp(key, *current)) {
				left = current;
				current = current.Right();
			}
			else {
				right = current;
				current = current.Left();
			}
		}
		return std::make_pair(left, right);
	}

	//  �������� ��������, ��������� ����������. ���������� ��������� ������� ����� ����������
	iterator erase(iterator elem) {}

	//������� ������� �� ��������� elem, ���� ��� ��� ���������� 0, ����� 1
	size_type erase(const value_type& elem) {}

	//  ���������!!!
	iterator erase(const_iterator first, const_iterator last) {}

	//  ����������� ������ � ��������� - � "����������" ���������� ������ ���� �� ������
	void printNode(const RBTreeNode* current, std::string spaces = "") const {			
		if (current == dummy) {
			std::cout << spaces << "Dummy\n";
			return;
		}
		printNode(current->right, spaces + "\t");
		char color = current->color ? 'b' : 'r';
		if (current->parent->right == current)
			std::cout << spaces + "/" << current->data << color << "\n";
		else
			std::cout << spaces + "\\" << current->data << color << "\n";
		printNode(current->left, spaces + "\t");
	}

	void PrintTree() const {
		std::cout << "-------------------RBTree:--------------------\n";
		printNode(dummy->left);
		std::cout << "----------------------------------------------\n";
	}

private:
	bool recur_equal(RBTreeNode* root1, RBTreeNode* root2) const {}
public:
	///����������� ��������� ���� �������� �� ��������� � �� ���������
	bool isEqualTo(const RBTree<T>& tree) const {
		return recur_equal(dummy->left, tree.dummy->left);
	}

	//���� ���������� �� �������,��� ������. ����������� ����� ������������� �������� ��������.
	friend bool operator==(const RBTree<T>& tree_1, const RBTree<T>& tree_2) {
		return tree_1.isEqualTo(tree_2);
	}

private:
	//  ����������� �������� ����� ������, �� ������� ��������� �������
	void Free_nodes(RBTreeNode* node) {
		if (node != dummy) {
			Free_nodes(node->left);
			Free_nodes(node->right);
			delete_node(node);
		}
	}

public:
	//  ������� ������ (��� �������� ��������� �������)
	void clear() {
		Free_nodes(dummy->left);
		tree_size = 0;
		dummy->parent = dummy->left = dummy->right = dummy;
	}

	~RBTree() {
		clear();
		delete_dummy(dummy);
	}
};

template <class Key, class Compare, class Allocator>
void swap(RBTree<Key, Compare, Allocator>& x, RBTree<Key, Compare, Allocator>& y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
};

//����������, ��� � ��������� ���������� � ����� ������ ��� ����� �����:

template <class Key, class Compare, class Allocator>
bool operator==(const RBTree<Key, Compare, Allocator>& x, const RBTree<Key, Compare, Allocator>& y) {
	typename RBTree<Key, Compare, Allocator>::const_iterator it1{ x.begin() }, it2{ y.begin() };
	while (it1 != x.end() && it2 != y.end() && *it1 == *it2) {
		++it1; ++it2;
	}

	return it1 == x.end() && it2 == y.end();
}

template <class Key, class Compare, class Allocator>
bool operator<(const RBTree<Key, Compare, Allocator>& x, const RBTree<Key, Compare, Allocator>& y) {

	typename RBTree<Key, Compare, Allocator>::const_iterator it1{ x.begin() }, it2{ y.begin() };
	while (it1 != x.end() && it2 != y.end() && *it1 == *it2) {
		++it1; ++it2;
	}

	if (it1 == x.end())
		return it2 != y.end();

	return it2 != y.end() && *it1 < *it2;
}

template <class Key, class Compare, class Allocator>
bool operator!=(const RBTree<Key, Compare, Allocator>& x, const RBTree<Key, Compare, Allocator>& y) {
	return !(x == y);
}

template <class Key, class Compare, class Allocator>
bool operator>(const RBTree<Key, Compare, Allocator>& x, const RBTree<Key, Compare, Allocator>& y) {
	return y < x;
}

template <class Key, class Compare, class Allocator>
bool operator>=(const RBTree<Key, Compare, Allocator>& x, const RBTree<Key, Compare, Allocator>& y) {
	return !(x < y);
}

template <class Key, class Compare, class Allocator>
bool operator<=(const RBTree<Key, Compare, Allocator>& x, const RBTree<Key, Compare, Allocator>& y) {
	return   !(y < x);
}
