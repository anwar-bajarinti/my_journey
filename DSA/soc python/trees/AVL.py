class AVLNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1

# Get height of a node
def get_height(node):
    return node.height if node else 0

# Get balance factor of a node
def get_balance(node):
    return get_height(node.left) - get_height(node.right) if node else 0

# Right rotate (for LL imbalance)
def right_rotate(y):
    x = y.left
    T2 = x.right

    # Perform rotation
    x.right = y
    y.left = T2

    # Update heights
    y.height = 1 + max(get_height(y.left), get_height(y.right))
    x.height = 1 + max(get_height(x.left), get_height(x.right))

    return x

# Left rotate (for RR imbalance)
def left_rotate(x):
    y = x.right
    T2 = y.left

    # Perform rotation
    y.left = x
    x.right = T2

    # Update heights
    x.height = 1 + max(get_height(x.left), get_height(x.right))
    y.height = 1 + max(get_height(y.left), get_height(y.right))

    return y

# Insert a key into AVL tree
def insert(root, key):
    # Step 1: Perform normal BST insert
    if not root:
        return AVLNode(key)
    if key < root.key:
        root.left = insert(root.left, key)
    else:
        root.right = insert(root.right, key)

    # Step 2: Update height of this node
    root.height = 1 + max(get_height(root.left), get_height(root.right))

    # Step 3: Get the balance factor
    balance = get_balance(root)

    # Step 4: Balance the tree with rotations

    # Case 1 - Left Left
    if balance > 1 and key < root.left.key:
        return right_rotate(root)

    # Case 2 - Right Right
    if balance < -1 and key > root.right.key:
        return left_rotate(root)

    # Case 3 - Left Right
    if balance > 1 and key > root.left.key:
        root.left = left_rotate(root.left)
        return right_rotate(root)

    # Case 4 - Right Left
    if balance < -1 and key < root.right.key:
        root.right = right_rotate(root.right)
        return left_rotate(root)

    return root

# Inorder traversal (left, root, right)
def inorder(root):
    if root:
        inorder(root.left)
        print(root.key, end=" ")
        inorder(root.right)


if __name__ == "__main__":
    root = None
    values = [10, 20, 30, 40, 50, 25]  # This triggers all types of rotations
    for val in values:
        root = insert(root, val)

    print("Inorder traversal of the AVL tree is:")
    inorder(root)  # Output: 10 20 25 30 40 50
    print()
