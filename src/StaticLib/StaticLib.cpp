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
	memcpy(p->value, value, strlen(value) + 1);

	p->left = p->right = NULL;

	return p;
}

// keyの値を見てノードを追加する
bool add(tree* t, int key, const char* value)
{
	if (t == NULL) return false;

	node* p = generate(key, value);
	node* tempo;

	if (p == NULL) return false;// メモリ確保できなかった。

	if (t->root == NULL) {
		t->root = p;
		return true;
	}

	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する

	//if (t->root->right != NULL) {
	//	if (key > t->root->key) {

	//		if (key > t->root->right->key) {
	//			tempo = t->root->right;
	//			t->root->right = p;
	//			t->root->left = t->root;
	//			t->root = tempo;
	//			return true;
	//		}
	//		else
	//		{
	//			tempo = t->root;
	//			t->root = p;
	//			t->root->left = tempo;
	//		}
	//	}
	//}

	//if (t->root->left != NULL) {
	//	if (key < t->root->key) {
	//		if (key < t->root->left->key) {
	//			tempo = t->root;
	//			t->root = t->root->left;
	//			t->root->right = tempo;
	//			t->root->left = p;
	//			return true;
	//		}
	//		else
	//		{
	//			tempo = t->root;
	//			t->root = p;
	//			t->root->right = tempo;
	//		}
	//	}
	//}

	if (t->root->key == p->key)
	{
		memcpy(t->root->value, p->value, sizeof(char) * 256);
		free(p);
		return true;
	}

	if (t->root->left == NULL && t->root->right == NULL) {

		if (key > t->root->key) {
			t->root->right = p;
		}
		else
		{
			t->root->left = p;
		}
	}
	return true;
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	// ToDo: 実装する
	if (t == NULL || key < -1) return NULL;



	if (key == t->root->key) {
		return t->root->value;
	}

	if (key == t->root->left->key && t->root->left != NULL)
	{
		return t->root->left->value;
	}
	if (key == t->root->right->key && t->root->right != NULL)
	{
		return t->root->right->value;
	}

	return NULL;
}

// keyの小さな順にコールバック関数funcを呼び出す
void search(const tree* t, void (*func)(const node* p))
{
	// ToDo: 実装する
	if (t->root->left != NULL) {
		func(t->root->left);
	}

	func(t->root);

	if (t->root->right != NULL) {
		func(t->root->right);
	}
}