class BSTNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

# Insertion
def insert(root, key):
    if root is None:
        return BSTNode(key)
    if key < root.key:
        root.left = insert(root.left, key)
    else:
        root.right = insert(root.right, key)
    return root

# Search
def search(root, key):
    if root is None or root.key == key:
        return root
    if key < root.key:
        return search(root.left, key)
    return search(root.right,key)

# Inorder Traversal
def inorder(root):
    if root:
        inorder(root.left)
        print(root.key, end=" ")
        inorder(root.right)

# Deletion
def delete(root, key):
    if root is None:
        return root
    if key < root.key:
        root.left = delete(root.left, key)
    elif key > root.key:
        root.right = delete(root.right, key)
    else:
        if root.left is None:
            return root.right
        elif root.right is None:
            return root.left
        temp = min_value_node(root.right)
        root.key = temp.key
        root.right = delete(root.right, temp.key)
    return root

def min_value_node(node):
    current = node
    while current.left:
        current = current.left
    return current

# -------------------------------
# ✅ DRIVER CODE (Test Inputs)
# -------------------------------
if __name__ == "__main__":
    root = None
    values = [50, 30, 20, 40, 70, 60, 80]
    for val in values:
        root = insert(root, val)

    print("Inorder traversal of BST:")
    inorder(root)  # Output: 20 30 40 50 60 70 80
    print("\n")

    # Search
    key = 40
    found = search(root, key)
    if found:
        print(f"Key {key} found in BST.")
    else:
        print(f"Key {key} not found.")

    # Delete
    key_to_delete = 30
    root = delete(root, key_to_delete)
    print(f"\nInorder after deleting {key_to_delete}:")
    inorder(root)  # Output: 20 40 50 60 70 80
    print()
