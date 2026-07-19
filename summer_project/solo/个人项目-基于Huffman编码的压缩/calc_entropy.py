import math
import heapq
from collections import Counter
import os

def calc_entropy_and_efficiency(filepath):
    with open(filepath, 'rb') as f:
        data = f.read()
    
    length = len(data)
    counter = Counter(data)
    
    entropy = 0.0
    for count in counter.values():
        p = count / length
        entropy -= p * math.log2(p)
        
    class Node:
        def __init__(self, freq, char=None, left=None, right=None):
            self.freq = freq
            self.char = char
            self.left = left
            self.right = right
            
        def __lt__(self, other):
            if self.freq != other.freq:
                return self.freq < other.freq
            c1 = self.char if self.char is not None else 256
            c2 = other.char if other.char is not None else 256
            return c1 < c2

    heap = []
    for char, count in counter.items():
        heapq.heappush(heap, Node(count, char))
        
    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        parent = Node(left.freq + right.freq, left=left, right=right)
        heapq.heappush(heap, parent)
        
    depths = {}
    def traverse(node, depth):
        if node.char is not None:
            depths[node.char] = depth
            return
        traverse(node.left, depth + 1)
        traverse(node.right, depth + 1)
        
    root = heap[0]
    traverse(root, 0)
    
    L = 0.0
    for char, count in counter.items():
        p = count / length
        L += p * depths[char]
        
    efficiency = (entropy / L) * 100
    
    print(f"\n--- {os.path.basename(filepath)} ---")
    print(f"Total Bytes: {length}")
    print("Top 3 Characters by frequency:")
    top3 = counter.most_common(3)
    for char, count in top3:
        p = count / length
        code_len = depths[char]
        h_contrib = -p * math.log2(p)
        l_contrib = p * code_len
        char_display = chr(char) if 32 <= char <= 126 else f"HEX:{char:02x}"
        print(f"  Char: '{char_display}', Count: {count}, p_i: {p:.4f}, CodeLen: {code_len}")
        print(f"  -> H contrib: {h_contrib:.4f}, L contrib: {l_contrib:.4f}")
    
    return entropy, L, efficiency

files = [
    r"c:\Users\ziton\Data_Structures\summer_project\solo\个人项目-基于Huffman编码的压缩\test_suite\hamlet.txt"
]

for file in files:
    calc_entropy_and_efficiency(file)
