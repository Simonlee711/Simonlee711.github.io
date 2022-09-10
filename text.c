uint64_t bytes_written;
static uint8_t bytes = 0;
static uint64_t hist[ALPHABET];

void LIpt(Node *root, Stack **s) { //Leaf and Internal Post Traversal
    if (root == NULL) { //->left == NULL && root->right == NULL){
        return;
    }
    LIpt(root->left, s);
    LIpt(root->right, s);
    if (root->left == NULL && root->right == NULL) {
        Node *L = node_create('L', 0);
        stack_push(*s, L);
        stack_push(*s, root);
    }
    if (root->left != NULL && root->right != NULL) {
        Node *I = node_create('I', 0);
        stack_push(*s, I);
    }
}
