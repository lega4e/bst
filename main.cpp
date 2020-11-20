/*
 * autor:   lis
 * created: Nov 13 2020
 * changed: Nov 20 03:37:20 2020
 */

#include <cstring>
#include <iostream>

#include <lis/macro.hpp>


using namespace std;





// types
/*
 * Структура узла; содержит 
 * 1. Ключ
 * 2. Указателей на левого и правого ребёнка
 * 3. Указатель на родителя
 */
struct Node
{
	int key;
	Node *left = nullptr;
	Node *right = nullptr;
	Node *parent = nullptr;

	/*
	 * Этот метод рекурсивно выводит (под)дерево, указывая,
	 * является ли поддерево левым или правым ребёнком 
	 */
	void print(string const &tab = "", char ch = 0) const
	{
		cout << tab;
		if(ch)
			cout << (ch == 'l' ? "l: " : "r: ");
		cout << key;
		if(left) cout.put('\n'), left->print(tab + "  ", 'l');
		if(right) cout.put('\n'), right->print(tab + "  ", 'r');
		return;
	}
};





// Процедуры
/*
 * Освобождает память (под)дерева
 * (реализует обратный обход дерева с
 * операцией delete)
 */
void free(Node *node)
{
	if(node)
	{
		free(node->left);
		free(node->right);
		delete node;
	}

	return;
}



// Три алгоритма обхода
/*
 * Алгоритм центрированного обхода дерева:
 * обработка самого узла происходит между
 * его поддеревьями
 */
template<typename Functor>
void inorder_wolk(Node *n, Functor f)
{
	if(!n)
		return;

	inorder_wolk(n->left, f);
	f(n);
	inorder_wolk(n->right, f);
	return;
}

/*
 * Алгоритм обхода бинарного дерева в
 * прямом порядке: сначала обратывается
 * сам узел и лишь затем его поддеревья
 */
template<typename Functor>
void preorder_walk(Node *n, Functor f)
{
	if(!n)
		return;

	f(n);
	inorder_wolk(n->left, f);
	inorder_wolk(n->right, f);
	return;
}

/*
 * Алгоритм обхода бинарного дерева в
 * обратном порядке: сперва берутся 
 * поддеревья данного узла и после —
 * сам узел
 */
template<typename Functor>
void postorder_walk(Node *n, Functor f)
{
	if(!n)
		return;

	inorder_wolk(n->left, f);
	inorder_wolk(n->right, f);
	f(n);
	return;
}



// Поиск элементов
/*
 * Рекурсивный алгоритм поиска по ключу
 * за время порядка O(h), где h — высота
 * дерева
 */
Node *find_recursive(Node *node, int key)
{
	 if(!node || node->key == key)
		 return node;
	 return key < node->key ?
		 find_recursive(node->left, key) :
		 find_recursive(node->right, key);
}

/*
 * Итеративный алгоритм поиска по ключу
 * за время порядка O(h), где h — высота
 * дерева
 */
Node *find(Node *node, int key)
{
	while(node && node->key != key)
		node = key < node->key ? node->left : node->right;
	return node;
}

/*
 * Нахождение минимального элемента
 * (другими словами, первого) — самого
 * левого
 */
Node *min(Node *node)
{
	if(!node)
		return nullptr;
	while(node->left)
		node = node->left;
	return node;
}

/*
 * Нахождение максимального элемента 
 * (другими словами, последнего) —
 * самого правого
 */
Node *max(Node *node)
{
	if(!node)
		return nullptr;
	while(node->right)
		node = node->right;
	return node;
}

/*
 * Нахождение следующего элемента, которым
 * является либо первый в правом поддереве,
 * либо первый предок, содержащий текущий
 * узел в левом педдереве
 */
Node *next(Node *node)
{
	if(!node or node->right)
		return min(node->right);

	while(node->parent and node != node->parent->left)
		node = node->parent;

	return node->parent;
}

/*
 * Нахождение предыдущего элемента, которым
 * является либо последний (наибольший) в
 * левом поддереве, либо первый предок,
 * содержащий текущий узел в правом 
 * поддереве
 */
Node *prev(Node *node)
{
	if(!node or node->left)
		return max(node->left);

	while(node->parent and node != node->parent->right)
		node = node->parent;

	return node->parent;
}





// Алгоритмы изменения структуры дерева
/*
 * Алгоритм вставки ключа: находит крайний
 * узел и вставляет новый узел с заданным
 * ключом левым или правым ребёнком; если
 * ключ уже существует, возвращает ложь;
 * если дерево пустое, вставляет ключ на 
 * место корня
 */
bool insert(Node **tree, int key)
{
	Node *prev = nullptr;
	Node *node = *tree;
	while(node)
	{
		if(key == node->key)
			return false;

		prev = node;
		if(key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	Node *inserting = new Node { key };
	inserting->parent = prev;
	if(!prev)
		*tree = inserting;
	else if(key < prev->key)
		prev->left = inserting;
	else
		prev->right = inserting;
	return true;
}

/*
 * Вспомогательная функция, которая перемещает узел
 * what на место where (ставит в соответствие указатель
 * на дочерний элемент у родителя lhs и указатель на
 * родителя у rhs).
 *
 * Оставляет неккоректными указатели where->parent и
 * what->parent->left или what->parent->right (в
 * завимисости от того, каким — левым или правым —
 * узлом был what)
 */
void replant(Node **tree, Node *where, Node *what)
{
	// set parent -> child link
	if(!where->parent)
		*tree = what;
	else if(where == where->parent->left)
		where->parent->left = what;
	else
		where->parent->right = what;

	// set child -> parent link
	if(what)
		what->parent = where->parent;

	return;
}

/*
 * Алгоритм удаления элемента из дерева;
 * возвращает истину, если был создан новый
 * узел и ложь, если узел с таким ключом уже
 * существовал
 */
bool erase(Node **tree, int key)
{
	Node *rmnode = find(*tree, key);
	if(!rmnode)
		return false;

	if(!rmnode->right)
	{
		replant(tree, rmnode, rmnode->left);
		delete rmnode;
		return true;
	}

	if(!rmnode->left)
	{
		replant(tree, rmnode, rmnode->right);
		delete rmnode;
		return true;
	}

	Node *nx = next(rmnode);
	if(nx->parent != rmnode)
	{
		replant(tree, nx, nx->right);
		nx->right = rmnode->right;
		nx->right->parent = nx;
	}

	replant(tree, rmnode, nx);
	nx->left = rmnode->left;
	nx->left->parent = nx;

	delete rmnode;
	return true;
}



// Прочие алгоритмы
/*
 * Алгоритм, который проверяет, является
 * ли данное бинарное дерево бинарным
 * деревом поиска
 */
bool is_bst(Node *node, int *min = nullptr, int *max = nullptr)
{
	if(!node)
		return true;

	if(
		( min and node->key < *min ) or
		( max and node->key > *max ) or
		( node->left  and node->left->key  > node->key ) or
		( node->right and node->right->key < node->key )
	)
	{
		return false;
	}

	return
		is_bst(node->left,  min, &node->key) and
		is_bst(node->right, &node->key, max);
}





// main
/*
 * Основная функция программы реализует 
 * следующие команды:
 * + KEY // добавить ключ KEY в дерево
 * - KEY // удалить ключ KEY из дерева
 * p     // отобразить дерево
 *
 * При выполнении каждой команды выполняется
 * проверка, является ли дерево BST.
 *
 * Для выхода используйте CTRL+D.
 */
int main( int argc, char *argv[] )
{
	char com;
	int val;
	string nil;
	Node *tree = nullptr;

	TRY

	while(cin >> com)
	{
		switch(com)
		{
		case '+':
			cin >> val;
			if(!cin)
				goto invalid_command;

			if(insert(&tree, val))
				 cout << "Success inserting " << val << endl;
			else
				 cout << "Value " << val << " already exists" << endl;
			break;

		case '-':
			cin >> val;
			if(!cin)
				goto invalid_command;

			if(erase(&tree, val))
				 cout << "Success erase " << val << endl;
			else
				 cout << "No found " << val << endl;
			break;

		case 'p':
			if(tree)
				tree->print();
			cout << endl;
			break;

		default:
			cerr << "Unknown command" << endl;
			getline(cin, nil);
			break;

		invalid_command:
			cerr << "Invalid command" << endl;
			cin.clear();
			getline(cin, nil);
			continue;
		}
		
		if(!is_bst(tree))
			throw "It's no BST!";
	}
	
	CATCH

	free(tree);

	return 0;
}





// end
