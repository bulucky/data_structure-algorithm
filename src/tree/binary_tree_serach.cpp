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
        is_find = false;
        return find(val, root_);
    }

    bool bst_delete(int val) {
        is_remove = false;
        pre = root_;
        return remove(val, root_);
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
    bool is_remove = false;
    bool is_left = false;
    TreeNode* pre = nullptr;

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

    bool remove(int val, TreeNode* t_node) {
        if (val == t_node->val) {
            is_remove = true;
            if (t_node->left == nullptr && t_node->right == nullptr) {
                delete t_node;
                t_node = nullptr;
                if (is_left) {
                    pre->left = nullptr;
                } else {
                    pre->right = nullptr;
                }
            } else if (t_node->left == nullptr || t_node->right == nullptr) {
                if (t_node->left == nullptr) {
                    t_node->val = t_node->right->val;
                    delete t_node->right;
                    t_node->right = nullptr;
                } else {
                    t_node->val = t_node->left->val;
                    delete t_node->left;
                    t_node->left = nullptr;
                }
            } else {
                TreeNode* tmp = t_node;
                tmp->val = val;
                // remove(val, t_node->right);
            }
        } else if (t_node->left != nullptr && val < t_node->val) {
            pre = t_node;
            is_left = true;
            remove(std::forward<int>(val), t_node->left);
        } else if (t_node->right != nullptr && val > t_node->val) {
            pre = t_node;
            is_left = false;
            remove(std::forward<int>(val), t_node->right);
        }

        return is_remove;
    }
};

int main(int argc, char const* argv[]) {
    TreeNode* root = new TreeNode(-1);
    BinarySerachTree* bst = new BinarySerachTree(root);

    bst->bst_insert(-3);
    bst->bst_insert(3);
    bst->bst_insert(-6);
    bst->bst_insert(-5);
    bst->bst_insert(2);
    bst->bst_insert(5);

    bst->bst_print(bst->root_);
    std::cout << "\n";

    std::cout << "find " << bst->bst_find(4) << "\n";
    std::cout << "find " << bst->bst_find(-2) << "\n";
    std::cout << "find " << bst->bst_find(3) << "\n";
    std::cout << "find " << bst->bst_find(5) << "\n";

    bst->bst_delete(2);

    bst->bst_print(bst->root_);

    delete bst;

    return 0;
}