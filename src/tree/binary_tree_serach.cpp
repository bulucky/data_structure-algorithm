#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(int val) : val(val) {}
};

class BinarySerachTree {
public:
    TreeNode* root_ = nullptr;

    BinarySerachTree(TreeNode* root)
        : root_(root) {
    }

    ~BinarySerachTree() {
        delete root_;
        root_ = nullptr;
    }

    void bst_insert(int val) {
        TreeNode* n_node = new TreeNode(val);
        insert(n_node, root_);
    }

    void bst_find(int val) {
    }

    void bst_delete(int val) {
    }

    void bst_print(TreeNode* root = nullptr) {
        if (root == nullptr) {
            return;
        }
        std::cout << root->val << " ";
        bst_print(root->left);
        bst_print(root->right);
    }

private:
    void insert(TreeNode* n_node, TreeNode* t_node) {
        if (n_node->val < t_node->val) {
            if (t_node->left == nullptr) {
                t_node->left = n_node;
                return;
            } else {
                insert(n_node, t_node->left);
            }
        } else if (n_node->val > t_node->val) {
            if (n_node->val > t_node->val) {
                if (t_node->right == nullptr) {
                    t_node->right = n_node;
                    return;
                } else {
                    insert(n_node, t_node->right);
                }
            }
        }
    }
};

int main(int argc, char const* argv[]) {
    TreeNode* root = new TreeNode(-1);
    BinarySerachTree* bst = new BinarySerachTree(root);

    bst->bst_insert(-2);
    bst->bst_insert(3);

    bst->bst_print(bst->root_);

    delete bst;

    return 0;
}