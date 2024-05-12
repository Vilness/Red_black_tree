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

public:
	//  Эти типы должен объявлять контейнер - для функциональности
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
	class iterator;   //  Предварительное объявление класса iterator, т.к. он определён ниже	
	using const_iterator = iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
	// Указательно на фиктивную вершину
	RBTreeNode* dummy;

	//  Количесто элементов в дереве
	size_type tree_size = 0;

	// Создание фиктивной вершины - используется только при создании дерева
	inline RBTreeNode* make_dummy()
	{
		// Выделяем память по размеру узла без конструирования
		dummy = Alc.allocate(1);

		//  Все поля, являющиеся указателями на узлы (left, right, parent) инициализируем и обнуляем
		std::allocator_traits<AllocType>::construct(Alc, &(dummy->parent));
		dummy->parent = dummy;

		std::allocator_traits<AllocType>::construct(Alc, &(dummy->left));
		dummy->left = dummy;

		std::allocator_traits<AllocType>::construct(Alc, &(dummy->right));
		dummy->right = dummy;

		dummy->isNull = true;
		dummy->color = true;

		//  Возвращаем указатель на созданную вершину
		return dummy;
	}

	// Создание узла дерева 
	inline RBTreeNode* make_node(T&& elem, RBTreeNode* parent, RBTreeNode* left, RBTreeNode* right, bool color)
	{
		// Создаём точно так же, как и фиктивную вершину, только для поля данных нужно вызвать конструктор
		RBTreeNode* new_node = Alc.allocate(1);

		//  Все поля, являющиеся указателями на узлы (left, right, parent) инициализируем и обнуляем
		std::allocator_traits<AllocType>::construct(Alc, &(new_node->parent));
		new_node->parent = parent;

		std::allocator_traits<AllocType>::construct(Alc, &(new_node->left));
		new_node->left = left;

		std::allocator_traits<AllocType>::construct(Alc, &(new_node->right));
		new_node->right = right;

		//  Конструируем поле данных
		std::allocator_traits<AllocType>::construct(Alc, &(new_node->data), std::forward<T>(elem));

		new_node->isNull = false;
		new_node->color = color;

		//  Возвращаем указатель на созданную вершину
		return new_node;
	}

	// Удаление фиктивной вершины
	inline void delete_dummy(RBTreeNode* node) {
		std::allocator_traits<AllocType>::destroy(Alc, &(node->parent));
		std::allocator_traits<AllocType>::destroy(Alc, &(node->left));
		std::allocator_traits<AllocType>::destroy(Alc, &(node->right));
		std::allocator_traits<AllocType>::deallocate(Alc, node, 1);
	}

	// Удаление вершины дерева
	inline void delete_node(RBTreeNode* node) {
		//  Тут удаляем поле данных (вызывается деструктор), а остальное удаляем так же, как и фиктивную
		std::allocator_traits<AllocType>::destroy(Alc, &(node->data));
		delete_dummy(node);
	}

	//  Рекурсивное копирование дерева
	RBTreeNode* recur_copy_tree(RBTreeNode* source, const RBTreeNode* source_dummy) {
		//  Сначала создаём дочерние поддеревья
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

		//  Теперь создаём собственный узел
		RBTreeNode* current = make_node(std::move(source->data), nullptr, left_sub_tree, right_sub_tree, source->color);
		//  Устанавливаем родителей
		if (source->right != source_dummy)
			current->right->parent = current;
		if (source->left != source_dummy)
			current->left->parent = current;
		//  Ну и всё, можно возвращать
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
		/*for (const auto& x : il)
			insert(x);*/
	}

	RBTree(const RBTree& tree) : RBTree() {
		//  Размер задаём
		tree_size = tree.tree_size;
		if (tree.empty()) return;

		dummy->left = recur_copy_tree(tree.dummy->left, tree.dummy);
		dummy->left->parent = dummy;

		//  Осталось установить min и max
		dummy->parent = GetMax(dummy->left);
		dummy->right = GetMin(dummy->left);
	}

	RBTree(RBTree&& tree) : RBTree() {
		this->swap(tree);
	}

	const RBTree& operator=(RBTree&& tree) {
		this->swap(tree);
		return *this;
	}

	const RBTree& operator=(const RBTree& tree)
	{
		if (this == &tree) return *this;

		this->clear();

		//  Размер задаём
		tree_size = tree.tree_size;
		if (tree.empty()) return;

		dummy->left = recur_copy_tree(tree.dummy->left, tree.dummy);
		dummy->left->parent = dummy;

		//  Осталось установить min и max
		dummy->parent = GetMax(dummy->left);
		dummy->right = GetMin(dummy->left);

		return *this;
	}

	//  Класс итератора для красно-черного дерева дерева поиска
	class iterator
	{
		friend class RBTree;
	protected:
		//  Указатель на узел дерева
		RBTreeNode* node;
	public:
		//  Определяем стандартные типы в соответствии с требованиями стандарта к двунаправленным итераторам
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = RBTree::value_type;
		using difference_type = RBTree::difference_type;
		using pointer = RBTree::pointer;
		using reference = RBTree::reference;

		//  Значение в узле, на который указывает итератор
		inline const T& operator*() const { return node->data; }

		//  Преинкремент - следующий элемент множества
		iterator& operator++() {
			if (!node->right->isNull) {
				node = GetMin(node->right);
				return *this;
			}

			while (!node->parent->isNull && node->parent->right == node)
				node = node->parent;			
			return *this;
		}

		//  Предекремент - переход на предыдущий элемент множества
		iterator& operator--() {
			if (!node->left->isNull) {
				node = GetMax(node->left);
				return *this;
			}

			while (!node->parent->isNull && node->parent->left == node)
				node = node->parent;			
			return *this;
		}

		//  Постинкремент
		iterator operator++(int) {
			iterator res(*this);
			++(*this);
			return res;
		}

		//  Постдекремент
		iterator operator--(int) {
			iterator res(*this);
			--(*this);
			return res;
		}

		friend bool operator==(const iterator& it_1, const iterator& it_2) { return it_1.node == it_2.node; }

		friend bool operator != (const iterator& it_1, const iterator& it_2) { return !(it_1 == it_2); }

		//  Эти операции не допускаются между прямыми и обратными итераторами
		const iterator& operator=(const reverse_iterator& it) = delete;
		bool operator==(const reverse_iterator& it) = delete;
		bool operator!=(const reverse_iterator& it) = delete;
		iterator(const reverse_iterator& it) = delete;
	};

	iterator begin() const noexcept { return iterator(dummy->right); }
	iterator end() const noexcept { return iterator(dummy); }

	reverse_iterator rbegin() const	noexcept { return reverse_iterator(iterator(dummy)); }
	reverse_iterator rend() const noexcept { return reverse_iterator(iterator(dummy->right)); }

	AllocType get_allocator() const noexcept { return Alc; }
	key_compare key_comp() const noexcept { return cmp; }
	value_compare value_comp() const noexcept { return cmp; }

	inline bool empty() const noexcept { return tree_size == 0; }

	size_type size() const { return tree_size; }

	void swap(RBTree& tree) {
		std::swap(tree_size, tree.tree_size);
		std::swap(dummy, tree->dummy);
	}

	///Вставка элемента в дерево
	std::pair<iterator, bool> insert(const T& value) {}

	//Вставка элемента в дерево
	std::pair<iterator, bool> insert(T&& value) {}

	//Вставка диапазона
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {}

	//Возвращает итератор на элемент, с ключом value, если его нет, то end()
	iterator find(const value_type& value) const {}

	//Итератор на минимальный элемент
	iterator GetMin() {}

	//Итератор на максимальный элемент
	iterator GetMax() {}

	//Итeратор на наибольший элемент, меньший или равный заданному
	iterator lower_bound(const value_type& key) const {}

	//Итeратор на наименьший элемент, больший или равный заданному
	iterator upper_bound(const value_type& key) const {}

	//Зачем?
	size_type count(const value_type& key) const {
		return find(key) != end() ? 1 : 0;
	}

	//Че делает?
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

private:
	///Заменяет поддерево dest, на поддерево subtree
	void transplant(iterator dest, iterator subtree) {}

public:
	//  Удаление элемента, заданного итератором. Возвращает следующий элемент после удаленного
	iterator erase(iterator elem) {}

	//Удаляет элемент со значением elem, если его нет возвращает 0, иначе 1
	size_type erase(const value_type& elem) {}

	//  Проверить!!!
	iterator erase(const_iterator first, const_iterator last) {}

private:
	///Переименовать
	void infixWalk(iterator root) {}

public:
	///Обход ЛКП (переименовать)
	void TreeWalkLeftRootRight() {
		infixWalk(iterator(dummy->left));
	}

	///Обход ПКЛ (переименовать)
	void TreeWalkRightRootLeft() {}

	///Обход дерева по уровням (переименовать)
	void TreeWalkLevelOrdered() {}

private:
	bool recur_equal(RBTreeNode* root1, RBTreeNode* root2) const {}
public:
	///Рекурсивное сравнение двух деревьев по элементам и по структуре
	bool isEqualTo(const RBTree<T>& tree) const {
		return recur_equal(dummy->left, tree.dummy->left);
	}

	//Если передавать по ссылкам,все хорошо. Конструктор копий принескольких деревьях ломается.
	friend bool operator==(const RBTree<T>& tree_1, const RBTree<T>& tree_2) {
		return tree_1.isEqualTo(tree_2);
	}

private:
	//  Рекурсивное удаление узлов дерева, не включая фиктивную вершину
	void Free_nodes(RBTreeNode* node) {
		if (node != dummy) {
			Free_nodes(node->left);
			Free_nodes(node->right);
			delete_node(node);
		}
	}

public:
	//  Очистка дерева (без удаления фиктивной вершины)
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

//Посмотреть, что в заготовке происходит и зачем вообще эта хуйня нужна:

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
