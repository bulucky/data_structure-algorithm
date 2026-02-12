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

    bool bst_find(int val) {
        return find(val, root_);
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
    bool is_find = false;

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

    bool find(int val, TreeNode* t_node) {
        if (val == t_node->val) {
            is_find = true;
        } else if (t_node->left != nullptr && val < t_node->val) {
            find(val, t_node->left);
        } else if (t_node->right != nullptr && val > t_node->val) {
            find(val, t_node->right);
        }
        return is_find;
    }
};

int main(int argc, char const* argv[]) {
    TreeNode* root = new TreeNode(-1);
    BinarySerachTree* bst = new BinarySerachTree(root);

    bst->bst_insert(-2);
    bst->bst_insert(3);

    bst->bst_print(bst->root_);

    std::cout << "find " << bst->bst_find(4) << "\n";

    delete bst;

    return 0;
}