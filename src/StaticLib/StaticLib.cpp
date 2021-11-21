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

	if (t->root == NULL) 
	{
		t->root = p;
		return true;
	}

	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する
	/*
	//keyがt->rootの中のkeyがkeyより大きい場合
	if (key < t->root->key)
	{
		//右に追加
		t->root->left = p;
	}
	//keyがt->rootの中のkeyがkeyより小さい場合
	if (key > t->root->key)
	{
		//左に追加
		t->root->right = p;
	}
	*/
	return add_revival(t->root,key, value);
}
//再起関数
bool add_revival(node*p, int key, const char*value)
{
	if (p == NULL) return false;

	if (key < p->key && p->left == NULL)
	{
		p->left = generate(key, value);
		return (p->left != NULL);

		return add_revival(p->left, key, value);
	}

	if (key > p->key && p->right == NULL)
	{
		p->right = generate(key, value);
		return (p->right != NULL);
		
		return add_revival(p->right, key, value);
	}
	

	return true;
}
// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	// ToDo: 実装する
	return NULL;
}

// keyの小さな順にコールバック関数funcを呼び出す
void search(const tree* t, void (*func)(const node* p))
{
	if (t == NULL) return;
	// ToDo: 実装する
}