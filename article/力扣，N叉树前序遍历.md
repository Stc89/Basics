# 力扣，N叉树前序遍历

题目链接

```
https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/
```

题目

给定一个 N 叉树，返回其节点值的前序遍历。

例如，给定一个 3叉树 :

 

![img](C:%5CUsers%5C32941%5CDesktop%5Cnarytreeexample.png)

 

返回其前序遍历: [1,3,5,6,2,4]。

 

说明: 递归法很简单，你可以使用迭代法完成此题吗?

# #解答

前序遍历就是从左边找，一直往右边查找

代码

```
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    void pre(Node* root,vector<int>& t)
    {
        if(!root)//如果root是空的就返回
            return;
        t.push_back(root->val);
        for(auto p:root->children)//C++ 11的for写法
            pre(p,t);
    }
    vector<int> preorder(Node* root) 
    {
        vector<int> result;
        pre(root,result);
        return result; //输出结果
    }
};
```

输出

![image-20201104214052475](C:%5CUsers%5C32941%5CDesktop%5Cimage-20201104214052475.png)