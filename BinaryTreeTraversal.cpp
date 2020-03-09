#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {    //二叉树遍历迭代算法（非递归）
public:
	vector<int> preorderTraversal(TreeNode* root) {    //二叉树先序遍历
		if (root == NULL) {
			return ans;
		}
		treeStack.push(root);
		while (!treeStack.empty()) {
			TreeNode* p = treeStack.top();
			treeStack.pop();
			ans.push_back(p->val);
			if (p->right != NULL) {
				treeStack.push(p->right);
			}
			if (p->left != NULL) {
				treeStack.push(p->left);
			}
		}
		return ans;
	}

	vector<int> postorderTraversal(TreeNode* root) {    //二叉树后续遍历
		if (root == NULL) {
			return ans;
		}
		treeStack.push(root);
		while (!treeStack.empty()) {
			TreeNode* p = treeStack.top();
			treeStack.pop();
			ans.push_back(p->val);
			if (p->left != NULL) {
				treeStack.push(p->left);
			}
			if (p->right != NULL) {
				treeStack.push(p->right);
			}
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}

	vector<int> inorderTraversal(TreeNode* root) {    //二叉树中序遍历
		TreeNode* p = root;
		while (p != NULL || !treeStack.empty()) {
			while (p != NULL) {
				treeStack.push(p);
				p = p->left;
			}
			p = treeStack.top();
			treeStack.pop();
			ans.push_back(p->val);
			p = p->right;
		}
		return ans;
	}

	vector<int> levelOrder0(TreeNode* root) {    //二叉树层次遍历，顺序输出
		treeQueue.push(root);
		while (!treeQueue.empty()) {
			TreeNode* p = treeQueue.front();
			treeQueue.pop();
			ans.push_back(p->val);
			if (p->left != NULL) {
				treeQueue.push(p->left);
			}
			if (p->right != NULL) {
				treeQueue.push(p->right);
			}
		}
		return ans;
	}

	vector<vector<int>> levelOrder(TreeNode* root) {    //二叉树层次遍历，逐层输出
		if (root == NULL) {
			return anss;
		}
		treeQueue.push(root);
		while (!treeQueue.empty()) {
			vector<int> level;
			int l = treeQueue.size();
			while (l-- != 0) {
				TreeNode* p = treeQueue.front();
				treeQueue.pop();
				level.push_back(p->val);
				if (p->left != NULL) {
					treeQueue.push(p->left);
				}
				if (p->right != NULL) {
					treeQueue.push(p->right);
				}
			}
			anss.push_back(level);
		}
		return anss;
	}

private:
	stack<TreeNode*> treeStack;
	vector<int> ans;
	queue<TreeNode*> treeQueue;
	vector<vector<int>> anss;
};
