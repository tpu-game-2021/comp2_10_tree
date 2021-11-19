#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// 2分木の初期化
void initialize(tree* t)
{
	if (t == NULL) return;

	t->root = NULL;
}

static void release_recursive(node* n)
{
	if (n == NULL) return;

	if (n->right) {
		release_recursive(n->right);
		n->right = NULL;
	}

	if (n->left) {
		release_recursive(n->left);
		n->left = NULL;
	}

	free(n);
}

// 使用メモリの全解放
void finalize(tree* t)
{
	if (t == NULL) return;

	release_recursive(t->root);
	t->root = NULL;
}


static node* generate(int key, const char* value)
{
	node* p = (node*)malloc(sizeof(node));

	if (p == NULL) return NULL;

	p->key = key;
	int n = (int)strlen(value);
	memcpy(p->value, value, strlen(value)+1);

	p->left = p->right = NULL;

	return p;
}

// keyの値を見てノードを追加する
bool add(tree* t, int key, const char* value)
{
	if (t == NULL) return false;

	node* p = generate(key, value);
	if (p == NULL) return false;// メモリ確保できなかった。


	if (t->root == NULL) {
		t->root = p;
		return true;
	}
	node* attention = t->root;
	while (1)
	{
		if (attention->key == p->key)
		{
			memcpy(attention->value, p->value,sizeof(char)*256);
			free(p);
			return true;
		}
		else if (attention->key > p->key) {
			if (attention->left == NULL) {
				attention->left = p;
				return true;
			}
			attention = attention->left;
		}
		else {
			if (attention->right == NULL) {
				attention->right = p;
				return true;
			}
			attention = attention->right;
		}
	}


	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する

	return false;
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	// ToDo: 実装する
	if (t->root == NULL) { return NULL; }

	node* attention = t->root;
	while (1)
	{
		if (attention == NULL){
			return NULL;
		}
		else if (attention->key == key) {
			return (attention->value);
		}
		else if(attention->key>key){
			attention = attention->left;
		}
		else{
			attention = attention->right;
		}
	}
	return NULL;
}

// keyの小さな順にコールバック関数funcを呼び出す
void mysearch( node* attention, void (*func)(const node* p))
{
	if (attention->left) {
		mysearch(attention->left, func);
	}
	func(attention);
	if (attention->right) {
		mysearch(attention->right, func);
	}
}
void search(const tree* t, void (*func)(const node* p))
{
	// ToDo: 実装する
	mysearch(t->root, func);
}
